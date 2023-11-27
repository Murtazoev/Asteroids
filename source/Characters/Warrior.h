#ifndef WARRIOR_H
#define WARRIOR_H

#include<Character.h>
#include<iostream>

class Warrior: public Character
{
    public:
        Warrior(Properties* props) ;

        virtual void Draw() ;
        virtual void Clean() ;
        virtual void Drop(string id) ;
        virtual void Update(float dt) ;
        int Angle ;

    private:
        int m_Row , m_Frame , m_FrameCount , m_AnimSpeed ;
};

#endif // WARRIOR_H
