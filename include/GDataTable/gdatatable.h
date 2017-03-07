/// ���ݱ�

#ifndef _DATA_TABLE_TABLE_H_
#define _DATA_TABLE_TABLE_H_

#include "gtableglobal.h"

class GVirtualTable;
class GVirtualTableCursor;

class GAPI GDataTable
{
public:
	class Cursor;
	class ConstCursor;
	class Filter;

public:
	/// ����һ������Ϊtablename�Ŀձ�
	GDataTable(const GString &tablename);

	/// ��������һ�ű�
	GDataTable(const GDataTable &table);

	/// �ƶ�����һ�ű�
	GDataTable(GDataTable &&table);

	/// ����һ�ű�
	~GDataTable();

	/// ������ֵһ�ű�
	GDataTable &operator=(const GDataTable &table);

	/// �ƶ���ֵһ�ű�
	GDataTable &operator=(GDataTable &&table);

	/// ����һ�ű�
	GDataTable Clone() cosnt;

public:
	//******************************************************//
	//************************ֻ������************************//
	//******************************************************//

	/// ��ȡ�ֶεļ���
	GTableFields<GDataTable> Fields() const;

	/// ��ȡ�еļ���
	GTableColumns<GDataTable> Columns() const;

	/// ��ȡ�еļ���
	GTableRows<GDataTable> Rows() const;

	/// �����ֶ�ID��ȡĳһ�ֶ�
	GTableField<GDataTable> FieldAt(gsize field) const;

	/// ������ID��ȡĳһ��
	GTableColumn<GDataTable> ColumnAt(gsize column) const;

	/// ������ID��ȡĳһ��
	GTableRow<GDataTable> RowAt(gsize row) const;

	/// ������ID��ȡĳһ��
	GTableRow<GDataTable> operator[](gsize row) const;

public:
	// ��������
	gbool IndexOn(const GString &fieldname, G_TABLE_INDEX_TYPE type);

public:
	// ��ȡһ��ֻ�����
	ConstCursor GetIterator() const;
	ConstCursor GetConstIterator() const;

	template<typename T> T GetValue(gsize row, gsize col);
	template<typename T> gvoid SetValue(gsize row, gsize col, const T &val);
	template<typename T> gvoid SetValue(gsize row, gsize col, T &&val);

public:
	// ���ݼ���
	Cursor Search(const Filter &filter);
	ConstCursor Search(const Filter &filter) const;
	ConstCursor ConstSearch(const Filter &filter) const;

private:
	gbool GetValue(gsize row, gsize col, gbool &) const;
	gbool GetValue(gsize row, gsize col, gchar &) const;
	gbool GetValue(gsize row, gsize col, gschar &) const;
	gbool GetValue(gsize row, gsize col, guchar &) const;
	gbool GetValue(gsize row, gsize col, gwchar &) const;
	gbool GetValue(gsize row, gsize col, gshort &) const;
	gbool GetValue(gsize row, gsize col, gushort &) const;
	gbool GetValue(gsize row, gsize col, gint &) const;
	gbool GetValue(gsize row, gsize col, guint &) const;
	gbool GetValue(gsize row, gsize col, glong &) const;
	gbool GetValue(gsize row, gsize col, gulong &) const;
	gbool GetValue(gsize row, gsize col, glonglong &) const;
	gbool GetValue(gsize row, gsize col, gulonglong &) const;
	gbool GetValue(gsize row, gsize col, gfloat &) const;
	gbool GetValue(gsize row, gsize col, gdouble &) const;
	gbool GetValue(gsize row, gsize col, gdecimal &) const;
	gbool GetValue(gsize row, gsize col, GString &) const;
	GVariety GetValue(gsize row, gsize col) const;

	gbool SetValue(gsize row, gsize col, gbool);
	gbool SetValue(gsize row, gsize col, gchar);
	gbool SetValue(gsize row, gsize col, gschar);
	gbool SetValue(gsize row, gsize col, guchar);
	gbool SetValue(gsize row, gsize col, gwchar);
	gbool SetValue(gsize row, gsize col, gshort);
	gbool SetValue(gsize row, gsize col, gushort);
	gbool SetValue(gsize row, gsize col, gint);
	gbool SetValue(gsize row, gsize col, guint);
	gbool SetValue(gsize row, gsize col, glong);
	gbool SetValue(gsize row, gsize col, gulong);
	gbool SetValue(gsize row, gsize col, glonglong);
	gbool SetValue(gsize row, gsize col, gulonglong);
	gbool SetValue(gsize row, gsize col, gfloat);
	gbool SetValue(gsize row, gsize col, gdouble);
	gbool SetValue(gsize row, gsize col, gdecimal);
	gbool SetValue(gsize row, gsize col, const GString &);
	gbool SetValue(gsize row, gsize col, GString &&);
	gbool SetValue(gsize row, gsize col, const GVariety &);
	gbool SetValue(gsize row, gsize col, GVariety &&);

public:
	enum { CLASS_CODE = CLASS_CODE_TABLE, };

private:
	GDataTable(GVirtualTable *);
	GVirtualTable *m_pVirtualTable;
};

#endif // _CSCORE_CSDATATABLE_H_
