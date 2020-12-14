#include "MyPhysicsEngine.h"

namespace SPACEYSHOOT
{

void MyPhysicsEngine::step(float h)
{
  vector<State> states, new_states;
  particles_to_states(states);
  new_states.resize(states.size());
  step(h, states, new_states);
  states_to_particles(new_states);
}

//step forward by h secs
void MyPhysicsEngine::step(float h, const vector<State>& states, vector<State>& new_states)
{
    vector<Vector2d> forces;
    vector<dState> dxdv;

    //1. update forces
    for(MyParticle * p : m_particles)
    {
      p->compute_force();
      forces.push_back(p->force);
    }

    //2. compute derivatives
    dxdv.resize(states.size());
    derive(states, forces, dxdv);

    //3. solve ode to get new states
    ode(h, states, dxdv, new_states);
}

//TODO: compute the derivatives
void MyPhysicsEngine::derive(const vector<MyPhysicsEngine::State>& states,
                             const vector<Vector2d>& forces,
                             vector<MyPhysicsEngine::dState>& dxdv)
{
    MyParticle* temppart;
    for (int i = 0; i < states.size(); i++)
    {
        temppart = this->m_particles.front();
        this->m_particles.pop_front();
        dxdv[i].dx = states[i].v;
        dxdv[i].dv = forces[i] / temppart->mass;
        this->m_particles.push_back(temppart);
    }
}

//TODO: implement midpoint method
void MyPhysicsEngine::ode(float h,
                          const vector<MyPhysicsEngine::State>& states,
                          const vector<MyPhysicsEngine::dState>& dxdv,
                          vector<MyPhysicsEngine::State>& new_states)
{
    vector<MyPhysicsEngine::State> mid_states (states);
    vector<MyPhysicsEngine::dState> mid_dstates (dxdv);
    vector<Vector2d> mid_forces (states.size());

//    euler(h / 2, states, dxdv, mid_states);
//    GetForce(mid_states, mid_forces);
//    derive(mid_states, mid_forces, mid_dstates);
//    euler(h, states, mid_dstates, new_states);

    euler(h, states, dxdv, new_states);
}

//TODO: implement Euler's method
void MyPhysicsEngine::euler(float h,
                            const vector<MyPhysicsEngine::State>& states,
                            const vector<MyPhysicsEngine::dState>& dxdv,
                            vector<MyPhysicsEngine::State>& new_states)
{
    for (int i = 0; i < states.size(); i++)
    {
        new_states[i].x = states[i].x + (dxdv[i].dx * h);
        new_states[i].v = states[i].v + (dxdv[i].dv * h);
    }
}

//Helper method for calculating force
void MyPhysicsEngine::GetForce(const vector<MyPhysicsEngine::State>& states, vector<Vector2d>& newforces)
{
    MyParticle* temppart;
    Point2d temppos;
    Vector2d tempvel;
    Vector2d tempforce;
    for (int i = 0; i < states.size(); i++)
    {
        temppart = this->m_particles.front();
        this->m_particles.pop_front();
        temppos = temppart->pos;
        tempvel = temppart->vel;
        tempforce = temppart->force;

        temppart->pos = states[i].x;
        temppart->vel = states[i].v;
        temppart->compute_force();
        newforces[i] = temppart->force;

        temppart->pos = temppos;
        temppart->vel = tempvel;
        temppart->force = tempforce;
        this->m_particles.push_back(temppart);
    }
}

}//end namespace GMUCS425
