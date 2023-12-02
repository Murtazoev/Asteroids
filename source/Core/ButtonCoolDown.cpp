#include "ButtonCoolDown.h"

ButtonCoolDown::ButtonCoolDown()
{
    isButtonBlocked = false ;
}

void ButtonCoolDown::StartCoolDown()
{
    isButtonBlocked = true;
    cooldownEndTime = chrono::steady_clock::now() + std::chrono::milliseconds(100);
}

bool ButtonCoolDown::IsCoolActive()
{
    return isButtonBlocked && chrono::steady_clock::now() < cooldownEndTime;
    if (chrono::steady_clock::now() < cooldownEndTime and isButtonBlocked == true)
        return true ;
    else
    {
        isButtonBlocked = false ;
        return false ;
    }
}

void ButtonCoolDown::ShowProperties()
{
    cout << isButtonBlocked << endl ;
    cout << "Button Properties" << endl ;
}

