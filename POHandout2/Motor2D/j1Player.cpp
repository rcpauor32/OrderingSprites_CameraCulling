#include "j1Player.h"
#include "j1Input.h"
#include "p2Log.h"

j1Player::j1Player()
{
}

j1Player::~j1Player()
{
}

bool j1Player::Awake()
{
	bool ret = true;
	LOG("Player Awake Start");

	return ret;
}

bool j1Player::Start()
{
	bool ret = true;
	LOG("Player Start");

	// Texture Settup

	//Walk
	{
		walk_rect[Up][0] = { 0, link_y*2, link_width, link_height};
		walk_rect[Up][1] = { link_x, link_y*2, link_width, link_height };
		walk_rect[Up][2] = { link_x*2 , link_y*2, link_width, link_height };
		walk_rect[Up][3] = { link_x*3, link_y*2, link_width, link_height };
		walk_rect[Up][4] = { link_x*4, link_y*2, link_width, link_height };
		walk_rect[Up][5] = { link_x*5, link_y*2, link_width, link_height };
		walk_rect[Up][6] = { link_x*6, link_y*2, link_width, link_height };

		walk_rect[Down][0] = { 0 ,  link_y, link_width, link_height };
		walk_rect[Down][1] = { link_x, link_y, link_width, link_height };
		walk_rect[Down][2] = { link_x*2, link_y, link_width, link_height };
		walk_rect[Down][3] = { link_x*3, link_y, link_width, link_height };
		walk_rect[Down][4] = { link_x*4, link_y, link_width, link_height };
		walk_rect[Down][5] = { link_x*5, link_y, link_width, link_height };
		walk_rect[Down][6] = { link_x*6, link_y, link_width, link_height };

		walk_rect[Right][0] = { 0  ,link_y*3,link_width,link_height };
		walk_rect[Right][1] = { link_x,link_y*3,link_width,link_height };
		walk_rect[Right][2] = { link_x*2,link_y*3,link_width,link_height };
		walk_rect[Right][3] = { link_x*3,link_y*3,link_width,link_height };
		walk_rect[Right][4] = { link_x*4,link_y*3,link_width,link_height };
		walk_rect[Right][5] = { link_x*5,link_y*3,link_width,link_height };
		walk_rect[Right][6] = { link_x*6,link_y*3,link_width,link_height };

		walk_rect[Left][0] = { 0  ,link_y*4,link_width,link_height };
		walk_rect[Left][1] = { link_x,link_y*4,link_width,link_height };
		walk_rect[Left][2] = { link_x*2,link_y*4,link_width,link_height };
		walk_rect[Left][3] = { link_x*3,link_y*4,link_width,link_height };
		walk_rect[Left][4] = { link_x*4,link_y*4,link_width,link_height };
		walk_rect[Left][5] = { link_x*5,link_y*4,link_width,link_height };
		walk_rect[Left][6] = { link_x*6,link_y*4,link_width,link_height };
	}

	Link_Movement = App->tex->Load("Sprites/Link_Movement.png");

	// !_Textures

	// Animations Settup

	// Walking
	{

		// Walking UP 
		{
			walk[Up].PushBack(walk_rect[Up][0]);
			walk[Up].PushBack(walk_rect[Up][1]);
			walk[Up].PushBack(walk_rect[Up][2]);
			walk[Up].PushBack(walk_rect[Up][3]);
			walk[Up].PushBack(walk_rect[Up][4]);
			walk[Up].PushBack(walk_rect[Up][5]);
			walk[Up].PushBack(walk_rect[Up][6]);
			walk[Up].speed = PL_WALK_FPS;
		}

		// Walking DOWN
		{
			walk[Down].PushBack(walk_rect[Down][0]);
			walk[Down].PushBack(walk_rect[Down][1]);
			walk[Down].PushBack(walk_rect[Down][2]);
			walk[Down].PushBack(walk_rect[Down][3]);
			walk[Down].PushBack(walk_rect[Down][4]);
			walk[Down].PushBack(walk_rect[Down][5]);
			walk[Down].PushBack(walk_rect[Down][6]);
			walk[Down].speed = PL_WALK_FPS;
		}

		// Walking LEFT
		{
			walk[Left].PushBack(walk_rect[Left][0]);
			walk[Left].PushBack(walk_rect[Left][1]);
			walk[Left].PushBack(walk_rect[Left][2]);
			walk[Left].PushBack(walk_rect[Left][3]);
			walk[Left].PushBack(walk_rect[Left][4]);
			walk[Left].PushBack(walk_rect[Left][5]);
			walk[Left].PushBack(walk_rect[Left][6]);
			walk[Left].speed = PL_WALK_FPS;
		}

		// Walking RIGHT
		{
			walk[Right].PushBack(walk_rect[Right][0]);
			walk[Right].PushBack(walk_rect[Right][1]);
			walk[Right].PushBack(walk_rect[Right][2]);
			walk[Right].PushBack(walk_rect[Right][3]);
			walk[Right].PushBack(walk_rect[Right][4]);
			walk[Right].PushBack(walk_rect[Right][5]);
			walk[Right].PushBack(walk_rect[Right][6]);
			walk[Right].speed = PL_WALK_FPS;
		}
	}

	// !_Animations

	// Variable Settup

	pos.x = 0;
	pos.y = 0;

	pl_speed.x = STD_PL_SPEED;
	pl_speed.y = STD_PL_SPEED;

	curr_dir = Down;

	// !_Variables

	return ret;
}

bool j1Player::Update(float dt)
{
	bool ret = true;

	// Logic
		//Movement
	{
		if (App->input->GetKey(SDL_SCANCODE_W) && App->input->GetKey(SDL_SCANCODE_A)) {
			pos.y -= pl_speed.y * sqrt(2) / 2;
			pos.x -= pl_speed.x * sqrt(2) / 2;
		}
		else if (App->input->GetKey(SDL_SCANCODE_A) && App->input->GetKey(SDL_SCANCODE_S)) {
			pos.y += pl_speed.y * sqrt(2) / 2;
			pos.x -= pl_speed.x * sqrt(2) / 2;
		}
		else if (App->input->GetKey(SDL_SCANCODE_S) && App->input->GetKey(SDL_SCANCODE_D)) {
			pos.y += pl_speed.y * sqrt(2) / 2;
			pos.x += pl_speed.x * sqrt(2) / 2;
		}
		else if (App->input->GetKey(SDL_SCANCODE_D) && App->input->GetKey(SDL_SCANCODE_W)) {
			pos.y -= pl_speed.y * sqrt(2) / 2;
			pos.x += pl_speed.x * sqrt(2) / 2;
		}
		else if (App->input->GetKey(SDL_SCANCODE_W)) {
			pos.y -= pl_speed.y;
			curr_dir = Up;
		}
		else if (App->input->GetKey(SDL_SCANCODE_A)) {
			pos.x -= pl_speed.x;
			curr_dir = Left;
		}
		else if (App->input->GetKey(SDL_SCANCODE_S)) {
			pos.y += pl_speed.y;
			curr_dir = Down;
		}
		else if (App->input->GetKey(SDL_SCANCODE_D)) {
			pos.x += pl_speed.x;
			curr_dir = Right;
		}

	}

	// !_Logic

	// Graphics
	
	App->render->Blit(Link_Movement, pos.x - PL_OFFSET_X, pos.y - PL_OFFSET_Y, &walk[curr_dir].GetCurrentFrame());

	//!_Graphics

	return ret;
}

bool j1Player::PostUpdate(float dt)
{
	bool ret = true;


	return ret;
}

bool j1Player::CleanUp()
{
	bool ret = true;
	LOG("Player CleanUp Start");

	// Unloading All Textures
	App->tex->UnLoad(Link_Movement);


	return ret;
}

bool j1Player::SetPosTile(int x, int y)
{
	bool ret = true;

	pos.x = App->map->MapToWorld(x, y).x;
	pos.y = App->map->MapToWorld(x, y).y;

	return ret;
}

p2Point<float> j1Player::GetPos()
{
	return pos;
}
