/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @file	gconstructor.h
** @brief	��������
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2017-1-24
** @version	0.1
**
** ��������������
** ������������construct
** �������������destruct
** ���й�����������ϸ��Ϊ��
** Ĭ�Ϲ��������
** �������Ĺ��������
** �������������copy construct
** �ƶ����������move construct
**
****************************************************************************/
#ifndef _CORE_CONSTRUCTOR_H_
#define _CORE_CONSTRUCTOR_H_

#include "gglobal.h"
#include "gtraits.h"

template <typename ClassT> gvoid GConstruct(ClassT *ptr);
template <typename ClassT> gvoid GConstruct(ClassT *ptr, const ClassT &copyable);
template <typename ClassT> gvoid GConstruct(ClassT *ptr, ClassT &&moveable);
template <typename ClassT> gvoid GDestruct(ClassT *ptr);

template <typename ClassT> gvoid GDefaultConstruct(ClassT *ptr);
template <typename ClassT> gvoid GCopyConstruct(ClassT *ptr, const ClassT &copyable);
template <typename ClassT> gvoid GMoveConstruct(ClassT *ptr, ClassT &&moveable);

#include "gconstructor.inl"

#endif // _CORE_CONSTRUCTOR_H_