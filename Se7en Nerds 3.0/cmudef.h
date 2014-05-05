#ifndef CMUDEFENSE_H_IS_INCLUDED
#define CMUDEFENSE_H_IS_INCLUDED
#include <stdio.h>
#include "fssimplewindow.h"
#include "yspng.h"
#include <time.h>
#include <math.h>
class ASTAR;
class MONSTER; 
class TOWER;
class MISSILE;
class MAP;
class GAMECONTROL;
class ANIMATE;
#define _CRT_SECURE_NO_WARNINGS
#define PI 3.14159265759

enum {UNWALKABLE, WALKABLE, ISTOWER};
enum {NOACTION,BUSY};

class ANIMATE
{
	YsRawPngDecoder *Chicken;
	double ScreenX,ScreenY,count,ChickenType;
	int LocalTimer,FrameID,MaxID;

public:
	ANIMATE();
	void Set(int type);
	void JumpChickenJump(int GlobalTimer,int ScreenX,int ScreenY);
	
};

class ASTAR
{
public:
	ASTAR();
	~ASTAR();

	static const int mapWidth=20,mapHeight=15;// mapWidth=40,mapHeight=30
	static const int notfinished=0,notStarted=0;
	static const int found=1,nonexistent=2; 
	static const int tileSize=40; // static const int tileSize added on 11/19/2012; tilesize=20;
	//static const int walkable=1,unwalkable=0;
	int onClosedList;
	int pathLength,pathLocation,pathStatus,xPath,yPath,*pathBank;
	int ReadPathX(int pathLocation);
	int ReadPathY(int pathLocation);
	//-----------------------------------------------------------------------------
	// External Function Prototypes
	//-----------------------------------------------------------------------------
	void ReadPath(int currentX,int currentY, int pixelsPerFrame);
	int FindPath (int MonsterScreenX, int MonsterScreenY,int ExitX, int ExitY,
	const int walkability[mapWidth][mapHeight]);
	void CleanUp();
};

class MAP 
{
public:
	static const int mapWidth=20; // mapWidth=40
	static const int mapHeight=15; // mapHeight=30
	int mapGrid[mapWidth][mapHeight],level;
	YsRawPngDecoder grassfield,stonewall,exit;
	
	void LoadMap(int inputlevel);
	//void SaveMap(char* nameOfNewMap);
	int canBuildTower(const MONSTER monster[],const int TotNumMonster);
	void DrawMap(int ProjectionX,int ProjectionY,int ExitX,int ExitY);
};	
/*
class MAP 
{
public:
	static const int mapWidth=20; // mapWidth=40
	static const int mapHeight=15; // mapHeight=30
	int mapGrid[mapWidth][mapHeight],level;
	ASTAR finder;
	YsRawPngDecoder grassfield,stonewall,exit;
	
	MAP();
	~MAP();
	void LoadMap(int inputlevel);
	void Cleanup();
	void SaveMap(char* nameOfNewMap);
	bool ChangeMap(int x, int y, class MONSTER monster[]);
	void DrawMap(int ProjectionX,int ProjectionY,int ExitX,int ExitY);
};	
*/

class MONSTER
{
	int XLoc,YLoc;
public:
	int Speed,state,Type; 
	int Hp,HpMax; //Health Point
	int LootValue;
	static const int TileSize=80;
	static const int mapWid=20,mapHei=15;
	int ELocX,ELocY,StartX,StartY;
	int ID,WaveStartTime,TimeLag;
	int MLocX,MLocY;
	int ModMap[mapWid][mapHei];
	ASTAR pathfinder;
	ASTAR pathchecker;
	ANIMATE animate;


	MONSTER();
	~MONSTER();
	int GetX() const;
	int GetY() const;
	void Initi(int typeinput,int idinput,int wavetimeinput);
	int DrawMonster(int ProjectionX,int ProjectionY,long int GlobalTimer);
	void MoveMonster(MAP &map); 
	void GotHit(int DamagePoint);
	void DrawHealth(int ProjectionX,int ProjectionY);
	int Disappear(void);
	int MoneyBack(void);
	int PathBlockingCheck(int mx,int my,MAP &map);
};

class MISSILE
{
protected:
	double Position[2];
	int State;
	double Speed;
	int Target;
public:
	MISSILE();
	~MISSILE();
	int TargetID;
	void CleanUp();
	void Set(double ttowerX,double ttowerY,double speed,int state);
	void SetState(int state);
	const int GetState(void)const;
	double getX(void);
	double getY(void);
	void Move(const double MonsterX, const double MonsterY);
	void DrawMissile(int pngProjX,int pngProjY);
};

class TOWER
{
protected:
	int TowerPositionX,TowerPositionY;
public:
	int state,type,Cost,MaxNumMis,TargetID,Damage;
	static const int TileSize=80;
	double Range;
	MISSILE *missile;
	int missileReleaseTime;

	YsRawPngDecoder towerlogo;

	TOWER();
	~TOWER();
	const double xx(void);
	const double yy(void);

	void CleanUp(void);
	void SetType(int typeinput);
	void setLocation(int mx,int my);  
	void DrawTower(int pngProjX,int pngProjY
		,int mx,int my);
	int MonsterWithinHitRange(double monsterX,double monsterY); 
	void releaseMissile(int i);
};

class GAMECONTROL
{
public:
    double Color1,Color2,Color3;
	long int timer;
	int Lives,ProjectionX,ProjectionY;
	int TotMoney,Click;
	//related to winning or losing condition
	static const int TotNumMonster=100
		,TotNumTower1=20,TotNumTower2=15,TotNumTower3=10,TotNumTower4=5;
	int NumMonster,MaxNumTower;
	int DeadMonster;
	//int winnumber;
	int terminate;
	//int attackmonster;
	int NumTower[4];
	int key,lb,mb,rb,mx,my,MouseEvent,InsPtr;
	//Class Initialization
	MAP map;	
	MONSTER monster[TotNumMonster];
	TOWER *tower[4];
	YsRawPngDecoder background,loading,life,towermini[4],instruction[4];
	ANIMATE winthegame,losethegame;
	//Prototype of Functions
	GAMECONTROL();
	~GAMECONTROL();
	void CleanUp();
	void Initialize(void);
    int StartMenu(void);
	void ShowTime(void);
	void ShowMoney(void);
	int CheckTowerBuildBlock(int towertype);
	void TowerLockedCheck(void);
	void KeyMouseControl();
	int LoadEverthing();
	int CheckWin();
	int CheckLose();
	void DrawControlPanel();
	int RunGame();
	//int PathBlockingCheck();

	//Test
	//int MLocX,MLocY;
};

/*int GAMECONTROL::PathBlockingCheck()
{
	int XLoc=monster[0].StartX;
	int YLoc=monster[0].StartY;
	int ELocX=monster[0].ELocX;
	int ELocY=monster[0].ELocY;
	int TileSize=monster[0].TileSize;

	if(	MLocX!=(mx+ProjectionX)/TileSize
		&& MLocY!=(my+600-ProjectionY)/TileSize
		&& mx>0 && mx<800
		&& my>0 && my<600
		)
	{
		const int mapWid=20,mapHei=15;
		int ModMap[mapWid][mapHei];
		for(int i=0;i<mapWid;i++)
			for(int j=0;j<mapHei;j++)
				ModMap[i][j]=map.mapGrid[i][j];
		MLocX=(mx+ProjectionX)/TileSize;
		MLocY=(my+600-ProjectionY)/TileSize;
		ModMap[(mx+ProjectionX)][(my+600-ProjectionY)]=UNWALKABLE;
		ASTAR *pathchecker;
		pathchecker=new ASTAR;
	
		if (pathchecker->pathStatus == pathchecker->notStarted)
		{
			pathchecker->pathStatus = pathchecker->FindPath(XLoc,YLoc,ELocX,ELocY,ModMap);
		} 
		printf("Monster Type%d,PathStatus%d.\n",monster[0].Type,pathchecker->pathStatus==pathchecker->found);
		if (pathchecker->pathStatus != pathchecker->found) 
		{
			pathchecker->CleanUp();
			return 1;
		}
		else 
		{
			pathchecker->CleanUp();
			return 0;
		}
	}
	return 2;
}
*/

#endif