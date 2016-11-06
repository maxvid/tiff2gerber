// код зависимый от библиотеки

//#include "stdafx.h"
#include "FreeImage.h"

void InitView(void);
//void LoadTIFF(void);
//void LoadTIFF(const wchar_t * parFileName);
void LoadTIFF(const _TCHAR * parFileName);
void SaveTIFF(FIBITMAP * parBitmap, const _TCHAR * parFileName, const _TCHAR * parNameSufix);
void InfoTIFF(FIBITMAP * parBitmap);
void UnLoadTIFF(void);
void UnLoadTIFF(FIBITMAP * parBitmap);
void CloneTIFF(void);

unsigned int GetBitmapSizeX(void);
unsigned int GetBitmapSizeY(void);
double GetPixelSizeX(void);
double GetPixelSizeY(void);
unsigned int GetColorType(void);

void ImageFormat(FIBITMAP * parBitmap);

void ImageGetScaneLine(FIBITMAP * parBitmap);

//unsigned int PullBitmap(FIBITMAP *parBitmap);
unsigned int PullBitmap(void);
unsigned int PullLine(unsigned int parY);
//unsigned int PullLinePixel(unsigned int parX);
unsigned int PullLinePixel(unsigned int * pPixel, unsigned int parX);

unsigned int PullBitmapPixel(unsigned int parX, unsigned int parY);



//void GetBitmap(void);
unsigned int GetPixel(unsigned int parX, unsigned int parY);



extern FIBITMAP *bitmap;
extern FIBITMAP *clone;
extern FIBITMAP *gray4bit;
extern FIBITMAP *gray8bit;






