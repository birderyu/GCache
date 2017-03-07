#ifndef _CORE_DATA_INDEX_H_
#define _CORE_DATA_INDEX_H_

#include "GCore/gobject.h"

class GFilter;

// value��һ���޷�������ֵ����ʾ�к�
// value�������ظ�
class GTableDataIndex
{
public:
	enum DATA_INDEX_TYPE
	{
		INDEX_TYPE_ORDER,		// �������������keyֵ�������򣬿���֧��>��>=��<��<=�Ȳ���
		INDEX_TYPE_UNORDER,		// �����������ٶȽϿ죬��֧��=����
	};

public:
	virtual ~GTableDataIndex();

	gbool Valid() const;

	// ����
	gbool Search(const GFilter &sFilter) const;

	gbool Add();
	gbool Remove();

	// �ع�����
	gbool Rebulid();
};

#endif // _CORE_TABLE_INDEX_H_