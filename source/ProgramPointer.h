#pragma once

class ProgramPointer
{
    public:
        ProgramPointer(unsigned int x, unsigned int y, char direction);
        ProgramPointer(ProgramPointer old, char relative_x, char relative_y);

        void init();
        void step();

        inline unsigned int getX() const { return m_x; }
        inline unsigned int getY() const { return m_y; }
        inline unsigned int getDirection() const { return m_direction; }
    private:
        unsigned int size_x, size_y;
        unsigned int m_x, m_y;
        char m_direction;
};
