#pragma once

#define GRAY_BLACK 0x00
#define GRAY_WHITE 0xFF
#define GRAY_FIND_FILL 0x80

class OutlineFill
{
	FIBITMAP *m_DIB;
public:
	OutlineFill(void);
	OutlineFill(FIBITMAP *parDIB);
	~OutlineFill(void);
private:
	int m_IDFill;
	char * m_szBound;
	int m_OutVert;
	int m_InVert;
	int m_CellNum;
public:
	unsigned int m_BitPerPixel;
	unsigned int m_Width;
	unsigned int m_Height;
	unsigned int m_Pitch;
	unsigned int m_ByteLine;
	unsigned int m_ColorType;
	BYTE * p_Bits;

	unsigned int m_countBlackPixel;
	unsigned int m_numMinX;
	unsigned int m_numMinY;
	unsigned int m_numMaxX;
	unsigned int m_numMaxY;

	void FindFillBitmap(void);
};
