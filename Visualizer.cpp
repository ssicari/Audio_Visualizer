// Copyright 2024 Sal Sicari

#include "AudioDecoder.hpp"
#include "Visualizer.hpp"

Visualizer::Visualizer(const std::vector<double>& frequencies, double scaleFactor, std::string file_path)
    : frequencies(frequencies), scaleFactor(scaleFactor), file_path(file_path), currentIndex(0) // Declare currentIndex here
{
    size_t slash = file_path.find_last_of('/');
    std::string song = file_path.substr(slash + 1);

    // SFML setup
    window.create(sf::VideoMode::getFullscreenModes()[0], "Now Playing: " + song, sf::Style::Titlebar);
    graph.setPrimitiveType(sf::Points); // Changed to Points for dynamic shapes

    // If you want to set a specific background color, you can uncomment the following line
    // window.clear(sf::Color::Black);

    if (!background_music.openFromFile(file_path))
    {
        std::cerr << "Error loading music" << std::endl;
    }

    background_music.play();
}

void Visualizer::visualization()
{
    sf::Clock clock;
    const sf::Time frameTime = sf::milliseconds(90); // Adjust the frame time based on your preference (60 FPS in this example)

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
        double currentFrequency = (frequencies[currentIndex] * scaleFactor);

        // Draw a growing transparent center green circle
        sf::CircleShape circle(2.0f * currentFrequency);
        circle.setPosition(window.getSize().x / 2.0f - 2.0f * currentFrequency, window.getSize().y / 2.0f - 2.0f * currentFrequency);
        circle.setFillColor(sf::Color(0, 255, 0, 0)); // Green with 50% transparency
        circle.setOutlineColor(sf::Color::Green); // Green outline color
        circle.setOutlineThickness(2.0f); // Adjust the outline thickness

	/*float circleRadius = circle.getRadius();
        sf::Vector2f circlePosition(
            std::max(circleRadius, std::min(view.getSize().x - circleRadius, view.getCenter().x - 5.0f * static_cast<float>(currentFrequency))),
            std::max(circleRadius, std::min(view.getSize().y - circleRadius, view.getCenter().y - 5.0f * static_cast<float>(currentFrequency)))
        );

        circle.setPosition(circlePosition);*/

        window.draw(circle);

        // Move to the next frequency
        currentIndex++;

        // Reset index if we reached the end
        if (currentIndex >= frequencies.size())
        {
            currentIndex = 0;
        }

        window.display();

        // Introduce a delay to control FPS
        sf::Time elapsed = clock.restart();
        if (elapsed < frameTime)
        {
            sf::sleep(frameTime - elapsed);
        }
    }
}


Visualizer::~Visualizer()
{
    window.close();
    background_music.stop();
}
