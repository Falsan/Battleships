#include "ChatLog.h"
#include <mutex>
#include <iostream>

#include <SFML\Network.hpp>

void ChatLog::addToChatLog(std::string _in)
{
	alterChatLog(true, _in);
}

void ChatLog::printLog()
{
	alterChatLog(false, "NULL");
}

void ChatLog::alterChatLog(bool _in, std::string _inString)
{
	int chatSize = 10;
	std::mutex mtx;

	mtx.lock();
	if (_in)
	{
		//drops the first item on the the vector list of our chat log
		m_chatLog.push_back(_inString);

		//If we have reached capacity on our chat log removes the first element 
		if (m_chatLog.size() > chatSize)
		{
			m_chatLog.erase(m_chatLog.begin());
		}
	}
	else
	{
		std::cout << "++++++ Chat log current size [" << m_chatLog.size() <<"/"<< chatSize << "] ++++++" << std::endl;
		for (auto it = m_chatLog.begin(); it != m_chatLog.end(); it++)
		{
			std::cout << (*it) << std::endl;
		}
		std::cout << "+++++++++++++++Chat Log++++++++++++++++++++" << std::endl;

	}


	mtx.unlock();


}