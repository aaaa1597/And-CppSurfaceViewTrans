#ifndef TESTNATIVESURFACE_H
#define TESTNATIVESURFACE_H

#include <jni.h>
#include <android/native_window.h>
#include <pthread.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>

class CppSurfaceView {
private:
    const char *VERTEXSHADER =
        "attribute vec4 vPosition;\n"
        "uniform mat4 u_rotMatrix;\n"
        "void main() {\n"
        "    gl_Position = u_rotMatrix * vPosition;\n"
        "}\n";

    const char *FRAGMENTSHADER =
        "precision mediump float;\n"
        "void main() {\n"
        "    gl_FragColor = vec4(1.0, 0.0, 1.0, 0.2);\n"
        "}\n";

    /* 移動 */
    static const int AMOUNTOFMOVE = -5;
    float mMoveX = AMOUNTOFMOVE;
    float mMoveY = AMOUNTOFMOVE;
    float mxPos = 100;
    float myPos = 130;
    GLuint mu_rotMatrixHandle = -1;

private:
    GLuint createProgram(const char *vertexshader, const char *fragmentshader);
    GLuint loadShader(int i, const char *vertexshader);
    void checkGlError(const char *argstr);

public:
    static const int STATUS_NONE   = 0;
    static const int STATUS_INITIALIZING = 1;
    static const int STATUS_DRAWING= 2;
    static const int STATUS_FINISH = 3;
    int mId = -1;
    int mStatus = STATUS_NONE;
    pthread_t mThreadId = -1;
    ANativeWindow *mWindow = NULL;
    EGLDisplay mEGLDisplay = NULL;
    EGLContext mEGLContext = NULL;
    EGLSurface mEGLSurface = NULL;
    GLuint mProgram = -1;
    bool isSurfaceCreated = false;
    int DspW = 0;
    int DspH = 0;

public:
    CppSurfaceView(int id);
    virtual ~CppSurfaceView();
    static void *draw_thread(void *pArg);
    void createThread(JNIEnv *pEnv, jobject surface);
    void initEGL();
    void finEGL();
    void initGL();
    void predrawGL();
    void drawGL();
    void destroy();
};

#endif //TESTNATIVESURFACE_H
