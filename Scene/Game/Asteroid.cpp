#define _USE_MATH_DEFINES
#include <cmath>
#include <cassert>
#include <fstream>
#include <random>
#include <string>
#include <tuple>
#include <utility>

#include "DxLib.h"

#include "Window.h"
#include "Scene/Game/Asteroid.h"
#include "Scene/Game/GameAssets.h"
#include "Scene/Game/Player.h"

namespace Scene {
    namespace Game {
		Asteroid::Asteroid(int AsteroidGH, double la, double sa, int x, int y) : mGraphicHandle(AsteroidGH), mRot(0), mLongAxis(la), mShortAxis(sa) {
			mX = x;
			mY = y;
			mSpeed = 10.0;
			mRotSpeed = M_PI / 30;
			mAngle = M_PI / 4;
		}

		Asteroid::Asteroid(int AsteroidGH, int x, int y, double angle, double rot_speed) : 
		mX(x), mY(y), mGraphicHandle(AsteroidGH), mRot(0), mAngle(angle), mRotSpeed(rot_speed) {
			mLongAxis = 50.0;
			mShortAxis = 30.0;
			mSpeed = 5.0;
		}

		void Asteroid::addAngle(double dtheta) {
			mRot += dtheta;
			if (mRot > 2 * M_PI) {
				mRot = std::fmod(mRot, 2 * M_PI);
			}
			if (mRot < 0) {
				mRot = 2 * M_PI + std::fmod(mRot, 2 * M_PI);
			}
		}

		double Asteroid::getRadius(int x, int y) const {
			double angle = std::atan2(y, x);
			double theta = angle + mRot;
			double rx, ry;
			if (angle >= 0 && angle < M_PI) {
				theta -= 2 * M_PI;
			}
			rx = mLongAxis * std::cos(theta);
			ry = mShortAxis * std::sin(theta);
			return std::sqrt(rx * rx + ry * ry);
		}

		int Asteroid::update() {
			addAngle(mRotSpeed);
			int dx = static_cast<int>(mSpeed * std::cos(mAngle));
			int dy = static_cast<int>(mSpeed * std::sin(mAngle));
			mX += dx;
			mY += dy;
			if (mX < 0) {
				if ((mAngle >= -M_PI && mAngle < -M_PI / 2) || (mAngle > M_PI / 2 && mAngle <= M_PI)) {
				   return 1;
				}
			}
			if (mX >= WINDOW.width) {
				if (mAngle > -M_PI/2 && mAngle < M_PI/2) {
					return 1;
				}
			}
			if (mY < 0) {
				if (mAngle > -M_PI && mAngle < 0) {
					return 1;
				}
			}
			if (mY >= WINDOW.height) {
				if (mAngle > 0 && mAngle < M_PI) {
					return 1;
				}
			}
			return 0;
		}

		void Asteroid::draw() const {
			DxLib::DrawRotaGraph(mX, mY, 1.0, mRot, mGraphicHandle, TRUE);
		}

		int Asteroid::checkHit(Player* p) {
			const int px = p->getX();
			const int py = p->getY();
			const double pr = p->getRadius();
			double rad = this->getRadius(px, py);
			double dist = std::sqrt((px-mX)*(px-mX) + (py-mY)*(py-mY));
			if (rad + pr > dist) {
				return 1;
			}
			return 0;
		}

		AsteroidManager::AsteroidManager(int gh, int interval)
			: mGraphicHandle(gh),
			  mInterval(interval),
			  mRand(0),
			  mFrameCount(0) {
			std::ifstream ifs("data/AsteroidManager.conf");
			std::string line;
			while (!ifs.eof()) {
				line.clear();
				std::getline(ifs, line);
				if (line == "" || line[0] == '#') continue;
				int mode = 0;
				std::string str_num = "";
				int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
				for (const char c : line) {
					if (mode == 0) {
						if ((c >= '0' && c <= '9') || c == '-') {
							str_num += c;
						}
						else if (c == ',') {
							++mode;
							x1 = std::stoi(str_num);
							str_num.clear();
						}
						continue;
					}
					else if (mode == 1) {
						if ((c >= '0' && c <= '9') || c == '-') {
							str_num += c;
						}
						else if (c == ')') {
							++mode;
							y1 = std::stoi(str_num);
							str_num.clear();
						}
						continue;
					}
					else if (mode == 2) {
						if ((c >= '0' && c <= '9') || c == '-') {
							str_num += c;
						}
						else if (c == ',') {
							++mode;
							x2 = std::stoi(str_num);
							str_num.clear();
						}
						continue;
					}
					else if (mode == 3) {
						if ((c >= '0' && c <= '9') || c == '-') {
							str_num += c;
						}
						else if (c == ')' || c == '\n') {
							++mode;
							y2 = std::stoi(str_num);
							str_num.clear();
						}
						continue;
					}
				}
				assert(mode == 4);
				if (mode == 4) {
					mPaths.emplace_back(x1, y1, std::atan2(y2 - y1, x2 - x1));
					mPaths.emplace_back(x2, y2, std::atan2(y1 - y2, x1 - x2));
				}
			}
		}

		AsteroidManager::~AsteroidManager() {
			for (Asteroid* a : mAsteroids) {
				delete a;
			}
		}

		void AsteroidManager::update() {
			if (mFrameCount % mInterval == 0) {
				createAsteroid();
			}
			for (auto iter = mAsteroids.begin(); iter != mAsteroids.end();) {
				if ((*iter)->update() == 1) {
					delete (*iter);
					iter = mAsteroids.erase(iter);
				}
				else {
					++iter;
				}
			}
			++mFrameCount;
		}

		void AsteroidManager::draw() const {
			for (const Asteroid* a : mAsteroids) a->draw();
		}

		int AsteroidManager::checkHit(Player* p) {
			bool flag = false;
			for (auto iter = mAsteroids.begin(); iter != mAsteroids.end();) {
				if ((*iter)->checkHit(p) == 1) {
					flag = true;
					delete (*iter);
					iter = mAsteroids.erase(iter);
				}
				else {
					++iter;
				}
			}
			if (flag) return 1;
			return 0;
		}


		void AsteroidManager::createAsteroid() {
			uint32_t rand = mRand();
			rand %= mPaths.size();
			int x, y;
			double angle;
			std::tie(x, y, angle) = mPaths.at(rand);
			rand = mRand();
			double rot_speed = (static_cast<double>(rand) / UINT32_MAX) * M_PI / 30.0;
			mAsteroids.push_back(new Asteroid(mGraphicHandle, x, y, angle, rot_speed));
		}

		void AsteroidManager::reset() {
			mRand.seed(0);
			for (Asteroid* a : mAsteroids) {
				delete a;
				a = nullptr;
			}
			mAsteroids.clear();
		}
    }
}


