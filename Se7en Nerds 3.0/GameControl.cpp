#include "cmudef.h"
#include <stdio.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yspng.h"

GAMECONTROL::GAMECONTROL()
	:timer(0),Lives(20),ProjectionX(0),ProjectionY(600)
	,key(0),TotMoney(30),NumMonster(0)
	,MouseEvent(0),Click(NOACTION),InsPtr(0)
{
    Color1=1.0;
    Color2=1.0;
    Color3=1.0;
	//NumTower=0;
	MaxNumTower=TotNumTower1+TotNumTower2+TotNumTower3+TotNumTower4;
	NumTower[0]=0;
	NumTower[1]=0;
	NumTower[2]=0;
	NumTower[3]=0;
	terminate=0;
	//related to ending condition
	DeadMonster=0;
	//winnumber=5;
	//attackmonster=0;
	if(YSOK==loading.Decode("../Pic/Loading.png")
		&& YSOK==instruction[0].Decode("../Pic/Instruction1.png")
		&& YSOK==instruction[1].Decode("../Pic/Instruction2.png")
		&& YSOK==instruction[2].Decode("../Pic/Instruction3.png")
		&& YSOK==instruction[3].Decode("../Pic/Instruction4.png")
		)
	{
		loading.Flip();
		instruction[0].Flip();
		instruction[1].Flip();
		instruction[2].Flip();
		instruction[3].Flip();
	}
	else
	{
		printf("Read Loading Picture Error.\n");
	}

	tower[0]=new TOWER [TotNumTower1];
	tower[1]=new TOWER [TotNumTower2];
	tower[2]=new TOWER [TotNumTower3];
	tower[3]=new TOWER [TotNumTower4];


	//MLocX=0;
	//MLocY=0;
}
GAMECONTROL::~GAMECONTROL()
{

}
void GAMECONTROL::CleanUp()
{
	NumTower[0]=0;
	NumTower[1]=0;
	NumTower[2]=0;
	NumTower[3]=0;
	delete [] tower[0];
	delete [] tower[1];
	delete [] tower[2];
	delete [] tower[3];
}
int GAMECONTROL::LoadEverthing()
{
	//-----------------------------------
	FsPollDevice();
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	int winWid,winHei;
    FsGetWindowSize(winWid,winHei);
    glViewport(0,0,winWid,winHei);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,(float)winWid-1,(float)winHei-1,0,-1,1);
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    glRasterPos2d(0.0,(double)(loading.hei-1));
	glDrawPixels(loading.wid,loading.hei,GL_RGBA,GL_UNSIGNED_BYTE,loading.rgba);
	FsSwapBuffers();
	//-----------------------------------
	
	map.LoadMap(1);
	//Initialize monsters
	for(int i=0;i<10;i++)
		monster[i].Initi(1,i,3000);
	
	//-----------------------------------
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	//int winWid,winHei;
    FsGetWindowSize(winWid,winHei);
    glViewport(0,0,winWid,winHei);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,(float)winWid-1,(float)winHei-1,0,-1,1);
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    glRasterPos2d(0.0,(double)(loading.hei-1));
	glDrawPixels(loading.wid,loading.hei,GL_RGBA,GL_UNSIGNED_BYTE,loading.rgba);
    glColor3ub(195,195,195);
	glBegin(GL_QUADS);
	glVertex2i(421,300);
	glVertex2i(421,400);
	glVertex2i(700,400);
	glVertex2i(700,300);
	glEnd();
	FsSwapBuffers();
	//-----------------------------------

	for(int i=10;i<30;i++)
		monster[i].Initi(2,i,3000);

	//-----------------------------------
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	//int winWid,winHei;
    FsGetWindowSize(winWid,winHei);
    glViewport(0,0,winWid,winHei);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,(float)winWid-1,(float)winHei-1,0,-1,1);
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    glRasterPos2d(0.0,(double)(loading.hei-1));
	glDrawPixels(loading.wid,loading.hei,GL_RGBA,GL_UNSIGNED_BYTE,loading.rgba);
    glColor3ub(195,195,195);
	glBegin(GL_QUADS);
	glVertex2i(455,300);
	glVertex2i(455,400);
	glVertex2i(700,400);
	glVertex2i(700,300);
	glEnd();
	FsSwapBuffers();
	//-----------------------------------

	for(int i=30;i<50;i++)
		monster[i].Initi(3,i,3000);

	//-----------------------------------
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	//int winWid,winHei;
    FsGetWindowSize(winWid,winHei);
    glViewport(0,0,winWid,winHei);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,(float)winWid-1,(float)winHei-1,0,-1,1);
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    glRasterPos2d(0.0,(double)(loading.hei-1));
	glDrawPixels(loading.wid,loading.hei,GL_RGBA,GL_UNSIGNED_BYTE,loading.rgba);
    glColor3ub(195,195,195);
	glBegin(GL_QUADS);
	glVertex2i(487,300);
	glVertex2i(487,400);
	glVertex2i(700,400);
	glVertex2i(700,300);
	glEnd();
	FsSwapBuffers();


	for(int i=50;i<80;i++)
		monster[i].Initi(4,i,3000);

	//-----------------------------------
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	//int winWid,winHei;
    FsGetWindowSize(winWid,winHei);
    glViewport(0,0,winWid,winHei);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,(float)winWid-1,(float)winHei-1,0,-1,1);
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    glRasterPos2d(0.0,(double)(loading.hei-1));
	glDrawPixels(loading.wid,loading.hei,GL_RGBA,GL_UNSIGNED_BYTE,loading.rgba);
	FsSwapBuffers();
	//-----------------------------------
	for(int i=80;i<100;i++)
		monster[i].Initi(5,i,3000);

	// set an array of Tower with 5 elements. One can only build 5 towers in the window.The number can be changed.
	for(int i=0;i<TotNumTower1;i++)
		tower[0][i].SetType(1);
	for(int i=0;i<TotNumTower2;i++)
		tower[1][i].SetType(2);
	for(int i=0;i<TotNumTower3;i++)
		tower[2][i].SetType(3);
	for(int i=0;i<TotNumTower4;i++)
		tower[3][i].SetType(4);
	if(YSOK==towermini[0].Decode("../Pic/tower1mini.png")
		&& YSOK==towermini[1].Decode("../Pic/tower2mini.png")
		&& YSOK==towermini[2].Decode("../Pic/tower3mini.png")
		&& YSOK==towermini[3].Decode("../Pic/tower4mini.png")
		&& YSOK==life.Decode("../Pic/liveleft.png")
		)
		{
			for(int i=0;i<4;i++)
			{
				towermini[i].Flip();
				for(int j=0;j<towermini[i].wid;j++)
				for(int k=0;k<towermini[i].hei;k++)
				{
					//If it's purple then make it transparent
					if(towermini[i].rgba[((towermini[i].hei-1-k)*towermini[i].wid+j)*4]==255 
						&& towermini[i].rgba[((towermini[i].hei-1-k)*towermini[i].wid+j)*4+1]==0 
						&& towermini[i].rgba[((towermini[i].hei-1-k)*towermini[i].wid+j)*4+2]==255)
						towermini[i].rgba[((towermini[i].hei-1-k)*towermini[i].wid+j)*4+3] = 0;//透明，设为 0
					else
						towermini[i].rgba[((towermini[i].hei-1-k)*towermini[i].wid+j)*4+3] = 255;//不透明，设为 255
				}
			}
			life.Flip();
			for(int i=0;i<life.wid;i++)
				for(int j=0;j<life.hei;j++)
				{
					if(life.rgba[((life.hei-1-j)*life.wid+i)*4]==255 
						&& life.rgba[((life.hei-1-j)*life.wid+i)*4+1]==0 
						&& life.rgba[((life.hei-1-j)*life.wid+i)*4+2]==255)
						life.rgba[((life.hei-1-j)*life.wid+i)*4+3] = 0;//透明，设为 0
					else
						life.rgba[((life.hei-1-j)*life.wid+i)*4+3] = 255;//不透明，设为 255
				}
		}
		else
			printf("Read Mini Tower Logo,and Live logo Picture Error.\n");
	winthegame.Set(6);
	losethegame.Set(5);



	return 1;
}
int GAMECONTROL::StartMenu(void)
{
    FsPollDevice();
	if(YSOK==background.Decode("../Pic/StartMenuBackground.png"))
	{
		background.Flip();
		//printf("Read Background Picture Successful.\n");
	}
	else
	{
		printf("Read Start Menu Background Error.\n");
		return 2;
	}
    while(1)
    {
        FsPollDevice();
        int winWid,winHei;
        FsGetWindowSize(winWid,winHei);
        glViewport(0,0,winWid,winHei);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0,(float)winWid-1,(float)winHei-1,0,-1,1);
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        glRasterPos2d(0.0,(double)(background.hei-1));
		glDrawPixels(background.wid,background.hei,GL_RGBA,GL_UNSIGNED_BYTE,background.rgba);
        
		glColor3d(1.0, 0.0, 0.0);
        glRasterPos2d(250, 100);
        YsGlDrawFontBitmap20x32("CMU DEFENCE");
        glColor3d(Color1, 1.0, 0.0);
        glRasterPos2d(250, 250);
        YsGlDrawFontBitmap16x24("PLAY");
        glColor3d(Color2, 1.0, 0.0);
        glRasterPos2d(250, 300);
        YsGlDrawFontBitmap16x24("HOW TO PLAY");
        glColor3d(Color3, 1.0, 0.0);
        glRasterPos2d(250, 350);
        YsGlDrawFontBitmap16x24("QUIT");
        
		int lb,mb,rb,mx,my;
        FsGetMouseEvent(lb, mb, rb, mx, my);
        if(mx>250 && mx<314 && my<250 && my>226)
        {
            Color1=0.0;
            glColor3d(1.0, 0.0, 1.0);
            glRasterPos2d(450, 250);
            YsGlDrawFontBitmap12x16("Click Left Button to Begin");
            if(lb==1)
            {
                return 1;
            }
        }
        else if(Color1!=1.0)
        {
            Color1=1.0;
        }
        
		if(mx>250 && mx<410 && my<300 && my>276)
        {
            Color2=0.0;
            glColor3d(1.0, 0.0, 1.0);
            glRasterPos2d(450, 300);
            YsGlDrawFontBitmap12x16("Build Selected Towers to");
            glRasterPos2d(450, 332);
            YsGlDrawFontBitmap12x16("Protect CMU from Monosters");
			if(lb==1)
				return 3;
        }
        else if(Color2!=1.0)
        {
            Color2=1.0;
        }
        
		if(mx>250 && mx<314 && my<350 && my>326)
        {
            Color3=0.0;
            glColor3d(1.0, 0.0, 1.0);
            glRasterPos2d(450, 350);
            YsGlDrawFontBitmap12x16("Click Left Button to Quit");
            if(lb==1)
            {
                return 2;
            }
        }
        else if(Color3!=1.0)
        {
            Color3=1.0;
        }
        
		FsSwapBuffers();
        FsSleep(25);
    }
	return 2;
}
void GAMECONTROL::ShowTime(void)
{
	char chartime[5];

	chartime[0]=48+(timer/600000%10);
	chartime[1]=48+(timer/60000%10);
	chartime[2]=':';
	chartime[3]=48+(timer/10000%6);
	chartime[4]=48+(timer/1000%10);
	
	glEnable(GL_BLEND);    
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glColor4ub(255,255,255,100);
	glBegin(GL_QUADS);
	glVertex2i(712,490-26);
	glVertex2i(712+16*5,490-26);
	glVertex2i(712+16*5,490);
	glVertex2i(712,490);
	glEnd();
	glDisable(GL_BLEND);

	glColor3ub(0,0,0);
	glRasterPos2d(712,490);
	YsGlDrawFontBitmap16x24(chartime);
}
void GAMECONTROL::ShowMoney(void)
{
	char charmoney[5];

	if(TotMoney>=10000)
	{
		glEnable(GL_BLEND);    
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glColor4ub(255,255,255,100);
		glBegin(GL_QUADS);
		glVertex2i(596,490-26);
		glVertex2i(596+20+16+16+16+16+16,490-26);
		glVertex2i(596+20+16+16+16+16+16,490);
		glVertex2i(596,490);
		glEnd();
		glDisable(GL_BLEND);
		charmoney[0]=48+(TotMoney/10000);
		charmoney[1]=48+(TotMoney/1000%10);
		charmoney[2]=48+((TotMoney/100)%10);
		charmoney[3]=48+((TotMoney/10)%10);
		charmoney[4]=48+(TotMoney%10);
		glColor3ub(0,0,0);
		glRasterPos2d(616,490);
		YsGlDrawFontBitmap16x24(charmoney);
		glColor3ub(0,0,0);
		glRasterPos2d(596,490);
		YsGlDrawFontBitmap16x24("$");
	}
	else if(TotMoney>=1000 && TotMoney<10000)
	{
		glEnable(GL_BLEND);    
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glColor4ub(255,255,255,100);
		glBegin(GL_QUADS);
		glVertex2i(612,490-26);
		glVertex2i(612+20+16+16+16+16,490-26);
		glVertex2i(612+20+16+16+16+16,490);
		glVertex2i(612,490);
		glEnd();
		glDisable(GL_BLEND);
		charmoney[0]=48+(TotMoney/1000);
		charmoney[1]=48+((TotMoney/100)%10);
		charmoney[2]=48+((TotMoney/10)%10);
		charmoney[3]=48+(TotMoney%10);
		glColor3ub(0,0,0);
		glRasterPos2d(632,490);
		YsGlDrawFontBitmap16x24(charmoney);
		glColor3ub(0,0,0);
		glRasterPos2d(612,490);
		YsGlDrawFontBitmap16x24("$");
	}
	else if(TotMoney>=100 && TotMoney<1000 )
	{
		glEnable(GL_BLEND);    
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glColor4ub(255,255,255,100);
		glBegin(GL_QUADS);
		glVertex2i(628,490-26);
		glVertex2i(628+20+16+16+16,490-26);
		glVertex2i(628+20+16+16+16,490);
		glVertex2i(628,490);
		glEnd();
		glDisable(GL_BLEND);
		charmoney[0]=48+((TotMoney/100)%10);
		charmoney[1]=48+((TotMoney/10)%10);
		charmoney[2]=48+(TotMoney%10);
		glColor3ub(0,0,0);
		glRasterPos2d(648,490);
		YsGlDrawFontBitmap16x24(charmoney);
		glColor3ub(0,0,0);
		glRasterPos2d(628,490);
		YsGlDrawFontBitmap16x24("$");
	}
	else if(TotMoney>=10 && TotMoney<100 )
	{
		glEnable(GL_BLEND);    
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glColor4ub(255,255,255,100);
		glBegin(GL_QUADS);
		glVertex2i(644,490-26);
		glVertex2i(644+20+16+16,490-26);
		glVertex2i(644+20+16+16,490);
		glVertex2i(644,490);
		glEnd();
		glDisable(GL_BLEND);
		charmoney[0]=48+((TotMoney/10)%10);
		charmoney[1]=48+(TotMoney%10);
		glColor3ub(0,0,0);
		glRasterPos2d(664,490);
		YsGlDrawFontBitmap16x24(charmoney);
		glColor3ub(0,0,0);
		glRasterPos2d(644,490);
		YsGlDrawFontBitmap16x24("$");
	}
	else if(TotMoney>0 && TotMoney<10 )
	{
		glEnable(GL_BLEND);    
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glColor4ub(255,255,255,100);
		glBegin(GL_QUADS);
		glVertex2i(660,490-26);
		glVertex2i(660+20+16,490-26);
		glVertex2i(660+20+16,490);
		glVertex2i(660,490);
		glEnd();
		glDisable(GL_BLEND);
		charmoney[0]=48+(TotMoney%10);
		glColor3ub(0,0,0);
		glRasterPos2d(680,490);
		YsGlDrawFontBitmap16x24(charmoney);
		glColor3ub(0,0,0);
		glRasterPos2d(660,490);
		YsGlDrawFontBitmap16x24("$");
	}
	else 
	{
		glEnable(GL_BLEND);    
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glColor4ub(255,255,255,100);
		glBegin(GL_QUADS);
		glVertex2i(660,490-26);
		glVertex2i(660+20+16,490-26);
		glVertex2i(660+20+16,490);
		glVertex2i(660,490);
		glEnd();
		glDisable(GL_BLEND);
		charmoney[0]=48;
		glColor3ub(0,0,0);
		glRasterPos2d(680,490);
		YsGlDrawFontBitmap16x24(charmoney);
		glColor3ub(0,0,0);
		glRasterPos2d(660,490);
		YsGlDrawFontBitmap16x24("$");	



	}

	
	

}
void GAMECONTROL::TowerLockedCheck(void)   //Tower Locked on a target check
{
	for(int towertype=0;towertype<4;towertype++)
	{
		if(NumTower[towertype]!=0)
			for(int j=0;j<NumTower[towertype];j++)
			{
				//Tower locked on target
				if(tower[towertype][j].TargetID!=-1)
				{
					for(int i=0;i<tower[towertype][j].MaxNumMis;i++)
					{
						if((tower[towertype][j].missile[i].GetState()==0)
						&& (timer-tower[towertype][j].missileReleaseTime)>700
						&& (monster[tower[towertype][j].TargetID].state==1))
						{	
							tower[towertype][j].missile[i].TargetID = tower[towertype][j].TargetID;
							tower[towertype][j].releaseMissile(i);
							//printf("missile release successfully %d\n", i);
							tower[towertype][j].missileReleaseTime=timer;											
						}
					}

					//Check run out of range
					if (monster[tower[towertype][j].TargetID].GetX()<tower[towertype][j].xx()-tower[towertype][j].Range 
						|| monster[tower[towertype][j].TargetID].GetX()>tower[towertype][j].xx()+tower[towertype][j].Range
						|| monster[tower[towertype][j].TargetID].GetY()<tower[towertype][j].yy()-tower[towertype][j].Range
						|| monster[tower[towertype][j].TargetID].GetY()>tower[towertype][j].yy()+tower[towertype][j].Range
						|| monster[tower[towertype][j].TargetID].state==0)
					{
						//printf("byebye\n");
						tower[towertype][j].TargetID=-1;
						//for(int i=0; i<5; i++)
						//{
						//	tower[towertype][j].missile[i].CleanUp();
						//}
					}
				}
				

				//Tower searching for target
				else if(tower[towertype][j].TargetID==-1)
				{
					for(int k=0;k<NumMonster;k++)
					{							
						if(0!=tower[towertype][j].MonsterWithinHitRange(monster[k].GetX(),monster[k].GetY()) 
							&& monster[k].state!=0
							&& tower[towertype][j].TargetID==-1
							)
						{
							tower[towertype][j].TargetID=monster[k].ID;
						}
					}		
				}
			}
	}
}
int GAMECONTROL::CheckTowerBuildBlock(int towertype)
{
	//Building Location Check
	for(int k=0;k<NumMonster;k++)
	{
		if(monster[k].state==1
			&& monster[k].MLocX!=(mx+ProjectionX)/monster[k].TileSize
			&& monster[k].MLocY!=(my+600-ProjectionY)/monster[k].TileSize)
		{
			if(0==monster[k].PathBlockingCheck(mx+ProjectionX,my+600-ProjectionY,map))
				return 1;
		}
	}
	return 0;
}
int GAMECONTROL::CheckWin()
{
	if (Lives>0 && DeadMonster==TotNumMonster)
	{
		terminate=2;
		return 1;
	}
	else
	{
		return 0;
	}
}
int GAMECONTROL::CheckLose()
{
	if (Lives<=0)
	{
		terminate=1;
		return 1;
	}
	else
	{
		return 0;
	}
}
void GAMECONTROL::KeyMouseControl()
{
	FsPollDevice();
 	key=FsInkey();
	MouseEvent=FsGetMouseEvent(lb,mb,rb,mx,my);
	int ChangeAmount=50;
	switch(key)
	{
	case FSKEY_ESC:
		terminate=1;
		printf("%d\n",terminate);
		break;
	case FSKEY_Q:
		terminate=1;
		printf("%d\n",terminate);
		break;
	case FSKEY_Y:
		terminate=2;
		printf("%d\n",terminate);
		break;
	case FSKEY_M:
		TotMoney+=20;
		break;
	case FSKEY_W: //Up
		if(ProjectionY+ChangeAmount>600) 
			ProjectionY=600;
		else ProjectionY+=ChangeAmount;
		//printf("%d\n",ProjectionY);
		break;
	case FSKEY_S: //Down
		if(ProjectionY-ChangeAmount<0)
			ProjectionY=0;
		else ProjectionY-=ChangeAmount;
		break;
	case FSKEY_A: //Left
		if(ProjectionX-ChangeAmount<0)
			ProjectionX=0;
		else ProjectionX-=ChangeAmount;
		break;
	case FSKEY_D: //Right
		if(ProjectionX+ChangeAmount>800)
			ProjectionX=800;
		else ProjectionX+=ChangeAmount;
		break;
	}
	//Tower Type One
	if(NumTower[0]<TotNumTower1
		&& FSMOUSEEVENT_LBUTTONUP!=MouseEvent
		&& FSMOUSEEVENT_LBUTTONDOWN==MouseEvent
		&& mx>472 && mx<552
		&& my>500 && my<580
		&& Click!=BUSY
		&& TotMoney>=tower[0][NumTower[0]].Cost
		)
	{
		if(tower[0][NumTower[0]].state==0)
		{
			tower[0][NumTower[0]].state=-1; //-1 for setting
			Click=BUSY;
		}
	}
	//Tower Type Two
	else if(NumTower[1]<TotNumTower2
		&& FSMOUSEEVENT_LBUTTONUP!=MouseEvent
		&& FSMOUSEEVENT_LBUTTONDOWN==MouseEvent
		&& mx>554 && mx<634
		&& my>500 && my<580
		&& Click!=BUSY
		&& TotMoney>=tower[1][NumTower[1]].Cost
		)
	{
		if(tower[1][NumTower[1]].state==0)
		{
			tower[1][NumTower[1]].state=-1; //-1 for setting
			Click=BUSY;
		}
	}
	//Tower Type Three
	else if(NumTower[2]<TotNumTower3
		&& FSMOUSEEVENT_LBUTTONUP!=MouseEvent
		&& FSMOUSEEVENT_LBUTTONDOWN==MouseEvent
		&& mx>636 && mx<716
		&& my>500 && my<580
		&& Click!=BUSY
		&& TotMoney>=tower[2][NumTower[2]].Cost
		)
	{
		if(tower[2][NumTower[2]].state==0)
		{
			tower[2][NumTower[2]].state=-1; //-1 for setting
			Click=BUSY;
		}
	}
	//Tower Type Four
	else if(NumTower[3]<TotNumTower4
		&& FSMOUSEEVENT_LBUTTONUP!=MouseEvent
		&& FSMOUSEEVENT_LBUTTONDOWN==MouseEvent
		&& mx>718 && mx<798
		&& my>500 && my<580
		&& Click!=BUSY
		&& TotMoney>=tower[3][NumTower[3]].Cost
		)
	{
		if(tower[3][NumTower[3]].state==0)
		{
			tower[3][NumTower[3]].state=-1; //-1 for setting
			Click=BUSY;
		}
	}
	//Second Click Tower Type One
		for (int t=0; t<4; t++) {
		if(tower[t][NumTower[t]].state==-1
			&& FSMOUSEEVENT_LBUTTONUP!=MouseEvent
			&& FSMOUSEEVENT_LBUTTONDOWN==MouseEvent
			&& Click==NOACTION
			&& TotMoney>=tower[t][NumTower[t]].Cost
			)
		{
			Click=NOACTION;
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			int canChange=1;
			if(map.mapGrid[(mx+ProjectionX)/80][(my+600-ProjectionY)/80]!=WALKABLE)
				break;
			map.mapGrid[(mx+ProjectionX)/80][(my+600-ProjectionY)/80]=ISTOWER;

			canChange=map.canBuildTower(monster,TotNumMonster);

			if (canChange==1) 
			{
				tower[t][NumTower[t]].setLocation((mx+ProjectionX)/2,(my+600-ProjectionY)/2);			
				tower[t][NumTower[t]].state=1;
				NumTower[t]++;
				canChange=0;
				TotMoney-=tower[t][NumTower[t]].Cost;
			}
			else 
			{
				printf("cannot place the tower here.\n"); // delete this line later
				map.mapGrid[(mx+ProjectionX)/80][(my+600-ProjectionY)/80]=WALKABLE;
				
				//tower[t][NumTower[t]].BlockingMonster=1;
			}
			
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		}
	}
/*	if(tower[0][NumTower[0]].state==-1
		&& FSMOUSEEVENT_LBUTTONUP!=MouseEvent
		&& FSMOUSEEVENT_LBUTTONDOWN==MouseEvent
		&& Click==NOACTION
		&& TotMoney>=tower[0][NumTower[0]].Cost
		)
	{
		Click=NOACTION;
		tower[0][NumTower[0]].setLocation((mx+ProjectionX)/2,(my+600-ProjectionY)/2);
		map.mapGrid[(mx+ProjectionX)/80][(my+600-ProjectionY)/80]=UNWALKABLE;
		tower[0][NumTower[0]].state=1;
		NumTower[0]++;
		TotMoney-=tower[0][NumTower[0]].Cost;
	}
	//Second Click Tower Type Two
	else if(tower[1][NumTower[1]].state==-1
		&& FSMOUSEEVENT_LBUTTONUP!=MouseEvent
		&& FSMOUSEEVENT_LBUTTONDOWN==MouseEvent
		&& Click==NOACTION
		&& TotMoney>=tower[1][NumTower[1]].Cost
		)
	{
		Click=NOACTION;
		tower[1][NumTower[1]].setLocation((mx+ProjectionX)/2,(my+600-ProjectionY)/2);
		map.mapGrid[(mx+ProjectionX)/80][(my+600-ProjectionY)/80]=UNWALKABLE;
		tower[1][NumTower[1]].state=1;
		NumTower[1]++;
		TotMoney-=tower[1][NumTower[1]].Cost;
	}
	//Second Click Tower Type Three
	else if(tower[2][NumTower[2]].state==-1
		&& FSMOUSEEVENT_LBUTTONUP!=MouseEvent
		&& FSMOUSEEVENT_LBUTTONDOWN==MouseEvent
		&& Click==NOACTION
		&& TotMoney>=tower[2][NumTower[2]].Cost
		)
	{
		Click=NOACTION;
		tower[2][NumTower[2]].setLocation((mx+ProjectionX)/2,(my+600-ProjectionY)/2);
		map.mapGrid[(mx+ProjectionX)/80][(my+600-ProjectionY)/80]=UNWALKABLE;
		tower[2][NumTower[2]].state=1;
		NumTower[2]++;
		TotMoney-=tower[2][NumTower[2]].Cost;
	}
	//Second Click Tower Type Four
	else if(tower[3][NumTower[3]].state==-1
		&& FSMOUSEEVENT_LBUTTONUP!=MouseEvent
		&& FSMOUSEEVENT_LBUTTONDOWN==MouseEvent
		&& Click==NOACTION
		&& TotMoney>=tower[3][NumTower[3]].Cost
		)
	{
		Click=NOACTION;
		tower[3][NumTower[3]].setLocation((mx+ProjectionX)/2,(my+600-ProjectionY)/2);
		map.mapGrid[(mx+ProjectionX)/80][(my+600-ProjectionY)/80]=UNWALKABLE;
		tower[3][NumTower[3]].state=1;
		NumTower[3]++;
		TotMoney-=tower[3][NumTower[3]].Cost;
	}
	
	*/


	//Mouse Move Out of the Menu Area
	if((mx<472 || mx>798)
		|| (my<500 || my>580))
		Click=NOACTION;
}
void GAMECONTROL::DrawControlPanel()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	int winWid,winHei;
    FsGetWindowSize(winWid,winHei);
    glViewport(0,0,winWid,winHei);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,(float)winWid-1,(float)winHei-1,0,-1,1);
	for(int i=0;i<4;i++)
	{
		glRasterPos2d(472+82*i,500+(double)(towermini[i].hei-1));
		glDrawPixels(towermini[i].wid,towermini[i].hei,GL_RGBA,GL_UNSIGNED_BYTE,towermini[i].rgba);
	}
	FsGetWindowSize(winWid,winHei);
    glViewport(0,0,winWid,winHei);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,(float)winWid-1,(float)winHei-1,0,-1,1);
	glRasterPos2d(0,550+(double)(life.hei-1));
	glDrawPixels(life.wid,life.hei,GL_RGBA,GL_UNSIGNED_BYTE,life.rgba);
	glDisable(GL_BLEND);


	char charlife[2];

	charlife[0]=48+((Lives/10)%10);
	charlife[1]=48+(Lives%10);

	glColor3ub(0,0,0);
	glRasterPos2d(44,585);
	YsGlDrawFontBitmap16x24(charlife);
}
int GAMECONTROL::RunGame()
{
    FsOpenWindow(16,16,800,600,1);
	int StartMenuState=0;
	while(StartMenuState!=2)
	{
	if(StartMenuState==0)
	{
		StartMenuState=StartMenu();
	}
	else if(StartMenuState==3)
	{
        FsPollDevice();
		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        int winWid,winHei;
        FsGetWindowSize(winWid,winHei);
        glViewport(0,0,winWid,winHei);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0,(float)winWid-1,(float)winHei-1,0,-1,1);
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        glRasterPos2d(0.0,(double)(instruction[InsPtr].hei-1));
		glDrawPixels(instruction[InsPtr].wid,instruction[InsPtr].hei,GL_RGBA,GL_UNSIGNED_BYTE,instruction[InsPtr].rgba);
		key=FsInkey();
		switch(key)
		{
		case FSKEY_RIGHT:
		case FSKEY_D:
			if(InsPtr<4)
				InsPtr++;
			break;
		case FSKEY_LEFT:
		case FSKEY_A:
			if(InsPtr>0)
				InsPtr--;

		}
		FsSwapBuffers();
		FsSleep(20);
		if(InsPtr==4)
		{
			StartMenuState=0;
			InsPtr=0;
		}

	}
    else if(StartMenuState==1)
    {
    printf("Play!\n");
	LoadEverthing();
	key=FsInkey();
	FsPassedTime();
	while(terminate==0)
	{
		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		timer+=FsPassedTime();
 		FsGetMouseEvent(lb,mb,rb,mx,my);

		FsPollDevice();
		KeyMouseControl();
		map.DrawMap(ProjectionX,ProjectionY,monster[0].ELocX,monster[0].ELocY);
		TowerLockedCheck();

		//Check if missile hit the monster
		for(int towertype=0;towertype<4;towertype++)
		for(int j=0;j<NumTower[towertype];j++)
		{
			for(int i=0;i<tower[towertype][j].MaxNumMis;i++)
			{
				if(tower[towertype][j].missile[i].GetState()==1)
				{
					tower[towertype][j].missile[i].Move(monster[tower[towertype][j].missile[i].TargetID].GetX(),monster[tower[towertype][j].missile[i].TargetID].GetY());

					double relativeX=tower[towertype][j].missile[i].getX()-monster[tower[towertype][j].missile[i].TargetID].GetX();
					double relativeY=tower[towertype][j].missile[i].getY()-monster[tower[towertype][j].missile[i].TargetID].GetY();
					if(relativeX<10 &&
						relativeX>-10 &&
						relativeY<10 &&
						relativeY>-10)
					{
						tower[towertype][j].missile[i].Set(0,0,0,0);
						monster[tower[towertype][j].missile[i].TargetID].GotHit(tower[towertype][j].Damage);
						//printf("%lf\n",monster.Blood);
					}
						
					tower[towertype][j].missile[i].DrawMissile(ProjectionX,ProjectionY);
	
				}
					//printf("missileID %d missileState %d \n",i,tower[towertype][j].missile[i].GetState());
			}
			
			/*  Checking If the tower location will block the pass
			if(tower[towertype][NumTower[towertype]].state==-1)
			{
				//printf("State==-1\n");
				tower[towertype][NumTower[towertype]].BlockingMonster
					=CheckTowerBuildBlock(towertype);
			}*/
		}
		for(int t=0;t<4;t++)
			for(int j=0;j<NumTower[t]+1;j++)
			tower[t][j].DrawTower(ProjectionX,ProjectionY,mx,my);

		for(int i=0;i<NumMonster+1 && i<TotNumMonster;i++)
		{
			monster[i].MoveMonster(map);					
			if(monster[i].DrawMonster(ProjectionX,ProjectionY,timer))
				NumMonster++;
			monster[i].DrawHealth(ProjectionX,ProjectionY);
			
			int Dis=monster[i].Disappear();
			
			if(Dis==0)
			{
				TotMoney+=monster[i].MoneyBack();
				DeadMonster++;
				printf("you have %d money,%d monsters dead.\n",TotMoney,DeadMonster);
			}
			
			else if(Dis==1) //Dissapear will return 1 if monster step on the end
			{
				Lives--;
				DeadMonster++;
				printf("You have %d Lives Left.\n",Lives);
			}
		}
		//printf("Number of Monster:%d.",NumMonster);
		
		CheckWin();
		CheckLose();
		DrawControlPanel();
		ShowTime();
		ShowMoney();
		FsSwapBuffers();
		FsSleep(20);
	} //End of while(terminate==0)
	while (terminate==1) //Lose Game or Quit in the middle
	{
		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
 		timer+=FsPassedTime();
		MouseEvent=FsGetMouseEvent(lb,mb,rb,mx,my);
		losethegame.JumpChickenJump(timer,400,50);
		losethegame.JumpChickenJump(timer,200,150);
		losethegame.JumpChickenJump(timer,200,250);
		losethegame.JumpChickenJump(timer,400,350);
		losethegame.JumpChickenJump(timer,600,150);
		losethegame.JumpChickenJump(timer,600,250);
		glBegin(GL_QUADS);
		glColor3ub(155,155,100);
		glVertex2i(300,510);
		glVertex2i(500,510);
		glVertex2i(500,550);
		glVertex2i(300,550);
		glEnd();
		glColor3ub(0,0,0);
		glRasterPos2i(330,180);
		YsGlDrawFontBitmap16x20("Game Over");
		glRasterPos2i(335,210);
		YsGlDrawFontBitmap16x20("You Lose");
		glRasterPos2i(320,540);
		YsGlDrawFontBitmap16x20("Exit Game");
		if(FSMOUSEEVENT_LBUTTONUP!=MouseEvent
		&& FSMOUSEEVENT_LBUTTONDOWN==MouseEvent
		&& mx>300 && mx<500
		&& my>510 && my<550
		)
		terminate=3; //For Exit Game
		FsPollDevice();
		FsSwapBuffers();
		FsSleep(20);
	}
	while(terminate==2) //Win Game
	{
		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
 		timer+=FsPassedTime();
		MouseEvent=FsGetMouseEvent(lb,mb,rb,mx,my);
		winthegame.JumpChickenJump(timer,400,50);
		winthegame.JumpChickenJump(timer,200,150);
		winthegame.JumpChickenJump(timer,200,250);
		winthegame.JumpChickenJump(timer,400,350);
		winthegame.JumpChickenJump(timer,600,150);
		winthegame.JumpChickenJump(timer,600,250);
		glBegin(GL_QUADS);
		glColor3ub(155,155,100);
		glVertex2i(300,510);
		glVertex2i(500,510);
		glVertex2i(500,550);
		glVertex2i(300,550);
		glEnd();
		glColor3ub(0,0,0);
		glRasterPos2i(330,180);
		YsGlDrawFontBitmap16x20("You Win!");
		glRasterPos2i(225,220);
		YsGlDrawFontBitmap16x20("You Protected CMU from");
		glRasterPos2i(235,250);
		YsGlDrawFontBitmap16x20("the Chicken Invasion!");
		glRasterPos2i(320,540);
		YsGlDrawFontBitmap16x20("Exit Game");
		if(FSMOUSEEVENT_LBUTTONUP!=MouseEvent
		&& FSMOUSEEVENT_LBUTTONDOWN==MouseEvent
		&& mx>300 && mx<500
		&& my>510 && my<550
		)
		terminate=3; //For Exit Game
		FsPollDevice();
		FsSwapBuffers();
		FsSleep(20);
	}

	CleanUp();
	//map.SaveMap("testmap.txt");
	return 0;

    } //End of if(SMS==1)
	} //End of while(StartMenuState!=2)
    if(StartMenuState==2)
    {
        printf("Quit!");
    }
	return 0;
}


