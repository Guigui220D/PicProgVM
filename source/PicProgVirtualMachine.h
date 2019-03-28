#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include "InitializationCodes.h"
#include "ProgramPointer.h"

class PPVM
{
    public:
        inline static PPVM* const getCurrentPPVM() { return currentPPVM; }

        PPVM(char* image_path, bool graphic_mode);
        ~PPVM();

        InitCodes::InitCodes initialize();

        void run();

        inline unsigned int getSizeX() const { return m_size_x; }
        inline unsigned int getSizeY() const { return m_size_y; }

    private:
        static PPVM* currentPPVM;

        sf::Image code_pic;

        char* m_image_path;
        bool m_graphic_mode;

        unsigned int m_size_x, m_size_y;

        ProgramPointer m_program_pointer;

        std::string getStringArg();
};
