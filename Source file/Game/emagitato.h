#ifndef __Game__emagitato__
#define __Game__emagitato__

#include <SDL2/SDL.h>

class emagitato
{
public:
    int x, y, lv, hp, atk, cost, injury, attack_x, attack_y, attack_w, attack_h, AWhichImage, DWhichImage;
    bool collision;
    Uint8 a;
    SDL_Surface *Image[8], *AttackImage[8], *AttackImage2[8], *DeadImage[8];
    //Inititalize variables
    emagitato();
    //Choose what to print
    void ChooseStage(SDL_Renderer *Renderer);
    //Get width
    int GetWidth();
    //Get height
    int GetHeight();
    //Get ani_ctrl
    int GetAAni();
    //light
    void Attack2(SDL_Renderer *Renderer);
    //Free the resources
    void free();
private:
    //Whichimage to print
    int width, height, WhichImage, D_ani_ctrl, A_ani_ctrl, M_ani_ctrl;
    SDL_Texture *CurrentTexture;
    
    //Dead
    void Dead(SDL_Renderer *Renderer);
    //Dead Fade Out
    void DFadeOut(SDL_Renderer *Renderer);
    //Fade in
    void FadeIn(SDL_Renderer *Renderer);
    //Fade out
    void FadeOut(SDL_Renderer *Renderer);
    //Attack
    void Attack(SDL_Renderer *Renderer);
    //Move
    void Move(SDL_Renderer *Renderer);
    //Set transparency
    void SetAlpha(Uint8 alpha);
};


#endif