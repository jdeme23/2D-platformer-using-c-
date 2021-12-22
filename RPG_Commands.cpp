#include "RPG_Commands.h"


cScriptProcessor::cScriptProcessor()
{
	bUserControlEnabled = true;
}

void cScriptProcessor::AddCommand(cCommand* cmd)
{
	m_listCommands.push_back(cmd);

}

void cScriptProcessor::ProcessCommands(float fElapsedTime)
{
	//If command(s) are available, halt user control
	bUserControlEnabled = m_listCommands.empty();
	
	if (!m_listCommands.empty())
	{
		//A command is available
		if (!m_listCommands.front()->bCompleted)
		{
			//Command has not been started
			if (!m_listCommands.front()->bStarted)
			{
				m_listCommands.front()->Start();
				m_listCommands.front()->bStarted = true;
			}
			else
				m_listCommands.front()->Update(fElapsedTime);
		}
		else
		{
			//Command has been completed
			delete m_listCommands.Front();
			m_listCommands.pop_Front();
		}
			
	}
}