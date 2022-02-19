#pragma once

#include "Scene/AbstractScene.h"

namespace Scene {
	namespace Game {
		class GameManager;
		class GameClear : public AbstractScene {
		public:
			GameClear(GameManager* gm);
			~GameClear();
			void update();
			void draw() const;
		private:
			GameManager* mGameManager;
			int mGraphicHandle;
			int mKeybindGH;
		};
	}
}
