/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"
#include "JSWebKitTransitionEvent.h"

#include "KURL.h"
#include "WebKitTransitionEvent.h"
#include <runtime/Error.h>
#include <runtime/JSNumberCell.h>
#include <runtime/JSString.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSWebKitTransitionEvent);

/* Hash table */

static const HashTableValue JSWebKitTransitionEventTableValues[4] =
{
    { "propertyName", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsWebKitTransitionEventPropertyName), (intptr_t)0 },
    { "elapsedTime", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsWebKitTransitionEventElapsedTime), (intptr_t)0 },
    { "constructor", DontEnum|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsWebKitTransitionEventConstructor), (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSWebKitTransitionEventTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 7, JSWebKitTransitionEventTableValues, 0 };
#else
    { 8, 7, JSWebKitTransitionEventTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSWebKitTransitionEventConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSWebKitTransitionEventConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSWebKitTransitionEventConstructorTableValues, 0 };
#else
    { 1, 0, JSWebKitTransitionEventConstructorTableValues, 0 };
#endif

class JSWebKitTransitionEventConstructor : public DOMConstructorObject {
public:
    JSWebKitTransitionEventConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
        : DOMConstructorObject(JSWebKitTransitionEventConstructor::createStructure(globalObject->objectPrototype()), globalObject)
    {
        putDirect(exec->propertyNames().prototype, JSWebKitTransitionEventPrototype::self(exec, globalObject), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual bool getOwnPropertyDescriptor(ExecState*, const Identifier&, PropertyDescriptor&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValue proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, StructureFlags), AnonymousSlotCount); 
    }
    
protected:
    static const unsigned StructureFlags = OverridesGetOwnPropertySlot | ImplementsHasInstance | DOMConstructorObject::StructureFlags;
};

const ClassInfo JSWebKitTransitionEventConstructor::s_info = { "WebKitTransitionEventConstructor", 0, &JSWebKitTransitionEventConstructorTable, 0 };

bool JSWebKitTransitionEventConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSWebKitTransitionEventConstructor, DOMObject>(exec, &JSWebKitTransitionEventConstructorTable, this, propertyName, slot);
}

bool JSWebKitTransitionEventConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSWebKitTransitionEventConstructor, DOMObject>(exec, &JSWebKitTransitionEventConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */

static const HashTableValue JSWebKitTransitionEventPrototypeTableValues[2] =
{
    { "initWebKitTransitionEvent", DontDelete|Function, (intptr_t)static_cast<NativeFunction>(jsWebKitTransitionEventPrototypeFunctionInitWebKitTransitionEvent), (intptr_t)5 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSWebKitTransitionEventPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSWebKitTransitionEventPrototypeTableValues, 0 };
#else
    { 2, 1, JSWebKitTransitionEventPrototypeTableValues, 0 };
#endif

const ClassInfo JSWebKitTransitionEventPrototype::s_info = { "WebKitTransitionEventPrototype", 0, &JSWebKitTransitionEventPrototypeTable, 0 };

JSObject* JSWebKitTransitionEventPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSWebKitTransitionEvent>(exec, globalObject);
}

bool JSWebKitTransitionEventPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSWebKitTransitionEventPrototypeTable, this, propertyName, slot);
}

bool JSWebKitTransitionEventPrototype::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticFunctionDescriptor<JSObject>(exec, &JSWebKitTransitionEventPrototypeTable, this, propertyName, descriptor);
}

const ClassInfo JSWebKitTransitionEvent::s_info = { "WebKitTransitionEvent", &JSEvent::s_info, &JSWebKitTransitionEventTable, 0 };

JSWebKitTransitionEvent::JSWebKitTransitionEvent(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<WebKitTransitionEvent> impl)
    : JSEvent(structure, globalObject, impl)
{
}

JSObject* JSWebKitTransitionEvent::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSWebKitTransitionEventPrototype(JSWebKitTransitionEventPrototype::createStructure(JSEventPrototype::self(exec, globalObject)));
}

bool JSWebKitTransitionEvent::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSWebKitTransitionEvent, Base>(exec, &JSWebKitTransitionEventTable, this, propertyName, slot);
}

bool JSWebKitTransitionEvent::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSWebKitTransitionEvent, Base>(exec, &JSWebKitTransitionEventTable, this, propertyName, descriptor);
}

JSValue jsWebKitTransitionEventPropertyName(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSWebKitTransitionEvent* castedThis = static_cast<JSWebKitTransitionEvent*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    WebKitTransitionEvent* imp = static_cast<WebKitTransitionEvent*>(castedThis->impl());
    JSValue result = jsString(exec, imp->propertyName());
    return result;
}

JSValue jsWebKitTransitionEventElapsedTime(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSWebKitTransitionEvent* castedThis = static_cast<JSWebKitTransitionEvent*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    WebKitTransitionEvent* imp = static_cast<WebKitTransitionEvent*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->elapsedTime());
    return result;
}

JSValue jsWebKitTransitionEventConstructor(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSWebKitTransitionEvent* domObject = static_cast<JSWebKitTransitionEvent*>(asObject(slotBase));
    return JSWebKitTransitionEvent::getConstructor(exec, domObject->globalObject());
}
JSValue JSWebKitTransitionEvent::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSWebKitTransitionEventConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}

JSValue JSC_HOST_CALL jsWebKitTransitionEventPrototypeFunctionInitWebKitTransitionEvent(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSWebKitTransitionEvent::s_info))
        return throwError(exec, TypeError);
    JSWebKitTransitionEvent* castedThisObj = static_cast<JSWebKitTransitionEvent*>(asObject(thisValue));
    WebKitTransitionEvent* imp = static_cast<WebKitTransitionEvent*>(castedThisObj->impl());
    const UString& typeArg = args.at(0).toString(exec);
    bool canBubbleArg = args.at(1).toBoolean(exec);
    bool cancelableArg = args.at(2).toBoolean(exec);
    const UString& propertyNameArg = args.at(3).toString(exec);
    double elapsedTimeArg = args.at(4).toNumber(exec);

    imp->initWebKitTransitionEvent(typeArg, canBubbleArg, cancelableArg, propertyNameArg, elapsedTimeArg);
    return jsUndefined();
}


}
