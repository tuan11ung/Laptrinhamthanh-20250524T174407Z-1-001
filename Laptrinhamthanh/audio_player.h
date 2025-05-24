#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include <vector>

void playAudio(const std::vector<short>& audioData, int sampleRate, int numChannels);

#endif // AUDIO_PLAYER_H