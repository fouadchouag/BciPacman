#include "PuzzleInputManager.h"


PuzzleInputManager::PuzzleInputManager(Puzzle * p): puzzle(p)
{

}


PuzzleInputManager::~PuzzleInputManager(void)
{
}

void   PuzzleInputManager::Update (){
	IND_Input::Update();

	int index = puzzle->getTileIndex(GetMouseX(), GetMouseY());
	Rotation * r = puzzle->rotations->at(index);
	if(OnMouseButtonPress(IND_MBUTTON_LEFT)){
		r->doRotate();
	} else if(OnMouseButtonPress(IND_MBUTTON_RIGHT)){
		r->doRotate();
		r->doRotate();
		r->doRotate();
	}
	puzzle->selectTile(index);

}