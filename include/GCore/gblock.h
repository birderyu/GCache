// GBlock��һ��byte����
// ��Block�޷������ڴ�ʱ�����ܳ�һ���쳣

#ifndef _CORE_BLOCK_H_
#define _CORE_BLOCK_H_

#include "gglobal.h"
#include "gstructure.h"

class GAPI GBlock
	: public GListT<GBlock>
{
public:
	// ��λ���ֽ�
	GBlock(gsize nSize = 0);
	GBlock(const GBlock &);
	GBlock(GBlock &&);
	~GBlock();
	
	gsize Size() const;	// �ڴ��ܳ���
	gbyte *CursorAt(gsize nCursor);
	const gbyte *CursorAt(gsize nCursor) const;

	gvoid Resize(gsize nSize);

	gbyte &GetAt(gsize);
	const gbyte &GetAt(gsize) const;

	gbyte &operator[](gsize);
	const gbyte &operator[](gsize) const;

private:
	// Not Safe
	GBlock(gbyte *, gsize, gbool bAutoRelease = false);

	gbool Valid() const;

	gvoid Initialize();
	gvoid Free();

	// ����ĳ���
	gsize m_nSize;

	// ��һλ�洢AutoRelease
	// �ڶ�λ�洢�Ƿ���ָ�����ͣ�0����ָ�룻1��ָ��
	gbyte m_tConfig[2];

	union
	{
		gbyte m_tBlock[G_POINTER_ADDRESS_SIZE];
		gbyte *m_pBlock;
	};
};

#endif // _CORE_BLOCK_H_