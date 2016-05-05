#include "basicfunctoins.h"
#include "potany.h"
#include "tankitato.h"
#include "magitato.h"
#include "healitato.h"
#include "epotany.h"
#include "etankitato.h"
#include "emagitato.h"
#include "ehealitato.h"
#include <cmath>
#include <iostream>
using namespace std;

void LoadImageToRenderer(std::string path, SDL_Renderer *Renderer, int x, int y)
{
    SDL_Texture *Texture=NULL;
    SDL_Surface *LoadedSurface=NULL;
    //Load the image
    LoadedSurface=IMG_Load(path.c_str());
    SDL_Rect renderquad={x, y, LoadedSurface->w, LoadedSurface->h};
    //Create texture from surface pixels
    Texture=SDL_CreateTextureFromSurface(Renderer, LoadedSurface);
    //Get rid of old loaded surface
    SDL_FreeSurface(LoadedSurface);
    //Render texture to screen
    SDL_RenderCopy(Renderer, Texture, NULL, &renderquad);
    //Free texture
    SDL_DestroyTexture(Texture);
}

void SurfaceToRenderer(SDL_Surface *image, SDL_Renderer *Renderer, int x, int y, SDL_Rect *clip, Uint8 a)
{
    int w=image->w, h=image->h;
    SDL_Texture *Texture=NULL;
    if (clip!=NULL)
    {
        w=clip->w;
        h=clip->h;
    }
    SDL_Rect renderquad={x, y, w, h};
    Texture=SDL_CreateTextureFromSurface(Renderer, image);
    SDL_SetTextureAlphaMod(Texture, a);
    SDL_RenderCopy(Renderer, Texture, clip, &renderquad);
    SDL_DestroyTexture(Texture);
}

opening::opening()
{
    SelectWhich=0;
    SelectWhichImage=7;
    gx=600;
    change=false;
    a=255;
    SelectImage[0]=IMG_Load("menuselect_0.png");
    SelectImage[1]=IMG_Load("menuselect_1.png");
    SelectImage[2]=IMG_Load("menuselect_2.png");
    SelectImage[3]=IMG_Load("menuselect_3.png");
    SelectImage[4]=IMG_Load("menuselect_4.png");
    SelectImage[5]=IMG_Load("menuselect_5.png");
    SelectImage[6]=IMG_Load("menuselect_6.png");
    SelectImage[7]=IMG_Load("menuselect_7.png");
    title=IMG_Load("title.png");
    play=IMG_Load("play.png");
    help=IMG_Load("help.png");
    quit=IMG_Load("quit.png");
    mgpotany=IMG_Load("menu_gpotany.png");
    mepotany=IMG_Load("menu_epotany.png");
    gclip={0, 0, mgpotany->w, mgpotany->h};
    eclip={0, 0, mepotany->w, mepotany->h};
}

void opening::Print(SDL_Renderer *Renderer)
{
    SurfaceToRenderer(mgpotany, Renderer, gx, 0, &gclip, 255);
    SurfaceToRenderer(mepotany, Renderer, 0, 0, NULL, 255);
    SurfaceToRenderer(title, Renderer, 225, 25, NULL, 255);
    SurfaceToRenderer(play, Renderer, 315, 160, NULL, 255);
    SurfaceToRenderer(help, Renderer, 500, 160, NULL, 255);
    SurfaceToRenderer(quit, Renderer, 405, 250, NULL, 255);
    Select(SelectWhich, Renderer);
}

void opening::Select(int s, SDL_Renderer *Renderer)
{
    if (s==0)
    {
        if (change==true)
        {
            SelectWhichImage=0;
            change=false;
        }
        SurfaceToRenderer(SelectImage[SelectWhichImage], Renderer, 320, 165, NULL, 255);
        if (SelectWhichImage!=7)
        {
            SelectWhichImage++;
            SelectWhichImage%=8;
        }
    }
    else if (s==1)
    {
        if (change==true)
        {
            SelectWhichImage=0;
            change=false;
        }
        SurfaceToRenderer(SelectImage[SelectWhichImage], Renderer, 500, 165, NULL, 255);
        if (SelectWhichImage!=7)
        {
            SelectWhichImage++;
            SelectWhichImage%=8;
        }
    }
    else if (s==2)
    {
        if (change==true)
        {
            SelectWhichImage=0;
            change=false;
        }
        SurfaceToRenderer(SelectImage[SelectWhichImage], Renderer, 410, 255, NULL, 255);
        if (SelectWhichImage!=7)
        {
            SelectWhichImage++;
            SelectWhichImage%=8;
        }
    }
}

void opening::EndPrint_FadeOut(SDL_Renderer *Renderer)
{
    a-=O_FADE_COE;
    SurfaceToRenderer(title, Renderer, 225, 25, NULL, a);
    SurfaceToRenderer(play, Renderer, 315, 160, NULL, a);
    SurfaceToRenderer(help, Renderer, 500, 160, NULL, a);
    SurfaceToRenderer(quit, Renderer, 405, 250, NULL, a);
    SurfaceToRenderer(SelectImage[SelectWhichImage], Renderer, 320, 165, NULL, a);
}

void opening::EndPrint_Move(SDL_Renderer *Renderer)
{
    gx+=O_MOVE_VEL;
    gclip.w-=O_MOVE_VEL;
    SurfaceToRenderer(mgpotany, Renderer, gx, 0, &gclip, 255);
    
    eclip.x+=O_MOVE_VEL;
    eclip.w-=O_MOVE_VEL;
    SurfaceToRenderer(mepotany, Renderer, 0, 0, &eclip, 255);
}

help::help()
{
    Select=0;
    WhichImage=0;
    M_ani_ctrl=0;
    for (int i=0;i<8;i++)
    {
        Image[0][i]=IMG_Load("help_0.png");
    }
    Image[1][0]=IMG_Load("help1_0.png");
    Image[1][1]=IMG_Load("help1_1.png");
    Image[1][2]=IMG_Load("help1_2.png");
    Image[1][3]=IMG_Load("help1_3.png");
    Image[1][4]=IMG_Load("help1_4.png");
    Image[1][5]=IMG_Load("help1_5.png");
    Image[1][6]=IMG_Load("help1_6.png");
    Image[1][7]=IMG_Load("help1_7.png");
    Image[2][0]=IMG_Load("help2_0.png");
    Image[2][1]=IMG_Load("help2_1.png");
    Image[2][2]=IMG_Load("help2_2.png");
    Image[2][3]=IMG_Load("help2_3.png");
    Image[2][4]=IMG_Load("help2_4.png");
    Image[2][5]=IMG_Load("help2_5.png");
    Image[2][6]=IMG_Load("help2_6.png");
    Image[2][7]=IMG_Load("help2_7.png");
    Image[3][0]=IMG_Load("help3_0.png");
    Image[3][1]=IMG_Load("help3_1.png");
    Image[3][2]=IMG_Load("help3_2.png");
    Image[3][3]=IMG_Load("help3_3.png");
    Image[3][4]=IMG_Load("help3_4.png");
    Image[3][5]=IMG_Load("help3_5.png");
    Image[3][6]=IMG_Load("help3_6.png");
    Image[3][7]=IMG_Load("help3_7.png");
    Image[4][0]=IMG_Load("help4_0.png");
    Image[4][1]=IMG_Load("help4_1.png");
    Image[4][2]=IMG_Load("help4_2.png");
    Image[4][3]=IMG_Load("help4_3.png");
    Image[4][4]=IMG_Load("help4_4.png");
    Image[4][5]=IMG_Load("help4_5.png");
    Image[4][6]=IMG_Load("help4_6.png");
    Image[4][7]=IMG_Load("help4_7.png");
}

void help::Print(SDL_Renderer *Renderer)
{
    SurfaceToRenderer(Image[Select][WhichImage], Renderer, 0, 0, NULL, 255);
    M_ani_ctrl++;
    if (M_ani_ctrl==7)
    {
        WhichImage++;
        M_ani_ctrl=0;
    }
    WhichImage%=8;
}

potatoqueue::potatoqueue() :gm(GMaterial_X, GMaterial_Y, 0), em(EMaterial_X, EMaterial_Y, 1), gh(SCREEN_WIDTH-200, SCREEN_HEIGHT-HOUSE_SPACE_Y-250, 0), eh(0, SCREEN_HEIGHT-HOUSE_SPACE_Y-250, 1)
{
    po[0].Image[0]=IMG_Load("gpotany_0.png");
    po[0].Image[1]=IMG_Load("gpotany_1.png");
    po[0].Image[2]=IMG_Load("gpotany_2.png");
    po[0].Image[3]=IMG_Load("gpotany_3.png");
    po[0].Image[4]=IMG_Load("gpotany_4.png");
    po[0].Image[5]=IMG_Load("gpotany_5.png");
    po[0].Image[6]=IMG_Load("gpotany_6.png");
    po[0].Image[7]=IMG_Load("gpotany_7.png");
    po[0].AttackImage[0]=IMG_Load("gp_attack_0.png");
    po[0].AttackImage[1]=IMG_Load("gp_attack_1.png");
    po[0].AttackImage[2]=IMG_Load("gp_attack_2.png");
    po[0].AttackImage[3]=IMG_Load("gp_attack_3.png");
    po[0].AttackImage[4]=IMG_Load("gp_attack_4.png");
    po[0].AttackImage[5]=IMG_Load("gp_attack_5.png");
    po[0].AttackImage[6]=IMG_Load("gp_attack_6.png");
    po[0].AttackImage[7]=IMG_Load("gp_attack_7.png");
    po[0].DeadImage[0]=IMG_Load("gp_dead_0.png");
    po[0].DeadImage[1]=IMG_Load("gp_dead_1.png");
    po[0].DeadImage[2]=IMG_Load("gp_dead_2.png");
    po[0].DeadImage[3]=IMG_Load("gp_dead_3.png");
    po[0].DeadImage[4]=IMG_Load("gp_dead_4.png");
    po[0].DeadImage[5]=IMG_Load("gp_dead_5.png");
    po[0].DeadImage[6]=IMG_Load("gp_dead_6.png");
    po[0].DeadImage[7]=IMG_Load("gp_dead_7.png");
    for (int i=1;i<NumberP;i++)
    {
        for (int j=0;j<8;j++)
        {
            po[i].Image[j]=po[0].Image[j];
            po[i].AttackImage[j]=po[0].AttackImage[j];
            po[i].DeadImage[j]=po[0].DeadImage[j];
        }
    }
    epo[0].Image[0]=IMG_Load("epotany_0.png");
    epo[0].Image[1]=IMG_Load("epotany_1.png");
    epo[0].Image[2]=IMG_Load("epotany_2.png");
    epo[0].Image[3]=IMG_Load("epotany_3.png");
    epo[0].Image[4]=IMG_Load("epotany_4.png");
    epo[0].Image[5]=IMG_Load("epotany_5.png");
    epo[0].Image[6]=IMG_Load("epotany_6.png");
    epo[0].Image[7]=IMG_Load("epotany_7.png");
    epo[0].AttackImage[0]=IMG_Load("ep_attack_0.png");
    epo[0].AttackImage[1]=IMG_Load("ep_attack_1.png");
    epo[0].AttackImage[2]=IMG_Load("ep_attack_2.png");
    epo[0].AttackImage[3]=IMG_Load("ep_attack_3.png");
    epo[0].AttackImage[4]=IMG_Load("ep_attack_4.png");
    epo[0].AttackImage[5]=IMG_Load("ep_attack_5.png");
    epo[0].AttackImage[6]=IMG_Load("ep_attack_6.png");
    epo[0].AttackImage[7]=IMG_Load("ep_attack_7.png");
    epo[0].DeadImage[0]=IMG_Load("ep_dead_0.png");
    epo[0].DeadImage[1]=IMG_Load("ep_dead_1.png");
    epo[0].DeadImage[2]=IMG_Load("ep_dead_2.png");
    epo[0].DeadImage[3]=IMG_Load("ep_dead_3.png");
    epo[0].DeadImage[4]=IMG_Load("ep_dead_4.png");
    epo[0].DeadImage[5]=IMG_Load("ep_dead_5.png");
    epo[0].DeadImage[6]=IMG_Load("ep_dead_6.png");
    epo[0].DeadImage[7]=IMG_Load("ep_dead_7.png");
    for (int i=1;i<NumberP;i++)
    {
        for (int j=0;j<8;j++)
        {
            epo[i].Image[j]=epo[0].Image[j];
            epo[i].AttackImage[j]=epo[0].AttackImage[j];
            epo[i].DeadImage[j]=epo[0].DeadImage[j];
        }
    }
    tank[0].Image[0]=IMG_Load("gtankitato_0.png");
    tank[0].Image[1]=IMG_Load("gtankitato_1.png");
    tank[0].Image[2]=IMG_Load("gtankitato_2.png");
    tank[0].Image[3]=IMG_Load("gtankitato_3.png");
    tank[0].Image[4]=IMG_Load("gtankitato_4.png");
    tank[0].Image[5]=IMG_Load("gtankitato_5.png");
    tank[0].Image[6]=IMG_Load("gtankitato_6.png");
    tank[0].Image[7]=IMG_Load("gtankitato_7.png");
    tank[0].AttackImage[0]=IMG_Load("gt_attack_0.png");
    tank[0].AttackImage[1]=IMG_Load("gt_attack_1.png");
    tank[0].AttackImage[2]=IMG_Load("gt_attack_2.png");
    tank[0].AttackImage[3]=IMG_Load("gt_attack_3.png");
    tank[0].AttackImage[4]=IMG_Load("gt_attack_4.png");
    tank[0].AttackImage[5]=IMG_Load("gt_attack_5.png");
    tank[0].AttackImage[6]=IMG_Load("gt_attack_6.png");
    tank[0].AttackImage[7]=IMG_Load("gt_attack_7.png");
    tank[0].DeadImage[0]=IMG_Load("gt_dead_0.png");
    tank[0].DeadImage[1]=IMG_Load("gt_dead_1.png");
    tank[0].DeadImage[2]=IMG_Load("gt_dead_2.png");
    tank[0].DeadImage[3]=IMG_Load("gt_dead_3.png");
    tank[0].DeadImage[4]=IMG_Load("gt_dead_4.png");
    tank[0].DeadImage[5]=IMG_Load("gt_dead_5.png");
    tank[0].DeadImage[6]=IMG_Load("gt_dead_6.png");
    tank[0].DeadImage[7]=IMG_Load("gt_dead_7.png");
    for (int i=1;i<NumberT;i++)
    {
        for (int j=0;j<8;j++)
        {
            tank[i].Image[j]=tank[0].Image[j];
            tank[i].AttackImage[j]=tank[0].AttackImage[j];
            tank[i].DeadImage[j]=tank[0].DeadImage[j];
        }
    }
    etank[0].Image[0]=IMG_Load("etankitato_0.png");
    etank[0].Image[1]=IMG_Load("etankitato_1.png");
    etank[0].Image[2]=IMG_Load("etankitato_2.png");
    etank[0].Image[3]=IMG_Load("etankitato_3.png");
    etank[0].Image[4]=IMG_Load("etankitato_4.png");
    etank[0].Image[5]=IMG_Load("etankitato_5.png");
    etank[0].Image[6]=IMG_Load("etankitato_6.png");
    etank[0].Image[7]=IMG_Load("etankitato_7.png");
    etank[0].AttackImage[0]=IMG_Load("et_attack_0.png");
    etank[0].AttackImage[1]=IMG_Load("et_attack_1.png");
    etank[0].AttackImage[2]=IMG_Load("et_attack_2.png");
    etank[0].AttackImage[3]=IMG_Load("et_attack_3.png");
    etank[0].AttackImage[4]=IMG_Load("et_attack_4.png");
    etank[0].AttackImage[5]=IMG_Load("et_attack_5.png");
    etank[0].AttackImage[6]=IMG_Load("et_attack_6.png");
    etank[0].AttackImage[7]=IMG_Load("et_attack_7.png");
    etank[0].DeadImage[0]=IMG_Load("et_dead_0.png");
    etank[0].DeadImage[1]=IMG_Load("et_dead_1.png");
    etank[0].DeadImage[2]=IMG_Load("et_dead_2.png");
    etank[0].DeadImage[3]=IMG_Load("et_dead_3.png");
    etank[0].DeadImage[4]=IMG_Load("et_dead_4.png");
    etank[0].DeadImage[5]=IMG_Load("et_dead_5.png");
    etank[0].DeadImage[6]=IMG_Load("et_dead_6.png");
    etank[0].DeadImage[7]=IMG_Load("et_dead_7.png");
    for (int i=1;i<NumberT;i++)
    {
        for (int j=0;j<8;j++)
        {
            etank[i].Image[j]=etank[0].Image[j];
            etank[i].AttackImage[j]=etank[0].AttackImage[j];
            etank[i].DeadImage[j]=etank[0].DeadImage[j];
        }
    }
    mag[0].Image[0]=IMG_Load("gmagitato_0.png");
    mag[0].Image[1]=IMG_Load("gmagitato_1.png");
    mag[0].Image[2]=IMG_Load("gmagitato_2.png");
    mag[0].Image[3]=IMG_Load("gmagitato_3.png");
    mag[0].Image[4]=IMG_Load("gmagitato_4.png");
    mag[0].Image[5]=IMG_Load("gmagitato_5.png");
    mag[0].Image[6]=IMG_Load("gmagitato_6.png");
    mag[0].Image[7]=IMG_Load("gmagitato_7.png");
    mag[0].AttackImage[0]=IMG_Load("gm_attack_0.png");
    mag[0].AttackImage[1]=IMG_Load("gm_attack_1.png");
    mag[0].AttackImage[2]=IMG_Load("gm_attack_2.png");
    mag[0].AttackImage[3]=IMG_Load("gm_attack_3.png");
    mag[0].AttackImage[4]=IMG_Load("gm_attack_4.png");
    mag[0].AttackImage[5]=IMG_Load("gm_attack_5.png");
    mag[0].AttackImage[6]=IMG_Load("gm_attack_6.png");
    mag[0].AttackImage[7]=IMG_Load("gm_attack_7.png");
    mag[0].AttackImage2[0]=IMG_Load("gm_attack2_0.png");
    mag[0].AttackImage2[1]=IMG_Load("gm_attack2_1.png");
    mag[0].AttackImage2[2]=IMG_Load("gm_attack2_2.png");
    mag[0].AttackImage2[3]=IMG_Load("gm_attack2_3.png");
    mag[0].AttackImage2[4]=IMG_Load("gm_attack2_4.png");
    mag[0].AttackImage2[5]=IMG_Load("gm_attack2_5.png");
    mag[0].AttackImage2[6]=IMG_Load("gm_attack2_6.png");
    mag[0].AttackImage2[7]=IMG_Load("gm_attack2_7.png");
    mag[0].DeadImage[0]=IMG_Load("gm_dead_0.png");
    mag[0].DeadImage[1]=IMG_Load("gm_dead_1.png");
    mag[0].DeadImage[2]=IMG_Load("gm_dead_2.png");
    mag[0].DeadImage[3]=IMG_Load("gm_dead_3.png");
    mag[0].DeadImage[4]=IMG_Load("gm_dead_4.png");
    mag[0].DeadImage[5]=IMG_Load("gm_dead_5.png");
    mag[0].DeadImage[6]=IMG_Load("gm_dead_6.png");
    mag[0].DeadImage[7]=IMG_Load("gm_dead_7.png");
    for (int i=1;i<NumberM;i++)
    {
        for (int j=0;j<8;j++)
        {
            mag[i].Image[j]=mag[0].Image[j];
            mag[i].AttackImage[j]=mag[0].AttackImage[j];
            mag[i].AttackImage2[j]=mag[0].AttackImage2[j];
            mag[i].DeadImage[j]=mag[0].DeadImage[j];
        }
    }
    emag[0].Image[0]=IMG_Load("emagitato_0.png");
    emag[0].Image[1]=IMG_Load("emagitato_1.png");
    emag[0].Image[2]=IMG_Load("emagitato_2.png");
    emag[0].Image[3]=IMG_Load("emagitato_3.png");
    emag[0].Image[4]=IMG_Load("emagitato_4.png");
    emag[0].Image[5]=IMG_Load("emagitato_5.png");
    emag[0].Image[6]=IMG_Load("emagitato_6.png");
    emag[0].Image[7]=IMG_Load("emagitato_7.png");
    emag[0].AttackImage[0]=IMG_Load("em_attack_0.png");
    emag[0].AttackImage[1]=IMG_Load("em_attack_1.png");
    emag[0].AttackImage[2]=IMG_Load("em_attack_2.png");
    emag[0].AttackImage[3]=IMG_Load("em_attack_3.png");
    emag[0].AttackImage[4]=IMG_Load("em_attack_4.png");
    emag[0].AttackImage[5]=IMG_Load("em_attack_5.png");
    emag[0].AttackImage[6]=IMG_Load("em_attack_6.png");
    emag[0].AttackImage[7]=IMG_Load("em_attack_7.png");
    emag[0].AttackImage2[0]=IMG_Load("em_attack2_0.png");
    emag[0].AttackImage2[1]=IMG_Load("em_attack2_1.png");
    emag[0].AttackImage2[2]=IMG_Load("em_attack2_2.png");
    emag[0].AttackImage2[3]=IMG_Load("em_attack2_3.png");
    emag[0].AttackImage2[4]=IMG_Load("em_attack2_4.png");
    emag[0].AttackImage2[5]=IMG_Load("em_attack2_5.png");
    emag[0].AttackImage2[6]=IMG_Load("em_attack2_6.png");
    emag[0].AttackImage2[7]=IMG_Load("em_attack2_7.png");
    emag[0].DeadImage[0]=IMG_Load("em_dead_0.png");
    emag[0].DeadImage[1]=IMG_Load("em_dead_1.png");
    emag[0].DeadImage[2]=IMG_Load("em_dead_2.png");
    emag[0].DeadImage[3]=IMG_Load("em_dead_3.png");
    emag[0].DeadImage[4]=IMG_Load("em_dead_4.png");
    emag[0].DeadImage[5]=IMG_Load("em_dead_5.png");
    emag[0].DeadImage[6]=IMG_Load("em_dead_6.png");
    emag[0].DeadImage[7]=IMG_Load("em_dead_7.png");
    for (int i=1;i<NumberM;i++)
    {
        for (int j=0;j<8;j++)
        {
            emag[i].Image[j]=emag[0].Image[j];
            emag[i].AttackImage[j]=emag[0].AttackImage[j];
            emag[i].AttackImage2[j]=emag[0].AttackImage2[j];
            emag[i].DeadImage[j]=emag[0].DeadImage[j];
        }
    }
    heal[0].Image[0]=IMG_Load("ghealitato_0.png");
    heal[0].Image[1]=IMG_Load("ghealitato_1.png");
    heal[0].Image[2]=IMG_Load("ghealitato_2.png");
    heal[0].Image[3]=IMG_Load("ghealitato_3.png");
    heal[0].Image[4]=IMG_Load("ghealitato_4.png");
    heal[0].Image[5]=IMG_Load("ghealitato_5.png");
    heal[0].Image[6]=IMG_Load("ghealitato_6.png");
    heal[0].Image[7]=IMG_Load("ghealitato_7.png");
    heal[0].AttackImage[0]=IMG_Load("gh_attack_0.png");
    heal[0].AttackImage[1]=IMG_Load("gh_attack_1.png");
    heal[0].AttackImage[2]=IMG_Load("gh_attack_2.png");
    heal[0].AttackImage[3]=IMG_Load("gh_attack_3.png");
    heal[0].AttackImage[4]=IMG_Load("gh_attack_4.png");
    heal[0].AttackImage[5]=IMG_Load("gh_attack_5.png");
    heal[0].AttackImage[6]=IMG_Load("gh_attack_6.png");
    heal[0].AttackImage[7]=IMG_Load("gh_attack_7.png");
    heal[0].AttackImage2[0]=IMG_Load("gh_attack2_0.png");
    heal[0].AttackImage2[1]=IMG_Load("gh_attack2_1.png");
    heal[0].AttackImage2[2]=IMG_Load("gh_attack2_2.png");
    heal[0].AttackImage2[3]=IMG_Load("gh_attack2_3.png");
    heal[0].AttackImage2[4]=IMG_Load("gh_attack2_4.png");
    heal[0].AttackImage2[5]=IMG_Load("gh_attack2_5.png");
    heal[0].AttackImage2[6]=IMG_Load("gh_attack2_6.png");
    heal[0].AttackImage2[7]=IMG_Load("gh_attack2_7.png");
    heal[0].DeadImage[0]=IMG_Load("gh_dead_0.png");
    heal[0].DeadImage[1]=IMG_Load("gh_dead_1.png");
    heal[0].DeadImage[2]=IMG_Load("gh_dead_2.png");
    heal[0].DeadImage[3]=IMG_Load("gh_dead_3.png");
    heal[0].DeadImage[4]=IMG_Load("gh_dead_4.png");
    heal[0].DeadImage[5]=IMG_Load("gh_dead_5.png");
    heal[0].DeadImage[6]=IMG_Load("gh_dead_6.png");
    heal[0].DeadImage[7]=IMG_Load("gh_dead_7.png");
    for (int i=1;i<NumberH;i++)
    {
        for (int j=0;j<8;j++)
        {
            heal[i].Image[j]=heal[0].Image[j];
            heal[i].AttackImage[j]=heal[0].AttackImage[j];
            heal[i].AttackImage2[j]=heal[0].AttackImage2[j];
            heal[i].DeadImage[j]=heal[0].DeadImage[j];
        }
    }
    eheal[0].Image[0]=IMG_Load("ehealitato_0.png");
    eheal[0].Image[1]=IMG_Load("ehealitato_1.png");
    eheal[0].Image[2]=IMG_Load("ehealitato_2.png");
    eheal[0].Image[3]=IMG_Load("ehealitato_3.png");
    eheal[0].Image[4]=IMG_Load("ehealitato_4.png");
    eheal[0].Image[5]=IMG_Load("ehealitato_5.png");
    eheal[0].Image[6]=IMG_Load("ehealitato_6.png");
    eheal[0].Image[7]=IMG_Load("ehealitato_7.png");
    eheal[0].AttackImage[0]=IMG_Load("eh_attack_0.png");
    eheal[0].AttackImage[1]=IMG_Load("eh_attack_1.png");
    eheal[0].AttackImage[2]=IMG_Load("eh_attack_2.png");
    eheal[0].AttackImage[3]=IMG_Load("eh_attack_3.png");
    eheal[0].AttackImage[4]=IMG_Load("eh_attack_4.png");
    eheal[0].AttackImage[5]=IMG_Load("eh_attack_5.png");
    eheal[0].AttackImage[6]=IMG_Load("eh_attack_6.png");
    eheal[0].AttackImage[7]=IMG_Load("eh_attack_7.png");
    eheal[0].AttackImage2[0]=IMG_Load("eh_attack2_0.png");
    eheal[0].AttackImage2[1]=IMG_Load("eh_attack2_1.png");
    eheal[0].AttackImage2[2]=IMG_Load("eh_attack2_2.png");
    eheal[0].AttackImage2[3]=IMG_Load("eh_attack2_3.png");
    eheal[0].AttackImage2[4]=IMG_Load("eh_attack2_4.png");
    eheal[0].AttackImage2[5]=IMG_Load("eh_attack2_5.png");
    eheal[0].AttackImage2[6]=IMG_Load("eh_attack2_6.png");
    eheal[0].AttackImage2[7]=IMG_Load("eh_attack2_7.png");
    eheal[0].DeadImage[0]=IMG_Load("eh_dead_0.png");
    eheal[0].DeadImage[1]=IMG_Load("eh_dead_1.png");
    eheal[0].DeadImage[2]=IMG_Load("eh_dead_2.png");
    eheal[0].DeadImage[3]=IMG_Load("eh_dead_3.png");
    eheal[0].DeadImage[4]=IMG_Load("eh_dead_4.png");
    eheal[0].DeadImage[5]=IMG_Load("eh_dead_5.png");
    eheal[0].DeadImage[6]=IMG_Load("eh_dead_6.png");
    eheal[0].DeadImage[7]=IMG_Load("eh_dead_7.png");
    for (int i=1;i<NumberH;i++)
    {
        for (int j=0;j<8;j++)
        {
            eheal[i].Image[j]=eheal[0].Image[j];
            eheal[i].AttackImage[j]=eheal[0].AttackImage[j];
            eheal[i].AttackImage2[j]=eheal[0].AttackImage2[j];
            eheal[i].DeadImage[j]=eheal[0].DeadImage[j];
        }
    }
}

void potatoqueue::Print(SDL_Renderer *Renderer)
{
    //don't change the order of the same kind of potatoes
    for (int i=m_c;i>=m_f;i--)
    {
        if (mag[i].hp>0 && mag[i].a==255 && (mag[i].x>(SPACE_X+mag[i].GetWidth()-1)))
        {
            if (CheckCollision(G_Magitato, i))
            {
                mag[i].collision=1;
                if (mag[i].AWhichImage==7 && mag[i].GetAAni()==(AtkA_Vel-1))
                {
                    switch(CollisionWithE(G_Magitato, i))
                    {
                        case E_Potany:
                            epo[ep_f].injury+=mag[i].atk;
                            break;
                        case E_Tankitato:
                            etank[et_f].injury+=mag[i].atk;
                            break;
                        case E_Magitato:
                            emag[em_f].injury+=mag[i].atk;
                            break;
                        case E_Healitato:
                            eheal[eh_f].injury+=mag[i].atk;
                            break;
                    }
                }
            }
            else
                mag[i].collision=0;
        }
        else
            mag[i].collision=0;
        /*if (mag[i].hp<=0 && mag[i].DWhichImage==8)
         {
         Pop(G_Magitato);
         mag[i].free();
         continue;
         }*/
        if ((mag[i].x==SPACE_X || mag[i].DWhichImage==8) && mag[i].a==0)
        {
            if (mag[i].x==SPACE_X)
            {
                if ((eh.hp-DamageM)<=0)
                    eh.hp=0;
                else
                    eh.hp-=DamageM;
            }
            Pop(G_Magitato);
            continue;
        }
        mag[i].ChooseStage(Renderer);
    }
    for (int i=em_c;i>=em_f;i--)
    {
        if (emag[i].hp>0 && emag[i].a==255 && ((emag[i].x+emag[i].GetWidth())<(SCREEN_WIDTH-SPACE_X-emag[i].GetWidth()+1)))
        {
            if (CheckCollision(E_Magitato, i))
            {
                emag[i].collision=1;
                if (emag[i].AWhichImage==7 && emag[i].GetAAni()==(AtkA_Vel-1))
                {
                    switch(CollisionWithG(E_Magitato, i))
                    {
                        case G_Potany:
                            po[p_f].injury+=emag[i].atk;
                            break;
                        case G_Tankitato:
                            tank[t_f].injury+=emag[i].atk;
                            break;
                        case G_Magitato:
                            mag[m_f].injury+=emag[i].atk;
                            break;
                        case G_Healitato:
                            heal[h_f].injury+=emag[i].atk;
                            break;
                    }
                }
            }
            else
                emag[i].collision=0;
        }
        else
            emag[i].collision=0;
        /*if (emag[i].hp<=0 && emag[i].DWhichImage==8)
         {
         Pop(E_Magitato);
         emag[i].free();
         continue;
         }*/
        if ((emag[i].x==(SCREEN_WIDTH-SPACE_X-emag[i].GetWidth()) || emag[i].DWhichImage==8) && emag[i].a==0)
        {
            if (emag[i].x==(SCREEN_WIDTH-SPACE_X-emag[i].GetWidth()))
            {
                if ((gh.hp-DamageM)<=0)
                    gh.hp=0;
                else
                    gh.hp-=DamageM;
            }
            Pop(E_Magitato);
            continue;
        }
        emag[i].ChooseStage(Renderer);
    }
    if (CollisionWithG(E_Magitato, em_f)==G_Magitato)
    {
        for (int i=em_c;i>=em_f;i--)
        {
            if (emag[i].collision==1)
                emag[i].Attack2(Renderer);
        }
    }
    if (CollisionWithE(G_Magitato, m_f)==E_Magitato)
    {
        for (int i=m_c;i>=m_f;i--)
        {
            if (mag[i].collision==1)
                mag[i].Attack2(Renderer);
        }
    }
    for (int i=t_c;i>=t_f;i--)
    {
        if (tank[i].hp>0 && tank[i].a==255 && (tank[i].x>(SPACE_X+100-1)))
        {
            if (CheckCollision(G_Tankitato, i))
            {
                tank[i].collision=1;
                if (tank[i].AWhichImage==7 && tank[i].GetAAni()==(AtkA_Vel-1))
                {
                    switch(CollisionWithE(G_Tankitato, i))
                    {
                        case E_Potany:
                            epo[ep_f].injury+=tank[i].atk;
                            break;
                        case E_Tankitato:
                            etank[et_f].injury+=tank[i].atk;
                            break;
                        case E_Magitato:
                            emag[em_f].injury+=tank[i].atk;
                            break;
                        case E_Healitato:
                            eheal[eh_f].injury+=tank[i].atk;
                            break;
                    }
                }
            }
            else
                tank[i].collision=0;
        }
        else
            tank[i].collision=0;
        /*if (tank[i].hp<=0 && tank[i].DWhichImage==8)
        {
            Pop(G_Tankitato);
            tank[i].free();
            continue;
        }*/
        if ((tank[i].x==SPACE_X || tank[i].DWhichImage==8) && tank[i].a==0)
        {
            if (tank[i].x==SPACE_X)
            {
                if ((eh.hp-DamageT)<=0)
                    eh.hp=0;
                else
                    eh.hp-=DamageT;
            }
            Pop(G_Tankitato);
            continue;
        }
        tank[i].ChooseStage(Renderer);
    }
    if (CollisionWithG(E_Magitato, em_f)==G_Tankitato)
    {
        for (int i=em_c;i>=em_f;i--)
        {
            if (emag[i].collision==1)
                emag[i].Attack2(Renderer);
        }
    }
    for (int i=et_c;i>=et_f;i--)
    {
        if (etank[i].hp>0 && etank[i].a==255 && ((etank[i].x+etank[i].GetWidth())<(SCREEN_WIDTH-SPACE_X-100+1)))
        {
            if (CheckCollision(E_Tankitato, i))
            {
                etank[i].collision=1;
                if (etank[i].AWhichImage==7 && etank[i].GetAAni()==(AtkA_Vel-1))
                {
                    switch(CollisionWithG(E_Tankitato, i))
                    {
                        case G_Potany:
                            po[p_f].injury+=etank[i].atk;
                            break;
                        case G_Tankitato:
                            tank[t_f].injury+=etank[i].atk;
                            break;
                        case G_Magitato:
                            mag[m_f].injury+=etank[i].atk;
                            break;
                        case G_Healitato:
                            heal[h_f].injury+=etank[i].atk;
                            break;
                    }
                }
            }
            else
                etank[i].collision=0;
        }
        else
            etank[i].collision=0;
        /*if (etank[i].hp<=0 && etank[i].DWhichImage==8)
        {
            Pop(E_Tankitato);
            etank[i].free();
            continue;
        }*/
        if ((etank[i].x==(SCREEN_WIDTH-SPACE_X-etank[i].GetWidth()) || etank[i].DWhichImage==8) && etank[i].a==0)
        {
            if (etank[i].x==(SCREEN_WIDTH-SPACE_X-etank[i].GetWidth()))
            {
                if ((gh.hp-DamageT)<=0)
                    gh.hp=0;
                else
                    gh.hp-=DamageT;
            }
            Pop(E_Tankitato);
            continue;
        }
        etank[i].ChooseStage(Renderer);
    }
    if (CollisionWithE(G_Magitato, m_f)==E_Tankitato)
    {
        for (int i=m_c;i>=m_f;i--)
        {
            if (mag[i].collision==1)
                mag[i].Attack2(Renderer);
        }
    }
    for (int i=h_c;i>=h_f;i--)
    {
        if (heal[i].hp>0 && heal[i].a==255 && (heal[i].x>(SPACE_X+heal[i].GetWidth()-1)))
        {
            if (CheckCollision(G_Healitato, i))
            {
                heal[i].collision=1;
                if (heal[i].AWhichImage==7 && heal[i].GetAAni()==(AtkA_Vel-1))
                {
                    switch(CollisionWithE(G_Healitato, i))
                    {
                        case G_Potany:
                            po[ep_f].injury-=heal[i].atk;
                            break;
                        case G_Tankitato:
                            tank[et_f].injury-=heal[i].atk;
                            break;
                        case G_Magitato:
                            mag[em_f].injury-=heal[i].atk;
                            break;
                        case G_Healitato:
                            heal[eh_f].injury-=heal[i].atk;
                            break;
                    }
                }
            }
            else
                heal[i].collision=0;
        }
        else
            heal[i].collision=0;
        /*if (heal[i].hp<=0 && heal[i].DWhichImage==8)
        {
            Pop(G_Healitato);
            heal[i].free();
            continue;
        }*/
        if ((heal[i].x==SPACE_X || heal[i].DWhichImage==8) && heal[i].a==0)
        {
            if (heal[i].x==SPACE_X)
            {
                if ((eh.hp-DamageH)<=0)
                    eh.hp=0;
                else
                    eh.hp-=DamageH;
            }
            Pop(G_Healitato);
            continue;
        }
        heal[i].ChooseStage(Renderer);
    }
    if (CollisionWithG(E_Magitato, em_f)==G_Healitato)
    {
        for (int i=em_c;i>=em_f;i--)
        {
            if (emag[i].collision==1)
                emag[i].Attack2(Renderer);
        }
    }
    for (int i=eh_c;i>=eh_f;i--)
    {
        if (eheal[i].hp>0 && eheal[i].a==255 && ((eheal[i].x+eheal[i].GetWidth())<(SCREEN_WIDTH-SPACE_X-eheal[i].GetWidth()+1)))
        {
            if (CheckCollision(E_Healitato, i))
            {
                eheal[i].collision=1;
                if (eheal[i].AWhichImage==7 && eheal[i].GetAAni()==(AtkA_Vel-1))
                {
                    switch(CollisionWithG(E_Healitato, i))
                    {
                        case E_Potany:
                            epo[p_f].injury-=eheal[i].atk;
                            break;
                        case E_Tankitato:
                            etank[t_f].injury-=eheal[i].atk;
                            break;
                        case E_Magitato:
                            emag[m_f].injury-=eheal[i].atk;
                            break;
                        case E_Healitato:
                            eheal[h_f].injury-=eheal[i].atk;
                            break;
                    }
                }
            }
            else
                eheal[i].collision=0;
        }
        else
            eheal[i].collision=0;
        /*if (eheal[i].hp<=0 && eheal[i].DWhichImage==8)
        {
            Pop(E_Healitato);
            eheal[i].free();
            continue;
        }*/
        if ((eheal[i].x==(SCREEN_WIDTH-SPACE_X-eheal[i].GetWidth()) || eheal[i].DWhichImage==8) && eheal[i].a==0)
        {
            if (eheal[i].x==(SCREEN_WIDTH-SPACE_X-eheal[i].GetWidth()))
            {
                if ((gh.hp-DamageH)<=0)
                    gh.hp=0;
                else
                    gh.hp-=DamageH;
            }
            Pop(E_Healitato);
            continue;
        }
        eheal[i].ChooseStage(Renderer);
    }
    if (CollisionWithE(G_Magitato, m_f)==E_Healitato)
    {
        for (int i=m_c;i>=m_f;i--)
        {
            if (mag[i].collision==1)
                mag[i].Attack2(Renderer);
        }
    }
    for (int i=p_c;i>=p_f;i--)
    {
        if (po[i].hp>0 && po[i].a==255 && (po[i].x>(SPACE_X+po[i].GetWidth()-1)))
        {
            if (CheckCollision(G_Potany, i))
            {
                po[i].collision=1;
                if (po[i].AWhichImage==7 && po[i].GetAAni()==(AtkA_Vel-1))
                {
                    switch(CollisionWithE(G_Potany, i))
                    {
                        case E_Potany:
                            epo[ep_f].injury+=po[i].atk;
                            break;
                        case E_Tankitato:
                            etank[et_f].injury+=po[i].atk;
                            break;
                        case E_Magitato:
                            emag[em_f].injury+=po[i].atk;
                            break;
                        case E_Healitato:
                            eheal[eh_f].injury+=po[i].atk;
                            break;
                    }
                }
            }
            else
                po[i].collision=0;
        }
        else
            po[i].collision=0;
        /*if (po[i].hp<=0 && po[i].DWhichImage==8)
        {
            Pop(G_Potany);
            po[i].free();
            continue;
        }*/
        if ((po[i].x==SPACE_X || po[i].DWhichImage==8) && po[i].a==0)
        {
            if (po[i].x==SPACE_X)
            {
                if ((eh.hp-DamageP)<=0)
                    eh.hp=0;
                else
                    eh.hp-=DamageP;
            }
            Pop(G_Potany);
            continue;
        }
        po[i].ChooseStage(Renderer);
    }
    if (CollisionWithG(E_Magitato, em_f)==G_Potany)
    {
        for (int i=em_c;i>=em_f;i--)
        {
            if (emag[i].collision==1)
                emag[i].Attack2(Renderer);
        }
    }
    for (int i=ep_c;i>=ep_f;i--)
    {
        if (epo[i].hp>0 && epo[i].a==255 && ((epo[i].x+epo[i].GetWidth())<(SCREEN_WIDTH-SPACE_X-epo[i].GetWidth()+1)))
        {
            if (CheckCollision(E_Potany, i))
            {
                epo[i].collision=1;
                if (epo[i].AWhichImage==7 && epo[i].GetAAni()==(AtkA_Vel-1))
                {
                    switch(CollisionWithG(E_Potany, i))
                    {
                        case G_Potany:
                            po[p_f].injury+=epo[i].atk;
                            break;
                        case G_Tankitato:
                            tank[t_f].injury+=epo[i].atk;
                            break;
                        case G_Magitato:
                            mag[m_f].injury+=epo[i].atk;
                            break;
                        case G_Healitato:
                            heal[h_f].injury+=epo[i].atk;
                            break;
                    }
                }
            }
            else
                epo[i].collision=0;
        }
        else
            epo[i].collision=0;
        /*if (epo[i].hp<=0 && epo[i].DWhichImage==8)
        {
            Pop(E_Potany);
            epo[i].free();
            continue;
        }*/
        if ((epo[i].x==(SCREEN_WIDTH-SPACE_X-epo[i].GetWidth()) || epo[i].DWhichImage==8)&& epo[i].a==0)
        {
            if (epo[i].x==(SCREEN_WIDTH-SPACE_X-epo[i].GetWidth()))
            {
                if ((gh.hp-DamageP)<=0)
                    gh.hp=0;
                else
                    gh.hp-=DamageP;
            }
            Pop(E_Potany);
            continue;
        }
        epo[i].ChooseStage(Renderer);
    }
    if (CollisionWithE(G_Magitato, m_f)==E_Potany)
    {
        for (int i=m_c;i>=m_f;i--)
        {
            if (mag[i].collision==1)
                mag[i].Attack2(Renderer);
        }
    }

    //Attack2
    for (int i=h_c;i>=h_f;i--)
    {
        if (heal[i].collision==1)
        {
            //adjust attack_x&y
            //CollisionWithE(G_Healitato, i);
            heal[i].Attack2(Renderer);
        }
    }
    for (int i=eh_c;i>=eh_f;i--)
    {
        if (eheal[i].collision==1)
        {
            //CollisionWithG(E_Healitato, i);
            eheal[i].Attack2(Renderer);
        }
    }
    
    for (int i=p_f;i<=p_c;i++)
    {
        po[i].hp-=po[i].injury;
        po[i].injury=0;
    }
    for (int i=ep_f;i<=ep_c;i++)
    {
        epo[i].hp-=epo[i].injury;
        epo[i].injury=0;
    }
    for (int i=t_f;i<=t_c;i++)
    {
        tank[i].hp-=tank[i].injury;
        tank[i].injury=0;
    }
    for (int i=et_f;i<=et_c;i++)
    {
        etank[i].hp-=etank[i].injury;
        etank[i].injury=0;
    }
    for (int i=m_f;i<=m_c;i++)
    {
        mag[i].hp-=mag[i].injury;
        mag[i].injury=0;
    }
    for (int i=em_f;i<=em_c;i++)
    {
        emag[i].hp-=emag[i].injury;
        emag[i].injury=0;
    }
    for (int i=h_f;i<=h_c;i++)
    {
        heal[i].hp-=heal[i].injury;
        heal[i].injury=0;
    }
    for (int i=eh_f;i<=eh_c;i++)
    {
        eheal[i].hp-=eheal[i].injury;
        eheal[i].injury=0;
    }
}

void potatoqueue::EndPrint(SDL_Renderer *Renderer)
{
    if (gh.hp==0)
    {
        for (int i=m_c;i>=m_f;i--)
        {
            if (mag[i].hp>0 && mag[i].a==255 && (mag[i].x>(SPACE_X+mag[i].GetWidth()-1)))
            {
                if (CheckCollision(G_Magitato, i))
                {
                    mag[i].collision=1;
                    if (mag[i].AWhichImage==7 && mag[i].GetAAni()==(AtkA_Vel-1))
                    {
                        switch(CollisionWithE(G_Magitato, i))
                        {
                            case E_Potany:
                                epo[ep_f].injury+=mag[i].atk;
                                break;
                            case E_Tankitato:
                                etank[et_f].injury+=mag[i].atk;
                                break;
                            case E_Magitato:
                                emag[em_f].injury+=mag[i].atk;
                                break;
                            case E_Healitato:
                                eheal[eh_f].injury+=mag[i].atk;
                                break;
                        }
                    }
                }
                else
                    mag[i].collision=0;
                    }
            else
                mag[i].collision=0;
            /*if (mag[i].hp<=0 && mag[i].DWhichImage==8)
             {
             Pop(G_Magitato);
             mag[i].free();
             continue;
             }*/
                if ((mag[i].x==SPACE_X || mag[i].DWhichImage==8) && mag[i].a==0)
                {
                    if (mag[i].x==SPACE_X)
                    {
                        if ((eh.hp-DamageM)<=0)
                            eh.hp=0;
                            else
                                eh.hp-=DamageM;
                                }
                    Pop(G_Magitato);
                    continue;
                }
            mag[i].ChooseStage(Renderer);
        }
        for (int i=t_c;i>=t_f;i--)
        {
            if (tank[i].hp>0 && tank[i].a==255 && (tank[i].x>(SPACE_X+100-1)))
            {
                if (CheckCollision(G_Tankitato, i))
                {
                    tank[i].collision=1;
                    if (tank[i].AWhichImage==7 && tank[i].GetAAni()==(AtkA_Vel-1))
                    {
                        switch(CollisionWithE(G_Tankitato, i))
                        {
                            case E_Potany:
                                epo[ep_f].injury+=tank[i].atk;
                                break;
                            case E_Tankitato:
                                etank[et_f].injury+=tank[i].atk;
                                break;
                            case E_Magitato:
                                emag[em_f].injury+=tank[i].atk;
                                break;
                            case E_Healitato:
                                eheal[eh_f].injury+=tank[i].atk;
                                break;
                        }
                    }
                }
                else
                    tank[i].collision=0;
                    }
            else
                tank[i].collision=0;
            /*if (tank[i].hp<=0 && tank[i].DWhichImage==8)
             {
             Pop(G_Tankitato);
             tank[i].free();
             continue;
             }*/
                if ((tank[i].x==SPACE_X || tank[i].DWhichImage==8) && tank[i].a==0)
                {
                    if (tank[i].x==SPACE_X)
                    {
                        if ((eh.hp-DamageT)<=0)
                            eh.hp=0;
                            else
                                eh.hp-=DamageT;
                                }
                    Pop(G_Tankitato);
                    continue;
                }
            tank[i].ChooseStage(Renderer);
        }
        for (int i=h_c;i>=h_f;i--)
        {
            if (heal[i].hp>0 && heal[i].a==255 && (heal[i].x>(SPACE_X+heal[i].GetWidth()-1)))
            {
                if (CheckCollision(G_Healitato, i))
                {
                    heal[i].collision=1;
                    if (heal[i].AWhichImage==7 && heal[i].GetAAni()==(AtkA_Vel-1))
                    {
                        switch(CollisionWithE(G_Healitato, i))
                        {
                            case G_Potany:
                                po[ep_f].injury-=heal[i].atk;
                                break;
                            case G_Tankitato:
                                tank[et_f].injury-=heal[i].atk;
                                break;
                            case G_Magitato:
                                mag[em_f].injury-=heal[i].atk;
                                break;
                            case G_Healitato:
                                heal[eh_f].injury-=heal[i].atk;
                                break;
                        }
                    }
                }
                else
                    heal[i].collision=0;
                    }
            else
                heal[i].collision=0;
            /*if (heal[i].hp<=0 && heal[i].DWhichImage==8)
             {
             Pop(G_Healitato);
             heal[i].free();
             continue;
             }*/
                if ((heal[i].x==SPACE_X || heal[i].DWhichImage==8) && heal[i].a==0)
                {
                    if (heal[i].x==SPACE_X)
                    {
                        if ((eh.hp-DamageH)<=0)
                            eh.hp=0;
                            else
                                eh.hp-=DamageH;
                                }
                    Pop(G_Healitato);
                    continue;
                }
            heal[i].ChooseStage(Renderer);
        }
        for (int i=p_c;i>=p_f;i--)
        {
            if (po[i].hp>0 && po[i].a==255 && (po[i].x>(SPACE_X+po[i].GetWidth()-1)))
            {
                if (CheckCollision(G_Potany, i))
                {
                    po[i].collision=1;
                    if (po[i].AWhichImage==7 && po[i].GetAAni()==(AtkA_Vel-1))
                    {
                        switch(CollisionWithE(G_Potany, i))
                        {
                            case E_Potany:
                                epo[ep_f].injury+=po[i].atk;
                                break;
                            case E_Tankitato:
                                etank[et_f].injury+=po[i].atk;
                                break;
                            case E_Magitato:
                                emag[em_f].injury+=po[i].atk;
                                break;
                            case E_Healitato:
                                eheal[eh_f].injury+=po[i].atk;
                                break;
                        }
                    }
                }
                else
                    po[i].collision=0;
                    }
            else
                po[i].collision=0;
            /*if (po[i].hp<=0 && po[i].DWhichImage==8)
             {
             Pop(G_Potany);
             po[i].free();
             continue;
             }*/
                if ((po[i].x==SPACE_X || po[i].DWhichImage==8) && po[i].a==0)
                {
                    if (po[i].x==SPACE_X)
                    {
                        if ((eh.hp-DamageP)<=0)
                            eh.hp=0;
                            else
                                eh.hp-=DamageP;
                                }
                    Pop(G_Potany);
                    continue;
                }
            po[i].ChooseStage(Renderer);
        }
        
        for (int i=m_c;i>=m_f;i--)
        {
            if (mag[i].collision==1)
                mag[i].Attack2(Renderer);
        }
        for (int i=h_c;i>=h_f;i--)
        {
            if (heal[i].collision==1)
            {
                //adjust attack_x&y
                //CollisionWithE(G_Healitato, i);
                heal[i].Attack2(Renderer);
            }
        }
        
        LoadImageToRenderer("e_victory.png", Renderer, 0, 0);
        LoadImageToRenderer("victory.png", Renderer, 0, 0);
        
        for (int i=em_c;i>=em_f;i--)
        {
            if (emag[i].hp>0 && emag[i].a==255 && ((emag[i].x+emag[i].GetWidth())<(SCREEN_WIDTH-SPACE_X-emag[i].GetWidth()+1)))
            {
                if (CheckCollision(E_Magitato, i))
                {
                    emag[i].collision=1;
                    if (emag[i].AWhichImage==7 && emag[i].GetAAni()==(AtkA_Vel-1))
                    {
                        switch(CollisionWithG(E_Magitato, i))
                        {
                            case G_Potany:
                                po[p_f].injury+=emag[i].atk;
                                break;
                            case G_Tankitato:
                                tank[t_f].injury+=emag[i].atk;
                                break;
                            case G_Magitato:
                                mag[m_f].injury+=emag[i].atk;
                                break;
                            case G_Healitato:
                                heal[h_f].injury+=emag[i].atk;
                                break;
                        }
                    }
                }
                else
                    emag[i].collision=0;
            }
            else
                emag[i].collision=0;
            /*if (emag[i].hp<=0 && emag[i].DWhichImage==8)
             {
             Pop(E_Magitato);
             emag[i].free();
             continue;
             }*/
            if ((emag[i].x==(SCREEN_WIDTH-SPACE_X-emag[i].GetWidth()) || emag[i].DWhichImage==8) && emag[i].a==0)
            {
                if (emag[i].x==(SCREEN_WIDTH-SPACE_X-emag[i].GetWidth()))
                {
                    if ((gh.hp-DamageM)<=0)
                        gh.hp=0;
                    else
                        gh.hp-=DamageM;
                }
                Pop(E_Magitato);
                continue;
            }
            emag[i].ChooseStage(Renderer);
        }
        for (int i=et_c;i>=et_f;i--)
        {
            if (etank[i].hp>0 && etank[i].a==255 && ((etank[i].x+etank[i].GetWidth())<(SCREEN_WIDTH-SPACE_X-100+1)))
            {
                if (CheckCollision(E_Tankitato, i))
                {
                    etank[i].collision=1;
                    if (etank[i].AWhichImage==7 && etank[i].GetAAni()==(AtkA_Vel-1))
                    {
                        switch(CollisionWithG(E_Tankitato, i))
                        {
                            case G_Potany:
                                po[p_f].injury+=etank[i].atk;
                                break;
                            case G_Tankitato:
                                tank[t_f].injury+=etank[i].atk;
                                break;
                            case G_Magitato:
                                mag[m_f].injury+=etank[i].atk;
                                break;
                            case G_Healitato:
                                heal[h_f].injury+=etank[i].atk;
                                break;
                        }
                    }
                }
                else
                    etank[i].collision=0;
            }
            else
                etank[i].collision=0;
            /*if (etank[i].hp<=0 && etank[i].DWhichImage==8)
             {
             Pop(E_Tankitato);
             etank[i].free();
             continue;
             }*/
            if ((etank[i].x==(SCREEN_WIDTH-SPACE_X-etank[i].GetWidth()) || etank[i].DWhichImage==8) && etank[i].a==0)
            {
                if (etank[i].x==(SCREEN_WIDTH-SPACE_X-etank[i].GetWidth()))
                {
                    if ((gh.hp-DamageT)<=0)
                        gh.hp=0;
                    else
                        gh.hp-=DamageT;
                }
                Pop(E_Tankitato);
                continue;
            }
            etank[i].ChooseStage(Renderer);
        }
        for (int i=eh_c;i>=eh_f;i--)
        {
            if (eheal[i].hp>0 && eheal[i].a==255 && ((eheal[i].x+eheal[i].GetWidth())<(SCREEN_WIDTH-SPACE_X-eheal[i].GetWidth()+1)))
            {
                if (CheckCollision(E_Healitato, i))
                {
                    eheal[i].collision=1;
                    if (eheal[i].AWhichImage==7 && eheal[i].GetAAni()==(AtkA_Vel-1))
                    {
                        switch(CollisionWithG(E_Healitato, i))
                        {
                            case E_Potany:
                                epo[p_f].injury-=eheal[i].atk;
                                break;
                            case E_Tankitato:
                                etank[t_f].injury-=eheal[i].atk;
                                break;
                            case E_Magitato:
                                emag[m_f].injury-=eheal[i].atk;
                                break;
                            case E_Healitato:
                                eheal[h_f].injury-=eheal[i].atk;
                                break;
                        }
                    }
                }
                else
                    eheal[i].collision=0;
            }
            else
                eheal[i].collision=0;
            /*if (eheal[i].hp<=0 && eheal[i].DWhichImage==8)
             {
             Pop(E_Healitato);
             eheal[i].free();
             continue;
             }*/
            if ((eheal[i].x==(SCREEN_WIDTH-SPACE_X-eheal[i].GetWidth()) || eheal[i].DWhichImage==8) && eheal[i].a==0)
            {
                if (eheal[i].x==(SCREEN_WIDTH-SPACE_X-eheal[i].GetWidth()))
                {
                    if ((gh.hp-DamageH)<=0)
                        gh.hp=0;
                    else
                        gh.hp-=DamageH;
                }
                Pop(E_Healitato);
                continue;
            }
            eheal[i].ChooseStage(Renderer);
        }
        for (int i=ep_c;i>=ep_f;i--)
        {
            if (epo[i].hp>0 && epo[i].a==255 && ((epo[i].x+epo[i].GetWidth())<(SCREEN_WIDTH-SPACE_X-epo[i].GetWidth()+1)))
            {
                if (CheckCollision(E_Potany, i))
                {
                    epo[i].collision=1;
                    if (epo[i].AWhichImage==7 && epo[i].GetAAni()==(AtkA_Vel-1))
                    {
                        switch(CollisionWithG(E_Potany, i))
                        {
                            case G_Potany:
                                po[p_f].injury+=epo[i].atk;
                                break;
                            case G_Tankitato:
                                tank[t_f].injury+=epo[i].atk;
                                break;
                            case G_Magitato:
                                mag[m_f].injury+=epo[i].atk;
                                break;
                            case G_Healitato:
                                heal[h_f].injury+=epo[i].atk;
                                break;
                        }
                    }
                }
                else
                    epo[i].collision=0;
            }
            else
                epo[i].collision=0;
            /*if (epo[i].hp<=0 && epo[i].DWhichImage==8)
             {
             Pop(E_Potany);
             epo[i].free();
             continue;
             }*/
            if ((epo[i].x==(SCREEN_WIDTH-SPACE_X-epo[i].GetWidth()) || epo[i].DWhichImage==8)&& epo[i].a==0)
            {
                if (epo[i].x==(SCREEN_WIDTH-SPACE_X-epo[i].GetWidth()))
                {
                    if ((gh.hp-DamageP)<=0)
                        gh.hp=0;
                    else
                        gh.hp-=DamageP;
                }
                Pop(E_Potany);
                continue;
            }
            epo[i].ChooseStage(Renderer);
        }
        
        for (int i=em_c;i>=em_f;i--)
        {
            if (emag[i].collision==1)
                emag[i].Attack2(Renderer);
        }
        for (int i=eh_c;i>=eh_f;i--)
        {
            if (eheal[i].collision==1)
            {
                //CollisionWithG(E_Healitato, i);
                eheal[i].Attack2(Renderer);
            }
        }
    }
    else if (eh.hp==0)
    {
        for (int i=em_c;i>=em_f;i--)
        {
            if (emag[i].hp>0 && emag[i].a==255 && ((emag[i].x+emag[i].GetWidth())<(SCREEN_WIDTH-SPACE_X-emag[i].GetWidth()+1)))
            {
                if (CheckCollision(E_Magitato, i))
                {
                    emag[i].collision=1;
                    if (emag[i].AWhichImage==7 && emag[i].GetAAni()==(AtkA_Vel-1))
                    {
                        switch(CollisionWithG(E_Magitato, i))
                        {
                            case G_Potany:
                                po[p_f].injury+=emag[i].atk;
                                break;
                            case G_Tankitato:
                                tank[t_f].injury+=emag[i].atk;
                                break;
                            case G_Magitato:
                                mag[m_f].injury+=emag[i].atk;
                                break;
                            case G_Healitato:
                                heal[h_f].injury+=emag[i].atk;
                                break;
                        }
                    }
                }
                else
                    emag[i].collision=0;
            }
            else
                emag[i].collision=0;
            /*if (emag[i].hp<=0 && emag[i].DWhichImage==8)
             {
             Pop(E_Magitato);
             emag[i].free();
             continue;
             }*/
            if ((emag[i].x==(SCREEN_WIDTH-SPACE_X-emag[i].GetWidth()) || emag[i].DWhichImage==8) && emag[i].a==0)
            {
                if (emag[i].x==(SCREEN_WIDTH-SPACE_X-emag[i].GetWidth()))
                {
                    if ((gh.hp-DamageM)<=0)
                        gh.hp=0;
                    else
                        gh.hp-=DamageM;
                }
                Pop(E_Magitato);
                continue;
            }
            emag[i].ChooseStage(Renderer);
        }
        for (int i=et_c;i>=et_f;i--)
        {
            if (etank[i].hp>0 && etank[i].a==255 && ((etank[i].x+etank[i].GetWidth())<(SCREEN_WIDTH-SPACE_X-100+1)))
            {
                if (CheckCollision(E_Tankitato, i))
                {
                    etank[i].collision=1;
                    if (etank[i].AWhichImage==7 && etank[i].GetAAni()==(AtkA_Vel-1))
                    {
                        switch(CollisionWithG(E_Tankitato, i))
                        {
                            case G_Potany:
                                po[p_f].injury+=etank[i].atk;
                                break;
                            case G_Tankitato:
                                tank[t_f].injury+=etank[i].atk;
                                break;
                            case G_Magitato:
                                mag[m_f].injury+=etank[i].atk;
                                break;
                            case G_Healitato:
                                heal[h_f].injury+=etank[i].atk;
                                break;
                        }
                    }
                }
                else
                    etank[i].collision=0;
            }
            else
                etank[i].collision=0;
            /*if (etank[i].hp<=0 && etank[i].DWhichImage==8)
             {
             Pop(E_Tankitato);
             etank[i].free();
             continue;
             }*/
            if ((etank[i].x==(SCREEN_WIDTH-SPACE_X-etank[i].GetWidth()) || etank[i].DWhichImage==8) && etank[i].a==0)
            {
                if (etank[i].x==(SCREEN_WIDTH-SPACE_X-etank[i].GetWidth()))
                {
                    if ((gh.hp-DamageT)<=0)
                        gh.hp=0;
                    else
                        gh.hp-=DamageT;
                }
                Pop(E_Tankitato);
                continue;
            }
            etank[i].ChooseStage(Renderer);
        }
        for (int i=eh_c;i>=eh_f;i--)
        {
            if (eheal[i].hp>0 && eheal[i].a==255 && ((eheal[i].x+eheal[i].GetWidth())<(SCREEN_WIDTH-SPACE_X-eheal[i].GetWidth()+1)))
            {
                if (CheckCollision(E_Healitato, i))
                {
                    eheal[i].collision=1;
                    if (eheal[i].AWhichImage==7 && eheal[i].GetAAni()==(AtkA_Vel-1))
                    {
                        switch(CollisionWithG(E_Healitato, i))
                        {
                            case E_Potany:
                                epo[p_f].injury-=eheal[i].atk;
                                break;
                            case E_Tankitato:
                                etank[t_f].injury-=eheal[i].atk;
                                break;
                            case E_Magitato:
                                emag[m_f].injury-=eheal[i].atk;
                                break;
                            case E_Healitato:
                                eheal[h_f].injury-=eheal[i].atk;
                                break;
                        }
                    }
                }
                else
                    eheal[i].collision=0;
            }
            else
                eheal[i].collision=0;
            /*if (eheal[i].hp<=0 && eheal[i].DWhichImage==8)
             {
             Pop(E_Healitato);
             eheal[i].free();
             continue;
             }*/
            if ((eheal[i].x==(SCREEN_WIDTH-SPACE_X-eheal[i].GetWidth()) || eheal[i].DWhichImage==8) && eheal[i].a==0)
            {
                if (eheal[i].x==(SCREEN_WIDTH-SPACE_X-eheal[i].GetWidth()))
                {
                    if ((gh.hp-DamageH)<=0)
                        gh.hp=0;
                    else
                        gh.hp-=DamageH;
                }
                Pop(E_Healitato);
                continue;
            }
            eheal[i].ChooseStage(Renderer);
        }
        for (int i=ep_c;i>=ep_f;i--)
        {
            if (epo[i].hp>0 && epo[i].a==255 && ((epo[i].x+epo[i].GetWidth())<(SCREEN_WIDTH-SPACE_X-epo[i].GetWidth()+1)))
            {
                if (CheckCollision(E_Potany, i))
                {
                    epo[i].collision=1;
                    if (epo[i].AWhichImage==7 && epo[i].GetAAni()==(AtkA_Vel-1))
                    {
                        switch(CollisionWithG(E_Potany, i))
                        {
                            case G_Potany:
                                po[p_f].injury+=epo[i].atk;
                                break;
                            case G_Tankitato:
                                tank[t_f].injury+=epo[i].atk;
                                break;
                            case G_Magitato:
                                mag[m_f].injury+=epo[i].atk;
                                break;
                            case G_Healitato:
                                heal[h_f].injury+=epo[i].atk;
                                break;
                        }
                    }
                }
                else
                    epo[i].collision=0;
            }
            else
                epo[i].collision=0;
            /*if (epo[i].hp<=0 && epo[i].DWhichImage==8)
             {
             Pop(E_Potany);
             epo[i].free();
             continue;
             }*/
            if ((epo[i].x==(SCREEN_WIDTH-SPACE_X-epo[i].GetWidth()) || epo[i].DWhichImage==8)&& epo[i].a==0)
            {
                if (epo[i].x==(SCREEN_WIDTH-SPACE_X-epo[i].GetWidth()))
                {
                    if ((gh.hp-DamageP)<=0)
                        gh.hp=0;
                    else
                        gh.hp-=DamageP;
                }
                Pop(E_Potany);
                continue;
            }
            epo[i].ChooseStage(Renderer);
        }
        
        for (int i=em_c;i>=em_f;i--)
        {
            if (emag[i].collision==1)
                emag[i].Attack2(Renderer);
        }
        for (int i=eh_c;i>=eh_f;i--)
        {
            if (eheal[i].collision==1)
            {
                //CollisionWithG(E_Healitato, i);
                eheal[i].Attack2(Renderer);
            }
        }
        
        LoadImageToRenderer("g_victory.png", Renderer, 0, 0);
        LoadImageToRenderer("victory.png", Renderer, 0, 0);
        
        for (int i=m_c;i>=m_f;i--)
        {
            if (mag[i].hp>0 && mag[i].a==255 && (mag[i].x>(SPACE_X+mag[i].GetWidth()-1)))
            {
                if (CheckCollision(G_Magitato, i))
                {
                    mag[i].collision=1;
                    if (mag[i].AWhichImage==7 && mag[i].GetAAni()==(AtkA_Vel-1))
                    {
                        switch(CollisionWithE(G_Magitato, i))
                        {
                            case E_Potany:
                                epo[ep_f].injury+=mag[i].atk;
                                break;
                            case E_Tankitato:
                                etank[et_f].injury+=mag[i].atk;
                                break;
                            case E_Magitato:
                                emag[em_f].injury+=mag[i].atk;
                                break;
                            case E_Healitato:
                                eheal[eh_f].injury+=mag[i].atk;
                                break;
                        }
                    }
                }
                else
                    mag[i].collision=0;
            }
            else
                mag[i].collision=0;
            /*if (mag[i].hp<=0 && mag[i].DWhichImage==8)
             {
             Pop(G_Magitato);
             mag[i].free();
             continue;
             }*/
            if ((mag[i].x==SPACE_X || mag[i].DWhichImage==8) && mag[i].a==0)
            {
                if (mag[i].x==SPACE_X)
                {
                    if ((eh.hp-DamageM)<=0)
                        eh.hp=0;
                    else
                        eh.hp-=DamageM;
                }
                Pop(G_Magitato);
                continue;
            }
            mag[i].ChooseStage(Renderer);
        }
        for (int i=t_c;i>=t_f;i--)
        {
            if (tank[i].hp>0 && tank[i].a==255 && (tank[i].x>(SPACE_X+100-1)))
            {
                if (CheckCollision(G_Tankitato, i))
                {
                    tank[i].collision=1;
                    if (tank[i].AWhichImage==7 && tank[i].GetAAni()==(AtkA_Vel-1))
                    {
                        switch(CollisionWithE(G_Tankitato, i))
                        {
                            case E_Potany:
                                epo[ep_f].injury+=tank[i].atk;
                                break;
                            case E_Tankitato:
                                etank[et_f].injury+=tank[i].atk;
                                break;
                            case E_Magitato:
                                emag[em_f].injury+=tank[i].atk;
                                break;
                            case E_Healitato:
                                eheal[eh_f].injury+=tank[i].atk;
                                break;
                        }
                    }
                }
                else
                    tank[i].collision=0;
            }
            else
                tank[i].collision=0;
            /*if (tank[i].hp<=0 && tank[i].DWhichImage==8)
             {
             Pop(G_Tankitato);
             tank[i].free();
             continue;
             }*/
            if ((tank[i].x==SPACE_X || tank[i].DWhichImage==8) && tank[i].a==0)
            {
                if (tank[i].x==SPACE_X)
                {
                    if ((eh.hp-DamageT)<=0)
                        eh.hp=0;
                    else
                        eh.hp-=DamageT;
                }
                Pop(G_Tankitato);
                continue;
            }
            tank[i].ChooseStage(Renderer);
        }
        for (int i=h_c;i>=h_f;i--)
        {
            if (heal[i].hp>0 && heal[i].a==255 && (heal[i].x>(SPACE_X+heal[i].GetWidth()-1)))
            {
                if (CheckCollision(G_Healitato, i))
                {
                    heal[i].collision=1;
                    if (heal[i].AWhichImage==7 && heal[i].GetAAni()==(AtkA_Vel-1))
                    {
                        switch(CollisionWithE(G_Healitato, i))
                        {
                            case G_Potany:
                                po[ep_f].injury-=heal[i].atk;
                                break;
                            case G_Tankitato:
                                tank[et_f].injury-=heal[i].atk;
                                break;
                            case G_Magitato:
                                mag[em_f].injury-=heal[i].atk;
                                break;
                            case G_Healitato:
                                heal[eh_f].injury-=heal[i].atk;
                                break;
                        }
                    }
                }
                else
                    heal[i].collision=0;
            }
            else
                heal[i].collision=0;
            /*if (heal[i].hp<=0 && heal[i].DWhichImage==8)
             {
             Pop(G_Healitato);
             heal[i].free();
             continue;
             }*/
            if ((heal[i].x==SPACE_X || heal[i].DWhichImage==8) && heal[i].a==0)
            {
                if (heal[i].x==SPACE_X)
                {
                    if ((eh.hp-DamageH)<=0)
                        eh.hp=0;
                    else
                        eh.hp-=DamageH;
                }
                Pop(G_Healitato);
                continue;
            }
            heal[i].ChooseStage(Renderer);
        }
        for (int i=p_c;i>=p_f;i--)
        {
            if (po[i].hp>0 && po[i].a==255 && (po[i].x>(SPACE_X+po[i].GetWidth()-1)))
            {
                if (CheckCollision(G_Potany, i))
                {
                    po[i].collision=1;
                    if (po[i].AWhichImage==7 && po[i].GetAAni()==(AtkA_Vel-1))
                    {
                        switch(CollisionWithE(G_Potany, i))
                        {
                            case E_Potany:
                                epo[ep_f].injury+=po[i].atk;
                                break;
                            case E_Tankitato:
                                etank[et_f].injury+=po[i].atk;
                                break;
                            case E_Magitato:
                                emag[em_f].injury+=po[i].atk;
                                break;
                            case E_Healitato:
                                eheal[eh_f].injury+=po[i].atk;
                                break;
                        }
                    }
                }
                else
                    po[i].collision=0;
            }
            else
                po[i].collision=0;
            /*if (po[i].hp<=0 && po[i].DWhichImage==8)
             {
             Pop(G_Potany);
             po[i].free();
             continue;
             }*/
            if ((po[i].x==SPACE_X || po[i].DWhichImage==8) && po[i].a==0)
            {
                if (po[i].x==SPACE_X)
                {
                    if ((eh.hp-DamageP)<=0)
                        eh.hp=0;
                    else
                        eh.hp-=DamageP;
                }
                Pop(G_Potany);
                continue;
            }
            po[i].ChooseStage(Renderer);
        }
        
        for (int i=m_c;i>=m_f;i--)
        {
            if (mag[i].collision==1)
                mag[i].Attack2(Renderer);
        }
        for (int i=h_c;i>=h_f;i--)
        {
            if (heal[i].collision==1)
            {
                //adjust attack_x&y
                //CollisionWithE(G_Healitato, i);
                heal[i].Attack2(Renderer);
            }
        }
    }
}

void potatoqueue::Push(int type)
{
    switch(type)
    {
        case G_Potany:
            p_c++; break;
        case G_Tankitato:
            t_c++; break;
        case G_Magitato:
            m_c++; break;
        case G_Healitato:
            h_c++; break;
        case E_Potany:
            ep_c++; break;
        case E_Tankitato:
            et_c++; break;
        case E_Magitato:
            em_c++; break;
        case E_Healitato:
            eh_c++; break;
    }
}

void potatoqueue::Pop(int type)
{
    switch(type)
    {
        case G_Potany:
            p_f++; break;
        case G_Tankitato:
            t_f++; break;
        case G_Magitato:
            m_f++; break;
        case G_Healitato:
            h_f++; break;
        case E_Potany:
            ep_f++; break;
        case E_Tankitato:
            et_f++; break;
        case E_Magitato:
            em_f++; break;
        case E_Healitato:
            eh_f++; break;
    }
}

bool potatoqueue::CheckCollision(int type, int WhichOne)
{
    if (type==G_Potany || type==G_Tankitato  || type==G_Magitato  || type==G_Healitato)
        return CollisionWithE(type, WhichOne);
    else if (type==E_Potany || type==E_Tankitato  || type==E_Magitato  || type==E_Healitato)
        return CollisionWithG(type, WhichOne);
    //Just in case that input(type) is invalid
    else
        return false;
}

int potatoqueue::CollisionWithG(int type, int WhichOne)
{
    if (type==E_Potany)
    {
        for (int i=t_f;i<=t_c;i++)
        {
            if ((epo[WhichOne].x+epo[WhichOne].GetWidth())>=tank[i].x && tank[i].hp>0 && tank[i].a==255)
            {
                epo[WhichOne].x=tank[i].x-epo[WhichOne].GetWidth();
                if (epo[WhichOne].x<SPACE_X)
                    epo[WhichOne].x=SPACE_X;
                return G_Tankitato;
            }

        }
        for (int i=p_f;i<=p_c;i++)
        {
            if ((epo[WhichOne].x+epo[WhichOne].GetWidth())>=po[i].x && po[i].hp>0 && po[i].a==255)
            {
                epo[WhichOne].x=po[i].x-epo[WhichOne].GetWidth();
                if (epo[WhichOne].x<SPACE_X)
                    epo[WhichOne].x=SPACE_X;
                return G_Potany;
            }

        }
        for (int i=m_f;i<=m_c;i++)
        {
            if ((epo[WhichOne].x+epo[WhichOne].GetWidth())>=mag[i].x && mag[i].hp>0 && mag[i].a==255)
            {
                epo[WhichOne].x=mag[i].x-epo[WhichOne].GetWidth();
                if (epo[WhichOne].x<SPACE_X)
                    epo[WhichOne].x=SPACE_X;
                return G_Magitato;
            }
        }
        for (int i=h_f;i<=h_c;i++)
        {
            if ((epo[WhichOne].x+epo[WhichOne].GetWidth())>=heal[i].x && heal[i].hp>0 && heal[i].a==255)
            {
                epo[WhichOne].x=heal[i].x-epo[WhichOne].GetWidth();
                if (epo[WhichOne].x<SPACE_X)
                    epo[WhichOne].x=SPACE_X;
                return G_Healitato;
            }
        }
        return false;
    }
    else if (type==E_Tankitato)
    {
        for (int i=t_f;i<=t_c;i++)
        {
            if ((etank[WhichOne].x+etank[WhichOne].GetWidth())>=tank[i].x&& tank[i].hp>0 && tank[i].a==255)
            {
                etank[WhichOne].x=tank[i].x-etank[WhichOne].GetWidth();
                if (etank[WhichOne].x<SPACE_X)
                    etank[WhichOne].x=SPACE_X;
                return G_Tankitato;
            }
        }
        for (int i=p_f;i<=p_c;i++)
        {
            if ((etank[WhichOne].x+etank[WhichOne].GetWidth())>=po[i].x && po[i].hp>0 && po[i].a==255)
            {
                etank[WhichOne].x=po[i].x-etank[WhichOne].GetWidth();
                if (etank[WhichOne].x<SPACE_X)
                    etank[WhichOne].x=SPACE_X;
                return G_Potany;
            }
        }
        for (int i=m_f;i<=m_c;i++)
        {
            if ((etank[WhichOne].x+etank[WhichOne].GetWidth())>=mag[i].x && mag[i].hp>0 && mag[i].a==255)
            {
                etank[WhichOne].x=mag[i].x-etank[WhichOne].GetWidth();
                if (etank[WhichOne].x<SPACE_X)
                    etank[WhichOne].x=SPACE_X;
                return G_Magitato;
            }
        }
        for (int i=h_f;i<=h_c;i++)
        {
            if ((etank[WhichOne].x+etank[WhichOne].GetWidth())>=heal[i].x && heal[i].hp>0 && heal[i].a==255)
            {
                etank[WhichOne].x=heal[i].x-etank[WhichOne].GetWidth();
                if (etank[WhichOne].x<SPACE_X)
                    etank[WhichOne].x=SPACE_X;
                return G_Healitato;
            }
        }
        return false;
    }
    else if (type==E_Magitato)
    {
        for (int i=t_f;i<=t_c;i++)
        {
            if ((emag[WhichOne].x+emag[WhichOne].GetWidth()+M_Range)>=tank[i].x && tank[i].hp>0 && tank[i].a==255)
            {
                if ((emag[WhichOne].x+emag[WhichOne].GetWidth()+M_Range)>tank[i].x)
                    emag[WhichOne].x-=M_Vel;
                if (emag[WhichOne].x<SPACE_X)
                    emag[WhichOne].x=SPACE_X;
                emag[WhichOne].attack_x=tank[i].x;
                return G_Tankitato;
            }
        }
        for (int i=p_f;i<=p_c;i++)
        {
            if ((emag[WhichOne].x+emag[WhichOne].GetWidth()+M_Range)>=po[i].x && po[i].hp>0 && po[i].a==255)
            {
                if ((emag[WhichOne].x+emag[WhichOne].GetWidth()+M_Range)>po[i].x)
                    emag[WhichOne].x-=M_Vel;
                if (emag[WhichOne].x<SPACE_X)
                    emag[WhichOne].x=SPACE_X;
                emag[WhichOne].attack_x=po[i].x;
                return G_Potany;
            }
        }
        for (int i=m_f;i<=m_c;i++)
        {
            if ((emag[WhichOne].x+emag[WhichOne].GetWidth()+M_Range)>=mag[i].x && mag[i].hp>0 && mag[i].a==255)
            {
                emag[WhichOne].x=mag[i].x-emag[WhichOne].GetWidth()-M_Range;
                if (emag[WhichOne].x<SPACE_X)
                    emag[WhichOne].x=SPACE_X;
                emag[WhichOne].attack_x=mag[i].x;
                return G_Magitato;
            }
        }
        for (int i=h_f;i<=h_c;i++)
        {
            if ((emag[WhichOne].x+emag[WhichOne].GetWidth()+M_Range)>=heal[i].x && heal[i].hp>0 && heal[i].a==255)
            {
                if ((emag[WhichOne].x+emag[WhichOne].GetWidth()+M_Range)>heal[i].x)
                    emag[WhichOne].x-=M_Vel;
                if (emag[WhichOne].x<SPACE_X)
                    emag[WhichOne].x=SPACE_X;
                emag[WhichOne].attack_x=heal[i].x;
                return G_Healitato;
            }
        }
        return false;
    }
    else if (type==E_Healitato)
    {
        if (eheal[WhichOne].hp<(10+eheal[WhichOne].lv*0))
        {
            if (eheal[WhichOne].AWhichImage==0 && eheal[WhichOne].GetAAni()==0)
            {
                eheal[WhichOne].attack_x=eheal[WhichOne].x+eheal[WhichOne].GetWidth()-100;
                eheal[WhichOne].attack_y=eheal[WhichOne].y-eheal[WhichOne].attack_h;
            }
            return E_Healitato;
        }
        for (int i=et_f;i<=et_c;i++)
        {
            if ((eheal[WhichOne].x+eheal[WhichOne].GetWidth()+H_Range)>=etank[i].x && etank[i].hp<(30+etank[i].lv*5) && etank[i].hp>0)
            {
                if (eheal[WhichOne].AWhichImage==0 && eheal[WhichOne].GetAAni()==0)
                {
                    eheal[WhichOne].attack_x=etank[i].x+etank[i].GetWidth()-100;
                    eheal[WhichOne].attack_y=etank[i].y-eheal[WhichOne].attack_h;
                }
                return E_Tankitato;
            }
        }
        for (int i=ep_f;i<=ep_c;i++)
        {
            if ((eheal[WhichOne].x+eheal[WhichOne].GetWidth()+H_Range)>=epo[i].x && epo[i].hp<(6+epo[i].lv*2) && epo[i].hp>0)
            {
                if (eheal[WhichOne].AWhichImage==0 && eheal[WhichOne].GetAAni()==0)
                {
                    eheal[WhichOne].attack_x=epo[i].x+epo[i].GetWidth()-100;
                    eheal[WhichOne].attack_y=epo[i].y-eheal[WhichOne].attack_h;
                }
                return E_Potany;
            }
        }
        for (int i=em_f;i<=em_c;i++)
        {
            if ((eheal[WhichOne].x+eheal[WhichOne].GetWidth()+H_Range)>=emag[i].x && emag[i].hp<(15-emag[i].lv*5) && emag[i].hp>0)
            {
                if (eheal[WhichOne].AWhichImage==0 && eheal[WhichOne].GetAAni()==0)
                {
                    eheal[WhichOne].attack_x=emag[i].x+emag[i].GetWidth()-100;
                    eheal[WhichOne].attack_y=emag[i].y-eheal[WhichOne].attack_h;
                }
                return E_Magitato;
            }
        }
        for (int i=eh_f;i<WhichOne;i++)
        {
            if ((eheal[WhichOne].x+eheal[WhichOne].GetWidth()+H_Range)>=eheal[i].x && eheal[i].hp<(10+eheal[i].lv*0) && eheal[i].hp>0)
            {
                if (eheal[WhichOne].AWhichImage==0 && eheal[WhichOne].GetAAni()==0)
                {
                    eheal[WhichOne].attack_x=eheal[i].x+eheal[i].GetWidth()-100;
                    eheal[WhichOne].attack_y=eheal[i].y-eheal[WhichOne].attack_h;
                }
                return E_Healitato;
            }
        }
        for (int i=t_f;i<=t_c;i++)
        {
            if ((eheal[WhichOne].x+eheal[WhichOne].GetWidth()+H_Range)>=tank[i].x && tank[i].hp>0 && tank[i].a==255)
            {
                if ((eheal[WhichOne].x+eheal[WhichOne].GetWidth()+H_Range)>tank[i].x)
                    eheal[WhichOne].x-=M_Vel;
                if (eheal[WhichOne].x<SPACE_X)
                    eheal[WhichOne].x=SPACE_X;
                if (eheal[WhichOne].AWhichImage==0 && eheal[WhichOne].GetAAni()==0)
                {
                    eheal[WhichOne].attack_x=eheal[eh_f].x+eheal[eh_f].GetWidth()-100;
                    eheal[WhichOne].attack_y=eheal[eh_f].y-eheal[eh_f].attack_h;
                }
                return G_Tankitato;
            }
        }
        for (int i=p_f;i<=p_c;i++)
        {
            if ((eheal[WhichOne].x+eheal[WhichOne].GetWidth()+H_Range)>=po[i].x && po[i].hp>0 && po[i].a==255)
            {
                if ((eheal[WhichOne].x+eheal[WhichOne].GetWidth()+H_Range)>po[i].x)
                    eheal[WhichOne].x-=M_Vel;
                if (eheal[WhichOne].x<SPACE_X)
                    eheal[WhichOne].x=SPACE_X;
                if (eheal[WhichOne].AWhichImage==0 && eheal[WhichOne].GetAAni()==0)
                {
                    eheal[WhichOne].attack_x=eheal[eh_f].x+eheal[eh_f].GetWidth()-100;
                    eheal[WhichOne].attack_y=eheal[eh_f].y-eheal[eh_f].attack_h;
                }
                return G_Potany;
            }
        }
        for (int i=m_f;i<=m_c;i++)
        {
            if ((eheal[WhichOne].x+eheal[WhichOne].GetWidth()+H_Range)>=mag[i].x && mag[i].hp>0 && mag[i].a==255)
            {
                if ((eheal[WhichOne].x+eheal[WhichOne].GetWidth()+H_Range)>mag[i].x)
                    eheal[WhichOne].x-=M_Vel;
                if (eheal[WhichOne].x<SPACE_X)
                    eheal[WhichOne].x=SPACE_X;
                if (eheal[WhichOne].AWhichImage==0 && eheal[WhichOne].GetAAni()==0)
                {
                    eheal[WhichOne].attack_x=eheal[eh_f].x+eheal[eh_f].GetWidth()-100;
                    eheal[WhichOne].attack_y=eheal[eh_f].y-eheal[eh_f].attack_h;
                }
                return G_Magitato;
            }
        }
        for (int i=h_f;i<=h_c;i++)
        {
            if ((eheal[WhichOne].x+eheal[WhichOne].GetWidth()+H_Range)>=heal[i].x && heal[i].hp>0 && heal[i].a==255)
            {
                if ((eheal[WhichOne].x+eheal[WhichOne].GetWidth()+H_Range)>heal[i].x)
                    eheal[WhichOne].x-=M_Vel;
                if (eheal[WhichOne].x<SPACE_X)
                    eheal[WhichOne].x=SPACE_X;
                if (eheal[WhichOne].AWhichImage==0 && eheal[WhichOne].GetAAni()==0)
                {
                    eheal[WhichOne].attack_x=eheal[eh_f].x+eheal[eh_f].GetWidth()-100;
                    eheal[WhichOne].attack_y=eheal[eh_f].y-eheal[eh_f].attack_h;
                }
                return G_Healitato;
            }
        }
        return false;
    }
    //Just in case that input(type) is invalid
    else
        return false;
}

int potatoqueue::CollisionWithE(int type, int WhichOne)
{
    if (type==G_Potany)
    {
        for (int i=et_f;i<=et_c;i++)
        {
            if (((etank[i].x+etank[i].GetWidth())>=po[WhichOne].x-M_Vel) && etank[i].hp>0 && etank[i].a==255)
            {
                po[WhichOne].x=etank[i].x+etank[i].GetWidth();
                if (po[WhichOne].x>SCREEN_WIDTH-SPACE_X-po[WhichOne].GetWidth())
                    po[WhichOne].x=SCREEN_WIDTH-SPACE_X-po[WhichOne].GetWidth();
                return E_Tankitato;
            }
        }
        for (int i=ep_f;i<=ep_c;i++)
        {
            if (((epo[i].x+epo[i].GetWidth())>=po[WhichOne].x-M_Vel) && epo[i].hp>0 && epo[i].a==255)
            {
                po[WhichOne].x=epo[i].x+epo[i].GetWidth();
                if (po[WhichOne].x>SCREEN_WIDTH-SPACE_X-po[WhichOne].GetWidth())
                    po[WhichOne].x=SCREEN_WIDTH-SPACE_X-po[WhichOne].GetWidth();
                return E_Potany;
            }
        }
        for (int i=em_f;i<=em_c;i++)
        {
            if (((emag[i].x+emag[i].GetWidth())>=po[WhichOne].x-M_Vel) && emag[i].hp>0 && emag[i].a==255)
            {
                po[WhichOne].x=emag[i].x+emag[i].GetWidth();
                if (po[WhichOne].x>SCREEN_WIDTH-SPACE_X-po[WhichOne].GetWidth())
                    po[WhichOne].x=SCREEN_WIDTH-SPACE_X-po[WhichOne].GetWidth();
                return E_Magitato;
            }
        }
        for (int i=eh_f;i<=eh_c;i++)
        {
            if (((eheal[i].x+eheal[i].GetWidth())>=po[WhichOne].x-M_Vel) && eheal[i].hp>0 && eheal[i].a==255)
            {
                po[WhichOne].x=eheal[i].x+eheal[i].GetWidth();
                if (po[WhichOne].x>SCREEN_WIDTH-SPACE_X-po[WhichOne].GetWidth())
                    po[WhichOne].x=SCREEN_WIDTH-SPACE_X-po[WhichOne].GetWidth();
                return E_Healitato;
            }
        }
        return false;
    }
    else if (type==G_Tankitato)
    {
        for (int i=et_f;i<=et_c;i++)
        {
            if (((etank[i].x+etank[i].GetWidth())>=tank[WhichOne].x-M_Vel) && etank[i].hp>0 && etank[i].a==255)
            {
                tank[WhichOne].x=etank[i].x+etank[i].GetWidth();
                if (tank[WhichOne].x>SCREEN_WIDTH-SPACE_X-tank[WhichOne].GetWidth())
                    tank[WhichOne].x=SCREEN_WIDTH-SPACE_X-tank[WhichOne].GetWidth();
                return E_Tankitato;
            }
        }
        for (int i=ep_f;i<=ep_c;i++)
        {
            if (((epo[i].x+epo[i].GetWidth())>=tank[WhichOne].x-M_Vel) && epo[i].hp>0 && epo[i].a==255)
            {
                tank[WhichOne].x=epo[i].x+epo[i].GetWidth();
                if (tank[WhichOne].x>SCREEN_WIDTH-SPACE_X-tank[WhichOne].GetWidth())
                    tank[WhichOne].x=SCREEN_WIDTH-SPACE_X-tank[WhichOne].GetWidth();
                return E_Potany;
            }
        }
        for (int i=em_f;i<=em_c;i++)
        {
            if (((emag[i].x+emag[i].GetWidth())>=tank[WhichOne].x-M_Vel) && emag[i].hp>0 && emag[i].a==255)
            {
                tank[WhichOne].x=emag[i].x+emag[i].GetWidth();
                if (tank[WhichOne].x>SCREEN_WIDTH-SPACE_X-tank[WhichOne].GetWidth())
                    tank[WhichOne].x=SCREEN_WIDTH-SPACE_X-tank[WhichOne].GetWidth();
                return E_Magitato;
            }
        }
        for (int i=eh_f;i<=eh_c;i++)
        {
            if (((eheal[i].x+eheal[i].GetWidth())>=tank[WhichOne].x-M_Vel) && eheal[i].hp>0 && eheal[i].a==255)
            {
                tank[WhichOne].x=eheal[i].x+eheal[i].GetWidth();
                if (tank[WhichOne].x>SCREEN_WIDTH-SPACE_X-tank[WhichOne].GetWidth())
                    tank[WhichOne].x=SCREEN_WIDTH-SPACE_X-tank[WhichOne].GetWidth();
                return E_Healitato;
            }
        }
        return false;
    }
    else if (type==G_Magitato)
    {
        for (int i=et_f;i<=et_c;i++)
        {
            if (((etank[i].x+etank[i].GetWidth()+M_Range)>=mag[WhichOne].x-M_Vel) && etank[i].hp>0 && etank[i].a==255)
            {
                if ((etank[i].x+etank[i].GetWidth()+M_Range)>mag[WhichOne].x)
                    mag[WhichOne].x+=M_Vel;
                if (mag[WhichOne].x>SCREEN_WIDTH-SPACE_X-mag[WhichOne].GetWidth())
                    mag[WhichOne].x=SCREEN_WIDTH-SPACE_X-mag[WhichOne].GetWidth();
                mag[WhichOne].attack_x=etank[i].x+etank[i].GetWidth()-100;
                return E_Tankitato;
            }
        }
        for (int i=ep_f;i<=ep_c;i++)
        {
            if (((epo[i].x+epo[i].GetWidth()+M_Range)>=mag[WhichOne].x-M_Vel) && epo[i].hp>0 && epo[i].a==255)
            {
                if ((epo[i].x+epo[i].GetWidth()+M_Range)>mag[WhichOne].x)
                    mag[WhichOne].x+=M_Vel;
                if (mag[WhichOne].x>SCREEN_WIDTH-SPACE_X-mag[WhichOne].GetWidth())
                    mag[WhichOne].x=SCREEN_WIDTH-SPACE_X-mag[WhichOne].GetWidth();
                mag[WhichOne].attack_x=epo[i].x+epo[i].GetWidth()-100;
                return E_Potany;
            }
        }
        for (int i=em_f;i<=em_c;i++)
        {
            if (((emag[i].x+emag[i].GetWidth()+M_Range)>=mag[WhichOne].x-M_Vel) && emag[i].hp>0 && emag[i].a==255)
            {
                mag[WhichOne].x=emag[i].x+emag[i].GetWidth()+M_Range;
                if (mag[WhichOne].x>SCREEN_WIDTH-SPACE_X-mag[WhichOne].GetWidth())
                    mag[WhichOne].x=SCREEN_WIDTH-SPACE_X-mag[WhichOne].GetWidth();
                mag[WhichOne].attack_x=emag[i].x+emag[i].GetWidth()-100;
                return E_Magitato;
            }
        }
        for (int i=eh_f;i<=eh_c;i++)
        {
            if (((eheal[i].x+eheal[i].GetWidth()+M_Range)>=mag[WhichOne].x-M_Vel) && eheal[i].hp>0 && eheal[i].a==255)
            {
                if ((eheal[i].x+eheal[i].GetWidth()+M_Range)>mag[WhichOne].x)
                    mag[WhichOne].x+=M_Vel;
                if (mag[WhichOne].x>SCREEN_WIDTH-SPACE_X-mag[WhichOne].GetWidth())
                    mag[WhichOne].x=SCREEN_WIDTH-SPACE_X-mag[WhichOne].GetWidth();
                mag[WhichOne].attack_x=eheal[i].x+eheal[i].GetWidth()-100;
                return E_Healitato;
            }
        }
        return false;
    }
    else if (type==G_Healitato)
    {
        if (heal[WhichOne].hp<(10+heal[WhichOne].lv*0))
        {
            if (heal[WhichOne].AWhichImage==0 && heal[WhichOne].GetAAni()==0)
            {
                heal[WhichOne].attack_x=heal[WhichOne].x;
                heal[WhichOne].attack_y=heal[WhichOne].y-heal[WhichOne].attack_h;
            }
            return G_Healitato;
        }
        for (int i=t_f;i<=t_c;i++)
        {
            if ((heal[WhichOne].x-H_Range-tank[i].GetWidth())<=tank[i].x && tank[i].hp<(30+tank[i].lv*5) && tank[i].hp>0)
            {
                if (heal[WhichOne].AWhichImage==0 && heal[WhichOne].GetAAni()==0)
                {
                    heal[WhichOne].attack_x=tank[i].x;
                    heal[WhichOne].attack_y=tank[i].y-heal[WhichOne].attack_h;
                }
                return G_Tankitato;
            }
        }
        for (int i=p_f;i<=p_c;i++)
        {
            if ((heal[WhichOne].x-H_Range-po[i].GetWidth())<=po[i].x && po[i].hp<(6+po[i].lv*2) && po[i].hp>0)
            {
                if (heal[WhichOne].AWhichImage==0 && heal[WhichOne].GetAAni()==0)
                {
                    heal[WhichOne].attack_x=po[i].x;
                    heal[WhichOne].attack_y=po[i].y-heal[WhichOne].attack_h;
                }
                return G_Potany;
            }
        }
        for (int i=m_f;i<=m_c;i++)
        {
            if ((heal[WhichOne].x-H_Range-mag[i].GetWidth())<=mag[i].x && mag[i].hp<(15-mag[i].lv*5) && mag[i].hp>0)
            {
                if (heal[WhichOne].AWhichImage==0 && heal[WhichOne].GetAAni()==0)
                {
                    heal[WhichOne].attack_x=mag[i].x;
                    heal[WhichOne].attack_y=mag[i].y-heal[WhichOne].attack_h;
                }
                return G_Magitato;
            }
        }
        for (int i=h_f;i<WhichOne;i++)
        {
            if ((heal[WhichOne].x-H_Range-heal[i].GetWidth())<=heal[i].x && heal[i].hp<(10+heal[i].lv*0) && heal[i].hp>0)
            {
                if (heal[WhichOne].AWhichImage==0 && heal[WhichOne].GetAAni()==0)
                {
                    heal[WhichOne].attack_x=heal[i].x;
                    heal[WhichOne].attack_y=heal[i].y-heal[WhichOne].attack_h;
                }
                return G_Healitato;
            }
        }
        for (int i=et_f;i<=et_c;i++)
        {
            if (((etank[i].x+etank[i].GetWidth()+H_Range)>=heal[WhichOne].x-M_Vel) && etank[i].hp>0 && etank[i].a==255)
            {
                if ((etank[i].x+etank[i].GetWidth()+H_Range)>heal[WhichOne].x)
                    heal[WhichOne].x+=M_Vel;
                if (heal[WhichOne].x>SCREEN_WIDTH-SPACE_X-heal[WhichOne].GetWidth())
                    heal[WhichOne].x=SCREEN_WIDTH-SPACE_X-heal[WhichOne].GetWidth();
                if (heal[WhichOne].AWhichImage==0 && heal[WhichOne].GetAAni()==0)
                {
                    heal[WhichOne].attack_x=heal[h_f].x;
                    heal[WhichOne].attack_y=heal[h_f].y-heal[h_f].attack_h;
                }
                return E_Tankitato;
            }
        }
        for (int i=ep_f;i<=ep_c;i++)
        {
            if (((epo[i].x+epo[i].GetWidth()+H_Range)>=heal[WhichOne].x-M_Vel) && epo[i].hp>0 && epo[i].a==255)
            {
                if ((epo[i].x+epo[i].GetWidth()+H_Range)>heal[WhichOne].x)
                    heal[WhichOne].x+=M_Vel;
                if (heal[WhichOne].x>SCREEN_WIDTH-SPACE_X-heal[WhichOne].GetWidth())
                    heal[WhichOne].x=SCREEN_WIDTH-SPACE_X-heal[WhichOne].GetWidth();
                if (heal[WhichOne].AWhichImage==0 && heal[WhichOne].GetAAni()==0)
                {
                    heal[WhichOne].attack_x=heal[h_f].x;
                    heal[WhichOne].attack_y=heal[h_f].y-heal[h_f].attack_h;
                }
                return E_Potany;
            }
        }
        for (int i=em_f;i<=em_c;i++)
        {
            if (((emag[i].x+emag[i].GetWidth()+H_Range)>=heal[WhichOne].x-M_Vel) && emag[i].hp>0 && emag[i].a==255)
            {
                if ((emag[i].x+emag[i].GetWidth()+H_Range)>heal[WhichOne].x)
                    heal[WhichOne].x+=M_Vel;
                if (heal[WhichOne].x>SCREEN_WIDTH-SPACE_X-heal[WhichOne].GetWidth())
                    heal[WhichOne].x=SCREEN_WIDTH-SPACE_X-heal[WhichOne].GetWidth();
                if (heal[WhichOne].AWhichImage==0 && heal[WhichOne].GetAAni()==0)
                {
                    heal[WhichOne].attack_x=heal[h_f].x;
                    heal[WhichOne].attack_y=heal[h_f].y-heal[h_f].attack_h;
                }
                return E_Magitato;
            }
        }
        for (int i=eh_f;i<=eh_c;i++)
        {
            if (((eheal[i].x+eheal[i].GetWidth()+H_Range)>=heal[WhichOne].x-M_Vel) && eheal[i].hp>0 && eheal[i].a==255)
            {
                if ((eheal[i].x+eheal[i].GetWidth()+H_Range)>heal[WhichOne].x)
                    heal[WhichOne].x+=M_Vel;
                if (heal[WhichOne].x>SCREEN_WIDTH-SPACE_X-heal[WhichOne].GetWidth())
                    heal[WhichOne].x=SCREEN_WIDTH-SPACE_X-heal[WhichOne].GetWidth();
                if (heal[WhichOne].AWhichImage==0 && heal[WhichOne].GetAAni()==0)
                {
                    heal[WhichOne].attack_x=heal[h_f].x;
                    heal[WhichOne].attack_y=heal[h_f].y-heal[h_f].attack_h;
                }
                return E_Healitato;
            }
        }
        return false;
    }
    //Just in case that input(type) is invalid
    else
        return false;
}

void potatoqueue::LevelUp(int type)
{
    if (type==G_Potany)
    {
        for (int i=p_f;i<NumberP;i++)
        {
            po[i].lv++;
            po[i].hp=6+po[i].lv*2;
            po[i].atk=5+po[i].lv*2;
            
        }
        if (po[p_f].lv==1)
        {
            po[p_f].Image[0]=IMG_Load("gpotany1_0.png");
            po[p_f].Image[1]=IMG_Load("gpotany1_1.png");
            po[p_f].Image[2]=IMG_Load("gpotany1_2.png");
            po[p_f].Image[3]=IMG_Load("gpotany1_3.png");
            po[p_f].Image[4]=IMG_Load("gpotany1_4.png");
            po[p_f].Image[5]=IMG_Load("gpotany1_5.png");
            po[p_f].Image[6]=IMG_Load("gpotany1_6.png");
            po[p_f].Image[7]=IMG_Load("gpotany1_7.png");
            po[p_f].AttackImage[0]=IMG_Load("gp1_attack_0.png");
            po[p_f].AttackImage[1]=IMG_Load("gp1_attack_1.png");
            po[p_f].AttackImage[2]=IMG_Load("gp1_attack_2.png");
            po[p_f].AttackImage[3]=IMG_Load("gp1_attack_3.png");
            po[p_f].AttackImage[4]=IMG_Load("gp1_attack_4.png");
            po[p_f].AttackImage[5]=IMG_Load("gp1_attack_5.png");
            po[p_f].AttackImage[6]=IMG_Load("gp1_attack_6.png");
            po[p_f].AttackImage[7]=IMG_Load("gp1_attack_7.png");
            po[p_f].DeadImage[0]=IMG_Load("gp1_dead_0.png");
            po[p_f].DeadImage[1]=IMG_Load("gp1_dead_1.png");
            po[p_f].DeadImage[2]=IMG_Load("gp1_dead_2.png");
            po[p_f].DeadImage[3]=IMG_Load("gp1_dead_3.png");
            po[p_f].DeadImage[4]=IMG_Load("gp1_dead_4.png");
            po[p_f].DeadImage[5]=IMG_Load("gp1_dead_5.png");
            po[p_f].DeadImage[6]=IMG_Load("gp1_dead_6.png");
            po[p_f].DeadImage[7]=IMG_Load("gp1_dead_7.png");
            for (int i=p_f+1;i<NumberP;i++)
            {
                for (int j=0;j<8;j++)
                {
                    po[i].Image[j]=po[p_f].Image[j];
                    po[i].AttackImage[j]=po[p_f].AttackImage[j];
                    po[i].DeadImage[j]=po[p_f].DeadImage[j];
                }
            }
        }
        else if (po[p_f].lv==2)
        {
            po[p_f].Image[0]=IMG_Load("gpotany2_0.png");
            po[p_f].Image[1]=IMG_Load("gpotany2_1.png");
            po[p_f].Image[2]=IMG_Load("gpotany2_2.png");
            po[p_f].Image[3]=IMG_Load("gpotany2_3.png");
            po[p_f].Image[4]=IMG_Load("gpotany2_4.png");
            po[p_f].Image[5]=IMG_Load("gpotany2_5.png");
            po[p_f].Image[6]=IMG_Load("gpotany2_6.png");
            po[p_f].Image[7]=IMG_Load("gpotany2_7.png");
            po[p_f].AttackImage[0]=IMG_Load("gp2_attack_0.png");
            po[p_f].AttackImage[1]=IMG_Load("gp2_attack_1.png");
            po[p_f].AttackImage[2]=IMG_Load("gp2_attack_2.png");
            po[p_f].AttackImage[3]=IMG_Load("gp2_attack_3.png");
            po[p_f].AttackImage[4]=IMG_Load("gp2_attack_4.png");
            po[p_f].AttackImage[5]=IMG_Load("gp2_attack_5.png");
            po[p_f].AttackImage[6]=IMG_Load("gp2_attack_6.png");
            po[p_f].AttackImage[7]=IMG_Load("gp2_attack_7.png");
            po[p_f].DeadImage[0]=IMG_Load("gp2_dead_0.png");
            po[p_f].DeadImage[1]=IMG_Load("gp2_dead_1.png");
            po[p_f].DeadImage[2]=IMG_Load("gp2_dead_2.png");
            po[p_f].DeadImage[3]=IMG_Load("gp2_dead_3.png");
            po[p_f].DeadImage[4]=IMG_Load("gp2_dead_4.png");
            po[p_f].DeadImage[5]=IMG_Load("gp2_dead_5.png");
            po[p_f].DeadImage[6]=IMG_Load("gp2_dead_6.png");
            po[p_f].DeadImage[7]=IMG_Load("gp2_dead_7.png");
            for (int i=p_f+1;i<NumberP;i++)
            {
                for (int j=0;j<8;j++)
                {
                    po[i].Image[j]=po[p_f].Image[j];
                    po[i].AttackImage[j]=po[p_f].AttackImage[j];
                    po[i].DeadImage[j]=po[p_f].DeadImage[j];
                }
            }
        }
    }
    else if (type==G_Tankitato)
    {
        for (int i=t_f;i<NumberT;i++)
        {
            tank[i].lv++;
            tank[i].hp=30+tank[i].lv*5;
            tank[i].atk=4+tank[i].lv*0;
        }
        if (tank[t_f].lv==1)
        {
            tank[t_f].Image[0]=IMG_Load("gtankitato1_0.png");
            tank[t_f].Image[1]=IMG_Load("gtankitato1_1.png");
            tank[t_f].Image[2]=IMG_Load("gtankitato1_2.png");
            tank[t_f].Image[3]=IMG_Load("gtankitato1_3.png");
            tank[t_f].Image[4]=IMG_Load("gtankitato1_4.png");
            tank[t_f].Image[5]=IMG_Load("gtankitato1_5.png");
            tank[t_f].Image[6]=IMG_Load("gtankitato1_6.png");
            tank[t_f].Image[7]=IMG_Load("gtankitato1_7.png");
            tank[t_f].AttackImage[0]=IMG_Load("gt1_attack_0.png");
            tank[t_f].AttackImage[1]=IMG_Load("gt1_attack_1.png");
            tank[t_f].AttackImage[2]=IMG_Load("gt1_attack_2.png");
            tank[t_f].AttackImage[3]=IMG_Load("gt1_attack_3.png");
            tank[t_f].AttackImage[4]=IMG_Load("gt1_attack_4.png");
            tank[t_f].AttackImage[5]=IMG_Load("gt1_attack_5.png");
            tank[t_f].AttackImage[6]=IMG_Load("gt1_attack_6.png");
            tank[t_f].AttackImage[7]=IMG_Load("gt1_attack_7.png");
            tank[t_f].DeadImage[0]=IMG_Load("gt1_dead_0.png");
            tank[t_f].DeadImage[1]=IMG_Load("gt1_dead_1.png");
            tank[t_f].DeadImage[2]=IMG_Load("gt1_dead_2.png");
            tank[t_f].DeadImage[3]=IMG_Load("gt1_dead_3.png");
            tank[t_f].DeadImage[4]=IMG_Load("gt1_dead_4.png");
            tank[t_f].DeadImage[5]=IMG_Load("gt1_dead_5.png");
            tank[t_f].DeadImage[6]=IMG_Load("gt1_dead_6.png");
            tank[t_f].DeadImage[7]=IMG_Load("gt1_dead_7.png");
            for (int i=t_f+1;i<NumberT;i++)
            {
                for (int j=0;j<8;j++)
                {
                    tank[i].Image[j]=tank[t_f].Image[j];
                    tank[i].AttackImage[j]=tank[t_f].AttackImage[j];
                    tank[i].DeadImage[j]=tank[t_f].DeadImage[j];
                }
            }
        }
        else if (tank[t_f].lv==2)
        {
            tank[t_f].Image[0]=IMG_Load("gtankitato2_0.png");
            tank[t_f].Image[1]=IMG_Load("gtankitato2_1.png");
            tank[t_f].Image[2]=IMG_Load("gtankitato2_2.png");
            tank[t_f].Image[3]=IMG_Load("gtankitato2_3.png");
            tank[t_f].Image[4]=IMG_Load("gtankitato2_4.png");
            tank[t_f].Image[5]=IMG_Load("gtankitato2_5.png");
            tank[t_f].Image[6]=IMG_Load("gtankitato2_6.png");
            tank[t_f].Image[7]=IMG_Load("gtankitato2_7.png");
            tank[t_f].AttackImage[0]=IMG_Load("gt2_attack_0.png");
            tank[t_f].AttackImage[1]=IMG_Load("gt2_attack_1.png");
            tank[t_f].AttackImage[2]=IMG_Load("gt2_attack_2.png");
            tank[t_f].AttackImage[3]=IMG_Load("gt2_attack_3.png");
            tank[t_f].AttackImage[4]=IMG_Load("gt2_attack_4.png");
            tank[t_f].AttackImage[5]=IMG_Load("gt2_attack_5.png");
            tank[t_f].AttackImage[6]=IMG_Load("gt2_attack_6.png");
            tank[t_f].AttackImage[7]=IMG_Load("gt2_attack_7.png");
            tank[t_f].DeadImage[0]=IMG_Load("gt2_dead_0.png");
            tank[t_f].DeadImage[1]=IMG_Load("gt2_dead_1.png");
            tank[t_f].DeadImage[2]=IMG_Load("gt2_dead_2.png");
            tank[t_f].DeadImage[3]=IMG_Load("gt2_dead_3.png");
            tank[t_f].DeadImage[4]=IMG_Load("gt2_dead_4.png");
            tank[t_f].DeadImage[5]=IMG_Load("gt2_dead_5.png");
            tank[t_f].DeadImage[6]=IMG_Load("gt2_dead_6.png");
            tank[t_f].DeadImage[7]=IMG_Load("gt2_dead_7.png");
            for (int i=t_f+1;i<NumberT;i++)
            {
                for (int j=0;j<8;j++)
                {
                    tank[i].Image[j]=tank[t_f].Image[j];
                    tank[i].AttackImage[j]=tank[t_f].AttackImage[j];
                    tank[i].DeadImage[j]=tank[t_f].DeadImage[j];
                }
            }
        }
    }
    else if (type==G_Magitato)
    {
        for (int i=m_f;i<NumberM;i++)
        {
            mag[i].lv++;
            mag[i].hp=15-mag[i].lv*5;
            mag[i].atk=5+mag[i].lv*5;
        }
        if (mag[m_f].lv==1)
        {
            mag[m_f].Image[0]=IMG_Load("gmagitato1_0.png");
            mag[m_f].Image[1]=IMG_Load("gmagitato1_1.png");
            mag[m_f].Image[2]=IMG_Load("gmagitato1_2.png");
            mag[m_f].Image[3]=IMG_Load("gmagitato1_3.png");
            mag[m_f].Image[4]=IMG_Load("gmagitato1_4.png");
            mag[m_f].Image[5]=IMG_Load("gmagitato1_5.png");
            mag[m_f].Image[6]=IMG_Load("gmagitato1_6.png");
            mag[m_f].Image[7]=IMG_Load("gmagitato1_7.png");
            mag[m_f].AttackImage[0]=IMG_Load("gm1_attack_0.png");
            mag[m_f].AttackImage[1]=IMG_Load("gm1_attack_1.png");
            mag[m_f].AttackImage[2]=IMG_Load("gm1_attack_2.png");
            mag[m_f].AttackImage[3]=IMG_Load("gm1_attack_3.png");
            mag[m_f].AttackImage[4]=IMG_Load("gm1_attack_4.png");
            mag[m_f].AttackImage[5]=IMG_Load("gm1_attack_5.png");
            mag[m_f].AttackImage[6]=IMG_Load("gm1_attack_6.png");
            mag[m_f].AttackImage[7]=IMG_Load("gm1_attack_7.png");
            mag[m_f].AttackImage2[0]=IMG_Load("gm1_attack2_0.png");
            mag[m_f].AttackImage2[1]=IMG_Load("gm1_attack2_1.png");
            mag[m_f].AttackImage2[2]=IMG_Load("gm1_attack2_2.png");
            mag[m_f].AttackImage2[3]=IMG_Load("gm1_attack2_3.png");
            mag[m_f].AttackImage2[4]=IMG_Load("gm1_attack2_4.png");
            mag[m_f].AttackImage2[5]=IMG_Load("gm1_attack2_5.png");
            mag[m_f].AttackImage2[6]=IMG_Load("gm1_attack2_6.png");
            mag[m_f].AttackImage2[7]=IMG_Load("gm1_attack2_7.png");
            mag[m_f].DeadImage[0]=IMG_Load("gm1_dead_0.png");
            mag[m_f].DeadImage[1]=IMG_Load("gm1_dead_1.png");
            mag[m_f].DeadImage[2]=IMG_Load("gm1_dead_2.png");
            mag[m_f].DeadImage[3]=IMG_Load("gm1_dead_3.png");
            mag[m_f].DeadImage[4]=IMG_Load("gm1_dead_4.png");
            mag[m_f].DeadImage[5]=IMG_Load("gm1_dead_5.png");
            mag[m_f].DeadImage[6]=IMG_Load("gm1_dead_6.png");
            mag[m_f].DeadImage[7]=IMG_Load("gm1_dead_7.png");
            for (int i=m_f+1;i<NumberM;i++)
            {
                for (int j=0;j<8;j++)
                {
                    mag[i].Image[j]=mag[m_f].Image[j];
                    mag[i].AttackImage[j]=mag[m_f].AttackImage[j];
                    mag[i].AttackImage2[j]=mag[m_f].AttackImage2[j];
                    mag[i].DeadImage[j]=mag[m_f].DeadImage[j];
                }
            }
        }
        else if (mag[m_f].lv==2)
        {
            mag[m_f].Image[0]=IMG_Load("gmagitato2_0.png");
            mag[m_f].Image[1]=IMG_Load("gmagitato2_1.png");
            mag[m_f].Image[2]=IMG_Load("gmagitato2_2.png");
            mag[m_f].Image[3]=IMG_Load("gmagitato2_3.png");
            mag[m_f].Image[4]=IMG_Load("gmagitato2_4.png");
            mag[m_f].Image[5]=IMG_Load("gmagitato2_5.png");
            mag[m_f].Image[6]=IMG_Load("gmagitato2_6.png");
            mag[m_f].Image[7]=IMG_Load("gmagitato2_7.png");
            mag[m_f].AttackImage[0]=IMG_Load("gm2_attack_0.png");
            mag[m_f].AttackImage[1]=IMG_Load("gm2_attack_1.png");
            mag[m_f].AttackImage[2]=IMG_Load("gm2_attack_2.png");
            mag[m_f].AttackImage[3]=IMG_Load("gm2_attack_3.png");
            mag[m_f].AttackImage[4]=IMG_Load("gm2_attack_4.png");
            mag[m_f].AttackImage[5]=IMG_Load("gm2_attack_5.png");
            mag[m_f].AttackImage[6]=IMG_Load("gm2_attack_6.png");
            mag[m_f].AttackImage[7]=IMG_Load("gm2_attack_7.png");
            mag[m_f].AttackImage2[0]=IMG_Load("gm2_attack2_0.png");
            mag[m_f].AttackImage2[1]=IMG_Load("gm2_attack2_1.png");
            mag[m_f].AttackImage2[2]=IMG_Load("gm2_attack2_2.png");
            mag[m_f].AttackImage2[3]=IMG_Load("gm2_attack2_3.png");
            mag[m_f].AttackImage2[4]=IMG_Load("gm2_attack2_4.png");
            mag[m_f].AttackImage2[5]=IMG_Load("gm2_attack2_5.png");
            mag[m_f].AttackImage2[6]=IMG_Load("gm2_attack2_6.png");
            mag[m_f].AttackImage2[7]=IMG_Load("gm2_attack2_7.png");
            mag[m_f].DeadImage[0]=IMG_Load("gm2_dead_0.png");
            mag[m_f].DeadImage[1]=IMG_Load("gm2_dead_1.png");
            mag[m_f].DeadImage[2]=IMG_Load("gm2_dead_2.png");
            mag[m_f].DeadImage[3]=IMG_Load("gm2_dead_3.png");
            mag[m_f].DeadImage[4]=IMG_Load("gm2_dead_4.png");
            mag[m_f].DeadImage[5]=IMG_Load("gm2_dead_5.png");
            mag[m_f].DeadImage[6]=IMG_Load("gm2_dead_6.png");
            mag[m_f].DeadImage[7]=IMG_Load("gm2_dead_7.png");
            for (int i=m_f+1;i<NumberM;i++)
            {
                for (int j=0;j<8;j++)
                {
                    mag[i].Image[j]=mag[m_f].Image[j];
                    mag[i].AttackImage[j]=mag[m_f].AttackImage[j];
                    mag[i].AttackImage2[j]=mag[m_f].AttackImage2[j];
                    mag[i].DeadImage[j]=mag[m_f].DeadImage[j];

                }
            }
        }
    }
    else if (type==G_Healitato)
    {
        for (int i=h_f;i<NumberH;i++)
        {
            heal[i].lv++;
            heal[i].hp=10+heal[i].lv*0;
            heal[i].atk=4+heal[i].lv*3;
        }
        if (heal[h_f].lv==1)
        {
            heal[h_f].Image[0]=IMG_Load("ghealitato1_0.png");
            heal[h_f].Image[1]=IMG_Load("ghealitato1_1.png");
            heal[h_f].Image[2]=IMG_Load("ghealitato1_2.png");
            heal[h_f].Image[3]=IMG_Load("ghealitato1_3.png");
            heal[h_f].Image[4]=IMG_Load("ghealitato1_4.png");
            heal[h_f].Image[5]=IMG_Load("ghealitato1_5.png");
            heal[h_f].Image[6]=IMG_Load("ghealitato1_6.png");
            heal[h_f].Image[7]=IMG_Load("ghealitato1_7.png");
            heal[h_f].AttackImage[0]=IMG_Load("gh1_attack_0.png");
            heal[h_f].AttackImage[1]=IMG_Load("gh1_attack_1.png");
            heal[h_f].AttackImage[2]=IMG_Load("gh1_attack_2.png");
            heal[h_f].AttackImage[3]=IMG_Load("gh1_attack_3.png");
            heal[h_f].AttackImage[4]=IMG_Load("gh1_attack_4.png");
            heal[h_f].AttackImage[5]=IMG_Load("gh1_attack_5.png");
            heal[h_f].AttackImage[6]=IMG_Load("gh1_attack_6.png");
            heal[h_f].AttackImage[7]=IMG_Load("gh1_attack_7.png");
            heal[h_f].AttackImage2[0]=IMG_Load("gh1_attack2_0.png");
            heal[h_f].AttackImage2[1]=IMG_Load("gh1_attack2_1.png");
            heal[h_f].AttackImage2[2]=IMG_Load("gh1_attack2_2.png");
            heal[h_f].AttackImage2[3]=IMG_Load("gh1_attack2_3.png");
            heal[h_f].AttackImage2[4]=IMG_Load("gh1_attack2_4.png");
            heal[h_f].AttackImage2[5]=IMG_Load("gh1_attack2_5.png");
            heal[h_f].AttackImage2[6]=IMG_Load("gh1_attack2_6.png");
            heal[h_f].AttackImage2[7]=IMG_Load("gh1_attack2_7.png");
            heal[h_f].DeadImage[0]=IMG_Load("gh1_dead_0.png");
            heal[h_f].DeadImage[1]=IMG_Load("gh1_dead_1.png");
            heal[h_f].DeadImage[2]=IMG_Load("gh1_dead_2.png");
            heal[h_f].DeadImage[3]=IMG_Load("gh1_dead_3.png");
            heal[h_f].DeadImage[4]=IMG_Load("gh1_dead_4.png");
            heal[h_f].DeadImage[5]=IMG_Load("gh1_dead_5.png");
            heal[h_f].DeadImage[6]=IMG_Load("gh1_dead_6.png");
            heal[h_f].DeadImage[7]=IMG_Load("gh1_dead_7.png");
            for (int i=h_f+1;i<NumberH;i++)
            {
                for (int j=0;j<8;j++)
                {
                    heal[i].Image[j]=heal[h_f].Image[j];
                    heal[i].AttackImage[j]=heal[h_f].AttackImage[j];
                    heal[i].AttackImage2[j]=heal[h_f].AttackImage2[j];
                    heal[i].DeadImage[j]=heal[h_f].DeadImage[j];
                }
            }
        }
        else if (heal[h_f].lv==2)
        {
            heal[h_f].Image[0]=IMG_Load("ghealitato2_0.png");
            heal[h_f].Image[1]=IMG_Load("ghealitato2_1.png");
            heal[h_f].Image[2]=IMG_Load("ghealitato2_2.png");
            heal[h_f].Image[3]=IMG_Load("ghealitato2_3.png");
            heal[h_f].Image[4]=IMG_Load("ghealitato2_4.png");
            heal[h_f].Image[5]=IMG_Load("ghealitato2_5.png");
            heal[h_f].Image[6]=IMG_Load("ghealitato2_6.png");
            heal[h_f].Image[7]=IMG_Load("ghealitato2_7.png");
            heal[h_f].AttackImage[0]=IMG_Load("gh2_attack_0.png");
            heal[h_f].AttackImage[1]=IMG_Load("gh2_attack_1.png");
            heal[h_f].AttackImage[2]=IMG_Load("gh2_attack_2.png");
            heal[h_f].AttackImage[3]=IMG_Load("gh2_attack_3.png");
            heal[h_f].AttackImage[4]=IMG_Load("gh2_attack_4.png");
            heal[h_f].AttackImage[5]=IMG_Load("gh2_attack_5.png");
            heal[h_f].AttackImage[6]=IMG_Load("gh2_attack_6.png");
            heal[h_f].AttackImage[7]=IMG_Load("gh2_attack_7.png");
            heal[h_f].AttackImage2[0]=IMG_Load("gh2_attack2_0.png");
            heal[h_f].AttackImage2[1]=IMG_Load("gh2_attack2_1.png");
            heal[h_f].AttackImage2[2]=IMG_Load("gh2_attack2_2.png");
            heal[h_f].AttackImage2[3]=IMG_Load("gh2_attack2_3.png");
            heal[h_f].AttackImage2[4]=IMG_Load("gh2_attack2_4.png");
            heal[h_f].AttackImage2[5]=IMG_Load("gh2_attack2_5.png");
            heal[h_f].AttackImage2[6]=IMG_Load("gh2_attack2_6.png");
            heal[h_f].AttackImage2[7]=IMG_Load("gh2_attack2_7.png");
            heal[h_f].DeadImage[0]=IMG_Load("gh2_dead_0.png");
            heal[h_f].DeadImage[1]=IMG_Load("gh2_dead_1.png");
            heal[h_f].DeadImage[2]=IMG_Load("gh2_dead_2.png");
            heal[h_f].DeadImage[3]=IMG_Load("gh2_dead_3.png");
            heal[h_f].DeadImage[4]=IMG_Load("gh2_dead_4.png");
            heal[h_f].DeadImage[5]=IMG_Load("gh2_dead_5.png");
            heal[h_f].DeadImage[6]=IMG_Load("gh2_dead_6.png");
            heal[h_f].DeadImage[7]=IMG_Load("gh2_dead_7.png");
            for (int i=h_f+1;i<NumberH;i++)
            {
                for (int j=0;j<8;j++)
                {
                    heal[i].Image[j]=heal[h_f].Image[j];
                    heal[i].AttackImage[j]=heal[h_f].AttackImage[j];
                    heal[i].AttackImage2[j]=heal[h_f].AttackImage2[j];
                    heal[i].DeadImage[j]=heal[h_f].DeadImage[j];
                }
            }
        }
    }
    else if (type==E_Potany)
    {
        for (int i=ep_f;i<NumberP;i++)
        {
            epo[i].lv++;
            epo[i].hp=6+epo[i].lv*2;
            epo[i].atk=5+epo[i].lv*2;
        }
        if (epo[ep_f].lv==1)
        {
            epo[ep_f].Image[0]=IMG_Load("epotany1_0.png");
            epo[ep_f].Image[1]=IMG_Load("epotany1_1.png");
            epo[ep_f].Image[2]=IMG_Load("epotany1_2.png");
            epo[ep_f].Image[3]=IMG_Load("epotany1_3.png");
            epo[ep_f].Image[4]=IMG_Load("epotany1_4.png");
            epo[ep_f].Image[5]=IMG_Load("epotany1_5.png");
            epo[ep_f].Image[6]=IMG_Load("epotany1_6.png");
            epo[ep_f].Image[7]=IMG_Load("epotany1_7.png");
            epo[ep_f].AttackImage[0]=IMG_Load("ep1_attack_0.png");
            epo[ep_f].AttackImage[1]=IMG_Load("ep1_attack_1.png");
            epo[ep_f].AttackImage[2]=IMG_Load("ep1_attack_2.png");
            epo[ep_f].AttackImage[3]=IMG_Load("ep1_attack_3.png");
            epo[ep_f].AttackImage[4]=IMG_Load("ep1_attack_4.png");
            epo[ep_f].AttackImage[5]=IMG_Load("ep1_attack_5.png");
            epo[ep_f].AttackImage[6]=IMG_Load("ep1_attack_6.png");
            epo[ep_f].AttackImage[7]=IMG_Load("ep1_attack_7.png");
            epo[ep_f].DeadImage[0]=IMG_Load("ep1_dead_0.png");
            epo[ep_f].DeadImage[1]=IMG_Load("ep1_dead_1.png");
            epo[ep_f].DeadImage[2]=IMG_Load("ep1_dead_2.png");
            epo[ep_f].DeadImage[3]=IMG_Load("ep1_dead_3.png");
            epo[ep_f].DeadImage[4]=IMG_Load("ep1_dead_4.png");
            epo[ep_f].DeadImage[5]=IMG_Load("ep1_dead_5.png");
            epo[ep_f].DeadImage[6]=IMG_Load("ep1_dead_6.png");
            epo[ep_f].DeadImage[7]=IMG_Load("ep1_dead_7.png");
            for (int i=ep_f+1;i<NumberP;i++)
            {
                for (int j=0;j<8;j++)
                {
                    epo[i].Image[j]=epo[ep_f].Image[j];
                    epo[i].AttackImage[j]=epo[ep_f].AttackImage[j];
                    epo[i].DeadImage[j]=epo[ep_f].DeadImage[j];
                }
            }
        }
        else if (epo[ep_f].lv==2)
        {
            epo[ep_f].Image[0]=IMG_Load("epotany2_0.png");
            epo[ep_f].Image[1]=IMG_Load("epotany2_1.png");
            epo[ep_f].Image[2]=IMG_Load("epotany2_2.png");
            epo[ep_f].Image[3]=IMG_Load("epotany2_3.png");
            epo[ep_f].Image[4]=IMG_Load("epotany2_4.png");
            epo[ep_f].Image[5]=IMG_Load("epotany2_5.png");
            epo[ep_f].Image[6]=IMG_Load("epotany2_6.png");
            epo[ep_f].Image[7]=IMG_Load("epotany2_7.png");
            epo[ep_f].AttackImage[0]=IMG_Load("ep2_attack_0.png");
            epo[ep_f].AttackImage[1]=IMG_Load("ep2_attack_1.png");
            epo[ep_f].AttackImage[2]=IMG_Load("ep2_attack_2.png");
            epo[ep_f].AttackImage[3]=IMG_Load("ep2_attack_3.png");
            epo[ep_f].AttackImage[4]=IMG_Load("ep2_attack_4.png");
            epo[ep_f].AttackImage[5]=IMG_Load("ep2_attack_5.png");
            epo[ep_f].AttackImage[6]=IMG_Load("ep2_attack_6.png");
            epo[ep_f].AttackImage[7]=IMG_Load("ep2_attack_7.png");
            epo[ep_f].DeadImage[0]=IMG_Load("ep2_dead_0.png");
            epo[ep_f].DeadImage[1]=IMG_Load("ep2_dead_1.png");
            epo[ep_f].DeadImage[2]=IMG_Load("ep2_dead_2.png");
            epo[ep_f].DeadImage[3]=IMG_Load("ep2_dead_3.png");
            epo[ep_f].DeadImage[4]=IMG_Load("ep2_dead_4.png");
            epo[ep_f].DeadImage[5]=IMG_Load("ep2_dead_5.png");
            epo[ep_f].DeadImage[6]=IMG_Load("ep2_dead_6.png");
            epo[ep_f].DeadImage[7]=IMG_Load("ep2_dead_7.png");
            for (int i=ep_f+1;i<NumberP;i++)
            {
                for (int j=0;j<8;j++)
                {
                    epo[i].Image[j]=epo[ep_f].Image[j];
                    epo[i].AttackImage[j]=epo[ep_f].AttackImage[j];
                    epo[i].DeadImage[j]=epo[ep_f].DeadImage[j];
                }
            }
        }
    }
    else if (type==E_Tankitato)
    {
        for (int i=et_f;i<NumberT;i++)
        {
            etank[i].lv++;
            etank[i].hp=30+etank[i].lv*5;
            etank[i].atk=4+etank[i].lv*0;
        }
        if (etank[et_f].lv==1)
        {
            etank[et_f].Image[0]=IMG_Load("etankitato1_0.png");
            etank[et_f].Image[1]=IMG_Load("etankitato1_1.png");
            etank[et_f].Image[2]=IMG_Load("etankitato1_2.png");
            etank[et_f].Image[3]=IMG_Load("etankitato1_3.png");
            etank[et_f].Image[4]=IMG_Load("etankitato1_4.png");
            etank[et_f].Image[5]=IMG_Load("etankitato1_5.png");
            etank[et_f].Image[6]=IMG_Load("etankitato1_6.png");
            etank[et_f].Image[7]=IMG_Load("etankitato1_7.png");
            etank[et_f].AttackImage[0]=IMG_Load("et1_attack_0.png");
            etank[et_f].AttackImage[1]=IMG_Load("et1_attack_1.png");
            etank[et_f].AttackImage[2]=IMG_Load("et1_attack_2.png");
            etank[et_f].AttackImage[3]=IMG_Load("et1_attack_3.png");
            etank[et_f].AttackImage[4]=IMG_Load("et1_attack_4.png");
            etank[et_f].AttackImage[5]=IMG_Load("et1_attack_5.png");
            etank[et_f].AttackImage[6]=IMG_Load("et1_attack_6.png");
            etank[et_f].AttackImage[7]=IMG_Load("et1_attack_7.png");
            etank[et_f].DeadImage[0]=IMG_Load("et1_dead_0.png");
            etank[et_f].DeadImage[1]=IMG_Load("et1_dead_1.png");
            etank[et_f].DeadImage[2]=IMG_Load("et1_dead_2.png");
            etank[et_f].DeadImage[3]=IMG_Load("et1_dead_3.png");
            etank[et_f].DeadImage[4]=IMG_Load("et1_dead_4.png");
            etank[et_f].DeadImage[5]=IMG_Load("et1_dead_5.png");
            etank[et_f].DeadImage[6]=IMG_Load("et1_dead_6.png");
            etank[et_f].DeadImage[7]=IMG_Load("et1_dead_7.png");
            for (int i=et_f+1;i<NumberT;i++)
            {
                for (int j=0;j<8;j++)
                {
                    etank[i].Image[j]=etank[et_f].Image[j];
                    etank[i].AttackImage[j]=etank[et_f].AttackImage[j];
                    etank[i].DeadImage[j]=etank[et_f].DeadImage[j];
                }
            }
        }
        else if (etank[et_f].lv==2)
        {
            etank[et_f].Image[0]=IMG_Load("etankitato2_0.png");
            etank[et_f].Image[1]=IMG_Load("etankitato2_1.png");
            etank[et_f].Image[2]=IMG_Load("etankitato2_2.png");
            etank[et_f].Image[3]=IMG_Load("etankitato2_3.png");
            etank[et_f].Image[4]=IMG_Load("etankitato2_4.png");
            etank[et_f].Image[5]=IMG_Load("etankitato2_5.png");
            etank[et_f].Image[6]=IMG_Load("etankitato2_6.png");
            etank[et_f].Image[7]=IMG_Load("etankitato2_7.png");
            etank[et_f].AttackImage[0]=IMG_Load("et2_attack_0.png");
            etank[et_f].AttackImage[1]=IMG_Load("et2_attack_1.png");
            etank[et_f].AttackImage[2]=IMG_Load("et2_attack_2.png");
            etank[et_f].AttackImage[3]=IMG_Load("et2_attack_3.png");
            etank[et_f].AttackImage[4]=IMG_Load("et2_attack_4.png");
            etank[et_f].AttackImage[5]=IMG_Load("et2_attack_5.png");
            etank[et_f].AttackImage[6]=IMG_Load("et2_attack_6.png");
            etank[et_f].AttackImage[7]=IMG_Load("et2_attack_7.png");
            etank[et_f].DeadImage[0]=IMG_Load("et2_dead_0.png");
            etank[et_f].DeadImage[1]=IMG_Load("et2_dead_1.png");
            etank[et_f].DeadImage[2]=IMG_Load("et2_dead_2.png");
            etank[et_f].DeadImage[3]=IMG_Load("et2_dead_3.png");
            etank[et_f].DeadImage[4]=IMG_Load("et2_dead_4.png");
            etank[et_f].DeadImage[5]=IMG_Load("et2_dead_5.png");
            etank[et_f].DeadImage[6]=IMG_Load("et2_dead_6.png");
            etank[et_f].DeadImage[7]=IMG_Load("et2_dead_7.png");
            for (int i=et_f+1;i<NumberT;i++)
            {
                for (int j=0;j<8;j++)
                {
                    etank[i].Image[j]=etank[et_f].Image[j];
                    etank[i].AttackImage[j]=etank[et_f].AttackImage[j];
                    etank[i].DeadImage[j]=etank[et_f].DeadImage[j];
                }
            }
        }
    }
    else if (type==E_Magitato)
    {
        for (int i=em_f;i<NumberM;i++)
        {
            emag[i].lv++;
            emag[i].hp=15-emag[i].lv*5;
            emag[i].atk=5+emag[i].lv*5;
        }
        if (emag[em_f].lv==1)
        {
            emag[em_f].Image[0]=IMG_Load("emagitato1_0.png");
            emag[em_f].Image[1]=IMG_Load("emagitato1_1.png");
            emag[em_f].Image[2]=IMG_Load("emagitato1_2.png");
            emag[em_f].Image[3]=IMG_Load("emagitato1_3.png");
            emag[em_f].Image[4]=IMG_Load("emagitato1_4.png");
            emag[em_f].Image[5]=IMG_Load("emagitato1_5.png");
            emag[em_f].Image[6]=IMG_Load("emagitato1_6.png");
            emag[em_f].Image[7]=IMG_Load("emagitato1_7.png");
            emag[em_f].AttackImage[0]=IMG_Load("em1_attack_0.png");
            emag[em_f].AttackImage[1]=IMG_Load("em1_attack_1.png");
            emag[em_f].AttackImage[2]=IMG_Load("em1_attack_2.png");
            emag[em_f].AttackImage[3]=IMG_Load("em1_attack_3.png");
            emag[em_f].AttackImage[4]=IMG_Load("em1_attack_4.png");
            emag[em_f].AttackImage[5]=IMG_Load("em1_attack_5.png");
            emag[em_f].AttackImage[6]=IMG_Load("em1_attack_6.png");
            emag[em_f].AttackImage[7]=IMG_Load("em1_attack_7.png");
            emag[em_f].AttackImage2[0]=IMG_Load("em1_attack2_0.png");
            emag[em_f].AttackImage2[1]=IMG_Load("em1_attack2_1.png");
            emag[em_f].AttackImage2[2]=IMG_Load("em1_attack2_2.png");
            emag[em_f].AttackImage2[3]=IMG_Load("em1_attack2_3.png");
            emag[em_f].AttackImage2[4]=IMG_Load("em1_attack2_4.png");
            emag[em_f].AttackImage2[5]=IMG_Load("em1_attack2_5.png");
            emag[em_f].AttackImage2[6]=IMG_Load("em1_attack2_6.png");
            emag[em_f].AttackImage2[7]=IMG_Load("em1_attack2_7.png");
            emag[em_f].DeadImage[0]=IMG_Load("em1_dead_0.png");
            emag[em_f].DeadImage[1]=IMG_Load("em1_dead_1.png");
            emag[em_f].DeadImage[2]=IMG_Load("em1_dead_2.png");
            emag[em_f].DeadImage[3]=IMG_Load("em1_dead_3.png");
            emag[em_f].DeadImage[4]=IMG_Load("em1_dead_4.png");
            emag[em_f].DeadImage[5]=IMG_Load("em1_dead_5.png");
            emag[em_f].DeadImage[6]=IMG_Load("em1_dead_6.png");
            emag[em_f].DeadImage[7]=IMG_Load("em1_dead_7.png");
            for (int i=em_f+1;i<NumberM;i++)
            {
                for (int j=0;j<8;j++)
                {
                    emag[i].Image[j]=emag[em_f].Image[j];
                    emag[i].AttackImage2[j]=emag[em_f].AttackImage2[j];
                    emag[i].DeadImage[j]=emag[em_f].DeadImage[j];
                }
            }
        }
        else if (emag[em_f].lv==2)
        {
            emag[em_f].Image[0]=IMG_Load("emagitato2_0.png");
            emag[em_f].Image[1]=IMG_Load("emagitato2_1.png");
            emag[em_f].Image[2]=IMG_Load("emagitato2_2.png");
            emag[em_f].Image[3]=IMG_Load("emagitato2_3.png");
            emag[em_f].Image[4]=IMG_Load("emagitato2_4.png");
            emag[em_f].Image[5]=IMG_Load("emagitato2_5.png");
            emag[em_f].Image[6]=IMG_Load("emagitato2_6.png");
            emag[em_f].Image[7]=IMG_Load("emagitato2_7.png");
            emag[em_f].AttackImage[0]=IMG_Load("em2_attack_0.png");
            emag[em_f].AttackImage[1]=IMG_Load("em2_attack_1.png");
            emag[em_f].AttackImage[2]=IMG_Load("em2_attack_2.png");
            emag[em_f].AttackImage[3]=IMG_Load("em2_attack_3.png");
            emag[em_f].AttackImage[4]=IMG_Load("em2_attack_4.png");
            emag[em_f].AttackImage[5]=IMG_Load("em2_attack_5.png");
            emag[em_f].AttackImage[6]=IMG_Load("em2_attack_6.png");
            emag[em_f].AttackImage[7]=IMG_Load("em2_attack_7.png");
            emag[em_f].AttackImage2[0]=IMG_Load("em2_attack2_0.png");
            emag[em_f].AttackImage2[1]=IMG_Load("em2_attack2_1.png");
            emag[em_f].AttackImage2[2]=IMG_Load("em2_attack2_2.png");
            emag[em_f].AttackImage2[3]=IMG_Load("em2_attack2_3.png");
            emag[em_f].AttackImage2[4]=IMG_Load("em2_attack2_4.png");
            emag[em_f].AttackImage2[5]=IMG_Load("em2_attack2_5.png");
            emag[em_f].AttackImage2[6]=IMG_Load("em2_attack2_6.png");
            emag[em_f].AttackImage2[7]=IMG_Load("em2_attack2_7.png");
            emag[em_f].DeadImage[0]=IMG_Load("em2_dead_0.png");
            emag[em_f].DeadImage[1]=IMG_Load("em2_dead_1.png");
            emag[em_f].DeadImage[2]=IMG_Load("em2_dead_2.png");
            emag[em_f].DeadImage[3]=IMG_Load("em2_dead_3.png");
            emag[em_f].DeadImage[4]=IMG_Load("em2_dead_4.png");
            emag[em_f].DeadImage[5]=IMG_Load("em2_dead_5.png");
            emag[em_f].DeadImage[6]=IMG_Load("em2_dead_6.png");
            emag[em_f].DeadImage[7]=IMG_Load("em2_dead_7.png");
            for (int i=em_f+1;i<NumberM;i++)
            {
                for (int j=0;j<8;j++)
                {
                    emag[i].Image[j]=emag[em_f].Image[j];
                    emag[i].AttackImage[j]=emag[em_f].AttackImage[j];
                    emag[i].AttackImage2[j]=emag[em_f].AttackImage2[j];
                    emag[i].DeadImage[j]=emag[em_f].DeadImage[j];
                }
            }
        }
    }
    else if (type==E_Healitato)
    {
        for (int i=eh_f;i<NumberH;i++)
        {
            eheal[i].lv++;
            eheal[i].hp=10+eheal[i].lv*0;
            eheal[i].atk=4+eheal[i].lv*3;
        }
        if (eheal[eh_f].lv==1)
        {
            eheal[eh_f].Image[0]=IMG_Load("ehealitato1_0.png");
            eheal[eh_f].Image[1]=IMG_Load("ehealitato1_1.png");
            eheal[eh_f].Image[2]=IMG_Load("ehealitato1_2.png");
            eheal[eh_f].Image[3]=IMG_Load("ehealitato1_3.png");
            eheal[eh_f].Image[4]=IMG_Load("ehealitato1_4.png");
            eheal[eh_f].Image[5]=IMG_Load("ehealitato1_5.png");
            eheal[eh_f].Image[6]=IMG_Load("ehealitato1_6.png");
            eheal[eh_f].Image[7]=IMG_Load("ehealitato1_7.png");
            eheal[eh_f].AttackImage[0]=IMG_Load("eh1_attack_0.png");
            eheal[eh_f].AttackImage[1]=IMG_Load("eh1_attack_1.png");
            eheal[eh_f].AttackImage[2]=IMG_Load("eh1_attack_2.png");
            eheal[eh_f].AttackImage[3]=IMG_Load("eh1_attack_3.png");
            eheal[eh_f].AttackImage[4]=IMG_Load("eh1_attack_4.png");
            eheal[eh_f].AttackImage[5]=IMG_Load("eh1_attack_5.png");
            eheal[eh_f].AttackImage[6]=IMG_Load("eh1_attack_6.png");
            eheal[eh_f].AttackImage[7]=IMG_Load("eh1_attack_7.png");
            eheal[eh_f].AttackImage2[0]=IMG_Load("eh1_attack2_0.png");
            eheal[eh_f].AttackImage2[1]=IMG_Load("eh1_attack2_1.png");
            eheal[eh_f].AttackImage2[2]=IMG_Load("eh1_attack2_2.png");
            eheal[eh_f].AttackImage2[3]=IMG_Load("eh1_attack2_3.png");
            eheal[eh_f].AttackImage2[4]=IMG_Load("eh1_attack2_4.png");
            eheal[eh_f].AttackImage2[5]=IMG_Load("eh1_attack2_5.png");
            eheal[eh_f].AttackImage2[6]=IMG_Load("eh1_attack2_6.png");
            eheal[eh_f].AttackImage2[7]=IMG_Load("eh1_attack2_7.png");
            eheal[eh_f].DeadImage[0]=IMG_Load("eh1_dead_0.png");
            eheal[eh_f].DeadImage[1]=IMG_Load("eh1_dead_1.png");
            eheal[eh_f].DeadImage[2]=IMG_Load("eh1_dead_2.png");
            eheal[eh_f].DeadImage[3]=IMG_Load("eh1_dead_3.png");
            eheal[eh_f].DeadImage[4]=IMG_Load("eh1_dead_4.png");
            eheal[eh_f].DeadImage[5]=IMG_Load("eh1_dead_5.png");
            eheal[eh_f].DeadImage[6]=IMG_Load("eh1_dead_6.png");
            eheal[eh_f].DeadImage[7]=IMG_Load("eh1_dead_7.png");
            for (int i=eh_f+1;i<NumberH;i++)
            {
                for (int j=0;j<8;j++)
                {
                    eheal[i].Image[j]=eheal[eh_f].Image[j];
                    eheal[i].AttackImage[j]=eheal[eh_f].AttackImage[j];
                    eheal[i].AttackImage2[j]=eheal[eh_f].AttackImage2[j];
                    eheal[i].DeadImage[j]=eheal[eh_f].DeadImage[j];
                }
            }
        }
        else if (eheal[eh_f].lv==2)
        {
            eheal[eh_f].Image[0]=IMG_Load("ehealitato2_0.png");
            eheal[eh_f].Image[1]=IMG_Load("ehealitato2_1.png");
            eheal[eh_f].Image[2]=IMG_Load("ehealitato2_2.png");
            eheal[eh_f].Image[3]=IMG_Load("ehealitato2_3.png");
            eheal[eh_f].Image[4]=IMG_Load("ehealitato2_4.png");
            eheal[eh_f].Image[5]=IMG_Load("ehealitato2_5.png");
            eheal[eh_f].Image[6]=IMG_Load("ehealitato2_6.png");
            eheal[eh_f].Image[7]=IMG_Load("ehealitato2_7.png");
            eheal[eh_f].AttackImage[0]=IMG_Load("eh2_attack_0.png");
            eheal[eh_f].AttackImage[1]=IMG_Load("eh2_attack_1.png");
            eheal[eh_f].AttackImage[2]=IMG_Load("eh2_attack_2.png");
            eheal[eh_f].AttackImage[3]=IMG_Load("eh2_attack_3.png");
            eheal[eh_f].AttackImage[4]=IMG_Load("eh2_attack_4.png");
            eheal[eh_f].AttackImage[5]=IMG_Load("eh2_attack_5.png");
            eheal[eh_f].AttackImage[6]=IMG_Load("eh2_attack_6.png");
            eheal[eh_f].AttackImage[7]=IMG_Load("eh2_attack_7.png");
            eheal[eh_f].AttackImage2[0]=IMG_Load("eh2_attack2_0.png");
            eheal[eh_f].AttackImage2[1]=IMG_Load("eh2_attack2_1.png");
            eheal[eh_f].AttackImage2[2]=IMG_Load("eh2_attack2_2.png");
            eheal[eh_f].AttackImage2[3]=IMG_Load("eh2_attack2_3.png");
            eheal[eh_f].AttackImage2[4]=IMG_Load("eh2_attack2_4.png");
            eheal[eh_f].AttackImage2[5]=IMG_Load("eh2_attack2_5.png");
            eheal[eh_f].AttackImage2[6]=IMG_Load("eh2_attack2_6.png");
            eheal[eh_f].AttackImage2[7]=IMG_Load("eh2_attack2_7.png");
            eheal[eh_f].DeadImage[0]=IMG_Load("eh2_dead_0.png");
            eheal[eh_f].DeadImage[1]=IMG_Load("eh2_dead_1.png");
            eheal[eh_f].DeadImage[2]=IMG_Load("eh2_dead_2.png");
            eheal[eh_f].DeadImage[3]=IMG_Load("eh2_dead_3.png");
            eheal[eh_f].DeadImage[4]=IMG_Load("eh2_dead_4.png");
            eheal[eh_f].DeadImage[5]=IMG_Load("eh2_dead_5.png");
            eheal[eh_f].DeadImage[6]=IMG_Load("eh2_dead_6.png");
            eheal[eh_f].DeadImage[7]=IMG_Load("eh2_dead_7.png");
            for (int i=eh_f+1;i<NumberH;i++)
            {
                for (int j=0;j<8;j++)
                {
                    eheal[i].Image[j]=eheal[eh_f].Image[j];
                    eheal[i].AttackImage[j]=eheal[eh_f].AttackImage[j];
                    eheal[i].AttackImage2[j]=eheal[eh_f].AttackImage2[j];
                    eheal[i].DeadImage[j]=eheal[eh_f].DeadImage[j];
                }
            }
        }
    }
}

void potatoqueue::free()
{
    for (int i=0;i<NumberP;i++)
    {
        for (int j=0;j<8;j++)
        {
            SDL_FreeSurface(po[i].Image[j]);
            SDL_FreeSurface(po[i].AttackImage[j]);
            SDL_FreeSurface(po[i].DeadImage[j]);
            SDL_FreeSurface(epo[i].Image[j]);
            SDL_FreeSurface(epo[i].AttackImage[j]);
            SDL_FreeSurface(epo[i].DeadImage[j]);
        }
    }
    for (int i=0;i<NumberT;i++)
    {
        for (int j=0;j<8;j++)
        {
            SDL_FreeSurface(tank[i].Image[j]);
            SDL_FreeSurface(tank[i].AttackImage[j]);
            SDL_FreeSurface(tank[i].DeadImage[j]);
            SDL_FreeSurface(etank[i].Image[j]);
            SDL_FreeSurface(etank[i].AttackImage[j]);
            SDL_FreeSurface(etank[i].DeadImage[j]);
        }
    }
    for (int i=0;i<NumberM;i++)
    {
        for (int j=0;j<8;j++)
        {
            SDL_FreeSurface(mag[i].Image[j]);
            SDL_FreeSurface(mag[i].AttackImage[j]);
            SDL_FreeSurface(mag[i].DeadImage[j]);
            SDL_FreeSurface(emag[i].Image[j]);
            SDL_FreeSurface(emag[i].AttackImage[j]);
            SDL_FreeSurface(emag[i].DeadImage[j]);
        }
    }
    for (int i=0;i<NumberH;i++)
    {
        for (int j=0;j<8;j++)
        {
            SDL_FreeSurface(heal[i].Image[j]);
            SDL_FreeSurface(heal[i].AttackImage[j]);
            SDL_FreeSurface(heal[i].DeadImage[j]);
            SDL_FreeSurface(eheal[i].Image[j]);
            SDL_FreeSurface(eheal[i].AttackImage[j]);
            SDL_FreeSurface(eheal[i].DeadImage[j]);
        }
    }
}

material::material()
{
    x=0;
    y=0;
    number=0;
    vel=0;
    Image[0]=IMG_Load("0.png");
    Image[1]=IMG_Load("1.png");
    Image[2]=IMG_Load("2.png");
    Image[3]=IMG_Load("3.png");
    Image[4]=IMG_Load("4.png");
    Image[5]=IMG_Load("5.png");
    Image[6]=IMG_Load("6.png");
    Image[7]=IMG_Load("7.png");
    Image[8]=IMG_Load("8.png");
    Image[9]=IMG_Load("9.png");
    Texture=NULL;
}

material::material(int p, int q, int t) :x(p), y(q), type(t)
{
    number=0;
    vel=0;
    a=0;
    Image[0]=IMG_Load("0.png");
    Image[1]=IMG_Load("1.png");
    Image[2]=IMG_Load("2.png");
    Image[3]=IMG_Load("3.png");
    Image[4]=IMG_Load("4.png");
    Image[5]=IMG_Load("5.png");
    Image[6]=IMG_Load("6.png");
    Image[7]=IMG_Load("7.png");
    Image[8]=IMG_Load("8.png");
    Image[9]=IMG_Load("9.png");
    Texture=NULL;
    if (type==0)
    {
        potato[0][0]=IMG_Load("somgpotany_0.png");
        potato[0][1]=IMG_Load("somgtankitato_0.png");
        potato[0][2]=IMG_Load("somgmagitato_0.png");
        potato[0][3]=IMG_Load("somghealitato_0.png");
        potato[1][0]=IMG_Load("somgpotany_1.png");
        potato[1][1]=IMG_Load("somgtankitato_1.png");
        potato[1][2]=IMG_Load("somgmagitato_1.png");
        potato[1][3]=IMG_Load("somghealitato_1.png");
    }
    else if (type==1)
    {
        potato[0][0]=IMG_Load("somepotany_0.png");
        potato[0][1]=IMG_Load("sometankitato_0.png");
        potato[0][2]=IMG_Load("somemagitato_0.png");
        potato[0][3]=IMG_Load("somehealitato_0.png");
        potato[1][0]=IMG_Load("somepotany_1.png");
        potato[1][1]=IMG_Load("sometankitato_1.png");
        potato[1][2]=IMG_Load("somemagitato_1.png");
        potato[1][3]=IMG_Load("somehealitato_1.png");
    }
}


void material::Print(SDL_Renderer *Renderer)
{
    for (int i=Digits-1;i>=0;i--)
    {
        int which=(int)(((int)((int)(number/pow(10,i))*pow(10,i))-(int)((int)(number/pow(10,i+1))*pow(10,i+1)))/pow(10,i));
        SDL_Rect renderquad={x+(Digits-1-i)*Image[which]->w, y, Image[which]->w, Image[which]->h};
        Texture=SDL_CreateTextureFromSurface(Renderer, Image[which]);
        SDL_RenderCopy(Renderer, Texture, NULL, &renderquad );
        SDL_DestroyTexture(Texture);
        Texture=NULL;
    }
    vel++;
    if (vel==Number_Vel)
    {
        vel=0;
        number++;
        if (number>=99999)
            number=99999;
    }
    if (type==0)
    {
        if (number>=CostM)
        {
            SurfaceToRenderer(potato[1][0], Renderer, 550, 400, NULL, 255);
            SurfaceToRenderer(potato[1][1], Renderer, 660, 400, NULL, 255);
            SurfaceToRenderer(potato[1][2], Renderer, 770, 400, NULL, 255);
            SurfaceToRenderer(potato[1][3], Renderer, 880, 400, NULL, 255);
        }
        else if (number>=CostH)
        {
            SurfaceToRenderer(potato[1][0], Renderer, 550, 400, NULL, 255);
            SurfaceToRenderer(potato[1][1], Renderer, 660, 400, NULL, 255);
            SurfaceToRenderer(potato[0][2], Renderer, 770, 400, NULL, 255);
            SurfaceToRenderer(potato[1][3], Renderer, 880, 400, NULL, 255);
        }
        else if (number>=CostT)
        {
            SurfaceToRenderer(potato[1][0], Renderer, 550, 400, NULL, 255);
            SurfaceToRenderer(potato[1][1], Renderer, 660, 400, NULL, 255);
            SurfaceToRenderer(potato[0][2], Renderer, 770, 400, NULL, 255);
            SurfaceToRenderer(potato[0][3], Renderer, 880, 400, NULL, 255);
        }
        else if (number>=CostP)
        {
            SurfaceToRenderer(potato[1][0], Renderer, 550, 400, NULL, 255);
            SurfaceToRenderer(potato[0][1], Renderer, 660, 400, NULL, 255);
            SurfaceToRenderer(potato[0][2], Renderer, 770, 400, NULL, 255);
            SurfaceToRenderer(potato[0][3], Renderer, 880, 400, NULL, 255);
        }
        else
        {
            SurfaceToRenderer(potato[0][0], Renderer, 550, 400, NULL, 255);
            SurfaceToRenderer(potato[0][1], Renderer, 660, 400, NULL, 255);
            SurfaceToRenderer(potato[0][2], Renderer, 770, 400, NULL, 255);
            SurfaceToRenderer(potato[0][3], Renderer, 880, 400, NULL, 255);
        }
    }
    else if (type==1)
    {
        if (number>=CostM)
        {
            SurfaceToRenderer(potato[1][0], Renderer, 50, 400, NULL, 255);
            SurfaceToRenderer(potato[1][1], Renderer, 160, 400, NULL, 255);
            SurfaceToRenderer(potato[1][2], Renderer, 270, 400, NULL, 255);
            SurfaceToRenderer(potato[1][3], Renderer, 380, 400, NULL, 255);
        }
        else if (number>=CostH)
        {
            SurfaceToRenderer(potato[1][0], Renderer, 50, 400, NULL, 255);
            SurfaceToRenderer(potato[1][1], Renderer, 160, 400, NULL, 255);
            SurfaceToRenderer(potato[0][2], Renderer, 270, 400, NULL, 255);
            SurfaceToRenderer(potato[1][3], Renderer, 380, 400, NULL, 255);
        }
        else if (number>=CostT)
        {
            SurfaceToRenderer(potato[1][0], Renderer, 50, 400, NULL, 255);
            SurfaceToRenderer(potato[1][1], Renderer, 160, 400, NULL, 255);
            SurfaceToRenderer(potato[0][2], Renderer, 270, 400, NULL, 255);
            SurfaceToRenderer(potato[0][3], Renderer, 380, 400, NULL, 255);
        }
        else if (number>=CostP)
        {
            SurfaceToRenderer(potato[1][0], Renderer, 50, 400, NULL, 255);
            SurfaceToRenderer(potato[0][1], Renderer, 160, 400, NULL, 255);
            SurfaceToRenderer(potato[0][2], Renderer, 270, 400, NULL, 255);
            SurfaceToRenderer(potato[0][3], Renderer, 380, 400, NULL, 255);
        }
        else
        {
            SurfaceToRenderer(potato[0][0], Renderer, 50, 400, NULL, 255);
            SurfaceToRenderer(potato[0][1], Renderer, 160, 400, NULL, 255);
            SurfaceToRenderer(potato[0][2], Renderer, 270, 400, NULL, 255);
            SurfaceToRenderer(potato[0][3], Renderer, 380, 400, NULL, 255);
        }
    }
}

void material::FadeIn(SDL_Renderer *Renderer)
{
    a+=O_FADE_COE;
    for (int i=Digits-1;i>=0;i--)
    {
        SDL_Rect renderquad={x+(Digits-1-i)*Image[0]->w, y, Image[0]->w, Image[0]->h};
        Texture=SDL_CreateTextureFromSurface(Renderer, Image[0]);
        SDL_SetTextureAlphaMod(Texture, a);
        SDL_RenderCopy(Renderer, Texture, NULL, &renderquad );
        SDL_DestroyTexture(Texture);
        Texture=NULL;
    }
    if (type==0)
    {
        if (number>=CostM)
        {
            SurfaceToRenderer(potato[1][0], Renderer, 550, 400, NULL, a);
            SurfaceToRenderer(potato[1][1], Renderer, 660, 400, NULL, a);
            SurfaceToRenderer(potato[1][2], Renderer, 770, 400, NULL, a);
            SurfaceToRenderer(potato[1][3], Renderer, 880, 400, NULL, a);
        }
        else if (number>=CostH)
        {
            SurfaceToRenderer(potato[1][0], Renderer, 550, 400, NULL, a);
            SurfaceToRenderer(potato[1][1], Renderer, 660, 400, NULL, a);
            SurfaceToRenderer(potato[0][2], Renderer, 770, 400, NULL, a);
            SurfaceToRenderer(potato[1][3], Renderer, 880, 400, NULL, a);
        }
        else if (number>=CostT)
        {
            SurfaceToRenderer(potato[1][0], Renderer, 550, 400, NULL, a);
            SurfaceToRenderer(potato[1][1], Renderer, 660, 400, NULL, a);
            SurfaceToRenderer(potato[0][2], Renderer, 770, 400, NULL, a);
            SurfaceToRenderer(potato[0][3], Renderer, 880, 400, NULL, a);
        }
        else if (number>=CostP)
        {
            SurfaceToRenderer(potato[1][0], Renderer, 550, 400, NULL, a);
            SurfaceToRenderer(potato[0][1], Renderer, 660, 400, NULL, a);
            SurfaceToRenderer(potato[0][2], Renderer, 770, 400, NULL, a);
            SurfaceToRenderer(potato[0][3], Renderer, 880, 400, NULL, a);
        }
        else
        {
            SurfaceToRenderer(potato[0][0], Renderer, 550, 400, NULL, a);
            SurfaceToRenderer(potato[0][1], Renderer, 660, 400, NULL, a);
            SurfaceToRenderer(potato[0][2], Renderer, 770, 400, NULL, a);
            SurfaceToRenderer(potato[0][3], Renderer, 880, 400, NULL, a);
        }
    }
    else if (type==1)
    {
        if (number>=CostM)
        {
            SurfaceToRenderer(potato[1][0], Renderer, 50, 400, NULL, a);
            SurfaceToRenderer(potato[1][1], Renderer, 160, 400, NULL, a);
            SurfaceToRenderer(potato[1][2], Renderer, 270, 400, NULL, a);
            SurfaceToRenderer(potato[1][3], Renderer, 380, 400, NULL, a);
        }
        else if (number>=CostH)
        {
            SurfaceToRenderer(potato[1][0], Renderer, 50, 400, NULL, a);
            SurfaceToRenderer(potato[1][1], Renderer, 160, 400, NULL, a);
            SurfaceToRenderer(potato[0][2], Renderer, 270, 400, NULL, a);
            SurfaceToRenderer(potato[1][3], Renderer, 380, 400, NULL, a);
        }
        else if (number>=CostT)
        {
            SurfaceToRenderer(potato[1][0], Renderer, 50, 400, NULL, a);
            SurfaceToRenderer(potato[1][1], Renderer, 160, 400, NULL, a);
            SurfaceToRenderer(potato[0][2], Renderer, 270, 400, NULL, a);
            SurfaceToRenderer(potato[0][3], Renderer, 380, 400, NULL, a);
        }
        else if (number>=CostP)
        {
            SurfaceToRenderer(potato[1][0], Renderer, 50, 400, NULL, a);
            SurfaceToRenderer(potato[0][1], Renderer, 160, 400, NULL, a);
            SurfaceToRenderer(potato[0][2], Renderer, 270, 400, NULL, a);
            SurfaceToRenderer(potato[0][3], Renderer, 380, 400, NULL, a);
        }
        else
        {
            SurfaceToRenderer(potato[0][0], Renderer, 50, 400, NULL, a);
            SurfaceToRenderer(potato[0][1], Renderer, 160, 400, NULL, a);
            SurfaceToRenderer(potato[0][2], Renderer, 270, 400, NULL, a);
            SurfaceToRenderer(potato[0][3], Renderer, 380, 400, NULL, a);
        }
    }
}

bool material::SucSummon(int type)
{
    if (type==G_Potany)
    {
        if (number>=CostP)
        {
            number-=CostP;
            return true;
        }
        else
            return false;
    }
    else if (type==G_Tankitato)
    {
        if (number>=CostT)
        {
            number-=CostT;
            return true;
        }
        else
            return false;
    }
    else if (type==G_Magitato)
    {
        if (number>=CostM)
        {
            number-=CostM;
            return true;
        }
        else
            return false;
    }
    else if (type==G_Healitato)
    {
        if (number>=CostH)
        {
            number-=CostH;
            return true;
        }
        else
            return false;
    }
    if (type==E_Potany)
    {
        if (number>=CostP)
        {
            number-=CostP;
            return true;
        }
        else
            return false;
    }
    else if (type==E_Tankitato)
    {
        if (number>=CostT)
        {
            number-=CostT;
            return true;
        }
        else
            return false;
    }
    else if (type==E_Magitato)
    {
        if (number>=CostM)
        {
            number-=CostM;
            return true;
        }
        else
            return false;
    }
    else if (type==E_Healitato)
    {
        if (number>=CostH)
        {
            number-=CostH;
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

bool material::LevelUp(int type)
{
    switch (type)
    {
        case G_Potany:
            if (number>=LvUpCostP)
            {
                number-=LvUpCostP;
                return true;
            }
            else
                return  false;
        case G_Tankitato:
            if (number>=LvUpCostT)
            {
                number-=LvUpCostT;
                return true;
            }
            else
                return  false;
        case G_Magitato:
            if (number>=LvUpCostM)
            {
                number-=LvUpCostM;
                return true;
            }
            else
                return  false;
        case G_Healitato:
            if (number>=LvUpCostH)
            {
                number-=LvUpCostH;
                return true;
            }
            else
                return  false;
        case E_Potany:
            if (number>=LvUpCostP)
            {
                number-=LvUpCostP;
                return true;
            }
            else
                return  false;
        case E_Tankitato:
            if (number>=LvUpCostT)
            {
                number-=LvUpCostT;
                return true;
            }
            else
                return  false;
        case E_Magitato:
            if (number>=LvUpCostM)
            {
                number-=LvUpCostM;
                return true;
            }
            else
                return  false;
        case E_Healitato:
            if (number>=LvUpCostH)
            {
                number-=LvUpCostH;
                return true;
            }
            else
                return  false;
        default:
            return false;
    }
}

house::house(int p, int q, int type) :house_x(p), house_y(q)
{
    hp=99;
    a=0;
    gore=type;
    p_levelup=-1;
    t_levelup=-1;
    m_levelup=-1;
    h_levelup=-1;
    for (int i=0;i<2;i++)
    {
        for (int j=0;j<4;j++)
        {
            levelup[i][j]=0;
        }
    }
    if (gore==0)
    {
        Image=IMG_Load("ghouse_0.png");
        Color[0][0]=IMG_Load("gcolor_00.png");
        Color[0][1]=IMG_Load("gcolor_01.png");
        Color[0][2]=IMG_Load("gcolor_02.png");
        Color[0][3]=IMG_Load("gcolor_03.png");
        Color[1][0]=IMG_Load("gcolor_10.png");
        Color[1][1]=IMG_Load("gcolor_11.png");
        Color[1][2]=IMG_Load("gcolor_12.png");
        Color[1][3]=IMG_Load("gcolor_13.png");
        number_x=GMaterial_X;
        number_y=85;
    }
    else if (gore==1)
    {
        Image=IMG_Load("ehouse_0.png");
        Color[0][0]=IMG_Load("ecolor_00.png");
        Color[0][1]=IMG_Load("ecolor_01.png");
        Color[0][2]=IMG_Load("ecolor_02.png");
        Color[0][3]=IMG_Load("ecolor_03.png");
        Color[1][0]=IMG_Load("ecolor_10.png");
        Color[1][1]=IMG_Load("ecolor_11.png");
        Color[1][2]=IMG_Load("ecolor_12.png");
        Color[1][3]=IMG_Load("ecolor_13.png");
        number_x=EMaterial_X;
        number_y=85;
    }
    Number[0]=IMG_Load("0.png");
    Number[1]=IMG_Load("1.png");
    Number[2]=IMG_Load("2.png");
    Number[3]=IMG_Load("3.png");
    Number[4]=IMG_Load("4.png");
    Number[5]=IMG_Load("5.png");
    Number[6]=IMG_Load("6.png");
    Number[7]=IMG_Load("7.png");
    Number[8]=IMG_Load("8.png");
    Number[9]=IMG_Load("9.png");
    Slash=IMG_Load("slash.png");
}

void house::FadeIn(SDL_Renderer *Renderer)
{
    a+=O_FADE_COE;
    SurfaceToRenderer(Image, Renderer, house_x, house_y, NULL, a);
    for (int i=4;i>=0;i--)
    {
        if ((i==4) || (i==3))
            SurfaceToRenderer(Number[9], Renderer, number_x+(4-i)*Number[0]->w, number_y, NULL, a);
        else if (i==2)
            SurfaceToRenderer(Slash, Renderer, number_x+(4-i)*Number[0]->w, number_y, NULL, a);
        else
        {
            int which=(int)(((int)((int)(LOADMAX/pow(10,i))*pow(10,i))-(int)((int)(LOADMAX/pow(10,i+1))*pow(10,i+1)))/pow(10,i));
            SurfaceToRenderer(Number[which], Renderer, number_x+(4-i)*Number[0]->w, number_y, NULL, a);
        }
    }
}

void house::Print(SDL_Renderer *Renderer)
{
    SurfaceToRenderer(Image, Renderer, house_x, house_y, NULL, 255);
    for (int i=0;i<2;i++)
    {
        for (int j=0;j<8;j++)
        {
            if (levelup[i][j]==1)
                SurfaceToRenderer(Color[i][j], Renderer, house_x, house_y, NULL, 255);
        }
    }
    for (int i=4;i>=0;i--)
    {
        SDL_Rect renderquad={number_x+(4-i)*Number[0]->w, number_y, Number[0]->w, Number[0]->h};
        if ((i==4) || i==3)
        {
            int which=(int)(((int)((int)(hp/pow(10,i-3))*pow(10,i-3))-(int)((int)(hp/pow(10,i-2))*pow(10,i-2)))/pow(10,i-3));
            Texture=SDL_CreateTextureFromSurface(Renderer, Number[which]);
            SDL_RenderCopy(Renderer, Texture, NULL, &renderquad );
            SDL_DestroyTexture(Texture);
            Texture=NULL;
        }
        else if (i==2)
        {
            Texture=SDL_CreateTextureFromSurface(Renderer, Slash);
            SDL_RenderCopy(Renderer, Texture, NULL, &renderquad );
            SDL_DestroyTexture(Texture);
            Texture=NULL;
        }
        else
        {
            int which=(int)(((int)((int)(LOADMAX/pow(10,i))*pow(10,i))-(int)((int)(LOADMAX/pow(10,i+1))*pow(10,i+1)))/pow(10,i));
            Texture=SDL_CreateTextureFromSurface(Renderer, Number[which]);
            SDL_RenderCopy(Renderer, Texture, NULL, &renderquad );
            SDL_DestroyTexture(Texture);
            Texture=NULL;
        }
    }
    
}

