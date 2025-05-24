#include <iostream>
#include "wav_reader.h"
#include "mp3_decoder.h"
#include "audio_player.h"
#include "audio_plot.h"

int main() {
    // Đọc file .wav
    WavHeader wavHeader;
    std::vector<short> wavData = readWavFile("sound.wav", wavHeader);
    if (wavData.empty()) {
        std::cerr << "Cannot read file .wav!" << std::endl;
    } else {
        std::cout << "WAV File Info:" << std::endl;
        std::cout << "Sample Rate: " << wavHeader.sampleRate << std::endl;
        std::cout << "Channels: " << wavHeader.numChannels << std::endl;
        std::cout << "Bits per Sample: " << wavHeader.bitsPerSample << std::endl;
        playAudio(wavData, wavHeader.sampleRate, wavHeader.numChannels);
        plotAudioData(wavData, "wav_plot.png");
    }

    // Giải mã file .mp3
    std::vector<short> mp3Data = decodeMp3File("sound.mp3");
    if (mp3Data.empty()) {
        std::cerr << "Cannot read file .mp3!" << std::endl;
    } else {
        std::cout << "MP3 File Info:" << std::endl;
        std::cout << "Decoded audio data size: " << mp3Data.size() << std::endl;
        playAudio(mp3Data, 44100, 2); // Giả sử sample rate là 44100 và stereo
        plotAudioData(mp3Data, "mp3_plot.png");
    }

    return 0;
}