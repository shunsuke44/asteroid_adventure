#include <cassert>

#include "DxLib.h"

#include "Scene/SceneManager.h"
#include "Scene/Title.h"

namespace Scene {
	Title::Title() {
		mGraphicHandle = DxLib::LoadGraph("data/img/title.png");
		assert(mGraphicHandle != -1);
		mCount = 0;
	}

	Title::~Title() {
		DxLib::DeleteGraph(mGraphicHandle);
	}

	void Title::update() {
		if (mCount < 20) { // ƒV[ƒ“‘JˆÚŒã–³”½‰žŽžŠÔ
			++mCount;
			return;
		}
		if (DxLib::CheckHitKeyAll()) {
			SceneManager::instance()->moveTo(SceneManager::SCENE_TITLE_MENU);
		}
	}

	void Title::draw() const {
		DxLib::DrawGraph(0, 0, mGraphicHandle, FALSE);
	}
}
