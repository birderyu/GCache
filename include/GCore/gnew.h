#ifndef _CORE_NEW_H_
#define _CORE_NEW_H_

#include <new>
#include "gmemory.h"
#include "gmemorypool.h"
#include "glockguard.h"

G_BEGIN_NAMESPACE

// NewHandler
class GNewHander
{
public:
	explicit GNewHander(std::new_handler nh)
		: handler(nh) {}
	~GNewHander()
	{
		std::set_new_handler(handler);
	}

private:
	std::new_handler handler;
	GNewHander(const GNewHander&);
	GNewHander &operator=(const GNewHander&);
};

// �̲߳���ȫ
// �����䵽�ڴ��
// ������NewHandler
template<typename ClassT>
class GNewT
{
public:
	static gpointer operator new(gsize) noexcept(false);
	static gvoid operator delete(gpointer) noexcept;
};

// �̲߳���ȫ
// ���䵽�ڴ��
// ������NewHandler
template<typename ClassT>
class GNewInPoolT
{
public:
	static gpointer operator new(gsize);
	static gvoid operator delete(gpointer);

private:
	static GMemoryPool<sizeof(ClassT)> pool;
};

// �̲߳���ȫ
// �����䵽�ڴ��
// ����NewHandler
template<typename ClassT>
class GNewWithHandlerT
{
public:
	static std::new_handler set_new_handler(std::new_handler p);
	static gpointer operator new(gsize);
	static gvoid operator delete(gpointer);

private:
	static std::new_handler currentHandler;
};

// �̲߳���ȫ
// ���䵽�ڴ��
// ����NewHandler
template<typename ClassT>
class GNewInPoolWithHandlerT
{
public:
	static std::new_handler set_new_handler(std::new_handler p);
	static gpointer operator new(gsize);
	static gvoid operator delete(gpointer);

private:
	static std::new_handler currentHandler;
	static GMemoryPool<sizeof(ClassT)> pool;
};

// �̰߳�ȫ
// �����䵽�ڴ��
// ������NewHandler
template<typename ClassT, typename LockT>
class GSafeNewT
{
public:
	static gpointer operator new(gsize);
	static gvoid operator delete(gpointer);

private:
	static LockT lock;
};

// �̰߳�ȫ
// �����䵽�ڴ��
// ����NewHandler
template<typename ClassT, typename LockT>
class GSafeNewWithHandlerT
{
public:
	static std::new_handler set_new_handler(std::new_handler p);
	static gpointer operator new(gsize);
	static gvoid operator delete(gpointer);

private:
	static std::new_handler currentHandler;
	static LockT lock;
};

// �̰߳�ȫ
// ���䵽�ڴ��
// ������NewHandler
template<typename ClassT, typename LockT>
class GSafeNewInPoolT
{
public:
	static gpointer operator new(gsize);
	static gvoid operator delete(gpointer);

private:
	static GMemoryPool<sizeof(ClassT)> pool;
	static LockT lock;
};

// �̰߳�ȫ
// ���䵽�ڴ��
// ����NewHandler
template<typename ClassT, typename LockT>
class GSafeNewInPoolWithHandlerT
{
public:
	static std::new_handler set_new_handler(std::new_handler p);
	static gpointer operator new(gsize);
	static gvoid operator delete(gpointer);

private:
	static std::new_handler currentHandler;
	static GMemoryPool<sizeof(ClassT)> pool;
	static LockT lock;
};

#include "gnew.inl"

G_END_NAMESPACE

#endif // _CORE_NEW_H_
