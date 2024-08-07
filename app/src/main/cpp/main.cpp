#include <jni.h>
#include <string>
#include <GLES3/gl3.h>
#include "RenderProgram.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_Cube_JNIWrapper_err(
        JNIEnv* env,
        jobject /* this */) {

    return env->NewStringUTF(RenderProgram::instance().getLastError().c_str());
}

std::string jstringTostring(JNIEnv *env, jstring jStr) {
    if (!jStr)
        return "";

    const auto stringClass = env->GetObjectClass(jStr);
    const auto getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const auto stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

    auto length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char *)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);

    return ret;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_com_Cube_JNIWrapper_compileShaders(
        JNIEnv* env,
        jobject /* this */,
        jstring vertSource,
        jstring fragSource) {

    try {
        return RenderProgram::instance().compileShaderProgram(jstringTostring(env, vertSource),
                                                       jstringTostring(env, fragSource));
    } catch (std::runtime_error &err) {
        return false;
    }
}

extern "C" JNIEXPORT jboolean JNICALL
Java_com_Cube_JNIWrapper_setUpGraphic(
        JNIEnv* env,
        jobject /* this */,
        jint width,
        jint height) {

    try {
        RenderProgram::instance().setupGraphic(width, height);
    } catch (std::runtime_error &err) {
        return false;
    }

    return true;
}

extern "C" JNIEXPORT void JNICALL
Java_com_Cube_JNIWrapper_renderFrame(JNIEnv* env, jobject /* this */) {

    RenderProgram::instance().renderFrame();
}

extern "C" JNIEXPORT void JNICALL
Java_com_Cube_JNIWrapper_round(JNIEnv* env, jobject /* this */,
                                  jfloat axX, jfloat axY, jfloat axZ) {

    RenderProgram::instance().rotateCube({axX, axY,axZ});
}

extern "C" JNIEXPORT void JNICALL
Java_com_Cube_JNIWrapper_orbit(JNIEnv* env, jobject /* this */, jboolean forward) {

    RenderProgram::instance().orbitCube(forward);
}