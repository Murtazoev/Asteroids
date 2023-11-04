#include "Engine.h"
#include <iostream>
#include <TextureManager.h>
#include<SDL2/SDL.h>
#include "Vector 2D.h"
#include<Transform.h>

using namespace std ;

Engine* Engine::s_Instance = nullptr ;

bool Engine::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 and IMG_Init(IMG_INIT_JPG or IMG_INIT_PNG) != 0 )
    {
        cout << "Failed to Initialize SDL .... " << endl ;
        return false ;
    }
    window = SDL_CreateWindow("Asteroids" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 1000 , 1000 , 0) ;
    if (window == nullptr)
    {
        cout << "Can not create a window ...." << endl ;
        return false ;
    }
    renderer = SDL_CreateRenderer(window , -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) ;
    if (renderer == nullptr)
    {
        cout << "Can not render ... " << endl ;
        return false ;
    }
    TextureManager::GetInstance()->Load("background" , "Assets/background.jpg") ;

    cout << "I am here" << endl ;

    Transform tf;
    tf.Log() ;

    return true ;
}

bool Engine::Clean()
{
    TextureManager::GetInstance()->Clean() ;
    SDL_DestroyRenderer(renderer) ;
    SDL_DestroyWindow(window) ;
    IMG_Quit() ;
    SDL_Quit() ;
}

void Engine::Quit()
{
    m_IsRunnin = false ;
}

void Engine::Update()
{
    cout << "It Is Working ...." << endl ;
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(renderer , 125 , 55 , 254 , 255) ;
    SDL_RenderClear(renderer) ;
    TextureManager::GetInstance()->Draw("background" , 0 , 0 , 1000 , 1000) ;
    SDL_RenderPresent(renderer) ;
}

void Engine::Events()
{
    SDL_Event event ;
    SDL_PollEvent(&event) ;
    if (event.type == SDL_QUIT)
    {
        Quit() ;
    }
}
