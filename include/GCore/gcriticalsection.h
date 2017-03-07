/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @file	gcriticalsection.h
** @brief	�����������͵Ķ���
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2017-1-22
** @version	1.0
**
****************************************************************************/
#ifndef _CORE_CRITICAL_SECTION_H_
#define _CORE_CRITICAL_SECTION_H_

#include "glock.h"

#define G_CRITICAL_SECTION_HANELD_SIZE G_POINTER_ADDRESS_SIZE*8

/****************************************************************************
**
** gobject.h
**
** @class		GCriticalSection
** @brief		�ٽ���
** @module		GCore
**
** �ٽ���Ҳ�ƹؼ�����Σ����ŵ����ٶȽϿ죬������Ϊ���Ĺ���λ���û�̬����˿���С�ڻ�������
** Ϊ��������ܣ�����ٽ����Ѿ��������̳߳���ʱ����������ԭ��������������һ�������󻹲���
** ��ȡ�ؼ�����Σ���ʱ�̲߳�ת���ں˷�ʽ������ȴ�״̬��
** Ĭ������²������������ܣ���Ҫ���ã�Ӧ�ڹ��캯����ָ�����ò�ָ������������
**
****************************************************************************/
class GAPI GCriticalSection final 
	: public GLock
{
public:
	GCriticalSection();
	GCriticalSection(gbool spin, gsize spin_count);
	~GCriticalSection();
	gvoid Lock();
	gvoid Unlock();

private:
	gvoid Initialize(gbool spin, gsize spin_count);
	gvoid Release();

private:
#ifdef G_SYSTEM_WINDOWS
	gbyte m_pHandle[G_CRITICAL_SECTION_HANELD_SIZE];
#endif // G_SYSTEM_WINDOWS
};

#undef G_CRITICAL_SECTION_HANELD_SIZE

#endif // _CORE_CRITICAL_SECTION_H_