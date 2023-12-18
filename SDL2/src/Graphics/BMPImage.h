#pragma once

#include "Color.h"
#include <vector>
#include <string>
#include <stdint.h>

class BMPImage {
public:
	BMPImage();
	bool LoadFile(const std::string& path);

	inline const std::vector<Color>& GetPixels() const { return mPixels; }
	inline const uint32_t GetWidth() const { return mWidth; }
	inline const uint32_t GetHeight() const { return mHeight; }

private:
	std::vector<Color> mPixels;
	uint32_t mWidth;
	uint32_t mHeight;
};
