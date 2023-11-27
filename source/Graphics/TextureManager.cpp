#include "TextureManager.h"
#include <Engine.h>

TextureManager* TextureManager::s_Instance = nullptr ;

using namespace std ;

bool TextureManager::Load(string id, string filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str()) ;
    if (surface == nullptr)
    {
        cout << "Failed to load surface in Texture Manager !!!" << endl ;
        return false ;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer() , surface) ;
    if (texture == nullptr)
    {
        cout << "Failed to create texture from surface in Texture Manager !!!" << endl ;
        return false ;
    }

    m_TextureMap[id] = texture ;

    return true ;
}

void TextureManager::Drop(string id)
{
    SDL_DestroyTexture(m_TextureMap[id]) ;
    m_TextureMap.erase(id) ;
}

void TextureManager::Clean()
{
    map < string , SDL_Texture*>::iterator it;
    for (it = m_TextureMap.begin() ; it != m_TextureMap.end() ; it ++ )
        SDL_DestroyTexture(it->second) ;
    m_TextureMap.clear() ;
    SDL_Log("texture map cleaned !") ;
}

void TextureManager::Draw(string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
    SDL_Rect sourceRect = {0 , 0 , width , height} ;
    SDL_Rect destinationRect = {x , y , width , height} ;
    if (id == "gameover")
        destinationRect = {x , y , 1000 , 340} ;
    if (id == "congragulations")
        destinationRect = {x , y , 500 , 500} ;
    if (id == "score")
        destinationRect = {x , y , 200 , 112} ;
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer() , m_TextureMap[id] , &sourceRect , &destinationRect , 0 , nullptr , flip) ;
}

void TextureManager::DrawFrame(string id , float x , float y , int width , int height , int angle , int row , int frame , SDL_RendererFlip flip)
{
    SDL_Rect sourceRect = {width*frame , height*row , width , height} ;
    SDL_Rect destinationRect = {x , y , 50 , 50} ;
    if (id == "asteroid")
        destinationRect = {x , y , 50 , 50} ;
    else if (id == "player")
        destinationRect = {x , y , 100 , 100 } ;
    else if (id == "shoot")
        destinationRect = {x , y , 30 , 30} ;
    else if (id == "Deleted")
        destinationRect = {x , y , 0 , 0} ;
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer() , m_TextureMap[id] , &sourceRect , &destinationRect , angle , nullptr , flip) ;
    // SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer() , &asd) ;
}
