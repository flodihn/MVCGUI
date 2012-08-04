#ifndef _FONT_H_
#define _FONT_H_

#define MAX_MESSAGE_STRING_LENGTH	512	    //max string length

#define NUM_CHARACTERS 96			        //number of charecters in font

SDL_Surface *font_clean[NUM_CHARACTERS];    //a surface for "cleanfont"
SDL_Surface *font_clean_large[NUM_CHARACTERS];    //a surface for "cleanfont"

SDL_Surface *speach_font[NUM_CHARACTERS];

	//How much space there should be between each character.
	int cleanfont_space[NUM_CHARACTERS];
	int speachfont_space[NUM_CHARACTERS];

//Struct to handle player message input
typedef struct chatmessage_
{
	char message[MAX_MESSAGE_STRING_LENGTH];	//players message
	int pos;					                //position in the message
	int chat_enabled;				            //If the chat is enabled or not
	int send_message;				            //Flag to send the message

}Chat_Message;

Chat_Message ChatMessage;

//this function draws a string of letters on the desired surface
int Font_String(int x,int y,char *string,SDL_Surface *surface,SDL_Surface *fnt[], int space[]);

//this function takes keyboard input from the user
void User_Message(SDL_Event event,int max_characters);

//this function erases the user message
void Erase_User_Message();

//this function takes only input of numbers
void User_Message_Only_Numbers(SDL_Event event,int max_characters);

#endif
