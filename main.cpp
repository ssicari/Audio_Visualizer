//Copyright 2024 Sal Sicari
#include "AudioDecoder.hpp"
#include "Visualizer.hpp"


int main(int argc, char* argv[])
{
    std::string song_dir = "/home/ssicari/Documents/Audio_Visualizer/Songs"; //this directory stores songs as mp3 to visualize
    std::string file_name;
    std::string file_path;
    std::string file_path_wav;
    int count = 0;
    const int spacer = 46;
    bool file_match = false;


    std::cout << "Here is a list of songs you can visualize!" << std::endl;
    std::cout << "If you would like to use your own song, save it as an mp3 and then put that in the Songs folder" << std::endl << std::endl;

    for(const auto& entry : std::filesystem::directory_iterator(song_dir))
	{
	    std::cout << std::left << std::setw(spacer) << entry.path().filename() << "\t";
	    count++;

	    if(count == 5)
	    {
	       std::cout << std::endl;
	       count = 0;
	    }
	}

    std::cout << std::endl;

    std::cout << "Please select a song from the list by typing <song_name.mp3> and then hitting enter NOTE: Case Sensitive" << std::endl;



    while(!file_match)
       {
	  std::cin >> file_name;
	  for(const auto& entry : std::filesystem::directory_iterator(song_dir))
	     {
		//std::cout << file_name << std::endl << entry.path().filename() << std::endl;
		if (file_name == entry.path().filename())
		   {
		      file_match = true;
		      break;
		   }

	     }
	  if (!file_match)
	   std::cerr << "That is not one of the listed songs. Please try again" << std::endl;
       }


    file_path = "/home/ssicari/Documents/Audio_Visualizer/Songs/" + file_name;
    file_path_wav = "/home/ssicari/Documents/Audio_Visualizer/Wav/" + file_name;

    size_t ext = file_path_wav.find_last_of('.');
    if (ext != std::string::npos)
      {
        file_path_wav = file_path_wav.substr(0, ext) + ".wav";
      }
    //std::cout << file_path_wav << std::endl;

    //std::cout << file_path << std::endl;


    //make object and pass file path to AudioDecoder Class

    AudioDecoder audio_data;
    audio_data.file_to_raw_audio(file_path);
    std::vector<double> frequencies = audio_data.raw_audio_to_freq();

    Visualizer visual(frequencies, 0.00001, file_path_wav);
    visual.visualization();


    return 0;
}
