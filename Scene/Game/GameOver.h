#pragma once

#include "Scene/AbstractScene.h"

namespace Scene {
	namespace Game {
		class GameManager;
		class GameOver : public AbstractScene {
		public:
			GameOver(GameManager* gm);
			~GameOver();
			void update();
			void draw() const;
		private:
			GameManager* mGameManager;
			int mGraphicHandle;
		};
	}
}
