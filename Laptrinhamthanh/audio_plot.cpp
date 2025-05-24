#include "audio_plot.h"
#include <fstream>
#include <iostream>

void plotAudioData(const std::vector<short>& audioData, const std::string& outputFile) {
    std::ofstream file("audio_data.txt");
    if (!file) {
        std::cerr << "Không thể tạo file audio_data.txt!" << std::endl;
        return;
    }
    for (size_t i = 0; i < audioData.size(); i++) {
        file << i << " " << audioData[i] << std::endl;
    }
    file.close();

    std::string command = "gnuplot -e \"set terminal png; set output '" + outputFile + "'; plot 'audio_data.txt' with lines\"";
    system(command.c_str());
}