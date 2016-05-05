#ifndef __Game__basicfunctoins__
#define __Game__basicfunctoins__

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string>
#include "parameters.h"
#include "potany.h"
#include "tankitato.h"
#include "magitato.h"
#include "healitato.h"
#include "epotany.h"
#include "etankitato.h"
#include "emagitato.h"
#include "ehealitato.h"

void LoadImageToRenderer(std::string path, SDL_Renderer *Renderer, int x, int y);

void SurfaceToRenderer(SDL_Surface* , SDL_Renderer *Renderer, int x, int y, SDL_Rect *clip, Uint8 a);

class opening
{
public:
    opening();
    
    bool change;
    int SelectWhich, gx;
    Uint8 a;
    SDL_Surface *SelectImage[8], *title, *play, *help, *quit, *mgpotany, *mepotany;
    
    void Print(SDL_Renderer *Renderer);
    void EndPrint_FadeOut(SDL_Renderer *Renderer);
    void EndPrint_Move(SDL_Renderer *Renderer);
private:
    int SelectWhichImage;
    SDL_Rect gclip, eclip;
    
    void Select(int, SDL_Renderer *Renderer);
};

class help
{
public:
    help();
    int Select, WhichImage, M_ani_ctrl;
    SDL_Surface *Image[5][8];
    
    void Print(SDL_Renderer *Renderer);
private:
};

class material
{
public:
    material();
    material(int, int, int);
    
    Uint8 a;
    void Print(SDL_Renderer *Renderer);
    void FadeIn(SDL_Renderer *Renderer);
    bool SucSummon (int type);
    bool LevelUp(int type);
private:
    int x, y, number, vel, type;
    SDL_Surface *Image[10], *potato[2][4];
    SDL_Texture *Texture;
};

class house
{
public:
    house(int, int, int);
    
    int hp, gore, p_levelup, t_levelup, m_levelup, h_levelup, levelup[2][4];
    Uint8 a;
    void FadeIn(SDL_Renderer *Renderer);
    void Print(SDL_Renderer *Renderer);
private:
    int house_x, house_y, number_x, number_y;
    SDL_Surface *Image, *Number[10], *Slash, *Color[2][4];
    SDL_Texture *Texture;
};

class potatoqueue
{
public:
    
    material gm, em;//為什麼不能在這直接gm(0, 0)
    house gh, eh;

    potatoqueue();
    void Print(SDL_Renderer *Renderer);
    void EndPrint(SDL_Renderer *Renderer);
    void Push(int type);
    void Pop(int type);
    bool CheckCollision(int type, int WhichOne);
    int CollisionWithG(int type, int WhichOne);
    int CollisionWithE(int type, int WhichOne);
    void LevelUp(int type);
    void free();

private:
    int p_f=0, p_c=-1,
        t_f=0, t_c=-1,
        m_f=0, m_c=-1,
        h_f=0, h_c=-1,
        ep_f=0, ep_c=-1,
        et_f=0, et_c=-1,
        em_f=0, em_c=-1,
        eh_f=0, eh_c=-1;
    
    potany po[NumberP];
    tankitato tank[NumberT];
    magitato mag[NumberM];
    healitato heal[NumberH];
    epotany epo[NumberP];
    etankitato etank[NumberT];
    emagitato emag[NumberM];
    ehealitato eheal[NumberH];
};

#endif