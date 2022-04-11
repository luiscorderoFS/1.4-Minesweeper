#include "Main.h"

wxBEGIN_EVENT_TABLE(Main, wxFrame)
wxEND_EVENT_TABLE()


Main::Main() : wxFrame(nullptr, wxID_ANY, "1.4 Minesweeper", wxPoint(30, 30), wxSize(1024, 780))
{
	/*btn1 = new wxButton(this, 10001, "Click Me", wxPoint(10, 10), wxSize(150, 50));
	txt1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 70), wxSize(300, 30));
	list1 = new wxListBox(this, wxID_ANY, wxPoint(10, 110), wxSize(300, 300));*/
	btns = new wxButton * [nFieldWidth * nFieldHeight];
	wxGridSizer* grid = new wxGridSizer(nFieldWidth, nFieldHeight, 0, 0);

	//Creating array of mines
	nField = new int[nFieldWidth * nFieldHeight];

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (int x = 0; x < nFieldWidth; x++)
	{
		for (int y = 0; y < nFieldHeight; y++)
		{
			btns[y * nFieldWidth + x] = new wxButton(this, 10000 + (y * nFieldWidth + x));
			btns[y * nFieldWidth + x]->SetFont(font);
			grid->Add(btns[y * nFieldWidth + x], 1, wxEXPAND | wxALL);
			btns[y * nFieldWidth + x]->SetBackgroundColour(*wxLIGHT_GREY);
			btns[y * nFieldWidth + x]->SetForegroundColour(wxColour(105, 105, 105));

			btns[y * nFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Main::OnButtonClicked, this);
			nField[y * nFieldWidth + x] = 0;
		}
	}

	this->SetSizer(grid);
	grid->Layout();
}

Main::~Main()
{
	delete[] btns;
}

void Main::OnButtonClicked(wxCommandEvent& evt)
{

	int x = (evt.GetId() - 10000) % nFieldWidth;
	int y = (evt.GetId() - 10000) / nFieldWidth;

	if (firstClick)
	{
		int mines = 50;
		while (mines)
		{
			int rX = rand() % nFieldWidth;
			int rY = rand() % nFieldHeight;

			if (rX != x && rY != y && nField[rY * nFieldWidth + rX] == 0)
			{
				nField[rY * nFieldWidth + rX] = -1;
				mines--;

			}
		}
		firstClick = false;
	}

	btns[y * nFieldWidth + x]->Enable(false);

	if (nField[y * nFieldWidth + x] == -1)
	{
		
		for (int x = 0; x < nFieldWidth; x++)
			for (int y = 0; y < nFieldHeight; y++)
			{	

				if (nField[y * nFieldWidth + x] == -1)
				{
					btns[y * nFieldWidth + x]->SetBackgroundColour(*wxBLACK);
					btns[y * nFieldWidth + x]->SetForegroundColour(*wxYELLOW);

					btns[y * nFieldWidth + x]->SetFont(wxFont(6, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false));

					btns[y * nFieldWidth + x]->SetLabel("        ,--.!,\n     __/   -*-\n   ,d08b.  '|`\n   0088MM     \n   `9MMP'     ");


				}
				else
				{
					int mineShow = 0;
					for (int i = -1; i < 2; i++)
						for (int j = -1; j < 2; j++)
						{
							if (x + i >= 0 && x + i < nFieldWidth && y + j >= 0 && y + j < nFieldHeight)
							{
								if (nField[(y + j) * nFieldWidth + (x + i)] == -1)
									mineShow++;
							}
						}
					ChangeColor(mineShow, y, x);
					btns[y * nFieldWidth + x]->SetLabel(std::to_string(mineShow));
				}
				

			}


		wxMessageBox("You lose entirely", "Sorry :(");
		//Reset Game

		firstClick = true;
		for (int x = 0; x < nFieldWidth; x++)
			for (int y = 0; y < nFieldHeight; y++)
			{
				nField[y * nFieldWidth + x] = 0;
				btns[y * nFieldWidth + x]->SetLabel("");
				btns[y * nFieldWidth + x]->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false));
				btns[y * nFieldWidth + x]->SetForegroundColour(wxColour(105,105,105));

				btns[y * nFieldWidth + x]->SetBackgroundColour(*wxLIGHT_GREY);
				btns[y * nFieldWidth + x]->Enable(true);
			}
	}
	else
	{
		//counting if neighbors are mines
		int mine_count = 0;
		for (int i = -1; i < 2; i++)
			for (int j = -1; j < 2; j++)
			{
				if (x + i >= 0 && x + i < nFieldWidth && y + j >= 0 && y + j < nFieldHeight)
				{
					if (nField[(y + j) * nFieldWidth + (x + i)] == -1)
						mine_count++;
				}
			}


		if (mine_count > 0)
		{
			ChangeColor(mine_count, y, x);
			btns[y * nFieldWidth + x]->SetLabel(std::to_string(mine_count));

		}
		else
		{
			btns[y * nFieldWidth + x]->SetLabel("0");

		}
	}



	evt.Skip();
}

void Main::ChangeColor(int mine_count, int y, int x)
{
	switch (mine_count)
	{
	case 1:
		btns[y * nFieldWidth + x]->SetBackgroundColour(*wxBLUE);
		break;
	case 2:
		btns[y * nFieldWidth + x]->SetBackgroundColour(*wxGREEN);
		break;
	case 3:
		btns[y * nFieldWidth + x]->SetBackgroundColour(*wxRED);
		break;
	case 4:
		btns[y * nFieldWidth + x]->SetBackgroundColour(wxColour(128, 0, 128));
		break;
	case 5:
		btns[y * nFieldWidth + x]->SetBackgroundColour(wxColour(128, 0, 0));
		break;
	case 6:
		btns[y * nFieldWidth + x]->SetBackgroundColour(wxColour(64, 224, 208));
		break;
	case 7:
		btns[y * nFieldWidth + x]->SetForegroundColour(wxColour(255,255,255));

		btns[y * nFieldWidth + x]->SetBackgroundColour(*wxBLACK);
		break;
	case 8:
		btns[y * nFieldWidth + x]->SetBackgroundColour(wxColour(128, 128, 128));
		break;
	}
}
