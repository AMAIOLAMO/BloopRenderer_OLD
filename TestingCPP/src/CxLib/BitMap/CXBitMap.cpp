#include "CXBitMap.h"

void FillUCharInUCharArray(unsigned char*, unsigned char, int, int);
void SetIntInUCharArray(unsigned char*, int, int);

CXBitMap::CXBitMap(int width, int height) :
	_width(width), _height(height), _colors(width* height) {}

CXColor CXBitMap::GetColor(int x, int y) const
{
	//x offset horizontal, _width * y offset vertical :D
	return _colors[x + _width * y];
}

void CXBitMap::SetColor(const CXColor& color, int x, int y)
{
	_colors[x + _width * y].SetColor(color);
}

const std::vector<CXColor>& CXBitMap::GetColors() const
{
	return _colors;
}

int CXBitMap::GetWidth() const
{
	return _width;
}

int CXBitMap::GetHeight() const
{
	return _height;
}

void CXBitMap::ExportTo(const char* path) const
{
	std::ofstream outStream;
	outStream.open(path, std::ios::out | std::ios::binary);

	//if not open
	if (!outStream.is_open())
	{
		outStream.close();
		throw std::exception("File cannot be opened...");
	}
	//else

	//char is simply 1 byte
	unsigned char bmpPad[3] = { 0, 0, 0 };
	
	//each color channel = 1 byte, which 1 color = 3 bytes, so we _width * 3
	const int PADDING_AMOUNT = (4 - (_width * 3) % 4) % 4;

	//in bytes
	const int FILE_HEADER_SIZE = 14;
	const int INFORMATION_HEADER_SIZE = 40;

	const char PIXEL_DATA_OFFSET = FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE;

	//file header + header's information +
	//width * height * color size -> 3 bytes + paddingAmount * height (each height has padding)
	const int FILE_SIZE = FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE + _width * _height * 3 + PADDING_AMOUNT * _height;

	unsigned char fileHeader[FILE_HEADER_SIZE];

	//file type
	fileHeader[0] = 'B';
	fileHeader[1] = 'M';

	//file size
	SetIntInUCharArray(fileHeader, 2, FILE_SIZE);
	/*fileHeader[2] = FILE_SIZE;
	fileHeader[3] = FILE_SIZE >> 8;
	fileHeader[4] = FILE_SIZE >> 16;
	fileHeader[5] = FILE_SIZE >> 24;*/

	// FillUCharInUCharArray(fileHeader, 0U, 6, 4);

	//reserved 1 (Not used)
	fileHeader[6] = 0; fileHeader[7] = 0;
	//reserved 2 (Not used)
	fileHeader[8] = 0; fileHeader[9] = 0;

	//pixel data offset
	fileHeader[10] = PIXEL_DATA_OFFSET;
	fileHeader[11] = 0; fileHeader[12] = 0; fileHeader[13] = 0;


	unsigned char informationHeader[INFORMATION_HEADER_SIZE];
	
	//header size
	informationHeader[0] = INFORMATION_HEADER_SIZE;
	informationHeader[1] = 0;
	informationHeader[2] = 0;
	informationHeader[3] = 0;

	//Image width
	SetIntInUCharArray(informationHeader, 4, _width);
	/*informationHeader[4] = _width;
	informationHeader[5] = _width >> 8;
	informationHeader[6] = _width >> 16;
	informationHeader[7] = _width >> 24;*/

	//Image height
	SetIntInUCharArray(informationHeader, 8, _height);
	/*informationHeader[8] = _height;
	informationHeader[9] = _height >> 8;
	informationHeader[10] = _height >> 16;
	informationHeader[11] = _height >> 24;*/

	// Planes
	informationHeader[12] = 1;
	informationHeader[13] = 0;
	// Bits per pixel (RGB)
	informationHeader[14] = 24;
	informationHeader[15] = 0;

	

#if 0
	//Compression (No Compression)
	FillUCharInUCharArray(informationHeader, 0, 16, 4);
	/*informationHeader[16] = 0; informationHeader[17] = 0;
	informationHeader[18] = 0; informationHeader[19] = 0;*/
	//Image size (No compression)
	FillUCharInUCharArray(informationHeader, 0, 20, 4);
	/*informationHeader[20] = 0; informationHeader[21] = 0;
	informationHeader[22] = 0; informationHeader[23] = 0;*/

	// X pixels per meter (Not specified)
	FillUCharInUCharArray(informationHeader, 0, 24, 4);
	/*informationHeader[24] = 0; informationHeader[25] = 0;
	informationHeader[26] = 0; informationHeader[27] = 0;*/
	// Y pixels per meter (Not specified)
	FillUCharInUCharArray(informationHeader, 0, 28, 4);
	/*informationHeader[28] = 0; informationHeader[29] = 0;
	informationHeader[30] = 0; informationHeader[31] = 0;*/

	// Total colors (not used)
	FillUCharInUCharArray(informationHeader, 0, 32, 4);
	/*informationHeader[32] = 0; informationHeader[33] = 0;
	informationHeader[34] = 0; informationHeader[35] = 0;*/
	
	// Important colors (ignored usually)
	FillUCharInUCharArray(informationHeader, 0, 36, 4);
	/*informationHeader[36] = 0; informationHeader[37] = 0;
	informationHeader[38] = 0; informationHeader[39] = 0;*/
#else
	//fill all :D
	FillUCharInUCharArray(informationHeader, 0, 16, 24);
#endif

	// ----------------------- WRITING OF BMP FILE ----------------------- //

	//file header n information header
	//write the file header as a char*
	outStream.write(reinterpret_cast<char*>(fileHeader), FILE_HEADER_SIZE);
	outStream.write(reinterpret_cast<char*>(informationHeader), INFORMATION_HEADER_SIZE);

	//pixels :D
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			CXColor color = GetColor(x, y);

			const float FLOATCOLOR_TO_UCHAR_SCALE = 255.0f;

			unsigned char ucharColor[] =
			{
				static_cast<unsigned char>(color.r * FLOATCOLOR_TO_UCHAR_SCALE),
				static_cast<unsigned char>(color.g * FLOATCOLOR_TO_UCHAR_SCALE),
				static_cast<unsigned char>(color.b * FLOATCOLOR_TO_UCHAR_SCALE)
			};

			//3 bytes 1 color :D
			outStream.write(reinterpret_cast<char*>(ucharColor), 3);
		}
		//each line finished remember to add padding hehe :D
		outStream.write(reinterpret_cast<char*>(bmpPad), PADDING_AMOUNT);
	}

	outStream.close();
}

//helper functions (local on this file scope only)
static void FillUCharInUCharArray(unsigned char* charArray, unsigned char value, int startIndex, int fillSize)
{
	for (int i = startIndex; i < startIndex + fillSize; i++)
		charArray[i] = value;
}

static void SetIntInUCharArray(unsigned char* charArray, int startIndex, int value)
{
	charArray[startIndex] = value;
	charArray[startIndex + 1] = value >> 8;
	charArray[startIndex + 2] = value >> 16;
	charArray[startIndex + 3] = value >> 24;
}
