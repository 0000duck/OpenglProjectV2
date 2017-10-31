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
bool isRelese = false;

unsigned char *loadFile(const char *path, int &fileSize) {
    unsigned char *file = nullptr;
    if(path== nullptr){
        return nullptr;
    }
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
    LOGE("onSurfaceChanged %f*%f",width,height);
    setViewPortSize((float)width,(float) height);


};

JNIEXPORT void JNICALL Java_sen_com_openglcamera_natives_CameraSGLNative_onDrawFrame
        (JNIEnv *env, jclass clzss) {
    if(camera!= nullptr &&!isRelese){
        draw();
    }


};

JNIEXPORT jobject JNICALL Java_sen_com_openglcamera_natives_CameraSGLNative_getSurfaceTexture
        (JNIEnv *, jclass){
    return camera->getSurfaceTextureObject();
}

JNIEXPORT void JNICALL
Java_sen_com_openglcamera_natives_CameraSGLNative_onChangeFileter(JNIEnv *env, jclass type,
                                                                  jint r,jint g,jint b,jint a,jint max) {
    float rc = (float)r/(float)max;
    float gc = (float)g/(float)max;
    float bc = (float)b/(float)max;
    float ac = (float)a/(float)max;
    LOGE("rc:%f**gc:%f**bc:%f**ac:%f",rc,gc,bc,ac);
    camera->changeFilter(rc,gc,bc,ac);
}

JNIEXPORT void JNICALL
Java_sen_com_openglcamera_natives_CameraSGLNative_onChangeVSFS(JNIEnv *env, jclass type,
                                                             jstring vs_, jstring fs_) {
    if (isRelese){
        return;
    }
    const char *vs = env->GetStringUTFChars(vs_, 0);
    const char *fs = env->GetStringUTFChars(fs_, 0);
    if (vs!= nullptr && fs!= nullptr){
        camera->changeVSFS(vs,fs);
    }
    env->ReleaseStringUTFChars(vs_, vs);
    env->ReleaseStringUTFChars(fs_, fs);
}

//稀放
JNIEXPORT void JNICALL
Java_sen_com_openglcamera_natives_CameraSGLNative_releaseNative(JNIEnv *env, jclass type) {
    if(camera !=NULL &&!isRelese){
        //javaSurfaceTextureObj 在析构函数好像不能delete ，因为是env Ref
        env->DeleteGlobalRef(camera->javaSurfaceTextureObj);
        delete(camera);
        isRelese = true;
    }

}
//修改形状
JNIEXPORT void JNICALL
Java_sen_com_openglcamera_natives_CameraSGLNative_onChangeShape(JNIEnv *env, jclass type, jint cameraShape) {
   if(camera->currentShap !=cameraShape){
       camera->changeShape(cameraShape);
   }


}
//检验数据
float checkData(float data){
    if(data >1.0f){
        data =1.0f;
    } else if(data <0){
        data =0.0f;
    }
    return data;
}
//修改背景颜色
JNIEXPORT void JNICALL
Java_sen_com_openglcamera_natives_CameraSGLNative_onChangeBgColor(JNIEnv *env, jclass type,
                                                                  jfloat r, jfloat g, jfloat b,
                                                                  jfloat a) {
    //检验数据
    r = checkData(r);
    g = checkData(g);
    b = checkData(b);
    a = checkData(a);

    camera->mBgColor = glm::vec4(r,g,b,a);
}