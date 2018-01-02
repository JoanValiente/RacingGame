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

	void CreateFloor(vec3 size, Color color, vec3 pos, float angle, vec3 rotation_axis);
	void LoadFloors();
	void PrintFloors();

public:
	Cube s, death;
	PhysBody3D *sensor, *death_pb;

	//Floor
	p2List<Cube> floors;
	p2List<PhysBody3D*> floors_pb;
	p2List<Cube> walls;
	p2List<PhysBody3D*> walls_pb;

};
