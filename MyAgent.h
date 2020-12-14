#pragma once

#include "MySprite.h"
#include "mathtool/Point.h"
#include "mathtool/Box.h"

namespace SPACEYSHOOT
{
    //this defines the transform of the agent
    class MyAgent
    {
      public:

        //movable: true if this agent can move
        //collision: true if this agent can collision with other agents
        MyAgent(bool movable=true, bool collision=true, int team = 0)
        {
          x=y=degree=ox=oy=0;
          scale=1;
          visible=true;
          sprite=NULL;
          this->movable=movable;
          this->collision=collision;
          this->team = team;
        }

        //react to the events
        virtual void handle_event(SDL_Event & e);

        //update this agent's motion, looks, sound, etc
        virtual void update();

        //render this agent
        virtual void display();

        //show HUD (heads-up display) or status bar
        virtual void draw_HUD();

        //transforms
        void rotate(float degree){ this->degree+=degree; }
        void rotateTo(float degree){ this->degree=degree; }

        virtual void tranlate(float x, float y) { this->x += x; this->y += y; this->ox += x; this->oy += y; }
        virtual void tranlateTo(float x, float y) { this->x = x; this->y = y; this->ox = this->x + scale * (this->sprite->getWidth() / 2); this->oy = this->y + scale * (this->sprite->getHeight() / 2);}

        void scaleTo(float s) { this->scale = s; this->ox = this->x + s * (this->sprite->getWidth() / 2); this->oy = this->y + s * (this->sprite->getHeight() / 2);}

        //display
        void show(){ visible=true; }
        void hide(){ visible=false; }

        //sprite, aks costume
        void setSprite(MySprite * sprite){ this->sprite=sprite; }
        MySprite * getSprite() { return this->sprite; }

        //motion/animation
        //void glide(float x, float y, float seconds);

        bool collide(MyAgent * other);

        SDL_Rect get_bounding_box();

        //ACCESS METHODS
        bool is_movable() const { return movable; }
        bool is_visible() const { return visible; }
        bool is_collidable() const { return collision; }

        float getX() const { return x; }
        float getY() const { return y; }
        float getAngle() const { return degree; }
        float getScale() const { return scale; }
        int getTeam() const { return team; }

      protected:

        void draw_bounding_box();
        void draw_circle(int32_t center_x, int32_t center_y, int32_t radius);

        //current position and orientations
        float x,y,ox,oy;
        float degree; //rotation
        float scale;
        int team;

    		bool visible;
    		bool movable;
    		bool collision;

        MySprite * sprite; //current sprite
        //it is possible that you can have more than one sprites
        //vector<MySprite *> sprites; //the sprites
    };

}//end namespace
