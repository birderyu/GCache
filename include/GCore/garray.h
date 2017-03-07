#ifndef _CORE_ARRAY_H_
#define _CORE_ARRAY_H_

#include "gobject.h"
#include "gserialize.h"
#include "gstructure.h"
#include "gallocator.h"
#include "gconstructor.h"

template <typename DataT>
class GArray
	: public GListT<GArray<DataT>>
	, virtual public GObject
{
public:
	/// ��̬����������һ������Ϊsize�����飬�����ε���ÿһ��Ԫ�ص�Ĭ�Ϲ��캯��
	static DataT *CreateArray(gsize size) noexcept(false);

	/// ��̬����������һ������Ϊsize�����飬������ʹ��copyableȥ��ʼ�������е�ÿһ��Ԫ��
	static DataT *CreateArray(gsize size, const DataT &copyable) noexcept(false);

	/// ��̬����������һ������Ϊcopy_size�����飬����copy_arr�ĵ�copy_start���copy_sizeԪ��ȥ��ʼ���µ�����
	static DataT *CreateArray(const DataT *copy_arr, gsize copy_start, gsize copy_size) noexcept(false);

	/// ��̬����������һ������Ϊsize�����飬����copy_arr�ĵ�copy_start���copy_sizeԪ��ȥ��ʼ���µ�����ĵ�start��ʼ��copy_size��Ԫ��
	/// �����Ԫ��ʹ��Ĭ�ϵĹ��캯������
	static DataT *CreateArray(gsize size, gsize start, const DataT *copy_arr, gsize copy_start, gsize copy_size) noexcept(false);

	/// ��̬������������old_arr������Ԫ����Ŀ��old_size����Ϊnew_size
	/// �������鲻���ڣ�old_arr == GNULL && old_size == 0�����ᴴ��һ������Ϊnew_size���µ�����
	/// �ڵ�����С�Ĺ����У����µ�����Ԫ����Ŀ����ԭ����Ŀ���ᴴ���µ�Ԫ�أ���֮���в���Ԫ�ر�����
	/// �ڵ�����С�Ĺ����У������ȵ����ƶ�����
	static DataT *ResizeArray(DataT *old_arr, gsize old_size, gsize new_size) noexcept(false);

	/// ��̬������������old_arr������Ԫ����Ŀ��old_size����Ϊnew_size
	/// �ڵ�����С�Ĺ����У����µ�����Ԫ����Ŀ����ԭ����Ŀ������copyableȥ��ʼ���µ�Ԫ�أ���֮���в���Ԫ�ر�����
	/// �ڵ�����С�Ĺ����У������ȵ����ƶ�����
	static DataT *ResizeArray(DataT *old_arr, gsize old_size, gsize new_size, const DataT &copyable) noexcept(false);

	/// ��̬������������old_arr������Ԫ����Ŀ����Ϊnew_size
	/// �ڵ�����С�Ĺ����У�������ԭ������Ĵ�old_startλ��ʼ��old_size��Ԫ�أ����õ�������ĵ�new_startλ
	/// �ڵ�����С�Ĺ����У������ȵ����ƶ�����
	static DataT *ResizeArray(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start) noexcept(false);

	/// ��̬������������old_arr������Ԫ����Ŀ����Ϊnew_size
	/// �ڵ�����С�Ĺ����У�������ԭ������Ĵ�old_startλ��ʼ��old_size��Ԫ�أ����õ�������ĵ�new_startλ
	/// �ڵ�����С�Ĺ����У��´���������Ԫ�أ���ʹ��copyable���г�ʼ��
	/// �ڵ�����С�Ĺ����У������ȵ����ƶ�����
	static DataT *ResizeArray(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const DataT &copyable) noexcept(false);

	/// ��̬�������Ƴ������е�ĳһλԪ�أ�����Ƴ�����Ԫ�ص�����������
	static DataT *RemoveArrayElementAt(DataT *arr, gsize size, gsize pos) noexcept(false);

	/// ��̬����������һ�����飬�����ε���ÿһ��Ԫ�ص���������
	static gvoid DestoryArray(DataT *arr, gsize size) noexcept;

	/// ��̬���������ε���ÿһ��Ԫ�ص��������������ͷ��ڴ�
	static gvoid ClearArray(DataT *arr, gsize size) noexcept;

	/// ��̬������������copy_arr�����ݿ�����arr��
	/// ���뱣֤copy_arr���ٰ�����size��Ԫ��
	static gvoid CopyArrayFrom(DataT *arr, gsize size, const DataT *copy_arr) noexcept(false);

	/// ��̬������������copy_arr�����ݿ�����arr��
	/// �ڿ����Ĺ����У�arr�ĵ�ַ�ͳ��Ȼ�����copy_arr�Ĳ�ͬ���ı�
	/// ��size��copy_size��һ�£������·����ڴ�
	/// ���ؿ���֮������ݵĵ�ַ
	static DataT *CopyArrayFrom(DataT *arr, gsize size, const DataT *copy_arr, gsize copy_size) noexcept(false);

public:
	enum { CLASS_CODE = CLASS_CODE_ARRAY, };

public:
	virtual ~GArray() = 0 {}

	virtual gsize Size() const = 0;
	virtual gbool IsEmpty() const = 0;

	//virtual DataT &ConstGetAt(gsize pos) = 0;
	virtual DataT &GetAt(gsize pos) = 0;
	virtual const DataT &GetAt(gsize pos) const = 0;

	//virtual DataT *ConstCursorAt(gsize pos) = 0;
	virtual DataT *CursorAt(gsize pos) = 0;
	virtual const DataT *CursorAt(gsize pos) const = 0;

	virtual DataT &operator[](gsize pos) = 0;
	virtual const DataT &operator[](gsize pos) const = 0;

	gbool Contains(const DataT &) const;
	gsize FirstIndexOf(const DataT &) const;
	gsize LastIndexOf(const DataT &) const;
	gsize CountOf(const DataT &) const;

	///
	virtual guint ClassCode() const;
};

#include "garray.inl"

#endif // _CORE_ARRAY_H_