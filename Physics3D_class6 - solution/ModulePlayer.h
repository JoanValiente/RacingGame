#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"



#define MAX_ACCELERATION 1500.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Respawn();
	void CreateCar();
	void ResetGame();

public:

	PhysVehicle3D* vehicle = nullptr;
	mat4x4 matrix;
	float turn;
	float acceleration;
	float brake;

	bool win = false, lose = false;

	bool dead = false;
	int timer = 0;
};