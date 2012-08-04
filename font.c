#include <stdlib.h>
#include <string.h>

#include "SDL/SDL.h"		//SDL biblioteket
#include "SDL/SDL_image.h"	//SDL image biblioteket

#include "gfx.h"

#ifndef _LOGIC_H_
#include "font.h"
#endif

#define FALSE 0
#define TRUE 1

//166 = Ä 167 = Å 215 = Ö
//Denna funktion skriver en sträng med tecken på skärmen
int Font_String(int x,int y,char *string,SDL_Surface *surface,SDL_Surface *fnt[], int space[])
{
int i;		//används för looping
int length;	//längd på text strängen
int c = 0;		//används för att kalkylera vilken bokstav som ska ritas

	//hämta längden på text strängen
        length=strlen(string);

		//loopa igenom text strängen
                for(i=0;i<length;i++)
                {
		//hämta bokstaven
                c = string[i] - 32;

                    //om strängen visar -42 så är det ett ö
                    if(c ==-42)
                    {
                        c= 184;
                    }
                    //om strängen visar -59 så är det ett ä
                    if(c ==-59)
                    {
                        c= 199;
                    }

                    //om strängen visar -60 så är det ett å
                    if(c ==-60)
                    {
                        c= 198;
                    }

                    if(c == -91)    //Å
                    {
                        c = 167;
                    }
                    if(c == -92)    //Ä
                    {
                        c = 166;
                    }

                    if(c == -74)    //Ö
                    {
                        c = 215;
                    }
			//rita upp den
			Draw_Image(fnt[c],surface,x,y);

			//flytta "x" pixlar till höger för att börja rita ut nästa bokstav.
			x+=space[c];
                }
return c;
}

//denna funktion läser in en textsträng från användaren
void User_Message(SDL_Event event,int max_characters)
{
int checked=0;		//används för att blockera underliggande "if satser".

if(max_characters>=512)
{
	max_characters=512;
}

Uint16 universal_key=0;	//vår unicode tangent

		//Om chatten är aktiverad
		if(ChatMessage.chat_enabled==TRUE)
		{
			//Visa vart i medelandet vi är med följande tecken:
			ChatMessage.message[ChatMessage.pos]= '|';
		}

		//om en tangent är nedtryckt
		if (event.type == SDL_KEYDOWN)
		{
			//on tangenten var enter
			if ( event.key.keysym.unicode == SDLK_RETURN)
			{
				//Om det redan finns text i chatmedelandet, dvs om användaren redan skrivigt något som han/hon vill skicka iväng
				if(ChatMessage.pos>0 && ChatMessage.chat_enabled==TRUE)
				{
					//markera att vi inte behöver göra något mer.
					checked=1;

					//flagga att det är dags att skicka medelandet vidare
					ChatMessage.send_message=TRUE;

					//Radera | tecknet från text strängen så att det inte finns med i det medelande som användaren skrivit in
					ChatMessage.message[ChatMessage.pos]= '\0';
				}

				//om chatten är avaktiverad
				if(ChatMessage.chat_enabled==FALSE && checked!=1)
				{
					//markera att vi inte behöver göra något mer.
					checked=1;

					//Aktivera chatten
					ChatMessage.chat_enabled=TRUE;
				}

				//om inget finns inmatat och chatten är aktiverad och användaren trycker enter
				if(ChatMessage.pos==0 && ChatMessage.chat_enabled==TRUE && checked!=1)
				{
					//det är ett tomt medelande, så stäng av chatten
					ChatMessage.chat_enabled=FALSE;
				}
			}
		}

		//om en tangent är nedtryckt och chatten är aktiverad
		if ( event.type == SDL_KEYDOWN && ChatMessage.chat_enabled==TRUE)
		{
			//kopiera vilken tangent som användaren trycker
			universal_key = event.key.keysym.unicode;

			//Begränsa vilka bokstäver som får vara med (0-9, A-Z, a-z, + lite annat, se font.h för att se vilka tecken som kan användas)
			if(universal_key >31 && universal_key <129)
			{
				//Uteslut följande knappar: backspace (radera bokstav), enter & escape
				if(universal_key != 0 && universal_key != SDLK_BACKSPACE && universal_key!= SDLK_RETURN && universal_key != SDLK_ESCAPE)
				{
					//kopiera den inmatade bokstaven till meddelandet
					ChatMessage.message[ChatMessage.pos]= universal_key;

					//gå till nästa position i medelandet
					ChatMessage.pos++;
				}
			}

			//om användaren trycker backspace
			if( universal_key == SDLK_BACKSPACE)
			{
				//radera | tecknet som visar vart vi är i textsträngen.
				ChatMessage.message[ChatMessage.pos]='\0';

				//gå tillbaks ett steg
				ChatMessage.pos--;

				//radera sista bokstaven
				ChatMessage.message[ChatMessage.pos]='\0';


					//se till så att vi inte går för långt i medelandet
					if(ChatMessage.pos<=0)
					{
						ChatMessage.pos=0;
					}

			}
		}

	//Limitera inmatningen till antal bokstäver vi angav
	if(ChatMessage.pos==max_characters)
	{
		ChatMessage.message[ChatMessage.pos] = '\0';
		ChatMessage.pos--;
	}
}

//denna funktion läser in endast siffror från användaren
void User_Message_Only_Numbers(SDL_Event event,int max_characters)
{
int checked=0;		//används för att blockera underliggande "if satser".

if(max_characters>=512)
{
	max_characters=512;
}

Uint16 universal_key=0;	//vår unicode tangent

		//Om chatten är aktiverad
		if(ChatMessage.chat_enabled==TRUE)
		{
			//Visa vart i medelandet vi är med följande tecken:
			ChatMessage.message[ChatMessage.pos]= '|';
		}

		//om en tangent är nedtryckt
		if (event.type == SDL_KEYDOWN)
		{
			//on tangenten var enter
			if ( event.key.keysym.unicode == SDLK_RETURN)
			{
				//Om det redan finns text i chatmedelandet, dvs om användaren redan skrivigt något som han/hon vill skicka iväng
				if(ChatMessage.pos>0 && ChatMessage.chat_enabled==TRUE)
				{
					//markera att vi inte behöver göra något mer.
					checked=1;

					//flagga att det är dags att skicka medelandet vidare
					ChatMessage.send_message=TRUE;

					//Radera | tecknet från text strängen så att det inte finns med i det medelande som användaren skrivit in
					ChatMessage.message[ChatMessage.pos]= '\0';
				}

				//om chatten är avaktiverad
				if(ChatMessage.chat_enabled==FALSE && checked!=1)
				{
					//markera att vi inte behöver göra något mer.
					checked=1;

					//Aktivera chatten
					ChatMessage.chat_enabled=TRUE;
				}

				//om inget finns inmatat och chatten är aktiverad och användaren trycker enter
				if(ChatMessage.pos==0 && ChatMessage.chat_enabled==TRUE && checked!=1)
				{
					//det är ett tomt medelande, så stäng av chatten
					ChatMessage.chat_enabled=FALSE;
				}
			}
		}

		//om en tangent är nedtryckt och chatten är aktiverad
		if ( event.type == SDL_KEYDOWN && ChatMessage.chat_enabled==TRUE)
		{
			//kopiera vilken tangent som användaren trycker
			universal_key = event.key.keysym.unicode;

			//Begränsa till endast siffror (0-9)
			if( (universal_key >47 && universal_key <58) || (universal_key == SDLK_PERIOD ))
			{
				//Uteslut följande knappar: backspace (radera bokstav), enter & escape
				if(universal_key != 0 && universal_key != SDLK_BACKSPACE && universal_key!= SDLK_RETURN && universal_key != SDLK_ESCAPE)
				{
					//kopiera den inmatade bokstaven till meddelandet
					ChatMessage.message[ChatMessage.pos]= universal_key;

					//gå till nästa position i medelandet
					ChatMessage.pos++;
				}
			}

			//om användaren trycker backspace
			if( universal_key == SDLK_BACKSPACE)
			{
				//radera | tecknet som visar vart vi är i textsträngen.
				ChatMessage.message[ChatMessage.pos]='\0';

				//gå tillbaks ett steg
				ChatMessage.pos--;

				//radera sista bokstaven
				ChatMessage.message[ChatMessage.pos]='\0';


					//se till så att vi inte går för långt i medelandet
					if(ChatMessage.pos<=0)
					{
						ChatMessage.pos=0;
					}

			}
		}

	//Limitera inmatningen till antal bokstäver vi angav
	if(ChatMessage.pos==max_characters)
	{
		ChatMessage.message[ChatMessage.pos] = '\0';
		ChatMessage.pos--;
	}
}


//denna funktion raderar användarens medelande
void Erase_User_Message()
{
int i=0;	//används för att loopa

	ChatMessage.pos=0;				//nollställ position i medelandet
	ChatMessage.send_message=FALSE;			//återställ send_message flaggan

	//gå igenom hela medelandet
	for(i=0;i<MAX_MESSAGE_STRING_LENGTH-1;i++)
	{
		//töm alla bokstäver.
		ChatMessage.message[i] = '\0';
	}
}
