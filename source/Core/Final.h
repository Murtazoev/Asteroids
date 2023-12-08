#ifndef FINAL_H
#define FINAL_H

#include<TextureManager.h>
#include<thread>
#include<conio.h>
#include<iostream>
#include<Asteroids.h>
#include<deque>
#include<Shooting.h>

using namespace std ;

class Final
{
    public:
        Final();
        void Init() ;
        void Draw() ;
        void Update() ;
        int posX , posY , desX , desY , Life ;
        void StartCoolDown() ;
        bool IsCoolActive() ;
        void CreateShot() ;
        bool Waiting ;
        void AsteroidsMovement() ;
        void EnemyMovement() ;
        bool DoesShipCrashes() ;
        bool HurtEnemy(int x , int y) ;
        bool IsIntersecting(int X , int Y , int CurX , int CurY) ;
        chrono::steady_clock::time_point cooldownEndTime;

    protected:

    private:
        deque < Asteroids* > ast ;
        Asteroids* asteroid ;
};

#endif // FINAL_H
