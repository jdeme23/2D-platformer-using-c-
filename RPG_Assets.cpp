#include "RPG_Assets.h"

RPG_Assets::RPG_Assets()
{

}

RPG_Assets::~RPG_Assets()
{

}

void RPG_Assets::LoadSprites()
{
	auto load = [&](string sName, wstring sFileName)
	{
		olcSprite* s = new olcSprite(sFileName);
		m_mapSprites[sName] = s;
	};

	load("village", L"rpgdata/gfx/toml_spritesheetdark.spr");
}