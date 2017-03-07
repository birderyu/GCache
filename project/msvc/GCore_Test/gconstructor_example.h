#pragma once

#include "gallocator.h"
#include "gconstructor.h"
#include "gstring.h"

gvoid Constructor_Test()
{
	// Ϊ�����������ͷ���һ���ռ�
	gint *p_int = GAllocate<gint>();

	// ����Ĭ�ϵĹ��캯��
	GConstruct<gint>(p_int);

	// �ͷ�һ�������������͵Ŀռ�
	GDeallocate<gint>(p_int);

	// Ϊ�������Ͷ������һ���ռ�
	// ע�⣺���������˿ռ䣬��δ���ù��캯��������ᴦ�ڡ�δ���塱��״̬
	GString *p_str = GAllocate<GString>();

	// �ͷ�һ���������Ͷ���Ŀռ�
	// ע�⣺�����ͷ��˿ռ䣬��δ�����������������ܻ�����ڴ�й©
	GDeallocate<GString>(p_str);

	// �����������ռ�
	gint *p_int_arr = GAllocate<gint>(10);

	// ���·����������ռ�
	p_int_arr = GReallocate<gint>(p_int_arr, 20);

	// �ͷŶ�������ռ�
	GDeallocate<gint>(p_int_arr);
}
