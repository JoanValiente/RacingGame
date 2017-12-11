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

	void LoadFloors();
	void PrintFloors();

public:
	Cube s;
	PhysBody3D* sensor;

	//Floor
	Cube floor1, floor2, floor3, floor4, floor5, floor6, floor7, floor8, floor9, floor10;
	PhysBody3D *floor1_pb, *floor2_pb, *floor3_pb, *floor4_pb, *floor5_pb, *floor6_pb, *floor7_pb, *floor8_pb, *floor9_pb, *floor10_pb;
};
