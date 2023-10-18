
#include <libusb.h>
#include <napi.h>

struct Device: public Napi::ObjectWrap<Device> {
    Device(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Device>(info) {
        // this should be the first reference, so refcount
        // should be 1, but with bun it is already 2
        uint32_t res = Ref();
        printf(" - refcount: %i (expected: 1)\n", res);
    }
};

Napi::Value testMethod(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    libusb_device** devs;
    libusb_context* usb_context = nullptr;
    libusb_init(&usb_context);
    libusb_get_device_list(usb_context, &devs);

    auto func = Device::DefineClass(
        env,
        "Device",
        {});
    
    Napi::Persistent(func).New({ Napi::External<libusb_device>::New(env, devs[0]) });

    libusb_free_device_list(devs, true);
    return env.Undefined();
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    exports.Set("test", Napi::Function::New(env, testMethod));
    return exports;
}
NODE_API_MODULE(usb_bindings, Init)
