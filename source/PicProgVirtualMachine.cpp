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
        if (size_x > 255 || size_y > 255)
            return InitCodes::ImageTooLarge;
        program_pointer_x = 0;
        program_pointer_y = 0;
        program_pointer_direction = 0;
        return InitCodes::Success;
    }
    else return InitCodes::WrongImageFilePath;
}

void PPVM::run()
{
    bool finished = false;

    unsigned int& ppx = program_pointer_x;
    unsigned int& ppy = program_pointer_y;
    char& dir = program_pointer_direction;
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
        case 1: //Terminate program
            finished = true;
            break;
        case 4:
            {
                auto keep_x = ppx, keep_y = ppy;

                ppx += (char)(col.g);
                ppy += (char)(col.b);

                std::cout << getStringArg();

                ppx = keep_x;
                ppy = keep_y;
            }
            break;
        default:
            printf("Unknown instruction : %i (at %u, %u)\n", col.r, ppx, ppy);
        }
        if (finished)
            break;
        //Move program pointer
        switch (dir & 0b11)
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

std::string PPVM::getStringArg()
{
    std::string ret;

    while (true)
    {
        sf::Color arg_col = code_pic.getPixel(program_pointer_x, program_pointer_y);

        if (arg_col.r)
        {
            ret += (char)arg_col.r;
        }
        else break;
        if (arg_col.g)
        {
            ret += (char)arg_col.g;
        }
        else break;
        if (arg_col.b)
        {
            ret += (char)arg_col.b;
        }
        else break;

        switch (program_pointer_direction & 0b11)
        {
        case 0b00: //Right
            program_pointer_x++;
            if (program_pointer_x >= size_x)
                program_pointer_x = 0;
            break;
        case 0b01: //Down
            program_pointer_y++;
            if (program_pointer_y >= size_y)
                program_pointer_y = 0;
            break;
        case 0b10: //Left
            program_pointer_x--;
            if (program_pointer_x >= size_x)
                program_pointer_x = size_x - 1;
            break;
        case 0b11: //Up
            program_pointer_y--;
            if (program_pointer_y >= size_y)
                program_pointer_y = size_y - 1;
            break;
        }
    }

    return ret;
}
