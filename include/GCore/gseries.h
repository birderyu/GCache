/// Ϊ��ʹ�ô��ṹ��String�����Ӹ�Ч�����������ݽṹGSeries
/// GSeries��Ϊ���д��ṹ���ںˣ�GString��GWString��GBytes����ӵ�������ص㣺
/// 1��Ϊ��֧�ִ��ڴ󲿷�ʹ�ó������䳤�ȶ�����֧��
/// 2��Ϊ��֧�ִ��ڴ󲿷�ʱ����ʵ����ֻ���������龰��֧��COW��copy-on-write��дʱ��������
#ifndef _CORE_ARRAY_DATA_H_
#define _CORE_ARRAY_DATA_H_

#include "garray.h"

#define G_ARRAY_DATA_LOCAL_TYPE		0
#define G_ARRAY_DATA_GLOBAL_TYPE	1
#define G_ARRAY_DATA_REFERENCE_TYPE	2

/// ��ʹ��һ���������洢����ʱ�����������������´���
/// Ϊ����������ĳ�ʼ�����ݣ���������С��MIN_SIZEʱ�����ݴ洢�ڱ��ؿռ��ϣ���֮��ȫ�ֿռ��п����ڴ�
/// ������������MIN_SIZEʱ������Ԥ����һЩ������ڴ棬ʵ���ڴ�Ĵ�С�洢��m_pArray��ǰ��λ�ռ���
/// m_nType���Ա�ʾ��ǰ����
template<typename T, 
	gsize LOCAL_SIZE,
	gbool HAS_END_FLAG, 
	T END_FLAG>
class GSeries
{
public:
	static const gsize MIN_CAPACITY = HAS_END_FLAG ? (LOCAL_SIZE - 1) : LOCAL_SIZE;
	static_assert(MIN_CAPACITY > 0, "MIN_CAPACITY must greater than zero.");

public:
	GSeries(gsize capacity = 0);
	GSeries(const T *copy_arr, gsize copy_size, gbool is_reference = false);
	GSeries(const GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &arr);
	GSeries(GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &&arr);
	~GSeries();

	gsize Size() const;
	gsize Capacity() const;

	gbool IsEmpty() const;

	gvoid Resize(gsize size);
	gvoid Reserve(gsize capacity);

	const T &ConstGetAt(gsize pos) const;
	const T &GetAt(gsize pos) const;
	T &GetAt(gsize pos);

	const T *ConstCursorAt(gsize pos) const;
	const T *CursorAt(gsize pos) const;
	T *CursorAt(gsize pos);

	const T *ConstStart() const;
	const T *Start() const;
	T *Start();

	gvoid SetAt(gsize pos, const T &data);
	gvoid SetAt(gsize pos, T &&data);

	// ������飬���ͷ��ڴ�
	gvoid Clear();

	// �������鲢�������ÿ�
	gvoid Dispose();

	// ��һ��������ӵ�ĩβ
	gvoid Append(const GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &series);
	gvoid Append(GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &&series);

	GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &operator=(const GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &arr);
	GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &operator=(GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &&arr);
	const T &operator[](gsize pos) const;
	T &operator[](gsize pos);

private:
	gvoid Free(); // ��������

	gbool IsReference() const;

	// ����������ת����ֵ����
	gvoid ToValue(gsize capacity);

	T *m_pStart;
	gsize m_nSize;
	gsize m_nCapacity;
	union
	{
		T  m_tArray[LOCAL_SIZE];
		T *m_pArray;
	};
	gbyte m_nType;
};

#include "gseries.inl"

GAPI typedef GSeries<gbyte, 4, false, 0>				GBytesData;
GAPI typedef GSeries<gchar, 8, true, '\0'>	GStringData;
GAPI typedef GSeries<gwchar, 4, true, L'\0'>	GWStringData;

#undef G_ARRAY_DATA_REFERENCE_TYPE
#undef G_ARRAY_DATA_GLOBAL_TYPE
#undef G_ARRAY_DATA_LOCAL_TYPE

#endif // _CORE_ARRAY_DATA_H_