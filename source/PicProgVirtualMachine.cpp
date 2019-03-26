#include "PicProgVirtualMachine.h"

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
    sf::Image code_pic;
    if (code_pic.loadFromFile(m_image_path))
    {
        return InitCodes::Success;
    }
    else return InitCodes::WrongImageFilePath;
}
