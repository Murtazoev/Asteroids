#include "MainMenu.h"

using namespace std ;

MainMenu* MainMenu::s_Instance = nullptr ;

MainMenu::MainMenu()
{
    //ctor
}

void MainMenu::Draw()
{
    TextureManager::GetInstance()->Draw("Shadow" , 0 , 0 , 1000 , 1000) ;
    TextureManager::GetInstance()->Draw("button1" , 300 , 125 , 940 , 210) ;
    if (Engine::GetInstance()->Levels[1] == false)
        TextureManager::GetInstance()->Draw("Shadow2" , 300 , 125 , 940 , 210) ;
    TextureManager::GetInstance()->Draw("button2" , 300 , 375 , 940 , 210) ;
    if (Engine::GetInstance()->Levels[2] == false)
        TextureManager::GetInstance()->Draw("Shadow2" , 300 , 375 , 940 , 210) ;
    TextureManager::GetInstance()->Draw("button3" , 300 , 625 , 940 , 210) ;
    if (Engine::GetInstance()->Levels[3] == false)
        TextureManager::GetInstance()->Draw("Shadow2" , 300 , 625 , 940 , 210) ;
    TextureManager::GetInstance()->Draw("button4" , 300 , 875 , 940 , 210) ;
    if (Engine::GetInstance()->Levels[4] == false)
        TextureManager::GetInstance()->Draw("Shadow2" , 300 , 875 , 940 , 210) ;
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
            if (mouseX >= 300 and mouseX <= 700 and mouseY >= 125 and mouseY <= 225)
                level = 1 ;
            if (mouseX >= 300 and mouseX <= 700 and mouseY >= 375 and mouseY <= 475)
                level = 2 ;
            if (mouseX >= 300 and mouseX <= 700 and mouseY >= 625 and mouseY <= 725)
                level = 3 ;
            if (mouseX >= 300 and mouseX <= 700 and mouseY >= 875 and mouseY <= 975)
                level = 4 ;
        }
    }
    return level ;
}
