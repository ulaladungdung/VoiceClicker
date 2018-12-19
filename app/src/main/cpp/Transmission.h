//
// Created by dodys on 12/17/2018.
//

#ifndef VOICECLICKER_TRANSMISSION_H
#define VOICECLICKER_TRANSMISSION_H

#define ASIO_STANDALONE //prevent boost being used

#include <cstdint>
#include <string>
#include <aaudio/AAudio.h>
#include "asio.hpp"


using asio::ip::udp;

class Transmission {

public:

    Transmission();

    void stop();


    void send(int16_t *audioData, int32_t numFrames);

private:

    std::string ipAddrs_;
    int port_;

    int32_t bufferSize;
    int32_t numFrames_ = 960;

    AAudioStream *stream_;

    void *data_;

    void logData();

    void setupClient();

    udp::socket *socket_;

    udp::endpoint endpoint_;

};


#endif //VOICECLICKER_TRANSMISSION_H
