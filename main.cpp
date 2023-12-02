#include <Engine.h>
#include<MainMenu.h>
#include<iostream>

using namespace std ;

int WinMain ( int argc , char* argv[])
{
    if (!Engine::GetInstance()->BuilWindow())
        return 0 ;
    Engine::GetInstance()->Init() ;
    while (Engine::GetInstance()->IsRunnin())
    {
        Engine::GetInstance()->Events() ;
        Engine::GetInstance()->Update() ;
        Engine::GetInstance()->Render() ;
    }
    Engine::GetInstance()->Clean() ;
}
