#pragma once

namespace Scene {
	namespace Game {
		class Player {
		public:
			Player(int gh);
			~Player() {}
			void update(unsigned int input);
			void draw() const;
			const int& getX() const { return mX; }
			const int& getY() const { return mY; }
			const double& getRadius() const { return mRadius; }
			void reset();
		private:
			int mX, mY;
			double mSpeed;
			const double mRadius;
			int mGraphicHandle;
		};
	}
}
