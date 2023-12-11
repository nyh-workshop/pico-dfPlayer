#ifndef DFPLAYER_H
#define DFPLAYER_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

constexpr uint8_t SERIAL_CMD_SIZE = 10;

namespace dfPlayer {
    enum cmd {
        NEXT = 0x01,
        PREV = 0x02,
        SPECIFY_TRACKING = 0x03,
        INC_VOL = 0x04,
        DEC_VOL = 0x05,
        SPECIFY_VOL = 0x06,
        SPECIFY_EQ = 0x07,
        SPECIFY_PLAYBACK_MODE = 0x08,
        SPECIFY_PLAYBACK_SRC = 0x09,
        ENTER_STANDBY = 0x0a,
        NORMAL_WORKING = 0x0b,
        RESET_MODULE = 0x0c,
        PLAYBACK = 0x0d,
        PAUSE = 0x0e,
        SPECIFY_FOLDER_PLAYBACK = 0x0f,
        VOL_ADJ_SET = 0x10,
        REPEAT_PLAY = 0x11
    };

    enum serialCommFormat {
        CMD = 0x03,
        PARA1 = 0x05,
        PARA2 = 0x06,
        CHKSUM_HIGH = 0x07,
        CHKSUM_LOW = 0x08
    };

    enum playback_modes {
        REPEAT = 0,
        REPEAT_FOLDER = 1,
        REPEAT_SINGLE = 2,
        RANDOM = 3
    };
}

template<typename T>
class DfPlayer {
public:
    void next();

    void previous();

    void reset();

    void specify_volume(uint8_t a_vol);

    void set_repeat_play(bool a_repeat);

    void increase_volume();

    void decrease_volume();

    void play_pause();

    void pause();

    void play();

    void set_playback_mode(dfPlayer::playback_modes playback_mode);

    void playback();


    bool paused = false;

    uint16_t calcChecksum(const uint8_t *a_serialCmdBuffer);

    void sendCmd(uint8_t a_cmd, uint16_t a_params);

    inline void uartSend(uint8_t *a_serialCmd);

private:
    const uint8_t serialBufferWithHeadersNoAck[SERIAL_CMD_SIZE] = {0x7e, 0xff, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                                   0xef};
    uint8_t tempSerialBuffer[SERIAL_CMD_SIZE]{};
};

template<typename T>
void DfPlayer<T>::next() {
    sendCmd(dfPlayer::cmd::NEXT, 0x0000);
}

template<typename T>
void DfPlayer<T>::previous() {
    sendCmd(dfPlayer::cmd::PREV, 0x0000);
}

template<typename T>
void DfPlayer<T>::reset() {
    sendCmd(dfPlayer::cmd::RESET_MODULE, 0x0000);
}

template<typename T>
void DfPlayer<T>::specify_volume(uint8_t a_vol) {
    // Clip volume to maximum of 31 only!
    uint16_t tempParam = a_vol & 0x001f;
    sendCmd(dfPlayer::cmd::SPECIFY_VOL, tempParam);
}

template<typename T>
void DfPlayer<T>::set_repeat_play(bool a_repeat) {
    uint16_t tempParam = a_repeat;
    sendCmd(dfPlayer::cmd::REPEAT_PLAY, tempParam);
}

template<typename T>
void DfPlayer<T>::increase_volume() {
    sendCmd(dfPlayer::cmd::INC_VOL, 0x0000);
}

template<typename T>
void DfPlayer<T>::decrease_volume() {
    sendCmd(dfPlayer::cmd::DEC_VOL, 0x0000);
}

template<typename T>
void DfPlayer<T>::play_pause() {
    if (paused) {
        sendCmd(dfPlayer::cmd::PLAYBACK, 0x0000);
        paused = false;
    } else {
        sendCmd(dfPlayer::cmd::PAUSE, 0x0000);
        paused = true;
    }
}

template<typename T>
void DfPlayer<T>::pause() {
    if (paused) {
        return;
    } else {
        sendCmd(dfPlayer::cmd::PAUSE, 0x0000);
        paused = true;
    }
}

template<typename T>
void DfPlayer<T>::play() {
    if (paused) {
        sendCmd(dfPlayer::cmd::PLAYBACK, 0x0000);
        paused = false;
    }
}

template<typename T>
void DfPlayer<T>::set_playback_mode(dfPlayer::playback_modes playback_mode) {
    uint16_t tempParam = playback_mode;
    sendCmd(dfPlayer::cmd::SPECIFY_PLAYBACK_MODE, tempParam);
}

template<typename T>
void DfPlayer<T>::playback() {
    sendCmd(dfPlayer::cmd::PLAYBACK, 0x0000);
}


template<typename T>
uint16_t DfPlayer<T>::calcChecksum(const uint8_t *a_serialCmdBuffer) {
    // Checksum is calculated from byte 1 to byte 6:
    uint16_t result = 0;
    for (uint8_t i = 1; i < 7; i++) {
        result += a_serialCmdBuffer[i];
    }
    result = -result;
    return result;
}

template<typename T>
void DfPlayer<T>::sendCmd(uint8_t a_cmd, uint16_t a_params) {
    memcpy(tempSerialBuffer, serialBufferWithHeadersNoAck, SERIAL_CMD_SIZE);

    tempSerialBuffer[dfPlayer::serialCommFormat::CMD] = a_cmd;
    tempSerialBuffer[dfPlayer::serialCommFormat::PARA1] = (a_params & 0xff00) >> 8;
    tempSerialBuffer[dfPlayer::serialCommFormat::PARA2] = (a_params & 0x00ff);

    int16_t checksum = calcChecksum(tempSerialBuffer);

    tempSerialBuffer[dfPlayer::serialCommFormat::CHKSUM_HIGH] = (checksum & 0xff00) >> 8;
    tempSerialBuffer[dfPlayer::serialCommFormat::CHKSUM_LOW] = (checksum & 0x00ff);

    uartSend(tempSerialBuffer);
}

template<typename T>
inline void DfPlayer<T>::uartSend(uint8_t *a_serialCmd) {
    static_cast<T *>(this)->uartSend(a_serialCmd);
}

#endif