#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "mvcgui.h"
#include "mvcgui_sdl.h"
#include "gfx.h"
#include "font.h"

//These are private prototypes

void render_button(MVCGUI_SDL_Button *button,SDL_Surface *display);

void render_label(MVCGUI_SDL_Label *label, SDL_Surface* display);

void handle_button_clicked(MVCGUI_Layout *layout, MVCGUI_Element *curr_element,
        MVCGUI_Mouse_Button mouse_button);

//These are the API functions
MVCGUI_Layout *MVCGUI_init(void *display)
{
    MVCGUI_Layout *layout = malloc(sizeof(MVCGUI_Layout));
    layout->num_elements = 0;
    layout->display = display;
    layout->callback_mouse_click = NULL;
    return layout;
}

//These are private help functions
void create_element(MVCGUI_Layout *layout, void *element,
        enum MVCGUI_Type type)
{
    layout->elements[layout->num_elements].type = type;
    layout->elements[layout->num_elements].element = element;
    layout->num_elements++;

    if(layout->num_elements >= MAX_ELEMENTS)
    {
        exit(1);
    }
}

void MVCGUI_render(MVCGUI_Layout *layout)
{
    int i = 0;
    MVCGUI_Element *curr_element;

    for(i = 0; i < layout->num_elements; ++i)
    {
        curr_element = &layout->elements[i];

        if(curr_element->type == MVCGUI_BUTTON)
        {
            render_button(
                (MVCGUI_SDL_Button*) curr_element->element,
                (SDL_Surface*) layout->display
            );
        }
        else if(curr_element->type == MVCGUI_LABEL)
        {
            render_label((MVCGUI_SDL_Label*) curr_element->element,
                (SDL_Surface*) layout->display);
        }

    }
}

void MVCGUI_inject_mouse_move(MVCGUI_Layout *layout,unsigned int x,
    unsigned int y, int mousewheel)
{
    layout->mousex = x;
    layout->mousey = y;
    SDL_WarpMouse(layout->mousex, layout->mousey);
}

void MVCGUI_inject_mouse_button(MVCGUI_Layout *layout,
        MVCGUI_Mouse_Button mouse_button)
{

    MVCGUI_Element *curr_element;

    int i;
    for(i = 0; i < layout->num_elements; ++i)
    {
        curr_element = &layout->elements[i];
        if(curr_element->type == MVCGUI_BUTTON)
        {
            handle_button_clicked(layout, curr_element, mouse_button);
        }
    }
}


void MCVGUI_element_callback_mouse_click(MVCGUI_Layout *layout,
        void (*funct_pointer)(MVCGUI_Element*, char *name))
{
    layout->callback_mouse_click = funct_pointer;
}

int are_rects_overlapping(MVCGUI_SDL_Rect *a, MVCGUI_SDL_Rect *b)
{
	if(*b->x + b->w < *a->x)	return 0;
	if(*b->x > *a->x + a->w)	return 0;
	if(*b->y + b->h < *a->y)	return 0;
	if(*b->y > *a->y + a->h)	return 0;

	return 1;
}

void setup_rectangle(MVCGUI_SDL_Rect *rect, int *x, int *y, int width,
        int height)
{
    rect->x = x;
    rect->y = y;
    rect->w = width;
    rect->h = height;
}
