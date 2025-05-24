#include "mp3_decoder.h"
#include <mpg123.h>
#include <iostream>

std::vector<short> decodeMp3File(const std::string& filename) {
    mpg123_handle* mh = mpg123_new(nullptr, nullptr);
    if (!mh) {
        std::cerr << "Failed to create mpg123 handle!" << std::endl;
        return {};
    }
    if (mpg123_open(mh, filename.c_str()) != MPG123_OK) {
        std::cerr << "Failed to open MP3 file!" << std::endl;
        mpg123_delete(mh);
        return {};
    }

    long rate;
    int channels, encoding;
    mpg123_getformat(mh, &rate, &channels, &encoding);

    if (encoding != MPG123_ENC_SIGNED_16) {
        mpg123_format_none(mh);
        mpg123_format(mh, rate, channels, MPG123_ENC_SIGNED_16);
    }

    std::vector<short> audioData;
    size_t bufferSize = mpg123_outblock(mh);
    std::vector<unsigned char> buffer(bufferSize);

    size_t done;
    int err;
    do {
        err = mpg123_read(mh, buffer.data(), bufferSize, &done);
        audioData.insert(audioData.end(), (short*)buffer.data(), (short*)(buffer.data() + done));
    } while (err == MPG123_OK);

    mpg123_close(mh);
    mpg123_delete(mh);

    return audioData;
}