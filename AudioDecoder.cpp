// Copyright 2024 Sal Sicari

#include "AudioDecoder.hpp"

AudioDecoder::AudioDecoder(const std::string& file_path)
{
    //No logic needed as this class takes a filepath performs operation and returns a vector of frequencies
}

void AudioDecoder::file_to_raw_audio(const std::string& file_path)
{
    //logic with mpg to turn file into raw audio vector
    //return raw_audio;
    mpg123_init();
    mpg123_handle *mpg_handler;
    mpg_handler = mpg123_new(NULL, NULL);

    const char* char_file_path = file_path.c_str();


    if (mpg123_open(mpg_handler, char_file_path) != MPG123_OK)
       {
	  std::cerr << "Error Opening MP3 File" << std::endl;
	  exit(-1);
       }

    long rate;
    int channels, encoding;
    mpg123_getformat(mpg_handler, &rate, &channels, &encoding);

    size_t bytes_read;
    short buf[8192];

    while(mpg123_read(mpg_handler, reinterpret_cast<unsigned char*>(buf), sizeof(buf), &bytes_read) == MPG123_OK && bytes_read > 0)
	{

	   for(size_t i = 0; i < sizeof(buf) / sizeof(buf[0]); i++)
	    {
	       raw_audio.push_back(buf[i]);
	    }
	}

    mpg123_close(mpg_handler);
    mpg123_delete(mpg_handler);
    mpg123_exit();

}

std::vector<double> AudioDecoder::raw_audio_to_freq()
{
    //logic to turn raw_audio vector to FFT
    //return FFT vector of magnitudes
    std::vector<double> frequencies;

    if (raw_audio.empty())
       {
         std::cerr << "Raw Audio Vector is empty" << std::endl;
         exit(-1);
       }

    int size = raw_audio.size();

    // Set up the FFTW
    fftw_complex* in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * size);
    fftw_complex* out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * size);
    fftw_plan plan = fftw_plan_dft_1d(size, in, out, FFTW_FORWARD, FFTW_ESTIMATE);


    for (int i = 0; i < size; i++)
       {
          in[i][0] = static_cast<double>(raw_audio[i]);
          in[i][1] = 0.0;
       }


    fftw_execute(plan);

    for (int i = 0; i < size; i++)
       {

	  double magnitude = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
          frequencies.push_back(magnitude);
	  //std::cout << magnitude << std::endl;
       }


    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);

    return frequencies;
}

