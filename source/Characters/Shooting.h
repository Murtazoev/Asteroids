#ifndef SHOOTING_H
#define SHOOTING_H

#include<Character.h>
#include<TextureManager.h>

class Shooting
{
    public:
        Shooting();

        string id ;
        int x , y , destX , destY , width , height ;
        void Draw() ;
        void CreateShot(string ID , int X , int Y , int DestX , int DestY , int Width , int Height) ;
        void Delete(string id) ;
        void Move() ;

    protected:

    private:
};

#endif // SHOOTING_H
