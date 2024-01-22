//Copyright 2024 Sal Sicari
#ifndef VISUALIZER_H
#define VISUALIZER_H
#include "AudioDecoder.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <algorithm>
#include <thread>
#include <chrono>

class Visualizer {
public:
    Visualizer(const std::vector<double>& frequencies, double scale_factor = 0.1, std::string file_path = "");
    ~Visualizer();
    void visualization();

private:
    std::vector<double> frequencies;
    double scale_factor;
    std::string file_path;
    sf::RenderWindow window;
    sf::VertexArray graph;
    sf::Music background_music;
    //sf::View view;
    size_t current_index = 0;
    int current_iteration = 0;
};



#endif
