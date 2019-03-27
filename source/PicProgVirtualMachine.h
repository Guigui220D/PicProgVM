#pragma once

#include <SFML/Graphics.hpp>

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
};
