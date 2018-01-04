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

	start_timer = SDL_GetTicks() / 1000;

	s[0].SetPos(0, 2.5f, 20);
	s[0].size = vec3(16, 3, 0.5);
	s[1].SetPos(-113, 9, 15);
	s[1].size = s[0].size;
	s[2].SetPos(-45, 2, 105);
	s[2].size = vec3(0.5, 3, 16);
	s[3].SetPos(-65, 9, -75);
	s[3].size = vec3(0.5, 3, 30);


	App->audio->PlayMusic(music);

	for (int i = 0; i < 4; i++)
	{
		sensor[i] = App->physics->AddBody(s[i], 0.0f);
		sensor[i]->SetAsSensor(true);
		sensor[i]->collision_listeners.add(this);
		s[i].color = Red;
		s[i].Render();
	}

	death.size = vec3(300, 0.25, 300);
	death.SetPos(-50, 0.1, 0);
	death.color = Black;

	death_pb = App->physics->AddBody(death, 0.0f);
	death_pb->SetAsSensor(true);
	death_pb->collision_listeners.add(this);

	// Road
	LoadCircuit();
	
	checkpoint1 = true, checkpoint2 = true, checkpoint3 = true;
	laps = 0;
	timer = 180;
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

	for (int i = 0; i < 4; i++)
	{
		sensor[i]->GetTransform(&s[i].transform);
	}

	death_pb->GetTransform(&death.transform);
	death.Render();


	// Road
	PrintCircuit();

	Timer();

	char title[80];
	sprintf_s(title, "Lap %i/3 Time %i", laps, actual_time);
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	LOG("Hit!");
	if (body1 == death_pb)
	{
		App->player->dead = true;
	}
	if (body1 == sensor[0])
	{
		if (checkpoint1 == true && checkpoint2 == true && checkpoint3 == true)
		{
			laps++;
			if(laps == 4)
			{ 
				App->player->win = true;
			}
			checkpoint1 = false, checkpoint2 = false, checkpoint3 = false;
		}
	}
	if (body1 == sensor[1])
	{
		checkpoint1 = true;
	}
	if (body1 == sensor[2])
	{
		checkpoint2 = true;
	}
	if (body1 == sensor[3])
	{
		checkpoint3 = true;
	}
}



void ModuleSceneIntro::LoadCircuit()
{	
	//ROAD
	CreateCircuit(vec3(16, 0.5, 160), White, vec3(0, 0.5, 0.75), 0, vec3(0, 0, 0));
	CreateCircuit(vec3(17, 0.5, 50), White, vec3(-16.5, 0.5, 85), 0, vec3(0, 0, 0));
	CreateCircuit(vec3(20, 0.5, 12), White, vec3(-35, 0.5, 104), 0, vec3(0, 0, 0));
	CreateCircuit(vec3(20, 0.5, 12), White, vec3(-54, 4, 104), -20, vec3(0, 0, 1));
	CreateCircuit(vec3(35, 0.5, 12), White, vec3(-80.75, 7.4, 104), 0, vec3(0, 0, 0));
	CreateCircuit(vec3(27.5, 0.5, 9), White, vec3(-100, 7.4, 93.5), 0, vec3(0, 0, 0));
	CreateCircuit(vec3(16, 0.5, 30), White, vec3(-121.75, 7.4, 83), 0, vec3(0, 0, 0));
	CreateCircuit(vec3(18, 0.5, 9), White, vec3(-104.75, 7.4, 72.5), 0, vec3(0, 0, 0));
	CreateCircuit(vec3(9, 0.5, 23), White, vec3(-104.73, 7.4, 59.5), 25, vec3(0, 1, 0));
	CreateCircuit(vec3(9, 0.5, 23), White, vec3(-104.73, 7.4, 42.5), -25, vec3(0, 1, 0));
	CreateCircuit(vec3(9, 0.5, 23), White, vec3(-104.73, 7.4, 25.5), 25, vec3(0, 1, 0));
	CreateCircuit(vec3(9, 0.5, 23), White, vec3(-104.73, 7.4, 8.5), -25, vec3(0, 1, 0));
	CreateCircuit(vec3(9, 0.5, 23), White, vec3(-120.8, 7.4, 59.5), -25, vec3(0, 1, 0));
	CreateCircuit(vec3(9, 0.5, 23), White, vec3(-120.8, 7.4, 42.5), 25, vec3(0, 1, 0));
	CreateCircuit(vec3(9, 0.5, 23), White, vec3(-120.8, 7.4, 25.5), -25, vec3(0, 1, 0));
	CreateCircuit(vec3(9, 0.5, 23), White, vec3(-120.8, 7.4, 8.5), 25, vec3(0, 1, 0));
	CreateCircuit(vec3(34, 0.5, 9), White, vec3(-112.75, 7.4, -4.5), 0, vec3(0, 0, 0));
	CreateCircuit(vec3(16, 0.5, 31.5), White, vec3(-103.75, 7.4, -24.75), 0, vec3(0, 0, 0));
	CreateCircuit(vec3(40.5, 0.5, 11), White, vec3(-129.925, 7.4, -29.95), 15, vec3(0, 1, 0));
	CreateCircuit(vec3(11, 0.5, 30), White, vec3(-145.4, 7.4, -45), 0, vec3(0, 0, 0));
	CreateCircuit(vec3(45, 0.5, 11), White, vec3(-127.8, 7.4, -60.22), 15, vec3(0, 1, 0));
	CreateCircuit(vec3(47.5, 0.5, 30), White, vec3(-92.85, 7.4, -75.75), 0, vec3(0, 0, 0));
	CreateCircuit(vec3(10, 0.5, 9), White, vec3(-64.249, 8.745, -75.75), 15, vec3(0, 0, 1));
	CreateCircuit(vec3(10, 0.5, 9), White, vec3(-40, 0.5, -75.75), 0, vec3(0, 0, 0));
	CreateCircuit(vec3(15, 0.5, 20), White, vec3(-27.5, 0.5, -75.75), 0, vec3(0, 0, 0));
	CreateCircuit(vec3(12, 0.5, 7), White, vec3(-14, 0.5, -75.75), 0, vec3(0, 0, 0));

	//WALLS
	CreateCircuit(vec3(14.5, 0.5, 132), RedGray, vec3(-8, 0.5, -6), 90, vec3(0, 0, 1));
	CreateCircuit(vec3(14.5, 0.5, 161), RedGray, vec3(8, 0.5, 1), 90, vec3(0, 0, 1));
	CreateCircuit(vec3(14.5, 16, 0.5), RedGray, vec3(0, 0.5, 81), 90, vec3(0, 0, 1));
	CreateCircuit(vec3(14.5, 17, 0.5), RedGray, vec3(-16.5, 0.5, 60), 90, vec3(0, 0, 1));
	CreateCircuit(vec3(14.5, 0.5, 38), RedGray, vec3(-25.2, 0.5, 79), 90, vec3(0, 0, 1));
	CreateCircuit(vec3(14.5, 0.5, 29.5), RedGray, vec3(-8.2, 0.5, 95.5), 90, vec3(0, 0, 1));
	CreateCircuit(vec3(14.5, 55, 0.5), RedGray, vec3(-35.8, 0.5, 110), 90, vec3(0, 0, 1));
	CreateCircuit(vec3(14.5, 38.5, 0.5), RedGray, vec3(-44.2, 0.5, 98), 90, vec3(0, 0, 1));
	CreateCircuit(vec3(14.5, 12.5, 0.5), RedGray, vec3(-14, 0.5, -72), 90, vec3(0, 0, 1));
	CreateCircuit(vec3(14.5, 28, 0.5), RedGray, vec3(-6, 0.5, -79.5), 90, vec3(0, 0, 1));
	CreateCircuit(vec3(14.5, 15, 0.5), RedGray, vec3(-27.5, 0.5, -65.5), 90, vec3(0, 0, 1));
	CreateCircuit(vec3(14.5, 15, 0.5), RedGray, vec3(-27.5, 0.5, -86), 90, vec3(0, 0, 1));
	CreateCircuit(vec3(14.5, 0.5, 6.5), RedGray, vec3(-20, 0.5, -82.5), 90, vec3(0, 0, 1));
	CreateCircuit(vec3(14.5, 0.5, 6.5), RedGray, vec3(-20, 0.5, -68.5), 90, vec3(0, 0, 1));
	CreateCircuit(vec3(14.5, 0.5, 6), RedGray, vec3(-35, 0.5, -83.25), 90, vec3(0, 0, 1));
	CreateCircuit(vec3(14.5, 0.5, 6), RedGray, vec3(-35, 0.5, -68.3), 90, vec3(0, 0, 1));
	CreateCircuit(vec3(14.5, 34, 0.5), RedGray, vec3(-52, 0.5, -80), 90, vec3(0, 0, 1));
	CreateCircuit(vec3(14.5, 34, 0.5), RedGray, vec3(-52, 0.5, -71), 90, vec3(0, 0, 1));

}


void ModuleSceneIntro::PrintCircuit()
{
	p2List_item <PhysBody3D*>* tmp_pb = circuit_pb.getFirst();
	p2List_item <Cube>* tmp = circuit.getFirst();
	while (tmp != nullptr) {
		tmp_pb->data->GetTransform(&tmp->data.transform);
		tmp->data.Render();
		tmp = tmp->next;
		tmp_pb = tmp_pb->next;
	}
}

void ModuleSceneIntro::Timer()
{
	if (App->player->win == false)
	{
		actual_time = SDL_GetTicks() / 1000 - start_timer;
		actual_time -= timer;
		actual_time = actual_time*-1;
	}

	if (actual_time == 0)
		App->player->lose = true;

}

void ModuleSceneIntro::CreateCircuit(vec3 size, Color color, vec3 pos, float angle, vec3 rotation_axis) {
	Cube tmp;
	PhysBody3D *tmp_pb;
	tmp.size = size;
	tmp.color = color;
	tmp.SetPos(pos.x, pos.y, pos.z);
	if (angle != 0) {
		tmp.SetRotation(angle, rotation_axis);
	}
	tmp_pb = App->physics->AddBody(tmp, 0.0f);
	tmp_pb->collision_listeners.add(this);
	tmp_pb->SetAsSensor(false);

	circuit.add(tmp);
	circuit_pb.add(tmp_pb);
	
}
