#include <time.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "gfx.h"

//Denna funktionen låser ett surface
void Slock(SDL_Surface *screen)
{
  if ( SDL_MUSTLOCK(screen) )
  {
    if ( SDL_LockSurface(screen) < 0 )
    {
      return;
    }
  }
}

//Denna funktion låser upp ett surface
void Sulock(SDL_Surface *screen)
{
  if ( SDL_MUSTLOCK(screen) )
  {
    SDL_UnlockSurface(screen);
  }
}


/*
    this function loads and convert an image to the right display format
    which is needed so the surfaces don't convert before blitting and thus
    slows down our application
*/
SDL_Surface *load_and_convert_image(char *name)
{
    FILE *out;	//filpekare
	SDL_Surface *converted_image;
	SDL_Surface *temp = IMG_Load(name);
//	if(!temp)
//		return NULL;

	if(!temp)
	{
				//öppna Error.txt
				out = fopen( "errorlog.txt", "wb" );

				//om det gick att öppna Error.txt
				if( out != NULL )
				{
					//skriv vad som gick fel
					fprintf(out,"could not load image: %s\n",name);

					//stäng filen
					fclose(out);
				}
			//avsluta programmet
			exit(1);
	}

	if(temp->format->Amask)
	{
		SDL_SetAlpha(temp, 0, SDL_ALPHA_OPAQUE);
		converted_image = SDL_DisplayFormatAlpha(temp);
	}
	else
	{
		/*set colorkey to magenta for the surface
		SDL_SetColorKey(temp, SDL_SRCCOLORKEY,
				SDL_MapRGB(temp->format, 255, 0, 255));*/

		/*convert the surface to the displayformat of the screen*/
		converted_image = SDL_DisplayFormat(temp);
	}

	/*free the temporary surface*/
	SDL_FreeSurface(temp);

	/*return the converted image*/
	return converted_image;
}

//denna funktion låser spelet vid en viss hastighet
void WaitFrame(int FPS_PER_SEC)
{
static Uint32 next_tick = 0;
Uint32 this_tick;

    /* Wait for the next frame */
    this_tick = SDL_GetTicks();

        if ( this_tick < next_tick ) {
            SDL_Delay(next_tick-this_tick);
        }

    next_tick = this_tick + (1000/FPS_PER_SEC);
}

//denna funktion skapar tripple buffer surface
void Create_tripple_buffer(SDL_Surface *GetPixelFormat,int width,int height)
{
FILE *out;	//filpekare
SDL_Surface *temp;
	//hämta pixelformatet.
	PixelFormat = GetPixelFormat->format;

	//Skapa tripple buffer surfacet
	temp = SDL_CreateRGBSurface(SDL_HWSURFACE,width,height,16,PixelFormat->Rmask,PixelFormat->Gmask,PixelFormat->Bmask,PixelFormat->Amask);

	TrippleBuffer = SDL_DisplayFormatAlpha(temp);

		//Om det inte gick
		if(TrippleBuffer==NULL)
		{

			//öppna Error.txt
			out = fopen( "Error.txt", "w" );

			//om det gick att öppna Error.txt
			if( out != NULL )
			{
				//skriv vad som gick fel
				fprintf(out,"could not create tripple buffer\n");

				//stäng filen
				fclose(out);
			}

			exit(1);
		}
    SDL_FreeSurface(temp);
}

/*this function copies a part of a surface into another one*/
void Surface_Copy(SDL_Surface *from, SDL_Surface *where,int x,int y,int w,int h)
{
	int width=0,height=0;	/*bredd & höjd på surface*/
	width = w-x;		/*kalkylera bredd*/
	height=h-y;		/*kalkylera höjd*/

	/*rectangeln från original surfacet*/
	SDL_Rect Rsrc;
	Rsrc.x=x;
	Rsrc.y=y;
	Rsrc.w=w;
	Rsrc.h=h;

	/*rektangeln på det nya surfacet*/
	SDL_Rect Rdst;
	Rdst.x=0;
	Rdst.y=0;
	Rdst.w=width;
	Rdst.h=height;

		/*kopiera ut rektangeln från ett surface, och placera den på ett annat*/
		SDL_BlitSurface(from, &Rsrc, where, &Rdst);
}
//Denna funktion klipper ut mindre bilder ur ett surface
void Get_Anim(char *file,SDL_Surface *image, SDL_Surface *anim[],int x,int y,int w,int h,int num_frames, int num_sprites_per_line,int grid_width)
{
	FILE *out;	//filpekare

	int i=0,j=0;	//används för att loopa
	int width=0;	//sprite bredd
	int height=0;	//sprite höjd
	int num_rows=0; //antal rader
	int xs=0;	//används för att spara start x position
    SDL_Surface *convert = NULL;

	width  = w-x;	//hämta bildens bredd
	height = h-y;	//hämta bildens höjd
	xs = x;		//sätt x start position

	//kalkylera hur många rader med sprites det finns
	num_rows = num_frames/num_sprites_per_line+1;

		//ladda in bilden och konvertera den till skärmens bildformat
		image = load_and_convert_image(file);

        if(image->format->Amask)
        {
            SDL_SetAlpha(image, 0, SDL_ALPHA_OPAQUE);
        }

		//hämta pixelformatet.
		PixelFormat = image->format;

			//om det inte gick att ladda in bilden eller om vi inte initierat pixel format
			if(image==NULL)
			{
				//öppna Error.txt
				out = fopen( "errorlogs/image_loaderror.txt", "wb" );

				//om det gick att öppna Error.txt
				if( out != NULL )
				{
					//skriv vad som gick fel
					fprintf(out,"could not load image: %s\n",file);

					//stäng filen
					fclose(out);
				}
			//avsluta programmet
			exit(1);
			}

	//gå igenom animationerna
	for(i=0;i<num_frames;i++)
	{
		//loopa igenom alla rader med sprites
		for(j=1;j<num_rows;j++)
		{
			//om vi kommit till slutet på en rad
			if(i==num_sprites_per_line*j)
			{
				//gå till nästa rad
				y+=height+grid_width;
				x=xs;
			}
		}
		//skapa ett surface för varje ny bild
		convert = SDL_CreateRGBSurface(SDL_HWSURFACE,width,height,16,PixelFormat->Rmask,PixelFormat->Gmask,PixelFormat->Bmask,PixelFormat->Amask);

        if(image->format->Amask)
        {
            anim[i] = SDL_DisplayFormatAlpha(convert);
        }
        else{
            anim[i] = SDL_DisplayFormat(convert);
        }

			// Om det inte gick
			if(anim[i] == NULL)
			{
				//öppna Error.txt
				out = fopen( "Error.txt", "w" );

				//om det gick att öppna Error.txt
				if( out != NULL )
				{
					//skriv vad som gick fel
					fprintf(out,"could not create surface from image: %s, sprite frame %d",file,i);

					//stäng filen
					fclose(out);
				}
			//avsluta programmet
			exit(1);
			}

		//sätt transparent färg till magenta
		if(!image->format->Amask)
		SDL_SetColorKey(anim[i],SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(anim[i]->format,255,0,255));

		//Hämta spriten från den laddade bilden
		Surface_Copy(image, anim[i],x,y,x+w,y+h);

		//gå till nästa bild
		x+=width+grid_width;
	}
//fria det allokerade minnet för bilden
SDL_FreeSurface(image);
SDL_FreeSurface(convert);
}

void Draw_Image(SDL_Surface *img,SDL_Surface *where, int x, int y)
{
  //set up the destination rectangle
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;

  //Draw it on the screen
  SDL_BlitSurface(img, NULL, where, &dest);
}

int SDL_CollideBoundingBox(SDL_Rect a , SDL_Rect b)
{
	if(b.x + b.w < a.x)	return 0;	//kolla ifall de två
	if(b.x > a.x + a.w)	return 0;	//rektanglarna rör vid varandra

	if(b.y + b.h < a.y)	return 0;
	if(b.y > a.y + a.h)	return 0;

	return 1;
}

void Setup_Rectangle(SDL_Rect *Rect,int x,int y,int width,int height)
{
Rect->x=x;
Rect->y=y;
Rect->w=width;
Rect->h=height;
}

void Clear_Surface(SDL_Surface *dst)
{
    SDL_FillRect(dst, NULL, 0x000000);
}
