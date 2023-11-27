#include "Engine.h"
#include <TextureManager.h>
#include<Transform.h>
#include<Warrior.h>
#include<windows.h>
#include<Asteroids.h>
// #include<bits/stdc++.h>
#include<deque>
#include<Shooting.h>
#include<cmath>
#include<algorithm>
#include<conio.h>
#include<thread>
#include<SDL2/SDL_ttf.h>

using namespace std ;

Engine* Engine::s_Instance = nullptr ;
Warrior* player = nullptr ;
Asteroids* asteroid = nullptr ;
Shooting* shot = nullptr ;
deque < Asteroids* > ast ;
deque < Shooting* > shots ;
int x , y , score ;

std::chrono::steady_clock::time_point cooldownEndTime;
bool isButtonBlocked = false;
bool GameOver = false ;
bool Won = false ;

void startCooldown() {
    isButtonBlocked = true;
    cooldownEndTime = std::chrono::steady_clock::now() + std::chrono::seconds(1);
}

bool isCooldownActive() {
    return isButtonBlocked && std::chrono::steady_clock::now() < cooldownEndTime;
}

bool Engine::Init()
{
    score = 0 ;
    m_IsRunnin = true ;
    GameOver = false ;
    Won = false ;
    shots.clear() ;
    ast.clear() ;
    x = y = 500 ;
    if (SDL_Init(SDL_INIT_VIDEO) != 0 and IMG_Init(IMG_INIT_JPG or IMG_INIT_PNG) != 0 )
    {
        cout << "Failed to Initialize SDL .... " << endl ;
        return false ;
    }
    window = SDL_CreateWindow("Asteroids" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 1000 , 1000 , 0) ;
    if (window == nullptr)
    {
        cout << "Can not create a window ...." << endl ;
        return false ;
    }
    renderer = SDL_CreateRenderer(window , -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) ;
    if (renderer == nullptr)
    {
        cout << "Can not render ... " << endl ;
        return false ;
    }
    TextureManager::GetInstance()->Load("player" , "Assets/ship.png") ;
    TextureManager::GetInstance()->Load("background" , "Assets/background.jpg") ;
    TextureManager::GetInstance()->Load("asteroid" , "Assets/asteroid.png" ) ;
    TextureManager::GetInstance()->Load("shoot" , "Assets/shoot.png") ;
    TextureManager::GetInstance()->Load("gameover" , "Assets/gameover.png") ;
    TextureManager::GetInstance()->Load("congragulations" , "Assets/congragulations.png") ;
    TextureManager::GetInstance()->Load("score" , "Assets/score.png") ;
    TextureManager::GetInstance()->Load("n0" , "Assets/numbers/0.png") ;
    TextureManager::GetInstance()->Load("n1" , "Assets/numbers/1.png") ;
    TextureManager::GetInstance()->Load("n2" , "Assets/numbers/2.png") ;
    TextureManager::GetInstance()->Load("n3" , "Assets/numbers/3.png") ;
    TextureManager::GetInstance()->Load("n4" , "Assets/numbers/4.png") ;
    TextureManager::GetInstance()->Load("n5" , "Assets/numbers/5.png") ;
    TextureManager::GetInstance()->Load("n6" , "Assets/numbers/6.png") ;
    TextureManager::GetInstance()->Load("n7" , "Assets/numbers/7.png") ;
    TextureManager::GetInstance()->Load("n8" , "Assets/numbers/8.png") ;
    TextureManager::GetInstance()->Load("n9" , "Assets/numbers/9.png") ;

    for (int i = 0 ; i < 10 ; i ++ )
    {
        int speed ;
        int x , y , z ;
        speed = 10 ;
        x = rand() % 900 ;
        y = rand() % 900 ;
        asteroid = new Asteroids(new Properties("asteroid" , x , y , 800 , 800)) ;
        asteroid->CurX = x ;
        asteroid->CurY = y ;
        z = rand() % 2 ;
        x = rand() % speed ;
        if (z == 0)
            x *= -1 ;
        z = rand() % 2 ;
        y = rand() % speed ;
        if (z == 0)
            y *= -1 ;
        asteroid->DestX = x ;
        asteroid->DestY = y ;
        ast.push_back(asteroid) ;
    }

    player = new Warrior(new Properties("player" , 500 , 500 , 512 , 512)) ;

    Transform tf;
    tf.Log() ;
    return true ;
}

bool Engine::Clean()
{
    TextureManager::GetInstance()->Clean() ;
    SDL_DestroyRenderer(renderer) ;
    SDL_DestroyWindow(window) ;
    IMG_Quit() ;
    TTF_Quit() ;
    SDL_Quit() ;
}

void Engine::Quit()
{
    exit(0) ;
}

bool IsIntersecting(int X , int Y , int CurX , int CurY)
{
    if (CurX >= X and CurX <= X + 30 and CurY >= Y and CurY <= Y + 30)
        return true ;
    CurX += 50 ;
    if (CurX >= X and CurX <= X + 30 and CurY >= Y and CurY <= Y + 30)
        return true ;
    CurX -= 50 ;
    CurY += 50 ;
    if (CurX >= X and CurX <= X + 30 and CurY >= Y and CurY <= Y + 30)
        return true ;
    CurX += 50 ;
    if (CurX >= X and CurX <= X + 30 and CurY >= Y and CurY <= Y + 30)
        return true ;
    return false ;
}

void Restart()
{
    SDL_Event event ;
    SDL_PollEvent(&event) ;
    int ok = 0 ;
    while (1)
    {
        if (GetAsyncKeyState('R') & 0x8000)
        {
            ok = -1 ;
            break ;
        }
        if (GetAsyncKeyState('Q') & 0x8000)
        {
            ok = 1 ;
            break ;
        }
        ok ++ ;
        Engine::GetInstance()->Render() ;
    }
    if (ok == -1)
    {
        Engine::GetInstance()->Clean() ;
        Engine::GetInstance()->Init() ;
    }
    if (ok == 1)
    {
        Engine::GetInstance()->Quit() ;
    }
}

void Pause()
{
    while (1)
    {
        if ((GetAsyncKeyState('P') & 0x8000) and (!isCooldownActive()))
        {
            isButtonBlocked = false ;
            startCooldown() ;
            break ;
        }
    }
}

bool DoesShipCrashes()
{
    for (auto i : ast)
    {
        int CurX , CurY ;
        CurX = i->CurX ;
        CurY = i->CurY ;
        if (CurX >= x and CurX <= x + 80 and CurY >= y and CurY <= y + 80)
            return true ;
        CurX += 50 ;
        if (CurX >= x and CurX <= x + 80 and CurY >= y and CurY <= y + 80)
            return true ;
        CurX -= 50 ;
        CurY += 50 ;
        if (CurX >= x and CurX <= x + 80 and CurY >= y and CurY <= y + 80)
            return true ;
        CurX += 50 ;
        if (CurX >= x and CurX <= x + 80 and CurY >= y and CurY <= y + 80)
            return true ;
        // cout << CurX << " " << CurY << " " << x << " " << y << endl ;
        // return false ;
    }
    return false ;
}

void Engine::Update()
{
    player->Update(0) ;
    // system("pause") ;
    if ((GetAsyncKeyState('P') & 0x8000) and (!isCooldownActive()))
    {
        isButtonBlocked = false ;
        startCooldown() ;
        Pause() ;
    }
    if (ast.size() == 0)
    {
        Won = true ;
        Engine::GetInstance()->Render() ;
        Restart() ;
    }
    // cout << "I am here" << endl ;
    if (DoesShipCrashes() == true)
    {
        // GameOver() ;
        // cout << "Crashed" << endl ;
        // TextureManager::GetInstance()->Draw("gameover" , 0 , 0 , 2200 , 1208) ;
        GameOver = true ;
        Engine::GetInstance()->Render() ;
        Restart() ;
    }
    for (int i = 0 ; i < shots.size() ; i ++ )
    {
        int ok = -1 ;
        for (int j = 0 ; j < ast.size() ; j ++ )
        {
            // cout << "Before Crash Update:: " << ast.size() << " " << shots.size() << endl ;
            if (IsIntersecting(shots[i]->x , shots[i]->y , ast[j]->CurX , ast[j]->CurY))
            {
                ok = j ;
                break ;
            }
        }
        if (ok != -1)
        {
            cout << ast[ok]->CurX << " " << ast[ok]->CurY << " " << shots[i]->x << " " << shots[i]->y << endl ;
            cout << ast.size() << " " << shots.size() << endl ;
            ast.erase(ast.begin() + ok) ;
            cout << ast.size() << endl ;
            // system("pause") ;
            shots[i]->Delete(shots[i]->id) ;
            shots.erase(shots.begin() + i) ;
            i -- ;
            score ++ ;
            // system("pause") ;
        }
    }
    // cout << " ! " << endl ;
    for (int i = 0 ; i < shots.size() ; i ++ )
    {
        int a , b ;
        // a = shots[i]->x ;
        // b = shots[i]->y
        if (shots[i]->x < 0 or shots[i]->y < 0 or shots[i]->x >= 1000 or shots[i]->y >= 1000)
        {
            shots[i]->Delete(shots[i]->id) ;
            // cout << i << endl ;
            shots.erase(shots.begin() , shots.begin() + i + 1) ;
            i -- ;
            continue ;
        }
    }
    /*
    asteroid->Update(0) ;
    ast->Update(0) ;
    */
}

void ScoreDraw()
{
    TextureManager::GetInstance()->Draw("score" , 0 , 0 , 300 , 169) ;
    int X = 210 ;
    deque < string > v ;
    int cnt = score ;
    while (v.size() == 0 or cnt != 0)
    {
        int a = cnt % 10 ;
        if (a == 0)
            v.push_back("n0") ;
        if (a == 1)
            v.push_back("n1") ;
        if (a == 2)
            v.push_back("n2") ;
        if (a == 3)
            v.push_back("n3") ;
        if (a == 4)
            v.push_back("n4") ;
        if (a == 5)
            v.push_back("n5") ;
        if (a == 6)
            v.push_back("n6") ;
        if (a == 7)
            v.push_back("n7") ;
        if (a == 8)
            v.push_back("n8") ;
        if (a == 9)
            v.push_back("n9") ;
        cnt /= 10 ;
    }
    cout << v.size() << endl ;
    for (int i = v.size() - 1 ; i >= 0 ; i -- )
    {
        TextureManager::GetInstance()->DrawFrame(v[i] , X , 0 , 300 , 400 , 0 , 0 , 0) ;
        X += 50 ;
    }
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(renderer , 125 , 55 , 254 , 255) ;
    SDL_RenderClear(renderer) ;
    TextureManager::GetInstance()->Draw("background" , 0 , 0 , 1000 , 1000) ;
    // TextureManager::GetInstance()->Draw("player" , 100 , 200 , 512 , 512 ) ;
    player->Draw() ;
    for (auto i : ast)
    {
        i->Draw() ;
    }
    for (auto i : shots)
    {
        i->Draw() ;
    }
    ScoreDraw() ;
    if (GameOver == true)
        TextureManager::GetInstance()->Draw("gameover" , 0 , 300 , 2200 , 680) ;
    if (Won == true)
        TextureManager::GetInstance()->Draw("congragulations" , 250 , 300 , 360 , 360) ;
    // TextureManager::GetInstance()->Draw("gameover" , 0 , 0 , 2200 , 1208) ;
    SDL_RenderPresent(renderer) ;
}

void PlayersMovement()
{
    int angle ;
    if (GetAsyncKeyState('W') & 0x8000)
    {
        y -= 5 ;
        angle = player->Angle ;
        player = new Warrior(new Properties("player" , x , y , 512 , 512)) ;
        player->Angle = angle ;
    }
    if (GetAsyncKeyState('A') & 0x8000)
    {
        x -= 5 ;
        angle = player->Angle ;
        player = new Warrior(new Properties("player" , x , y , 512 , 512)) ;
        player->Angle = angle ;
    }
    if (GetAsyncKeyState('S') & 0x8000)
    {
        y += 5 ;
        angle = player->Angle ;
        player = new Warrior(new Properties("player" , x , y , 512 , 512)) ;
        player->Angle = angle ;
    }
    if (GetAsyncKeyState('D') & 0x8000)
    {
        x += 5 ;
        angle = player->Angle ;
        player = new Warrior(new Properties("player" , x , y , 512 , 512)) ;
        player->Angle = angle ;
    }
    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
        player->Angle -= 5 ;
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        player->Angle += 5 ;
    if (GetKeyState(VK_RETURN) & 0x8000)
    {
        shot = new Shooting ;
        double X , Y , pi , ans , a , b ;
        pi = 2 * acos(0.0) ;
        a = player->Angle ;
        a = a * pi / 180.0 ;
        Y = cos(a) ;
        X = sin(a) ;
        // cout << X << " " << Y << " " << pi << " " << player->Angle << endl ;
        a = X * 50 ;
        b = Y * 50 ;
        b *= -1 ;
        // a *= -1 ;
        X *= 10 ;
        Y *= -10 ;
        shot->CreateShot("shoot" , x + a + 30 , y + b + 30 , X , Y , 800 , 800 ) ;
        shots.push_back(shot) ;
    }
}

void AsteroidsMovement()
{
    for (int i = 0 ; i < ast.size() ; i ++ )
    {
        int x , y , x1 , y1 ;
        /// cout << ast->CurX << " " << ast->CurY << " " << ast->DestX << " " << ast->DestY << endl ;
        x = ast[i]->CurX + ast[i]->DestX ;
        if (x < 0 or x >= 1000)
            ast[i]->DestX *= -1 , x = ast[i]->CurX + ast[i]->DestX ;
        y = ast[i]->CurY + ast[i]->DestY ;
        if (y < 0 or y >= 1000)
            ast[i]->DestY *= -1 , y = ast[i]->CurY + ast[i]->DestY ;
        x1 = ast[i]->DestX ;
        y1 = ast[i]->DestY ;
        ast[i] = new Asteroids(new Properties("asteroid" , x , y , 800 , 800)) ;
        ast[i]->CurX = x ;
        ast[i]->CurY = y ;
        ast[i]->DestX = x1 ;
        ast[i]->DestY = y1 ;
    }
}

void ShotingMovement()
{
    for (auto i : shots)
    {
        i->Move() ;
    }
}

void Engine::Events()
{
    SDL_Event event ;
    SDL_PollEvent(&event) ;
    PlayersMovement() ;
    AsteroidsMovement() ;
    ShotingMovement() ;
    if (event.type == SDL_QUIT)
    {
        Quit() ;
    }
}
