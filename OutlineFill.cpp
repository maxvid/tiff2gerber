#include "StdAfx.h"
//#include "OutlineFill.h"

OutlineFill::OutlineFill(FIBITMAP *parDIB)
{
	m_DIB = parDIB;
	m_BitPerPixel = FreeImage_GetBPP(m_DIB);
	m_Width = FreeImage_GetWidth(m_DIB);
	m_Height = FreeImage_GetHeight(m_DIB);
	m_Pitch = FreeImage_GetPitch(m_DIB);
	m_ByteLine = FreeImage_GetLine(m_DIB);
	m_ColorType = FreeImage_GetColorType(m_DIB);
	p_Bits = (BYTE*)FreeImage_GetBits(m_DIB);
}

OutlineFill::OutlineFill(void)
{
}

OutlineFill::~OutlineFill(void)
{
}

void OutlineFill::FindFillBitmap(void)
{
	if(4 == m_BitPerPixel);
//	*(bits + (index >> 1) + (index) * pitch) ^= (0x0001 & index) ? 0x0C : 0xC0;// grayscale 4 bit
//	unsigned char double_pixel = *(p_Bits + (parX >> 1) + (parY * m_Pitch));
//	BYTE pixel = (0x0001 & parX) ? (twoPix >> 4) : (twoPix & 0x0F);
	if(8 == m_BitPerPixel);
	unsigned int X = 0, Y = 0;
	unsigned char pixel = *(p_Bits + X + Y * m_Pitch);// grayscale 8 bit

	unsigned int flagBegin = 0;
	unsigned int flagEnd = 0;
	unsigned int firstX = 0;
	unsigned int firstY = 0;
	unsigned int endX = 0;
	unsigned int endY = 0;
	m_countBlackPixel = 0;
	m_numMinX = 0;
	m_numMinY = 0;
	m_numMaxX = 0;
	m_numMaxY = 0;

	BYTE *point_Bits = OutlineFill::p_Bits;
	for(Y = 0; Y < m_Height; Y++) 
	{
		BYTE *point_Pixel = (BYTE*)point_Bits;
		if(1 == flagBegin)
		{
		}
		else
		{
		for(X = 0; X < m_Width; X++) 
		{
			if(GRAY_BLACK == *point_Pixel) // нашли черный пиксел
			{
				flagBegin = 1;
				firstX = X;
				firstY = Y;
				m_numMinX = X;
				m_numMinY = Y;
				break;
			}
			point_Pixel += 1; // next Pixel
		}
		for(X; X < m_Width; X++) 
		{
			if(GRAY_WHITE == *point_Pixel) // нашли белый пиксел
			{
				endX = X - 1;
				endY = Y;
				m_numMinX = X - 1;
				break;
			}
			if(GRAY_BLACK == *point_Pixel) // нашли черный пиксел
			{
				*point_Pixel = GRAY_FIND_FILL; // зарисуем его серым
				m_countBlackPixel++; // увеличим счетчик этой заливки
			}
			point_Pixel += 1; // next Pixel
		}
		}
		point_Bits += m_Pitch; // next Line
	}
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
