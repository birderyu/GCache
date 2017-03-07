// �����ʵ��
#ifndef _CORE_TABLE_EX_H_
#define _CORE_TABLE_EX_H_

#include "GCore/gglobal.h"
#include "GCore/gstring.h"
#include "GGeometry/ggeometry.h"
#include "gtableglobal.h"

// ���
class GVirtualCursor
{
public:
	gbool HasNext() const;
	gvoid Next(); // ������

	gvoid SetValue();
	gbool GetValue() const;
};

// Ԫ����
class GVirtualMeta
{
public:
	GVirtualMeta();

private:
	GString m_sTableName;
};

// ��
class GVirtualTable
{
public:
	virtual ~GVirtualTable() = 0;

public:
	// �û�Ȩ��
	virtual gbool CanEditStructure() const = 0;	// �Ƿ�֧�ֱ༭��ṹ
	virtual gbool CanEditData() const = 0;		// �Ƿ�֧�ֱ༭������
	virtual gbool CanRollBack() const = 0;		// �Ƿ�֧�ֻع�

public:
	// Ԫ��Ϣ��ȡ
	virtual GString				TableName() const = 0;
	virtual gsize				FieldCount() const = 0;
	virtual G_TABLE_FIELD_TYPE	FieldType(gsize) const = 0;
	virtual GString				FieldName(gsize) const = 0;
	virtual GString				FieldText(gsize) const = 0;
	virtual gsize				FieldSize() const = 0;
	virtual gsize				FieldID(const GString &) const = 0;
	virtual gsize				RecordCount() const = 0;
	virtual gbool				HasGeometry() const = 0;
	virtual gsize				GeometryFieldID() const = 0;
	virtual GString				GeometryFieldName() const = 0;

public:
	// ��ṹ�༭
	virtual gvoid SetTableName(const GString &) = 0;
	virtual gvoid StartEditStructure() = 0;
	virtual gvoid SetFieldCount(gsize) = 0;
	virtual gvoid SetFieldType(gsize, G_TABLE_FIELD_TYPE) = 0;
	virtual gvoid SetFieldName(gsize, const GString &) = 0;
	virtual gvoid SetFieldText(gsize, const GString &) = 0;
	virtual gvoid SertFieldLength(gsize, gsize) = 0;
	virtual gvoid EndEditStructure(gbool) = 0;

public:
	// ���ݷ���
	virtual gbool GetValue(gsize row, gsize col, gbool &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, gchar &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, gschar &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, guchar &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, gwchar &) const = 0;
	virtual gbool GetValue(gsize row, gsize col,  gshort &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, gushort &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, gint &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, guint &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, glong &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, gulong &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, glonglong &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, gulonglong &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, gfloat &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, gdouble &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, gdecimal &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, GString &) const = 0;
	virtual GVariety GetValue(gsize row, gsize col) const = 0;
	virtual GGeometryP GetGeometry(gsize row, gsize col) const = 0;

public:
	// ���ݱ༭
	virtual gbool StartEditData() = 0;
	virtual gbool SetRecordCount(gsize) = 0;
	virtual gbool SetValue(gsize row, gsize col, gbool) = 0;
	virtual gbool SetValue(gsize row, gsize col, gchar) = 0;
	virtual gbool SetValue(gsize row, gsize col, gschar) = 0;
	virtual gbool SetValue(gsize row, gsize col, guchar) = 0;
	virtual gbool SetValue(gsize row, gsize col, gwchar) = 0;
	virtual gbool SetValue(gsize row, gsize col, gshort) = 0;
	virtual gbool SetValue(gsize row, gsize col, gushort) = 0;
	virtual gbool SetValue(gsize row, gsize col, gint) = 0;
	virtual gbool SetValue(gsize row, gsize col, guint) = 0;
	virtual gbool SetValue(gsize row, gsize col, glong) = 0;
	virtual gbool SetValue(gsize row, gsize col, gulong) = 0;
	virtual gbool SetValue(gsize row, gsize col, glonglong) = 0;
	virtual gbool SetValue(gsize row, gsize col, gulonglong) = 0;
	virtual gbool SetValue(gsize row, gsize col, gfloat) = 0;
	virtual gbool SetValue(gsize row, gsize col, gdouble) = 0;
	virtual gbool SetValue(gsize row, gsize col, gdecimal) = 0;
	virtual gbool SetValue(gsize row, gsize col, const GString &) = 0;
	virtual gbool SetValue(gsize row, gsize col, const GVariety &) = 0;
	virtual gbool SetGeometry(gsize row, gsize col, const GGeometryP &) = 0;
	virtual gbool EndEditData(gbool) = 0;

private:
	GVirtualMeta *m_pMeta;
};

#endif //_CORE_TABLE_EX_H_