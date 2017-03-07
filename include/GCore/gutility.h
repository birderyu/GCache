#ifndef _CORE_UTILITY_H_
#define _CORE_UTILITY_H_

#include "gtraits.h"

/// �ƶ�����
template<typename T> typename GRemoveReference<T>::Type &&GMove(T &&t);

/// ����ת������
template<typename T> T&& GForward(typename GRemoveReference<T>::Type &t);
template<typename T> T&& GForward(typename GRemoveReference<T>::Type &&t);

/// ����������������ʹ���ƶ�����
template<typename T> gvoid GSwap(T &a, T &b);

#include "gutility.inl"

#endif // _CORE_UTILITY_H_
