#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "cmudef.h"
#include "fssimplewindow.h"

void MAP::LoadMap(int inputlevel)
{
	level=inputlevel;
	//Load Background Picture
	if(YSOK==grassfield.Decode("../Pic/GrassField.png")
		&& YSOK==stonewall.Decode("../Pic/WallStone.png")
		&& YSOK==exit.Decode("../Pic/Exit.png")
		)
	//if(YSOK==grassfield.Decode("../Pic/DirtField.png"))
	{
		//printf("Background Field Picture Load Success.\n");
		grassfield.Flip();
		stonewall.Flip();
		exit.Flip();
		for(int j=0;j<exit.wid;j++)
			for(int k=0;k<exit.hei;k++)
			{
				//If it's purple then make it transparent
				if(exit.rgba[((exit.hei-1-k)*exit.wid+j)*4]==255 
					&& exit.rgba[((exit.hei-1-k)*exit.wid+j)*4+1]==0 
					&& exit.rgba[((exit.hei-1-k)*exit.wid+j)*4+2]==255)
					exit.rgba[((exit.hei-1-k)*exit.wid+j)*4+3] = 0;//set transparent when 0
				else
					exit.rgba[((exit.hei-1-k)*exit.wid+j)*4+3] = 255;//not transparent when 255
			}	
	}
	else
		printf("Grass Field, Stone, Exit Load Error.\n");

	//Load Walkability Map file
	char ioBuffer[256];
	char fn[256];
	FILE *fp;
	if(level==1)
	{
		fp=fopen("../Map/levelonemap.txt","r");
	}
	if(fp!=NULL)
    {
		printf("Loading map file.\n",fn);
        for (int i=0;i<mapWidth;i++)
		{
			for(int j=0;j<mapHeight;j++)
			{
				fgets(ioBuffer,256,fp);
				mapGrid[i][j]=atoi(ioBuffer); // Envalue mapGrid				
			}
		}
		//printf("mapGrid is initialized.\n");
	}
    else
    {
        printf("Cannot open a file.\n");
    }
	if(fp!=NULL)
    {
		//printf("Closing levelonemap.txt file. \n");
        fclose(fp);
    }
}

/*
void MAP::SaveMap(char* nameOfNewMap)
{
    char fn[256];    
    char ioBuffer[256];
	FILE *fpp;
    //char nameOfNewMap[256];
	//printf("Name the map you want to save: \n");
	// create a new map name
    //scanf("%s", nameOfNewMap);

    strcpy(fn,nameOfNewMap);

    fpp=fopen(fn,"w");
    
    if (fpp!=NULL)
    {
        for (int i=0;i<mapWidth;i++)
        {
			for(int j=0;j<mapHeight;j++)
            {
				_itoa(mapGrid[i][j],ioBuffer,10);
				fwrite(ioBuffer,1,strlen(ioBuffer),fpp);
				fwrite("\n",1,1,fpp);
	        }
        }
		printf("%s is saved successfully.\n",fn);
    }
    if(fpp!=NULL)
    {
        fclose(fpp);
    }
}
bool MAP::ChangeMap(int x, int y, MONSTER monster[])//monster[2]
{
	int findPath = 0;
    if ( !(x>=0 && x<mapWidth && 
		   y>=0 && y<mapHeight) )
    {
		//printf("Mouse is not on the map.\n");
        return false;
    }
    else if (mapGrid[x][y]==UNWALKABLE) // walkable=1; unwalkable=0
    {
		//printf("Tower exsited at this position.\n");
	    return false;
    }
	
    int mapGridDuplicate[mapWidth][mapHeight]; // deep copy the current map
    for (int i=0; i<mapWidth; i++)
	{
		for (int j=0; j<mapHeight; j++)
		{
			mapGridDuplicate[i][j] = mapGrid[i][j];
		}
    }
	mapGridDuplicate[x][y] = UNWALKABLE;
	// check if all monsters can walk out after building the new tower
	for (int m=0; m<2; m++)
    {

	    if (monster[m].state==1)		
	    {
			findPath = finder.FindPath(monster[m].GetX(), monster[m].GetY(),75,59,mapGrid);
			if (findPath!=1) 
			{
				//printf("Tentative tower location (%d, %d) is invalid.\n", x, y);
				return false;
			}
	    }
    }
	
    mapGrid[x][y]=UNWALKABLE;
	//printf("Paths are found and map is changed.\n");
	return true;
}
*/
void MAP::DrawMap(int pngProjX,int pngProjY,int ExitX,int ExitY)
{
	int ProjectionX=pngProjX,ProjectionY=600-pngProjY;
	FsPollDevice();
	//printf("ProjectionX:%d ProjectionY:%d\n",pngProjX,pngProjY);
	int winWid,winHei;
    FsGetWindowSize(winWid,winHei);
    glViewport(0,0,winWid,winHei);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,(float)winWid-1,(float)winHei-1,0,-1,1);
	glRasterPos2d(0,(double)winHei-1);
	//glDrawPixels(800,600,GL_RGBA,GL_UNSIGNED_BYTE,grassfield.rgba);
	
	unsigned char *VisibleGrass;
	VisibleGrass=new unsigned char [800*600*4];
	
	for(int j=0;j<600;j++)
		for(int i=0;i<800;i++)
		{
			VisibleGrass[(j*800+i)*4]
			=grassfield.rgba[((j+pngProjY)*grassfield.wid+i+pngProjX)*4];
			VisibleGrass[(j*800+i)*4+1]
			=grassfield.rgba[((j+pngProjY)*grassfield.wid+i+pngProjX)*4+1];
			VisibleGrass[(j*800+i)*4+2]
			=grassfield.rgba[((j+pngProjY)*grassfield.wid+i+pngProjX)*4+2];
			VisibleGrass[(j*800+i)*4+3]
			=grassfield.rgba[((j+pngProjY)*grassfield.wid+i+pngProjX)*4+3];
		}

	glDrawPixels(800,600,GL_RGBA,GL_UNSIGNED_BYTE,VisibleGrass);
	delete [] VisibleGrass;
	int TileSize=1600/mapWidth;
	for(int i=0;i<mapWidth;i++)
	{
		for(int j=0;j<mapHeight;j++)
		{
			if(mapGrid[i][j]==UNWALKABLE
				//&& i*TileSize>=ProjectionX-TileSize && i*TileSize<ProjectionX+800
				//&& j*TileSize>=ProjectionY-TileSize && j*TileSize<ProjectionY+600
				)
			{
				int winWid,winHei;
				FsGetWindowSize(winWid,winHei);
				glViewport(0,0,winWid,winHei);
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				glOrtho(0,(float)winWid-1,(float)winHei-1,0,-1,1);
				glRasterPos2d(-ProjectionX+TileSize*i,-ProjectionY+TileSize*j+TileSize-1);//+(double)stonewall.hei);//winHei);
				glDrawPixels(stonewall.wid,stonewall.hei,GL_RGBA,GL_UNSIGNED_BYTE,stonewall.rgba);
				
				/*
				glEnable(GL_BLEND);    
				glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
				glColor4ub(255,0,0,50);
				glBegin(GL_QUADS);
				glVertex2i(-ProjectionX+TileSize*i,-ProjectionY+TileSize*j);
				glVertex2i(-ProjectionX+TileSize*i+TileSize,-ProjectionY+TileSize*j);
				glVertex2i(-ProjectionX+TileSize*i+TileSize,-ProjectionY+TileSize*j+TileSize);
				glVertex2i(-ProjectionX+TileSize*i,-ProjectionY+TileSize*j+TileSize);
				
				glEnd();
				glDisable(GL_BLEND);
				*/
			}
			/*else if(mapGrid[i][j]==WALKABLE)
			{
				glColor3ub(255,100,0);
				glBegin(GL_QUADS);
				glVertex2i(TileSize*i,TileSize*j);
				glVertex2i(TileSize*i+TileSize,TileSize*j);
				glVertex2i(TileSize*i+TileSize,TileSize*j+TileSize);
				glVertex2i(TileSize*i,TileSize*j+TileSize);
				glEnd();
			}*/
		}
	}
	//int winWid,winHei;
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	FsGetWindowSize(winWid,winHei);
    glViewport(0,0,winWid,winHei);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(0,(float)winWid-1,(float)winHei-1,0,-1,1);
	//printf("ExitX/tile:%d,Y:%d",ExitX*2/TileSize,ExitY*2/TileSize);
	glRasterPos2d(-ProjectionX+(ExitX*2/TileSize)*TileSize,-ProjectionY+(ExitY*2/TileSize)*TileSize+(double)exit.hei);//winHei);
	glDrawPixels(exit.wid,exit.hei,GL_RGBA,GL_UNSIGNED_BYTE,exit.rgba);
	glDisable(GL_BLEND);				
	/*glColor3ub(0,0,0);
	glRasterPos2d(720,585);
	YsGlDrawFontBitmap16x24("Back");*/
}
int MAP::canBuildTower(const MONSTER monster[], const int TotNumMonster)//monster[2]
{
	int canBuild=1;
	ASTAR finder;
	for (int m=0; m<TotNumMonster;m++)
	{
		if (monster[m].state==1) 
		{
			//printf("check every monster[%d] path.\n",m); // delete this line later
			if(finder.FindPath(monster[m].GetX(),monster[m].GetY(),799,300,mapGrid)!=finder.found)
			{
				canBuild=0;
				//printf("In for loop, cannot place a tower here.\n"); // delete this line later
				break;
			}
		}
	}
	finder.~ASTAR(); 
	return canBuild;
}
