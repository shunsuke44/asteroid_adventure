#include <cassert>

#include "DxLib.h"

#include "buttons.h"
#include "Scene/SceneManager.h"
#include "Scene/Game/GameAssets.h"
#include "Scene/Game/GameManager.h"
#include "Scene/Game/GamePause.h"
#include "Scene/Game/GamePlay.h"

static const char* menu_str[] = {
	"�Q�[���ɖ߂�",
	"���g���C",
	"���j���[�ɖ߂�",
};

namespace Scene {
	namespace Game {
		GamePause::GamePause(GameManager* gm) : mGameManager(gm) {
			mGraphicHandle = DxLib::LoadGraph("data/img/pause_menu.png");
			assert(mGraphicHandle != -1);
			mArrowGH = DxLib::LoadGraph("data/img/arrow.png");
			assert(mArrowGH != -1);
			mGameAssets = GameAssets::instance();
			mCount = 0;
			mSelected = 0;
			mPrevPushed = false;
			mMenu.emplace_back(179, 170); // �Q�[���ɖ߂�
			mMenu.emplace_back(179, 256); // ���g���C
			mMenu.emplace_back(179, 337); // ���j���[�ɖ߂�
			mMenuStr.emplace_back(234, 176, "�Q�[���ɖ߂�");
			mMenuStr.emplace_back(234, 260, "���g���C");
			mMenuStr.emplace_back(234, 344, "���j���[�ɖ߂�");
			mMenuFont = DxLib::CreateFontToHandle("MS P�S�V�b�N", 30, 9, DX_FONTTYPE_ANTIALIASING);
			mKeyFont = DxLib::CreateFontToHandle("MS P�S�V�b�N", 24, -1, DX_FONTTYPE_ANTIALIASING);
			mMenuColor = DxLib::GetColor(8, 49, 0);
			mKeyColor = DxLib::GetColor(8, 49, 0);
		}

		GamePause::~GamePause() {
			DxLib::DeleteGraph(mGraphicHandle);
			DxLib::DeleteGraph(mArrowGH);
		}

		void GamePause::update() {
			if (mCount < 20) {
				++mCount;
				return;
			}
			char buf[256];
			DxLib::GetHitKeyStateAll(buf);
			if (buf[KEY_INPUT_W]) {
				if (!mPrevPushed) {
					--mSelected;
					if (mSelected < 0) mSelected += mMenu.size();
				}
				mPrevPushed = true;
			}
			else if (buf[KEY_INPUT_S]) {
				if (!mPrevPushed) {
					++mSelected;
					if (mSelected >= mMenu.size()) mSelected -= mMenu.size();
				}
				mPrevPushed = true;
			}
			else if (buf[KEY_INPUT_SPACE]) {
				if (mSelected == 0) {
					mGameManager->moveTo(GameManager::SCENE_GAMEPLAY);
					return;
				}
				if (mSelected == 1) {
					mGameManager->moveTo(GameManager::SCENE_RETRY);
					return;
				}
				if (mSelected == 2) {
					SceneManager::instance()->moveTo(SceneManager::SCENE_TITLE_MENU);
				}
			}
			else mPrevPushed = false;
			// TODO:
		}

		void GamePause::draw() const {
			DxLib::DrawGraph(0, 0, mGameAssets->getBackground(), FALSE);
			DxLib::DrawGraph(0, 0, mGraphicHandle, TRUE);
			for (const auto& t : mMenuStr) {
				int x, y;
				std::string s;
				std::tie(x, y, s) = t;
				DxLib::DrawStringToHandle(x, y, s.c_str(), mMenuColor, mMenuFont);
			}
			KeyButton* button = KeyButton::instance();
			button->drawButton(830, 580, 2);
			button->drawButton(830, 618, 3);
			button->drawButton(816, 657, 0);
			DxLib::DrawStringToHandle(893, 578, "���", mKeyColor, mKeyFont);
			DxLib::DrawStringToHandle(893, 615, "����", mKeyColor, mKeyFont);
			DxLib::DrawStringToHandle(893, 652, "����", mKeyColor, mKeyFont);
			DxLib::DrawGraph(mMenu[mSelected].first, mMenu[mSelected].second, mArrowGH, TRUE);
		}
	}
}
