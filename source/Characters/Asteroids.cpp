#include "Asteroids.h"
#include<TextureManager.h>
#include<SDL2/SDL.h>
#include<iostream>

Asteroids::Asteroids(Properties* props): Character(props)
{
    m_Row = 0 ;
    m_FrameCount = 1 ;
    m_AnimSpeed = 200 ;
}

void Asteroids::Draw()
{
    TextureManager::GetInstance()->DrawFrame(m_TextureID , m_Transform->X , m_Transform->Y , m_Width , m_Height , Angle , m_Row , m_Frame) ;
}

void Asteroids::Clean()
{
    TextureManager::GetInstance()->Clean() ;
}

void Asteroids::Update(float dt)
{
    m_Frame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount ;
}

void Asteroids::Drop(string id)
{
    TextureManager::GetInstance()->Drop(id) ;
}
