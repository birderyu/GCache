#ifndef _CORE_ARRAY_DATA_INLINE_
#define _CORE_ARRAY_DATA_INLINE_

namespace GNova {
	namespace Series {
		namespace Private {

			template<gbool HAS_END_FLAG>
			class GSeriesHelper
			{
			public:
				template<typename T> 
				GINLINE static T *CreateSeries(gsize size) noexcept(false)
				{
					return GArray<T>::CreateArray(size);
				}

				/// ��������һ������
				template<typename T> 
				GINLINE static T *CreateSeries(const T *copy_arr, gsize copy_size) noexcept(false)
				{
					return GArray<T>::CreateArray(copy_arr, 0, copy_size);
				}

				/// ����һ������Ϊsize�����飬����copy_arrȥ��ʼ���µ�����
				template<typename T> 
				GINLINE static T *CreateSeries(gsize size, const T *copy_arr, gsize copy_size) noexcept(false)
				{
					return GArray<T>::CreateArray(size, 0, copy_arr, 0, copy_size);
				}

				template<typename T> 
				GINLINE static gvoid DestorySeries(T *arr, gsize size) noexcept(false)
				{
					GArray<T>::DestoryArray(arr, size);
				}

				template<typename T> 
				GINLINE static gvoid ClearSeries(T *arr, gsize size) noexcept(false)
				{
					GArray<T>::ClearArray(arr, size);
				}

				template<typename T> 
				GINLINE static T *ResizeSeries(T *old_arr, gsize old_size, gsize new_size) noexcept(false)
				{
					return GArray<T>::ResizeArray(old_arr, old_size, new_size);
				}

				template<typename T>
				GINLINE static gvoid SetEndFlag(T *arr, gsize size, const T &end_flag)
				{

				}

				template<typename T> 
				GINLINE static gvoid SetEndFlag(T *arr, gsize size, T &&end_flag)
				{

				}

				/// arr��copy_arr��Ԫ�ظ���Ӧ���ڻ����size
				template<typename T>
				GINLINE static gvoid CopySeriesFrom(T *arr, gsize size, const T *copy_arr)
				{
					GArray<T>::CopyArrayFrom(arr, size, copy_arr);
				}
			};

			template<>
			template<typename T>
			GINLINE T *GSeriesHelper<true>::CreateSeries(gsize size) noexcept(false)
			{
				return GArray<T>::CreateArray(size + 1);
			}

			template<>
			template<typename T>
			GINLINE T *GSeriesHelper<true>::CreateSeries(const T *copy_arr, gsize copy_size) noexcept(false)
			{
				return GArray<T>::CreateArray(copy_arr, 0, copy_size + 1);
			}

			template<>
			template<typename T>
			GINLINE T *GSeriesHelper<true>::CreateSeries(gsize size, const T *copy_arr, gsize copy_size) noexcept(false)
			{
				return GArray<T>::CreateArray(size + 1, 0, copy_arr, 0, copy_size + 1);
			}

			template<>
			template<typename T>
			GINLINE gvoid GSeriesHelper<true>::DestorySeries(T *arr, gsize size) noexcept(false)
			{
				GArray<T>::DestoryArray(arr, size + 1);
			}

			template<>
			template<typename T>
			GINLINE gvoid GSeriesHelper<true>::ClearSeries(T *arr, gsize size) noexcept(false)
			{
				GArray<T>::ClearArray(arr, size + 1);
			}

			template<>
			template<typename T>
			GINLINE T *GSeriesHelper<true>::ResizeSeries(T *old_arr, gsize old_size, gsize new_size) noexcept(false)
			{
				return GArray<T>::ResizeArray(old_arr, old_size + 1, new_size + 1);
			}

			template<>
			template<typename T>
			GINLINE gvoid GSeriesHelper<true>::CopySeriesFrom(T *arr, gsize size, const T *copy_arr)
			{
				GArray<T>::CopyArrayFrom(arr, size + 1, copy_arr);
			}

			template<>
			template<typename T>
			GINLINE gvoid GSeriesHelper<true>::SetEndFlag(T *arr, gsize size, const T &end_flag)
			{
				arr[size] = end_flag;
			}

			template<>
			template<typename T>
			GINLINE gvoid GSeriesHelper<true>::SetEndFlag(T *arr, gsize size, T &&end_flag)
			{
				arr[size] = GForward<T>(end_flag);
			}
		}
	}
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::GSeries(gsize capacity)
	: m_nSize(0), m_pStart(GNULL)
{
	if (capacity <= MIN_CAPACITY)
	{
		m_nType = G_ARRAY_DATA_LOCAL_TYPE;
		m_nCapacity = MIN_CAPACITY;
		m_pStart = m_tArray;
	}
	else
	{
		m_nType = G_ARRAY_DATA_GLOBAL_TYPE;
		m_nCapacity = capacity;
		m_pArray = GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::CreateSeries<T>(capacity);
		m_pStart = m_pArray;
	}
	GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::SetEndFlag<T>(m_pStart, m_nSize, END_FLAG);
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::GSeries(const T *copy_arr, gsize copy_size, gbool is_reference)
	: m_nSize(copy_size), m_pStart(GNULL)
{
	if (is_reference)
	{
		// ���ÿ���
		m_nType = G_ARRAY_DATA_REFERENCE_TYPE;
		m_nCapacity = 0;
		m_nSize = copy_size;
		m_pStart = const_cast<T *>(copy_arr);
	}
	else
	{
		// ֵ����
		if (copy_size <= MIN_CAPACITY)
		{
			m_nType = G_ARRAY_DATA_LOCAL_TYPE;
			m_nCapacity = MIN_CAPACITY;
			GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::CopySeriesFrom<T>(m_tArray, copy_size, copy_arr);
			m_pStart = m_tArray;
		}
		else
		{
			m_nType = G_ARRAY_DATA_GLOBAL_TYPE;
			m_nCapacity = copy_size;
			m_pArray = GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::CreateSeries<T>(copy_arr, copy_size);
			m_pStart = m_pArray;
		}
		GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::SetEndFlag<T>(m_pStart, m_nSize, END_FLAG);
	}
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::GSeries(const GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &arr)
	: m_nSize(arr.m_nSize)
	, m_nCapacity(arr.m_nSize)
	, m_nType(arr.m_nType)
	, m_pStart(GNULL)
{
	switch (arr.m_nType)
	{
	case G_ARRAY_DATA_LOCAL_TYPE:
	{
		GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::CopySeriesFrom<T>(m_tArray, arr.m_nSize, arr.m_pStart);
		m_pStart = m_tArray;
	}
		break;
	case G_ARRAY_DATA_GLOBAL_TYPE:
	{
		m_pArray = GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::CreateSeries(arr.m_pStart, arr.m_nSize);
		m_pStart = m_pArray;
	}
		break;
	case G_ARRAY_DATA_REFERENCE_TYPE:
	{
		m_pStart = m_pArray;
	}
		break;
	default:
		throw "illegal type, type must be local or global or reference.";
		break;
	}
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::GSeries(GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &&arr)
	: m_nSize(arr.m_nSize)
	, m_nCapacity(arr.m_nCapacity)
	, m_nType(arr.m_nType)
	, m_pStart(arr.m_pStart)
{
	switch (arr.m_nType)
	{
	case G_ARRAY_DATA_LOCAL_TYPE:
	{
		m_pStart = m_tArray;
		GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::CopySeriesFrom<T>(m_pStart, arr.m_nSize, arr.m_pStart);
	}
		break;
	case G_ARRAY_DATA_GLOBAL_TYPE:
	{
		// ֵ��arr���ݱ����ÿ�
		arr.m_nType = G_ARRAY_DATA_LOCAL_TYPE;

		arr.m_pStart = arr.m_tArray;
		arr.m_nCapacity = arr.MIN_CAPACITY;
		arr.m_nSize = 0;
	}
		break;
	case G_ARRAY_DATA_REFERENCE_TYPE:
	{
		// ���ã�arr���������ÿ�
		m_pArray = arr.m_pStart;
		m_pStart = m_pArray;
	}
		break;
	default:
		throw "illegal type, type must be local or global or reference.";
		break;
	}
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::~GSeries()
{
	Free();
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE gsize GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::Size() const
{
	return m_nSize;
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE gsize GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::Capacity() const
{
	return m_nCapacity;
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE gbool GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::IsEmpty() const
{
	return m_nSize == 0;
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE gvoid GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::Resize(gsize size)
{
	if (IsReference())
	{
		// ��������
		ToValue(size);
		m_nSize = size;
		GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::SetEndFlag<T>(m_pStart, m_nSize, END_FLAG);
	}
	else
	{
		// ֵ����
		if (m_nSize == size)
		{
			return;
		}

		if (size <= m_nCapacity)
		{
			m_nSize = size;
			GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::SetEndFlag<T>(m_pStart, m_nSize, END_FLAG);
			return;
		}

		if (m_nType == G_ARRAY_DATA_LOCAL_TYPE)
		{
			// ��Ҫ��local type��չ��global type
			T *arr = GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::CreateSeries(size, m_tArray, m_nSize);
			m_nCapacity = size;
			m_pArray = arr;
			m_nType = G_ARRAY_DATA_GLOBAL_TYPE;
			m_pStart = m_pArray;
		}
		else if (m_nType == G_ARRAY_DATA_GLOBAL_TYPE)
		{
			// ��������
			m_pArray = GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::ResizeSeries<T>(m_pArray, m_nCapacity, size);
		}
		m_nSize = size;
		GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::SetEndFlag<T>(m_pStart, m_nSize, END_FLAG);
	}
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE gvoid GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::Reserve(gsize capacity)
{
	if (IsReference())
	{
		// ��������
		ToValue(capacity > m_nSize ? capacity : m_nSize);
	}
	else
	{
		// ֵ����
		if (capacity < m_nCapacity)
		{
			// ��������
			return;
		}

		if (m_nType == G_ARRAY_DATA_LOCAL_TYPE)
		{
			// ��Ҫ��local type��չ��global type
			T *arr = GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::CreateSeries(capacity, m_tArray, m_nSize);
			m_pArray = arr;
			m_nType = G_ARRAY_DATA_GLOBAL_TYPE;
			m_pStart = m_pArray;
		}
		else
		{
			// ��������
			m_pArray = GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::ResizeSeries<T>(m_pArray, m_nCapacity, capacity);
		}
		m_nCapacity = capacity;
	}
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE const T &GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::ConstGetAt(gsize pos) const
{
	GASSERT(pos < m_nSize);
	return m_pStart[pos];
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE const T &GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::GetAt(gsize pos) const
{
	GASSERT(pos < m_nSize);
	return m_pStart[pos];
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE T &GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::GetAt(gsize pos)
{
	ToValue(m_nSize);
	GASSERT(pos < m_nSize);
	return m_pStart[pos];
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE const T *GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::ConstCursorAt(gsize pos) const
{
	return m_pStart + pos;
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE const T *GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::CursorAt(gsize pos) const
{
	return m_pStart + pos;
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE T *GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::CursorAt(gsize pos)
{
	ToValue(m_nSize);
	return m_pStart + pos;
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE const T *GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::ConstStart() const
{
	return m_pStart;
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE const T *GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::Start() const
{
	return m_pStart;
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE T *GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::Start()
{
	ToValue(m_nSize);
	return m_pStart;
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE gvoid GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::SetAt(gsize pos, const T &data)
{
	ToValue(m_nSize);
	GASSERT(pos < m_nSize);
	m_pStart[pos] = data;
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE gvoid GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::SetAt(gsize pos, T &&data)
{
	ToValue(m_nSize);
	GASSERT(pos < m_nSize);
	m_pStart[pos] = GForward<T>(data);
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE gvoid GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::Clear()
{
	switch (m_nType)
	{
	case G_ARRAY_DATA_LOCAL_TYPE:
	case G_ARRAY_DATA_GLOBAL_TYPE:
	{
		GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::ClearSeries<T>(m_pArray, m_nCapacity);
	}
		break;
	case G_ARRAY_DATA_REFERENCE_TYPE:
	{
		// ������ת��Ϊһ���յ�local type
		m_nType = G_ARRAY_DATA_LOCAL_TYPE;
		m_nSize = 0;
		m_nCapacity = MIN_CAPACITY;
		m_pStart = m_tArray;
		GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::SetEndFlag<T>(m_pStart, m_nSize, END_FLAG);
	}
		break;
	default:
		throw "illegal type, type must be local or global or reference.";
		break;
	}
	m_nSize = 0;
	GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::SetEndFlag<T>(m_pStart, m_nSize, END_FLAG);
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE gvoid GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::Dispose()
{
	// �ͷ��ڴ�
	Free();

	// ������ת��Ϊlocal type���ÿ�
	m_nType = G_ARRAY_DATA_LOCAL_TYPE;
	m_nSize = 0;
	m_nCapacity = MIN_CAPACITY;
	m_pStart = m_tArray;
	GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::SetEndFlag<T>(m_pStart, m_nSize, END_FLAG);
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE gvoid GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::Append(const GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &series)
{
	ToValue(m_nSize + series.m_nSize); // ת����ֵ����
	Reserve(m_nSize + series.m_nSize);
	GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::CopySeriesFrom(m_pStart + m_nSize, series.m_nSize, series.m_pStart);
	m_nSize += series.m_nSize;
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE gvoid GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::Append(GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &&series)
{
	ToValue(m_nSize + series.m_nSize); // ת����ֵ����
	Reserve(m_nSize + series.m_nSize);
	GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::CopySeriesFrom(m_pStart + m_nSize, series.m_nSize, series.m_pStart);
	m_nSize += series.m_nSize;
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::operator=(const GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &arr)
{
	if (this == &arr)
	{
		return *this;
	}

	if (arr.IsReference())
	{
		// arr�������ͣ������õĴ���
		Free(); // �ͷſռ�
		m_nSize = arr.m_nSize;
		m_nType = arr.m_nType;
		m_nCapacity = arr.m_nCapacity;
		m_pStart = arr.m_pStart;
		return *this;
	}

	// arr����������
	if (m_nType == G_ARRAY_DATA_LOCAL_TYPE)
	{
		// ����ԭ����local type
		if (arr.m_nSize > m_nCapacity)
		{
			// ��local type��չ��global type����������ڴ棬����Ҫ����Ԫ��
			m_nCapacity = arr.m_nSize;
			m_nType = G_ARRAY_DATA_GLOBAL_TYPE;
			m_pArray = GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::CreateSeries<T>(arr.m_nSize);
			m_pStart = m_pArray;
		}
	}
	else if (m_nType == G_ARRAY_DATA_GLOBAL_TYPE)
	{
		// ����ԭ����global type
		// ��m_nCapacity >= arr.m_nSizeʱ��˵��ԭ����������Ѿ��ܹ��������µ����飬����������·����ڴ�
		// �������·����ڴ�
		if (m_nCapacity < arr.m_nSize)
		{
			// ԭ�е������Ѿ��޷��������µ����飬��Ҫ���ɵ���������
			GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::DestorySeries<T>(m_pArray, m_nCapacity);
			if (arr.m_nSize <= MIN_CAPACITY)
			{
				// �µ����齫����local type����������ڴ�
				m_nCapacity = MIN_CAPACITY;
				m_nType = G_ARRAY_DATA_LOCAL_TYPE;
				m_pStart = m_tArray;
			}
			else
			{
				// �µ����齫����global type����Ҫ�����ڴ�
				m_nCapacity = arr.m_nSize;
				m_nType = G_ARRAY_DATA_GLOBAL_TYPE;
				m_pArray = GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::CreateSeries<T>(arr.m_nSize);
				m_pStart = m_pArray;
			}
		}
	}
	else if (m_nType == G_ARRAY_DATA_REFERENCE_TYPE)
	{
		// ����ԭ����reference�������ڴ沢����
		m_nSize = arr.m_nSize;
		m_nCapacity = arr.m_nSize;
		m_nType = arr.m_nType;
		m_pStart = GNULL;

		switch (arr.m_nType)
		{
		case G_ARRAY_DATA_LOCAL_TYPE:
		{
			GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::CopySeriesFrom<T>(m_tArray, arr.m_nSize, arr.m_pStart);
			m_pStart = m_tArray;
		}
		break;
		case G_ARRAY_DATA_GLOBAL_TYPE:
		{
			m_pArray = GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::CreateSeries(arr.m_pStart, arr.m_nSize);
			m_pStart = m_pArray;
		}
		break;
		default:
			throw "illegal type, type must be local or global or reference.";
			break;
		}
	}
	else
	{
		throw "illegal type, type must be local or global or reference.";
	}

	// ����Ԫ��
	m_nSize = arr.m_nSize;
	GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::CopySeriesFrom(m_pStart, arr.m_nSize, arr.m_pStart);
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::operator=(GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &&arr)
{
	if (this == &arr)
	{
		return *this;
	}

	// ���پɵ�����
	Free();

	if (arr.IsReference())
	{
		// arr��������
		m_nSize = arr.m_nSize;
		m_nType = arr.m_nType;
		m_nCapacity = arr.m_nCapacity;
		m_pStart = arr.m_pStart;
		return *this;
	}

	// �ƶ���ֵ�µ�����
	m_nSize = arr.m_nSize;
	m_nCapacity = arr.m_nCapacity;
	m_nType = arr.m_nType;

	switch (arr.m_nType)
	{
	case G_ARRAY_DATA_LOCAL_TYPE:
	{
		GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::CopySeriesFrom<T>(m_tArray, arr.m_nSize, arr.m_pStart);
		m_pStart = m_tArray;
	}
		break;
	case G_ARRAY_DATA_GLOBAL_TYPE:
	{
		m_pArray = arr.m_pArray;
		m_pStart = m_pArray;
		// arr�����ÿ�
		arr.m_nType = G_ARRAY_DATA_LOCAL_TYPE;
		arr.m_pStart = arr.m_tArray;
		arr.m_nCapacity = arr.MIN_CAPACITY;
		arr.m_nSize = 0;
	}
		break;
	case G_ARRAY_DATA_REFERENCE_TYPE:
	{
		m_pStart = arr.m_pStart;
	}
		break;
	default:
		throw "illegal type, type must be local or global or reference.";
		break;
	}
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE const T &GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::operator[](gsize pos) const
{
	return ConstGetAt(pos);
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE T &GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::operator[](gsize pos)
{
	ToValue(m_nSize);
	return GetAt(pos);
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE gvoid GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::Free()
{
	switch (m_nType)
	{
	case G_ARRAY_DATA_LOCAL_TYPE:
	{
		// ֻ����Ԫ�أ����ͷ��ڴ�
		GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::ClearSeries<T>(m_pArray, m_nCapacity);
	}
	break;
	case G_ARRAY_DATA_GLOBAL_TYPE:
	{
		// ����Ԫ�غ��ͷ��ڴ�
		GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::DestorySeries<T>(m_pArray, m_nCapacity);
	}
	break;
	case G_ARRAY_DATA_REFERENCE_TYPE:
	{
		// ���ã���������
	}
	break;
	default:
		throw "illegal type, type must be local or global or reference.";
		break;
	}
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE gbool GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::IsReference() const
{
	return m_nType == G_ARRAY_DATA_REFERENCE_TYPE;
}

template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
GINLINE gvoid GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>::ToValue(gsize capacity)
{
	if (!IsReference())
	{
		return;
	}

	// ʵ�ʵĴ�СΪm_nSize��capacity�еĽ�С�ߣ��������ڵ�capacity��Сʱ�����ԭ�����������ض�
	gsize real_size = m_nSize < capacity ? m_nSize : capacity;

	if (capacity <= MIN_CAPACITY)
	{
		m_nType = G_ARRAY_DATA_LOCAL_TYPE;
		m_nCapacity = MIN_CAPACITY;
		GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::CopySeriesFrom<T>(m_tArray, real_size, m_pStart);
		m_pStart = m_tArray;
	}
	else
	{
		m_nType = G_ARRAY_DATA_GLOBAL_TYPE;
		m_nCapacity = capacity;
		m_pArray = GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::CreateSeries<T>(capacity);
		GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::CopySeriesFrom<T>(m_pArray, real_size, m_pStart);
		m_pStart = m_pArray;
	}

	m_nSize = real_size;
	GNova::Series::Private::GSeriesHelper<HAS_END_FLAG>::SetEndFlag<T>(m_pStart, m_nSize, END_FLAG);
}

#endif // _CORE_ARRAY_DATA_INLINE_
