#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<IObject.h>
#include<Transform.h>

struct Properties
{
    public:
        Properties(string textureID , int x , int y , int width , int height , SDL_RendererFlip flip = SDL_FLIP_NONE)
        {
            X = x ;
            Y = y ;
            Flip = flip ;
            Width = width ;
            Height = height ;
            TextureID = textureID ;
        }

    public:
        float X , Y ;
        int Width, Height ;
        string TextureID ;
        SDL_RendererFlip Flip ;
};

class GameObject : public IObject
{
    public:
        GameObject(Properties* props) :
        m_TextureID(props->TextureID) , m_Width(props->Width) , m_Height(props->Height) , m_Flip(props->Flip)
        {
            m_Transform = new Transform(props->X , props->Y) ;
        }

        virtual void Draw() = 0 ;
        virtual void Clean() = 0 ;
        virtual void Update(float dt) = 0 ;

    protected:
        Transform* m_Transform ;
        int m_Width, m_Height , m_Angle ;
        string m_TextureID ;
        SDL_RendererFlip m_Flip ;
};

#endif // GAMEOBJECT_H
