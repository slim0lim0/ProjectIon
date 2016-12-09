#ifndef __LOGMANAGER_H__
#define __LOGMANAGER_H__

class LogManager
{

	// Member Methods:
public:
	static LogManager& GetInstance();
	~LogManager();

	void Log(const char* pcMessage);
protected:

private:
	LogManager();
	LogManager(const LogManager& oLogManager);
	LogManager& operator=(const LogManager& oLogManager);

public:

protected:
	static LogManager* sm_pInstance;

private:

};

#endif //__LOGMANAGER_H__