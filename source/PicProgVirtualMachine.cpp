#include "PicProgVirtualMachine.h"

#include "stdio.h"

PPVM* PPVM::currentPPVM;

PPVM::PPVM(char* image_path, bool graphic_mode) :
    m_image_path(image_path),
    m_graphic_mode(graphic_mode),
    m_program_pointer(0, 0, 0)
{
    currentPPVM = this;
}

PPVM::~PPVM() {}

InitCodes::InitCodes PPVM::initialize()
{
    //Try to open file
    if (code_pic.loadFromFile(m_image_path))
    {
        m_size_x = code_pic.getSize().x;
        m_size_y = code_pic.getSize().y;
        if (m_size_x > 255 || m_size_y > 255)
            return InitCodes::ImageTooLarge;
        m_program_pointer.init();
        return InitCodes::Success;
    }
    else return InitCodes::WrongImageFilePath;
}

void PPVM::run()
{
    bool finished = false;
    //Right : 00b
    //Down : 01b
    //Left : 10b
    //Up : 11b
    while (true)
    {
        //Get current pixel
        sf::Color col = code_pic.getPixel(m_program_pointer.getX(), m_program_pointer.getY());
        //Do op
        switch (col.r)
        {
        case 0: break; //Break
        case 1: //Terminate program
            finished = true;
            break;
        case 4:
            {
                ProgramPointer keep = m_program_pointer;

                m_program_pointer = ProgramPointer(m_program_pointer, col.g, col.b);

                std::cout << getStringArg();

                m_program_pointer = keep;
            }
            break;
        default:
            printf("Unknown instruction : %i (at %u, %u)\n", col.r, m_program_pointer.getX(), m_program_pointer.getY());
        }
        if (finished)
            break;
        //Move program pointer
        m_program_pointer.step();
    }
}

std::string PPVM::getStringArg()
{
    std::string ret;

    while (true)
    {
        sf::Color arg_col = code_pic.getPixel(m_program_pointer.getX(), m_program_pointer.getY());

        if (arg_col.r)
            ret += (char)arg_col.r;
        else break;
        if (arg_col.g)
            ret += (char)arg_col.g;
        else break;
        if (arg_col.b)
            ret += (char)arg_col.b;
        else break;

        m_program_pointer.step();
    }

    return ret;
}
