#include "stdafx.h"
//#include "Gerber.h"

//using namespace std;

/*	
strcmp() ���������� ��� ������ (������ �������� ==)
strncmp()���������� ����� ���� �����
strcat()��������� ��� ������ (������ �������� +)
strncat()��������� � ������ �������� ������
strchr()������� ������ ��������� � � ����� ��������� �������
strrchr()������� ��������� ��������� ��������� �������
strstr()������� ������ ��������� �������� ������
strcpy()�������� ���� ������ � ������ (������ �������� =)
strncpy()�������� ����� ����� ������ � ������
strlen()���������� ����� ������
strlwr()��������� ��� ������ � ������ �������
strupr()��������� ��� ������ � ������� �������
strnset()� ������ ������ �� N �������� ��������
strtok()��������� ������ �� ���������
str�spn()���������� ������ ������� ������� ������, ������� ����������� ��������� ������������������ �������� 
strspn() ���������� ������ ������� ������� ������, ������� �� ����������� ��������� ������������������ ��������
_strspnp() ���������� ��������� (�������� ������), ������� ���������� � ������� �������������� � ������ ������
_strrev() �������������� ������
_memccpy() �������� ������� �� ����� ������ � ������ �� ��������� �������, �� �� ����� �������� �����
memcpy()�������� �� ����� ������ � ������ �������� ���-�� ��������
isalpha()���������, �������� �� ������ ������
isalnum()���������, �������� �� ������ ������ ��� ��� ���
iscntrl()���������, �������� �� ������ �����������
islower()���������, ��������� �� ������ � ������ ��������
isupper()���������, ��������� �� ������ � ������� ��������
isspace()���������, �������� �� ������ ������������
ispunct()���������, �������� �� ������ �������� ����������
*/

std::ofstream fileGerber;

Gerber::Gerber(const _TCHAR * parFileName, const _TCHAR * parNameSufix)
{
	sizeXbitmap = GetBitmapSizeX(); // in pixel
	sizeYbitmap = GetBitmapSizeY(); // in pixel
	sizeXpixel = GetPixelSizeX(); // in mm
	sizeYpixel = GetPixelSizeY(); // in mm
	colorType = GetColorType(); // ����� ��� ������ �������� �����

	int sizeStringFileName = 50 + _tcslen(parFileName) * sizeof(*parFileName);

	pFileNameTIFF = NULL;
	pFileNameTIFF = new _TCHAR[sizeStringFileName];
	if(NULL == pFileNameTIFF)
	{
		wcout << _TEXT("������ ����������, ������ ����������.") << endl << _TEXT("��������� ����� �������.") << endl;
		_tsystem(_T("pause"));
		exit(1);
	}
	_tcscpy_s(pFileNameTIFF, sizeStringFileName, parFileName);

	pFileNameGerber = NULL;
	pFileNameGerber = new _TCHAR[sizeStringFileName];
	if(NULL == pFileNameGerber)
	{
		wcout << _TEXT("������ ����������, ������ ����������.") << endl << _TEXT("��������� ����� �������.") << endl;
		_tsystem(_T("pause"));
		exit(1);
	}
	_tcscpy_s(pFileNameGerber, sizeStringFileName, parFileName);
//	_tcscpy_s(_tcsrchr(pFileNameGerber, _T('.')), 50, _TEXT(".grb")); // ������������ ��� ������� � ��������� �����
	_tcscpy_s(_tcsrchr(pFileNameGerber, _T('.')), 50, parNameSufix); // ������������ ��� ������� � ��������� �����
	wcout << _TEXT("������� ����: ") << endl << pFileNameGerber << endl;

//***************************************************************//
//������� ���� ��� ������
//***************************************************************//
//	ofstream fileGerber;
//	ofstream fileGerber;
//    fileGerber.open(pFileNameGerber, ios::in | ios::out | ios::binary);// ���� ��������� �� ������, �� ���� ��� ������ ������������! ����� ����� ������� ������� ����
    fileGerber.open(pFileNameGerber, ios::out | ios::binary);
	if (!fileGerber.is_open())
	{
		//���� ���� �� ����������, �� ������� ����
        wcout << _TEXT("�������� ������� gerber ����. ������ �� ��� ����������, ������� ���. ���� � ��� ��� ���� �� ������ � ��� �����.") << endl << _TEXT("��������� ����� �������") << endl;
		_tsystem(_T("pause"));
		exit(1);
	}

	//���� ���� �� ����������, �� ������� ����
//	cout << "File is created" << endl;
//	fileGerber.open(pFileNameGerber, ios::out | ios::binary);
//	fileGerber.close();
		// ��������� ��������� ����
//		fileGerber.open(pFileNameGerber, ios::in | ios::out | ios::binary);
//	fileGerber.open(pFileNameGerber, ios::out | ios::binary);
	wcout << _TEXT("Gerber File is Opened") << endl;
//				fileGerber << _TEXT("����� �����-������") << endl;
//				fileGerber << _TCHAR("����� �����-������") << endl;
/////////	fileGerber << ("��������� gerber-�") << endl;
//		if(fileGerber.eof()) { fileGerber.clear(); }
//	fileGerber.close();
}

Gerber::Gerber(void)
{
	pFileNameGerber = NULL;
	pFileNameTIFF = NULL;
}

Gerber::~Gerber(void)
{
	if(NULL != pFileNameGerber)
	{
		delete [] pFileNameGerber;
		pFileNameGerber = NULL;
	}
	if(NULL != pFileNameTIFF)
	{
		delete [] pFileNameTIFF;
		pFileNameTIFF = NULL;
	}
    if (fileGerber.is_open())
	{
//        wcout << _TEXT("��������� gerber") << endl;
//		fileGerber << ("��������� gerber") << endl;

		// M02 - End of program
		fileGerber << "M02*" << "\r\n";
		fileGerber.close();
    }
}

void Gerber::CreateGerberFlash(void)
{
	PutGerberHeader(); // 1
	PutGerberParameters(); // 2
	PutGerberImageFlash(); // ������ �������� � ������ ������ �������
}

void Gerber::CreateGerberLine(void)
{
	PutGerberHeader(); // 1
	PutGerberParameters(); // 2
	PutGerberImageLines(); // ������ �������� � ������ ������� � ������ �������
}

void Gerber::CreateGerberFill(void)
{
	PutGerberHeader(); // 1
	PutGerberParameters(); // 2
	PutGerberImageOutlineFill(); // ������ �������� � ������ �������� �������
}

void Gerber::PutGerberHeader(void)
{
//	fileGerber << ("��������� gerber-�") << endl;
	fileGerber << "G04 tiff2gerber" << " *\r\n";
	fileGerber << "G04 FreeImage Version " << FreeImage_GetVersion() << " *\r\n";

//////////////////////////////////////////////////////////////////////////
// ������� ������ ������� ���� � ����� � ������ ����
	time_t rawtime; // calendar time
	struct tm timeinfo;
	const int buffer_size = 256;//
	_TCHAR _tbuffer[buffer_size]; 
	char buffer[buffer_size]; 
	time( &rawtime ); // get current cal time
	if(0 == localtime_s(&timeinfo, &rawtime))
	{
		if(0 == _tasctime_s(_tbuffer, buffer_size, &timeinfo))
		{
			wcout << _TEXT("Current time and date: ") << _tbuffer << endl;
		}
		if(0 == asctime_s(buffer, buffer_size, &timeinfo))
		{
			int n = strlen(buffer);
			buffer[n - 1] = 0;
			fileGerber << "G04 Current time and date: " << buffer << " *\r\n";
		}
	}
//////////////////////////////////////////////////////////////////////////
// ������� ������ ���� � ��� ��������� ����� � ������ ����
	size_t nByte;
	if(0 == _wcstombs_s_l(&nByte, buffer, 255, pFileNameTIFF, 255,  _create_locale(LC_ALL, ("Russian"))))
	{
		fileGerber << "G04 Input File: \"" << buffer <<  "\" *\r\n"; // ���� � �������� ""
	}
}

void Gerber::PutGerberParameters(void)
{
//////////////////////////////////////////////////////////////////////////
// ������� ��������� ����������� �������
	// FS - Format Specification
	// D - none omit zeroes
	// L - omit leading zeroes
	// A - absolute coordinate values
	// X44 - 4 of integer and 4 of decimal places in the X coordinate data
	// Y44 - 4 of integer and 4 of decimal places in the Y coordinate data
//	fileGerber << "%FSDAX44Y44*%" << "\r\n";
	fileGerber << "%FSLAX44Y44*%" << "\r\n";

	//MO - MOde of data
	//MM - specify units in millimeter
	fileGerber << "%MOMM*%" << "\r\n";

	// SF - Scale Factor
	// A - A-axis data scale factor
	// B - B-axis data scale factor
	fileGerber << "%SFA1.000B1.000*%" << "\r\n";
	fileGerber << "\r\n";

	// MI - Mirror Image
	// A0 - A-axis disable mirror
	// B0 - B-axis disable mirror
	fileGerber << "%MIA0B0*%" << "\r\n";

	// IP - Image Polarity
	// POS - output the image with positive polarity
	fileGerber << "%IPPOS*%" << "\r\n";

	// AD - Aperture Difinition
	// D - D-code
	// 99 - D-code number define
	// R, - Rectangle or Square
	// 0.01000X - X axis dimension
	// 0.01000 - Y axis dimension
	fileGerber << "%ADD98R,0.01000X0.01000*%" << "\r\n";

	{// ������� ���������� �������� � D-����� D99 �� ������� ������� ���� ��� ������� �� �������
		char buffer[50];
		sprintf_s(buffer, 50, "%6.5f", 0.002 + sizeXpixel); // ���� ��� �������
		buffer[1] = '.';
		fileGerber << "%ADD99R," << buffer;
		sprintf_s(buffer, 50, "%6.5f", 0.002 + sizeYpixel); // ���� ��� �������
		buffer[1] = '.';
		fileGerber << "X" << buffer << "*%" << "\r\n";
	}

	// LN - Layer Name
	fileGerber << "%LNtiff_line*%" << "\r\n";

	// LP - Layer Polarity
	// D - dark polarity
	fileGerber << "%LPD*%" << "\r\n";
}

void Gerber::PutGerberImageLines(void)
{
	//G54 - Select Aperture
	fileGerber << "G54D99*" << "\r\n";

	//D01 - Draw mode on
	//D02 - Draw mode off
	//G36 - Turn on Outline Fill
	//G37 - Turn off Outline Fill
	//G01 - Set Linear Interpolation Mode
	//G04 - Ignore Data Block

//	fileGerber << "X00000250Y00000900D02*" << "\r\n";
//	fileGerber << "G01X00000700D01*" << "\r\n";

//	PutGerberLine(5, 13, 43, 17);
//	Gerber::PutGerberLine(7, 4, 15);
//	PutGerberFlash(9, 8);

/////////////////////////////////////////////////////////////
// ������ ����� �� ������� �������
/*	PutGerberLine(0, 0, sizeXbitmap, 0);
	PutGerberLine(sizeXbitmap, 0, sizeXbitmap, sizeYbitmap);
	PutGerberLine(sizeXbitmap, sizeYbitmap + 1, 0, sizeYbitmap + 1);
	PutGerberLine(0, sizeYbitmap, 0, 0);*/
	PutGerberLine(-1, -2, sizeXbitmap, -2);
	PutGerberLine(sizeXbitmap + 1, -1, sizeXbitmap + 1, sizeYbitmap);
	PutGerberLine(sizeXbitmap, sizeYbitmap + 1, -1, sizeYbitmap + 1);
	PutGerberLine(-2, sizeYbitmap, -2, -1);

/////////////////////////////////////////////////////////////
// ������ ����� � �����
/*	PutGerberFlash(1, 1);
	PutGerberFlash(sizeXbitmap - 1, 1);
	PutGerberFlash(sizeXbitmap - 1, sizeYbitmap - 1);
	PutGerberFlash(1, sizeYbitmap - 1);*/
	PutGerberFlash(-1, -1);
	PutGerberFlash(sizeXbitmap, -1);
	PutGerberFlash(sizeXbitmap, sizeYbitmap);
	PutGerberFlash(-1, sizeYbitmap);

/////////////////////////////////////////////////////////////
// ������� ������� �������� (� ����� ��� ��������� �����)
//	PullLine(unsigned int parY);
//	PullLinePixel(unsigned int parX);
	PullBitmap();
	unsigned int Pixel;
	unsigned int x, y;
	unsigned int beginX, beginY;
	unsigned int endX, endY;
	unsigned int flag = 0;
	for(y = 0; y < sizeYbitmap; y++)
	{
		PullLine(y);
		cout << "  " << (y * 100) / sizeYbitmap << " %                  \r";
		for(x = 0; x < sizeXbitmap; x++)
		{
			PullLinePixel(&Pixel, x);
			if(!flag)
			{
				if(colorType == Pixel)
				{
					beginX = x, beginY = y;
					flag = 1;
				}
			}
			else
			{
				if(colorType != Pixel)
				{
					endX = x - 1, endY = y;
					flag = 0;
					PutGerberLine(beginX, beginY, endX, endY);
//					PutGerberLine(beginX, beginY, endX);
				}
			}
		}
		if(!flag)
		{
//			if(colorType != Pixel)
			{
				beginX = x, beginY = y;
				flag = 1;
			}
		}
		else
		{
//			if(colorType == Pixel)
			{
//				endX = x - 1, endY = y;
				endX = x - 1, endY = y;
				flag = 0;
				PutGerberLine(beginX, beginY, endX, endY);
//				PutGerberLine(beginX, beginY, endX);
			}
		}
		flag = 0;
		fileGerber.flush();
	}
}

void Gerber::PutGerberImageFlash(void)
{
	//G54 - Select Aperture
	fileGerber << "G54D99*" << "\r\n";

	//D01 - Draw mode on
	//D02 - Draw mode off
	//G36 - Turn on Outline Fill
	//G37 - Turn off Outline Fill
	//G01 - Set Linear Interpolation Mode
	//G04 - Ignore Data Block

//	fileGerber << "X00000250Y00000900D02*" << "\r\n";
//	fileGerber << "G01X00000700D01*" << "\r\n";

//	PutGerberLine(5, 13, 43, 17);
//	Gerber::PutGerberLine(7, 4, 15);
//	PutGerberFlash(9, 8);

/////////////////////////////////////////////////////////////
// ������ ����� �� ������� �������
/*	PutGerberLine(0, 0, sizeXbitmap, 0);
	PutGerberLine(sizeXbitmap, 0, sizeXbitmap, sizeYbitmap);
	PutGerberLine(sizeXbitmap, sizeYbitmap + 1, 0, sizeYbitmap + 1);
	PutGerberLine(0, sizeYbitmap, 0, 0);*/
	PutGerberLine(-1, -2, sizeXbitmap, -2);
	PutGerberLine(sizeXbitmap + 1, -1, sizeXbitmap + 1, sizeYbitmap);
	PutGerberLine(sizeXbitmap, sizeYbitmap + 1, -1, sizeYbitmap + 1);
	PutGerberLine(-2, sizeYbitmap, -2, -1);

/////////////////////////////////////////////////////////////
// ������ ����� � �����
/*	PutGerberFlash(1, 1);
	PutGerberFlash(sizeXbitmap - 1, 1);
	PutGerberFlash(sizeXbitmap - 1, sizeYbitmap - 1);
	PutGerberFlash(1, sizeYbitmap - 1);*/
	PutGerberFlash(-1, -1);
	PutGerberFlash(sizeXbitmap, -1);
	PutGerberFlash(sizeXbitmap, sizeYbitmap);
	PutGerberFlash(-1, sizeYbitmap);

/////////////////////////////////////////////////////////////
// ������� ������� ��������
	PullBitmap();
	unsigned int Pixel;
	unsigned int x, y;
	for(y = 0; y < sizeYbitmap; y++)
	{
		PullLine(y);
		cout << "y = " << (y * 100) / sizeYbitmap << "                  \r";
		for(x = 0; x < sizeXbitmap; x++)
		{
			PullLinePixel(&Pixel, x);
			if(Pixel)
			{
				PutGerberFlash(x, y);
			}
		}
		fileGerber.flush();
	}
}

void Gerber::PutGerberLine(int parBeginX, int parBeginY, int parEndX, int parEndY)
{
	if((parBeginX == parEndX) && (parBeginY == parEndY)) PutGerberFlash(parBeginX, parBeginY);
	long val;
	char buffer[50];
//	fileGerber << "X00000250Y00000900D02*" << "\r\n";
//	fileGerber << "G01X00000700Y00000900D01*" << "\r\n";
//	val = static_cast<long>(100000000 + 10000 * sizeXpixel * parBeginX + 0.5);
	val = static_cast<long>(10000 * sizeXpixel * parBeginX + 0.5);
	_ltoa_s(val , buffer, 50, 10);
//	fileGerber << 'X' << buffer + 1; 
	fileGerber << 'X' << buffer; 
//	val = static_cast<long>(100000000 + 10000 * sizeYpixel * parBeginY + 0.5);
	val = static_cast<long>(10000 * sizeYpixel * parBeginY + 0.5);
	_ltoa_s(val , buffer, 50, 10);
//	fileGerber << 'Y' << buffer + 1 << "D02*\r\n"; 
	fileGerber << 'Y' << buffer << "D02*\r\n"; 
//	val = static_cast<long>(100000000 + 10000 * sizeXpixel * parEndX + 0.5);
	val = static_cast<long>(10000 * sizeXpixel * parEndX + 0.5);
	_ltoa_s(val , buffer, 50, 10);
//	fileGerber << "G01X" << buffer + 1; 
	fileGerber << "G01X" << buffer; 
//	val = static_cast<long>(100000000 + 10000 * sizeYpixel * parEndY + 0.5);
	val = static_cast<long>(10000 * sizeYpixel * parEndY + 0.5);
	_ltoa_s(val , buffer, 50, 10);
//	fileGerber << 'Y' << buffer + 1 << "D01*\r\n"; 
	fileGerber << 'Y' << buffer << "D01*\r\n"; 
}

void Gerber::PutGerberLine(int parBeginX, int parBeginY, int parEndX)
{
	if(parBeginX == parEndX) PutGerberFlash(parBeginX, parBeginY);
	long val;
	char buffer[50];
//	fileGerber << "X00000250Y00000900D02*" << "\r\n";
//	fileGerber << "G01X00000700D01*" << "\r\n";
//	val = static_cast<long>(100000000 + 10000 * sizeXpixel * parBeginX + 0.5);
	val = static_cast<long>(10000 * sizeXpixel * parBeginX + 0.5);
	_ltoa_s(val , buffer, 50, 10);
//	fileGerber << 'X' << buffer + 1; 
	fileGerber << 'X' << buffer; 
//	val = static_cast<long>(100000000 + 10000 * sizeYpixel * parBeginY + 0.5);
	val = static_cast<long>(10000 * sizeYpixel * parBeginY + 0.5);
	_ltoa_s(val , buffer, 50, 10);
//	fileGerber << 'Y' << buffer + 1 << "D02*\r\n"; 
	fileGerber << 'Y' << buffer << "D02*\r\n"; 
//	val = static_cast<long>(100000000 + 10000 * sizeXpixel * parEndX + 0.5);
	val = static_cast<long>(10000 * sizeXpixel * parEndX + 0.5);
	_ltoa_s(val , buffer, 50, 10);
//	fileGerber << "G01X" << buffer + 1 << "D01*\r\n"; 
	fileGerber << "G01X" << buffer << "D01*\r\n"; 
}

void Gerber::PutGerberFlash(int parX, int parY)
{
	long val;
	char buffer[50];
//	fileGerber << "X00000250Y00000900D03*" << "\r\n";
//	val = static_cast<long>(100000000 + 10000 * sizeXpixel * parX + 0.5);
	val = static_cast<long>(10000 * sizeXpixel * parX + 0.5);
	_ltoa_s(val , buffer, 50, 10);
//	fileGerber << 'X' << buffer + 1; 
	fileGerber << 'X' << buffer; 
//	val = static_cast<long>(100000000 + 10000 * sizeYpixel * parY + 0.5);
	val = static_cast<long>(10000 * sizeYpixel * parY + 0.5);
	_ltoa_s(val , buffer, 50, 10);
//	fileGerber << 'Y' << buffer + 1 << "D03*\r\n"; 
	fileGerber << 'Y' << buffer << "D03*\r\n"; 
}
