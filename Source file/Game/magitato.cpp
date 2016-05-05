#include "magitato.h"
#include "parameters.h"
#include "basicfunctoins.h"
#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

magitato::magitato()
{
    lv=0;
    hp=15;
    atk=5;
    cost=CostM;
    injury=0;
    attack_x=0;
    attack_y=SCREEN_HEIGHT-SPACE_X-200;
    attack_w=100;
    attack_h=200;
    width=100;
    height=150;
    WhichImage=0;
    AWhichImage=0;
    DWhichImage=0;
    collision=0;
    a=0;
    D_ani_ctrl=0;
    A_ani_ctrl=0;
    M_ani_ctrl=0;
    CurrentTexture=NULL;
    x=SCREEN_WIDTH-SPACE_X-width;
    y=SCREEN_HEIGHT-SPACE_Y-height;
}

void magitato::ChooseStage(SDL_Renderer *Renderer)
{
    if (hp<=0)
    {
        if (DWhichImage==8)
            DFadeOut(Renderer);
        else
            Dead(Renderer);
    }
    else if (a<255 && x==(SCREEN_WIDTH-SPACE_X-width))
        FadeIn(Renderer);
    else if (a!=0 && x==SPACE_X)
        FadeOut(Renderer);
    else if (collision==1 && a!=0)
        Attack(Renderer);
    else if (a==255 && x!=SPACE_X)
        Move(Renderer);
    SDL_DestroyTexture(CurrentTexture);
    CurrentTexture=NULL;
}

void magitato::Dead(SDL_Renderer *Renderer)
{
    //Set location
    SDL_Rect renderquad={x, y, width, height};
    CurrentTexture=SDL_CreateTextureFromSurface(Renderer, DeadImage[DWhichImage]);
    //Render to screen
    SDL_RenderCopy(Renderer, CurrentTexture, NULL, &renderquad );
    D_ani_ctrl++;
    if (D_ani_ctrl==DA_Vel)
    {
        DWhichImage++;
        D_ani_ctrl=0;
    }
}

void magitato::DFadeOut(SDL_Renderer *Renderer)
{
    //Set location
    SDL_Rect renderquad={x, y, width, height};
    CurrentTexture=SDL_CreateTextureFromSurface(Renderer, DeadImage[7]);
    SetAlpha(a);
    //Render to screen
    SDL_RenderCopy(Renderer, CurrentTexture, NULL, &renderquad );
    if (a!=0)
        a-=FADE_COE;
}

void magitato::FadeIn(SDL_Renderer *Renderer)
{
    //Set location
    SDL_Rect renderquad={x, y, width, height};
    CurrentTexture=SDL_CreateTextureFromSurface(Renderer, Image[WhichImage]);
    SetAlpha(a);
    //Render to screen
    SDL_RenderCopy(Renderer, CurrentTexture, NULL, &renderquad );
    a+=FADE_COE;
}

void magitato::FadeOut(SDL_Renderer *Renderer)
{
    //Set location
    SDL_Rect renderquad={x, y, width, height};
    CurrentTexture=SDL_CreateTextureFromSurface(Renderer, Image[WhichImage]);
    SetAlpha(a);
    //Render to screen
    SDL_RenderCopy(Renderer, CurrentTexture, NULL, &renderquad );
    if (a!=0)
        a-=FADE_COE;
}

void magitato::Attack(SDL_Renderer *Renderer)
{
    //Set location
    SDL_Rect renderquad={x, y, width, height};
    CurrentTexture=SDL_CreateTextureFromSurface(Renderer, AttackImage[AWhichImage]);
    //Render to screen
    SDL_RenderCopy(Renderer, CurrentTexture, NULL, &renderquad );
    /*A_ani_ctrl++;
    if (A_ani_ctrl==AtkA_Vel)
    {
        AWhichImage++;
        A_ani_ctrl=0;
    }
    AWhichImage%=8;*/
}

void magitato::Attack2(SDL_Renderer *Renderer)
{
    SDL_Rect renderquad={attack_x, attack_y, attack_w, attack_h};
    CurrentTexture=SDL_CreateTextureFromSurface(Renderer, AttackImage2[AWhichImage]);
    //Render to screen
    SDL_RenderCopy(Renderer, CurrentTexture, NULL, &renderquad );
    A_ani_ctrl++;
    if (A_ani_ctrl==AtkA_Vel)
    {
        AWhichImage++;
        A_ani_ctrl=0;
    }
    AWhichImage%=8;
    SDL_DestroyTexture(CurrentTexture);
    CurrentTexture=NULL;
}

void magitato::Move(SDL_Renderer *Renderer)
{
    //Set location
    SDL_Rect renderquad={x, y, width, height};
    CurrentTexture=SDL_CreateTextureFromSurface(Renderer, Image[WhichImage]);
    //Render to screen
    SDL_RenderCopy(Renderer, CurrentTexture, NULL, &renderquad );
    if (x!=SPACE_X)
        x-=M_Vel;
    if (x<SPACE_X)
        x=SPACE_X;
    M_ani_ctrl++;
    if (M_ani_ctrl==MA_Vel)
    {
        WhichImage++;
        M_ani_ctrl=0;
    }
    WhichImage%=8;
}

void magitato::SetAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(CurrentTexture, alpha);
}

int magitato::GetWidth()
{
    return width;
}

int magitato::GetHeight()
{
    return height;
}

int magitato::GetAAni()
{
    return A_ani_ctrl;
}

void magitato::free()
{
    for (int i=0;i<8;i++)
    {
        SDL_FreeSurface(Image[i]);
        Image[i]=NULL;
        SDL_FreeSurface(AttackImage[i]);
        AttackImage[i]=NULL;
        SDL_FreeSurface(DeadImage[i]);
        DeadImage[i]=NULL;
    }
}