#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "p2DynArray.h"

struct SDL_Texture;
class UIElement;
class GuiImage;
class GuiText;
class GuiButton;
class GuiWindow;
class GuiTextInput;
class GuiScrollBar;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

public:
	// EXERCISE[3]
	enum Characters {
		ryu = 0,
		ken,
		blanka,
		guile,
		honda,
		chunli,
		zangief,
		dhalsim,
		__LAST

	};
private:
	struct CharFace {
		iPoint charbox_pos;
		Characters character;
		SDL_Rect texture_rect;
		
	} charface[__LAST];

	GuiImage* P1Face;
	GuiImage* P2Face;
	GuiImage* P3Face;

};

#endif // __j1SCENE_H__