
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

	void PutGerberHeader(void); // ����� ��������� � ������
	void PutGerberParameters(void); // ����� ��������� �������� � ������

	void PutGerberImageOutlineFill(void); // ������ �������� � ������ �������� �������
	void PutGerberImageLines(void); // ������ �������� � ������ ������� � ������ �������
	void PutGerberImageFlash(void); // ������ �������� � ������ ������ �������

	void PutGerberLine(int parBeginX, int parBeginY, int parEndX, int parEndY); // ������ ������ ����� �������� �� ����������� ������
	void PutGerberLine(int parBeginX, int parBeginY, int parEndX); // ������ �������������� ����� �� ������ ����� �� ����������� ������ ����� ���������� X
	void PutGerberFlash(int parBeginX, int parBeginY); // ������ ���� ���� �� �����������

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


