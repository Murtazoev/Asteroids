#ifndef GAME_H
#define GAME_H

#include<iostream>
#include<TextureManager.h>
#include<ButtonCoolDown.h>
#include<windows.h>
#include<Engine.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<conio.h>
#include<thread>
#include<iostream>

class Game
{
    public:
        static Game* GetInstance()
        {
            return s_Instance = (!(s_Instance == nullptr))? s_Instance : new Game() ;
        }
        Game();
        void Pause() ;
        void Reset() ;
        void CheckEvents() ;
        void Quit() ;
        int WasClicked() ;
        void StartCoolDown() ;
        bool IsCoolActive() ;
        bool Waiting ;
        chrono::steady_clock::time_point cooldownEndTime;


    protected:

    private:
        // Game(){} ;
        static Game* s_Instance;
        ButtonCoolDown* pauseButton = new ButtonCoolDown() ;
};

#endif // GAME_H
