// Copyright 2024 Sal Sicari

#include "AudioDecoder.hpp"
#include "Visualizer.hpp"

Visualizer::Visualizer(const std::vector<double>& frequencies, double scale_factor, std::string file_path)
    : frequencies(frequencies), scale_factor(scale_factor), file_path(file_path), current_index(0)
{
    size_t slash = file_path.find_last_of('/');
    std::string song = file_path.substr(slash + 1);

    // SFML setup
    window.create(sf::VideoMode::getFullscreenModes()[0], "Now Playing: " + song, sf::Style::Titlebar);
    graph.setPrimitiveType(sf::Points);

    if (!background_music.openFromFile(file_path))
    {
        std::cerr << "Error loading music" << std::endl;
    }

    background_music.play();
}

void Visualizer::visualization()
{
    sf::Clock clock;
    const sf::Time frame_time = sf::milliseconds(90);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();

        // Check the current frequency
        double current_frequency = (frequencies[current_index] * scale_factor);
	sf::CircleShape circle(2.0f * current_frequency, 3);
	//sf::CircleShape circle(2.0f * current_frequency, 4);
	//sf::CircleShape circle(2.0f * current_frequency, 8);

        circle.setPosition(window.getSize().x / 2.0f - 2.0f * current_frequency, window.getSize().y / 2.0f - 2.0f * current_frequency);
        circle.setFillColor(sf::Color(0, 255, 0, 0));
	//std::cout << "Freq: " << current_frequency << std::endl;

	if (current_frequency <= 50)
	  {
	    circle.setOutlineColor(sf::Color::Blue);
	  }
	else if (current_frequency > 50 && current_frequency <= 100)
	  {
	    circle.setOutlineColor(sf::Color::Cyan);
	  }
	else if (current_frequency > 100 && current_frequency <= 150)
	  {
	    circle.setOutlineColor(sf::Color::Green);
	  }
	else if (current_frequency > 150 && current_frequency <= 200)
	  {
	    circle.setOutlineColor(sf::Color::Yellow);
	  }
	else if (current_frequency > 200 && current_frequency <= 250)
	  {
	    circle.setOutlineColor(sf::Color::Red);
	  }
	else if (current_frequency > 250 && current_frequency <= 300)
	  {
	    circle.setOutlineColor(sf::Color::Magenta);
	  }
	else if (current_frequency > 300)
	  {
	    circle.setOutlineColor(sf::Color::White);
	  }

	circle.setOutlineThickness(2.0f); // Adjust the outline thickness
	window.draw(circle);


	for (int i = 1; i <= 5; ++i)
        {
            sf::CircleShape glowCircle(2.0f * current_frequency, 3);
            glowCircle.setPosition(window.getSize().x / 2.0f - 2.0f * current_frequency, window.getSize().y / 2.0f - 2.0f * current_frequency);
            glowCircle.setFillColor(sf::Color::Transparent);
            glowCircle.setOutlineColor(sf::Color(255, 255, 255, 0)); // Adjust opacity
            glowCircle.setOutlineThickness(5.0f);
            window.draw(glowCircle);
        }

        window.display();

        // Move to the next frequency
        current_index++;

        // Reset index if we reached the end
        if (current_index >= frequencies.size())
        {
            current_index = 0;
        }


	const float rotation_speed = 400.0f;
        const float square_size = 675.0f;
        const double frequency_threshold = 255.0; // Adjust the frequency threshold as needed

        if (current_frequency > frequency_threshold)
        {
            for (float angle = 0.0f; angle < 360.0f; angle += 45.0f)
            {
                sf::RectangleShape spinning_square(sf::Vector2f(square_size, square_size));
		spinning_square.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
                spinning_square.setFillColor(sf::Color(0, 255, 0, 0)); // Adjust color as needed
		spinning_square.setOutlineColor(sf::Color::White);
		spinning_square.setOutlineThickness(1.5f);
                spinning_square.setRotation(angle + rotation_speed * clock.getElapsedTime().asSeconds() * 180.0f / 3.141592f);
                window.draw(spinning_square);
            }
        }


	const double growing_circle_frequency_upper_threshold = 200.0;
	const double growing_circle_frequency_lower_threshold = 50.0;
	const float growing_circle_growth_rate = 40.0f;
	const int max_iterations = 50;  // Adjust the maximum number of iterations
	//int current_iteration = 0;

	if (current_frequency >= growing_circle_frequency_lower_threshold && current_frequency <= growing_circle_frequency_upper_threshold)
	{
	    // Check if the maximum number of iterations is reached
	    if (current_iteration < max_iterations)
	    {
	        // Calculate the incremental radius growth
	        float incremental_growth = current_iteration * growing_circle_growth_rate;

	        // Create a growing transparent circle
	        sf::CircleShape growing_circle(incremental_growth);
	        growing_circle.setOrigin(incremental_growth, incremental_growth);
	        growing_circle.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
	        growing_circle.setFillColor(sf::Color(0, 255, 0, 0));
	        growing_circle.setOutlineColor(sf::Color((current_index * 100), (current_index / 2), (current_index))); // Adjust color as needed
	        growing_circle.setOutlineThickness(7.f);
	        window.draw(growing_circle);

	        // Increment the iteration counter
	        current_iteration++;
	    }
	    else
	    {
	        // Reset the counter when the maximum iterations are reached
	        current_iteration = 0;
	    }
	}


        window.display();

        sf::Time elapsed = clock.restart();
        if (elapsed < frame_time)
        {
            sf::sleep(frame_time - elapsed);
        }
    }
}


Visualizer::~Visualizer()
{
    window.close();
    background_music.stop();
}
