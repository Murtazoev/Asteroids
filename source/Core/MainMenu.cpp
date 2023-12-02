#include "MainMenu.h"

using namespace std ;

MainMenu* MainMenu::s_Instance = nullptr ;

MainMenu::MainMenu()
{
    //ctor
}

void MainMenu::Draw()
{
    TextureManager::GetInstance()->Draw("button1" , 300 , 300 , 940 , 210) ;
    TextureManager::GetInstance()->Draw("button2" , 300 , 500 , 940 , 210) ;
    TextureManager::GetInstance()->Draw("button3" , 300 , 700 , 940 , 210) ;
}

int MainMenu::Check()
{
    SDL_Event event ;
    SDL_PollEvent(&event) ;
    int level = 0 ;
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            int mouseX = event.button.x ;
            int mouseY = event.button.y ;
            if (mouseX >= 300 and mouseX <= 700 and mouseY >= 300 and mouseY <= 400)
                level = 1 ;
            if (mouseX >= 300 and mouseX <= 700 and mouseY >= 500 and mouseY <= 600)
                level = 2 ;
            if (mouseX >= 300 and mouseX <= 700 and mouseY >= 700 and mouseY <= 800)
                level = 3 ;
        }
    }
    return level ;
}
