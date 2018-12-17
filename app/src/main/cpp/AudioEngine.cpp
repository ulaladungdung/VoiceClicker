//
// Created by dodys on 12/16/2018.
//

#include <string>
#include "DooDeeLOG.h"
#include "AudioEngine.h"


AAudioStreamBuilder* AudioEngine::createStreamBuilder() {

    AAudioStreamBuilder *builder = nullptr;
    aaudio_result_t result = AAudio_createStreamBuilder(&builder);
    if (result != AAUDIO_OK) {
        LOGE("Error creating stream builder: %s", AAudio_convertResultToText(result));
    }
    return builder;
}


AudioEngine::AudioEngine() {
    createRecordingStream();
    return;
}

AudioEngine::~AudioEngine() {
    closeRecordingStream();
}

void AudioEngine::createRecordingStream(){

    AAudioStreamBuilder* builder = nullptr;
    AAudioStream *stream = nullptr;

    builder = createStreamBuilder();

    if(builder == nullptr){
        LOGE("Failed setting up stream");
        return;
    }

    setupRecordingStreamParameter(builder);
    aaudio_result_t result = AAudioStreamBuilder_openStream(builder,&stream);
    logRecordingStreamParameter(stream);
    LOGD("Recording Stream has been successfully created");
    LOGD(AAudio_convertResultToText(result));
}

void AudioEngine::setupRecordingStreamParameter(AAudioStreamBuilder *builder) {
    AAudioStreamBuilder_setDeviceId(builder, playbackDeviceId_);
    AAudioStreamBuilder_setDirection(builder, AAUDIO_DIRECTION_INPUT);
    AAudioStreamBuilder_setSharingMode(builder, AAUDIO_SHARING_MODE_EXCLUSIVE);
    // We request EXCLUSIVE mode since this will give us the lowest possible latency.
    // If EXCLUSIVE mode isn't available the builder will fall back to SHARED mode.
    AAudioStreamBuilder_setPerformanceMode(builder, AAUDIO_PERFORMANCE_MODE_LOW_LATENCY);
    AAudioStreamBuilder_setDirection(builder, AAUDIO_DIRECTION_OUTPUT);

//    AAudioStreamBuilder_setFormat(builder, sampleFormat_);
//    AAudioStreamBuilder_setChannelCount(builder, sampleChannels_);

//    AAudioStreamBuilder_setDataCallback(builder, ::dataCallback, this);
//    AAudioStreamBuilder_setErrorCallback(builder, ::errorCallback, this);

}

void AudioEngine::logRecordingStreamParameter(AAudioStream *stream) {
    int32_t result;
    result = AAudioStream_getDeviceId(stream);
    LOGD(std::to_string(result).c_str());
    result = AAudioStream_getDirection(stream);
    LOGD(std::to_string(result).c_str());
    result = AAudioStream_getSharingMode(stream);
    LOGD(std::to_string(result).c_str());
    result = AAudioStream_getSampleRate(stream);
    LOGD(std::to_string(result).c_str());
    result = AAudioStream_getChannelCount(stream);
    LOGD(std::to_string(result).c_str());
    result = AAudioStream_getFormat(stream);
    LOGD(std::to_string(result).c_str());
    result = AAudioStream_getBufferCapacityInFrames(stream);
    LOGD(std::to_string(result).c_str());
}

void AudioEngine::closeRecordingStream() {
    LOGD("close Stream");
    return;
}
