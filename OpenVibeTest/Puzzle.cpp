#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "puzzle.h"
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>
#include <sstream>



void Puzzle::cleanUp()
{	

}


bool Puzzle::checkWin()
{
	for(std::vector<Rotation *>::iterator it = rotations->begin();it != rotations->end();it++){
		if((*it)->getRotation()!=ROT_0){
			return false;
		}
	}
	return true;
}

void Puzzle::rotateLeft(int i){
	Rotation * crot = rotations->at(i);
	crot->rotateLeft();
}
void Puzzle::rotateRight(int i){
	Rotation * crot = rotations->at(i);
	crot->rotateRight();
}

int Puzzle::randInt(int n)
{
	static int init = 0;

	if(init == 0)
	{
		srand(time(NULL));
		init = 1;
	}

	return rand() % n;
}

void Puzzle::reset()
{
	initTiles();
	this->started = false;
}

void Puzzle::scramble()
{
	for(int i=0;i<tileCols;i++){
		for(int j=0;j<tileRows;j++){
			int r = randInt(4);
			Rotation * crot = rotations->at(i+j*tileRows);
			crot->setRotation((rotation_t)r);
		}
	}

	started = true;
}


Puzzle::Puzzle(CIndieLib *mI)
{

	bpp = 32;
	tileRows = 3;
	tileCols = 3;
	tileWidth = 133;
	tileHeight = 133;
	this->mI = mI;
	selectedTile=-1;

    this->tiles = new std::vector<IND_Entity2d *>();
	this->rotations = new std::vector<Rotation *>();
	fontSmall = new IND_Font();
	fontBig = new IND_Font();
	textTitle = new IND_Entity2d();
 
}
void Puzzle::initGame(){
	mI->FontManager->Add(fontSmall, ".\\data\\font_small.png", ".\\data\\font_small.xml", IND_ALPHA, IND_32);
	mI->FontManager->Add (fontBig, ".\\data\\font_big.png", ".\\data\\font_big.xml", IND_ALPHA, IND_32);					
	mI->Entity2dManager->Add (textTitle);
	textTitle->SetFont(fontBig);

	//textTitle->SetText				("IndieLib Fonts");	
	textTitle->SetLineSpacing		(18);
	textTitle->SetCharSpacing		(-8);
	textTitle->SetPosition			(200, 40, 1);
	textTitle->SetAlign				(IND_CENTER);

	initTiles();
	scramble();

	IND_Surface * cpbgimg = new IND_Surface(); 
	mI->SurfaceManager->Add(cpbgimg, ".\\data\\cp.png", IND_ALPHA, IND_32);
	controlDisplay = new IND_Entity2d();
	mI->Entity2dManager->Add(controlDisplay);
	controlDisplay->SetSurface (cpbgimg);
	controlDisplay->SetPosition(0,0,0);
	controlDisplay->SetShow(true);

	IND_Surface * rarrow = new IND_Surface(); 
	mI->SurfaceManager->Add(rarrow, ".\\data\\aright.png", IND_ALPHA, IND_32);
	rightArrow = new IND_Entity2d();	
	mI->Entity2dManager->Add(rightArrow);
	rightArrow->SetSurface (rarrow);
	rightArrow->SetPosition(tileWidth*tileCols/2,0,1);
	rightArrow->SetShow(false);

	IND_Surface * larrow = new IND_Surface(); 
	mI->SurfaceManager->Add(larrow, ".\\data\\aleft.png", IND_ALPHA, IND_32);
	leftArrow = new IND_Entity2d();	
	mI->Entity2dManager->Add(leftArrow);
	leftArrow->SetSurface (larrow);
	leftArrow->SetPosition(tileWidth*(tileCols)/2-tileWidth,0,1);
	leftArrow->SetShow(false);

	IND_Surface * fdbr = new IND_Surface(); 
	mI->SurfaceManager->Add(fdbr, ".\\data\\feedback.png", IND_ALPHA, IND_32);
	feedbackRight = new IND_Entity2d();	
	mI->Entity2dManager->Add(feedbackRight);
	feedbackRight->SetSurface (fdbr);
	feedbackRight->SetPosition(tileWidth*tileCols/2,0,2);
	feedbackRight->SetShow(true);

	IND_Surface * fdbl = new IND_Surface(); 
	mI->SurfaceManager->Add(fdbl, ".\\data\\feedback.png", IND_ALPHA, IND_32);
	feedbackLeft = new IND_Entity2d();	
	mI->Entity2dManager->Add(feedbackLeft);
	feedbackLeft->SetSurface (fdbr);
	feedbackLeft->SetPosition(0,0,2);
	feedbackLeft->SetShow(true);
}
void Puzzle::initTiles(){
	for(int i=0;i<tileCols;i++){
		for(int j=0;j<tileRows;j++){
			std::stringstream ss(std::stringstream::out);
			ss << ".\\data\\im_" << i+1 << "_" << j+1<< ".png";
			std::string s = ss.str();
			IND_Surface * tile = new IND_Surface(); 
			if(!mI->SurfaceManager->Add(tile, (char *)ss.str().c_str(), IND_ALPHA, IND_32)) {return;}
			IND_Entity2d * etile = new IND_Entity2d();	
			mI->Entity2dManager->Add (etile);
			etile->SetSurface (tile);
			etile->SetPosition(i*tileWidth,j*(tileHeight) + tileHeight,0);
			tiles->push_back(etile);
			rotations->push_back(new Rotation(etile,tileWidth,tileHeight));
		}
	}	
}

void Puzzle::hideTiles(){
	for(std::vector<IND_Entity2d *>::iterator it = tiles->begin();it != tiles->end();it++){
		(*it)->SetShow(false);
	}
}

void Puzzle::showTiles(){
	for(std::vector<IND_Entity2d *>::iterator it = tiles->begin();it != tiles->end();it++){
		(*it)->SetShow(true);
	}
}