/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @file	gjsonarray.h
** @brief	Json�������͵Ķ���
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2017-1-3
** @version	1.0
** @see		GJsonArray
**
** Json�����ڷ���������д��
** ����ɰ����������
** {
**	"employees":[
**		{ "firstName":"John", "lastName" : "Doe" },
** 		{ "firstName":"Anna", "lastName" : "Smith" },
** 		{ "firstName":"Peter", "lastName" : "Jones" }
**	]
** }
** ������������У����� "employees" �ǰ���������������飬ÿ������
** ����һ������ĳ�ˣ����պ������ļ�¼��
**
****************************************************************************/

#ifndef _CORE_JSON_ARRAY_H_
#define _CORE_JSON_ARRAY_H_

#include "glist.h"

G_BEGIN_NAMESPACE
class GJsonValue;
class GJsonParserMessage;
G_END_NAMESPACE

G_BEGIN_NAMESPACE

class GAPI GJsonArray
	: public GObject
{
public:
	GJsonArray();
	~GJsonArray();

	gbool Valid() const;

	GString ToString() const;

	gbool Parse(const GString &jsonStr, gsize *cursor = GNULL, GJsonParserMessage *msg = GNULL);

private:
	gvoid Dispose();
	GList<GJsonValue*> m_tJsonValues;
};

G_END_NAMESPACE

#endif // _CORE_JSON_ARRAY_H_