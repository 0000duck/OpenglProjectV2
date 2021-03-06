////
//// Created by Administrator on 2017/10/20.
////
//
//#include <sggl.h>
//#include "camera.h"
//
//
//Camera::Camera (){
//    isChangeVSFS = false;
//    fsPath = nullptr;
//    vsPath = nullptr;
//}
//
//Camera::~Camera(){
//    if (fsPath!= nullptr){
//        delete fsPath;
//    }
//
//    if(vsPath!= nullptr){
//        delete vsPath;
//    }
//    if(mShader!= nullptr){
//        delete mShader;
//    }
//
//   if(vertexBuffer){
//       free(vertexBuffer);
//   }
//    LOGE("稀放完毕");
//}
//
//jobject Camera::getSurfaceTextureObject() {
//    if (javaSurfaceTextureObj == NULL) {
//        return NULL;
//    }
//    return javaSurfaceTextureObj;
//}
//
//void Camera::init(float x,float y,float z) {
//    mModelMatrix = glm::translate(x,y,z);
//    vertexBuffer = new VertexBuffer;
//    vertexBuffer->setSize(4);
//    ////测试正方形 ---start
////    vertexBuffer->setColor(0,0.3f,0.3f,0.3f,1.0f);
////    vertexBuffer->setColor(1,0.3f,0.3f,0.3f,1.0f);
////    vertexBuffer->setColor(2,0.3f,0.3f,0.3f,1.0f);
////    vertexBuffer->setColor(3,0.3f,0.3f,0.3f,1.0f);
////
////    vertexBuffer->setTexcoord(0,0.0f,1.0f);
////    vertexBuffer->setTexcoord(1,1.0f, 1.0f);
////    vertexBuffer->setTexcoord(2,1.0f, 0.0f);
////    vertexBuffer->setTexcoord(3,0.0f, 0.0f);
////
////    vertexBuffer->setPosition(0,-1.0f, 1.0f, 0.0f, 1.0f);
////    vertexBuffer->setPosition(1,-1.0f, -1.0f, 0.0f, 1.0f);
////    vertexBuffer->setPosition(2,1.0f, -1.0f, 0.0f, 1.0f);
////    vertexBuffer->setPosition(3,1.0f, 1.0f, 0.0f,1.0f);
//////测试正方形 ---end
//
//    //////测试圆形-----start
//
//    vertexBuffer->setSize(400);
//    float rudis = 1.0f;
//    float sinValue;
//    float cosValue;
//    double angle ;
//    int i;
//    for ( i = 0; i <vertexBuffer->mVertexCount; i++) {
//        angle= 2 * M_PI * i / vertexBuffer->mVertexCount;
//        sinValue= sin(angle);
//        cosValue = cos(angle);
//        vertexBuffer->setPosition(i, rudis * cosValue, rudis *sinValue, 0);
//        vertexBuffer->setColor(i, 0.7f, 0.3f, 0.1f, 1.0f);
//        vertexBuffer->setTexcoord(i,(sinValue + 1.0f)*0.5f,(cosValue + 1.0f)*0.5f);
//    }
//
//    //////测试圆形-----end
//
///////测试数据,图像贴图倒了的数据，先保留
////    vertexBuffer->setPosition(0,-1.0f, 1.0f, 0.0f, 1.0f);
////    vertexBuffer->setPosition(1,-1.0f, -1.0f, 0.0f, 1.0f);
////    vertexBuffer->setPosition(2,1.0f, 1.0f, 0.0f, 1.0f);
////    vertexBuffer->setPosition(3,1.0f, -1.0f, 0.0f,1.0f);
////
////    vertexBuffer->setTexcoord(0,0.0f,0.0f);
////    vertexBuffer->setTexcoord(1,1.0f, 0.0f);
////    vertexBuffer->setTexcoord(2,0.0f, 1.0f);
////    vertexBuffer->setTexcoord(3,1.0f, 1.0f);
//
//
//    mShader = new SShader;
//    mShader->init("resource/camera/camera_normal.vs", "resource/camera/camera_normal.fs");
////    mShader->init("Res/camera_filter_rgba.vs", "Res/camera_filter_customer.fs");
//    //设置滤镜的分量，请查看camera_back&while.fs ,注意的是如果fs vs 没有这个属性不要设置，避免出现黑屏，或者是清屏颜色
//    mShader->setUiformVec4("U_MultipleFilter",1.0f,1.0f,1.0f,1.0f);
//}
//
//
//void Camera::createSurfaceTextureObject(JNIEnv *env) {
//    glGenTextures(1, &textureId);
//    glBindTexture(GL_TEXTURE_EXTERNAL_OES, textureId);
//    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    const char *stClassPath = "android/graphics/SurfaceTexture";
//    const jclass surfaceTextureClass = env->FindClass(stClassPath);
//    if (surfaceTextureClass == 0) {
//    }
//
////    // find the constructor that takes an int
//    const jmethodID constructor = env->GetMethodID(surfaceTextureClass, "<init>", "(I)V");
//    if (constructor == 0) {
//    }
//
//    jobject obj = env->NewObject(surfaceTextureClass, constructor, textureId);
//    if (obj == 0) {
//    }
//    javaSurfaceTextureObj = env->NewGlobalRef(obj);
//
//}
//void Camera::drawModel(glm::mat4 &mViewMatrix, glm::mat4 &mProjectionMatrix) {
//    //画之前看看有没有更改了滤镜文件
//    if (isChangeVSFS == true){
//        LOGE("chang fs vs");
//        mShader->init(vsPath,fsPath);
//        mShader->setUiformVec4("U_MultipleFilter",1.0f,1.0f,1.0f,1.0f);
//        delete vsPath;
//        delete fsPath;
//        isChangeVSFS = false;
//    }
//    glEnable(GL_DEPTH_TEST);
//    vertexBuffer->bind();
//    mShader->bind(glm::value_ptr(mModelMatrix), glm::value_ptr(mViewMatrix),
//                  glm::value_ptr(mProjectionMatrix));
//
//    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexBuffer->mVertexCount);
//    vertexBuffer->unBind();
//}
////修改 shader 变量参数
//void Camera::changeFilter(float cr,float cg, float cb , float ca){
//    mShader->setUiformVec4("U_MultipleFilter",cr,cg,cb,ca);
//
//}
//
////修改 vs shader ,和fs shader
//void Camera::changeVSFS(const char* vspath, const char*fspath){
//    //给camera vsPath ，fsPath 中赋值，到时用完后得 清内存
//    size_t vsSize = strlen(vspath);
//    vsPath = (char *) malloc(vsSize);
//    memset(vsPath, 0, vsSize + 1);
//    memcpy(vsPath, vspath, vsSize);
//
//    size_t fsSize = strlen(fspath);
//    fsPath = (char *) malloc(fsSize);
//    memset(fsPath, 0, fsSize + 1);
//    memcpy(fsPath, fspath, fsSize);
//    LOGE("changeVSFS:%s,%s",vsPath,fsPath);
//    isChangeVSFS = true;
//}
//
//
//
