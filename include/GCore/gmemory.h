/// C�����ڴ����

#ifndef _CORE_MEMORY_H_
#define _CORE_MEMORY_H_

#include "gglobal.h"

/****************************************************************************
**
** GNew
**
** @name		GMalloc
** @brief		�����ڴ�
** @param[in]	size {gsize} �����ڴ�Ĵ�С����λ�ֽ�
** @return		{gpointer} �����ڴ���׵�ַ��������ʧ���򷵻�NULL
**
****************************************************************************/
GAPI gpointer GMalloc(gsize size);

/****************************************************************************
**
** GNew
**
** @name		GCalloc
** @brief		�����ڴ�
** @param[in]	n {gsize} �����ڴ�Ĵ�С����λ��
** @param[in]	size {gsize} �����ڴ�Ĵ�С����λ�ֽ�
** @return		{gpointer} �����ڴ���׵�ַ����СΪn*size���ֽڣ�������ʧ���򷵻�NULL
**
****************************************************************************/
GAPI gpointer GCalloc(gsize n, gsize size);

/****************************************************************************
**
** GNew
**
** @name		GRealloc
** @brief		���·����ڴ�
** @param[in]	oldptr {gpointer} ���ڴ��׵�ַ
** @param[in]	newsize {gsize} ���ڴ�Ĵ�С����λ�ֽ�
** @return		{gpointer} �·����ڴ���׵�ַ��������ʧ���򷵻�NULL
**
****************************************************************************/
GAPI gpointer GRealloc(gpointer oldptr, gsize newsize);

/****************************************************************************
**
** GNew
**
** @name		GFree
** @brief		�ͷ��ڴ�
** @param[in]	pfree {gpointer} �ڴ��׵�ַ
**
****************************************************************************/
GAPI gvoid GFree(gpointer pfree);

/****************************************************************************
**
** GNew
**
** @name		GMemCopy
** @brief		�ڴ濽��
** @param[in]	dst {gvoid *} �ڴ濽����Ŀ��
** @param[in]	src {const gvoid *} �ڴ濽������Դ
** @param[in]	size {gsize} �ڴ濽���Ĵ�С����λ�ֽ�
** @return		{gpointer} ���������ڴ���׵�ַ
**
****************************************************************************/
GAPI gpointer GMemCopy(gvoid *dst, const gvoid *src, gsize size);

/****************************************************************************
**
** GNew
**
** @name		GMemMove
** @brief		�ڴ��ƶ�
** @param[in]	dst {gvoid *} �ڴ��ƶ�����׵�ַ
** @param[in]	src {const gvoid *} �ڴ��ƶ�ǰ���׵�ַ
** @param[in]	size {gsize} �ڴ��ƶ��Ĵ�С����λ�ֽ�
** @return		{gpointer} �ڴ��ƶ�����׵�ַ
**
****************************************************************************/
GAPI gpointer GMemMove(gvoid *dst, const gvoid *src, gsize size);

/****************************************************************************
**
** GNew
**
** @name		GMemSet
** @brief		�ڴ�����
** @param[in]	dst {gvoid *} ����ֵ�ڴ���׵�ַ
** @param[in]	value {gbyte} ֵ
** @param[in]	size {gsize} �ڴ����õĴ�С����λ�ֽ�
** @return		{gpointer} �ڴ����ú���׵�ַ
**
****************************************************************************/
GAPI gpointer GMemSet(gvoid *dst, gbyte value, gsize size);

#endif // _CORE_MEMORY_H_
