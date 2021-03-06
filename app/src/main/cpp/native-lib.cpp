#include <jni.h>

/* @file native-lib.cpp
 * Function: bridge Java and C++ (AAudio API specifically).
 * */

#include "AudioEngine.h"
#include "DooDeeLOG.h"
#include "Transmission.h"


static AudioEngine *engine = nullptr;
static Transmission *tEngine = nullptr;

extern "C" {

JNIEXPORT void JNICALL
Java_com_doodee_voiceclicker_MicFeature_AudioEngine_startEngine(JNIEnv *env, jclass type,
                                                                jstring ipAddress_,
                                                                jint audioStreamPort) {

    const char *ipAddress = env->GetStringUTFChars(ipAddress_, 0);

    engine = new AudioEngine();
    tEngine = new Transmission(ipAddress, audioStreamPort);
    LOGD("OKEHHHH");

    env->ReleaseStringUTFChars(ipAddress_, ipAddress);

}

JNIEXPORT void JNICALL
Java_com_doodee_voiceclicker_MicFeature_AudioEngine_stopEngine(JNIEnv *env, jclass type) {
    engine->stopStream();
}
JNIEXPORT void JNICALL
Java_com_doodee_voiceclicker_MicFeature_Transmission_stopTransmission(JNIEnv *env, jclass type) {

    engine->toggleTransmission();
    tEngine->stop();

}
JNIEXPORT void JNICALL
Java_com_doodee_voiceclicker_MicFeature_Transmission_startTransmission(JNIEnv *env, jclass type,
                                                                       jstring ipAddress_,
                                                                       jint audioStreamPort) {
    const char *ipAddress = env->GetStringUTFChars(ipAddress_, 0);

    if (tEngine == nullptr) {
        tEngine = new Transmission(ipAddress, audioStreamPort);
    }
    engine->toggleTransmission();
    engine->setTransmissionEngine(tEngine);

    env->ReleaseStringUTFChars(ipAddress_, ipAddress);
}
}