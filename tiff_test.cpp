// tiff_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//	#include <gdiplus.h>

#pragma comment(lib,"FreeImage.lib")
//#pragma comment(lib,"FreeImaged.lib")

//#define UNICODE
//#define _UNICODE

// "E:\_prj_\VS\tiff_test\tiff\��� ����� � �������� �������\Marissa Mayer.jpg"
// "E:\_prj_\VS\tiff_test\tiff\��� ����� � �������� �������\eset_CCITT4.tif"
// "E:\_prj_\VS\tiff_test\tiff\��� ����� � �������� �������\small50x50b.TIF"
// "E:\_prj_\VS\tiff_test\tiff\��� ����� � �������� �������\small50x50bb.TIF"
// "E:\_prj_\VS\tiff_test\tiff\��� ����� � �������� �������\krevetka-0003.jpg"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
//int main(int argc, char* argv[])
{
	_tsetlocale( LC_ALL, _T("Russian"));

	cout << "argc: " << argc << endl;
	for(int index = 0; index < argc; index++)
	{
		wcout << "argv[ " << index << " ]: " << argv[index] << endl;
	}
	cout << endl;
	if(2 != argc)
	{
		wcout << _TEXT("��� �������������� ��������� ������� ��� ��������� ������������ �����") << endl;
		wcout << _TEXT("��������:") << endl;
		wcout << _TEXT("tiff2gerber.exe maket.tiff") << endl;
		_tsystem(_T("pause"));
		exit(1);
	}

	InitView();
//	LoadTIFF(&FileName);
	LoadTIFF(argv[1]);
	wcout << endl << _TEXT("�������� ����:") << endl;
	InfoTIFF(bitmap);
//	clone = FreeImage_ConvertToGreyscale(bitmap);

	wcout << endl << _TEXT("�����������:") << endl;
	clone = FreeImage_Threshold(bitmap, 127);
	SaveTIFF(clone, argv[1], _TEXT("_CCITT4.tiff"));
	InfoTIFF(clone);

	UnLoadTIFF(bitmap); // �������� �������� ���� ��������
	bitmap = clone; // ��������� ��������� �� ����

	int timeGerberLine = clock();
	{
		Gerber gerb(argv[1], _TEXT("_L.gbr"));
		gerb.CreateGerberLine();
//		gerb.CreateGerberFlash();
	}
	wcout << _TEXT("����� ��������� �����: ") << clock() - timeGerberLine << _TEXT(" ��") << endl;

//	SaveTIFF(clone, argv[1], _TEXT("_rebit.tiff"));

	wcout << endl << _TEXT("��� ������� �������:") << endl;
	gray4bit = FreeImage_ConvertTo4Bits(clone);
	gray8bit = FreeImage_ConvertTo8Bits(clone);
	UnLoadTIFF(clone);
	bitmap = gray8bit; // ��������� ��������� �� ����
	SaveTIFF(gray4bit, argv[1], _TEXT("_gray4bit.tiff"));
	SaveTIFF(gray8bit, argv[1], _TEXT("_gray8bit.tiff"));
	wcout << endl << _TEXT("����� 4 ���:") << endl;
	InfoTIFF(gray4bit);
	wcout << endl << _TEXT("����� 8 ���:") << endl;
	InfoTIFF(gray8bit);

	int timeGerberFill = clock();
	{
		Gerber gerb(argv[1], _TEXT("_F.gbr"));
		gerb.CreateGerberFill();
	}
	wcout << _TEXT("����� ��������� �����: ") << clock() - timeGerberFill << _TEXT(" ��") << endl;
	SaveTIFF(gray4bit, argv[1], _TEXT("_re4bit.tiff"));
	SaveTIFF(gray8bit, argv[1], _TEXT("_re8bit.tiff"));

	UnLoadTIFF(gray4bit);
	UnLoadTIFF(gray8bit);

//	cout << "������� <Enter> ��� �������� ����" << endl;
//	std::cin.get();  // �������� ������� ������� - �nter
//	cout << "������� ����� ������ ��� �������� ����" << endl;
//	_getch();
	_tsystem(_T("pause"));
//	system("pause"); � �������� #include <stdlib.h>.
	return 0;
}


