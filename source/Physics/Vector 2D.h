#ifndef VECTOR 2D_H
#define VECTOR 2D_H

#include<iostream>

using namespace std ;

class Vector2D
{
    public: int X , Y;

    public:
        /// Addition
        Vector2D operator+ (const Vector2D& v2) const
        {
            return Vector2D(X + v2.X , Y + v2.Y) ;
        }

        /// Subtraction
        Vector2D operator- (const Vector2D& v2) const
        {
            return Vector2D(X - v2.X , Y - v2.Y) ;
        }
        Vector2D operator* (const float scalar) const
        {
            return Vector2D(X * scalar , Y * scalar) ;
        }
        void Log(string msg = "")
        {
            cout << msg << "X , Y :" << X << " " << Y << endl ;
        }

    public:
        Vector2D(float x = 0 , float y = 0): X(x) , Y(y){}

    private:

};

#endif // VECTOR 2D_H
