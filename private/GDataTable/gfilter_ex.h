#ifndef _CORE_FILTER_EX_H_
#define _CORE_FILTER_EX_H_

#include "GCore/gdynamicarray.h"
#include "GCore/gvariety.h"
#include "GCore/gstring.h"

class GFilter_Ex
{
public:
	struct GFilterData;

protected:
	// ��������
	enum G_UNION_TYPE
	{
		UNION_TYPE_ERROR = -1,
		UNION_TYPE_SINGLE = 0,	// �����Ϲ�ϵ��ֻ��һ��������
		UNION_TYPE_AND,			// �߼���
		UNION_TYPE_OR,			// �߼���
	};

	/// �Ƚ�����
	enum G_COMPARE_TYPE
	{
		COMPARE_TYPE_ERROR = -1,		// �Ƿ��ıȽ�����
		COMPARE_TYPE_EQUAL,			// ����
		COMPARE_TYPE_LESS,			// С��
		COMPARE_TYPE_LESS_EQUAL,	// С�ڵ���
		COMPARE_TYPE_GREATER,		// ����
		COMPARE_TYPE_GREATER_EQUAL,	// ���ڵ���
		COMPARE_TYPE_NOTEQUAL,		// ������
		COMPARE_TYPE_LIKE,			// ģ���Ƚ�
	};

private:
	class GFilterCell
	{
	public:
		GFilterCell();
		GFilterCell(const GFilterCell &tCell);
		virtual ~GFilterCell();
		gbool SetFilter(const GString &sFilter);
		gbool IsValid() const;
		gbool Release();
		GString ToString() const;
		GFilterCell &operator=(const GFilterCell &tCell);

	private:		
		GString m_sFieldName;
		GVariety m_tFieldValue;
		G_COMPARE_TYPE m_emCompareType;
	};

	struct GFilterData
	{
		GFilterData();
		GFilterData(const GFilterData &tData);
		gbool SetFilter(const GString &sFilter);
		gbool IsValid() const;
		GString ToString() const;
		gbool Release();
		GFilterData &operator=(const GFilterData &tData);

	private:
		GDynamicArray<GFilterData> m_tChildren;
		GFilterCell m_tCell;
		G_UNION_TYPE m_emUnionType;
	};

	struct GFilterParse
	{
		// �����������ַ���
		static gbool ParseFilter(const GString &sFilter, G_UNION_TYPE &emUnionType, 
			GDynamicArray<GFilterData> &tData, GFilterCell &tCell);

		// �����������ַ�����Ԥ�����ַ�������"OID = 1; NAME = 'ABC'"����Ϊ"OID = 1 AND NAME = ABC"
		static gbool ParseFilter_PreParseFilter(GString &sFilter);
		// �����������ַ������������ϵķ��ţ���ȡ���ϵ�ö��ֵ
		static gbool ParseFilter_ParseUnionType(const GString &sUnion, G_UNION_TYPE &emUnionType);
		// �����������ַ������ж������Ƿ�Ϸ�
		static gbool ParseFilter_IsBracketLegal(const GString &sFilter);
		// �����������ַ������Ƴ���ʼ��Ч�����ţ���"(OID = 1 AND TYPE = 2)"����Ϊ"OID = 1 AND TYPE = 2"
		static gbool ParseFilter_TrimBracket(GString &sFilter);
		// �����������ַ�����ָ�����Ϸ���ȥ�ֽ�����
		// ֻ�ֽ��һ������
		// ��"(OID = 1 OR TYPE = 2) AND (NAME = ABC AND (CITY = 'BJ' OR SIZE = 100))"
		// ��Ϊ"(OID = 1 OR TYPE = 2)" �� "(NAME = ABC AND (CITY = 'BJ' OR SIZE = 100))"
		static gbool ParseFilter_BreakUpBracketOnOneLevel(const GString &sFilter, const GString &sUnion, GStringList &tFilterList);
		// 
		static gbool ParseFilter_ParseCompareType(const GString &sCompare, G_COMPARE_TYPE &emCompareType);
		static gbool GetCompareString(G_COMPARE_TYPE emCompareType, GString &sCompare);
		static gbool GetUnionString(G_UNION_TYPE emUnionType, GString &sUnion);
	};

public:
	GFilter_Ex(const GString &sFilter);
	GFilter_Ex(const GFilter_Ex &tFilter);
	virtual ~GFilter_Ex();
	virtual gbool SetFilter(const GString &sFilter);
	virtual GFilter_Ex &operator=(const GFilter_Ex &tFilter);

	gbool IsValid() const;
	GString ToString() const;

private:
	gbool Initialize();
	gbool Release();
	GFilterData m_tFilterData;

private:
	static GStringList m_tUnionSymbols;
	static gbool m_bInitializeUnionSymbols;

	static GStringList m_tCompareSymbols;
	static gbool m_bInitializeCompareSymbols;
};

#endif // _CORE_FILTER_EX_H_