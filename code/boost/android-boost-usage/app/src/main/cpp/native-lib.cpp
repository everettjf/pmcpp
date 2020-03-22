#include <jni.h>
#include <string>
#include <boost/format.hpp>

extern "C" JNIEXPORT jstring JNICALL
Java_com_everettjf_androidboostusage_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {

    auto str = boost::format("writing %1%,  x=%2% : %3%-th try") % "toto" % 40.23 % 50;
    std::string hello = str.str();
    return env->NewStringUTF(hello.c_str());
}
