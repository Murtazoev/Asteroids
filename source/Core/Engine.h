#ifndef ENGINE_H
#define ENGINE_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<Transform.h>
#include<Asteroids.h>
#include<deque>
#include<Shooting.h>
#include<Warrior.h>
#include<ButtonCoolDown.h>
#include<cmath>
#include<algorithm>
#include<MainMenu.h>
#include<map>
#include<Final.h>

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
        bool DoesShipCrashes() ;
        void ScoreDraw() ;
        void PlayersMovement() ;
        void ShotingMovement() ;
        void AsteroidsMovement() ;
        int NumberOfAsteroids , AsteroidsSpeed , CurrentLevel , WINDOW_SIZE = 1000 , ShipPositionX , ShipPositionY , score ;
        bool BuilWindow() ;
        bool MainMenu , Menu , level4 , GameOver ;
        void GameOvver() ;
        void GameWon() ;
        void CreateAsteroids() ;
        map < int , bool > Levels ;
        deque < Shooting* > shots ;
        SDL_Renderer* GetRenderer()
        {
            return renderer ;
        }

    private:
        Engine(){}
        bool m_IsRunnin , Won ;
        SDL_Renderer* renderer ;
        SDL_Window* window ;
        static Engine* s_Instance;
        int PLAYER_INITIAL_POSITION = WINDOW_SIZE / 2;
        int ShipWidth , ShipHeight;
        deque < Asteroids* > ast ;
        ButtonCoolDown* EnterButton = nullptr ;
        Warrior* player = nullptr ;
        Asteroids* asteroid = nullptr ;
        Final* finall = nullptr ;
        Shooting* shot = nullptr ;
};

#endif // ENGINE_H
