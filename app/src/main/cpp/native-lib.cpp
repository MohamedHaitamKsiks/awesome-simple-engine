#define STB_IMAGE_IMPLEMENTATION

#include <jni.h>
#include <string>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

#include "engine/File.h"
#include "engine/Image.h"
#include "engine/vec2.h"
#include "engine/Texture.h"
#include "engine/Sprite.h"
#include "engine/Resource.h"
#include "engine/GameObject.h"
#include "engine/Material.h"
#include "engine/Renderer.h"

extern "C" JNIEXPORT void JNICALL
Java_com_example_myapplication_MyRenderer_init(
        JNIEnv* env,
        jclass clazz,
        jobject assetManagerJava,
        jobject surface) {

    AAssetManager* assetManager = AAssetManager_fromJava(env, assetManagerJava);
    ANativeWindow* window;
    window = ANativeWindow_fromSurface(env, surface);

    ASEngine::Renderer::init();
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_myapplication_MyRenderer_surfaceChange(
        JNIEnv* env,
        jclass clazz,
        jint width,
        jint height) {

    ASEngine::Renderer::surfaceChange(width, height);
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_myapplication_MyRenderer_update(
        JNIEnv* env,
        jclass clazz) {

    ASEngine::Renderer::draw();
}
