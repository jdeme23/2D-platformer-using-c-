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

	float fPlayerPosX = 0.0f;
	float fPlayerPosY = 0.0f;

	float fPlayerVelX = 0.0f;
	float fPlayerVelY = 0.0f;

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
		//Utility Lambdas
		auto GetTile = [&](int x, int y)
		{
			if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
				return sLevel[y * nLevelWidth + x];
			else
				reurn L'';
		};

		auto SetTile = [&](int x, int y, wchar_t c)
		{
			if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
				sLevel[y * nLevelWidth + x] = c;
		
		};

		fPlayerVelX = 0.0f;
		fPlayerVelX = 0.0f;

		//Handle Input
		if (IsFocused())
		{
			if (GetKey(VK_UP).bHeld)
			{
				fPlayerVelY = -6.0f;
			}
			if (GetKey(VK_DOWN).bHeld)
			{
				fPlayerVelY = 6.0f;
			}
			if (GetKey(VK_LEFT).bHeld)
			{
				fPlayerVelX = -6.0f;
			}
			if (GetKey(VK_RIGHT).bHeld)
			{
				fPlayerVelX = 6.0f;
			}
		}
		
		fPlayerPosX = fPlayerPosX + fPlayerVelX * fElapsedTime;
		fPlayerPosY = fPlayerPosY + fPlayerVelY * fElapsedTime;

		fCameraPosX = fPlayerPosX;
		fCameraPosY = fPlayerPosY;

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

		//Clamp camera to game boundaries 
		if (fOffsetX < 0) fOffsetX = 0;
		if (fOffsetY < 0) fOffsetY = 0;
		if (fOffsetX > nLevelWidth - nVisibleTilesX) fOffsetX = nLevelWidth - nVisibleTilesX;
		if (fOffsetY > nLevelHeight - nVisibleTilesY) fOffsetY = nLevelHeight - nVisibleTilesY;

		//Draw visible tile map
		for (int x = 0; x < nVisibleTilesX; x++)
		{
			for(int y = 0; y < nVisibleTilesY; y++)
			{
				wchar_t sTileID = GetTile(x + fOffsetX, y + fOffsetY);
				switch (sTileID)
				{
				case L'.';
					Fill(x * nTileWidth, y * nTileHeight, (x + 1) * nTileWidth, (y + 1) * nTileHeight, PIXEL_SOLID, FG_CYAN);
					break;
				case L'#';
					Fill(x * nTileWidth, y * nTileHeight, (x + 1) * nTileWidth, (y + 1) * nTileHeight, PIXEL_SOLID, FG_RED);
					break; 
				default:
				}
			}
		}

		//Draw Player
		Fill((fPlayerPosX - fOffsetX) * nTileWidth, (fPlayerPosY - fOffsetY) * nTileWidth, PIXEL_SOLID, FG_GREEN)	


		return true;
	}
};






int main()
{
	HJ_Platformer game;
	if (game.ConstructConsole(160, 120, 8, 8))
		game.Start();
	
		return 0;
}

