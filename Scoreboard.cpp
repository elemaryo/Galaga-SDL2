#include "Scoreboard.h"

Scoreboard::Scoreboard() : Scoreboard({230, 230, 230})
{

}

Scoreboard::Scoreboard(SDL_Color color)
{
	mColor = color;
	Score(0);
}

Scoreboard::~Scoreboard()
{

	ClearBoard();
}

// delete all the textures in score and clear vector
void Scoreboard::ClearBoard()
{
	for (int i = 0; i < mScore.size(); i++)
	{
		delete mScore[i];
		mScore[i] = NULL;
	}

	mScore.clear();
}

void Scoreboard::Score(int score)
{
	ClearBoard();
	// score has 00 so loop twice to add two textures with two 0s
	if (score == 0)
	{
		for (int i = 0; i < 2; i++)
		{
			mScore.push_back(new Texture("0", "emulogic.ttf", 32, mColor));
			mScore[i]->Parent(this);
			// keep adding digits to the left
			mScore[i]->Pos(Vector2(-32.0f * i, 0.0f));
		}
	}

	else
	{
		//convert score to string
		std::string str = std::to_string(score);
		int lastIndex = str.length() - 1;

		for (int i = 0; i <= lastIndex; i++)
		{
			mScore.push_back(new Texture(str.substr(i, 1), "emulogic.ttf", 32, mColor));
			mScore[i]->Parent(this);
			// keep adding digits to the left
			mScore[i]->Pos(Vector2(-32.0f * (lastIndex - i), 0.0f));
		}
	}
}

void Scoreboard::Render()
{

	for (int i = 0; i < mScore.size(); i++)
	{
		mScore[i]->Render();
	}
}
