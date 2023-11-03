#ifndef ENGINE_H
#define ENGINE_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

class Engine
{
    public:
        static Engine* GetInstance()
        {
            return s_Instance = (!(s_Instance == nullptr))? s_Instance : new Engine() ;
        }
        bool Init() ;
        bool Clean() ;
        void Quit() ;
        void Update() ;
        void Render() ;
        void Events() ;
        bool IsRunnin() {return m_IsRunnin;} ;
        SDL_Renderer* GetRenderer()
        {
            return renderer ;
        }
    private:
        Engine(){}
        bool m_IsRunnin ;
        SDL_Window* window ;
        SDL_Renderer* renderer ;
        static Engine* s_Instance;
};

#endif // ENGINE_H
