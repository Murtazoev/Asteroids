#ifndef MAINMENU_H
#define MAINMENU_H

#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<TextureManager.h>

class MainMenu
{
    public:
        MainMenu() ;
        static MainMenu* GetInstance()
        {
            return s_Instance = (!(s_Instance == nullptr))? s_Instance : new MainMenu() ;
        }
        void Draw() ;
        int Check() ;

    protected:

    private:
        static MainMenu* s_Instance ;
};

#endif // MAINMENU_H
