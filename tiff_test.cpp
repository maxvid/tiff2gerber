// tiff_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//	#include <gdiplus.h>

#pragma comment(lib,"FreeImage.lib")
//#pragma comment(lib,"FreeImaged.lib")

//#define UNICODE
//#define _UNICODE

// "E:\_prj_\VS\tiff_test\tiff\тут папка с русскими буквами\Marissa Mayer.jpg"
// "E:\_prj_\VS\tiff_test\tiff\тут папка с русскими буквами\eset_CCITT4.tif"
// "E:\_prj_\VS\tiff_test\tiff\тут папка с русскими буквами\small50x50b.TIF"
// "E:\_prj_\VS\tiff_test\tiff\тут папка с русскими буквами\small50x50bb.TIF"
// "E:\_prj_\VS\tiff_test\tiff\тут папка с русскими буквами\krevetka-0003.jpg"

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
		wcout << _TEXT("Для преобразования требуется указать имя исходного графического файла") << endl;
		wcout << _TEXT("Например:") << endl;
		wcout << _TEXT("tiff2gerber.exe maket.tiff") << endl;
		_tsystem(_T("pause"));
		exit(1);
	}

	InitView();
//	LoadTIFF(&FileName);
	LoadTIFF(argv[1]);
	wcout << endl << _TEXT("Исходный файл:") << endl;
	InfoTIFF(bitmap);
//	clone = FreeImage_ConvertToGreyscale(bitmap);

	wcout << endl << _TEXT("Двухцветный:") << endl;
	clone = FreeImage_Threshold(bitmap, 127);
	SaveTIFF(clone, argv[1], _TEXT("_CCITT4.tiff"));
	InfoTIFF(clone);

	UnLoadTIFF(bitmap); // выгрузим исходный файл картинки
	bitmap = clone; // скопируем указатель на клон

	int timeGerberLine = clock();
	{
		Gerber gerb(argv[1], _TEXT("_L.gbr"));
		gerb.CreateGerberLine();
//		gerb.CreateGerberFlash();
	}
	wcout << _TEXT("Время обработки файла: ") << clock() - timeGerberLine << _TEXT(" мс") << endl;

//	SaveTIFF(clone, argv[1], _TEXT("_rebit.tiff"));

	wcout << endl << _TEXT("Для анализа заливки:") << endl;
	gray4bit = FreeImage_ConvertTo4Bits(clone);
	gray8bit = FreeImage_ConvertTo8Bits(clone);
	UnLoadTIFF(clone);
	bitmap = gray8bit; // скопируем указатель на клон
	SaveTIFF(gray4bit, argv[1], _TEXT("_gray4bit.tiff"));
	SaveTIFF(gray8bit, argv[1], _TEXT("_gray8bit.tiff"));
	wcout << endl << _TEXT("Серый 4 бит:") << endl;
	InfoTIFF(gray4bit);
	wcout << endl << _TEXT("Серый 8 бит:") << endl;
	InfoTIFF(gray8bit);

	int timeGerberFill = clock();
	{
		Gerber gerb(argv[1], _TEXT("_F.gbr"));
		gerb.CreateGerberFill();
	}
	wcout << _TEXT("Время обработки файла: ") << clock() - timeGerberFill << _TEXT(" мс") << endl;
	SaveTIFF(gray4bit, argv[1], _TEXT("_re4bit.tiff"));
	SaveTIFF(gray8bit, argv[1], _TEXT("_re8bit.tiff"));

	UnLoadTIFF(gray4bit);
	UnLoadTIFF(gray8bit);

//	cout << "Нажмите <Enter> для закрытия окна" << endl;
//	std::cin.get();  // Ожидание нажатия клавиши - Еnter
//	cout << "Нажмите любую кнопку для закрытия окна" << endl;
//	_getch();
	_tsystem(_T("pause"));
//	system("pause"); и включить #include <stdlib.h>.
	return 0;
}


