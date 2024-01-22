//Copyright 2024 Sal Sicari
#ifndef AUDIODECODER_H
#define AUDIODECODER_H
#include <iostream>
#include <mpg123.h>
#include <fftw3.h>
#include <cmath>
#include <algorithm>
#include <typeinfo>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <filesystem>
#include <algorithm>

class AudioDecoder {
public:
    AudioDecoder() {}; //default constructor
    AudioDecoder(const std::string& file_path);
    void file_to_raw_audio(const std::string& file_path);
    std::vector<double> raw_audio_to_freq();

private:
    std::vector<double> raw_audio;


};


#endif
