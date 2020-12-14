#pragma once

#include "MyAgent.h"
#include "mathtool/Vector.h"
#include "MyPhysicsEngine.h"

/**
struct MyParticle
{
	//this function updates this->force
	virtual void compute_force() = 0;

	float mass;     //mass of this particle
	mathtool::Vector2d force; //force applied to this particle
	mathtool::Point2d pos;      //position;
	mathtool::Vector2d vel;     //velocity
};
*/

namespace SPACEYSHOOT
{
	class MyBulletAgent : public MyAgent, public MyParticle
	{
	public:

		typedef mathtool::Vector2d Vector2d;

		MyBulletAgent(float ispeed, float imass, float vx, float vy, int team) :MyAgent(true, true, team)
		{
			speed = ispeed; mass = imass; collide_with = NULL; this->friendly = friendly;
			vel[0] = vx; vel[1] = vy; vel = vel.normalize() * speed;
		}

		virtual void update();
		virtual void handle_event(SDL_Event& e);
//		virtual void draw_HUD();
		virtual void compute_force();

		virtual void tranlate(float x, float y) { this->x += x; this->y += y; this->ox += x; this->oy += y; this->pos[0] += x; this->pos[1] += y; }
		virtual void tranlateTo(float x, float y) { this->ox = x; this->oy = y; this->x = this->ox - scale * (this->sprite->getWidth() / 2); this->y = this->oy - scale * (this->sprite->getHeight() / 2); this->pos[0] = ox; this->pos[1] = oy; }

		std::string get_bullet_filename() { return filename; }

	private:
		//basic data
		std::string filename = "imgs/bullet.png";
		float speed;
		bool friendly;
		MyAgent* collide_with;
	};
}