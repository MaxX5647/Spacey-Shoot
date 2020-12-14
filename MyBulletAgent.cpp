#include "MyBulletAgent.h"
#include "MyGame.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>

namespace SPACEYSHOOT
{

	void SPACEYSHOOT::MyBulletAgent::update()
	{
		tranlateTo(this->pos[0], this->pos[1]);
		MyGame* game = getMyGame();
		MyScene* scene = game->getSceneManager()->get_active_scene();
		if (this->pos[0] < -10 || this->pos[0] > game->getScreenWidth() + 10.0 || this->pos[1] < -10 || this->pos[1] > game->getScreenHeight() + 10.0)
		{
			//printf("x: %f y: %f\n", this->pos[0], this->pos[1]);
			scene->destroy_bullet(this);
		}
	}

	void SPACEYSHOOT::MyBulletAgent::handle_event(SDL_Event& e)
	{
		if (e.type == SDL_USEREVENT)
		{
			if (e.user.code == 1 && e.user.data1 == this)
			{
				MyScene* scene = getMyGame()->getSceneManager()->get_active_scene();
				//Hit an enemy/neutral object
				if (((MyAgent*)e.user.data2)->getTeam() != this->team)
				{
					scene->destroy_bullet(this);
				}
			}
		}
	}

	void SPACEYSHOOT::MyBulletAgent::compute_force()
	{

	}

}
