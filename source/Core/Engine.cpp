#include "Engine.h"
#include <TextureManager.h>
#include<windows.h>
#include<Game.h>

using namespace std ; // delete this
// 1. Write your functions in camelCase or snake_case
// 2. Move the global variables into classes
// 3. Read about "Separation of concern"
// 4. Read about enum.
// 5. Write inital variable as constant, don't hard code value.
// 6. DRY principle
// 7. Code formatter: clang-format
// 8. pragma once

Engine* Engine::s_Instance = nullptr ;

bool Engine::BuilWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 and IMG_Init(IMG_INIT_JPG or IMG_INIT_PNG) != 0 )
    {
        cout << "Failed to Initialize SDL .... " << endl ;
        return false ;
    }
    window = SDL_CreateWindow("Asteroids" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , WINDOW_SIZE , WINDOW_SIZE , 0) ;
    if (window == nullptr)
    {
        cout << "Can not create a window ...." << endl ;
        return false ;
    }
    MainMenu = true ;
    Menu = false ;
    Levels.clear() ;
    Levels[1] = true ;
    level4 = false ;
    finall = new Final ;
    return true ;
}


bool Engine::Init()
{
    level4 = false ;
    ShipWidth = ShipHeight = 512 ;
    // NumberOfAsteroids = 1 ;
    score = 0 ;
    // AsteroidsSpeed = 10 ;
    m_IsRunnin = true ;
    GameOver = false ;
    Won = false ;
    Menu = false ;
    shots.clear() ;
    ast.clear() ;
    ShipPositionX = ShipPositionY = PLAYER_INITIAL_POSITION;
        /// Setting the Standard values
    renderer = SDL_CreateRenderer(window , -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        cout << "Can not render ... " << endl ;
        return false ;
    }
        /// Creating the Window and Renderer
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
    TextureManager::GetInstance()->Load("button1" , "Assets/button1.png") ;
    TextureManager::GetInstance()->Load("button2" , "Assets/button2.png") ;
    TextureManager::GetInstance()->Load("button3" , "Assets/button3.png") ;
    TextureManager::GetInstance()->Load("button4" , "Assets/button4.png") ;
    TextureManager::GetInstance()->Load("Resume" , "Assets/Resume.png") ;
    TextureManager::GetInstance()->Load("Restart" , "Assets/Restart.png") ;
    TextureManager::GetInstance()->Load("Quit" , "Assets/Quit.png") ;
    TextureManager::GetInstance()->Load("Shadow" , "Assets/shadow.png") ;
    TextureManager::GetInstance()->Load("Shadow2" , "Assets/shadow2.png") ;
    TextureManager::GetInstance()->Load("Enemy" , "Assets/final_enemy.png") ;

    player = new Warrior(new Properties("player" , ShipPositionX , ShipPositionY , ShipWidth , ShipHeight)) ;
    EnterButton = new ButtonCoolDown() ;
    /*
    Transform tf;
    tf.Log() ;
    */
    if (MainMenu == false)
        CreateAsteroids() ;
    return true ;
}

void Engine::CreateAsteroids()
{
    for (int i = 0 ; i < NumberOfAsteroids ; i ++ )
    {
        int ShipPositionX , ShipPositionY , z ;
        // AsteroidsSpeed = 10 ;
        ShipPositionX = rand() % WINDOW_SIZE ; // fix this
        ShipPositionY = 0 ; // where are these numbers coming
        asteroid = new Asteroids(new Properties("asteroid" , ShipPositionX , ShipPositionY , 800 , 800)) ;
        asteroid->CurX = ShipPositionX ;
        asteroid->CurY = ShipPositionY ;
        // Code duplication, DRY
        z = rand() % 2 ;
        ShipPositionX = rand() % AsteroidsSpeed ;
        if (z == 0)
            ShipPositionX *= -1 ;

        // ShipPositionY = getRandomR
        z = rand() % 2 ;
        ShipPositionY = rand() % AsteroidsSpeed ;
        if (z == 0)
            ShipPositionY *= -1;


        asteroid->DestX = ShipPositionX ;
        asteroid->DestY = ShipPositionY ;
        ast.push_back(asteroid) ;
    }
    // Init() ;
}


bool Engine::Clean()
{
    TextureManager::GetInstance()->Clean() ;
    SDL_DestroyRenderer(renderer) ;
}

void Engine::Quit()
{
    SDL_DestroyWindow(window) ;
    IMG_Quit() ;
    TTF_Quit() ;
    SDL_Quit() ;
    exit(0) ;
}

bool IsIntersecting(int X , int Y , int CurX , int CurY)
{
    if (CurX >= X and CurX <= X + 30 and CurY >= Y and CurY <= Y + 30)
        return true;
    CurX += 50 ;
    if (CurX >= X and CurX <= X + 30 and CurY >= Y and CurY <= Y + 30)
        return true;
    CurX -= 50 ;
    CurY += 50 ;
    if (CurX >= X and CurX <= X + 30 and CurY >= Y and CurY <= Y + 30)
        return true;
    CurX += 50 ;
    if (CurX >= X and CurX <= X + 30 and CurY >= Y and CurY <= Y + 30)
        return true;
    return false;
}

bool Engine::DoesShipCrashes()
{
    for (auto i : ast)
    {
        int CurX , CurY ;
        CurX = i->CurX ;
        CurY = i->CurY ;
        if (CurX >= ShipPositionX and CurX <= ShipPositionX + 80 and CurY >= ShipPositionY and CurY <= ShipPositionY + 80)
            return true ;
        CurX += 50 ;
        if (CurX >= ShipPositionX and CurX <= ShipPositionX + 80 and CurY >= ShipPositionY and CurY <= ShipPositionY + 80)
            return true ;
        CurX -= 50 ;
        CurY += 50 ;
        if (CurX >= ShipPositionX and CurX <= ShipPositionX + 80 and CurY >= ShipPositionY and CurY <= ShipPositionY + 80)
            return true ;
        CurX += 50 ;
        if (CurX >= ShipPositionX and CurX <= ShipPositionX + 80 and CurY >= ShipPositionY and CurY <= ShipPositionY + 80)
            return true ;
    }
    return false ;
}

void Engine::GameOvver()
{
    cout << "Salom" << endl ;
    GameOver = true ;
    Game::GetInstance()->StartCoolDown() ;
    Render() ;
    Game::GetInstance()->Reset() ;
}

void Engine::GameWon()
{
    Won = true ;
    Levels[CurrentLevel + 1] = true ;
    Game::GetInstance()->StartCoolDown() ;
    Render() ;
    Game::GetInstance()->Reset() ;
}

void Engine::Update()
{
    player->Update(0) ;
    // finall->Update() ;
    if (!ast.size() and MainMenu == false)
    {
        GameWon() ;
    }
    if (DoesShipCrashes())
    {
        GameOvver() ;
    }
    for (int i = 0 ; i < shots.size() ; i ++ )
    {
        int ok = -1 ;
        for (int j = 0 ; j < ast.size() ; j ++ )
        {
            if (IsIntersecting(shots[i]->x , shots[i]->y , ast[j]->CurX , ast[j]->CurY))
            {
                ok = j ;
                break ;
            }
        }
        if (ok != -1)
        {
            ast.erase(ast.begin() + ok) ;
            shots[i]->Delete(shots[i]->id) ;
            shots.erase(shots.begin() + i) ;
            i -- ;
            score ++ ;
        }
    }
    for (int i = 0 ; i < shots.size() ; i ++ )
    {
        int a , b ;
        if (shots[i]->x < 0 or shots[i]->y < 0 or shots[i]->x >= 1000 or shots[i]->y >= 1000)
        {
            shots[i]->Delete(shots[i]->id) ;
            shots.erase(shots.begin() , shots.begin() + i + 1) ;
            i -- ;
            continue ;
        }
    }
}

void Engine::ScoreDraw()
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
    if (level4)
    {
        ScoreDraw() ;
        player->Draw() ;
        finall->Draw() ;
        if (GameOver == true)
        {
            cout << "Game Over" << endl ;
            TextureManager::GetInstance()->Draw("gameover" , 0 , 300 , 2200 , 680) ;
            // system("pause") ;
            // return ;
        }
        else if (Won == true)
            TextureManager::GetInstance()->Draw("congragulations" , 250 , 300 , 360 , 360) ;
        else
            finall->Update() ;
        for (auto i : shots)
            i->Draw() ;
    }
    else if (MainMenu)
    {
        MainMenu::GetInstance()->Draw() ;
        int check = MainMenu::GetInstance()->Check() ;
        if (check == 1 and Levels[1] == true)
        {
            AsteroidsSpeed = 5 ;
            NumberOfAsteroids = 10 ;
            MainMenu = false ;
            CurrentLevel = 1 ;
            CreateAsteroids() ;
        }
        else if (check == 2 and Levels[2] == true)
        {
            AsteroidsSpeed = 10 ;
            NumberOfAsteroids = 15 ;
            MainMenu = false ;
            CurrentLevel = 2 ;
            CreateAsteroids() ;
        }
        else if (check == 3 and Levels[3] == true)
        {
            AsteroidsSpeed = 15 ;
            NumberOfAsteroids = 20 ;
            MainMenu = false ;
            CurrentLevel = 3 ;
            CreateAsteroids() ;
        }
        else if (check == 4 and Levels[4] == true) //and Levels[4] == true)
        {
            level4 = true ;
            finall->Init() ;
        }
    }
    else
    {
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
        if (Menu == true)
        {
            TextureManager::GetInstance()->Draw("Shadow" , 0 , 0 , 1000 , 1000 ) ;
            TextureManager::GetInstance()->Draw("Resume" , 300 , 300 , 940 , 210 ) ;
            TextureManager::GetInstance()->Draw("Restart" , 300 , 500 , 940 , 210 ) ;
            TextureManager::GetInstance()->Draw("Quit" , 300 , 700 , 940 , 210 ) ;
        }
    }
    SDL_RenderPresent(renderer) ;
}

void Engine::PlayersMovement()
{
    int angle ;
    if (GetAsyncKeyState('W') & 0x8000)
    {
        ShipPositionY -= 5 ;
        angle = player->Angle ;
        player = new Warrior(new Properties("player" , ShipPositionX , ShipPositionY , ShipWidth , ShipHeight)) ;
        player->Angle = angle ;
    }
    if (GetAsyncKeyState('A') & 0x8000)
    {
        ShipPositionX -= 5 ;
        angle = player->Angle ;
        player = new Warrior(new Properties("player" , ShipPositionX , ShipPositionY , ShipWidth , ShipHeight)) ;
        player->Angle = angle ;
    }
    if (GetAsyncKeyState('S') & 0x8000)
    {
        ShipPositionY += 5 ;
        angle = player->Angle ;
        player = new Warrior(new Properties("player" , ShipPositionX , ShipPositionY , ShipWidth , ShipHeight)) ;
        player->Angle = angle ;
    }
    if (GetAsyncKeyState('D') & 0x8000)
    {
        ShipPositionX += 5 ;
        angle = player->Angle ;
        player = new Warrior(new Properties("player" , ShipPositionX , ShipPositionY , ShipWidth , ShipHeight)) ;
        player->Angle = angle ;
    }
    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
        player->Angle -= 5 ;
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        player->Angle += 5 ;
    if (GetAsyncKeyState(VK_RETURN) & 0x8001 and !(EnterButton->IsCoolActive()))
    {
        EnterButton->StartCoolDown() ;
        shot = new Shooting ;
        double X , Y , pi , ans , a , b ;
        pi = 2 * acos(0.0) ;
        a = player->Angle ;
        a = a * pi / 180.0 ;
        Y = cos(a) ;
        X = sin(a) ;
        a = X * 50 ;
        b = Y * 50 ;
        b *= -1 ;
        X *= 10 ;
        Y *= -10 ;
        shot->CreateShot("shoot" , ShipPositionX + a + 30 , ShipPositionY + b + 30 , X , Y , 800 , 800 ) ;
        shots.push_back(shot) ;
    }
}

void Engine::AsteroidsMovement()
{
    for (int i = 0 ; i < ast.size() ; i ++ )
    {
        int MoveToX , MoveToY , x1 , y1 ;
        MoveToX = ast[i]->CurX + ast[i]->DestX ;
        if (MoveToX < 0 or MoveToX >= WINDOW_SIZE)
            ast[i]->DestX *= -1 , MoveToX = ast[i]->CurX + ast[i]->DestX ;
        MoveToY = ast[i]->CurY + ast[i]->DestY ;
        if (MoveToY < 0 or MoveToY >= WINDOW_SIZE)
            ast[i]->DestY *= -1 , MoveToY = ast[i]->CurY + ast[i]->DestY ;
        x1 = ast[i]->DestX ;
        y1 = ast[i]->DestY ;
        ast[i] = new Asteroids(new Properties("asteroid" , MoveToX , MoveToY , 800 , 800)) ;
        ast[i]->CurX = MoveToX ;
        ast[i]->CurY = MoveToY ;
        ast[i]->DestX = x1 ;
        ast[i]->DestY = y1 ;
    }
}

void Engine::ShotingMovement()
{
    for (auto i : shots)
    {
        i->Move() ;
    }
}

void Engine::Events()
{
    // cout << "Events Happening :: " << endl ;
    Game::GetInstance()->CheckEvents() ;
    PlayersMovement() ;
    AsteroidsMovement() ;
    ShotingMovement() ;
}
