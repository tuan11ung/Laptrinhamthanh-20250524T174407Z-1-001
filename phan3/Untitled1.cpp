#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class DigitalAudioSignal {
private:
    std::vector<double> samples; // Mẫu tín hiệu âm thanh
    int sampleRate; // Tần số lấy mẫu (Hz)
    double duration; // Độ dài tín hiệu (giây)

public:
    // Constructor
    DigitalAudioSignal(int rate, double length) : sampleRate(rate), duration(length) {
        samples.resize(static_cast<size_t>(sampleRate * duration), 0.0);
    }
    
    // Lấy số lượng mẫu
    size_t getSampleCount() const {
        return samples.size();
    }
    
    // Truy cập vào mẫu tín hiệu
    double getSample(size_t index) const {
        if (index < samples.size()) {
            return samples[index];
        }
        return 0.0;
    }
    
    // Chuẩn hóa tín hiệu (bình thường hóa về [-1, 1])
    void normalize() {
        double maxVal = 0.0;
        for (auto s : samples) maxVal = std::max(maxVal, std::abs(s));
        if (maxVal > 0) {
            for (auto &s : samples) s /= maxVal;
        }
    }
    
    // Áp dụng hiệu ứng tăng âm lượng
    void amplify(double factor) {
        for (auto &s : samples) {
            s *= factor;
        }
    }
    
    // Đảo ngược tín hiệu âm thanh
    void reverse() {
        std::reverse(samples.begin(), samples.end());
    }
    
    // Lọc tín hiệu đơn giản bằng trung bình cộng
    void smooth() {
        std::vector<double> smoothed(samples.size());
        if (samples.size() > 2) {
            smoothed[0] = samples[0];
            smoothed[samples.size() - 1] = samples[samples.size() - 1];
            for (size_t i = 1; i < samples.size() - 1; ++i) {
                smoothed[i] = (samples[i - 1] + samples[i] + samples[i + 1]) / 3.0;
            }
            samples = smoothed;
        }
    }
    
    // Phép cộng tín hiệu
    DigitalAudioSignal operator+(const DigitalAudioSignal &other) const {
        DigitalAudioSignal result(sampleRate, duration);
        size_t minSize = std::min(samples.size(), other.samples.size());
        for (size_t i = 0; i < minSize; ++i) {
            result.samples[i] = samples[i] + other.samples[i];
        }
        return result;
    }
    
    // Phép trừ tín hiệu
    DigitalAudioSignal operator-(const DigitalAudioSignal &other) const {
        DigitalAudioSignal result(sampleRate, duration);
        size_t minSize = std::min(samples.size(), other.samples.size());
        for (size_t i = 0; i < minSize; ++i) {
            result.samples[i] = samples[i] - other.samples[i];
        }
        return result;
    }
    
    // Phép nhân tín hiệu
    DigitalAudioSignal operator*(const DigitalAudioSignal &other) const {
        DigitalAudioSignal result(sampleRate, duration);
        size_t minSize = std::min(samples.size(), other.samples.size());
        for (size_t i = 0; i < minSize; ++i) {
            result.samples[i] = samples[i] * other.samples[i];
        }
        return result;
    }
    
    // Phép trễ tín hiệu
    DigitalAudioSignal delay(int delaySamples) const {
        DigitalAudioSignal result(sampleRate, duration + static_cast<double>(delaySamples) / sampleRate);
        result.samples.resize(delaySamples + samples.size(), 0.0);
        for (size_t i = 0; i < samples.size(); ++i) {
            result.samples[i + delaySamples] = samples[i];
        }
        return result;
    }
    
    // Phép tích chập tín hiệu
    DigitalAudioSignal convolve(const DigitalAudioSignal &filter) const {
        double newDuration = duration + filter.duration;
        DigitalAudioSignal result(sampleRate, newDuration);
        result.samples.resize(samples.size() + filter.samples.size() - 1, 0.0);
        for (size_t i = 0; i < samples.size(); ++i) {
            for (size_t j = 0; j < filter.samples.size(); ++j) {
                result.samples[i + j] += samples[i] * filter.samples[j];
            }
        }
        return result;
    }
    
    // Hiển thị thông tin tín hiệu
    void printInfo() const {
        std::cout << "Sample Rate: " << sampleRate << " Hz\n";
        std::cout << "Total Samples: " << samples.size() << "\n";
        std::cout << "Duration: " << (samples.size() / (double)sampleRate) << " seconds\n";
    }
    
    // Thiết lập giá trị mẫu
    void setSample(size_t index, double value) {
        if (index < samples.size()) {
            samples[index] = value;
        }
    }
    
    // Thay đổi kích thước tín hiệu
    void resize(size_t newSize) {
        samples.resize(newSize, 0.0);
        duration = static_cast<double>(samples.size()) / sampleRate;
    }
};

int main() {
    double duration = 1.0; // Độ dài tín hiệu (giây)
    DigitalAudioSignal signal1(44100, duration);
    DigitalAudioSignal signal2(44100, duration);
    
    signal1.resize(5000); 

    // Tạo tín hiệu sóng sin và cos
    for (size_t i = 0; i < signal1.getSampleCount(); ++i) {
        signal1.setSample(i, sin(2 * M_PI * 440 * i / 44100)); // Sóng sin 440Hz
        signal2.setSample(i, cos(2 * M_PI * 440 * i / 44100)); // Sóng cos 440Hz
    }
    
    // Thông tin ban đầu
    signal1.printInfo();
    
    // Thực hiện các phép toán trên tín hiệu
    DigitalAudioSignal sumSignal = signal1 + signal2;
    DigitalAudioSignal diffSignal = signal1 - signal2;
    DigitalAudioSignal prodSignal = signal1 * signal2;
    DigitalAudioSignal delayedSignal = signal1.delay(4410); // Trễ 0.1 giây
    DigitalAudioSignal convolvedSignal = signal1.convolve(signal2);
    
    // Hiển thị thông tin sau xử lý
    sumSignal.printInfo();
    diffSignal.printInfo();
    prodSignal.printInfo();
    delayedSignal.printInfo();
    convolvedSignal.printInfo();
    
    return 0;
}