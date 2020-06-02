#include "ScreenText.h"


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