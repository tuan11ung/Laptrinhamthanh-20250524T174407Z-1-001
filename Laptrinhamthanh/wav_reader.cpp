#include "wav_reader.h"
#include <fstream>
#include <iostream>

std::vector<short> readWavFile(const std::string& filename, WavHeader& header) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file!" << std::endl;
        return {};
    }

    // Đọc header
    file.read((char*)&header, sizeof(WavHeader));

    // Đọc dữ liệu âm thanh
    std::vector<short> audioData(header.subchunk2Size / sizeof(short));
    file.read((char*)audioData.data(), header.subchunk2Size);

    return audioData;
}