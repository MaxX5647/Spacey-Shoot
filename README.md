# Spacey-Shoot
CS425 Final Project

## Original Project Proposal
Team members: Max Martin

Game name: Spacy Shoot


1.	Provide an overview of your game (give a short description about the game, i.e., core mechanics, game plot, objective, etc.): 
The player flies a spaceship on a 2-D plane, navigating different sectors (levels), and shooting enemies to collect scrap (points) with the ultimate goal of finding and defeating the boss enemy.

2.	What will be the main technical components (game AI, motion planning, physics, procedural content generation) that your game will focus on? 
The main technical component will be the physics of the ships flying through space as well as the AI of the enemies. The sectors could also be generated procedurally if I have time.

3.	What game engine/tools/libraries will your game use?
The game will primarily use elements from the game engine used in the CS425 projects.

4.	Why do you think your game is interesting/exciting? 
The game will be engaging because of the skill-based flying and shooting as well as the goal driven progression.

5.	How would you divide the tasks among your team members (if more than one)? 
Its just me.


## What I Have Implemented
  - Modified MyAgent to include additional values.
    - Added Team value to keep track of whether Agents are friendly, enemy, or neither.
    - Added added an "ox" and "oy" value to keep track of the Agents "origin" or the center of its scaled sprite. Also modified tranlateTo() and scale() to update this value.

  - Added PlayerAgent to represent the player controlled ship. This implements MyParticle so that it can be simulated in the physics engine.
    - Added functionality to PlayerAgent to ensure it always faces the mouse.
    - Added SDL events to control the PlayerAgent with "WASD" keyboard events.
    - Added SDL event to spawn BulletAgents with the left mouse button.
    - Added collision handling with the screen borders to keep the player on the screen.
    
  - Added BulletAgent to represent bullets in the game. This also implements MyParticle so that it can be simulated in the physics engine.
    - Added functionality to destroy the bullet agent when it leaves the screen.
    - Added SDL event to destroy the bullet when it collides with an Agent with a different "Team" value. (No collidable Agents other than the player and their bullets currently       exits.)
    
  - Added ObjectAgent to represent stationary decorative or collidable objects.
    - Added functionality to rotate at a set speed while active in scene.
    
  - Modified MyScene to account for the new Agent types and add new required functionality.
    - Added the player ship "w" and asteroids "a" to the level loading code.
    - Added function create_bullet() to create BulletAgents in the scene and set their initial direction, velocity, and team.
    - Added function destroy_bullet() to remove BulletAgents from the scene.
    - Added two new lists of Agents m_bullets and m_decorators to allow for bullets and decorators to be handled differently than ship agents and also drawn in the desired             order.
    
    
## Notes
- Obviously I did not get done as much as I had hoped when I made the project proposal. This is simply because of a lack of time due to projects and finals in other classes. I had begun to implement collision handling between the ship and the asteroids but I was not able to finish it in time so I removed it for this submission. I had also intended to add enemy Agents that would use behavior trees to dictate their actions but I could not get to that either.
- The Technical component used in this project is using physics engine implemented in PA05 to simulate the player ships movement in space as well as bullet movement.


## Video Demo




