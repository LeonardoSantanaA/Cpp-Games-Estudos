#pragma once

#include <string>
#include <functional>
#include "../Shapes/AARectangle.h"
#include "../Graphics/Color.h"
#include "../Graphics/BitmapFont.h"

class Screen;

class Button {
public:
	using ButtonAction = std::function<void(void)>;

	Button(const BitmapFont& bitmapFont, const Color& textColor, const Color& highlightColor = Color::White());
	void Init(const Vec2D& topLeft, unsigned int width, unsigned int height);
	void Draw(Screen& theScreen);
	void ExecuteAction();

	inline void SetButtonText(const std::string& text) { mTitle = text; }
	inline const std::string& GetButtonText() const { return mTitle; }
	inline void SetHighlighted(bool highlighted) { mHighlited = highlighted; }
	inline bool IsHightlighted() const { return mHighlited; }
	inline void SetButtonAction(Button::ButtonAction action) { mAction = action; }


private:
	const BitmapFont& mBitmapFont;
	std::string mTitle;
	AARectangle mBBox;

	bool mHighlited;
	ButtonAction mAction;
	Color mHighlightColor;
	Color mTextColor;
};