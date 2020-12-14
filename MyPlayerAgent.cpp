#include "MyPlayerAgent.h"
#include "MyGame.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>

namespace SPACEYSHOOT
{



	void MyPlayerAgent::update()
	{
		tranlateTo(this->pos[0], this->pos[1]);

		//Always point towards the mouse
		int x, y, dx, dy;
		SDL_GetMouseState(&x, &y);
		dx = x - this->ox;
		dy = y - this->oy;
		this->degree = atan2((double)dy, (double)dx) * (180.0 / M_PI);

		//Fire weapons
		if (this->p_cooldown > 0)
		{
			this->p_cooldown -= 1;
		}
		else
		{
			if (this->p_active)
			{
				MyScene* scene = getMyGame()->getSceneManager()->get_active_scene();
				scene->create_bullet(400, 1, ox, oy, dx, dy, 0);
				this->p_cooldown = 8;
			}
		}

		MyGame* game = getMyGame();

		//Stay within the game screen
		if (this->ox < 0) { this->vel[0] *= -1; }
		if (this->ox > game->getScreenWidth()) { this->vel[0] *= -1; }
		if (this->oy < 0) { this->vel[1] *= -1; }
		if (this->oy > game->getScreenHeight()) { this->vel[1] *= -1; }

	}

	void MyPlayerAgent::display()
	{
		if (!this->visible) return; //not visible...
		//setup positions and ask sprite to draw something
		//printf("x: %f y: %f\n", this->force[0], this->force[1]);
		this->sprite->display(x, y, scale, degree, NULL, SDL_FLIP_NONE);

		//SDL_SetRenderDrawColor(getMyGame()->getRenderer(), 255, 100, 0, 100);
		//draw_bounding_box();
	}

	void MyPlayerAgent::handle_event(SDL_Event& e)
	{
		
		if (e.type == SDL_MOUSEMOTION)
		{
			
		}
		//Add thrust
		else if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.scancode == SDL_SCANCODE_W && wdown == false)
			{
				this->thrust[1] += -1;
				wdown = true;
			}
			else if (e.key.keysym.scancode == SDL_SCANCODE_A && adown == false)
			{
				this->thrust[0] += -1;
				adown = true;
			}
			else if (e.key.keysym.scancode == SDL_SCANCODE_D && ddown == false)
			{
				this->thrust[0] += 1;
				ddown = true;
			}
			else if (e.key.keysym.scancode == SDL_SCANCODE_S && sdown == false)
			{
				this->thrust[1] += 1;
				sdown = true;
			}
		}
		//Reduce thrust
		else if (e.type == SDL_KEYUP)
		{
			if (e.key.keysym.scancode == SDL_SCANCODE_W)
			{
				this->thrust[1] -= -1;
				wdown = false;
			}
			else if (e.key.keysym.scancode == SDL_SCANCODE_A)
			{
				this->thrust[0] -= -1;
				adown = false;
			}
			else if (e.key.keysym.scancode == SDL_SCANCODE_D)
			{
				this->thrust[0] -= 1;
				ddown = false;
			}
			else if (e.key.keysym.scancode == SDL_SCANCODE_S)
			{
				this->thrust[1] -= 1;
				sdown = false;
			}
		}
		//Firing mouse
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				this->p_active = true;
			}
		}
		//Stop Firing mouse
		else if (e.type == SDL_MOUSEBUTTONUP)
		{
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				this->p_active = false;
			}
		}
		//Handle Collision
		else if (e.type == SDL_USEREVENT)
		{
			if (e.user.code == 1 && e.user.data1 == this)
			{
				if (((MyAgent*)e.user.data2)->getTeam() == 2)
				{
					this->vel *= -1;
				}
			}
		}
	}

	void MyPlayerAgent::draw_HUD()
	{

	}

	void MyPlayerAgent::compute_force()
	{
		MyGame* game = getMyGame();
		if (this->thrust[0] == 0 && this->thrust[1] == 0) { this->force = this->thrust; }
		else { this->force = this->thrust.normalize() * this->speed; }

		if (this->vel[0] != 0 || this->vel[1] != 0) { this->idamp = this->vel.normalize(); }

		this->idamp = this->idamp * (sqr(this->vel.norm()) / (10.0 * speed));

		this->force = this->force - this->idamp;

		
	}

}