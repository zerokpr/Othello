#include "Button.h"
#include "Vector.h"

bool Button::ContainsPoint(const Vector2& pt){
	return (pt.x >= mPosition.x &&
		pt.x < (mPosition.x + mSize.x) &&
		pt.y >= mPosition.y &&
		pt.y < (mPosition.y + mSize.y));
}

void Button::OnClick() {
	if (mOnClick && mIsActivated) {
		mOnClick();
	}
}

void Button::Draw() {
	// �{�^���w�i�摜�`��
	if (mIsActivated) {
		if (mHighlighted) {
			mHighlightedTex->Draw(mPosition.x, mPosition.y, mSize.x, mSize.y);
		}
		else {
			mNormalTex->Draw(mPosition.x, mPosition.y, mSize.x, mSize.y);
		}
		// ������`��
		mFont->Draw(mPosition.x + mSize.x/5, mPosition.y + mSize.y/5, mName);
	}
}