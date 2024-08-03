#include <jni.h>
#include <string>
#include <GLES3/gl3.h>
#include "render/Cube.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_Cube_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}