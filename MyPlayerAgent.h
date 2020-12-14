#pragma once

#include "MyAgent.h"
#include "mathtool/Point.h"
#include "mathtool/Vector.h"
#include "MyPhysicsEngine.h"

namespace SPACEYSHOOT
{
	class MyPlayerAgent : public MyAgent, public MyParticle
	{
	public:

		typedef mathtool::Vector2d Vector2d;

		MyPlayerAgent(float ispeed, float imass) :MyAgent(true,true)
		{
			speed = ispeed; mass = imass; collide_with = NULL; thrust = Vector2d();
		}

		virtual void update();
		virtual void display();
		virtual void handle_event(SDL_Event& e);
		virtual void draw_HUD();
		virtual void compute_force();

		virtual void tranlate(float x, float y) { this->x += x; this->y += y; this->ox += x; this->oy += y; this->pos[0] += x; this->pos[1] += y; }
		virtual void tranlateTo(float x, float y) { this->x = x; this->y = y; this->ox = this->x + scale * (this->sprite->getWidth() / 2); this->oy = this->y + scale * (this->sprite->getHeight() / 2); this->pos[0] = x; this->pos[1] = y; }

	private:
		//basic data
		int p_cooldown = 0;
		float speed;
		bool flip = false, wdown = false, adown = false, ddown = false, sdown = false, p_active = false, p_left = false, colliding = false;
		MyAgent* collide_with;
		Vector2d thrust, idamp, collision;
	};
}

