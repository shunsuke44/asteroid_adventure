#pragma once

#include <vector>
#include <random>

namespace Scene {
    namespace Game {
		class GamePlay;
		class Player;
		class Asteroid {
		public:
			Asteroid(int AsteroidGH, double la, double sa, int x, int y);
			Asteroid(int AsteroidGH, int x, int y, double angle, double rot_speed);
			~Asteroid() {}
			const double& getAngle() const { return mRot; }
			double getRadius(int x, int y) const;
			int update();
			void draw() const;
			int checkHit(Player* p);
		private:
			int mX, mY;
			int mGraphicHandle;
			void addAngle(double dtheta);
			double mRot;
			double mRotSpeed;
			double mLongAxis, mShortAxis;
			double mSpeed;
			double mAngle;
		};

		class AsteroidManager {
		public:
			AsteroidManager(int gh, int interval);
			~AsteroidManager();
			void update();
			void draw() const;
			int checkHit(Player* p);
			void reset();
		private:
			void createAsteroid();
			const int mGraphicHandle;
			const int mInterval;
			std::vector<Asteroid*> mAsteroids;
			std::vector<std::tuple<int, int, double>> mPaths;
			std::mt19937 mRand;
			int mFrameCount;
		};
    }
}
