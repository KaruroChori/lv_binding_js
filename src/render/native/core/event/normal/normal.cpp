#include "normal.hpp"

#include "engine.hpp"

WRAPPED_STOPPROPAGATION

static JSClassID WrapNormalEventID;

static void EventFinalizer(JSRuntime *rt, JSValue val) {
}

static JSClassDef NormalEventWrapClass = {
    .class_name = "normal",
    .finalizer = EventFinalizer,
};

JSValue WrapNormalEvent (lv_event_t* e, std::string uid) {
    TJSRuntime* qrt;
    JSContext* ctx;
    JSValue proto;
    JSValue obj;

    qrt = GetRuntime();
    ctx = qrt->ctx;
    proto = JS_GetClassProto(ctx, WrapNormalEventID);
    obj = JS_NewObjectProtoClass(ctx, proto, WrapNormalEventID);
    JS_FreeValue(ctx, proto);

    JS_SetOpaque(obj, e);

    return obj;
};

static const JSCFunctionListEntry component_proto_funcs[] = {
    TJS_CFUNC_DEF("stopPropagation", 0, NativeEventStopPropagation)
};

void NativeNormalEventWrapInit (JSContext* ctx) {
    JS_NewClassID(JS_GetRuntime(ctx), &WrapNormalEventID);
    JS_NewClass(JS_GetRuntime(ctx), WrapNormalEventID, &NormalEventWrapClass);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, component_proto_funcs, countof(component_proto_funcs));
    JS_SetClassProto(ctx, WrapNormalEventID, proto);
}
