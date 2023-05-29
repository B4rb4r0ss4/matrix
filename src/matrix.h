#pragma once

#include <string>
#include <vector>
#include <ctime>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Matrix {
    private:
        // Window
        sf::RenderWindow* window;
        sf::VideoMode vidMode;
        sf::Event eve; 
        
        // Font
        sf::Font font;
        unsigned int fontSize;
        
        // priv functions
        void initializer();
        
        // priv structs
        
        struct Text {
            sf::Text te;
            static constexpr unsigned int minStrLen  = 10u;
            static constexpr unsigned int maxStrLen  = 20u;
            static constexpr unsigned char beginner  = 'a';
            static constexpr unsigned char ender     = 'z';

            int randi(const int& a, const int& b);
            void setRandX();
            void setStr(const int& j);
        };

        // variables
        std::vector<Text> textes;
        float timerMax;
        float timer;
        float movTime;
        unsigned int newsGen;

    public: 
        // contructor & destructor
        Matrix();
        virtual ~Matrix();
        
        // accessor
        const bool running() const;

        // functions 
        void initEvents();
        void update();
        void genText(const int& j);
        void updateMov();
};
