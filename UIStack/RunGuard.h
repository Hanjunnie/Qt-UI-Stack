#pragma once

#include <QObject>
#include <QSharedMemory>
#include <QSystemSemaphore>

class RunGuard  
{
public:
	RunGuard(const QString& key);
	~RunGuard();

	bool isAnotherRunning();
	bool tryToRun();
	void release();

private:
	const QString key;
	const QString memlockKey;
	const QString sharedmemKey;

	QSharedMemory sharedMem;
	QSystemSemaphore memLock;

	RunGuard(const RunGuard&) = delete;
};
