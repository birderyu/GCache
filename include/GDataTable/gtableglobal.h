#ifndef _CORE_TABLE_GLOBAL_H_
#define _CORE_TABLE_GLOBAL_H_

#include "GCore/gobject.h"
#include "GCore/gvariety.h"
#include "GCore/gdynamicarray.h"
#include "gtableaction.h"

class GDataTable;
class GDataView;
template<typename TableT> class GTableCell;
template<typename TableT> class GTableField;
template<typename TableT> class GTableFields;
template<typename TableT> class GTableRow;
template<typename TableT> class GTableRows;
template<typename TableT> class GTableColumn;
template<typename TableT> class GTableColumns;

// ������
enum G_TABLE_TYPE
{
	TABLE_TYPE_SERIAL,		// �����ڴ��Ĭ�ϣ�
	TABLE_TYPE_SIMPLE,		// ���ڴ��
	TABLE_TYPE_VARIANT,		// �������ͱ�
	TABLE_TYPE_OBJECT,		// �����
};

// ���ֶ�����
enum G_TABLE_FIELD_TYPE
{
	TABLE_FIELD_TYPE_ILLEGAL = -1,
	TABLE_FIELD_TYPE_BOOL,
	TABLE_FIELD_TYPE_CHAR,
	TABLE_FIELD_TYPE_SCHAR,
	TABLE_FIELD_TYPE_UCHAR,
	TABLE_FIELD_TYPE_WCHAR,
	TABLE_FIELD_TYPE_SHORT,
	TABLE_FIELD_TYPE_USHORT,
	TABLE_FIELD_TYPE_INT,
	TABLE_FIELD_TYPE_UINT,
	TABLE_FIELD_TYPE_LONG,
	TABLE_FIELD_TYPE_ULONG,
	TABLE_FIELD_TYPE_LONGLONG,
	TABLE_FIELD_TYPE_ULONGLONG,
	TABLE_FIELD_TYPE_FLOAT,
	TABLE_FIELD_TYPE_DOUBLE,
	TABLE_FIELD_TYPE_LONGDOUBLE,
	TABLE_FIELD_TYPE_DATETIME,	// ������
	TABLE_FIELD_TYPE_BYTES,		// �ֽ�����
	TABLE_FIELD_TYPE_STRING,	// �ַ���
	TABLE_FIELD_TYPE_WSTRING,	// ���ַ���
	TABLE_FIELD_TYPE_GEOMETRY,	// �����ֶ�
	TABLE_FIELD_TYPE_OBJECT,	// Object����
};

// ����������
enum G_TABLE_INDEX_TYPE
{
	TABLE_INDEX_TYPE_NULL,		// ������
	TABLE_INDEX_TYPE_UNORDER,	// ��������
	TABLE_INDEX_TYPE_ORDER,		// ��������
	TABLE_INDEX_TYPE_SPATIAL,	// �ռ�����
};

#endif // _CORE_TABLE_GLOBAL_H_