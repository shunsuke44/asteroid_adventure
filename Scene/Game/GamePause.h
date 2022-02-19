#pragma once

#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "Scene/AbstractScene.h"

namespace Scene {
	namespace Game {
		class GameManager;
		class GameAssets;
		class GamePause : public AbstractScene {
		public:
			GamePause(GameManager* gm);
			~GamePause();
			void update();
			void draw() const;
		private:
			GameManager* mGameManager;
			GameAssets* mGameAssets;
			int mGraphicHandle;
			int mMenuFont;
			int mMenuColor;
			int mKeyFont;
			int mKeyColor;
			int mArrowGH;
			int mCount;
			int mSelected;
			bool mPrevPushed;
			std::vector<std::pair<int, int>> mMenu;
			std::vector<std::tuple<int, int, std::string>> mMenuStr;
		};
	}
}
