#include "cmudef.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fssimplewindow.h"
#include <string.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

MISSILE::MISSILE()
	:Speed(0),Target(0)
{
	CleanUp();
}
MISSILE::~MISSILE()
{
	CleanUp();
}
void MISSILE::CleanUp()
{
	Position[0]=0;Position[1]=0;State=0;
}
void MISSILE::Set(double ttowerX,double ttowerY,double speed,int state)
{
	CleanUp();
	Position[0]=ttowerX;
	Position[1]=ttowerY;
	Speed=speed;
	State=state;
}
const int MISSILE::GetState()const
{
	return State;
}
double MISSILE::getX(void)
{
	return Position[0];
}
double MISSILE::getY(void)
{
	return Position[1];
}
void MISSILE::Move(const double MonsterX, const double MonsterY)
{
	if(State==1)
	{
		double relativePosition[2];
		relativePosition[0] = MonsterX-Position[0];
		relativePosition[1] = MonsterY-Position[1];
		Position[0] += Speed*(relativePosition[0]/sqrt(relativePosition[0]*relativePosition[0]+relativePosition[1]*relativePosition[1]));
		Position[1] += Speed*(relativePosition[1]/sqrt(relativePosition[0]*relativePosition[0]+relativePosition[1]*relativePosition[1]));
	}
}
void MISSILE::DrawMissile(int pngProjX,int pngProjY)
{
	int ProjectionX=pngProjX,ProjectionY=600-pngProjY;
	glColor3d(0,0,0);
	glBegin(GL_QUADS);
	glVertex2i(2*Position[0]-ProjectionX-5,2*Position[1]-ProjectionY-5);
	glVertex2i(2*Position[0]-ProjectionX+5,2*Position[1]-ProjectionY-5);
	glVertex2i(2*Position[0]-ProjectionX+5,2*Position[1]-ProjectionY+5);
	glVertex2i(2*Position[0]-ProjectionX-5,2*Position[1]-ProjectionY+5);
	glEnd();
}

TOWER::TOWER()
	:MaxNumMis(5)
	,state(0),TowerPositionX(0),TowerPositionY(0)
	,missileReleaseTime(0),TargetID(-1)
	//,BlockingMonster(0)
{

}
TOWER::~TOWER()
{
	delete [] missile;
	CleanUp();
}
void TOWER::SetType(int typeinput)
{
	type=typeinput;
	if(type==1)
	{
		missile=new MISSILE [MaxNumMis];
		Range=100;
		Damage=2;
		Cost=10;
		if(YSOK==towerlogo.Decode("../Pic/tower1.png"))
		{
			towerlogo.Flip();
			for(int j=0;j<towerlogo.wid;j++)
				for(int k=0;k<towerlogo.hei;k++)
				{
					//If it's purple then make it transparent
					if(towerlogo.rgba[((towerlogo.hei-1-k)*towerlogo.wid+j)*4]==255 
						&& towerlogo.rgba[((towerlogo.hei-1-k)*towerlogo.wid+j)*4+1]==0 
						&& towerlogo.rgba[((towerlogo.hei-1-k)*towerlogo.wid+j)*4+2]==255)
						towerlogo.rgba[((towerlogo.hei-1-k)*towerlogo.wid+j)*4+3] = 0;//透明，设为 0
					else
						towerlogo.rgba[((towerlogo.hei-1-k)*towerlogo.wid+j)*4+3] = 255;//不透明，设为 255
				}
		}
		else
			printf("Read Tower Picture Error.\n");
	}
	else if(type==2)
	{
		missile=new MISSILE [MaxNumMis];
		Range=150;
		Damage=5;
		Cost=30;
		if(YSOK==towerlogo.Decode("../Pic/tower2.png"))
		{
			towerlogo.Flip();
			for(int j=0;j<towerlogo.wid;j++)
				for(int k=0;k<towerlogo.hei;k++)
				{
					//If it's purple then make it transparent
					if(towerlogo.rgba[((towerlogo.hei-1-k)*towerlogo.wid+j)*4]==255 
						&& towerlogo.rgba[((towerlogo.hei-1-k)*towerlogo.wid+j)*4+1]==0 
						&& towerlogo.rgba[((towerlogo.hei-1-k)*towerlogo.wid+j)*4+2]==255)
						towerlogo.rgba[((towerlogo.hei-1-k)*towerlogo.wid+j)*4+3] = 0;//透明，设为 0
					else
						towerlogo.rgba[((towerlogo.hei-1-k)*towerlogo.wid+j)*4+3] = 255;//不透明，设为 255
				}
		}
		else
			printf("Read Tower Picture Error.\n");
	}
	else if(type==3)
	{
		missile=new MISSILE [MaxNumMis];
		Range=200;
		Damage=10;
		Cost=70;
		if(YSOK==towerlogo.Decode("../Pic/tower3.png"))
		{
			towerlogo.Flip();
			for(int j=0;j<towerlogo.wid;j++)
				for(int k=0;k<towerlogo.hei;k++)
				{
					//If it's purple then make it transparent
					if(towerlogo.rgba[((towerlogo.hei-1-k)*towerlogo.wid+j)*4]==255 
						&& towerlogo.rgba[((towerlogo.hei-1-k)*towerlogo.wid+j)*4+1]==0 
						&& towerlogo.rgba[((towerlogo.hei-1-k)*towerlogo.wid+j)*4+2]==255)
						towerlogo.rgba[((towerlogo.hei-1-k)*towerlogo.wid+j)*4+3] = 0;//透明，设为 0
					else
						towerlogo.rgba[((towerlogo.hei-1-k)*towerlogo.wid+j)*4+3] = 255;//不透明，设为 255
				}
		}
		else
			printf("Read Tower Picture Error.\n");
	}
	else if(type==4)
	{
		missile=new MISSILE [MaxNumMis];
		Range=180;
		Damage=15;
		Cost=120;
		if(YSOK==towerlogo.Decode("../Pic/tower4.png"))
		{
			towerlogo.Flip();
			for(int j=0;j<towerlogo.wid;j++)
				for(int k=0;k<towerlogo.hei;k++)
				{
					//If it's purple then make it transparent
					if(towerlogo.rgba[((towerlogo.hei-1-k)*towerlogo.wid+j)*4]==255 
						&& towerlogo.rgba[((towerlogo.hei-1-k)*towerlogo.wid+j)*4+1]==0 
						&& towerlogo.rgba[((towerlogo.hei-1-k)*towerlogo.wid+j)*4+2]==255)
						towerlogo.rgba[((towerlogo.hei-1-k)*towerlogo.wid+j)*4+3] = 0;//透明，设为 0
					else
						towerlogo.rgba[((towerlogo.hei-1-k)*towerlogo.wid+j)*4+3] = 255;//不透明，设为 255
				}
		}
		else
			printf("Read Tower Picture Error.\n");
	}
}
void TOWER::CleanUp()
{
	TowerPositionX=0;
	TowerPositionY=0;
	state=0;
}
void TOWER::setLocation(int mx,int my)
{
	TowerPositionX=mx;
	TowerPositionY=my;
	//printf("TowerX:%d,TowerY:%d\n",TowerPositionX,TowerPositionY);
}
void TOWER::DrawTower(int pngProjX,int pngProjY,int mx,int my)
{
	int ProjectionX=pngProjX,ProjectionY=600-pngProjY;
	//printf("Tower State=%d.\n",state);
	if(state==-1
		&& mx>0 && mx<800
		&& my>0 && my<600
		)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glColor4ub(0,0,0,50);
		glBegin(GL_QUADS);
		mx+=ProjectionX;
		my+=ProjectionY;
		//printf("Draw Tower Called");
		//printf("Mouse Movement captured within DrawTower Fuction,\nMouseX:%d,MouseY:%d.\n",mx,my);
		glVertex2i((mx/TileSize)*TileSize-ProjectionX,(my/TileSize)*TileSize-ProjectionY);
		glVertex2i((mx/TileSize)*TileSize+TileSize-ProjectionX,(my/TileSize)*TileSize-ProjectionY);
		glVertex2i((mx/TileSize)*TileSize+TileSize-ProjectionX,(my/TileSize)*TileSize+TileSize-ProjectionY);
		glVertex2i((mx/TileSize)*TileSize-ProjectionX,(my/TileSize)*TileSize+TileSize-ProjectionY);
		glEnd();
		
		double rad=Range;
		glColor3ub(255,0,0);
		glBegin(GL_LINES);
		for(int j=0; j<64; j++)
		{
			double angle=(double)j*PI/32.0;
			double x=mx+cos(angle)*rad-ProjectionX;
			double y=my+sin(angle)*rad-ProjectionY;
			glVertex2d(x,y);
		}
		glEnd();
		glDisable(GL_BLEND);

	}
	else if(state)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		int winWid,winHei;
		FsGetWindowSize(winWid,winHei);
		glViewport(0,0,winWid,winHei);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,(float)winWid-1,(float)winHei-1,0,-1,1);
		//printf("TowerPosition:%d %d.\n",TowerPositionX,TowerPositionY);
		glRasterPos2d((TowerPositionX*2/(TileSize))*(TileSize)-ProjectionX,(TowerPositionY*2/(TileSize))*(TileSize)-ProjectionY+(double)(towerlogo.hei-1));
		glDrawPixels(towerlogo.wid,towerlogo.hei,GL_RGBA,GL_UNSIGNED_BYTE,towerlogo.rgba);
		glDisable(GL_BLEND);
		/*
		glColor3ub(0,0,255);
		glBegin(GL_QUADS);
		glVertex2i((TowerPositionX/TileSize)*TileSize-ProjectionX,(TowerPositionY/TileSize)*TileSize-ProjectionY);
		glVertex2i((TowerPositionX/TileSize)*TileSize+TileSize-ProjectionX,(TowerPositionY/TileSize)*TileSize-ProjectionY);
		glVertex2i((TowerPositionX/TileSize)*TileSize+TileSize-ProjectionX,(TowerPositionY/TileSize)*TileSize+TileSize-ProjectionY);
		glVertex2i((TowerPositionX/TileSize)*TileSize-ProjectionX,(TowerPositionY/TileSize)*TileSize+TileSize-ProjectionY);
		glEnd();*/
	}
}
int TOWER::MonsterWithinHitRange(double monsterX,double monsterY)
{
	double judge=(monsterX-TowerPositionX)*(monsterX-TowerPositionX)+(monsterY-TowerPositionY)*(monsterY-TowerPositionY);
	if(judge<=Range*Range)
	{
		return 1;
	}
	return 0;
}
void TOWER::releaseMissile(int i)
{
	//Set missilestate to 1.& Set missile's original location as (x,y)，i.e, the tower's location.
	missile[i].Set(TowerPositionX,TowerPositionY,7,1);   
    
}


const double TOWER::xx(void)
{
	return TowerPositionX;
}
const double TOWER::yy(void)
{
	return TowerPositionY;
}