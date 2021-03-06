package sen.com.openglcamera.renderer;

import android.graphics.SurfaceTexture;
import android.opengl.GLSurfaceView;
import android.util.Log;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import sen.com.openglcamera.camera.CameraNewVersion;
import sen.com.openglcamera.natives.BaseGLNative;
import sen.com.openglcamera.view.CameraSGLSurfaceViewV2;

/**
 * Author : 唐家森
 * Version: 1.0
 * On     : 2017/10/11 13:06
 * Des    :
 */

public class CameraRendererV2 implements GLSurfaceView.Renderer, SurfaceTexture.OnFrameAvailableListener {
    GLSurfaceView mGLSurfaceView;
    private CameraNewVersion mCamera;
    private SurfaceTexture mSurfaceTexture;

    public CameraRendererV2(CameraSGLSurfaceViewV2 cameraSGLSurfaceView) {
        mGLSurfaceView = cameraSGLSurfaceView;

    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        mSurfaceTexture = BaseGLNative.getSurfaceTexture();
        if(mSurfaceTexture!=null){
            Log.e("sen_","mSurfaceTexture is not null");
            mSurfaceTexture.setOnFrameAvailableListener(this);
        }
        mCamera.setSurfaceTexture(mSurfaceTexture);
        mCamera.onResume();
        BaseGLNative.onSurfaceCreated();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        BaseGLNative.onSurfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        if (mSurfaceTexture != null &&!BaseGLNative.isStop) {
            mSurfaceTexture.updateTexImage();

           // BaseGLNative.onDrawFrame(mCamera.getCurrentData());
        }

    }

    public void init(CameraSGLSurfaceViewV2 cameraSGLSurfaceView, CameraNewVersion camera) {
        mGLSurfaceView = cameraSGLSurfaceView;
        mCamera = camera;
    }

    @Override
    public void onFrameAvailable(SurfaceTexture surfaceTexture) {
        if(!BaseGLNative.isStop) {
            mGLSurfaceView.requestRender();
        }

    }





}
