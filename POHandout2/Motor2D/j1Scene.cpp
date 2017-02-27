#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "j1Scene.h"
#include <time.h>

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	
	P1Face = (GuiImage*)App->gui->CreateElement(GuiType::image);
	P1Face->pos = { 210, 61 };

	P2Face = (GuiImage*)App->gui->CreateElement(GuiType::image);
	P2Face->pos = { 350, 61 };

	P3Face = (GuiImage*)App->gui->CreateElement(GuiType::image);
	P3Face->pos = { 250, 80 };

	charface[ryu].character = ryu;
	charface[ryu].texture_rect = { 925, 605, 168, 279 };
	charface[ryu].charbox_pos = { 240, 78 };

	charface[ken].character = ken;
	charface[ken].charbox_pos = { 240, 174 };
	charface[ken].texture_rect = { 925, 884, 168, 279 };

	charface[honda].character = honda;
	charface[honda].charbox_pos = { 312, 78 };
	charface[honda].texture_rect = { 1093, 605, 168, 279 };

	charface[blanka].character = blanka;
	charface[blanka].charbox_pos = { 384, 78 };
	charface[blanka].texture_rect = { 1261, 605, 168, 279 };

	charface[guile].character = guile;
	charface[guile].charbox_pos = { 456, 78 };
	charface[guile].texture_rect = { 1429, 605, 168, 279 };

	charface[chunli].character = chunli;
	charface[chunli].charbox_pos = {312, 174 };
	charface[chunli].texture_rect = { 1093, 884, 168, 279 };

	charface[zangief].character = zangief;
	charface[zangief].charbox_pos = { 384, 174 };
	charface[zangief].texture_rect = { 1261, 884, 168, 279 };

	charface[dhalsim].character = dhalsim;
	charface[dhalsim].charbox_pos = { 456, 174 };
	charface[dhalsim].texture_rect = { 1429, 884, 168, 279 };

	P1Face->texture_rect = charface[ryu].texture_rect;
	P2Face->texture_rect = charface[ken].texture_rect;
	P3Face->texture_rect = charface[honda].texture_rect;

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{

	
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
