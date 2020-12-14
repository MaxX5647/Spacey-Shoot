#pragma once

#include <iostream>
#include "MyManager.h"
#include "MyAgent.h"

namespace SPACEYSHOOT
{
    class MyPhysicsEngine;

    //this defines one level of the game
    class MyScene
    {
        public:

          MyScene(){
            m_active=true;
            m_backdrop=NULL;
            m_width=m_height=0;
            physics=NULL;
          }

          //load the level from an input into the scene
          virtual bool create( std::istream & input);

          //hand the event
          virtual void handle_event(SDL_Event & e);

          //update the scene
          virtual void update();

          //display the scene
          virtual void display();

          //show HUD (heads-up display) or status bar
          virtual void draw_HUD();

          //used to spawn bullet agents
          virtual void create_bullet(float ispeed, float imass, float ix, float iy, float vx, float vy, int team);

          //used to destroy bullet agents
          virtual void destroy_bullet(MyAgent* bullet);

          //ACCESS methods
          bool is_active() const { return m_active; }
          void deactive(){ m_active=false; }
          void activate(){ m_active=true; }
          int get_width() const { return m_width; } //level width
          int get_height()const { return m_height; } //level height
          //get all agents created in this level
          const std::list<MyAgent * > & get_agents() const { return m_agents; }
          const std::list<MyAgent*>& get_bullets() const { return m_bullets; }

        protected:

          //detect collisions in board range
          //return the number of pairs of collisions
          virtual int broad_range_collision();

          std::list<MyAgent * > m_agents;
          std::list<MyAgent*> m_bullets;
          std::list<MyAgent*> m_deadbullets;
          std::list<MyAgent*> m_decorators;
          MyAgent * m_backdrop;
          bool m_active;
          int m_width, m_height; //level width and height

          //NEW
          MyPhysicsEngine * physics;
    };


    class MySceneManager : public MyManager<MyScene>
    {
    public:

    	//create a texture from file
    	bool create(std::string name, std::string scene_file);

      //get the first active scene
      MyScene * get_active_scene();

    };//end of class MyTextureManager
}
