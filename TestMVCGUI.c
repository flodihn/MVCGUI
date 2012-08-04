#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "gfx.h"
#include "font.h"
#include "time.h"

#include "mvcgui.h"

void callback_test(MVCGUI_Element* element,char *name)
{
    if(strcmp(name,"TestButton2")==0)
    exit(0);
}

void run_test()
{
    int done = 0;
    SDL_Event event;
    int mousex = 0;
    int mousey = 0;

    int button1x = 0;
    int buttony = 0;
    int button2x = 200;

    int layoutx = 100;
    int layouty = 100;

    char *labeltext = "My Label";

    char *button = "data/button.png";
    char *button_pressed = "data/button_pressed.png";
    char *button_mouseover = "data/button_mouseover.png";

    MVCGUI_Layout *layout = MVCGUI_init((void*)screen);
    MVCGUI_create_button(layout, &button1x, &buttony, "TestButton", &button,
        &button_pressed, &button_mouseover);
    MVCGUI_create_button(layout, &button2x, &buttony, "TestButton2", &button,
        &button_pressed, &button_mouseover);
    MVCGUI_create_label(layout, &layoutx, &layouty, &labeltext);

    MCVGUI_element_callback_mouse_click(layout,callback_test);
    while(!done)
    {
        if(!SDL_PollEvent(&event) > 0) continue;

    Clear_Surface(screen);
        switch (event.type)
        {
            case SDL_KEYUP:
            {
                if ( event.key.keysym.sym == SDLK_ESCAPE )
                {
                    done = 1;
                }
                if ( event.key.keysym.sym == SDLK_a )
                {
                    buttony+=2;
                }
            }break;

            case SDL_MOUSEMOTION:
            {
                SDL_GetMouseState(&mousex, &mousey);
                MVCGUI_inject_mouse_move(layout, mousex, mousey, 0);
            }break;

            case SDL_MOUSEBUTTONUP:
            {
                if( event.button.button == SDL_BUTTON_LEFT)
                {
                    MVCGUI_inject_mouse_button(layout,
                        MVCGUI_MOUSE_BUTTON_LEFT_UP);
                }

            }break;

            case SDL_MOUSEBUTTONDOWN:
            {
                if( event.button.button == SDL_BUTTON_LEFT)
                {
                    MVCGUI_inject_mouse_button(layout,
                        MVCGUI_MOUSE_BUTTON_LEFT_DOWN);
                }
            }break;

        default:break;
        }

        MVCGUI_render(layout);

        SDL_Flip(screen);

    }
}

int main(int argc, char *argv[])
{
    int i=0;
	//if we fail to initiate SDL video
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return 0;

    screen = SDL_SetVideoMode( 1280,768, 32, SDL_DOUBLEBUF | SDL_HWSURFACE );

    if(screen==0)
        return 0;

    for(i=0;i<NUM_CHARACTERS;i++)
    {
        cleanfont_space[i] = 8;
    }
    Get_Anim("data/cleanfont.png",TempImage,font_clean,0,0,8,8,NUM_CHARACTERS,16,1);
srand(time(0));

    run_test();

    return 0;
}

