#pragma once
#include "wx/wx.h"

class Main : public wxFrame
{
public:
	Main();
	~Main();


public:
	int nFieldWidth = 10;
	int nFieldHeight = 10;
	wxButton** btns;

	int* nField = nullptr;
	bool firstClick = true;

	void OnButtonClicked(wxCommandEvent& evt);

	void ChangeColor(int mine_count, int y, int x);

	wxDECLARE_EVENT_TABLE();
};

