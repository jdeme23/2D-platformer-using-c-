#include "cMap.h"

#include <fstream>

cMap::cMap()
{
	nWidth = 0;
	nHeight = 0;
	pSprite = nullptr;
	m_indices = nullptr;
	m_solids = nullptr;
}

cMap::~cMap()
{
	delete[] m_indices;
	delete[] m_solids;
}

int cMap::GetIndex(int x, int y)
{
	if (x >= 0 && x < nWidth && y > 0 && y < nHeight)
		return m_indices[y * nWidth + x];
	else
		return 0;
}

bool cMap::GetSolid(int x, int y)
{
	if (x >= 0 && x < nWidth && y > 0 && y < nHeight)
		return m_solids[y * nWidth + x];
	else
		return 0;
}

bool cMap::Create(string fileData, olcSprite* sprite, string name)
{
	sName = name;
	pSprite = sprite;

	ifstream data(fileData, ios::in | ios::binary);
	if (data.is_open())
	{
		data >> nWidth >> nHeight;
		
		for ()
		{
			for ()
			{

			}
		}
			return true;
	}
	
	return false;
}