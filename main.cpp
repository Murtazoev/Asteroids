#include <Engine.h>

using namespace std ;

int WinMain ( int argc , char* argv[])
{
    Engine::GetInstance()->Init() ;

    while (Engine::GetInstance()->IsRunnin())
    {
        Engine::GetInstance()->Events() ;
        Engine::GetInstance()->Update() ;
        Engine::GetInstance()->Render() ;
//        cout << "It is working" << endl ;
    }
    Engine::GetInstance()->Clean() ;
}
