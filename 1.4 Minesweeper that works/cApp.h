#pragma once
#include "wx/wx.h"
#include "Main.h"

class cApp : public wxApp
{
private:
	Main* mainWindow = nullptr;
public:
	cApp();
	~cApp();
	virtual bool OnInit();
};

