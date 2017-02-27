#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "j1Module.h"
#include "Animation.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Map.h"

#define MAX_SPRITE_FRAMES 8

#define PL_OFFSET 12
#define PL_OFFSET_X 33
#define PL_OFFSET_Y 35

#define PL_WALK_FPS 0.8f

#define link_width 99
#define link_height 107
#define link_y 110
#define link_x 102

#define STD_PL_SPEED 2.5


class j1Player : public j1Module {
public:
	enum Direction {
		FirstDir = 0,
		Up,
		Left,
		Right,
		Down,
		__LASTDIR
	};

private:
	p2Point<float> pos;
	p2Point<float> pl_speed;

	SDL_Texture* Link_Movement = nullptr;

	// All player sprites / animations
	Animation walk[Direction::__LASTDIR];
	SDL_Rect walk_rect[Direction::__LASTDIR][MAX_SPRITE_FRAMES];

	Direction curr_dir;

public:
	j1Player();
	virtual ~j1Player();

private:
	bool Awake();
	bool Start();
	bool Update(float dt);
	bool PostUpdate(float dt);
	bool CleanUp();

public:
	bool SetPosTile(int x, int y);
	p2Point<float> GetPos();

};

#endif // !__PLAYER_H__
