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
        cout << "I am here : main " << endl ;
        Engine::GetInstance()->Render() ;
//        cout << "It is working" << endl ;
    }
    Engine::GetInstance()->Clean() ;
}
