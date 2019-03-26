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

    private:
        char* m_image_path;
        bool m_graphic_mode;
};
