/**
 * @file
 * @author  Johan Forsblom & Christian Flodihn
 * @version 1.0
 *
 * @section LICENSE
 *
 * Copyright (c) <''2012''> <''Johan Forsblom & Christian Flodihn''>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 *  distribution.
 *
 * @section DESCRIPTION
 *
 *
 */

#ifndef _MVCGUI_H
#define _MVCGUI_H

#define MAX_ELEMENTS   1024

/** \enum MVCGUI_Type
 * \brief The different MVCGUI element types. I.e button, label etc.
 */
typedef enum MVCGUI_Type{
    MVCGUI_BUTTON,
    MVCGUI_LABEL
} MVCGUI_Type;


/** \enum MVCGUI_Mouse_Button
 * \brief The different mousebuttons that can be pressed.
 */
typedef enum MVCGUI_Mouse_Button{
    MVCGUI_MOUSE_BUTTON_LEFT_DOWN,
    MVCGUI_MOUSE_BUTTON_LEFT_UP,
    MVCGUI_MOUSE_BUTTON_RIGHT_DOWN,
    MVCGUI_MOUSE_BUTTON_RIGHT_UP,
    MVCGUI_MOUSE_BUTTON_MIDDLE_DOWN,
    MVCGUI_MOUSE_BUTTON_MIDDLE_UP,
    MVCGUI_MOUSE_BUTTON_WHEEL_DOWN,
    MVCGUI_MOUSE_BUTTON_WHEEL_UP
} MVCGUI_Mouse_Button;

/** \struct MVCGUI_Element
 * \brief Generic base struct for all MVCGUI elements.
 */
typedef struct MVCGUI_Element
{
    void *element;
    MVCGUI_Type type;

} MVCGUI_Element;

/** \struct MVCGUI_Layout
 * \brief Structure of one layout, containing other GUI elements.
 */
typedef struct MVCGUI_Layout
{
    unsigned int num_elements;
    int mousex;
    int mousey;
    int mousewheel;
    void *display;

    void (*callback_mouse_click)(MVCGUI_Element*, char *name);

    MVCGUI_Element elements[MAX_ELEMENTS];
} MVCGUI_Layout;

/**
 * Create a simple button
 *
 * This creates a button on the screen with a callback. You can define
 * its size & coordinates with the button.rect. image_filename is mandatory,
 * pressed & mouseover can be NULL.
 *
 * @param  layout The layout where you want to store the button.
 * @param  x Pointer to the button's x position
 * @param  y Pointer to the button's y position
 * @param  button_name An unique ID name for the button element.
 * @param  image_filename The filename of the image you want on the button.
 * @param  image_pressed_filename The filename of the image you want when the
 * button is pressed
 * @param  image_mouseover_filename The filename of the image you want when the
 * mouse is over the button
 * @return void
 */
void MVCGUI_create_button(MVCGUI_Layout *layout, int *x, int *y,
        char *button_name, char **image_filename,
        char **image_pressed_filename, char **image_mouseover_filename);

/**
 *  Create a text label
 *
 * @param  layout The layout where you want to place the label
 * @param  label_text Point to the text which will be displayed.
 * @param  x Pointer to the label's x position
 * @param  y Pointer to the label's y position
 * @return void
 */
void MVCGUI_create_label(MVCGUI_Layout *layout, int *x, int *y,
        char **label_text);

/**
 * Element Callback
 *
 * Thiss callback is called when you have clicked with the mouse
 *
 * @param  layout The layout where you want to store the button.
 * @param  funct_pointer The function pointer that shall be called.
 * @return void
 */
void MCVGUI_element_callback_mouse_click(MVCGUI_Layout *layout,
        void (*funct_pointer)(MVCGUI_Element*, char *name));

/**
 * Initialize MVCGUI
 *
 * This must be called first before using any other MVCGUI function.
 *
 * @param  display The screen you want to use for rendering, for example
 * an SDL_Surface.
 * @return MVCGUI_Layout
 */
MVCGUI_Layout *MVCGUI_init(void *display);

/**
 * Render
 *
 * This function renders the the layout on the display
 *
 * @param layout
 * @return void
 */
void MVCGUI_render(MVCGUI_Layout *layout);

/**
 * Inject Mouse
 *
 * This function injects the mouse movement and the mousewheel.
 *
 * @param layout
 * @param x The absolute mouse x coordinate
 * @param y The aboslute mouse y coordinate
 * @param mousewheel The relative mousewheel position
 * @return void
 */
void MVCGUI_inject_mouse_move(MVCGUI_Layout *layout, unsigned int x,
    unsigned int y, int mousewheel);

/**
 * Inject Mouse
 *
 * This function injects the mouse movement and the mousewheel.
 *
 * @param layout
 * @param button the mouse button you want inject
 * @return void
 */
void MVCGUI_inject_mouse_button(MVCGUI_Layout *layout,
    MVCGUI_Mouse_Button button);
#endif
