
#include "stdafx.h"

#pragma once
//#include <fstream>


class Gerber
{
	_TCHAR * pFileNameGerber;
	_TCHAR * pFileNameTIFF;
//	LPTSTR * pNameGerber;

	unsigned int colorType; // white / black

	unsigned int sizeXbitmap; // in pixel
	unsigned int sizeYbitmap; // in pixel
	double sizeXpixel; // in mm
	double sizeYpixel; // in mm

private:
//	ofstream fileGerber;

	void PutGerberHeader(void); // пишем заголовок в гербер
	void PutGerberParameters(void); // пишем параметры картинки в гербер

	void PutGerberImageOutlineFill(void); // рисуем картинку в гербер контуром заливки
	void PutGerberImageLines(void); // рисуем картинку в гербер линиями и иногда флешами
	void PutGerberImageFlash(void); // рисуем картинку в гербер просто флешами

	void PutGerberLine(int parBeginX, int parBeginY, int parEndX, int parEndY); // рисуем прямую линию наклонно по координатам концов
	void PutGerberLine(int parBeginX, int parBeginY, int parEndX); // рисуем горизонтальную линию по первой точки по координатам первой точки координате X
	void PutGerberFlash(int parBeginX, int parBeginY); // ставим один флеш по координатам

public:
	Gerber(void);
	Gerber(const _TCHAR * parFileName, const _TCHAR * parNameSufix);
	~Gerber(void);

//	void CreateGerber(void);
	void CreateGerberFlash(void);
	void CreateGerberLine(void);
	void CreateGerberFill(void);

};


extern std::ofstream fileGerber;


