#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "mvcgui.h"
#include "mvcgui_sdl.h"
#include "gfx.h"
#include "font.h"
#include "assert.h"

void render_button(MVCGUI_SDL_Button *button, SDL_Surface* display)
{
    if(strcmp(*button->model_ptr, button->filename_cache) !=0)
    {
        SDL_FreeSurface(button->image);
        button->image = IMG_Load(*button->model_ptr);
        sprintf(button->filename_cache,"%s",*button->model_ptr);
    }
    if(button->pressed==true && button->image_pressed != NULL)
    {
        Draw_Image(button->image_pressed, display,
            *button->rect.x,
            *button->rect.y);
    }
    if(button->pressed==false)
    {
        Draw_Image(button->image, display, *button->rect.x, *button->rect.y);
    }

    #if MVCGUI_DEBUG
        Font_String(*button->rect.x, *button->rect.y, button->button_name, screen,
            font_clean,cleanfont_space);
    #endif
}

void handle_button_clicked(MVCGUI_Layout *layout, MVCGUI_Element *curr_element,
        MVCGUI_Mouse_Button mouse_button)
{
    MVCGUI_SDL_Rect rect_mouse;
    setup_rectangle(&rect_mouse, (int*) &layout->mousex, (int*) &layout->mousey, 1, 1);
    MVCGUI_SDL_Button *sdl_button = (MVCGUI_SDL_Button*) curr_element->element;

    if(are_rects_overlapping(&rect_mouse, &sdl_button->rect) &&
            mouse_button == MVCGUI_MOUSE_BUTTON_LEFT_DOWN)
    {
        sdl_button->pressed = true;
    }
    else if(sdl_button->pressed == true)
    {
        if(layout->callback_mouse_click != NULL &&
                are_rects_overlapping(&rect_mouse, &sdl_button->rect))
        {
            layout->callback_mouse_click(curr_element, sdl_button->button_name);
        }
        sdl_button->pressed = false;
    }
}


void MVCGUI_create_button(MVCGUI_Layout *layout, int *x, int *y,
        char *button_name, char **image_filename,
        char **image_pressed_filename, char **image_mouseover_filename)
{

    assert(button_name!=NULL);
    assert(*image_filename != NULL);

    MVCGUI_SDL_Button *new_button = malloc(sizeof(MVCGUI_SDL_Button));
    new_button->image = IMG_Load(*image_filename);
    sprintf(new_button->button_name,"%s", button_name);
    new_button->pressed = false;

    setup_rectangle(&new_button->rect, x, y, new_button->image->w,
            new_button->image->h);

    new_button->model_ptr = image_filename;
    sprintf(new_button->filename_cache,"%s",*image_filename);

    if(*image_pressed_filename != NULL)
    {
        new_button->image_pressed = IMG_Load(*image_pressed_filename);
        new_button->model_pressed_ptr = image_pressed_filename;
        sprintf(new_button->filename_pressed_cache, "%s",
                *image_pressed_filename);
    }
    if(*image_mouseover_filename != NULL)
    {
        new_button->image_mouseover = IMG_Load(*image_mouseover_filename);
        new_button->model_mouseover_ptr = image_mouseover_filename;
        sprintf(new_button->filename_mouseover_cache, "%s",
                *image_mouseover_filename);
    }

    #if MVCGUI_DEBUG
    sprintf(new_button->debug_str, "x:%d,y:%d", *new_button->rect.x,
        *new_button->rect.y);
    #endif

    create_element(layout, (MVCGUI_Element*) new_button, MVCGUI_BUTTON);

}
