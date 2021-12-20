// 2D Platformer using c++ 
// using olcPixelGameEngine by Javidx9 - OneLoneCoder

#include <iostream>
#include <string>
using namespace std;

#include <olcConsoleGameEngine.h>

class HJ_Platformer : public olcConsoleGameEngine
{
public:
	HJ_Platformer()
	{
		m_sAppName = L"Tile Based Platform Game";
	}
private:
	wstring sLevel;
	int nLevelWidth;
	int nLevelHeight;

	float fCameraPosX = 0.0f;
	float fCameraPosY = 0.0f;


protected:
	virtual bool OnUserCreate()
	{
		nLevelWidth = 64;
		nLevelHeight = 16;

		sLevel += L"................................................................";
		sLevel += L"................................................................";
		sLevel += L"................................................................";
		sLevel += L"................................................................";
		sLevel += L"........................##......................................";
		sLevel += L"..........................#...##................................";
		sLevel += L".................................#........##....................";
		sLevel += L".....................###.............#..........................";
		sLevel += L"..................###............#....##........................";
		sLevel += L"................###.............................................";
		sLevel += L"######################..#####################..#......##########";
		sLevel += L"....................##.....#............#...........###.........";
		sLevel += L".....................#......#############.......####............";
		sLevel += L".....................#......................####................";
		sLevel += L".....................#########################..................";
		sLevel += L"................................................................";


		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime)
	{
		// Draw the level
		int nTileWidth = 16; 
		int nTileHeight = 16;
		int nVisibleTilesX = ScreenWidth() / nTileWidth;
		int nVisibleTilesY = ScreenHeight() / nTileHeight;

		// calculate top-leftmost visible tile
		//		offset the camera so that it is positioned 
		//		in the middle of the screen.
		float fOffsetX = fCameraPosX - (float)nVisibleTilesX / 2.0f;
		float fOffsetY = fCameraPosY - (float)nVisibleTilesY / 2.0f;



		return true;
	}
};






int main()
{
	cout << "I work" << endl;
	
	HJ_Platformer game;
	if (game.ConstructConsole(160, 120, 8, 8))
		game.Start();
	return 0;
}

