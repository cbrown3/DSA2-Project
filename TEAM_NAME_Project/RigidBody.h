//PHYSICS by Joshua McMahan
//ReEngine code from Alberto Bobadilla - included just in case

#ifndef __RIGIDBODY_H_
#define __RIGIDBODY_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll

class RigidBody
{
private:
	RigidBody() //Constructor
	{

	};
	RigidBody(RigidBody const& other) //Copy Constructor
	{

	};
	RigidBody& operator=(RigidBody const& other) //Copy operator
	{

	};
	~RigidBody() //destructor
	{

	};
public:
	//The objects state holds information on it's forces. This is the main meat of the physics.
	struct State
	{
		float x; //position of the object in 2d space
		float v; //velocity of the object in 2d space 

		glm::vec3 position; //Position of the object in 3d space - location in 3d space
		glm::vec3 momentum; //momentum of the object in 3d space - forces still acting on an object prior to full stop
		glm::quat orientation; //orientation of the object in 3d space - direction object is "facing", used to simulate tiping the object
		glm::vec3 angularMomentum; //angular momentum of the object in 3d space - used to affect the orientation from forces that would tip the object

		glm::vec3 velocity; //velocity of the object in 3d space - moves the object around in 3d space, changing position
		glm::quat spin; //spin refers to the orientation being affected by angular velocity - used to turn and tip the object
		glm::vec3 angularVelocity; //moves the object around its local axis so that is can change its orientation

		float mass; //how heavy a given object is - used in calculating momentum and inertia
		float inverseMass; //inverse of the mass
		float inertia; //
		float inverseInertia; //inverse of the inertia

		void recalculate()
		{
			velocity = momentum*inverseMass; //calculate velocity

			angularVelocity = angularMomentum*inverseInertia; //calculate angular velocity

			//I need to normalize the orientation. this is the equation, but i need to just do something like orientation.normalize but that is not here. Working on a work around.
			//orientation = (orientation.x + orientation.y + orientation.z + orientation.w)/(sqrt((orientation.x*orientation.x) + (orientation.y*orientation.y) + (orientation.z*orientation.z) + (orientation.w*orientation.w)));

			glm::quat q(0, angularVelocity.x, angularVelocity.y, angularVelocity.z); //temp quat too store angular velocity as to affect spin

			spin = 0.5f * q * orientation; //calculate spin
		};
	};

	//Stores values that are derived from base ones
	struct Derivative
	{
		float dx; //dx/dt = vel in 2d
		float dv; //dv/dt = spd in 2d

		glm::vec3 velocity; //vel in 3d
		glm::vec3 force; //3d forces

		glm::quat spin; //orientation changing force
		glm::vec3 torque; //acceleration force for spining
	};

	//object acceleration
	float acceleration(const State &state, float t)
	{
		const float k = 10;
		const float b = 1;
		return -k * state.x - b*state.v;
	};

	//calculates the derivative of a given object's state
	Derivative Evaluate(const State &initial, float t, float dt, const Derivative &d)
	{
		//calculating a temp state from the object's passed in state
		State state;
		state.x = initial.x + d.dx*dt;
		state.v = initial.v + d.dv*dt;

		Derivative output; //Temp to store the output

		output.dx = state.v; //get dx
		output.dv = acceleration(state, t + dt); //get dv

		return output;
	};

	//Integrates the values of an object state
	void Integrate(State &state, float t, float dt)
	{
		Derivative a, b, c, d; //temp values

		//Evaluate all of the derivatives
		a = Evaluate(state, t, 0.0f, Derivative());
		b = Evaluate(state, t, dt*0.5f, a);
		c = Evaluate(state, t, dt*0.5f, b);
		d = Evaluate(state, t, dt, c);

		//calk the Dx and Dt
		float dXdT = 1.0f / 6.0f * (a.dx + 2.0f*(b.dx + c.dx) + d.dx);
		float dVdT = 1.0f / 6.0f * (a.dv + 2.0f*(b.dv + c.dv) + d.dv);

		//Return the values to the state
		state.x = state.x + dXdT * dt;
		state.v = state.v + dVdT * dt;
	};

	//Returns the calculated torque of an objects state
	glm::vec3 Torque(const State &state, float t)
	{
		return glm::vec3(1, 0, 0) - state.angularVelocity * 0.1f;
	};
};

#endif //__RIGIDBODY_H_