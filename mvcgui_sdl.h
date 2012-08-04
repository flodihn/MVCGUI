#ifndef _MVCGUI_SDL_H_
#define _MVCGUI_SDL_H_

#include <stdbool.h>

#define MAX_ELEMENTS        1024
#define MVCGUI_DEBUG        1


typedef struct MVCGUI_SDL_Rect
{
    int *x;
    int *y;
    int w;
    int h;
}MVCGUI_SDL_Rect;


typedef struct MVCGUI_SDL_Button
{
    MVCGUI_SDL_Rect rect;
    SDL_Surface *image;
    SDL_Surface *image_pressed;
    SDL_Surface *image_mouseover;
    char filename_cache[255];
    char filename_pressed_cache[255];
    char filename_mouseover_cache[255];
    char **model_ptr;
    char **model_pressed_ptr;
    char **model_mouseover_ptr;
    bool pressed;
    char button_name[128];

    #if MVCGUI_DEBUG
        char debug_str[255];
    #endif
} MVCGUI_SDL_Button;

typedef struct MVCGUI_SDL_Label
{
    int *x;
    int *y;
    char **model_ptr;
}MVCGUI_SDL_Label;



int are_rects_overlapping(MVCGUI_SDL_Rect *a, MVCGUI_SDL_Rect *b);

void setup_rectangle(MVCGUI_SDL_Rect *rect, int *x, int *y, int width,
        int height);

void create_element(MVCGUI_Layout *layout, void *element,
        enum MVCGUI_Type type);

#endif


