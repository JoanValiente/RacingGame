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

	Cube floor1, floor2, floor3, floor4, floor5, floor6, floor7, floor8, floor9, floor10, floor11, floor12, floor13, floor14, floor15, floor16, floor17, floor18, floor19, floor20, floor21, floor22, floor23, floor24, floor25, floor26;
	PhysBody3D *floor1_pb, *floor2_pb, *floor3_pb, *floor4_pb, *floor5_pb, *floor6_pb, *floor7_pb, *floor8_pb, *floor9_pb, *floor10_pb, *floor11_pb, *floor12_pb, *floor13_pb, *floor14_pb, *floor15_pb, *floor16_pb, *floor17_pb, *floor18_pb, *floor19_pb, *floor20_pb, *floor21_pb, *floor22_pb, *floor23_pb, *floor24_pb, *floor25_pb, *floor26_pb;
};
