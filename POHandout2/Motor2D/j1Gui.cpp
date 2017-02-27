#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	focus_it = focus_list.start;

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN) {
		if (focus_it->next != NULL)
			focus_it = focus_it->next;
		else
			focus_it = focus_list.start;
	}
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	for (p2List_item<UIElement*>* it = elements.start; it != NULL; it = it->next) {
		if(it->data->active)
			it->data->Update();
	}
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	DeleteElements();

	return true;
}

UIElement * j1Gui::CreateElement(GuiType type)
{
	UIElement* ret = nullptr;

	switch (type)
	{
	case GuiType::image:
		ret = new GuiImage();
		ret->type = image;
		break;

	case GuiType::text:
		ret = new GuiText();
		ret->type = text;
		break;
	
	case GuiType::button:
		ret = new GuiButton();
		ret->type = button;
		break;

	case GuiType::textin:
		ret = new GuiTextInput();
		ret->type = textin;
		break;
	case GuiType::scrollbar:
		ret = new GuiScrollBar();
		ret->type = scrollbar;
		break;
	}

	if (ret != nullptr) {
		ret->focus_order = 0;
		ret->pos.x = 0;
		ret->pos.y = 0;
		ret->texture = atlas;
		ret->active = true;
		ret->movable = false;
		ret->Start();
		elements.add(ret);
	}

	return ret;
}

UIElement * j1Gui::CreateElement(GuiType type, const char* path)
{
	
	UIElement* ret = nullptr;

	switch (type)
	{
	case GuiType::image:
		ret = new GuiImage();
		ret->type = image;
		break;

	case GuiType::text:
		ret = new GuiText();
		ret->type = text;
		break;

	case GuiType::button:
		ret = new GuiButton();
		ret->type = button;
		break;

	case GuiType::textin:
		ret = new GuiTextInput();
		ret->type = textin;
		break;
	case GuiType::scrollbar:
		ret = new GuiScrollBar();
		ret->type = scrollbar;
		break;

	}

	if (ret != nullptr) {
		ret->focus_order = 0;
		ret->pos.x = 0;
		ret->pos.y = 0;
		ret->texture = App->tex->Load(path);
		ret->active = true;
		ret->movable = false;
		ret->Start();
		elements.add(ret);
	}

	return ret;
}

void j1Gui::DeleteElements()
{
	for (p2List_item<UIElement*>* it = elements.start; it != NULL; it = it->next) {
		if(it != nullptr)
			delete it->data;
	}
}

// const getter for atlas
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------

void GuiImage::Update()
{
	if (DetectMouse() && App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT) {
		if (movable == true) {
			iPoint motion;
			App->input->GetMouseMotion(motion.x, motion.y);
			MoveBy(motion.x, motion.y);
		}
	}
		

	App->render->Blit(this->texture, pos.x, pos.y, &texture_rect);
}

void GuiText::Update()
{
	texture = App->font->Print(string.GetString());
	App->font->CalcSize(string.GetString(), texture_rect.w, texture_rect.h);
	
	App->render->Blit(texture, pos.x, pos.y, &texture_rect);
}

void GuiButton::Start()
{
	state = standard;

	for (int i = standard; i < GuiButton::Unknown; i++) {
		image[i] = new GuiImage();
		image[i]->active = true;
	}

	texture_rect = image[standard]->texture_rect;

}

void GuiButton::Update()
{
	texture_rect = image[standard]->texture_rect;

	if (state != disabled || state != tabbed) {

		if (DetectMouse() == true) {
			state = hover;
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT) {
				state = left_clicked;
				iPoint motion;
				App->input->GetMouseMotion(motion.x, motion.y);
				this->MoveBy(motion.x, motion.y);
			}
			if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_REPEAT)
				state = right_clicked;
		}
		else
			state = standard;
	
	}


	image[state]->pos.x = this->pos.x;
	image[state]->pos.y = this->pos.y;

	if (image[state] != nullptr) {
		image[state]->Update();
	}
	else
		image[standard]->Update();

}


UIElement * UIElement::Attach(UIElement * child)
{
	if(child != nullptr)
		children.add(child);

	return child;
}

void UIElement::MoveBy(int x, int y)
{
	pos.x += x;
	pos.y += y;

	for (p2List_item<UIElement*>* it = children.start; it != NULL; it = it->next) {
		it->data->MoveBy(x, y);
	}
}

bool UIElement::DetectMouse()
{
	bool ret = false;

	iPoint mousepos;

	App->input->GetMousePosition(mousepos.x, mousepos.y);

	if (mousepos.x >= pos.x && mousepos.x <= pos.x + texture_rect.w && mousepos.y >= pos.y && mousepos.y <= pos.y + texture_rect.h)
		ret = true;

	return ret;
}

void GuiTextInput::Start()
{
	text = CREATETEXT;
	triggered = false;
}

void GuiTextInput::Update()
{
	
	text->pos = pos;


	App->font->CalcSize(text->string.GetString(), texture_rect.w, texture_rect.h);
	texture_rect.w *= 2;
	texture_rect.h *= 2;
	//App->render->Blit(texture, pos.x, pos.y, &texture_rect);
	if (!App->font->Print(text->string.GetString(), text->color)) {
		LOG("ERROR PRINTING HELLO WORLD");
	}
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) {
		if (DetectMouse()) {
			triggered = true;
			//textbar_pos = pos.x;
			SDL_StartTextInput();
		}
		else triggered = false;
	}

	if (triggered) {

		text->string += App->input->GetText();
		//App->render->Blit(textbar, textbar_pos, pos.y);
		//if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN) {
		//	textbar_pos += rekt.w / tex.Length();
		//	//cursorpos[0]++;
		//}
		//if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) {
		//	textbar_pos += rekt.w / tex.Length();
		//	//if (cursorpos[0]>0) cursorpos[0]--;
		//}
		if (App->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN) {
			text->string.Trim();
		}
	}
	else { 
		SDL_StopTextInput(); 
		triggered = false;
		}
	}

void GuiScrollBar::Update()
{
	iPoint prePos = this->pos;
	
	if (DetectMouse() && App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT) {
		iPoint motion;
		App->input->GetMouseMotion(motion.x, motion.y);
		MoveBy(0, motion.y);
		if (pos.y < limit_max)
			MoveBy(0, -motion.y);
		if (pos.y > limit_min)
			MoveBy(0, -motion.y);

	}

	for (p2List_item<UIElement*>* it = children.start; it != NULL; it = it->next) {
		
		int dif = pos.y - prePos.y;

		if (prePos.y != pos.y) 
			it->data->pos.y += dif;

		if (it->data->pos.y < show_rect.y) {
			it->data->texture_rect.y -= (it->data->pos.y - show_rect.y);
			it->data->pos.y = show_rect.y;
		}
		else {
			it->data->texture_rect.y += (show_rect.y - it->data->pos.y);
			it->data->pos.y = show_rect.y;
		}

		if (it->data->pos.y + it->data->texture_rect.h > show_rect.y + show_rect.h) {
			it->data->texture_rect.h -= (it->data->pos.y + it->data->texture_rect.h - show_rect.y - show_rect.h);
		}
		else {
			it->data->texture_rect.h += (show_rect.y + show_rect.h - it->data->pos.y - it->data->texture_rect.h);
		}

		if (it->data->texture_rect.w == 0)
			it->data->active = false;
		else 
			it->data->active = true;
	}

	App->render->Blit(texture, pos.x, pos.y, &texture_rect);

}
