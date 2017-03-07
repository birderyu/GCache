#pragma once

#include "grunnable.h"
#include "gthread.h"
#include "gstring.h"

/// һ��������GRunnable����
class GSelfThread : public GRunnable
{
public:
	GSelfThread(const GString &name)
		: name_(name)
	{

	}

protected:
	gint Run()
	{
		std::cout << name_.CString() << std::endl;
		return 0;
	}

private:
	GString name_;
};

/// ʹ��������ķ�ʽʵ��һ���߳���
gvoid SelfThread_Test()
{
	GSelfThread task("use self thread.");
	task.Start();
	GThread::Sleep(5);
	task.Stop();
}

/// ʹ�ð󶨵ķ�ʽʵ��һ���߳���
gvoid BindThread_Test()
{
	GThread task;
	task.Start();
	GThread::Sleep(5);
	task.Stop();
}