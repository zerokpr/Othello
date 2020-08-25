#include "ScreenText.h"

void ScreenText::ChangeText(const std::string text) {
	mText = text;
}

void ScreenText::Draw(void) {
	if (mIsActivated) {
		mFont->Draw(
			mPos.x, mPos.y,
			mText,
			mColor,
			mPointSize
		);
	}
}