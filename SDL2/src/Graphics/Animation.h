#pragma once

#include "../Utils/Vec2D.h"
#include "Color.h"
#include <vector>
#include <string>

struct AnimationFrame {
	std::string frame = "";
	std::string overlay = "";
	Color frameColor = Color::White();
	Color overlayColor = Color::White();
	Size size;
	Vec2D offset = Vec2D::Zero;
	int frameColorSet = 0;
};

class Animation {
public:
	Animation();

	AnimationFrame GetAnimationFrame(uint32_t frameNum) const;

	inline void AddFrame(const std::string& frame) { mFrames.push_back(frame); }
	inline void AddFrameColor(const Color& color) { mFrameColors.push_back(color); }
	inline void AddOverlayFrameColor(const Color& color) { mOverlayColors.push_back(color); }
	inline void AddFrameOffset(const Vec2D& offset) { mFrameOffsets.push_back(offset); }

	inline void SetSpriteSheetName(const std::string& spriteSheetName) { mSpriteSheetName = spriteSheetName; }
	inline const std::string& GetSpriteSheetName() const { return mSpriteSheetName; }

	inline void SetName(const std::string& animationName) { mAnimationName = animationName; }
	inline const std::string& GetName() const { return mAnimationName; }

	inline void SetSize(const Vec2D& size) { mSize = size; }
	inline Vec2D GetSize() const { Return mSize; }

	inline SetFPS(int fps) { mFPS = fps; }
	inline int GetFPS() const { return mFPS; }

	inline void SetOverlayName(const std::string& overlayName) { mOverlay = overlayName; }
	inline const std::string& GetOverlayName() const { return mOverlay; }

	inline size_t GetNumFrames() const { return mFrames.size(); }
	inline size_t GetNumFrameColors() const { return mFrameColors.size(); }
	inline size_t GetNumOverlayColors() const { return mOverlayColors.size(); }
	inline size_t GetNumFrameOffsets() const { return mFrameOffsets.size(); }

private:
	std::string mAnimationName;
	std::string mSpriteSheetName;
	std::string mOverlay;
	std::vector<std::string> mFrames;
	std::vector<Color> mFrameColors;
	std::vector<Color> mOverlayColors;
	std::vector<Vec2D> mFrameOffsets;
	Vec2D mSize;
	int mFPS;
};