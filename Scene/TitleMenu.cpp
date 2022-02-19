#include <cassert>

#include "DxLib.h"

#include "Scene/SceneManager.h"
#include "Scene/TitleMenu.h"

namespace Scene {
	TitleMenu::TitleMenu() : mSelected(0), mPrevPushed(false) {
		mGraphicHandle = DxLib::LoadGraph("data/img/title_menu.png");
		assert(mGraphicHandle != -1);
		mArrowGH = DxLib::LoadGraph("data/img/arrow.png");
		assert(mArrowGH != -1);
		mMenu.emplace_back(155, 275); // タイトルに戻る
		mMenu.emplace_back(155, 371); // ゲームスタート
		mCount = 0;
	}

	TitleMenu::~TitleMenu() {
		DxLib::DeleteGraph(mGraphicHandle);
	}

	void TitleMenu::update() {
		if (mCount < 20) { // シーン遷移後無反応時間
			++mCount;
			return;
		}
		char key[256];
		DxLib::GetHitKeyStateAll(key);
		if (key[KEY_INPUT_W]) {
			if (!mPrevPushed) {
				--mSelected;
				if (mSelected < 0) mSelected += mMenu.size();
			}
			mPrevPushed = true;
		}
		else if (key[KEY_INPUT_S]) {
			if (!mPrevPushed) {
				++mSelected;
				if (mSelected >= mMenu.size()) mSelected -= mMenu.size();
			}
			mPrevPushed = true;
		}
		else if (key[KEY_INPUT_SPACE]) {
			if (!mPrevPushed) {
				if (mSelected == 0) {
					SceneManager::instance()->moveTo(SceneManager::SCENE_TITLE);
				}
				else if (mSelected == 1) {
					SceneManager::instance()->moveTo(SceneManager::SCENE_GAME);
				}
			}
			mPrevPushed = true;
		}
		else {
			mPrevPushed = false;
		}
	}

	void TitleMenu::draw() const {
		DxLib::DrawGraph(0, 0, mGraphicHandle, FALSE);
		DxLib::DrawGraph(mMenu[mSelected].first, mMenu[mSelected].second, mArrowGH, TRUE);
	}
}