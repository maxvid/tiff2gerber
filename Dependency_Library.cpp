// код зависимый от применяемой графической библиотеки

#include "stdafx.h"

using namespace std;

FIBITMAP *bitmap = NULL;
FIBITMAP *clone = NULL;
FIBITMAP *gray4bit = NULL;
FIBITMAP *gray8bit = NULL;

void InitView(void)
{
//	FreeImage_Initialise();
//	FreeImage_DeInitialise();
	wcout << _TEXT("FreeImage Version: ") << FreeImage_GetVersion() << endl << endl;
	wcout << _TEXT(" Лицензия: ") << FreeImage_GetCopyrightMessage() << endl << endl;
}

void LoadTIFF(const _TCHAR * parFileName)
{
	/*
#define TIFF_DEFAULT        0
#define TIFF_CMYK			0x0001	// reads/stores tags for separated CMYK (use | to combine with compression flags)
#define TIFF_PACKBITS       0x0100  // save using PACKBITS compression
#define TIFF_DEFLATE        0x0200  // save using DEFLATE compression (a.k.a. ZLIB compression)
#define TIFF_ADOBE_DEFLATE  0x0400  // save using ADOBE DEFLATE compression
#define TIFF_NONE           0x0800  // save without any compression
#define TIFF_CCITTFAX3		0x1000  // save using CCITT Group 3 fax encoding
#define TIFF_CCITTFAX4		0x2000  // save using CCITT Group 4 fax encoding
#define TIFF_LZW			0x4000	// save using LZW compression
#define TIFF_JPEG			0x8000	// save using JPEG compression
#define TIFF_LOGLUV			0x10000	// save using LogLuv compression
	*/
//	_tcsncpy 

//	int
	FREE_IMAGE_FORMAT file_format = FreeImage_GetFileTypeU(parFileName);
	wcout << _TEXT(" File Format is: ") << file_format << endl;

//	FIBITMAP *bitmap = FreeImage_Load(FIF_BMP, “mybitmap.bmp”, BMP_DEFAULT);
//	FIBITMAP *bitmap = FreeImage_Load(FIF_TIFF, "E:\\_prj_\\VS\\tiff_test\\tiff\\eset_un.tif", TIFF_NONE);
//	bitmap = FreeImage_LoadU(FIF_TIFF, parFileName, TIFF_DEFAULT);
	bitmap = FreeImage_LoadU(file_format, parFileName, TIFF_DEFAULT);
	if (bitmap)
	{
	// bitmap successfully loaded!
		wcout << _TEXT(" tiff successfully loaded!") << endl;
	}
	else
	{
		wcout << parFileName << endl;
		wcout << _TEXT("  TIFF error load!") << endl;
		_tsystem(_T("pause"));
		exit(1);
	}
}

void SaveTIFF(FIBITMAP * parBitmap, const _TCHAR * parFileName, const _TCHAR * parNameSufix)
{
	int sizeStringFileName = 50 + _tcslen(parFileName) * sizeof(*parFileName);

	_TCHAR * pFileNameTIFF = NULL;
	pFileNameTIFF = new _TCHAR[sizeStringFileName];
	if(NULL == pFileNameTIFF)
	{
		wcout << _TEXT("ошибка выполнения, память недоступна.") << endl << _TEXT("Программа будет закрыта.") << endl;
		_tsystem(_T("pause"));
		exit(1);
	}
	_tcscpy_s(pFileNameTIFF, sizeStringFileName, parFileName);

	_TCHAR * pFileNameClone = NULL;
	pFileNameClone = new _TCHAR[sizeStringFileName];
	if(NULL == pFileNameClone)
	{
		wcout << _TEXT("ошибка выполнения, память недоступна.") << endl << _TEXT("Программа будет закрыта.") << endl;
		_tsystem(_T("pause"));
		exit(1);
	}
	_tcscpy_s(pFileNameClone, sizeStringFileName, parFileName);
//	_tcscpy_s(_tcsrchr(pFileNameClone, _T('.')), 50, _TEXT(".grb")); // переписываем имя начиная с последней точки
	_tcscpy_s(_tcsrchr(pFileNameClone, _T('.')), 50, parNameSufix); // переписываем имя начиная с последней точки
	wcout << _TEXT("Создаем файл: ") << endl << pFileNameClone << endl;

//	FreeImage_Save(FIF_TIFF, clone, "E:\\_prj_\\VS\\tiff_test\\tiff\\eset_CCITT4_clone.tif", TIFF_CCITTFAX4);
	FreeImage_SaveU(FIF_TIFF, parBitmap, pFileNameClone, TIFF_CCITTFAX4);

	if(NULL != pFileNameClone)
	{
		delete [] pFileNameClone;
		pFileNameClone = NULL;
	}
	if(NULL != pFileNameTIFF)
	{
		delete [] pFileNameTIFF;
		pFileNameTIFF = NULL;
	}
}

void InfoTIFF(FIBITMAP * parBitmap)
{
	if(!parBitmap) 
	{
		_tsystem(_T("pause"));
		exit(1);
	}
	// bitmap successfully loaded!
	FREE_IMAGE_TYPE image_type = FreeImage_GetImageType(parBitmap);
	wcout << _TEXT("   FreeImage_GetImageType: ") << image_type << endl;
	switch(image_type)
	{
	case FIT_UNKNOWN: // Unknown format (returned value only, never use it as input value)
		wcout << _TEXT("        FIT_UNKNOWN, Unknown format") << endl; break;
	case FIT_BITMAP: // Standard image: 1-, 4-, 8-, 16-, 24-, 32-bit
		wcout << _TEXT("        FIT_BITMAP, Standard image: 1-, 4-, 8-, 16-, 24-, 32-bit") << endl; break;
	case FIT_UINT16: // Array of unsigned short: unsigned 16-bit
		wcout << _TEXT("        FIT_UINT16, Array of unsigned short: unsigned 16-bit") << endl; break;
	case FIT_INT16: // Array of short: signed 16-bit
		wcout << _TEXT("        FIT_INT16, Array of short: signed 16-bit") << endl; break;
	case FIT_UINT32: // Array of unsigned long: unsigned 32-bit
		wcout << _TEXT("        FIT_UINT32, Array of unsigned long: unsigned 32-bit") << endl; break;
	case FIT_INT32: // Array of long: signed 32-bit
		wcout << _TEXT("        FIT_INT32, Array of long: signed 32-bit") << endl; break;
	case FIT_FLOAT: // Array of float: 32-bit IEEE floating point
		wcout << _TEXT("        FIT_FLOAT, Array of float: 32-bit IEEE floating point") << endl; break;
	case FIT_DOUBLE: // Array of double: 64-bit IEEE floating point
		wcout << _TEXT("        FIT_DOUBLE, Array of double: 64-bit IEEE floating point") << endl; break;
	case FIT_COMPLEX: // Array of FICOMPLEX: 2 x 64-bit IEEE floating point
		wcout << _TEXT("        FIT_COMPLEX, Array of FICOMPLEX: 2 x 64-bit IEEE floating point") << endl; break;
	case FIT_RGB16: // 48-bit RGB image: 3 x 16-bit
		wcout << _TEXT("        FIT_RGB16, 48-bit RGB image: 3 x 16-bit") << endl; break;
	case FIT_RGBA16: // 64-bit RGBA image: 4 x 16-bit
		wcout << _TEXT("        FIT_RGBA16, 64-bit RGBA image: 4 x 16-bit") << endl; break;
	case FIT_RGBF: // 96-bit RGB float image: 3 x 32-bit IEEE floating point
		wcout << _TEXT("        FIT_RGBF, 96-bit RGB float image: 3 x 32-bit IEEE floating point") << endl; break;
	case FIT_RGBAF: // 128-bit RGBA float image: 4 x 32-bit IEEE floating point
		wcout << _TEXT("        FIT_RGBAF, 128-bit RGBA float image: 4 x 32-bit IEEE floating point") << endl; break;
	}

	wcout << _TEXT("   FreeImage_GetColorsUsed: ") << FreeImage_GetColorsUsed(parBitmap) << endl;
	wcout << _TEXT("   FreeImage_GetBPP (the size of one pixel in the bitmap in bits): ") << FreeImage_GetBPP(parBitmap) << endl;
	wcout << _TEXT("   FreeImage_GetWidth (the width of the bitmap in pixel units): ") << FreeImage_GetWidth(parBitmap) << endl;
	wcout << _TEXT("   FreeImage_GetHeight (the height of the bitmap in pixel units): ") << FreeImage_GetHeight(parBitmap) << endl;
//	wcout << _TEXT("   FreeImage_GetLine (the width of the bitmap in bytes): ") << FreeImage_GetLine(parBitmap) << endl;
//	wcout << _TEXT("   FreeImage_GetPitch (the width of the bitmap in bytes, rounded to the next 32-bit boundary): ") << FreeImage_GetPitch(bitmap) << endl;
	wcout << _TEXT("   FreeImage_GetDIBSize: ") << FreeImage_GetDIBSize(parBitmap) << endl;
//	wcout << _TEXT("   FreeImage_GetPalette: ") << FreeImage_GetPalette(bitmap) << endl;
	wcout << _TEXT("   FreeImage_GetDotsPerMeterX: ") << FreeImage_GetDotsPerMeterX(parBitmap) << _TEXT(",    DotsPerInchX: ") << static_cast<unsigned int> (0.5 + FreeImage_GetDotsPerMeterX(parBitmap) * 0.0254) << endl;
	wcout << _TEXT("   FreeImage_GetDotsPerMeterY: ") << FreeImage_GetDotsPerMeterY(parBitmap) << _TEXT(",    DotsPerInchY: ") << static_cast<unsigned int> (0.5 + FreeImage_GetDotsPerMeterY(parBitmap) * 0.0254) << endl;
//	BITMAPINFOHEADER * info_header = FreeImage_GetInfoHeader(parBitmap);
//	BITMAPINFO * info = FreeImage_GetInfo(parBitmap);
	FREE_IMAGE_COLOR_TYPE color_type = FreeImage_GetColorType(parBitmap);
	wcout << _TEXT("   FREE_IMAGE_COLOR_TYPE: ") << color_type << endl;
	switch(color_type)
	{
	case FIC_MINISWHITE: // = 0,// min value is white
		wcout << _TEXT("         FIC_MINISWHITE, min value is white") << endl; break;
	case FIC_MINISBLACK: // = 1,		// min value is black
		wcout << _TEXT("         FIC_MINISBLACK, min value is black") << endl; break;
	case FIC_RGB: //        = 2,		// RGB color model
		wcout << _TEXT("         FIC_RGB, RGB color model") << endl; break;
	case FIC_PALETTE: //    = 3,		// color map indexed
		wcout << _TEXT("         FIC_PALETTE, color map indexed") << endl; break;
	case FIC_RGBALPHA: //   = 4,		// RGB color model with alpha channel
		wcout << _TEXT("         FIC_RGBALPHA, RGB color model with alpha channel") << endl; break;
	case FIC_CMYK: //       = 5		// CMYK color model
		wcout << _TEXT("         FIC_CMYK, CMYK color model") << endl; break;
	default:
		wcout << _TEXT("         UNKNOWN color model") << endl; break;
	}

	unsigned int DotsPerMeterX = FreeImage_GetDotsPerMeterX(parBitmap);
	unsigned int DotsPerMeterY = FreeImage_GetDotsPerMeterY(parBitmap);
	if( 2 > DotsPerMeterX ) DotsPerMeterX = 72;
	if( 2 > DotsPerMeterY ) DotsPerMeterY = 72;
	double ImageSizeX = 1000. * FreeImage_GetWidth(parBitmap) / DotsPerMeterX;
	double ImageSizeY = 1000. * FreeImage_GetHeight(parBitmap) / DotsPerMeterY;
	double PixelSizeX = 1000. / DotsPerMeterX;
	double PixelSizeY = 1000. / DotsPerMeterY;
	wcout << _TEXT("  Размер изображения по горизонтали (X): ") << ImageSizeX << _TEXT(" мм") << endl;
	wcout << _TEXT("  Размер изображения по вертикали (Y): ") << ImageSizeY << _TEXT(" мм") << endl;
	wcout << _TEXT("  Размер точки по горизонтали (X): ") << PixelSizeX << _TEXT(" мм") << endl;
	wcout << _TEXT("  Размер точки по вертикали (Y): ") << PixelSizeY << _TEXT(" мм") << endl;

//		FreeImage_GetBits(bitmap);
//		FreeImage_GetScanLine(bitmap);
//		FreeImage_GetPixelIndex(bitmap, index_X, index_Y, &pointValue);
//		FreeImage_Threshold(bitmap, Threshold);
}

unsigned int GetBitmapSizeX(void)
{
	return FreeImage_GetWidth(bitmap); // in pixel
}

unsigned int GetBitmapSizeY(void)
{
	return FreeImage_GetHeight(bitmap); // in pixel
}

double GetPixelSizeX(void)
{
	unsigned int DotsPerMeterX = FreeImage_GetDotsPerMeterX(bitmap);
	if( 2 > DotsPerMeterX ) DotsPerMeterX = 72;
	double PixelSizeX = 1000. / DotsPerMeterX;
	return PixelSizeX; // in mm
}

double GetPixelSizeY(void)
{
	unsigned int DotsPerMeterY = FreeImage_GetDotsPerMeterY(bitmap);
	if( 2 > DotsPerMeterY ) DotsPerMeterY = 72;
	double PixelSizeY = 1000. / DotsPerMeterY;
	return PixelSizeY; // in mm
}

unsigned int GetColorType(void)
{
	return FreeImage_GetColorType(bitmap);
}

void UnLoadTIFF(void)
{
	if (bitmap) 
	{
	// bitmap successfully loaded!
		wcout << _TEXT(" Выгружаем TIFF") << endl;
		FreeImage_Unload(bitmap);
		bitmap = NULL;
	}
}

void UnLoadTIFF(FIBITMAP * parBitmap)
{
	if (parBitmap) 
	{
	// bitmap successfully loaded!
//		wcout << _TEXT(" Выгружаем TIFF") << endl;
		FreeImage_Unload(parBitmap);
		parBitmap = NULL;
	}
}

void CloneTIFF(void)
{
// this code assumes there is a bitmap loaded and
// present in a variable called ‘dib’
//	FIBITMAP *clone = FreeImage_Clone(dib);
	if( 2 < FreeImage_GetColorsUsed(bitmap)) 
	{
		unsigned char Threshold = 127;
		clone = FreeImage_Clone(bitmap);
		clone = FreeImage_Threshold(clone, Threshold);
	}
	else
	{
		clone = FreeImage_Clone(bitmap);
	}

	if (clone) 
	{
// clone succeeded!
//		FreeImage_Save(FIF_TIFF, bitmap, "E:\\_prj_\\VS\\tiff_test\\tiff\\eset_CCITT4_clone.tif", TIFF_NONE);
		FreeImage_Save(FIF_TIFF, clone, "E:\\_prj_\\VS\\tiff_test\\tiff\\eset_CCITT4_clone.tif", TIFF_CCITTFAX4);
		wcout << _TEXT("требуется преобразовать клон и сформировать имя файла клона") << endl;
//		FreeImage_Unload(clone);
		clone = NULL;
	}
}

void ImageFormat(FIBITMAP * parBitmap)
{
//	unsigned int x, y;
	FREE_IMAGE_TYPE image_type = FreeImage_GetImageType(parBitmap);
	wcout << _TEXT("Формат изображения: ");
// test pixel access
	switch(image_type) 
	{
	case FIT_UNKNOWN: wcout << _TEXT(" FIT_UNKNOWN") << endl; break;
	case FIT_BITMAP: wcout << _TEXT(" FIT_BITMAP") << endl; break;
	case FIT_UINT16: wcout << _TEXT(" FIT_UINT16") << endl; break;
	case FIT_INT16: wcout << _TEXT(" FIT_INT16") << endl; break;
	case FIT_UINT32: wcout << _TEXT(" FIT_UINT32") << endl; break;
	case FIT_INT32: wcout << _TEXT(" FIT_INT32") << endl; break;
	case FIT_FLOAT: wcout << _TEXT(" FIT_FLOAT") << endl; break;
	case FIT_DOUBLE: wcout << _TEXT(" FIT_DOUBLE") << endl; break;
	case FIT_COMPLEX: wcout << _TEXT(" FIT_COMPLEX") << endl; break;
	case FIT_RGB16: wcout << _TEXT(" FIT_RGB16") << endl; break;
	case FIT_RGBF: wcout << _TEXT(" FIT_RGBF") << endl; break;
	case FIT_RGBA16: wcout << _TEXT(" FIT_RGBA16") << endl; break;
	case FIT_RGBAF: wcout << _TEXT(" FIT_RGBAF") << endl; break;
	}
}

void ImageGetScaneLine(FIBITMAP * parBitmap)
{
	unsigned int x, y;
	FREE_IMAGE_TYPE image_type = FreeImage_GetImageType(parBitmap);
	wcout << _TEXT("Формат изображения: ");
// test pixel access
	switch(image_type) 
	{
	case FIT_UNKNOWN: wcout << _TEXT(" FIT_UNKNOWN") << endl;
		break;
	case FIT_BITMAP: wcout << _TEXT(" FIT_BITMAP") << endl;
		if(1 == FreeImage_GetBPP(parBitmap)) 
		{
			unsigned int H;
			for(y = 0; y < (H = FreeImage_GetHeight(parBitmap)); y++) 
			{
				BYTE *bits = (BYTE *)FreeImage_GetScanLine(parBitmap, y);
//				ofstream file;
//				file.open("E:\\GetScanLine.iii");
//				file << *bits;
//				file.close();
				cout << "y = " << (y * 100) / H << "                  \r";

				for(x = 0; x < FreeImage_GetWidth(parBitmap); x++) 
				{
//					bits[x] = 128;
					if((0 != bits[x]) && (3100 != x))
					{
//						wcout << _TEXT(" bits[x] = " << bits[x] << ", x = " << x << ", y = " << y << endl;
//						cout << "bits[x] = " << bits[x] << ", x = " << x << ", y = " << y << "\r";
//						return; // 
						break;
					}
				}
			}
		}
		if(FreeImage_GetBPP(parBitmap) == 8) 
		{
			for(y = 0; y < FreeImage_GetHeight(parBitmap); y++) 
			{
				BYTE *bits = (BYTE *)FreeImage_GetScanLine(parBitmap, y);
				for(x = 0; x < FreeImage_GetWidth(parBitmap); x++) 
				{
					bits[x] = 128;
				}
			}
		}
	break;
	case FIT_UINT16: wcout << _TEXT(" FIT_UINT16") << endl;
		for(y = 0; y < FreeImage_GetHeight(parBitmap); y++) 
		{
			unsigned short *bits = (unsigned short *)FreeImage_GetScanLine(parBitmap, y);
			for(x = 0; x < FreeImage_GetWidth(parBitmap); x++) 
			{
				bits[x] = 128;
			}
		}
	break;
	case FIT_INT16: wcout << _TEXT(" FIT_INT16") << endl;
		for(y = 0; y < FreeImage_GetHeight(parBitmap); y++) 
		{
			short *bits = (short *)FreeImage_GetScanLine(parBitmap, y);
			for(x = 0; x < FreeImage_GetWidth(parBitmap); x++) 
			{
				bits[x] = 128;
			}
		}
	break;
	case FIT_UINT32: wcout << _TEXT(" FIT_UINT32") << endl;
		for(y = 0; y < FreeImage_GetHeight(parBitmap); y++) 
		{
			DWORD *bits = (DWORD *)FreeImage_GetScanLine(parBitmap, y);
			for(x = 0; x < FreeImage_GetWidth(parBitmap); x++) 
			{
				bits[x] = 128;
			}
		}
	break;
	case FIT_INT32: wcout << _TEXT(" FIT_INT32") << endl;
		for(y = 0; y < FreeImage_GetHeight(parBitmap); y++) 
		{
			LONG *bits = (LONG *)FreeImage_GetScanLine(parBitmap, y);
			for(x = 0; x < FreeImage_GetWidth(parBitmap); x++) 
			{
				bits[x] = 128;
			}
		}
	break;
	case FIT_FLOAT: wcout << _TEXT(" FIT_FLOAT") << endl;
		for(y = 0; y < FreeImage_GetHeight(parBitmap); y++) 
		{
			float *bits = (float *)FreeImage_GetScanLine(parBitmap, y);
			for(x = 0; x < FreeImage_GetWidth(parBitmap); x++) 
			{
				bits[x] = 128;
			}
		}
	break;
	case FIT_DOUBLE: wcout << _TEXT(" FIT_DOUBLE") << endl;
		for(y = 0; y < FreeImage_GetHeight(parBitmap); y++) 
		{
			double *bits = (double *)FreeImage_GetScanLine(parBitmap, y);
			for(x = 0; x < FreeImage_GetWidth(parBitmap); x++) 
			{
				bits[x] = 128;
			}
		}
	break;
	case FIT_COMPLEX: wcout << _TEXT(" FIT_COMPLEX") << endl;
		for(y = 0; y < FreeImage_GetHeight(parBitmap); y++) 
		{
			FICOMPLEX *bits = (FICOMPLEX *)FreeImage_GetScanLine(parBitmap, y);
			for(x = 0; x < FreeImage_GetWidth(parBitmap); x++) 
			{
				bits[x].r = 128;
				bits[x].i = 128;
			}
		}
	break;
	case FIT_RGB16: wcout << _TEXT(" FIT_RGB16") << endl;
		for(y = 0; y < FreeImage_GetHeight(parBitmap); y++) 
		{
			FIRGB16 *bits = (FIRGB16 *)FreeImage_GetScanLine(parBitmap, y);
			for(x = 0; x < FreeImage_GetWidth(parBitmap); x++) 
			{
				bits[x].red = 128;
				bits[x].green = 128;
				bits[x].blue = 128;
			}
		}
	break;
	case FIT_RGBF: wcout << _TEXT(" FIT_RGBF") << endl;
		for(y = 0; y < FreeImage_GetHeight(parBitmap); y++) 
		{
			FIRGBF *bits = (FIRGBF *)FreeImage_GetScanLine(parBitmap, y);
			for(x = 0; x < FreeImage_GetWidth(parBitmap); x++) 
			{
				bits[x].red = 128;
				bits[x].green = 128;
				bits[x].blue = 128;
			}
		}
	break;
	case FIT_RGBA16: wcout << _TEXT(" FIT_RGBA16") << endl;
		for(y = 0; y < FreeImage_GetHeight(parBitmap); y++) 
		{
			FIRGBA16 *bits = (FIRGBA16 *)FreeImage_GetScanLine(parBitmap, y);
			for(x = 0; x < FreeImage_GetWidth(parBitmap); x++) 
			{
				bits[x].red = 128;
				bits[x].green = 128;
				bits[x].blue = 128;
				bits[x].alpha = 128;
			}
		}
	break;
	case FIT_RGBAF: wcout << _TEXT(" FIT_RGBAF") << endl;
		for(y = 0; y < FreeImage_GetHeight(parBitmap); y++) 
		{
			FIRGBAF *bits = (FIRGBAF *)FreeImage_GetScanLine(parBitmap, y);
			for(x = 0; x < FreeImage_GetWidth(parBitmap); x++) 
			{
				bits[x].red = 128;
				bits[x].green = 128;
				bits[x].blue = 128;
				bits[x].alpha = 128;
			}
		}
	break;
	}
}


BYTE * bitsLine = NULL;
BYTE * bitsBitmap = NULL;

//unsigned int PullBitmap(FIBITMAP *parBitmap)
unsigned int PullBitmap(void)
{
	FIBITMAP *parBitmap = bitmap;
	FREE_IMAGE_TYPE image_type = FreeImage_GetImageType(parBitmap);
	if(FIT_BITMAP != image_type)
	{
		wcout << _TEXT("!FIT_BITMAP - Ошибочный формат исходного файла") << endl;
		return 1; // error
	}
	if(1 != FreeImage_GetBPP(parBitmap)) // the size of one pixel in the bitmap in bits.
	{
		wcout << _TEXT("FreeImage_GetBPP - Ошибочный размер пиксела в битах") << endl;
		return 1; // error
	}
	if(FALSE == FreeImage_HasPixels(parBitmap)) // FALSE if the bitmap does not contain pixel data
	{
		wcout << _TEXT("FreeImage_HasPixels - Отсутствуют пикселы в изображении") << endl;
		return 1; // error
	}

	bitsBitmap = FreeImage_GetBits(parBitmap);
	if(NULL == bitsBitmap) // NULL if the bitmap does not contain pixel data
	{
		wcout << _TEXT("FreeImage_GetBits - Отсутствует доступ к пикселам") << endl;
		return 1; // error
	}
	return 0;
}

unsigned int PullBitmapPixel(unsigned int parX, unsigned int parY)
{
//	FIBITMAP *parBitmap = bitmap;
	FIBITMAP *parBitmap = gray4bit;
	unsigned int width = FreeImage_GetWidth(parBitmap);
	unsigned int height = FreeImage_GetHeight(parBitmap);
	unsigned int pitch = FreeImage_GetPitch(parBitmap);
	unsigned int byteLine = FreeImage_GetLine(parBitmap);
	unsigned int colorType = FreeImage_GetColorType(parBitmap);

//	unsigned int x, y;

	BYTE *bits = (BYTE*)FreeImage_GetBits(parBitmap);
//	*(bits + (index >> 1) + (index) * pitch) ^= (0x0001 & index) ? 0x0C : 0xC0;// grayscale 4 bit
	unsigned char twoPix = *(bits + (parX >> 1) + (parY * pitch));
	unsigned char onePix = (0x0001 & parX) ? (twoPix >> 4) : (twoPix & 0x0F);
	return onePix;
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

unsigned int PullLine(unsigned int parY)
{
	FIBITMAP *parBitmap = bitmap;
	if(parY >= FreeImage_GetHeight(parBitmap))
	{
		wcout << _TEXT("FreeImage_GetHeight - Вышли за высоту изображения. Y = ") << parY << endl;
		return 2; // out off range
	}

	bitsLine = (BYTE *)FreeImage_GetScanLine(parBitmap, parY);
	if(NULL == bitsLine)
	{
		wcout << _TEXT("FreeImage_GetScanLine - Отсутствует доступ к пикселам") << endl;
		return 1; // error
	}
	return 0;
}

unsigned int PullLinePixel(unsigned int * pPixel, unsigned int parX)
{
	FIBITMAP *parBitmap = bitmap;
	/*
	if(parX >= FreeImage_GetWidth(parBitmap))
	{
		wcout << _TEXT("FreeImage_GetHeight - Вышли за высоту изображения. X = ") << parX << endl;
		return 2; // out off range
	}*/

//	pPixel = bitsLine[parX >> 3]; // получаем байт картинки, восемь пикселов
//	* pPixel = (bitsLine[parX >> 3] & (0x80 >> (parX & 0x0003))) ? 1: 0; // получаем бит картинки
	BYTE pixels = bitsLine[parX >> 3];
	BYTE mask = 0x80 >> (parX & 0x0007); 
	* pPixel = (pixels & mask) ? 0: 1; // получаем бит картинки
	return 0;
}

unsigned int GetPixel(unsigned int parX, unsigned int parY)
{
	unsigned int x, y;
	FIBITMAP *parBitmap = bitmap;
	FREE_IMAGE_TYPE image_type = FreeImage_GetImageType(parBitmap);
	wcout << _TEXT("Формат изображения: ");
	switch(image_type) 
	{
	case FIT_UNKNOWN: wcout << _TEXT(" FIT_UNKNOWN") << endl;
		break;
	case FIT_BITMAP: wcout << _TEXT(" FIT_BITMAP") << endl;
		if(1 == FreeImage_GetBPP(parBitmap)) 
		{
			unsigned int H;
			for(y = 0; y < (H = FreeImage_GetHeight(parBitmap)); y++) 
			{
				BYTE *bits = (BYTE *)FreeImage_GetScanLine(parBitmap, y);
//				ofstream file;
//				file.open("E:\\GetScanLine.iii");
//				file << *bits;
//				file.close();
				cout << "y = " << (y * 100) / H << "                  \r";

				for(x = 0; x < FreeImage_GetWidth(parBitmap); x++) 
				{
//					bits[x] = 128;
					if((0 != bits[x]) && (3100 != x))
					{
//						wcout << _TEXT(" bits[x] = " << bits[x] << ", x = " << x << ", y = " << y << endl;
//						cout << "bits[x] = " << bits[x] << ", x = " << x << ", y = " << y << "\r";
//						return; // 
						break;
					}
				}
			}
		}
		break;
	}
	return 0;
}