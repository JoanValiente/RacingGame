#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

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

	s.size = vec3(5, 3, 1);
	s.SetPos(0, 2.5f, 20);

	sensor = App->physics->AddBody(s, 0.0f);
	sensor->SetAsSensor(true);
	sensor->collision_listeners.add(this);

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


	// Road
	PrintFloors();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	LOG("Hit!");
}

void ModuleSceneIntro::LoadFloors()
{
	floor1.size = vec3(16, 0.5, 165);
	floor1.color = White;
	floor1.SetPos(0, 0.5, 0);
	floor1_pb = App->physics->AddBody(floor1, 0.0f);
	floor1_pb->collision_listeners.add(this);
	floor1_pb->SetAsSensor(false);

	floor2.size = vec3(17, 0.5, 50);
	floor2.color = White;
	floor2.SetPos(-16.5, 0.5, 85);
	floor2_pb = App->physics->AddBody(floor2, 0.0f);
	floor2_pb->collision_listeners.add(this);
	floor2_pb->SetAsSensor(false);

	floor3.size = vec3(20, 0.5, 12);
	floor3.color = White;
	floor3.SetPos(-35, 0.5, 104);
	floor3_pb = App->physics->AddBody(floor3, 0.0f);
	floor3_pb->collision_listeners.add(this);
	floor3_pb->SetAsSensor(false);

	floor4.size = vec3(20, 0.5, 12);
	floor4.color = White;
	floor4.SetPos(-54, 4, 104);
	floor4.SetRotation(-20, vec3(0, 0, 1));
	floor4_pb = App->physics->AddBody(floor4, 0.0f);
	floor4_pb->collision_listeners.add(this);
	floor4_pb->SetAsSensor(false);

	floor5.size = vec3(35, 0.5, 12);
	floor5.color = White;
	floor5.SetPos(-80.75, 7.4, 104);
	floor5_pb = App->physics->AddBody(floor5, 0.0f);
	floor5_pb->collision_listeners.add(this);
	floor5_pb->SetAsSensor(false);

	floor6.size = vec3(27.5, 0.5, 9);
	floor6.color = White;
	floor6.SetPos(-100, 7.4, 93.5);
	floor6_pb = App->physics->AddBody(floor6, 0.0f);
	floor6_pb->collision_listeners.add(this);
	floor6_pb->SetAsSensor(false);
	
	floor7.size = vec3(16, 0.5, 30);
	floor7.color = White;
	floor7.SetPos(-121.75, 7.4, 83);
	floor7_pb = App->physics->AddBody(floor7, 0.0f);
	floor7_pb->collision_listeners.add(this);
	floor7_pb->SetAsSensor(false);

	floor8.size = vec3(18, 0.5, 9);
	floor8.color = White;
	floor8.SetPos(-104.75, 7.4, 72.5);
	floor8_pb = App->physics->AddBody(floor8, 0.0f);
	floor8_pb->collision_listeners.add(this);
	floor8_pb->SetAsSensor(false);

	floor9.size = vec3(9, 0.5, 23);
	floor9.color = White;
	floor9.SetPos(-104.73, 7.4, 59.5);
	floor9.SetRotation(25, vec3(0, 1, 0));
	floor9_pb = App->physics->AddBody(floor9, 0.0f);
	floor9_pb->collision_listeners.add(this);
	floor9_pb->SetAsSensor(false);

	floor10.size = vec3(9, 0.5, 23);
	floor10.color = White;
	floor10.SetPos(-104.73, 7.4, 42.5);
	floor10.SetRotation(-25, vec3(0, 1, 0));
	floor10_pb = App->physics->AddBody(floor10, 0.0f);
	floor10_pb->collision_listeners.add(this);
	floor10_pb->SetAsSensor(false);
}

void ModuleSceneIntro::PrintFloors()
{
	floor1_pb->GetTransform(&floor1.transform);
	floor1.Render();

	floor2_pb->GetTransform(&floor2.transform);
	floor2.Render();

	floor3_pb->GetTransform(&floor3.transform);
	floor3.Render();

	floor4_pb->GetTransform(&floor4.transform);
	floor4.Render();

	floor5_pb->GetTransform(&floor5.transform);
	floor5.Render();

	floor6_pb->GetTransform(&floor6.transform);
	floor6.Render();

	floor7_pb->GetTransform(&floor7.transform);
	floor7.Render();

	floor8_pb->GetTransform(&floor8.transform);
	floor8.Render();

	floor9_pb->GetTransform(&floor9.transform);
	floor9.Render();

	floor10_pb->GetTransform(&floor10.transform);
	floor10.Render();
}

