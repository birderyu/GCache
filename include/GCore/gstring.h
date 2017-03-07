/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @author	birderyu
** @contact	https://github.com/birderyu
** @file	gstring.h
** @date	2016-12-03
** @brief	�ַ������͵Ķ���
**
****************************************************************************/

#ifndef _CORE_STRING_H_
#define _CORE_STRING_H_

#include "gstructure.h"
#include "gobject.h"
#include "gseries.h"

class GStringList;

/****************************************************************************
**
** gstring.h
**
** @class	GString
** @module	GCore
** @brief	�ַ�������
**
****************************************************************************/
class GAPI GString final 
	: public GListT<GString>
	, virtual public GArray<gchar>
	, virtual public GObject
{
	friend class GVariety;
	friend GAPI GString operator+(const GString &s1, const GString &s2);
	friend GAPI gbool operator==(const GString &s1, const GString &s2);
	friend GAPI gbool operator!=(const GString &s1, const GString &s2);
	friend GAPI gbool operator>(const GString &s1, const GString &s2);
	friend GAPI gbool operator>=(const GString &s1, const GString &s2);
	friend GAPI gbool operator<(const GString &s1, const GString &s2);
	friend GAPI gbool operator<=(const GString &s1, const GString &s2);

public: // ��������
	enum { CLASS_CODE = CLASS_CODE_STRING, };
	static const gsize MAX_SIZE = GListT<GString>::MAX_SIZE;
	static const gsize NULL_POS = GListT<GString>::NULL_POS;

public: // ��̬����
	static GString Number(gsmall num, gint nBase = 10);
	static GString Number(gusmall num, gint nBase = 10);
	static GString Number(gshort num, gint nBase = 10);
	static GString Number(gushort num, gint nBase = 10);
	static GString Number(gint num, gint nBase = 10);
	static GString Number(guint num, gint nBase = 10);
	static GString Number(glong num, gint nBase = 10);
	static GString Number(gulong num, gint nBase = 10);
	static GString Number(glonglong num, gint nBase = 10);
	static GString Number(gulonglong num, gint nBase = 10);
	static GString Number(gfloat num, gint nBase = 10);
	static GString Number(gdouble num, gint nBase = 10);
	static GString Number(gdecimal num, gint nBase = 10);

public: // ���췽��
	GString();
	GString(gchar c);
	GString(const gchar *str);
	GString(const GString &str);
	GString(GString &&str);

public: // Array��Ϊ
	gsize Size() const;
	gbool IsEmpty() const;
	gchar &GetAt(gsize pos);
	const gchar &GetAt(gsize pos) const;
	gchar *CursorAt(gsize);
	const gchar *CursorAt(gsize) const;
	gvoid Resize(gsize size);
	gvoid Reserve(gsize size);
	gbool StartWith(gchar c) const;
	gbool EndWith(gchar c) const;
	gvoid Append(const GString &str);
	gvoid Append(GString &&str);

public: // �ַ�����Ϊ
	gbool Equals(const GString &, gbool bIsSensitive = true) const;
	GString Trim() const;
	GString TrimLeft() const;
	GString TrimRight() const;
	GString ToUpper() const;
	GString ToLower() const;
	gcstring CString() const;
	GString &Replace(const GString &from, const GString &to, gbool bIsSensitive = true);
	// bIgnoreEmpty���Ƿ���Կո�; bIsSensitive����Сд�Ƿ�����
	GStringList Split(const GString &sSep, gbool bIgnoreEmpty = false, gbool bIsSensitive = true) const;
	gsize Find(gchar c, gsize start = 0, gbool bIsSensitive = true) const;
	gsize Find(const GString &str, gsize start = 0, gbool bIsSensitive = true) const;
	GString SubString(gsize start, gsize length) const;

public: // ����ת��
	gsmall ToSmall(gbool *bIsOk = GNULL) const;
	gusmall ToUSmall(gbool *bIsOk = GNULL) const;
	gshort ToShort(gbool *bIsOk = GNULL) const;
	gushort ToUShort(gbool *bIsOk = GNULL) const;
	gint ToInt(gbool *bIsOk = GNULL) const;
	guint ToUInt(gbool *bIsOk = GNULL) const;
	glong ToLong(gbool *bIsOk = GNULL) const;
	gulong ToULong(gbool *bIsOk = GNULL) const;
	glonglong ToLongLong(gbool *bIsOk = GNULL) const;
	gulonglong ToULongLong(gbool *bIsOk = GNULL) const;
	gfloat ToFloat(gbool *bIsOk = GNULL) const;
	gdouble ToDouble(gbool *bIsOk = GNULL) const;
	glongdouble ToLongDouble(gbool *bIsOk = GNULL) const;

public: // Object
	const GObject *Boxing() const;
	guint ClassCode() const;
	GString ToString() const;

public: // ���������
	GString &operator=(const GString &str);
	GString &operator=(GString &&sStr);
	GString &operator+=(const GString &sStr);
	const gchar &operator[](gsize) const;
	gchar &operator[](gsize);

private: // ˽�з���
	GString(const gchar *pStr, gsize size);
	GString(const GStringData &str);
	GString(GStringData &&str);

private: // ˽�г�Ա
	GStringData m_tString;
};

/// �����
GAPI GString operator+(const GString &s1, const GString &s2);
GAPI gbool operator==(const GString &s1, const GString &s2);
GAPI gbool operator!=(const GString &s1, const GString &s2);
GAPI gbool operator>(const GString &s1, const GString &s2);
GAPI gbool operator>=(const GString &s1, const GString &s2);
GAPI gbool operator<(const GString &s1, const GString &s2);
GAPI gbool operator<=(const GString &s1, const GString &s2);

typedef GString GAString;

#endif // _CORE_STRING_H_
