#include <cassert>

#include "DxLib.h"

#include "buttons.h"

KeyButton* KeyButton::mInstance = nullptr;

void KeyButton::create() {
	assert(mInstance == nullptr);
	mInstance = new KeyButton();
}

void KeyButton::destroy() {
	delete mInstance;
	mInstance = nullptr;
}

KeyButton::KeyButton() {
	DxLib::LoadDivGraph("data/img/buttons.png", 5, 5, 1, 50, 20, mButtons);
}

KeyButton::~KeyButton() {
	for (int i = 0; i < 5; ++i) {
		DxLib::DeleteGraph(mButtons[i]);
	}
}

void KeyButton::drawButton(int x, int y, int idx) const {
	assert(idx >= 0 && idx < 5);
	DxLib::DrawGraph(x, y, mButtons[idx], TRUE);
}
