#pragma once

namespace Scene {
	class AbstractScene {
	public:
		virtual ~AbstractScene() {}
		virtual void update() = 0;
		virtual void draw() const = 0;
	};
}
