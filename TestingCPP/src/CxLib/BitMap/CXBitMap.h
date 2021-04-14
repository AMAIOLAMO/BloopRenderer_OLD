#pragma once

#include "CXColor.h"
#include <fstream>
#include <vector>
//#include <array>

class CXBitMap
{
private:
	int _width, _height;
	std::vector<CXColor> _colors;

public:
	CXBitMap(int width, int height);

	CXColor GetColor(int x, int y) const;

	void SetColor(const CXColor& color, int x, int y);

	/// <summary>
	/// Get's the color vectors of this vector (readonly)
	/// </summary>
	const std::vector<CXColor>& GetColors() const;

	int GetWidth() const;

	int GetHeight() const;

	void ExportTo(const char* path) const;
};
