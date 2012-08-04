#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "mvcgui.h"
#include "mvcgui_sdl.h"
#include "gfx.h"
#include "font.h"

void render_label(MVCGUI_SDL_Label *label, SDL_Surface* display)
{
    Font_String(*label->x, *label->y, *label->model_ptr, display,
        font_clean, cleanfont_space);
}

void MVCGUI_create_label(MVCGUI_Layout *layout, int *x, int *y,
        char **label_text)
{
    MVCGUI_SDL_Label *new_label = malloc(sizeof(MVCGUI_SDL_Label));
    new_label->model_ptr = label_text;
    new_label->x = x;
    new_label->y = y;

    create_element(layout, (MVCGUI_Element*) new_label, MVCGUI_LABEL);
}
