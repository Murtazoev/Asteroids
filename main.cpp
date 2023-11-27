#include <Engine.h>
#include<iostream>

using namespace std ;

int WinMain ( int argc , char* argv[])
{
    Engine::GetInstance()->Init() ;
    while (Engine::GetInstance()->IsRunnin())
    {
        Engine::GetInstance()->Events() ;
        Engine::GetInstance()->Update() ;
        Engine::GetInstance()->Render() ;
    }
    Engine::GetInstance()->Clean() ;
}
