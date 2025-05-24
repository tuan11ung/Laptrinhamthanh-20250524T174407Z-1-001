#include <iostream>

extern "C" {
    #include <portaudio.h>
}

int main() {
    // Khởi tạo PortAudio
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "Lỗi khởi tạo PortAudio: " << Pa_GetErrorText(err) << std::endl;
        return 1;
    }

    // In số thiết bị âm thanh
    int numDevices = Pa_GetDeviceCount();
    std::cout << "Số thiết bị âm thanh: " << numDevices << std::endl;

    // Dừng PortAudio
    err = Pa_Terminate();
    if (err != paNoError) {
        std::cerr << "Lỗi đóng PortAudio: " << Pa_GetErrorText(err) << std::endl;
        return 1;
    }

    return 0;
}