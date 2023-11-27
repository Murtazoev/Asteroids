#include "Shooting.h"

Shooting::Shooting()
{
    //ctor
}

void Shooting::Draw()
{
    TextureManager::GetInstance()->DrawFrame(id , x , y , width , height , 0 , 0 , 0) ;
}

void Shooting::CreateShot(string ID, int X, int Y, int DestX, int DestY, int Width, int Height)
{
    id = ID ;
    x = X ;
    y = Y ;
    destX = DestX ;
    destY = DestY ;
    width = Width ;
    height = Height ;
}

void Shooting::Delete(string id)
{
    TextureManager::GetInstance()->DrawFrame("#" , 0 , 0 , 0 , 0 , 0 , 0 , 0) ;
}

void Shooting::Move()
{
    x += destX ;
    y += destY ;
}
