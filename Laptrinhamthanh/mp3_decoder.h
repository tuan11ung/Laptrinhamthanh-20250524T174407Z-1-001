#ifndef MP3_DECODER_H
#define MP3_DECODER_H

#include <vector>
#include <string>

std::vector<short> decodeMp3File(const std::string& filename);

#endif // MP3_DECODER_H