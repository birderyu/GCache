// �����ڴ��
// ʹ��һ�����������ڴ�洢��ṹ

#ifndef _CORE_SERIAL_TABLE_H_
#define _CORE_SERIAL_TABLE_H_

#include "gvirtualtable.h"
#include "GCore/gvector.h"

class GSerialTable 
	: public GVirtualTable
{
public:
	GSerialTable();

private:
	GVector<gbyte> m_tBlock;
	GString m_sTableName;
};

#endif // _CORE_SERIAL_TABLE_H_