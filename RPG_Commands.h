#pragma once
#include <list>
using namespace std;

class cCommand
{
public:
	cCommand() {}
	virtual ~cCommand() {}
	
	bool bStarted = false;
	bool bCompleted = false;

	virtual void Start() {}
	virtual void Update(float fElapsedTime) {};
};

class cScriptProcessor
{
public:
	cScriptProcessor();

public:
	void AddCommand(cCommand* cmd);
	void ProcessCommands(float fElapsedTime);

public:
	bool bUserControlEnabled;

private:
	list<cCommand*> m_listCommands;

};

class cCommand_MoveTo : public cCommand
{
public:
	cCommand_MoveTo(cDymamic* object, float x, float y, float duration = 0.0f); //33:57
};