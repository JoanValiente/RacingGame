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
}

/*
struct FloorDef {
	vec3  size;
	color color;
	vec3  pos;
	float rot_angle;
	vec3  rot_axis;
};
*/

void ModuleSceneIntro::LoadFloors()
{
	/*
	FloorDef floor_defs = {
		{ vec3(9, 0.5, 23), White, vec3(-120.8, 7.4, 8.5), 25, vec3(0, 1, 0) },
		{ vec3(9, 0.5, 23), White, vec3(-120.8, 7.4, 8.5), 25, vec3(0, 1, 0) },
	};
	*/

	floor1.size = vec3(16, 0.5, 160);
	floor1.color = White;
	floor1.SetPos(0, 0.5, 0.75);
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

	floor11.size = vec3(9, 0.5, 23);
	floor11.color = White;
	floor11.SetPos(-104.73, 7.4, 25.5);
	floor11.SetRotation(25, vec3(0, 1, 0));
	floor11_pb = App->physics->AddBody(floor11, 0.0f);
	floor11_pb->collision_listeners.add(this);
	floor11_pb->SetAsSensor(false);

	floor12.size = vec3(9, 0.5, 23);
	floor12.color = White;
	floor12.SetPos(-104.73, 7.4, 8.5);
	floor12.SetRotation(-25, vec3(0, 1, 0));
	floor12_pb = App->physics->AddBody(floor12, 0.0f);
	floor12_pb->collision_listeners.add(this);
	floor12_pb->SetAsSensor(false);

	floor13.size = vec3(9, 0.5, 23);
	floor13.color = White;
	floor13.SetPos(-120.8, 7.4, 59.5);
	floor13.SetRotation(-25, vec3(0, 1, 0));
	floor13_pb = App->physics->AddBody(floor13, 0.0f);
	floor13_pb->collision_listeners.add(this);
	floor13_pb->SetAsSensor(false);

	floor14.size = vec3(9, 0.5, 23);
	floor14.color = White;
	floor14.SetPos(-120.8, 7.4, 42.5);
	floor14.SetRotation(25, vec3(0, 1, 0));
	floor14_pb = App->physics->AddBody(floor14, 0.0f);
	floor14_pb->collision_listeners.add(this);
	floor14_pb->SetAsSensor(false);

	floor15.size = vec3(9, 0.5, 23);
	floor15.color = White;
	floor15.SetPos(-120.8, 7.4, 25.5);
	floor15.SetRotation(-25, vec3(0, 1, 0));
	floor15_pb = App->physics->AddBody(floor15, 0.0f);
	floor15_pb->collision_listeners.add(this);
	floor15_pb->SetAsSensor(false);

	floor16.size = vec3(9, 0.5, 23);
	floor16.color = White;
	floor16.SetPos(-120.8, 7.4, 8.5);
	floor16.SetRotation(25, vec3(0, 1, 0));
	floor16_pb = App->physics->AddBody(floor16, 0.0f);
	floor16_pb->collision_listeners.add(this);
	floor16_pb->SetAsSensor(false);

	//CreateFloor(vec3(9, 0.5, 23), White, vec3(-120.8, 7.4, 8.5), 25, vec3(0, 1, 0));

	floor17.size = vec3(34, 0.5, 9);
	floor17.color = White;
	floor17.SetPos(-112.75, 7.4, -4.5);
	floor17_pb = App->physics->AddBody(floor17, 0.0f);
	floor17_pb->collision_listeners.add(this);
	floor17_pb->SetAsSensor(false);

	floor18.size = vec3(16, 0.5, 31.5);
	floor18.color = White;
	floor18.SetPos(-103.75, 7.4, -24.75);
	floor18_pb = App->physics->AddBody(floor18, 0.0f);
	floor18_pb->collision_listeners.add(this);
	floor18_pb->SetAsSensor(false);

	floor19.size = vec3(40.5, 0.5, 11);
	floor19.color = White;
	floor19.SetPos(-129.925, 7.4, -29.95);
	floor19.SetRotation(15, vec3(0, 1, 0));
	floor19_pb = App->physics->AddBody(floor19, 0.0f);
	floor19_pb->collision_listeners.add(this);
	floor19_pb->SetAsSensor(false);

	floor20.size = vec3(11, 0.5, 30);
	floor20.color = White;
	floor20.SetPos(-145.4, 7.4, -45);
	floor20_pb = App->physics->AddBody(floor20, 0.0f);
	floor20_pb->collision_listeners.add(this);
	floor20_pb->SetAsSensor(false);

	floor21.size = vec3(45, 0.5, 11);
	floor21.color = White;
	floor21.SetPos(-127.8, 7.4, -60.22);
	floor21.SetRotation(15, vec3(0, 1, 0));
	floor21_pb = App->physics->AddBody(floor21, 0.0f);
	floor21_pb->collision_listeners.add(this);
	floor21_pb->SetAsSensor(false);

	floor22.size = vec3(47.5, 0.5, 30);
	floor22.color = White;
	floor22.SetPos(-92.85, 7.4, -75.75);
	floor22_pb = App->physics->AddBody(floor22, 0.0f);
	floor22_pb->collision_listeners.add(this);
	floor22_pb->SetAsSensor(false);

	floor23.size = vec3(10, 0.5, 9);
	floor23.color = White;
	floor23.SetPos(-64.249, 8.745, -75.75);
	floor23.SetRotation(15, vec3(0, 0, 1));
	floor23_pb = App->physics->AddBody(floor23, 0.0f);
	floor23_pb->collision_listeners.add(this);
	floor23_pb->SetAsSensor(false);

	floor24.size = vec3(10, 0.5, 9);
	floor24.color = White;
	floor24.SetPos(-40, 0.5, -75.75);
	floor24_pb = App->physics->AddBody(floor24, 0.0f);
	floor24_pb->collision_listeners.add(this);
	floor24_pb->SetAsSensor(false);

	floor25.size = vec3(15, 0.5, 20);
	floor25.color = White;
	floor25.SetPos(-27.5, 0.5, -75.75);
	floor25_pb = App->physics->AddBody(floor25, 0.0f);
	floor25_pb->collision_listeners.add(this);
	floor25_pb->SetAsSensor(false);

	floor26.size = vec3(12, 0.5, 7);
	floor26.color = White;
	floor26.SetPos(-14, 0.5, -75.75);
	floor26_pb = App->physics->AddBody(floor26, 0.0f);
	floor26_pb->collision_listeners.add(this);
	floor26_pb->SetAsSensor(false);
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

	floor11_pb->GetTransform(&floor11.transform);
	floor11.Render();

	floor12_pb->GetTransform(&floor12.transform);
	floor12.Render();

	floor13_pb->GetTransform(&floor13.transform);
	floor13.Render();

	floor14_pb->GetTransform(&floor14.transform);
	floor14.Render();

	floor15_pb->GetTransform(&floor15.transform);
	floor15.Render();

	floor16_pb->GetTransform(&floor16.transform);
	floor16.Render();

	floor17_pb->GetTransform(&floor17.transform);
	floor17.Render();

	floor18_pb->GetTransform(&floor18.transform);
	floor18.Render();

	floor19_pb->GetTransform(&floor19.transform);
	floor19.Render();

	floor20_pb->GetTransform(&floor20.transform);
	floor20.Render();

	floor21_pb->GetTransform(&floor21.transform);
	floor21.Render();

	floor22_pb->GetTransform(&floor22.transform);
	floor22.Render();

	floor23_pb->GetTransform(&floor23.transform);
	floor23.Render();

	floor24_pb->GetTransform(&floor24.transform);
	floor24.Render();
	
	floor25_pb->GetTransform(&floor25.transform);
	floor25.Render();

	floor26_pb->GetTransform(&floor26.transform);
	floor26.Render();
}

