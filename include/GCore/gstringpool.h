/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @author	birderyu
** @contact	https://github.com/birderyu
** @file	gstringpool.h
** @date	2016-12-03
** @brief	�ַ��������͵Ķ���
**
****************************************************************************/

#ifndef _CORE_STRING_POOL_H_
#define _CORE_STRING_POOL_H_

#include "gglobal.h"
#include "gmemorystore.h"
#include "gvector.h"
#include "gmap.h"

/****************************************************************************
**
** gstringpool.h
**
** @class	GStringPool
** @module	GCore
** @brief	�ַ���������
**
**	Ϊ�˴����ַ����ı䳤���ԣ����ö���������ڴ�ṹȥ�洢�ʹ����ַ�����
** 		���ַ������ڲ������ַ�����Ϊ���¼������ͣ��ֱ�������¼��ִ洢��ʽ��
** 1.STRING_POOL_SMALL_STRING�����ַ���������Ϊ1+1+�ַ�����ʵ�ʳ��ȣ�����'\0'������һ
**   ���������ڴ�洢��������֧�ֵ��ַ�������󳤶�Ϊ255��
** 2.STRING_POOL_NORMAL_STRING����ͨ�ַ���������Ϊ1+2+�ַ�����ʵ�ʳ��ȣ�����'\0'����
**   ��һ���������ڴ�洢��֧�ֵ��ַ�������󳤶�Ϊ65535�ͣ�nMaxSize-3���Ľ�С�ߣ�
** 3.STRING_POOL_PART_STRING_START�������ַ����ģ���λ����λ��
**   ����Ϊ1+4+G_POINTER_ADDRESS_SIZE+��ǰ�����ַ����ĳ��ȣ�������֧�ֵ��ַ��������
**   ����Ϊ4294967295��
** 4.STRING_POOL_PART_STRING_MIDDLE�������ַ����ģ���λ���м䣬
**   ����Ϊ1+4+G_POINTER_ADDRESS_SIZE+G_POINTER_ADDRESS_SIZE+��ǰ�����ַ�����
**   ���ȣ�������֧�ֵ��ַ�������󳤶�Ϊ4294967295��
** 5.STRING_POOL_PART_STRING_END�������ַ����ģ���λ�ڽ�β��
**   ����Ϊ1+4+G_POINTER_ADDRESS_SIZE+��ǰ�����ַ����ĳ��ȣ�������֧�ֵ��ַ��������
**   ����Ϊ4294967295��
** 6.STRING_POOL_REFERENCE_STRING�������ַ���������Ϊ1+G_POINTER_ADDRESS_SIZE��
**   �洢��һ���ַ������׵�ַ������ʱ�����´���һ��ȫ�����ĸ�����
**
****************************************************************************/
class GAPI GStringPool
{
	enum TYPE
	{
		STRING_POOL_SMALL_STRING = 0,
		STRING_POOL_NORMAL_STRING,
		STRING_POOL_PART_STRING_START,
		STRING_POOL_PART_STRING_MIDDLE,
		STRING_POOL_PART_STRING_END,
		STRING_POOL_REFERENCE_STRING,
	};

public:
	GStringPool(gsize nInitSzie = 2048, gsize nMaxSize = 10240);
	gpointer Alloc(gsize);
	gvoid Free(gpointer);

private:
	/// ����վ
	GMap<gsize, GVector<gaddress>> m_tRecycle;
	GMemoryStore m_tStore;
};

#endif // _CORE_STRING_POOL_H_