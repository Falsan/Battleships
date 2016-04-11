#pragma once
#include <vector>

class ChatLog
{
public:
	ChatLog()= default;
	~ChatLog() = default;

	void addToChatLog(std::string _in);
	void printLog();
	//std::vector<std::string> getLog() { return m_chatLog; }


private:
void alterChatLog(bool _in, std::string _inString);
	std::vector<std::string> m_chatLog;
};