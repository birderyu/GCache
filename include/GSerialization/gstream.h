// ��
#ifndef _CORE_STREAM_H_
#define _CORE_STREAM_H_

#include "GCore/gglobal.h"

class GAPI GStream
{
public:
	virtual ~GStream() = 0;
	virtual gbool Valid() const = 0;

	// �Ƿ��ǳ����
	virtual gbool IsAbstract() const = 0;
	// �Ƿ��Ƕ����ƣ�����Ϊ�ı�
	virtual gbool IsBinary() const = 0;
	// �Ƿ��л���
	virtual gbool HasBuffer() const = 0;
	// �Ƿ����ļ�
	virtual gbool HasFile() const = 0;
	// �Ƿ���������
	virtual gbool IsInput() const = 0;
	// �Ƿ��������
	virtual gbool IsOutput() const = 0;
};

#endif // _CORE_STREAM_H_
