#ifndef _GFX_H_
#define _GFX_H_

#define TRUE	1			//Sant
#define FALSE	0			//Falskt
#define PI      3.1415926535897932384626433832795f	//PI

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

typedef struct tColorRGBA
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
}tColorRGBA;

typedef struct Mouse_
{
    int x;          //musens x position
    int y;          //musens y position
    int x_scale;    //används för att ordna till musens position då fönsterstorleken är ändrad
    int y_scale;    //används för att ordna till musens position då fönsterstorleken är ändrad
}MOUSE;

MOUSE Mouse;

SDL_Surface *screen;			//skärm surface

SDL_Surface *TempImage;			//ett temporärt surface för inläsning av grafik
SDL_PixelFormat *PixelFormat;	//Vilket pixelformat som används (24bpp, 32bpp etc)
SDL_Surface *TrippleBuffer;		//tripple buffern
SDL_Surface *ScreenStretch;

int fullscreen;                 //om spelet körs i fullskärmsläge eller inte just nu

//Denna funktion låser ett surface
void Slock(SDL_Surface *screen);

//Denna funktion låser upp ett surface
void Sulock(SDL_Surface *screen);

//denna funktion rensar ett skärm surface
void Clear_Surface(SDL_Surface *dst);

//Denna funktion ritar upp en bild på valt surface på position x,y
void Draw_Image(SDL_Surface *img,SDL_Surface *where, int x, int y);

//denna funktion laddar en .png till ett temporärt surface som sedan omvandlas till skärmens format.
SDL_Surface *Load_And_Convert_Bitmap(char *file);

//Denna funktion kopierar en definierad del av ett surface till ett annat
void Surface_Copy(SDL_Surface *from, SDL_Surface *where,int x,int y,int w,int h);

//Denna funktion klipper ut mindre bilder ur ett surface
void Get_Anim(char *file,SDL_Surface *image, SDL_Surface *anim[],int x,int y,int w,int h,int num_frames, int num_sprites_per_line,int grid_width);

//Denna funktion testar ifall två rektanglar har kolliderat
int SDL_CollideBoundingBox(SDL_Rect a , SDL_Rect b);

//denna funktion sätter upp en rektangels x,y position, och dess bredd & höjd
void Setup_Rectangle(SDL_Rect *Rect,int x,int y,int width,int height);

////denna funktion skapar tripple buffer surface
void Create_tripple_buffer(SDL_Surface *GetPixelFormat,int width,int height);

//denna funktion låser spelet vid en viss hastighet
void WaitFrame(int FPS_PER_SEC);

int SDL_StretchBlt( SDL_Surface *src , SDL_Rect *aSrcRect , SDL_Surface *dst , SDL_Rect *aDstRect , int smooth );

//denna funktion ändrar storlek på ett surface
SDL_Surface * Stretch_Surface(SDL_Surface *Surface, float stretchX, float stretchY);

//denna funktion roterar ett surface (denna är limiterad till fyrkanter)
SDL_Surface *Rotate_Surface (SDL_Surface *src,float angle, float scale);

#endif
