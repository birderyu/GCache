// ����ͼ
// ����ͼ����һ��ʵ�ʴ��ڵı�����������ĳһ�ű�Ĳ�������

#ifndef _CORE_TABLE_VIEW_H_
#define _CORE_TABLE_VIEW_H_

#include "gtableglobal.h"

class GDataTable;
class GVirtualTable;

class GAPI GDataView
	: GTableActionT<GDataView>
{
public:
	GDataView(GDataTable &, GSizeArray *rows, GSizeArray *columns);

private:
	GVirtualTable *m_pVirtualTable;
	GSizeArray *m_pRows;
	GSizeArray *m_pColumns;
};

#endif // _CORE_TABLE_VIEW_H_