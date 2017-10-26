//
// Created by Administrator on 2017/10/11.
// 方法名和java 层opengl 对应
//
#include "CameraSGLNative.h"
#include "sggl.h"
#include "scence.h"

//c++ 11 的nullptr
AAssetManager *aAssetManager = nullptr;
Camera *camera;


unsigned char *loadFile(const char *path, int &fileSize) {
    unsigned char *file = nullptr;
    fileSize = 0;
    //android 读取内部资源的方法
    AAsset *asset = AAssetManager_open(aAssetManager, path, AASSET_MODE_UNKNOWN);
    if (asset == nullptr)
        return nullptr;
    //读取成功
    fileSize = AAsset_getLength(asset);
    //开辟内存 +1 为了file[fileSize] = '\0';
    file = new unsigned char[fileSize + 1];
    AAsset_read(asset, file, fileSize);
    //为了程序的健壮性
    file[fileSize] = '\0';
    //关闭
    AAsset_close(asset);
    return file;
}


 void JNICALL Java_sen_com_openglcamera_natives_CameraSGLNative_initAssetManager
        (JNIEnv *env, jclass clzss, jobject assetManager) {
    aAssetManager = AAssetManager_fromJava(env, assetManager);
   camera = beforInit(env);

};

JNIEXPORT void JNICALL Java_sen_com_openglcamera_natives_CameraSGLNative_onSurfaceCreated
        (JNIEnv *env, jclass clzss) {
    init();

};


JNIEXPORT void JNICALL Java_sen_com_openglcamera_natives_CameraSGLNative_onSurfaceChanged
        (JNIEnv *env, jclass clzss, jint width, jint height) {
    setViewPortSize(width, height);


};

JNIEXPORT void JNICALL Java_sen_com_openglcamera_natives_CameraSGLNative_onDrawFrame
        (JNIEnv *env, jclass clzss) {
    draw();

};

JNIEXPORT jobject JNICALL Java_sen_com_openglcamera_natives_CameraSGLNative_getSurfaceTexture
        (JNIEnv *, jclass){
    return camera->getSurfaceTextureObject();
}

JNIEXPORT void JNICALL
Java_sen_com_openglcamera_natives_CameraSGLNative_onChangeFileter(JNIEnv *env, jclass type,
                                                                  jstring camera_vs,
                                                                  jstring camera_fs) {
    const char *cameraVs = env->GetStringUTFChars(camera_vs, 0);
    const char *cameraFs = env->GetStringUTFChars(camera_fs, 0);
    camera->changeFilter(0.8f,0.0f,0.2f,0.0f);
    env->ReleaseStringUTFChars(camera_vs, cameraVs);
    env->ReleaseStringUTFChars(camera_fs, cameraFs);
}