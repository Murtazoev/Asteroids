#include "Warrior.h"
#include<TextureManager.h>
#include<SDL2/SDL.h>
#include<iostream>

Warrior::Warrior(Properties* props): Character(props)
{
    m_Row = 0 ;
    m_FrameCount = 1 ;
    m_AnimSpeed = 200 ;
}

void Warrior::Draw()
{
    TextureManager::GetInstance()->DrawFrame(m_TextureID , m_Transform->X , m_Transform->Y , m_Width , m_Height , Angle , m_Row , m_Frame) ;
}

void Warrior::Clean()
{
    TextureManager::GetInstance()->Clean() ;
}

void Warrior::Update(float dt)
{
    m_Frame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount ;
}

void Warrior::Drop(string id)
{
    cout << "I am here bitch" << endl ;
    TextureManager::GetInstance()->Drop(id) ;
}

