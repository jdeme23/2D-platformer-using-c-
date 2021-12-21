// 2D Platformer using c++ 
// using olcPixelGameEngine by Javidx9 - OneLoneCoder

#include <iostream>
#include <string>
using namespace std;

#include "olcConsoleGameEngineOOP.h"
#include "cMap.h"

class HJ_Platformer : public olcConsoleGameEngineOOP
{
public:
	HJ_Platformer()
	{
		m_sAppName = L"Tile Based Platform Game";
	}
private:
	cMap* m_pCurrentMap = nullptr;

	float fPlayerPosX = 0.0f;
	float fPlayerPosY = 0.0f;

	float fPlayerVelX = 0.0f;
	float fPlayerVelY = 0.0f;

	float fCameraPosX = 0.0f;
	float fCameraPosY = 0.0f;


protected:
	virtual bool OnUserCreate()
	{
		m_pCurrentMap = new cMap_Village1();


		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime)
	{

		fPlayerVelX = 0.0f;
		fPlayerVelY = 0.0f;

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

		float fNewPlayerPosX = fPlayerPosX + fPlayerVelX * fElapsedTime;
		float fNewPlayerPosY = fPlayerPosY + fPlayerVelY * fElapsedTime;

		//Collision
		if (fPlayerVelX <= 0)
		{
			if (m_pCurrentMap->GetSolid(fNewPlayerPosX + 0.0f, fPlayerPosY + 0.0f) || m_pCurrentMap->GetSolid(fNewPlayerPosX + 0.0f, fPlayerPosY + 0.9f) )
			{
				fNewPlayerPosX = (int)fNewPlayerPosX + 1;
				fPlayerVelX = 0;
			}
				 
		}
		else
		{
			if (m_pCurrentMap->GetSolid(fNewPlayerPosX + 1.0f, fPlayerPosY + 0.0f) || m_pCurrentMap->GetSolid(fNewPlayerPosX + 1.0f, fPlayerPosY + 0.9f) )
			{
				fNewPlayerPosX = (int)fNewPlayerPosX;
				fPlayerVelX = 0;
			}
		}

		if (fPlayerVelY <= 0)
		{
			if (m_pCurrentMap->GetSolid(fNewPlayerPosX + 0.0f, fNewPlayerPosY) || m_pCurrentMap->GetSolid(fNewPlayerPosX + 0.9f, fNewPlayerPosY) )
			{
				fNewPlayerPosY = (int)fNewPlayerPosY + 1;
				fPlayerVelX = 0;
			}

		}
		else
		{
			if (m_pCurrentMap->GetSolid(fNewPlayerPosX + 0.0f, fNewPlayerPosY + 1.0f) || m_pCurrentMap->GetSolid(fNewPlayerPosX + 0.9f, fNewPlayerPosY + 1.0f))
			{
				fNewPlayerPosY = (int)fNewPlayerPosY;
				fPlayerVelY = 0;
			}
		}

		fPlayerPosX = fNewPlayerPosX;
		fPlayerPosY = fNewPlayerPosY;


		fCameraPosX = fPlayerPosX;
		fCameraPosY = fPlayerPosY;

		// Draw the level
		int nTileWidth = 8;
		int nTileHeight = 8;
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
		if (fOffsetX > m_pCurrentMap->nWidth - nVisibleTilesX) fOffsetX = m_pCurrentMap->nWidth - nVisibleTilesX;
		if (fOffsetY > m_pCurrentMap->nHeight - nVisibleTilesY) fOffsetY = m_pCurrentMap->nHeight - nVisibleTilesY;

		//Get offsets for smooth movement
		float fTileOffsetX = (fOffsetX - (int)fOffsetX) * nTileWidth;
		float fTileOffsetY = (fOffsetY - (int)fOffsetY) * nTileHeight;	

		//Draw visible tile map
		for (int x = -1; x < nVisibleTilesX + 1; x++)
		{
			for (int y = -1; y < nVisibleTilesY + 1; y++)
			{
				int idx = m_pCurrentMap->GetIndex(x + fOffsetX, y + fOffsetY);
				int sx = idx % 10; // column
				int sy = idx / 10; // row
			
				DrawPartialSprite(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, m_pCurrentMap->pSprite, sx * nTileWidth, sy * nTileHeight, nTileWidth, nTileHeight);
			}
		}

		//Draw Player
		Fill((fPlayerPosX - fOffsetX) * nTileWidth, (fPlayerPosY - fOffsetY) * nTileWidth, (fPlayerPosX - fOffsetX + 1.0f) * nTileWidth, (fPlayerPosY - fOffsetY + 1.0f) * nTileHeight, PIXEL_SOLID, FG_GREEN);


		return true;
	}
};



int main()
{
	HJ_Platformer game;
	if (game.ConstructConsole(117, 117, 4, 4))
		game.Start();

	return 0;
}

