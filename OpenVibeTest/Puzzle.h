#ifndef PUZZLE_H_
#define PUZZLE_H_
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include "CIndieLib_vc2008.h"
#include "Rotation.h"

class Puzzle
{
public:
	bool running;
	bool started;

	int width;
	int height;

	int bpp;

	int tileRows;
	int tileCols;
	int tileWidth;
	int tileHeight;
	int scramNum;

	int selectedTile;

	CIndieLib *mI;

	std::vector<IND_Entity2d *> * tiles;
	std::vector<Rotation *> * rotations;

	IND_Font * fontSmall;
	IND_Font  *fontBig;
	IND_Entity2d * textTitle;

	IND_Entity2d * rightArrow;
	IND_Entity2d * leftArrow;

	IND_Entity2d * feedbackLeft;
	IND_Entity2d * feedbackRight;

	IND_Entity2d * controlDisplay;


public:
	Puzzle(CIndieLib *mI);
	void cleanUp();
	void rotateLeft(int i);
	void rotateRight(int i);
	void setTitle(std::string title);
	void drawTile(int r, int c);
	void drawLast();
	void drawGame();
	bool checkWin();
	int randInt(int n);
	void reset();
	void initGame();
	void scramble();
	void initTiles();
	void hideTiles();
	void showTiles();
	void selectTile(int index){
		if(index!=selectedTile){
			if(selectedTile!=-1){
				tiles->at(selectedTile)->SetTint(255,255,255);
			}
			selectedTile = index;
			tiles->at(index)->SetTint(120,120,120);
		}
	}


	inline int getTileIndex(int x, int y){
		int tileX = x/tileWidth;
		int tileY = y/tileHeight;
		tileX = (tileX>tileCols)?tileCols:tileX;
		tileY = (tileY>tileRows)?tileRows:tileY;
		tileX = (tileX<0)?0:tileX;
		tileY = (tileY<0)?0:tileY;
		return tileX*tileCols+ tileY; 
	}

	int getSelectedTile(){
		return selectedTile;
	}

	IND_Entity2d * getTextTitle(){
	  return textTitle;
	}


};
#endif