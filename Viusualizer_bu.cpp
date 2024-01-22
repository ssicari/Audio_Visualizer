// Copyright 2024 Sal Sicari

#include "AudioDecoder.hpp"
#include "Visualizer.hpp"

Visualizer::Visualizer(const std::vector<double>& frequencies, double scaleFactor, std::string file_path)
        : frequencies(frequencies), scaleFactor(scaleFactor), file_path(file_path)
    {
        size_t slash = file_path.find_last_of('/');
	std::string song = file_path.substr(slash + 1);

	//std::cout << "Frequencies Size: " << frequencies.size() << std::endl;


        // SFML setup
        window.create(sf::VideoMode::getFullscreenModes()[0], "Now Playing: " + song, sf::Style::Titlebar);
	//window.create(sf::VideoMode(800, 600), "Now Playing: " + song, sf::Style::Titlebar);
	graph.setPrimitiveType(sf::LineStrip);

        // Populate SFML VertexArray with points based on frequencies
        for (std::size_t i = 0; i < frequencies.size(); ++i)
        {
            //graph.append(sf::Vertex(sf::Vector2f(i, scaleFactor * frequencies[i])));
	    graph.append(sf::Vertex(sf::Vector2f(i, window.getSize().y - scaleFactor * frequencies[i])));
	    //std::cout << frequencies[i] << std::endl;
        }


	if (!background_music.openFromFile(file_path))
	  {
	    std::cerr << "Error loading music" << std::endl;
	  }

	background_music.play();

    }


void Visualizer::visualization()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
	      {
		//std::cout << "Window closed event received." << std::endl;
                window.close();
	      }
        }


	//std::cout << "Visualization loop iteration." << std::endl;
        window.clear();

        // Draw a simple line
        //sf::VertexArray line(sf::LinesStrip, frequencies.size());
        /*for (std::size_t i = 0; i < frequencies.size(); ++i)
        {
            line[i].position = sf::Vector2f(i, window.getSize().y - scaleFactor * frequencies[i]);
            line[i].color = sf::Color::White;
        }*/

	graph.clear();
	//std::cout << "SIZE: " << frequencies.size() << std::endl;
	for (std::size_t i = 0; i < frequencies.size(); ++i)
	   {
    	     graph.append(sf::Vertex(sf::Vector2f(i, window.getSize().y - scaleFactor * frequencies[i]), sf::Color::White));
	     //std::cout << "Frequency: " << (scaleFactor * frequencies[i]) << std::endl;
	   }

	//std::cout << "OUTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT" << std::endl;

	window.draw(graph);
	window.display();
    }
}


Visualizer::~Visualizer()
{
   window.close();
   background_music.stop();
}
