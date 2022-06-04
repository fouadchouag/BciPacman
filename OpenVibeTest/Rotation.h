#ifndef ROTATION_H_
#define ROTATION_H_

#include "CIndieLib_vc2008.h"
#include <cmath>

typedef enum{
	ROT_0, ROT_90, ROT_180, ROT_270
} rotation_t;

class Rotation
{
private:
	rotation_t rotation;
	IND_Entity2d * entity;
	int width;
	int height;

public:
	Rotation(IND_Entity2d * entity, int width, int height): width(width), entity(entity), rotation(ROT_0), height(height)
	{}

	~Rotation(void)
	{
	}

	void rotateLeft(){
		setRotation((rotation_t)((rotation-1)%ROT_270));
	}

	void rotateRight(){
		setRotation((rotation_t)((rotation+1)%ROT_270));
	}

	void doRotate(){
		int x,y;
		x = entity->GetPosX();
		y = entity->GetPosY();
		entity->SetAngleXYZ(0,0,entity->GetAngleZ()+90);
		switch(rotation){
			case ROT_0:
				entity->SetPosition(x+width,y,0);
				rotation = ROT_90;
				break;
			case ROT_90:
				entity->SetPosition(x,y+height,0);
				rotation = ROT_180;
				break;
			case ROT_180:
				entity->SetPosition(x-width,y,0);
				rotation = ROT_270;
				break;
			case ROT_270:
				entity->SetPosition(x,y-height,0);
				rotation = ROT_0;
				break;
		}
	}

	void setRotation(rotation_t r){
		int delta = rotation - r;
		if(delta<0){
			for(int i=0;i<(1-delta);i++){
				doRotate();
			}
		} else {
			for(int i=0;i<delta;i++){
				doRotate();
			}		
		}
	}

	rotation_t getRotation(){
		return rotation;
	}

};

#endif;