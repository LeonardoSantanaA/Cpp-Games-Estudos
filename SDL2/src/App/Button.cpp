#include "Button.h"
#include "../Graphics/Screen.h"

Button::Button(const BitmapFont& bitmapFont, const Color& textColor, const Color& highlightColor):
	mBitmapFont(bitmapFont), mTextColor(textColor), mHighlightColor(highlightColor), mTitle(""), mHighlited(false), mAction(nullptr)
{

}

void Button::Init(const Vec2D& topLeft, unsigned int width, unsigned int height) {
	mBBox = AARectangle(topLeft, width, height);
}

void Button::Draw(Screen& theScreen) {
	theScreen.Draw(mBitmapFont, mTitle, mBitmapFont.GetDrawPosition(mTitle, mBBox, BFXA_CENTER, BFYA_CENTER), mTextColor);

	if (mHighlited) {
		theScreen.Draw(mBBox, mHighlightColor);
	}
}

void Button::ExecuteAction() {
	mAction();
}