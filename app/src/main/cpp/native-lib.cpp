#define STB_IMAGE_IMPLEMENTATION


#include <string>

#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <android/input.h>
#include <android/native_activity.h>



#include "engine/asengine.h"

extern "C" JNIEXPORT void JNICALL
Java_com_example_myapplication_MyRenderer_init(
        JNIEnv* env,
        jclass clazz,
        jobject assetManagerJava,
        jobject surface) {

    ANativeWindow* window;
    window = ANativeWindow_fromSurface(env, surface);

    //init texture
    ASEngine::Texture::init();

    //init ressource manager
    AAssetManager* assetManager = AAssetManager_fromJava(env, assetManagerJava);
    ASEngine::Resource::init(assetManager);

    //load sprite
    ASEngine::Image image = ASEngine::Image::load("sprites/spr_run.png");
    ASEngine::Texture texture = ASEngine::Texture::load(image);
    image.destroy();
    ASEngine::Sprite::load("spr_run", texture, 6, ASEngine::vec2{24.0f, 24.0f});
    ALOG("spr_run loaded");

    //load default material
    std::string vertexCode = ASEngine::Resource::loadAsText("materials/default.vert");
    std::string fragmentCode = ASEngine::Resource::loadAsText("materials/default.frag");
    ASEngine::Material::load("mt_default", vertexCode, fragmentCode);
    ALOG("loaded default material");

    //init renderer
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

