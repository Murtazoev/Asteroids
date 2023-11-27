#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include <Character.h>

class Asteroids: public Character
{
    public:
        Asteroids(Properties* props) ;

        virtual void Draw() ;
        virtual void Clean() ;
        virtual void Drop(string id) ;
        virtual void Update(float dt) ;
        int CurX , CurY , DestX , DestY , Angle ;

    private:
        int m_Row , m_Frame , m_FrameCount , m_AnimSpeed ;
};

#endif // ASTEROIDS_H
