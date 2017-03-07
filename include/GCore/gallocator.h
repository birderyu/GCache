/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @file	gallocator.h
** @brief	�ռ������
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2017-1-24
** @version	0.1
**
** ��������������
** �����ڴ������allocate
** �ͷ��ڴ������deallocate
**
****************************************************************************/
#ifndef _CORE_ALLOCATOR_H_
#define _CORE_ALLOCATOR_H_

#include "gmemory.h"
#include <new>

template <typename ClassT> ClassT *GAllocate(gsize n = 1) noexcept(false);
template <typename ClassT> gvoid GDeallocate(ClassT *ptr) noexcept;
template <typename ClassT> ClassT *GReallocate(ClassT *oldptr, gsize newsize) noexcept(false);

#include "gallocator.inl"

#endif // _CORE_ALLOCATOR_H_
