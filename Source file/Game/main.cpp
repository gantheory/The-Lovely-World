#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include "parameters.h"
#include "basicfunctoins.h"
#include "potany.h"
#include "tankitato.h"
#include "magitato.h"
#include "healitato.h"
#include "epotany.h"
#include "etankitato.h"
#include "emagitato.h"
#include "ehealitato.h"
#include <iostream>
using namespace std;

int main()
{
    //The window we'll be rendering to
    SDL_Window *Window=NULL;
    //The window renderer
    SDL_Renderer *Renderer=NULL;
    //Music that will be played
    Mix_Music *Music=NULL;
    
    //Create a window
    Window=SDL_CreateWindow("The Lovely World",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    //Create renderer for window
    Renderer=SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 65536 );
    Music=Mix_LoadMUS("Original 1st.wav");
    Mix_PlayMusic( Music, -1 );
    
    opening open;
    potatoqueue poqueue;
    help h;
    
    bool quit=false, Opening=true, Help=false, EndOpening=false, EndGame=false;
    
    SDL_Event e;
    while (!quit)
    {
        if (Help)
        {
            SDL_RenderClear(Renderer);
            h.Print(Renderer);
            SDL_RenderPresent(Renderer);
            
            while (SDL_PollEvent(&e)!=0)
            {
                if (e.type==SDL_QUIT)
                    quit=true;
                else
                {
                    if (e.type==SDL_KEYUP && (EndOpening==false))
                    {
                        switch(e.key.keysym.sym)
                        {
                            case SDLK_RETURN:
                                Help=false; break;
                            case SDLK_RIGHT:
                                h.Select++;
                                h.Select%=5; break;
                            case SDLK_LEFT:
                                if (h.Select>0)
                                    h.Select--;
                                else if (h.Select==0)
                                    h.Select=4; break;
                                
                        }
                    }
                }
            }
        }
        else if (Opening)
        {
            SDL_RenderClear(Renderer);
            
            LoadImageToRenderer("background_default.jpg", Renderer, 0, 0);
            if (!EndOpening)
                open.Print(Renderer);
            else
            {
                if (open.a!=0)
                    open.EndPrint_FadeOut(Renderer);
                if (open.gx!=SCREEN_WIDTH)
                    open.EndPrint_Move(Renderer);
                if ((open.a==0) && (open.gx==SCREEN_WIDTH))
                    Opening=false;
            }
            
            SDL_RenderPresent(Renderer);

            while (SDL_PollEvent(&e)!=0)
            {
                if (e.type==SDL_QUIT)
                    quit=true;
                else
                {
                    if (e.type==SDL_KEYUP && (EndOpening==false))
                    {
                        switch(e.key.keysym.sym)
                        {
                            case SDLK_RETURN:
                                if (open.SelectWhich==0)
                                {
                                    EndOpening=true;
                                    Mix_HaltMusic();
                                    Music=Mix_LoadMUS("Original 2nd.wav");
                                    Mix_PlayMusic( Music, -1 );
                                }
                                else if (open.SelectWhich==1)
                                    Help=true;
                                else if (open.SelectWhich==2)
                                    quit=true;
                                break;
                            case SDLK_UP:
                                if (open.SelectWhich==2)
                                    open.SelectWhich=0;
                                else if (open.SelectWhich==1)
                                    open.SelectWhich=2;
                                else if (open.SelectWhich==0)
                                    open.SelectWhich=2;
                                open.change=true;
                                break;
                            case SDLK_RIGHT:
                                if (open.SelectWhich==0)
                                    open.SelectWhich=1;
                                else if (open.SelectWhich==1)
                                    open.SelectWhich=0;
                                else if (open.SelectWhich==2)
                                    open.SelectWhich=1;
                                open.change=true;
                                break;
                            case SDLK_LEFT:
                                if (open.SelectWhich==1)
                                    open.SelectWhich=0;
                                else if (open.SelectWhich==0)
                                    open.SelectWhich=1;
                                else if (open.SelectWhich==2)
                                    open.SelectWhich=0;
                                open.change=true;
                                break;
                            case SDLK_DOWN:
                                if ((open.SelectWhich==1) || (open.SelectWhich==0))
                                    open.SelectWhich=2;
                                else if (open.SelectWhich==2)
                                    open.SelectWhich=0;
                                open.change=true;
                                break;
                        }
                    }
                }

            }
        }
        else if (EndGame)
        {
            SDL_RenderClear(Renderer);
            LoadImageToRenderer("background_default.jpg", Renderer, 0, 0);
            
            poqueue.gh.Print(Renderer);
            poqueue.eh.Print(Renderer);
            poqueue.gm.Print(Renderer);
            poqueue.em.Print(Renderer);
            poqueue.EndPrint(Renderer);
            
            SDL_RenderPresent(Renderer);
            
            while (SDL_PollEvent(&e)!=0)
            {
                if (e.type==SDL_QUIT)
                    quit=true;
                else
                {
                    if (e.type==SDL_KEYUP)
                    {
                        switch (e.key.keysym.sym)
                        {
                            case SDLK_RETURN:
                                quit=true;
                        }
                    }
                }
            }
        }
        else
        {
            //Clear screen
            SDL_RenderClear(Renderer);
            LoadImageToRenderer("background_default.jpg", Renderer, 0, 0);
            if ((poqueue.gm.a!=255) || (poqueue.em.a!=255))
            {
                poqueue.gm.FadeIn(Renderer);
                poqueue.em.FadeIn(Renderer);
                poqueue.gh.FadeIn(Renderer);
                poqueue.eh.FadeIn(Renderer);
            }
            else
            {
                poqueue.gh.Print(Renderer);
                poqueue.eh.Print(Renderer);
                poqueue.gm.Print(Renderer);
                poqueue.em.Print(Renderer);
                poqueue.Print(Renderer);
            }
            
            if ((poqueue.gh.hp==0) || (poqueue.eh.hp==0))
                EndGame=true;
            
            //Update screen
            SDL_RenderPresent(Renderer);
            
            while (SDL_PollEvent(&e)!=0)
            {
                if (e.type==SDL_QUIT)
                    quit=true;
                else
                {
                    if (e.type==SDL_KEYUP)
                    {
                        switch (e.key.keysym.sym)
                        {
                            case SDLK_u:
                                if (poqueue.gm.SucSummon(G_Potany))
                                    poqueue.Push(G_Potany); break;
                            case SDLK_i:
                                if (poqueue.gm.SucSummon(G_Tankitato))
                                    poqueue.Push(G_Tankitato); break;
                            case SDLK_o:
                                if (poqueue.gm.SucSummon(G_Magitato))
                                    poqueue.Push(G_Magitato); break;
                            case SDLK_p:
                                if (poqueue.gm.SucSummon(G_Healitato))
                                    poqueue.Push(G_Healitato); break;
                            case SDLK_q:
                                if (poqueue.em.SucSummon(E_Potany))
                                    poqueue.Push(E_Potany); break;
                            case SDLK_w:
                                if (poqueue.em.SucSummon(E_Tankitato))
                                    poqueue.Push(E_Tankitato); break;
                            case SDLK_e:
                                if (poqueue.em.SucSummon(E_Magitato))
                                    poqueue.Push(E_Magitato); break;
                            case SDLK_r:
                                if (poqueue.em.SucSummon(E_Healitato))
                                    poqueue.Push(E_Healitato); break;
                            case SDLK_a:
                                if (poqueue.eh.p_levelup<1)
                                {
                                    if (poqueue.em.LevelUp(E_Potany))
                                    {
                                        poqueue.LevelUp(E_Potany);
                                        poqueue.eh.p_levelup++;
                                        poqueue.eh.levelup[poqueue.eh.p_levelup][0]++;
                                    }
                                } break;
                            case SDLK_s:
                                if (poqueue.eh.t_levelup<1)
                                {
                                    if (poqueue.em.LevelUp(E_Tankitato))
                                    {
                                        poqueue.LevelUp(E_Tankitato);
                                        poqueue.eh.t_levelup++;
                                        poqueue.eh.levelup[poqueue.eh.t_levelup][1]++;
                                    }
                                } break;
                            case SDLK_d:
                                if (poqueue.eh.m_levelup<1)
                                {
                                    if (poqueue.em.LevelUp(E_Magitato))
                                    {
                                        poqueue.LevelUp(E_Magitato);
                                        poqueue.eh.m_levelup++;
                                        poqueue.eh.levelup[poqueue.eh.m_levelup][2]++;
                                    }
                                } break;
                            case SDLK_f:
                                if (poqueue.eh.h_levelup<1)
                                {
                                    if (poqueue.em.LevelUp(E_Healitato))
                                    {
                                        poqueue.LevelUp(E_Healitato);
                                        poqueue.eh.h_levelup++;
                                        poqueue.eh.levelup[poqueue.eh.h_levelup][3]++;
                                    }
                                } break;
                            case SDLK_h:
                                if (poqueue.gh.p_levelup<1)
                                {
                                    if (poqueue.gm.LevelUp(G_Potany))
                                    {
                                        poqueue.LevelUp(G_Potany);
                                        poqueue.gh.p_levelup++;
                                        poqueue.gh.levelup[poqueue.gh.p_levelup][0]++;
                                    }
                                } break;
                            case SDLK_j:
                                if (poqueue.gh.t_levelup<1)
                                {
                                    if (poqueue.gm.LevelUp(G_Tankitato))
                                    {
                                        poqueue.LevelUp(G_Tankitato);
                                        poqueue.gh.t_levelup++;
                                        poqueue.gh.levelup[poqueue.gh.t_levelup][1]++;
                                    }
                                } break;
                            case SDLK_k:
                                if (poqueue.gh.m_levelup<1)
                                {
                                    if (poqueue.gm.LevelUp(G_Magitato))
                                    {
                                        poqueue.LevelUp(G_Magitato);
                                        poqueue.gh.m_levelup++;
                                        poqueue.gh.levelup[poqueue.gh.m_levelup][2]++;
                                    }
                                } break;
                            case SDLK_l:
                                if (poqueue.gh.h_levelup<1)
                                {
                                    if (poqueue.gm.LevelUp(G_Healitato))
                                    {
                                        poqueue.LevelUp(G_Healitato);
                                        poqueue.gh.h_levelup++;
                                        poqueue.gh.levelup[poqueue.gh.h_levelup][3]++;
                                    }
                                } break;
                            case SDLK_m:
                                //If the music is paused
                                if( Mix_PausedMusic() == 1 )
                                {
                                    //Resume the music
                                    Mix_ResumeMusic();
                                }
                                //If the music is playing
                                else
                                {
                                    //Pause the music
                                    Mix_PauseMusic();
                                }
                        }
                    }
                }
            }
        }
    }
    
    poqueue.free();
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    Renderer=NULL;
    Window=NULL;
    
    Mix_Quit();
    SDL_Quit();
    IMG_Quit();
}