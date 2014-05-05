#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fssimplewindow.h"
#include "cmudef.h"
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS



MONSTER::MONSTER()
	:TimeLag(2000)
{	
	XLoc=0;	// MonsterScreenX
	YLoc=300; // MonsterScreenY
	state=0;
	ID=-1;
	ELocX=799; // ExitScreenX
	ELocY=380; // ExitScreenY
	Type=0;

	//MLocX=0;
	//MLocY=0;
}
MONSTER::~MONSTER()
{
}
int MONSTER::GetX() const
{
	return XLoc;
}
int MONSTER::GetY() const
{
	return YLoc;
}
void MONSTER::Initi(int typeinput,int idinput,int wavetimeinput)
{
	Type=typeinput;
	ID=idinput;
	WaveStartTime=wavetimeinput;
	if(Type==1)
	{
		animate.Set(1);
		Speed=1;
		HpMax=8;
		Hp=HpMax;
		LootValue=4;
		StartX=0;
		StartY=0;
	}
	else if (Type==2)
	{
		animate.Set(2);
		Speed=1;
		HpMax=20;
		Hp=HpMax;
		LootValue=5;
		StartX=0;
		StartY=0;
	}
	else if (Type==3)
	{
		animate.Set(3);
		Speed=2;
		HpMax=50;
		Hp=HpMax;
		LootValue=10;
		StartX=0;
		StartY=0;
	}
	else if (Type==4)
	{
		animate.Set(4);
		Speed=3;
		HpMax=80;
		Hp=HpMax;
		LootValue=15;
		StartX=0;
		StartY=0;
	}
	else if (Type==5)
	{
		animate.Set(1);
		Speed=3;
		HpMax=150;
		Hp=HpMax;
		LootValue=15;
		StartX=0;
		StartY=0;
	}
	XLoc=StartX;
	YLoc=StartY;
}
int MONSTER::DrawMonster(int pngProjX,int pngProjY,long int GlobalTimer)
{
	int ScreenX=2*XLoc-pngProjX,ScreenY=2*YLoc-600+pngProjY;
	//Check Starting Time
	int StateChange=0;
	//printf("Globaltimer:%d,StartTime=%d,Lag=%d,MonsterID=%d.\n",GlobalTimer,WaveStartTime,TimeLag,ID);
	if(GlobalTimer-WaveStartTime-TimeLag*ID>=0
		&& state==0
		&& Hp>0
		)
	{
		state=1;
		StateChange=1;
		//printf("Monster State=1, for ID=%d\n",ID);
	}
	if(state==1)
	{
		animate.JumpChickenJump(GlobalTimer,ScreenX,ScreenY);
	}
	return StateChange;
}
//This function need to be modiefied after the function of pathfinder change

void MONSTER::MoveMonster(MAP &map)
{
	if(state==1)
	{
		if (XLoc != ELocX || YLoc != ELocY) 
		{	
		if (pathfinder.pathStatus == pathfinder.notStarted || pathfinder.pathLocation == 2)
		{
			//Generate a new path. Enter coordinates of smiley sprite (xLoc(1)/
			//yLoc(1)) as the target.
			pathfinder.pathStatus = pathfinder.FindPath(XLoc,YLoc,ELocX,ELocY,map.mapGrid);
			//printf("pathStatus: %d\n",pathfinder.pathStatus);
		}
		} 

	//2.Move chaser.
		if (pathfinder.pathStatus == pathfinder.found) 
		{
			//printf("Monster found path.\n"); // remove this line
		//1.Read path information
			//pathfinder.ReadPath(XLoc,YLoc,Speed);
			pathfinder.ReadPath(XLoc,YLoc,Speed); //
		//2.Move sprite. xLoc/yLoc = current location of sprite. xPath and
		//	yPath = coordinates of next step on the path that were/are
		//	read using the readPath function.
			if (XLoc > pathfinder.xPath) XLoc = XLoc - Speed;
			if (XLoc < pathfinder.xPath) XLoc = XLoc + Speed;
			if (YLoc > pathfinder.yPath) YLoc = YLoc - Speed;		
			if (YLoc < pathfinder.yPath) YLoc = YLoc + Speed;
	
		//3.When sprite reaches the end location square	(end of its current
		//	path) ...		
			if (pathfinder.pathLocation == pathfinder.pathLength) 
			{
		//		Center the chaser in the square (not really necessary, but 
		//		it looks a little better for the chaser, which moves in 3 pixel
		//		increments and thus isn't always centered when it reaches its
		//		target).
				if (abs(XLoc - pathfinder.xPath) < Speed) XLoc = pathfinder.xPath;
				if (abs(YLoc - pathfinder.yPath) < Speed) YLoc = pathfinder.yPath;
			}
		}
	}
}
void MONSTER::GotHit(int DamagePoint)
{
	Hp=Hp-DamagePoint;
}
void MONSTER::DrawHealth(int pngProjX,int pngProjY)
{
	int ProjectionX=pngProjX,ProjectionY=600-pngProjY;
	if(state==1)
	{
		//Red rectangular for loss
		glColor3ub(255,0,0);
		glBegin(GL_QUADS);
		glVertex2i(2*XLoc-15-ProjectionX,2*YLoc-25-ProjectionY);
		glVertex2i(2*XLoc-15-ProjectionX,2*YLoc-25+5-ProjectionY);
		glVertex2i(2*XLoc+15-ProjectionX,2*YLoc-25+5-ProjectionY);
		glVertex2i(2*XLoc+15-ProjectionX,2*YLoc-25-ProjectionY);
		glEnd();

		// Green rectangular for remain
		glColor3ub(0,255,0);
		glBegin(GL_QUADS);
		glVertex2i(2*XLoc-15-ProjectionX,2*YLoc-25-ProjectionY);
		glVertex2i(2*XLoc-15-ProjectionX,2*YLoc-25+5-ProjectionY);
		double RelativeHp=(double)Hp/(double)HpMax;
		glVertex2i(2*XLoc-15+(int)30*RelativeHp-ProjectionX,2*YLoc-25+5-ProjectionY);
		glVertex2i(2*XLoc-15+(int)30*RelativeHp-ProjectionX,2*YLoc-25-ProjectionY);
		glEnd();
	}
}
int MONSTER::Disappear(void)
{
	if(Hp<=0
		&& state)
	{
		state=0;
		//StateOfMoney=0;
		return 0;
	}
	else if(Hp>0 
		&& XLoc+39>ELocX && XLoc-39<ELocX
		&& YLoc+39>ELocY && YLoc-39<ELocY
		&& state
		)
	{
		state=0;
		Hp=0;
		return 1;
	}
	else return 2;
}
int MONSTER::MoneyBack()
{
	if(Hp<=0)// && StateOfMoney==0)
		return LootValue;//if a monster die, earn $200
		//StateOfMoney=1;
	return 0;
	
}
int MONSTER::PathBlockingCheck(int mx,int my,MAP &map)
{
	if(mx>0 && mx<800
		&& my>0 && my<600
		)
	{
		for(int i=0;i<mapWid;i++)
			for(int j=0;j<mapHei;j++)
				ModMap[i][j]=map.mapGrid[i][j];
		MLocX=mx/TileSize;
		MLocY=my/TileSize;
		ModMap[MLocX][MLocY]=UNWALKABLE;
		//printf("i:%d,j:%d.\n",MLocX,MLocY);
		/*glBegin(GL_QUADS);
		glColor3ub(0,0,0);
		glVertex2i(MLocX*TileSize,MLocX*TileSize);
		glVertex2i(MLocX*TileSize+TileSize,MLocX*TileSize);
		glVertex2i(MLocX*TileSize+TileSize,MLocX*TileSize+TileSize);
		glVertex2i(MLocX*TileSize,MLocX*TileSize+TileSize);
		glEnd();
		*/
		if (pathchecker.pathStatus == pathchecker.notStarted)
		{
			pathchecker.pathStatus = pathchecker.FindPath(XLoc,YLoc,ELocX,ELocY,ModMap);
		} 
		printf("MonsterID%d,PathStatus%d.\n",ID,pathchecker.pathStatus==pathchecker.found);
		if (pathchecker.pathStatus != pathchecker.found) 
		{
			pathchecker.CleanUp();
			return 1;
		}
		else 
		{
			pathchecker.CleanUp();
			return 0;
		}
	}
	return 2;
}

ANIMATE::ANIMATE(void)
	:ScreenX(0),ScreenY(0)
	,LocalTimer(0),FrameID(0)
{
}
void ANIMATE::Set(int type)
{
	ChickenType=type;
	if(ChickenType==1)
	{
		MaxID=11;
		Chicken=new YsRawPngDecoder [MaxID+1];
		if(YSOK==Chicken[0].Decode("../Pic/1-0.png")
			&& YSOK==Chicken[1].Decode("../Pic/1-1.png")
			&& YSOK==Chicken[2].Decode("../Pic/1-2.png")
			&& YSOK==Chicken[3].Decode("../Pic/1-3.png")
			&& YSOK==Chicken[4].Decode("../Pic/1-4.png")
			&& YSOK==Chicken[5].Decode("../Pic/1-5.png")
			&& YSOK==Chicken[6].Decode("../Pic/1-6.png")
			&& YSOK==Chicken[7].Decode("../Pic/1-7.png")
			&& YSOK==Chicken[8].Decode("../Pic/1-8.png")
			&& YSOK==Chicken[9].Decode("../Pic/1-9.png")
			&& YSOK==Chicken[10].Decode("../Pic/1-10.png")
			&& YSOK==Chicken[11].Decode("../Pic/1-11.png"))
		{
				//printf("Type 1 Chicken Load Success.\n");
				for(int i=0;i<=MaxID;i++)
				{
					Chicken[i].Flip();
					for(int j=0;j<Chicken[i].wid;j++)
						for(int k=0;k<Chicken[i].hei;k++)
						{
							//If it's purple then make it transparent
							if(Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4]==255 
								&& Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4+1]==0 
								&& Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4+2]==255)
								Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4+3] = 0;//透明，设为 0
							else
								Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4+3] = 255;//不透明，设为 255
						}				
				}
		}
		else
			printf("Type 1 Chicken Load Error.");
	}
	else if(ChickenType==2)
	{
		MaxID=11;
		Chicken=new YsRawPngDecoder [MaxID+1];
		if(YSOK==Chicken[0].Decode("../Pic/2-0.png")
			&& YSOK==Chicken[1].Decode("../Pic/2-1.png")
			&& YSOK==Chicken[2].Decode("../Pic/2-2.png")
			&& YSOK==Chicken[3].Decode("../Pic/2-3.png")
			&& YSOK==Chicken[4].Decode("../Pic/2-4.png")
			&& YSOK==Chicken[5].Decode("../Pic/2-5.png")
			&& YSOK==Chicken[6].Decode("../Pic/2-6.png")
			&& YSOK==Chicken[7].Decode("../Pic/2-7.png")
			&& YSOK==Chicken[8].Decode("../Pic/2-8.png")
			&& YSOK==Chicken[9].Decode("../Pic/2-9.png")
			&& YSOK==Chicken[10].Decode("../Pic/2-10.png")
			&& YSOK==Chicken[11].Decode("../Pic/2-11.png"))
		{
				//printf("Type 2 Chicken Load Success.\n");
				for(int i=0;i<=MaxID;i++)
				{
					Chicken[i].Flip();
					for(int j=0;j<Chicken[i].wid;j++)
						for(int k=0;k<Chicken[i].hei;k++)
						{
							//如果是紫红色则设置为透明色
							if(Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4]==255 
								&& Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4+1]==0 
								&& Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4+2]==255)
								Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4+3] = 0;//透明，设为 0
							else
								Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4+3] = 255;//不透明，设为 255
						}				
				}
		}
		else
			printf("Type 2 Chicken Load Error.");
	}
	else if(ChickenType==3)
	{
		MaxID=9;
		Chicken=new YsRawPngDecoder [MaxID+1];
		if(YSOK==Chicken[0].Decode("../Pic/3-0.png")
			&& YSOK==Chicken[1].Decode("../Pic/3-1.png")
			&& YSOK==Chicken[2].Decode("../Pic/3-2.png")
			&& YSOK==Chicken[3].Decode("../Pic/3-3.png")
			&& YSOK==Chicken[4].Decode("../Pic/3-4.png")
			&& YSOK==Chicken[5].Decode("../Pic/3-5.png")
			&& YSOK==Chicken[6].Decode("../Pic/3-6.png")
			&& YSOK==Chicken[7].Decode("../Pic/3-7.png")
			&& YSOK==Chicken[8].Decode("../Pic/3-8.png")
			&& YSOK==Chicken[9].Decode("../Pic/3-9.png"))
		{
				//printf("Type 3 Chicken Load Success.\n");
				for(int i=0;i<=MaxID;i++)
				{
					Chicken[i].Flip();
					for(int j=0;j<Chicken[i].wid;j++)
						for(int k=0;k<Chicken[i].hei;k++)
						{
							//如果是紫红色则设置为透明色
							if(Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4]==255 
								&& Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4+1]==0 
								&& Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4+2]==255)
								Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4+3] = 0;//透明，设为 0
							else
								Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4+3] = 255;//不透明，设为 255
						}				
				}
		}
		else
			printf("Type 3 Chicken Load Error.");
	}
	else if(ChickenType==4)
	{
		MaxID=39;
		Chicken=new YsRawPngDecoder [MaxID+1];
		if(YSOK==Chicken[0].Decode("../Pic/4-0.png")
			&& YSOK==Chicken[1].Decode("../Pic/4-1.png")
			&& YSOK==Chicken[2].Decode("../Pic/4-2.png")
			&& YSOK==Chicken[3].Decode("../Pic/4-3.png")
			&& YSOK==Chicken[4].Decode("../Pic/4-4.png")
			&& YSOK==Chicken[5].Decode("../Pic/4-5.png")
			&& YSOK==Chicken[6].Decode("../Pic/4-6.png")
			&& YSOK==Chicken[7].Decode("../Pic/4-7.png")
			&& YSOK==Chicken[8].Decode("../Pic/4-8.png")
			&& YSOK==Chicken[9].Decode("../Pic/4-9.png")
			&& YSOK==Chicken[10].Decode("../Pic/4-10.png")
			&& YSOK==Chicken[11].Decode("../Pic/4-11.png")
			&& YSOK==Chicken[12].Decode("../Pic/4-12.png")
			&& YSOK==Chicken[13].Decode("../Pic/4-13.png")
			&& YSOK==Chicken[14].Decode("../Pic/4-14.png")
			&& YSOK==Chicken[15].Decode("../Pic/4-15.png")
			&& YSOK==Chicken[16].Decode("../Pic/4-16.png")
			&& YSOK==Chicken[17].Decode("../Pic/4-17.png")
			&& YSOK==Chicken[18].Decode("../Pic/4-18.png")
			&& YSOK==Chicken[19].Decode("../Pic/4-19.png")
			&& YSOK==Chicken[20].Decode("../Pic/4-20.png")
			&& YSOK==Chicken[21].Decode("../Pic/4-21.png")
			&& YSOK==Chicken[22].Decode("../Pic/4-22.png")
			&& YSOK==Chicken[23].Decode("../Pic/4-23.png")
			&& YSOK==Chicken[24].Decode("../Pic/4-24.png")
			&& YSOK==Chicken[25].Decode("../Pic/4-25.png")
			&& YSOK==Chicken[26].Decode("../Pic/4-26.png")
			&& YSOK==Chicken[27].Decode("../Pic/4-27.png")
			&& YSOK==Chicken[28].Decode("../Pic/4-28.png")
			&& YSOK==Chicken[29].Decode("../Pic/4-29.png")
			&& YSOK==Chicken[30].Decode("../Pic/4-30.png")
			&& YSOK==Chicken[31].Decode("../Pic/4-31.png")
			&& YSOK==Chicken[32].Decode("../Pic/4-32.png")
			&& YSOK==Chicken[33].Decode("../Pic/4-33.png")
			&& YSOK==Chicken[34].Decode("../Pic/4-34.png")
			&& YSOK==Chicken[35].Decode("../Pic/4-35.png")
			&& YSOK==Chicken[36].Decode("../Pic/4-36.png")
			&& YSOK==Chicken[37].Decode("../Pic/4-37.png")
			&& YSOK==Chicken[38].Decode("../Pic/4-38.png")
			&& YSOK==Chicken[39].Decode("../Pic/4-39.png"))
		{
				//printf("Type 4 Chicken Load Success.\n");
				for(int i=0;i<=MaxID;i++)
				{
					Chicken[i].Flip();
					for(int j=0;j<Chicken[i].wid;j++)
						for(int k=0;k<Chicken[i].hei;k++)
						{
							//如果是紫红色则设置为透明色
							if(Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4]==255 
								&& Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4+1]==0 
								&& Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4+2]==255)
								Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4+3] = 0;//透明，设为 0
							else
								Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4+3] = 255;//不透明，设为 255
						}				
				}
		}
		else
			printf("Type 4 Chicken Load Error.");
	}
	else if(ChickenType==5)
	{
		MaxID=7;
		Chicken=new YsRawPngDecoder [MaxID+1];
		if(YSOK==Chicken[0].Decode("../Pic/WinTheGame-1.png")
			&& YSOK==Chicken[1].Decode("../Pic/WinTheGame-2.png")
			&& YSOK==Chicken[2].Decode("../Pic/WinTheGame-3.png")
			&& YSOK==Chicken[3].Decode("../Pic/WinTheGame-4.png")
			&& YSOK==Chicken[4].Decode("../Pic/WinTheGame-5.png")
			&& YSOK==Chicken[5].Decode("../Pic/WinTheGame-6.png")
			&& YSOK==Chicken[6].Decode("../Pic/WinTheGame-7.png")
			&& YSOK==Chicken[7].Decode("../Pic/WinTheGame-8.png")
			)
		{
				//printf("Type 5 Chicken Load Success.\n");
				for(int i=0;i<=MaxID;i++)
				{
					Chicken[i].Flip();
					/*for(int j=0;j<Chicken[i].wid;j++)
						for(int k=0;k<Chicken[i].hei;k++)
						{
							//如果是紫红色则设置为透明色
							if(Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4]==255 
								&& Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4+1]==0 
								&& Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4+2]==255)
								Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4+3] = 0;//透明，设为 0
							else
								Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4+3] = 255;//不透明，设为 255
						}
						*/		
				}
		}
		else
			printf("Type 5 Chicken Load Error.");
	}
	else if(ChickenType==6)
	{
		MaxID=6;
		Chicken=new YsRawPngDecoder [MaxID+1];
		if(YSOK==Chicken[0].Decode("../Pic/LoseTheGame-1.png")
			&& YSOK==Chicken[1].Decode("../Pic/LoseTheGame-2.png")
			&& YSOK==Chicken[2].Decode("../Pic/LoseTheGame-3.png")
			&& YSOK==Chicken[3].Decode("../Pic/LoseTheGame-4.png")
			&& YSOK==Chicken[4].Decode("../Pic/LoseTheGame-5.png")
			&& YSOK==Chicken[5].Decode("../Pic/LoseTheGame-6.png")
			&& YSOK==Chicken[6].Decode("../Pic/LoseTheGame-7.png")
			)
		{
				//printf("Type 6 Chicken Load Success.\n");
				for(int i=0;i<=MaxID;i++)
				{
					Chicken[i].Flip();
					/*for(int j=0;j<Chicken[i].wid;j++)
						for(int k=0;k<Chicken[i].hei;k++)
						{
							//如果是紫红色则设置为透明色
							if(Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4]==255 
								&& Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4+1]==0 
								&& Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4+2]==255)
								Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4+3] = 0;//透明，设为 0
							else
								Chicken[i].rgba[((Chicken[i].hei-1-k)*Chicken[i].wid+j)*4+3] = 255;//不透明，设为 255
						}
						*/		
				}
		}
		else
			printf("Type 6 Chicken Load Error.");
	}
}
void ANIMATE::JumpChickenJump(int GlobalTimer,int ScreenX,int ScreenY)
{
	if(GlobalTimer-LocalTimer>100)
	{
		if(FrameID==MaxID)
			FrameID=0;
		else
			FrameID++;
		LocalTimer=GlobalTimer;
	}
	
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	int winWid,winHei;
    FsGetWindowSize(winWid,winHei);
    glViewport(0,0,winWid,winHei);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,(float)winWid-1,(float)winHei-1,0,-1,1);
	glRasterPos2d(ScreenX-40,ScreenY-40+(double)(Chicken[FrameID].hei-1));
	glDrawPixels(Chicken[FrameID].wid,Chicken[FrameID].hei,GL_RGBA,GL_UNSIGNED_BYTE,Chicken[FrameID].rgba);
	glDisable(GL_BLEND);
}


/*
int main()
{
	MONSTER monster();
	
	
	printf("aaaa");
	Map map;
	FsOpenWindow(16,16,800,600,1);
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		
		glColor3ub(0,255,0);
		glBegin(GL_QUADS);
		for (int i=0; i<40; i++)
		{
			for (int j=0; j<30; j++)
			{
				glVertex2i(map.mapGrid[i][j]*20,map.mapGrid[i][j]*20+20);
				//glVertex2i(XLoc-10,YLoc-15+5);
				//glVertex2i(XLoc+10*Blood,YLoc+5);
				//glVertex2i(XLoc+10*Blood,YLoc-5);
			}
		}
		glEnd();
	//map.

	monster.DrawMonster();
	//monster.MoveMonster(map);
	return 0;
}
*/
/*
bool MONSTER:: checkPath() 
{
	pathfinder.FindPath(XLoc,YLoc,ELocX,ELocY,map.mapGrid[80][60]);
}
*/