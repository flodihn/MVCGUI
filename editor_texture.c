#include <GL/GL.h>
#include <SOIL.h>
GLuint GetTexture(char *Filename)
{
	GLuint tex_ID;

	tex_ID = SOIL_load_OGL_texture(
				Filename,
				SOIL_LOAD_AUTO,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_POWER_OF_TWO
				| SOIL_FLAG_MIPMAPS
				| SOIL_FLAG_MULTIPLY_ALPHA
				| SOIL_FLAG_COMPRESS_TO_DXT
				| SOIL_FLAG_DDS_LOAD_DIRECT
				| SOIL_FLAG_INVERT_Y
				);

		if( tex_ID > 0 )
		{
			glEnable( GL_TEXTURE_2D );
			glBindTexture( GL_TEXTURE_2D, tex_ID );

			return tex_ID;
		}
		else
			return 0;
}
