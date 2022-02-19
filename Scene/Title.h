#pragma once

#include "Scene/AbstractScene.h"

namespace Scene {
	class Title : public AbstractScene {
	public:
		Title();
		~Title();
		void update();
		void draw() const;
	private:
		int mGraphicHandle;
		int mCount;
	};
}
