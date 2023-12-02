#ifndef BUTTONCOOLDOWN_H
#define BUTTONCOOLDOWN_H

#include<conio.h>
#include<thread>
#include<iostream>

using namespace std ;

class ButtonCoolDown
{
    public:
        ButtonCoolDown();
        void StartCoolDown() ;
        bool IsCoolActive() ;
        void ShowProperties() ;

    protected:

    private:
        chrono::steady_clock::time_point cooldownEndTime;
        bool isButtonBlocked ;
};

#endif // BUTTONCOOLDOWN_H
