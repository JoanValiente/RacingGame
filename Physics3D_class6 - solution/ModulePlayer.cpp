#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	CreateCar();

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		acceleration = MAX_ACCELERATION;
	}

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if(turn < TURN_DEGREES)
			turn +=  TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if(turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		acceleration = -MAX_ACCELERATION;
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();
	
	char title[80];
	sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	//App->window->SetTitle(title);

	if (dead == true)
	{
		Respawn();
	}


	return UPDATE_CONTINUE;
}


void ModulePlayer::Respawn()
{
	if (timer == 0)
	{
		vehicle->SetPos(0, 1, 10);
		vehicle->SetTransform(&matrix);
	}

	if (timer < 100)
	{
		App->player->vehicle->Brake(BRAKE_POWER);
		timer++;
	}
	else
	{
		dead = false;
		timer = 0;
	}

	

}

void ModulePlayer::CreateCar()
{
	VehicleInfo car;
	// Car properties ----------------------------------------
	car.chassis_size.Set(2, 2, 4);
	car.chassis_offset.Set(0, 1.5, 0);
	car.mass = 500.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 1;
	float suspensionRestLength = 0.5f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;

	vec3 direction(0, -1, 0);
	vec3 axis(-1, 0, 0);

	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);

	for (int i = 0; i < car.num_wheels; i++)
	{
		if (i == 0 || i == 1)
		{
			car.wheels[i].front = true;
			car.wheels[i].drive = true;
			car.wheels[i].steering = true;
		}
		else
		{
			car.wheels[i].front = false;
			car.wheels[i].drive = false;
			car.wheels[i].steering = false;
		}
		car.wheels[i].direction = direction;
		car.wheels[i].axis = axis;
		car.wheels[i].suspensionRestLength = suspensionRestLength;
		car.wheels[i].radius = wheel_radius;
		car.wheels[i].width = wheel_width;
		car.wheels[i].brake = true;
	}

	
	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 1, 10);
	vehicle->GetTransform(&matrix);

}
