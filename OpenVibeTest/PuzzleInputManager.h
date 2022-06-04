#pragma once
#include "CIndieLib_vc2008.h"
#include "puzzle.h"

class PuzzleInputManager :
	public IND_Input
{
private:
	Puzzle * puzzle;
public:
	PuzzleInputManager(Puzzle * p);
	~PuzzleInputManager(void);
	void 	Update ();
};


