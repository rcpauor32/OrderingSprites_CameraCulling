#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "j1Fonts.h"
#include "p2Point.h"
#include "j1App.h"
#include "SDL\include\SDL_rect.h"

#define CREATEIMAGE(path) (GuiImage*)App->gui->CreateElement(GuiType::image, path);
#define CREATETEXT (GuiText*)App->gui->CreateElement(GuiType::text);

#define CURSOR_WIDTH 2

enum GuiEvents
{
	listening_ends,
	mouse_enters,
	mouse_leaves,
	mouse_lclick_down,
	mouse_lclick_up,
	mouse_rclick_down,
	mouse_rclick_up,
	gain_focus,
	lost_focus,
	input_changed,
	input_submit,
	value_changed
};

enum GuiType {
	image = 0,
	text,
	button,
	window,
	textin,
	scrollbar,
	unknown
};

// UI ELEMENT
class UIElement {
public:
	iPoint pos;
	GuiType type;
	
	bool active;
	bool movable;

	SDL_Texture* texture;
	SDL_Rect texture_rect;

	p2List<UIElement*> children;

	uint focus_order;

public:
	virtual void Start() {};
	virtual void Update() {};

	UIElement* Attach(UIElement* child);

protected:
	void MoveBy(int x, int y);
	bool DetectMouse();

};

// IMAGE
class GuiImage : public UIElement {
public:
	void Update();
};

// TEXT LABEL
class GuiText : public UIElement {
public:
	_TTF_Font* font;
	SDL_Color color;
	p2SString string;

public:
	
	GuiText(){}
	~GuiText(){}

public:
	void Update();
};

// BUTTON
class GuiButton : public UIElement {
public:
	enum State {
		standard = 0,
		left_clicked,
		right_clicked,
		hover,
		disabled,
		tabbed,
		Unknown
	} state;

	GuiImage* image[State::Unknown];

public:
	GuiButton(){}
	~GuiButton() {
		for (int i = standard; i < Unknown; i++)
			if (image[i] != nullptr)
				delete image[i];
	}

	void Start();
	void Update();

};

// TEXT INPUT
class GuiTextInput : public UIElement {
public:
	bool triggered;
	SDL_Rect input_rect;
	GuiText* text;

public:
	void Start();
	void Update();

};

class GuiScrollBar : public UIElement {
public:
	int limit_min, limit_max;
	SDL_Rect show_rect;
public:
	void Update();

};

// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Gui creation functions
	UIElement* CreateElement(GuiType type);
	UIElement* CreateElement(GuiType type, const char* path);
	void DeleteElements();

	p2List<UIElement*> focus_list;
	p2List_item<UIElement*>* focus_it;

	SDL_Texture* GetNonConstAtlas() const {
		return atlas;
	}

	const SDL_Texture* GetAtlas() const;

private:
	p2List<UIElement*> elements;

	SDL_Texture* atlas;
	p2SString atlas_file_name;
};

#endif // __j1GUI_H__