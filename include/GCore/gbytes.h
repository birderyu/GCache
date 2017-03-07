/// �ֽ����� byte array��bytes��
#ifndef _CORE_BYTES_H_
#define _CORE_BYTES_H_

#include "gobject.h"
#include "gstructure.h"
#include "gseries.h"

class GByteBuffer;

class GAPI GBytes final
	: public GListT<GBytes>
	, public GArray<gbyte>
	, public GObject
{
	friend class GByteBuffer;

public:
	/// ��һ����������ֵת�����ֽ����飬���ظ�ֵ��ռ���ֽ���
	/// �ֽ������Ǵ�˵ģ�����ֱ�����������ֽ���
	template<typename T> static gsize ArithmeticToBytes(const T *val, gbyte *bytes);

	/// ��һ���ֽ�����ת������������ֵ�����ظ�ֵ��ռ���ֽ���
	/// �ֽ������Ǵ�˵�
	template<typename T> static gsize BytesToArithmetic(const gbyte *bytes, T *val);

public:
	GBytes();
	GBytes(const gbyte *bytes, gsize size);
	GBytes(const GBytes &bytes);
	GBytes(GBytes &&bytes);
	explicit GBytes(const GByteBuffer &bytes);
	explicit GBytes(GByteBuffer &&bytes);

	gvoid Reserve(gsize capacity);
	gvoid Resize(gsize size);
	gvoid Clear();
	gvoid Dispose();

	gbool IsEmpty() const;
	gsize Size() const;
	gsize Capacity() const;

	gbyte &GetAt(gsize);
	const gbyte &GetAt(gsize) const;
	gbyte *CursorAt(gsize pos);
	const gbyte *CursorAt(gsize pos) const;

	const gbyte *Head() const;
	gbyte *Head();
	const gbyte *Tail() const;
	gbyte *Tail();

	GBytes &operator=(const GBytes &bytes);
	GBytes &operator=(GBytes &&bytes);
	GBytes &operator=(const GByteBuffer &bytes);
	GBytes &operator=(GByteBuffer &&bytes);
	gbyte &operator[](gsize);
	const gbyte &operator[](gsize) const;

private:
	GBytesData m_tBytes;
};

#include "gbytes.inl"

#endif // _CORE_BYTES_H_