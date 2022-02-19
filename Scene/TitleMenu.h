#pragma once

#include <utility>
#include <vector>

#include "Scene/AbstractScene.h"

namespace Scene {
	class TitleMenu : public AbstractScene {
	public:
		TitleMenu();
		~TitleMenu();
		void update();
		void draw() const;
	private:
		int mGraphicHandle;
		int mArrowGH;
		int mSelected;
		bool mPrevPushed;
		int mCount;
		std::vector<std::pair<int, int>> mMenu;
	};
}
