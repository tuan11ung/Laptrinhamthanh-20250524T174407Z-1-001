#include "audio_player.h" // Include file header
#include <portaudio.h>
#include <iostream> // Thêm thư viện iostream

using namespace std; // Sử dụng namespace std (khuyến nghị hạn chế)

struct AudioData {
    const std::vector<short>* data;
    size_t frameIndex;
};

// Callback function để phát âm thanh
static int audioCallback(const void* inputBuffer, void* outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void* userData) {
    float* out = (float*)outputBuffer;
    AudioData* audioData = (AudioData*)userData;

    for (unsigned long i = 0; i < framesPerBuffer; i++) {
        if (audioData->frameIndex < audioData->data->size()) {
            *out++ = (*audioData->data)[audioData->frameIndex++] / 32768.0f; // Chuyển đổi sang float
        } else {
            *out++ = 0; // Silence
        }
    }
    return (audioData->frameIndex >= audioData->data->size()) ? paComplete : paContinue;
}

// Hàm phát âm thanh
void playAudio(const std::vector<short>& audioDataVec, int sampleRate, int numChannels) {
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        cerr << "PortAudio error: " << Pa_GetErrorText(err) << endl; // Sử dụng cerr và endl
        return;
    }

    PaStream* stream;
    PaStreamParameters outputParameters;
    outputParameters.device = Pa_GetDefaultOutputDevice();
    outputParameters.channelCount = numChannels;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = nullptr;

    AudioData audioData = { &audioDataVec, 0 };

    err = Pa_OpenStream(&stream, nullptr, &outputParameters, sampleRate, 512, paClipOff, audioCallback, &audioData);
    if (err != paNoError) {
        cerr << "PortAudio error: " << Pa_GetErrorText(err) << endl; // Sử dụng cerr và endl
        Pa_Terminate();
        return;
    }

    err = Pa_StartStream(stream);
    if (err != paNoError) {
        cerr << "PortAudio error: " << Pa_GetErrorText(err) << endl; // Sử dụng cerr và endl
        Pa_CloseStream(stream);
        Pa_Terminate();
        return;
    }

    while (Pa_IsStreamActive(stream)) {
        Pa_Sleep(100);
    }

    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();

    cout << "Playback finished." << endl; // Sử dụng cout và endl
}