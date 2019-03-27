#include "PicProgVirtualMachine.h"

#include "stdio.h"

PPVM* PPVM::currentPPVM;

PPVM::PPVM(char* image_path, bool graphic_mode) :
    m_image_path(image_path),
    m_graphic_mode(graphic_mode)
{
    currentPPVM = this;
}

PPVM::~PPVM() {}

InitCodes::InitCodes PPVM::initialize()
{
    //Try to open file
    if (code_pic.loadFromFile(m_image_path))
    {
        size_x = code_pic.getSize().x;
        size_y = code_pic.getSize().y;
        if (size_x > 4096 || size_y > 4096)
            return InitCodes::ImageTooLarge;
        return InitCodes::Success;
    }
    else return InitCodes::WrongImageFilePath;
}

void PPVM::run()
{
    unsigned int program_pointer_x = 0, program_pointer_y = 0;
    unsigned int& ppx = program_pointer_x;
    unsigned int& ppy = program_pointer_y;
    char direction = 0;
    //Right : 00b
    //Down : 01b
    //Left : 10b
    //Up : 11b
    while (true)
    {
        //Get current pixel
        sf::Color col = code_pic.getPixel(ppx, ppy);
        //Do op
        switch (col.r)
        {
        case 0: break; //Break
        default:
            printf("Unknown instruction : %i (at %u, %u)\n", col.r, ppx, ppy);
        }
        //Move program pointer
        switch (direction & 0b11)
        {
        case 0b00: //Right
            ppx++;
            if (ppx >= size_x)
                ppx = 0;
            break;
        case 0b01: //Down
            ppy++;
            if (ppy >= size_y)
                ppy = 0;
            break;
        case 0b10: //Left
            ppx--;
            if (ppx >= size_x)
                ppx = size_x - 1;
            break;
        case 0b11: //Up
            ppy--;
            if (ppy >= size_y)
                ppy = size_y - 1;
            break;
        }
    }
}
