#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	void CreateCircuit(vec3 size, Color color, vec3 pos, float angle, vec3 rotation_axis);
	void LoadCircuit();
	void PrintCircuit();

public:
	Cube s[4], death;
	PhysBody3D *sensor[4], *death_pb = nullptr;

	bool checkpoint1 = false, checkpoint2 = false, checkpoint3 = false;
	int laps = 0;


	//Floor
	p2List<Cube> circuit;
	p2List<PhysBody3D*> circuit_pb;
	

};
