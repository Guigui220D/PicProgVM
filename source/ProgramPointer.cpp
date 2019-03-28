#include "ProgramPointer.h"

#include "PicProgVirtualMachine.h"

ProgramPointer::ProgramPointer(unsigned int x, unsigned int y, char direction) :
    m_x(x),
    m_y(y),
    m_direction(direction & 0b11)
{ }

ProgramPointer::ProgramPointer(ProgramPointer old, char relative_x, char relative_y) :
    size_x(PPVM::getCurrentPPVM()->getSizeX()),
    size_y(PPVM::getCurrentPPVM()->getSizeY()),
    m_x((old.getX() + relative_x) % size_x),
    m_y((old.getY() + relative_y) % size_y),
    m_direction(old.getDirection())
{ }

void ProgramPointer::init()
{
    size_x = PPVM::getCurrentPPVM()->getSizeX();
    size_y = PPVM::getCurrentPPVM()->getSizeY();

    m_x %= size_x;
    m_y %= size_y;
}

void ProgramPointer::step()
{
    switch (m_direction & 0b11)
    {
    case 0b00: //Right
        if (++m_x >= size_x)
            m_x = 0;
        break;
    case 0b01: //Down
        if (++m_y >= size_y)
            m_y = 0;
        break;
    case 0b10: //Left
        if (--m_x >= size_x)
            m_x = size_x - 1;
        break;
    case 0b11: //Up
        if (--m_y >= size_y)
            m_y = size_y - 1;
        break;
    }
}
