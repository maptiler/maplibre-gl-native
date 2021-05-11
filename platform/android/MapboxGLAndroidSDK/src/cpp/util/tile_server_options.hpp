#pragma once

#include <mbgl/util/noncopyable.hpp>
#include <mbgl/util/tile_server_options.hpp>

#include <jni/jni.hpp>

namespace mbgl {
namespace android {

class TileServerOptions : private mbgl::util::noncopyable {
public:

    static constexpr auto Name() { return "com/mapbox/mapboxsdk/util/TileServerOptions"; };

    static jni::Local<jni::Object<TileServerOptions>> New(jni::JNIEnv&, const mbgl::TileServerOptions&);

    static mbgl::TileServerOptions getTileServerOptions(jni::JNIEnv&, const jni::Object<TileServerOptions>&);

    static void registerNative(jni::JNIEnv&);
};


} // namespace android
} // namespace mbgl