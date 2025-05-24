#ifndef WAV_READER_H
#define WAV_READER_H

#include <vector>
#include <string>
#include <cstdint> // Thêm dòng này vào sau #include <vector>

struct WavHeader {
    char chunkID[4];      // "RIFF"
    uint32_t chunkSize;   // Kích thước file
    char format[4];       // "WAVE"
    char subchunk1ID[4];  // "fmt "
    uint32_t subchunk1Size; // Kích thước fmt chunk
    uint16_t audioFormat;  // Định dạng âm thanh (1 = PCM)
    uint16_t numChannels;  // Số kênh
    uint32_t sampleRate;   // Sample rate
    uint32_t byteRate;     // Byte rate
    uint16_t blockAlign;   // Block align
    uint16_t bitsPerSample; // Bits per sample
    char subchunk2ID[4];   // "data"
    uint32_t subchunk2Size; // Kích thước data chunk
};

std::vector<short> readWavFile(const std::string& filename, WavHeader& header);

#endif // WAV_READER_H