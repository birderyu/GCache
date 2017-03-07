// ʹ������ʵ�ֵĶ���
#ifndef _CORE_ARRAY_QUEUE_H_
#define _CORE_ARRAY_QUEUE_H_

#include "gqueue.h"
#include "gdynamicarray.h"

#define G_QUEUE_DEFAULT_CAPACITY 1024

template <typename DataT>
class GArrayQueue
	: public GQueue<DataT>
{
public:
	//���캯��
	GArrayQueue(gsize capacity)
		: m_nFront(0)
		, m_nRear(0)
		, m_tArray(capacity)
	{
		
	}
	//��������
	~GArrayQueue()
	{
		
	}

	gvoid Clear();
	gvoid Dispose();

	DataT front();          //����Ԫ��
	bool pop();         //����
	bool push(T t);     //���
	gbool IsEmpty() const;
	int Size();         //���еĴ�С

private:
	gsize m_nFront; // ����
	gsize m_nRear;	// ��β
	GDynamicArray<DataT> m_tArray;
};

#include "garrayqueue.inl"

#undef G_QUEUE_DEFAULT_CAPACITY

template <typename DataT>
DataT GArrayQueue<DataT>::front()
{
	if (m_nFront != m_nRear)
		return m_tArray[m_nFront];
};

template <typename DataT>
bool GArrayQueue<DataT>::pop()
{
	if (m_nFront == m_nRear)
		return false;
	m_nFront = (m_nFront + 1) % maxsize;
	return true;
};

template <typename DataT>
bool GArrayQueue<DataT>::push(T t)
{
	if ((m_nRear + 1) % maxsize == m_nFront)
		return false;
	m_tArray[m_nRear] = t;
	m_nRear = (m_nRear + 1) % maxsize;
	return true;
};

template <typename DataT>
gbool GArrayQueue<DataT>::IsEmpty() const
{
	if (m_nFront == m_nRear)
		return true;
	else
		return false;
};

template <typename DataT>
int GArrayQueue<DataT>::Size()
{
	return (m_nRear - m_nFront + maxsize) % maxsize;
};

#endif // _CORE_ARRAY_QUEUE_H_
