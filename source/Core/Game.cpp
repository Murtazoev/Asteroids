#include "Game.h"

using namespace std ;


Game* Game::s_Instance = nullptr ;

Game::Game()
{
    //ctor
}

void Game::Pause()
{
    // cout << "I got to GamePause" << endl ;
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8001 and !(pauseButton->IsCoolActive()))
    {
        Engine::GetInstance()->Menu = true ;
        Engine::GetInstance()->Render() ;
        pauseButton->StartCoolDown() ;
        while(1)
        {
            int WhichButton = 0 ;
            WhichButton = WasClicked() ;
            if (WhichButton == 1)
                break ;
            else if (WhichButton == 2)
            {
                Engine::GetInstance()->Clean() ;
                Engine::GetInstance()->Init() ;
                break ;
            }
            else if (WhichButton == 3)
                exit(0) ;
            cout << "Nothing Happened !" << endl ;
        }
        Engine::GetInstance()->Menu = false ;
        Engine::GetInstance()->Render() ;
    }
    /*
    while (1)
        {
            if ((GetAsyncKeyState('P') & 0x8000) and !(pauseButton->IsCoolActive()))
            {
                pauseButton->StartCoolDown() ;
                break ;
            }
        }
    */
}

void Game::Reset()
{
    cooldownEndTime = chrono::steady_clock::now() + chrono::seconds(2);
    while (1)
    {
        if (chrono::steady_clock::now() >= cooldownEndTime)
        {
            Engine::GetInstance()->MainMenu = true ;
            Engine::GetInstance()->Clean() ;
            Engine::GetInstance()->Init() ;
            break ;
        }
        Pause() ;
    }
}

void Game::Quit()
{
    if (GetAsyncKeyState('Q') & 0x8000)
        Engine::GetInstance()->Quit() ;
}

void Game::CheckEvents()
{
    Pause() ;
    Quit() ;
}

int Game::WasClicked()
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

void Game::StartCoolDown()
{
    Waiting = true;
    cooldownEndTime = chrono::steady_clock::now() + std::chrono::milliseconds(5000);
}

bool Game::IsCoolActive()
{
    return Waiting && chrono::steady_clock::now() < cooldownEndTime;
    if (chrono::steady_clock::now() < cooldownEndTime and Waiting == true)
        return true ;
    else
    {
        Waiting = false ;
        return false ;
    }
}
