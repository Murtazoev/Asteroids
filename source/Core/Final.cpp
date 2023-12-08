#include "Final.h"
#include<Engine.h>
#include<cmath>
#include<Game.h>

Final::Final()
{
    Life = 100 ;
    //ctor
}

void Final::Init()
{
    Engine::GetInstance()->score = 100 ;
    posX = posY = 0 ;
    desX = rand() % 10 ;
    desY = rand() % 10 ;
    Engine::GetInstance()->AsteroidsSpeed = 10 ;
    ast.clear() ;
    StartCoolDown() ;
}

void Final::Draw()
{
    TextureManager::GetInstance()->Draw("Enemy" , posX , posY , 800 , 800) ;
    for (auto i : ast)
        i->Draw() ;
}

bool Final::DoesShipCrashes()
{
    for (auto i : ast)
    {
        int CurX , CurY ;
        CurX = i->CurX ;
        CurY = i->CurY ;
        if (CurX >= Engine::GetInstance()->ShipPositionX and CurX <= Engine::GetInstance()->ShipPositionX + 80 and CurY >= Engine::GetInstance()->ShipPositionY and CurY <= Engine::GetInstance()->ShipPositionY + 80)
            return true ;
        CurX += 50 ;
        if (CurX >= Engine::GetInstance()->ShipPositionX and CurX <= Engine::GetInstance()->ShipPositionX + 80 and CurY >= Engine::GetInstance()->ShipPositionY and CurY <= Engine::GetInstance()->ShipPositionY + 80)
            return true ;
        CurX -= 50 ;
        CurY += 50 ;
        if (CurX >= Engine::GetInstance()->ShipPositionX and CurX <= Engine::GetInstance()->ShipPositionX + 80 and CurY >= Engine::GetInstance()->ShipPositionY and CurY <= Engine::GetInstance()->ShipPositionY + 80)
            return true ;
        CurX += 50 ;
        if (CurX >= Engine::GetInstance()->ShipPositionX and CurX <= Engine::GetInstance()->ShipPositionX + 80 and CurY >= Engine::GetInstance()->ShipPositionY and CurY <= Engine::GetInstance()->ShipPositionY + 80)
            return true ;
    }
    int CurX , CurY ;
    CurX = Engine::GetInstance()->ShipPositionX ;
    CurY = Engine::GetInstance()->ShipPositionY ;
    if (CurX >= posX + 50 and CurX <= posX + 150 and CurY >= posY + 50 and CurY <= posY + 150)
        return true ;
    CurX += 100 ;
    if (CurX >= posX + 50 and CurX <= posX + 150 and CurY >= posY + 50 and CurY <= posY + 150)
        return true ;
    CurX -= 100 ;
    CurY += 100 ;
    if (CurX >= posX + 50 and CurX <= posX + 150 and CurY >= posY + 50 and CurY <= posY + 150)
        return true ;
    CurX += 100 ;
    if (CurX >= posX + 50 and CurX <= posX + 150 and CurY >= posY + 50 and CurY <= posY + 150)
        return true ;
    return false ;
}

bool Final::IsIntersecting(int X , int Y , int CurX , int CurY)
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

bool Final::HurtEnemy(int x , int y)
{
    deque < Shooting* > sht ;
    sht = Engine::GetInstance()->shots ;
    int X , Y ;
    X = posX + 50 ;
    Y = posY + 50 ;
    if (x >= X and x <= X + 150 and y >= Y and y <= Y + 150)
        return true ;
    if (x + 50 >= X and x + 50 <= X + 150 and y >= Y and y <= Y + 150)
        return true ;
    if (x >= X and x <= X + 150 and y + 50 >= Y and y + 50 <= Y + 150)
        return true ;
    if (x + 50 >= X and x + 50 <= X + 150 and y + 50 >= Y and y + 50 <= Y + 150)
        return true ;
    return false ;
}

void Final::Update()
{
    if ((!ast.size() and Engine::GetInstance()->MainMenu == false) or (Engine::GetInstance()->score == 0))
    {
        Engine::GetInstance()->GameWon() ;
    }
    if (DoesShipCrashes())
    {
        Engine::GetInstance()->GameOvver() ;
    }
    if (!IsCoolActive())
    {
        CreateShot() ;
        // system("pause") ;
        StartCoolDown() ;
    }
    ////
    deque < Shooting* > sht ;
    sht = Engine::GetInstance()->shots ;
    for (int i = 0 ; i < sht.size() ; i ++ )
    {
        int ok = -1 ;
        for (int j = 0 ; j < ast.size() ; j ++ )
        {
            if (IsIntersecting(sht[i]->x , sht[i]->y , ast[j]->CurX , ast[j]->CurY))
            {
                ok = j ;
                break ;
            }
        }
        if (ok != -1)
        {
            ast.erase(ast.begin() + ok) ;
            sht[i]->Delete(sht[i]->id) ;
            sht.erase(sht.begin() + i) ;
            i -- ;
        }
        else if (HurtEnemy(sht[i]->x , sht[i]->y))
        {
            sht.erase(sht.begin() + i) ;
            i -- ;
            Engine::GetInstance()->score -- ;
        }
    }
    for (int i = 0 ; i < sht.size() ; i ++ )
    {
        int a , b ;
        if (sht[i]->x < 0 or sht[i]->y < 0 or sht[i]->x >= 1000 or sht[i]->y >= 1000)
        {
            sht[i]->Delete(sht[i]->id) ;
            sht.erase(sht.begin() , sht.begin() + i + 1) ;
            i -- ;
            continue ;
        }
    }
    Engine::GetInstance()->shots = sht ;
    AsteroidsMovement() ;
    EnemyMovement() ;
}

void Final::CreateShot()
{
    int z ;
    double x , y , a , b ;
    x = posX - Engine::GetInstance()->ShipPositionX ;
    y = posY - Engine::GetInstance()->ShipPositionY ;
    double AngleRadians = atan2(y , x) ;
    double angleDegree = AngleRadians * 180 / M_PI ;
    if (angleDegree < 360.0)
        angleDegree += 360 ;
//       a = a * pi / 180.0 ;
//        Y = cos(a) ;
//        X = sin(a) ;
//        a = X * 50 ;
//        b = Y * 50 ;
//        b *= -1 ;
//        X *= 10 ;
//        Y *= -10 ;
    angleDegree = angleDegree * M_PI / 180.0 ;
    x = cos(angleDegree) ;
    y = sin(angleDegree) ;
    a = x * 100 ;
    b = y * 100 ;
    b *= -1 ;
    a *= -1 ;
    x *= 10 ;
    y *= 10 ;
    x *= -1 ;
    y *= -1 ;
    asteroid = new Asteroids(new Properties("asteroid" , posX + a + 50 , posY + b + 50 , 800 , 800)) ;
    asteroid->CurX = posX + a ;
    asteroid->CurY = posY + b ;
    asteroid->DestX = x ;
    asteroid->DestY = y ;
    // system("pause") ;
    ast.push_back(asteroid) ;
}

void Final::AsteroidsMovement()
{
    for (int i = 0 ; i < ast.size() ; i ++ )
    {
        int MoveToX , MoveToY , x1 , y1 ;
        MoveToX = ast[i]->CurX + ast[i]->DestX ;
        if (MoveToX < 0 or MoveToX >= Engine::GetInstance()->WINDOW_SIZE)
            ast[i]->DestX *= -1 , MoveToX = ast[i]->CurX + ast[i]->DestX ;
        MoveToY = ast[i]->CurY + ast[i]->DestY ;
        if (MoveToY < 0 or MoveToY >= Engine::GetInstance()->WINDOW_SIZE)
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


void Final::StartCoolDown()
{
    Waiting = true;
    cooldownEndTime = chrono::steady_clock::now() + std::chrono::milliseconds(1000);
}

bool Final::IsCoolActive()
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

void Final::EnemyMovement()
{
    int MoveToX , MoveToY ;
    MoveToX = posX + desX ;
    if (MoveToX < 0 or MoveToX >= Engine::GetInstance()->WINDOW_SIZE - 100 )
        desX *= -1 , MoveToX = posX + desX ;
    MoveToY = posY + desY ;
    if (MoveToY < 0 or MoveToY >= Engine::GetInstance()->WINDOW_SIZE - 100 )
        desY *= -1 , MoveToY = posY + desY ;
    int x1 , y1 ;
    x1 = desX ;
    y1 = desY ;
    posX = MoveToX ;
    posY = MoveToY ;
    desX = x1 ;
    desY = y1 ;
}

