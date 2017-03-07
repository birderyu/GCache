#ifndef _CORE_ARRAY_INLINE_
#define _CORE_ARRAY_INLINE_

namespace GNova {
	namespace Array {
		namespace Private {

			/// DataT�������õĹ��캯�������蹹�죬�������ڴ�
			template <typename DataT> GINLINE DataT *_GArrayCreate(gsize size, GTrueType) noexcept(false)
			{
				/// ������������Ҫ����
				return GAllocate<DataT>(size);
			}

			/// DataT���������õĹ��캯���������ڴ�֮�����ε���Ԫ�صĹ��캯��
			template <typename DataT> GINLINE DataT *_GArrayCreate(gsize size, GFalseType) noexcept(false)
			{
				DataT *arr = GAllocate<DataT>(size);
				for (gsize i = 0; i < size; i++)
				{
					GConstruct<DataT>(arr + i);
				}
				return arr;
			}

			/// DataT���������ͣ�ֱ��ʹ���ڴ濽��������ɿ��������߼�
			template <typename DataT> GINLINE DataT *_GArrayCreate(const DataT *copy_arr, gsize copy_start, gsize copy_size, GTrueType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(copy_size);
				GMemCopy(new_arr, copy_arr + copy_start, copy_size);
				return new_arr;
			}

			/// DataT�����������ͣ����ÿ����������캯������
			template <typename DataT> GINLINE DataT *_GArrayCreate(const DataT *copy_arr, gsize copy_start, gsize copy_size, GFalseType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(copy_size);
				for (gsize i = 0; i < copy_size; i++)
				{
					GConstruct<DataT>(new_arr + i, copy_arr[i + copy_start]);
				}
				return new_arr;
			}

			/// DataT���������ͣ�ֱ��ʹ���ڴ濽��������ɿ��������߼�������Ԫ�����蹹�죬�������ڴ�
			template <typename DataT> GINLINE DataT *_GArrayCreate(gsize size, gsize start, const DataT *copy_arr, gsize copy_start, gsize copy_size, GTrueType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(size);
				gsize new_copy_size = size - start;
				gsize real_copy_size = copy_size < new_copy_size ? copy_size : new_copy_size;
				GMemCopy(new_arr + start, copy_arr + copy_start, real_copy_size);
				return new_arr;
			}

			/// DataT�����������ͣ����ÿ����������캯������
			template <typename DataT> GINLINE DataT *_GArrayCreate(gsize size, gsize start, const DataT *copy_arr, gsize copy_start, gsize copy_size, GFalseType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(size);
				gsize new_copy_size = size - start;

				for (gsize i = 0; i < start; i++)
				{
					GConstruct<DataT>(new_arr + i);
				}

				if (copy_size < new_copy_size)
				{
					for (gsize i = start; i < start + copy_size; i++)
					{
						GConstruct<DataT>(new_arr + i, copy_arr[i + copy_start]);
					}
					for (gsize i = start + copy_size; i < size; i++)
					{
						GConstruct<DataT>(new_arr + i);
					}
				}
				else
				{
					for (gsize i = start; i < size; i++)
					{
						GConstruct<DataT>(new_arr + i, copy_arr[i + copy_start]);
					}
				}

				return new_arr;
			}

			/// DataT�������õ��ƶ����캯�����ҵ�ǰ�������������ͣ�ֱ�ӵ����ڴ�����������Ԫ����Ŀ�ĵ���
			template <typename DataT> GINLINE DataT *__GArrayResize(DataT *old_arr, gsize old_size, gsize new_size, GTrueType) noexcept(false)
			{
				return GReallocate<DataT>(old_arr, new_size);
			}

			/// DataT�������õ��ƶ����캯�����ҵ�ǰ�����ǲ��������ͣ�ʹ�ÿ������������ƶ�����
			template <typename DataT> GINLINE DataT *__GArrayResize(DataT *old_arr, gsize old_size, gsize new_size, GFalseType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(new_size);
				if (old_size < new_size)
				{
					for (gsize i = 0; i < old_size; i++)
					{
						GConstruct<DataT>(new_arr + i, old_arr[i]);
					}
					for (gsize i = old_size; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i);
					}
				}
				else // old_size >= new_size
				{
					for (gsize i = 0; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i, old_arr[i]);
					}
				}

				// ���پɵ�����
				GArray<DataT>::DestoryArray(old_arr, old_size);
				return new_arr;
			}

			/// DataT�������õ��ƶ����캯��������Ҫ����Ԫ�أ���ʱ�������������
			template <typename DataT> GINLINE DataT *_GArrayResize(DataT *old_arr, gsize old_size, gsize new_size, GTrueType) noexcept(false)
			{
				/// ����DataT�Ƿ����������ͣ����ò�ͬ�Ĵ����߼�
				return __GArrayResize(old_arr, old_size, new_size,
					GTypeTraits<DataT>::Arithmetic());
			}

			/// DataT���������õ��ƶ����캯���������ƶ������������Ԫ�صĹ��죬�������Ԫ�ص���Ĭ�Ϲ��캯��
			template <typename DataT> GINLINE DataT *_GArrayResize(DataT *old_arr, gsize old_size, gsize new_size, GFalseType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(new_size);
				if (old_size < new_size)
				{
					for (gsize i = 0; i < old_size; i++)
					{
						GConstruct<DataT>(new_arr + i, GMove(old_arr[i]));
					}
					for (gsize i = old_size; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i);
					}
				}
				else // old_size >= new_size
				{
					for (gsize i = 0; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i, GMove(old_arr[i]));
					}
				}

				// ���پɵ�����
				GArray<DataT>::DestoryArray(old_arr, old_size);
				return new_arr;
			}

			/// DataT�������õ��ƶ����캯�����ҵ�ǰ�������������ͣ�����ʹ���ڴ����
			template <typename DataT> GINLINE DataT *__GArrayResize(DataT *old_arr, gsize old_size, gsize new_size, const DataT &copyable, GTrueType) noexcept(false)
			{
				DataT *new_arr = GReallocate<DataT>(old_arr, new_size);
				if (old_size < new_size)
				{
					for (gsize i = old_size; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i, copyable);
					}
				}
				return new_arr;
			}

			/// DataT�������õ��ƶ����캯�����ҵ�ǰ�����ǲ��������ͣ�ʹ�ÿ������������ƶ�����
			template <typename DataT> GINLINE DataT *__GArrayResize(DataT *old_arr, gsize old_size, gsize new_size, const DataT &copyable, GFalseType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(new_size);
				if (old_size < new_size)
				{
					for (gsize i = 0; i < old_size; i++)
					{
						GConstruct<DataT>(new_arr + i, old_arr[i]);
					}
					for (gsize i = old_size; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i, copyable);
					}
				}
				else // old_size >= new_size
				{
					for (gsize i = 0; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i, old_arr[i]);
					}
				}

				// ���پɵ�����
				GArray<DataT>::DestoryArray(old_arr, old_size);
				return new_arr;
			}

			/// DataT�������õ��ƶ����캯������ʱ�������������
			template <typename DataT> GINLINE DataT *_GArrayResize(DataT *old_arr, gsize old_size, gsize new_size, const DataT &copyable, GTrueType) noexcept(false)
			{
				/// ����DataT�Ƿ����������ͣ����ò�ͬ�Ĵ����߼�
				return __GArrayResize(old_arr, old_size, new_size, copyable,
					GTypeTraits<DataT>::Arithmetic());
			}

			/// DataT���������õ��ƶ����캯����ʹ���ƶ�����
			template <typename DataT> GINLINE DataT *_GArrayResize(DataT *old_arr, gsize old_size, gsize new_size, const DataT &copyable, GFalseType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(new_size);
				if (old_size < new_size)
				{
					for (gsize i = 0; i < old_size; i++)
					{
						GConstruct<DataT>(new_arr + i, GMove(old_arr[i]));
					}
					for (gsize i = old_size; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i, copyable);
					}
				}
				else // old_size >= new_size
				{
					for (gsize i = 0; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i, GMove(old_arr[i]));
					}
				}

				// ���پɵ�����
				GArray<DataT>::DestoryArray(old_arr, old_size);
				return new_arr;
			}

			/// DataT�������õ��ƶ����캯�����ҵ�ǰ�������������ͣ�����ʹ�õȺŲ���
			template <typename DataT> GINLINE DataT *__GArrayResize(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, GTrueType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(new_size);
				gsize new_real_size = new_start + old_size;

				gsize j = old_start;
				if (new_real_size < new_size)
				{
					for (gsize i = new_start; i < new_real_size; i++)
					{
						new_arr[i] = old_arr[j++];
					}
				}
				else // old_size >= new_size
				{
					for (gsize i = new_start; i < new_size; i++)
					{
						new_arr[i] = old_arr[j++];
					}
				}

				// ���پɵ�����
				GArray<DataT>::DestoryArray(old_arr, old_start + old_size);
				return new_arr;
			}

			/// DataT�������õ��ƶ����캯�����ҵ�ǰ�����ǲ��������ͣ�ʹ�ÿ������������ƶ�����
			template <typename DataT> GINLINE DataT *__GArrayResize(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, GFalseType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(new_size);
				gsize new_real_size = new_start + old_size;

				gsize j = old_start;
				if (new_real_size < new_size)
				{
					for (gsize i = 0; i < new_start; i++)
					{
						GConstruct<DataT>(new_arr + i);
					}
					for (gsize i = new_start; i < new_real_size; i++)
					{
						GConstruct<DataT>(new_arr + i, old_arr[j++]);
					}
					for (gsize i = new_real_size; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i);
					}
				}
				else // old_size >= new_size
				{
					for (gsize i = 0; i < new_start; i++)
					{
						GConstruct<DataT>(new_arr + i);
					}
					for (gsize i = new_start; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i, old_arr[j++]);
					}
				}

				// ���پɵ�����
				GArray<DataT>::DestoryArray(old_arr, old_start + old_size);
				return new_arr;
			}

			/// DataT�������õ��ƶ����캯������ʱ�������������
			template <typename DataT> GINLINE DataT *_GArrayResize(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, GTrueType) noexcept(false)
			{
				/// ����DataT�Ƿ����������ͣ����ò�ͬ�Ĵ����߼�
				return __GArrayResize(old_arr, old_start, old_size, new_size, new_start,
					GTypeTraits<DataT>::Arithmetic());
			}

			/// DataT���������õ��ƶ����캯����ʹ���ƶ�����
			template <typename DataT> GINLINE DataT *_GArrayResize(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, GFalseType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(new_size);
				gsize new_real_size = new_start + old_size;
				gsize j = old_start;

				if (new_real_size < new_size)
				{
					for (gsize i = 0; i < new_start; i++)
					{
						GConstruct<DataT>(new_arr + i);
					}
					for (gsize i = new_start; i < new_real_size; i++)
					{
						GConstruct<DataT>(new_arr + i, GMove(old_arr[j++]));
					}
					for (gsize i = new_real_size; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i);
					}
				}
				else // old_size >= new_size
				{
					for (gsize i = 0; i < new_start; i++)
					{
						GConstruct<DataT>(new_arr + i);
					}
					for (gsize i = new_start; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i, GMove(old_arr[j++]));
					}
				}

				// ���پɵ�����
				GArray<DataT>::DestoryArray(old_arr, old_start + old_size);
				return new_arr;
			}

			/// DataT�������õ��ƶ����캯�����ҵ�ǰ�������������ͣ�����ʹ�õȺŲ���
			template <typename DataT> GINLINE DataT *__GArrayResize(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const DataT &copyable, GTrueType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(new_size);
				gsize new_real_size = new_start + old_size;

				gsize j = old_start;
				if (new_real_size < new_size)
				{
					for (gsize i = 0; i < new_start; i++)
					{
						new_arr[i] = copyable;
					}
					for (gsize i = new_start; i < new_real_size; i++)
					{
						new_arr[i] = old_arr[j++];
					}
					for (gsize i = new_real_size; i < new_size; i++)
					{
						new_arr[i] = copyable;
					}
				}
				else // old_size >= new_size
				{
					for (gsize i = 0; i < new_start; i++)
					{
						new_arr[i] = copyable;
					}
					for (gsize i = new_start; i < new_size; i++)
					{
						new_arr[i] = old_arr[j++];
					}
				}

				// ���پɵ�����
				GArray<DataT>::DestoryArray(old_arr, old_start + old_size);
				return new_arr;
			}

			/// DataT�������õ��ƶ����캯�����ҵ�ǰ�����ǲ��������ͣ�ʹ�ÿ������������ƶ�����
			template <typename DataT> GINLINE DataT *__GArrayResize(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const DataT &copyable, GFalseType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(new_size);
				gsize new_real_size = new_start + old_size;

				gsize j = old_start;
				if (new_real_size < new_size)
				{
					for (gsize i = 0; i < new_start; i++)
					{
						GConstruct<DataT>(new_arr + i, copyable);
					}
					for (gsize i = new_start; i < new_real_size; i++)
					{
						GConstruct<DataT>(new_arr + i, old_arr[j++]);
					}
					for (gsize i = new_real_size; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i, copyable);
					}
				}
				else // old_size >= new_size
				{
					for (gsize i = 0; i < new_start; i++)
					{
						GConstruct<DataT>(new_arr + i, copyable);
					}
					for (gsize i = new_start; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i, old_arr[j++]);
					}
				}

				// ���پɵ�����
				GArray<DataT>::DestoryArray(old_arr, old_start + old_size);
				return new_arr;
			}

			/// DataT�������õ��ƶ����캯������ʱ�������������
			template <typename DataT> GINLINE DataT *_GArrayResize(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const DataT &copyable, GTrueType) noexcept(false)
			{
				/// ����DataT�Ƿ����������ͣ����ò�ͬ�Ĵ����߼�
				return __GArrayResize(old_arr, old_start, old_size, new_size, new_start, copyable,
					GTypeTraits<DataT>::Arithmetic());
			}

			/// DataT���������õ��ƶ����캯����ʹ���ƶ�����
			template <typename DataT> GINLINE DataT *_GArrayResize(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const DataT &copyable, GFalseType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(new_size);
				gsize new_real_size = new_start + old_size;
				gsize j = old_start;

				if (new_real_size < new_size)
				{
					for (gsize i = 0; i < new_start; i++)
					{
						GConstruct<DataT>(new_arr + i, copyable);
					}
					for (gsize i = new_start; i < new_real_size; i++)
					{
						GConstruct<DataT>(new_arr + i, GMove(old_arr[j++]));
					}
					for (gsize i = new_real_size; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i, copyable);
					}
				}
				else // old_size >= new_size
				{
					for (gsize i = 0; i < new_start; i++)
					{
						GConstruct<DataT>(new_arr + i, copyable);
					}
					for (gsize i = new_start; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i, GMove(old_arr[j++]));
					}
				}

				// ���پɵ�����
				GArray<DataT>::DestoryArray(old_arr, old_start + old_size);
				return new_arr;
			}

			/// DataT�������õ��ƶ����캯�����ҵ�ǰ�������������ͣ�ʹ���ڴ濽��
			template <typename DataT> GINLINE DataT *__GArrayRemoveAt(DataT *arr, gsize size, gsize pos, GTrueType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(size - 1);
				if (pos > 0)
				{
					GMemCopy(new_arr, arr, pos);
				}
				GMemCopy(new_arr + pos, arr + pos + 1, size - pos - 1);

				// ���پɵ�����
				GArray<DataT>::DestoryArray(arr, size);
				return new_arr;
			}

			/// DataT�������õ��ƶ����캯�����ҵ�ǰ�������������ͣ�ʹ�ÿ�������
			template <typename DataT> GINLINE DataT *__GArrayRemoveAt(DataT *arr, gsize size, gsize pos, GFalseType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(size - 1);
				for (gsize i = 0; i < pos; i++)
				{
					GConstruct<DataT>(new_arr + i, arr[i]);
				}
				for (gsize i = pos + 1; i < size; i++)
				{
					GConstruct<DataT>(new_arr + i - 1, arr[i]);
				}

				// ���پɵ�����
				GArray<DataT>::DestoryArray(arr, size);
				return new_arr;
			}

			/// DataT�������õ��ƶ����캯������ʱ�������������
			template <typename DataT> GINLINE DataT *_GArrayRemoveAt(DataT *arr, gsize size, gsize pos, GTrueType) noexcept(false)
			{
				/// ����DataT�Ƿ����������ͣ����ò�ͬ�Ĵ����߼�
				return __GArrayRemoveAt(arr, size, pos,
					GTypeTraits<DataT>::Arithmetic());
			}

			/// DataT���������õ��ƶ����캯����ʹ���ƶ�����
			template <typename DataT> GINLINE DataT *_GArrayRemoveAt(DataT *arr, gsize size, gsize pos, GFalseType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(size - 1);
				for (gsize i = 0; i < pos; i++)
				{
					GConstruct<DataT>(new_arr + i, GMove(arr[i]));
				}
				for (gsize i = pos + 1; i < size; i++)
				{
					GConstruct<DataT>(new_arr + i - 1, GMove(arr[i]));
				}

				// ���پɵ�����
				GArray<DataT>::DestoryArray(arr, size);
				return new_arr;
			}

			/// DataT���������õ�����������������
			template <typename DataT> GINLINE gvoid _GArrayClear(DataT *arr, gsize size, GTrueType) noexcept
			{

			}

			/// DataT���������õ��������������ε�����������
			template <typename DataT> GINLINE gvoid _GArrayClear(DataT *arr, gsize size, GFalseType) noexcept
			{
				if (!arr)
				{
					return;
				}
				for (gsize i = 0; i < size; i++)
				{
					arr[i].~DataT();
				}
			}

			/// DataT���������ͣ�������������ֱ��ʹ���ڴ濽��
			template <typename DataT> GINLINE gvoid _GArrayCopyFrom(DataT *arr, gsize size, const DataT *copy_arr, GTrueType)
			{
				GMemCopy(arr, copy_arr, size);
			}

			/// DataT�����������ͣ����������ڵ��ÿ�������
			template <typename DataT> GINLINE gvoid _GArrayCopyFrom(DataT *arr, gsize size, const DataT *copy_arr, GFalseType) noexcept(false)
			{
				for (gsize i = 0; i < size; i++)
				{
					// ����ԭ��Ԫ��
					GDestruct<DataT>(arr + i);

					// ���������µ�Ԫ��
					GConstruct<DataT>(arr + i, copy_arr[i]);
				}
			}

			/// DataT���������ͣ�������������ֱ��ʹ���ڴ濽��
			template <typename DataT> GINLINE DataT *_GArrayCopyFrom(DataT *arr, gsize size, const DataT *copy_arr, gsize copy_size, GTrueType) noexcept(false)
			{
				if (size != copy_size)
				{
					GDeallocate<DataT>(arr);
					arr = GAllocate<DataT>(copy_size);
				}

				GMemCopy(arr, copy_arr, copy_size);
				return arr;
			}

			/// DataT�����������ͣ����������ٵ��ÿ�������
			template <typename DataT> GINLINE DataT *_GArrayCopyFrom(DataT *arr, gsize size, const DataT *copy_arr, gsize copy_size, GFalseType) noexcept(false)
			{
				for (gsize i = 0; i < size; i++)
				{
					GDestruct<DataT>(arr + i);
				}
				if (size != copy_size)
				{
					GDeallocate<DataT>(arr);
					arr = GAllocate<DataT>(copy_size);
				}
				for (gsize i = 0; i < copy_size; i++)
				{
					GConstruct<DataT>(arr + i, copy_arr[i]);
				}
				return arr;
			}

		}
	}
}

template <typename DataT>
GINLINE DataT *GArray<DataT>::CreateArray(gsize size) noexcept(false)
{
	GASSERT(size > 0);

	/// ����DataT�Ƿ�������õ�Ĭ�Ϲ��캯����ȥ���ò�ͬ�Ĵ����߼�
	return GNova::Array::Private::_GArrayCreate<DataT>(size,
		GTypeTraits<DataT>::TrivialDefaultConstructible());
}

template <typename DataT>
GINLINE DataT *GArray<DataT>::CreateArray(gsize size, const DataT &copyable) noexcept(false)
{
	GASSERT(size > 0);

	DataT *arr = GAllocate<DataT>(size);
	for (gsize i = 0; i < size; i++)
	{
		// ��GConstruct�ĵ��ù����У��Ѿ�����������������͵Ĵ����߼�
		GConstruct<DataT>(arr + i, copyable);
	}
	return arr;
}

template <typename DataT>
GINLINE DataT *GArray<DataT>::CreateArray(const DataT *copy_arr, gsize copy_start, gsize copy_size) noexcept(false)
{
	// ��copy_arr�����ڣ�����copy_start�����˷�Χ����ᱨ��
	GASSERT(copy_arr && copy_start < copy_size);

	// ����DataT�Ƿ����������ͣ�ȥ���ò�ͬ�Ĵ����߼�
	return GNova::Array::Private::_GArrayCreate<DataT>(copy_arr, copy_start, copy_size,
		GTypeTraits<DataT>::Arithmetic());
}

template <typename DataT>
GINLINE DataT *GArray<DataT>::CreateArray(gsize size, gsize start, const DataT *copy_arr, gsize copy_start, gsize copy_size) noexcept(false)
{
	GASSERT(start < size && copy_arr && copy_start < copy_size);

	// ����DataT�Ƿ����������ͣ�ȥ���ò�ͬ�Ĵ����߼�
	return GNova::Array::Private::_GArrayCreate(size, start, copy_arr, copy_start, copy_size,
		GTypeTraits<DataT>::Arithmetic());
}

template <typename DataT>
GINLINE DataT *GArray<DataT>::ResizeArray(DataT *old_arr, gsize old_size, gsize new_size) noexcept(false)
{
	// �ж�DataT�Ƿ�����ƶ����캯�������ж��Ƿ���Ҫ���ò�ͬ�ĺ���
	return GNova::Array::Private::_GArrayResize<DataT>(old_arr, old_size, new_size,
		GTypeTraits<DataT>::TrivialMoveConstructible());
}

template <typename DataT>
GINLINE DataT *GArray<DataT>::ResizeArray(DataT *old_arr, gsize old_size, gsize new_size, const DataT &copyable) noexcept(false)
{
	// �ж�DataT�Ƿ�����ƶ����캯�������ж��Ƿ���Ҫ���ò�ͬ�ĺ���
	return GNova::Array::Private::_GArrayResize<DataT>(old_arr, old_size, new_size, copyable,
		GTypeTraits<DataT>::TrivialMoveConstructible());
}

template <typename DataT>
GINLINE DataT *GArray<DataT>::ResizeArray(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start) noexcept(false)
{
	GASSERT(old_start < old_size);

	// �ж�DataT�Ƿ�����ƶ����캯�������ж��Ƿ���Ҫ���ò�ͬ�ĺ���
	return GNova::Array::Private::_GArrayResize<DataT>(old_arr, old_start, old_size, new_size, new_start,
		GTypeTraits<DataT>::TrivialMoveConstructible());
}

template <typename DataT>
GINLINE DataT *GArray<DataT>::ResizeArray(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const DataT &copyable) noexcept(false)
{
	// �ж�DataT�Ƿ�����ƶ����캯�������ж��Ƿ���Ҫ���ò�ͬ�ĺ���
	return GNova::Array::Private::_GArrayResize<DataT>(old_arr, old_start, old_size, new_size, new_start, copyable,
		GTypeTraits<DataT>::TrivialMoveConstructible());
}

template <typename DataT>
GINLINE DataT *GArray<DataT>::RemoveArrayElementAt(DataT *arr, gsize size, gsize pos) noexcept(false)
{
	GASSERT(size > 0 && pos < size);

	// �ж�DataT�Ƿ�����ƶ����캯�������ж��Ƿ���Ҫ���ò�ͬ�ĺ���
	return GNova::Array::Private::_GArrayRemoveAt(arr, size, pos,
		GTypeTraits<DataT>::TrivialMoveConstructible());
}

template <typename DataT>
GINLINE gvoid GArray<DataT>::ClearArray(DataT *arr, gsize size) noexcept
{
	GNova::Array::Private::_GArrayClear(arr, size,
		GTypeTraits<DataT>::TrivialDestructible());
}

template <typename DataT>
GINLINE gvoid GArray<DataT>::DestoryArray(DataT *arr, gsize size) noexcept
{
	// �ж�DataT�Ƿ�����������������ж��Ƿ���Ҫ���ò�ͬ�ĺ���
	GNova::Array::Private::_GArrayClear(arr, size,
		GTypeTraits<DataT>::TrivialDestructible());

	// �ͷ��ڴ�
	GDeallocate<DataT>(arr);
}

template <typename DataT>
GINLINE gvoid GArray<DataT>::CopyArrayFrom(DataT *arr, gsize size, const DataT *copy_arr) noexcept(false)
{
	GASSERT(arr && copy_arr);

	// �ж�DataT�Ƿ��ǻ������ͣ����ж��Ƿ���Ҫ���ò�ͬ�ĺ���
	GNova::Array::Private::_GArrayCopyFrom<DataT>(arr, size, copy_arr,
		GTypeTraits<DataT>::Arithmetic());
}

template <typename DataT>
GINLINE DataT *GArray<DataT>::CopyArrayFrom(DataT *arr, gsize size, const DataT *copy_arr, gsize copy_size) noexcept(false)
{
	GASSERT(arr && copy_arr);

	// �ж�DataT�Ƿ��ǻ������ͣ����ж��Ƿ���Ҫ���ò�ͬ�ĺ���
	return GNova::Array::Private::_GArrayCopyFrom<DataT>(arr, size, copy_arr, copy_size,
		GTypeTraits<DataT>::Arithmetic());
}

template <typename DataT>
GINLINE gbool GArray<DataT>::Contains(const DataT &data) const
{
	gsize size = Size();
	for (gsize i = 0; i < size; i++)
	{
		if (GetAt(i) == data)
		{
			return true;
		}
	}
	return false;
}

template <typename DataT>
GINLINE gsize GArray<DataT>::FirstIndexOf(const DataT &data) const
{
	gsize size = Size();
	for (gsize i = 0; i < size; i++)
	{
		if (GetAt(i) == data)
		{
			return i;
		}
	}
	return NULL_POS;
}

template <typename DataT>
GINLINE gsize GArray<DataT>::LastIndexOf(const DataT &data) const
{
	gsize size = Size();
	for (gsize i = size; i > 0; i--)
	{
		// ע�ⲻ����i����0
		if (GetAt(i - 1) == data)
		{
			return i - 1;
		}
	}
	return NULL_POS;
}

template <typename DataT>
GINLINE gsize GArray<DataT>::CountOf(const DataT &data) const
{
	gsize size = Size();
	gsize count = 0;
	for (gsize i = 0; i < size; i++)
	{
		if (GetAt(i) == data)
		{
			count++;
		}
	}
	return count;
}

template <typename DataT>
GINLINE guint GArray<DataT>::ClassCode() const
{
	return GArray<DataT>::CLASS_CODE;
}

#endif // _CORE_ARRAY_INLINE_