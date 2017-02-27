// ----------------------------------------------------
// j1Module.h
// Interface for all engine modules
// ----------------------------------------------------

#ifndef __j1MODULE_H__
#define __j1MODULE_H__

#include "p2SString.h"
#include "p2DynArray.h"
#include "PugiXml\src\pugixml.hpp"

class j1App;
class UIElement;
struct Command;
enum GuiEvents;
struct CVar;


class j1Module
{
public:

	j1Module() : active(false)
	{}

	virtual ~j1Module()
	{}

	void Init()
	{
		active = true;
	}

	// Called before render is available
	virtual bool Awake(pugi::xml_node&)
	{
		return true;
	}

	// Called before the first frame
	virtual bool Start()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PreUpdate()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool Update(float dt)
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PostUpdate()
	{
		return true;
	}

	// Called before quitting
	virtual bool CleanUp()
	{
		return true;
	}

	virtual bool Load(pugi::xml_node&)
	{
		return true;
	}

	virtual bool Save(pugi::xml_node&) const
	{
		return true;
	}


	virtual void OnGui(UIElement* ui, GuiEvents event)
	{}

	virtual bool OnCommand(const Command*, const p2DynArray<p2SString>& arguments, p2SString& return_message)
	{
		return true;
	}

	virtual void OnCVar(const CVar* var)
	{}

public:

	p2SString	name;
	bool		active;

};

#endif // __j1MODULE_H__