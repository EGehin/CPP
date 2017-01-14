#include "SDL_Wrapper.h"
#include <iostream>
#include <string>

// Load Image
SDL_Surface* LoadImage(const char* ImageLocation)
{
	// Initialize Variables
	SDL_Surface *SDL_S_Return = NULL;

	// Load Image
	SDL_S_Return = IMG_Load(ImageLocation);

	// If it hasn't been loaded...
	if(SDL_S_Return == NULL)
	{
		// Send out an Error Message
		fprintf(stderr, "Error: %s\n", IMG_GetError());
	}

	// Return the Surface (Will be NULL if file isn't loaded)
	return SDL_S_Return;
}

// Create New Image
SDL_Surface* CreateNewImage(int Width, int Height)
{
	return SDL_CreateRGBSurface(0, Width, Height, 24, 0, 0, 0, 0);
}

// Convert To Array
Uint8* GetPixelArray(SDL_Surface* LoadedImage, int *Width, int *Height)
{
	// Initialize Variables
	Uint8* Pixl_Return = NULL;

	// Check if Image is actually loaded
	if(LoadedImage == NULL)
		return NULL;

	// Get Pixels
	Pixl_Return = (Uint8*) LoadedImage->pixels;

	// Set Width and Height
	*Width = LoadedImage->w;
	*Height = LoadedImage->h;

	// Return Array
	return Pixl_Return;
}

// Get Pixel 
Uint8* GetPixelByteAtPosition(SDL_Surface* LoadedImage, int X, int Y)
{
	int bpp = LoadedImage->format->BytesPerPixel;

    return (Uint8*) LoadedImage->pixels + Y * LoadedImage->pitch + X * bpp;
}

// Get RGB Values of a Pixel
void GetRGBValues(SDL_Surface* LoadedImage, int X, int Y, Uint8 *R, Uint8 *G, Uint8 *B)
{
	// Initialize Variables
	Uint32 Pxl_Colour;
	Uint8* Pxl = GetPixelByteAtPosition(LoadedImage, X, Y);

	// Convert the Pixel into Correct Format
	switch(LoadedImage->format->BytesPerPixel) 
	{
    case 1:
        Pxl_Colour = *Pxl;
        break;

    case 2:
        Pxl_Colour = *(Uint16 *) Pxl;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            Pxl_Colour = Pxl[0] << 16 | Pxl[1] << 8 | Pxl[2];
        else
            Pxl_Colour = Pxl[0] | Pxl[1] << 8 | Pxl[2] << 16;
        break;

    case 4:
        Pxl_Colour = *(Uint32 *) Pxl;
        break;

    default:
		Pxl_Colour = 0;
    }

	// Convert into RGB
	SDL_GetRGB(Pxl_Colour, LoadedImage->format, R, G, B);

}

// Get RGB Values of a Pixel
void GetRGBAValues(SDL_Surface* LoadedImage, int X, int Y, Uint8 *R, Uint8 *G, Uint8 *B, Uint8 *A)
{
	// Initialize Variables
	Uint32 Pxl_Colour;
	Uint8* Pxl = GetPixelByteAtPosition(LoadedImage, X, Y);

	// Convert the Pixel into Correct Format
	switch(LoadedImage->format->BytesPerPixel) 
	{
    case 1:
        Pxl_Colour = *Pxl;
        break;

    case 2:
        Pxl_Colour = *(Uint16 *) Pxl;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            Pxl_Colour = Pxl[0] << 24 | Pxl[1] << 16 | Pxl[2] << 8 | Pxl[3];
        else
            Pxl_Colour = Pxl[0] | Pxl[1] << 8 | Pxl[2] << 16 | Pxl[3] << 24;
        break;

    case 4:
        Pxl_Colour = *(Uint32 *) Pxl;
        break;

    default:
		Pxl_Colour = 0;
    }

	// Convert into RGBA
	SDL_GetRGBA(Pxl_Colour, LoadedImage->format, R, G, B, A);
}

// Set RGB Values of a Pixel
void SetRGBValues(SDL_Surface* LoadedImage, int X, int Y, Uint8 R, Uint8 G, Uint8 B)
{
	// Initialize Variables
	Uint32 Pxl_Colour;
    Uint8 *Pxl = GetPixelByteAtPosition(LoadedImage, X, Y);

	// Convert RGB into Correct Pixel Format
	Pxl_Colour = SDL_MapRGB(LoadedImage->format, R, G, B);

	// Set Pixel depending on Bits Per Pixel
    switch(LoadedImage->format->BytesPerPixel) {
    case 1:
        *Pxl = Pxl_Colour;
        break;

    case 2:
        *(Uint16*) Pxl = Pxl_Colour;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            Pxl[0] = (Pxl_Colour >> 16) & 0xff;
            Pxl[1] = (Pxl_Colour >> 8) & 0xff;
            Pxl[2] = Pxl_Colour & 0xff;
        } else {
            Pxl[0] = Pxl_Colour & 0xff;
            Pxl[1] = (Pxl_Colour >> 8) & 0xff;
            Pxl[2] = (Pxl_Colour >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32*) Pxl = Pxl_Colour;
        break;
    }
}

void SetRGBAValues(SDL_Surface* LoadedImage, int X, int Y, Uint8 R, Uint8 G, Uint8 B, Uint8 A)
{
	// Initialize Variables
	Uint32 Pxl_Colour;
    Uint8 *Pxl = GetPixelByteAtPosition(LoadedImage, X, Y);

	// Convert RGB into Correct Pixel Format
	Pxl_Colour = SDL_MapRGBA(LoadedImage->format, R, G, B, A);

	// Set Pixel depending on Bits Per Pixel
    switch(LoadedImage->format->BytesPerPixel) {
    case 1:
        *Pxl = Pxl_Colour;
        break;

    case 2:
        *(Uint16*) Pxl = Pxl_Colour;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            Pxl[0] = (Pxl_Colour >> 24) & 0xff;
            Pxl[1] = (Pxl_Colour >> 16) & 0xff;
            Pxl[2] = (Pxl_Colour >> 8) & 0xff;
			Pxl[3] = Pxl_Colour & 0xff;
        } else {
            Pxl[0] = Pxl_Colour & 0xff;
            Pxl[1] = (Pxl_Colour >> 8) & 0xff;
            Pxl[2] = (Pxl_Colour >> 16) & 0xff;
			Pxl[3] = (Pxl_Colour >> 24) & 0xff;
        }
        break;

    case 4:
        *(Uint32*) Pxl = Pxl_Colour;
        break;
    }
}

// Save Image as BMP
void SaveImageBMP(SDL_Surface* LoadedImage, const char * ImageLocation)
{
	SDL_SaveBMP(LoadedImage, ImageLocation);
}