// ���͵ļ�ԭ�Ӳ���
#ifndef _CORE_ATOM_H_
#define _CORE_ATOM_H_

#include "gglobal.h"

/// ԭ�Ӳ���
/// ��֧��guint��gulong��gulonglong�Լ���֮�ȼ����ͣ���guint32��guint64����ԭ�Ӳ���
class GAtom
{
public:
	/// CAS������compare-and-swap��
	/// ��target��ֵ��comperand�Ƚϣ�����ȣ���target��ֵ�滻Ϊexchange������������
	/// �������ɹ����򷵻�true�����򷵻�false
	/// 
	/// ����windows��û���ṩ���ز������͵�cas�����������windows����ʵ���ȵ�����ValuedCompareAndSwap���ٱȽϽ��
	/// Ч�������ValuedCompareAndSwap�����½�
	template<typename T> static gbool CompareAndSwap(T *target, T comperand, T exchange);

	/// ����ֵ��CAS������valued compare-and-swap��
	/// ��target��ֵ��comperand�Ƚϣ�����ȣ���target��ֵ�滻Ϊexchange������������
	/// ����target֮ǰ��ֵ
	template<typename T> static T ValuedCompareAndSwap(T *target, T comperand, T exchange);

	/// ԭ������������������ֵ���൱��++*var
	template<typename T> static T IncrementAndFetch(T *target);

	/// ԭ���Լ�������������ֵ���൱��--*var
	template<typename T> static T DecrementAndFetch(T *target);

	/// ԭ���������������ؾ�ֵ���൱��*var++
	template<typename T> static T FetchAndIncrement(T *target);

	/// ԭ���Լ����������ؾ�ֵ���൱��*var--
	template<typename T> static T FetchAndDecrement(T *target);

	/// FAA������fetch-and-add��
	/// ����һ��ֵ��target������ԭ����ֵ
	template<typename T> static T FetchAndAdd(T *target, T value);

	/// FAS������fetch-and-subtract��
	/// ��target��ȥһ��ֵ������ԭ����ֵ
	template<typename T> static T FetchAndSubtract(T *target, T value);

	/// ����ֵ�����ؾ�ֵ
	template<typename T> static T Exchange(T *target, T value);

	/// ����ֵ��������ֵ
	/// 
	/// ����û���ṩ������ֵ��ԭ�ӽ���������SetValue��ʵ��ʹ��Exchange��ʵ�ֵģ�����Ƽ�ʹ��Exchange
	template<typename T> static T SetValue(T *target, T value);

	/// ��ȡֵ
	template<typename T> static T GetValue(T *target);
};

#include "gatom.inl"

#endif // _CORE_ATOM_H_