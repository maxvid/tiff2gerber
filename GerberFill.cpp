#include "stdafx.h"


void Gerber::PutGerberImageOutlineFill(void)
{
	//G54 - Select Aperture
	fileGerber << "G54D99*" << "\r\n";

	//D01 - Draw mode on
	//D02 - Draw mode off
	//G36 - Turn on Outline Fill
	//G37 - Turn off Outline Fill
	//G01 - Set Linear Interpolation Mode
	//G04 - Ignore Data Block

/////////////////////////////////////////////////////////////
// рисуем рамку по размеру рисунка
	PutGerberLine(-1, -2, sizeXbitmap, -2);
	PutGerberLine(sizeXbitmap + 1, -1, sizeXbitmap + 1, sizeYbitmap);
	PutGerberLine(sizeXbitmap, sizeYbitmap + 1, -1, sizeYbitmap + 1);
	PutGerberLine(-2, sizeYbitmap, -2, -1);

/////////////////////////////////////////////////////////////
// ставим точки в углах
	PutGerberFlash(-1, -1);
	PutGerberFlash(sizeXbitmap, -1);
	PutGerberFlash(sizeXbitmap, sizeYbitmap);
	PutGerberFlash(-1, sizeYbitmap);

	PullBitmapPixel(1, 1);
//	OutlineFill FillFirst(gray4bit);
	OutlineFill FillFirst(gray8bit);
	FillFirst.FindFillBitmap();
}

/*
unsigned int PullBitmapPixel(unsigned int parX, unsigned int parY)
{
//	FIBITMAP *parBitmap = bitmap;
	FIBITMAP *parBitmap = gray4bit;
	unsigned int width = FreeImage_GetWidth(parBitmap);
	unsigned int height = FreeImage_GetHeight(parBitmap);
	unsigned int pitch = FreeImage_GetPitch(parBitmap);
	unsigned int byteLine = FreeImage_GetLine(parBitmap);
	unsigned int colorType = FreeImage_GetColorType(parBitmap);

	unsigned int x, y;

//	wcout << _TEXT("PITCH = ") << pitch << endl;
	BYTE *bits = (BYTE*)FreeImage_GetBits(parBitmap);
	for(y = 0; y < height; y++) 
	{
		BYTE *pixel = (BYTE*)bits;
		for(x = 0; x < width; x++) 
		{
//			pixel[FI_RGBA_RED] = 128;
//			pixel[FI_RGBA_GREEN] = 128;
//			pixel[FI_RGBA_BLUE] = 128;
			pixel += 3;
		}
/////// next line
//		bits += pitch;
	}
	unsigned int byteX = parX >> 3;
	BYTE bitX = 0x80 >> (0x0007 & parX);
	for(unsigned int index = 0; index < height;  index++)
	{
//		*(bits + (index >> 3) + (index) * pitch) = (0x80 >> (0x0007 & index)); black and white
//		*(bits + (index >> 1) + (index) * pitch) = (0x80 >> (0x0001 & index));// grayscale 4 bit
		*(bits + (index >> 1) + (index) * pitch) ^= (0x0001 & index) ? 0x0C : 0xC0;// grayscale 4 bit
	}
	return 0;
}
*/
