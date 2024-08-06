#include <jni.h>
#include <string>
#include <GLES3/gl3.h>
#include "RenderProgram.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_Cube_JNIWrapper_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

std::string jstringTostring(JNIEnv *env, jstring jStr) {
    if (!jStr)
        return "";

    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

    size_t length = (size_t) env->GetArrayLength(stringJbytes);
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
        RenderProgram::instance().compileShaderProgram(jstringTostring(env, vertSource),
                                                       jstringTostring(env, fragSource));
    } catch (std::runtime_error &err) {
        return false;
    }

    return true;
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