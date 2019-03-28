#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include "InitializationCodes.h"

class PPVM
{
    public:
        static PPVM* currentPPVM;

        PPVM(char* image_path, bool graphic_mode);
        ~PPVM();

        InitCodes::InitCodes initialize();

        void run();

    private:
        sf::Image code_pic;

        char* m_image_path;
        bool m_graphic_mode;

        unsigned int size_x, size_y;

        unsigned int program_pointer_x, program_pointer_y;
        char program_pointer_direction;

        std::string getStringArg();
};
