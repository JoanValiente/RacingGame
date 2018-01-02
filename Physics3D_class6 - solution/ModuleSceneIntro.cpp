#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePlayer.h"
#include "PhysVehicle3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	s.size = vec3(16, 3, 0.5);
	s.SetPos(0, 2.5f, 20);

	sensor = App->physics->AddBody(s, 0.0f);
	sensor->SetAsSensor(true);
	sensor->collision_listeners.add(this);


	death.size = vec3(300, 0.25, 300);
	death.SetPos(-50, 0.1, 0);
	death.color = Black;

	death_pb = App->physics->AddBody(death, 0.0f);
	death_pb->SetAsSensor(true);
	death_pb->collision_listeners.add(this);

	// Road
	LoadFloors();
	

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	sensor->GetTransform(&s.transform);
	s.Render();

	death_pb->GetTransform(&death.transform);
	death.Render();


	// Road
	PrintFloors();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	LOG("Hit!");
	if (body1 == death_pb)
	{
		App->player->dead = true;
		App->player->vehicle->SetPos(0, 1, 10);
	}
}



void ModuleSceneIntro::LoadFloors()
{	
	CreateFloor(vec3(16, 0.5, 160), White, vec3(0, 0.5, 0.75), 0, vec3(0, 0, 0));
	CreateFloor(vec3(17, 0.5, 50), White, vec3(-16.5, 0.5, 85), 0, vec3(0, 0, 0));
	CreateFloor(vec3(20, 0.5, 12), White, vec3(-35, 0.5, 104), 0, vec3(0, 0, 0));
	CreateFloor(vec3(20, 0.5, 12), White, vec3(-54, 4, 104), -20, vec3(0, 0, 1));
	CreateFloor(vec3(35, 0.5, 12), White, vec3(-80.75, 7.4, 104), 0, vec3(0, 0, 0));
	CreateFloor(vec3(27.5, 0.5, 9), White, vec3(-100, 7.4, 93.5), 0, vec3(0, 0, 0));
	CreateFloor(vec3(16, 0.5, 30), White, vec3(-121.75, 7.4, 83), 0, vec3(0, 0, 0));
	CreateFloor(vec3(18, 0.5, 9), White, vec3(-104.75, 7.4, 72.5), 0, vec3(0, 0, 0));
	CreateFloor(vec3(9, 0.5, 23), White, vec3(-104.73, 7.4, 59.5), 25, vec3(0, 1, 0));
	CreateFloor(vec3(9, 0.5, 23), White, vec3(-104.73, 7.4, 42.5), -25, vec3(0, 1, 0));
	CreateFloor(vec3(9, 0.5, 23), White, vec3(-104.73, 7.4, 25.5), 25, vec3(0, 1, 0));
	CreateFloor(vec3(9, 0.5, 23), White, vec3(-104.73, 7.4, 8.5), -25, vec3(0, 1, 0));
	CreateFloor(vec3(9, 0.5, 23), White, vec3(-120.8, 7.4, 59.5), -25, vec3(0, 1, 0));
	CreateFloor(vec3(9, 0.5, 23), White, vec3(-120.8, 7.4, 42.5), 25, vec3(0, 1, 0));
	CreateFloor(vec3(9, 0.5, 23), White, vec3(-120.8, 7.4, 25.5), -25, vec3(0, 1, 0));
	CreateFloor(vec3(9, 0.5, 23), White, vec3(-120.8, 7.4, 8.5), 25, vec3(0, 1, 0));
	CreateFloor(vec3(34, 0.5, 9), White, vec3(-112.75, 7.4, -4.5), 0, vec3(0, 0, 0));	
	CreateFloor(vec3(16, 0.5, 31.5), White, vec3(-103.75, 7.4, -24.75), 0, vec3(0, 0, 0));
	CreateFloor(vec3(40.5, 0.5, 11), White, vec3(-129.925, 7.4, -29.95), 15, vec3(0, 1, 0));
	CreateFloor(vec3(11, 0.5, 30), White, vec3(-145.4, 7.4, -45), 0, vec3(0, 0, 0));
	CreateFloor(vec3(45, 0.5, 11), White, vec3(-127.8, 7.4, -60.22), 15, vec3(0, 1, 0));
	CreateFloor(vec3(47.5, 0.5, 30), White, vec3(-92.85, 7.4, -75.75), 0, vec3(0, 0, 0));
	CreateFloor(vec3(10, 0.5, 9), White, vec3(-64.249, 8.745, -75.75), 15, vec3(0, 0, 1));
	CreateFloor(vec3(10, 0.5, 9), White, vec3(-40, 0.5, -75.75), 0, vec3(0, 0, 0));
	CreateFloor(vec3(15, 0.5, 20), White, vec3(-27.5, 0.5, -75.75), 0, vec3(0, 0, 0));
	CreateFloor(vec3(12, 0.5, 7), White, vec3(-14, 0.5, -75.75), 0, vec3(0, 0, 0));

}

void ModuleSceneIntro::PrintFloors()
{ 
	p2List_item <PhysBody3D*>* tmp_pb = floors_pb.getFirst();
	p2List_item <Cube>* tmp = floors.getFirst();
	while (tmp != nullptr) {
		tmp_pb->data->GetTransform(&tmp->data.transform);
		tmp->data.Render();
		tmp = tmp->next;
		tmp_pb = tmp_pb->next;
	}
}
void ModuleSceneIntro::CreateFloor(vec3 size, Color color, vec3 pos, float angle, vec3 rotation_axis) {
	Cube floor;
	PhysBody3D *floor_pb;
	floor.size = size;
	floor.color = White;
	floor.SetPos(pos.x, pos.y, pos.z);
	if (angle != 0) {
		floor.SetRotation(angle, rotation_axis);
	}
	floor_pb = App->physics->AddBody(floor, 0.0f);
	floor_pb->collision_listeners.add(this);
	floor_pb->SetAsSensor(false);

	floors.add(floor);
	floors_pb.add(floor_pb);
}
