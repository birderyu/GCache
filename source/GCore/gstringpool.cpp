#include "gstringpool.h"

GStringPool::GStringPool(gsize nInitSzie, gsize nMaxSize)
:m_tStore(nInitSzie, nInitSzie)
{

}

gpointer GStringPool::Alloc(gsize size)
{
	GMap<gsize, GVector<gaddress>>::ConstIterator citer = m_tRecycle.ConstFind(size);
	if (citer != m_tRecycle.ConstEnd())
	{
		// TODO�����ڴ����վ�л�ȡһ���ڴ�
	}
	return m_tStore.Alloc(size);
}

gvoid GStringPool::Free(gpointer)
{

}