/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the either Technology Preview License Agreement or the
** Beta Release License Agreement.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QCONTIGUOUSCACHE_H
#define QCONTIGUOUSCACHE_H

#include <QtCore/qatomic.h>
#include <limits.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Core)

struct Q_CORE_EXPORT QContiguousCacheData
{
    QBasicAtomicInt ref;
    int alloc;
    int count;
    int start;
    int offset;
    uint sharable : 1;

    void dump() const;
};

template <typename T>
struct QContiguousCacheTypedData
{
    QBasicAtomicInt ref;
    int alloc;
    int count;
    int start;
    int offset;
    uint sharable : 1;

    T array[1];
};

template<typename T>
class QContiguousCache {
    typedef QContiguousCacheTypedData<T> Data;
    union { QContiguousCacheData *p; QContiguousCacheTypedData<T> *d; };
public:
    explicit QContiguousCache(int capacity = 0);
    QContiguousCache(const QContiguousCache<T> &v) : d(v.d) { d->ref.ref(); if (!d->sharable) detach_helper(); }

    inline ~QContiguousCache() { if (!d) return; if (!d->ref.deref()) free(d); }

    inline void detach() { if (d->ref != 1) detach_helper(); }
    inline bool isDetached() const { return d->ref == 1; }
    inline void setSharable(bool sharable) { if (!sharable) detach(); d->sharable = sharable; }

    QContiguousCache<T> &operator=(const QContiguousCache<T> &other);
    bool operator==(const QContiguousCache<T> &other) const;
    inline bool operator!=(const QContiguousCache<T> &other) const { return !(*this == other); }

    inline int capacity() const {return d->alloc; }
    inline int count() const { return d->count; }
    inline int size() const { return d->count; }

    inline bool isEmpty() const { return d->count == 0; }
    inline bool isFull() const { return d->count == d->alloc; }
    inline int available() const { return d->alloc - d->count; }

    void clear();
    void setCapacity(int size);

    const T &at(int pos) const;
    T &operator[](int i);
    const T &operator[](int i) const;

    void append(const T &value);
    void prepend(const T &value);
    void insert(int pos, const T &value);

    inline bool containsIndex(int pos) const { return pos >= d->offset && pos - d->offset < d->count; }
    inline int firstIndex() const { return d->offset; }
    inline int lastIndex() const { return d->offset + d->count - 1; }

    inline const T &first() const { Q_ASSERT(!isEmpty()); return d->array[d->start]; }
    inline const T &last() const { Q_ASSERT(!isEmpty()); return d->array[(d->start + d->count -1) % d->alloc]; }
    inline T &first() { Q_ASSERT(!isEmpty()); detach(); return d->array[d->start]; }
    inline T &last() { Q_ASSERT(!isEmpty()); detach(); return d->array[(d->start + d->count -1) % d->alloc]; }

    void removeFirst();
    T takeFirst();
    void removeLast();
    T takeLast();

    inline bool areIndexesValid() const
    { return d->offset >= 0 && d->offset < INT_MAX - d->count && (d->offset % d->alloc) == d->start; }

    inline void normalizeIndexes() { d->offset = d->start; }
    // debug
    void dump() const { p->dump(); }
private:
    void detach_helper();

    QContiguousCacheData *malloc(int aalloc);
    void free(Data *x);
    int sizeOfTypedData() {
        // this is more or less the same as sizeof(Data), except that it doesn't
        // count the padding at the end
        return reinterpret_cast<const char *>(&(reinterpret_cast<const Data *>(this))->array[1]) - reinterpret_cast<const char *>(this);
    }
};

template <typename T>
void QContiguousCache<T>::detach_helper()
{
    union { QContiguousCacheData *p; QContiguousCacheTypedData<T> *d; } x;

    x.p = malloc(d->alloc);
    x.d->ref = 1;
    x.d->count = d->count;
    x.d->start = d->start;
    x.d->offset = d->offset;
    x.d->alloc = d->alloc;
    x.d->sharable = true;

    T *dest = x.d->array + x.d->start;
    T *src = d->array + d->start;
    int count = x.d->count;
    while (count--) {
        if (QTypeInfo<T>::isComplex) {
            new (dest) T(*src);
        } else {
            *dest = *src;
        }
        dest++;
        if (dest == x.d->array + x.d->alloc)
            dest = x.d->array;
        src++;
        if (src == d->array + d->alloc)
            src = d->array;
    }

    if (!d->ref.deref())
        free(d);
    d = x.d;
}

template <typename T>
void QContiguousCache<T>::setCapacity(int asize)
{
    if (asize == d->alloc)
        return;
    detach();
    union { QContiguousCacheData *p; QContiguousCacheTypedData<T> *d; } x;
    x.p = malloc(asize);
    x.d->alloc = asize;
    x.d->count = qMin(d->count, asize);
    x.d->offset = d->offset + d->count - x.d->count;
    x.d->start = x.d->offset % x.d->alloc;
    T *dest = x.d->array + (x.d->start + x.d->count-1) % x.d->alloc;
    T *src = d->array + (d->start + d->count-1) % d->alloc;
    int count = x.d->count;
    while (count--) {
        if (QTypeInfo<T>::isComplex) {
            new (dest) T(*src);
        } else {
            *dest = *src;
        }
        if (dest == x.d->array)
            dest = x.d->array + x.d->alloc;
        dest--;
        if (src == d->array)
            src = d->array + d->alloc;
        src--;
    }
    /* free old */
    free(d);
    d = x.d;
}

template <typename T>
void QContiguousCache<T>::clear()
{
    if (d->ref == 1) {
        if (QTypeInfo<T>::isComplex) {
            int count = d->count;
            T * i = d->array + d->start;
            T * e = d->array + d->alloc;
            while (count--) {
                i->~T();
                i++;
                if (i == e)
                    i = d->array;
            }
        }
        d->count = d->start = d->offset = 0;
    } else {
        union { QContiguousCacheData *p; QContiguousCacheTypedData<T> *d; } x;
        x.p = malloc(d->alloc);
        x.d->ref = 1;
        x.d->alloc = d->alloc;
        x.d->count = x.d->start = x.d->offset = 0;
        x.d->sharable = true;
        if (!d->ref.deref()) free(d);
        d = x.d;
    }
}

template <typename T>
inline QContiguousCacheData *QContiguousCache<T>::malloc(int aalloc)
{
    return static_cast<QContiguousCacheData *>(qMalloc(sizeOfTypedData() + (aalloc - 1) * sizeof(T)));
}

template <typename T>
QContiguousCache<T>::QContiguousCache(int capacity)
{
    p = malloc(capacity);
    d->ref = 1;
    d->alloc = capacity;
    d->count = d->start = d->offset = 0;
    d->sharable = true;
}

template <typename T>
QContiguousCache<T> &QContiguousCache<T>::operator=(const QContiguousCache<T> &other)
{
    other.d->ref.ref();
    if (!d->ref.deref())
        free(d);
    d = other.d;
    if (!d->sharable)
        detach_helper();
    return *this;
}

template <typename T>
bool QContiguousCache<T>::operator==(const QContiguousCache<T> &other) const
{
    if (other.d == d)
        return true;
    if (other.d->start != d->start
            || other.d->count != d->count
            || other.d->offset != d->offset
            || other.d->alloc != d->alloc)
        return false;
    for (int i = firstIndex(); i <= lastIndex(); ++i)
        if (!(at(i) == other.at(i)))
            return false;
    return true;
}

template <typename T>
void QContiguousCache<T>::free(Data *x)
{
    if (QTypeInfo<T>::isComplex) {
        int count = d->count;
        T * i = d->array + d->start;
        T * e = d->array + d->alloc;
        while (count--) {
            i->~T();
            i++;
            if (i == e)
                i = d->array;
        }
    }
    qFree(x);
}
template <typename T>
void QContiguousCache<T>::append(const T &value)
{
    detach();
    if (QTypeInfo<T>::isComplex) {
        if (d->count == d->alloc)
            (d->array + (d->start+d->count) % d->alloc)->~T();
        new (d->array + (d->start+d->count) % d->alloc) T(value);
    } else {
        d->array[(d->start+d->count) % d->alloc] = value;
    }

    if (d->count == d->alloc) {
        d->start++;
        d->start %= d->alloc;
        d->offset++;
    } else {
        d->count++;
    }
}

template<typename T>
void QContiguousCache<T>::prepend(const T &value)
{
    detach();
    if (d->start)
        d->start--;
    else
        d->start = d->alloc-1;
    d->offset--;

    if (d->count != d->alloc)
        d->count++;
    else
        if (d->count == d->alloc)
            (d->array + d->start)->~T();

    if (QTypeInfo<T>::isComplex)
        new (d->array + d->start) T(value);
    else
        d->array[d->start] = value;
}

template<typename T>
void QContiguousCache<T>::insert(int pos, const T &value)
{
    Q_ASSERT_X(pos >= 0 && pos < INT_MAX, "QContiguousCache<T>::insert", "index out of range");
    detach();
    if (containsIndex(pos)) {
        if(QTypeInfo<T>::isComplex)
            new (d->array + pos % d->alloc) T(value);
        else
            d->array[pos % d->alloc] = value;
    } else if (pos == d->offset-1)
        prepend(value);
    else if (pos == d->offset+d->count)
        append(value);
    else {
        // we don't leave gaps.
        clear();
        d->offset = pos;
        d->start = pos % d->alloc;
        d->count = 1;
        if (QTypeInfo<T>::isComplex)
            new (d->array + d->start) T(value);
        else
            d->array[d->start] = value;
    }
}

template <typename T>
inline const T &QContiguousCache<T>::at(int pos) const
{ Q_ASSERT_X(pos >= d->offset && pos - d->offset < d->count, "QContiguousCache<T>::at", "index out of range"); return d->array[pos % d->alloc]; }
template <typename T>
inline const T &QContiguousCache<T>::operator[](int pos) const
{ Q_ASSERT_X(pos >= d->offset && pos - d->offset < d->count, "QContiguousCache<T>::at", "index out of range"); return d->array[pos % d->alloc]; }

template <typename T>
inline T &QContiguousCache<T>::operator[](int pos)
{
    detach();
    if (!containsIndex(pos))
        insert(pos, T());
    return d->array[pos % d->alloc];
}

template <typename T>
inline void QContiguousCache<T>::removeFirst()
{
    Q_ASSERT(d->count > 0);
    detach();
    d->count--;
    if (QTypeInfo<T>::isComplex)
        (d->array + d->start)->~T();
    d->start = (d->start + 1) % d->alloc;
    d->offset++;
}

template <typename T>
inline void QContiguousCache<T>::removeLast()
{
    Q_ASSERT(d->count > 0);
    detach();
    d->count--;
    if (QTypeInfo<T>::isComplex)
        (d->array + (d->start + d->count) % d->alloc)->~T();
}

template <typename T>
inline T QContiguousCache<T>::takeFirst()
{ T t = first(); removeFirst(); return t; }

template <typename T>
inline T QContiguousCache<T>::takeLast()
{ T t = last(); removeLast(); return t; }

QT_END_NAMESPACE

QT_END_HEADER

#endif