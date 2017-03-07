/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @file	gobject.h
** @brief	�����������͵Ķ���
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2015-12-31
** @version	1.0
** @see		GObject
**
****************************************************************************/

#ifndef _CORE_OBJECT_H_
#define _CORE_OBJECT_H_

#include "gglobal.h"
#include "gsharedpointer.h"

G_BEGIN_NAMESPACE
class GObject;
class GString;
class GBytes;
typedef GSharedPointer<GObject> GObjectP;
G_END_NAMESPACE

G_BEGIN_NAMESPACE

// �����к�
enum G_CLASS_CODE
{
	CLASS_CODE_OBJECT = 0,					// Object

	CLASS_CODE_PACKAGE,						// Package
	CLASS_CODE_NUMBER,						// Number
	CLASS_CODE_BYTE,						// Byte
	CLASS_CODE_BOOLEAN,						// Boolean
	CLASS_CODE_CHARACTER,					// Character
	CLASS_CODE_SIGNED_CHARACTER,			// SignedCharacter
	CLASS_CODE_UNSIGNED_CHARACTER,			// UnsignedCharacter
	CLASS_CODE_WIND_CHARACTER,				// WindCharacter
	CLASS_CODE_SMALL_INTEGER,				// SmallInteger
	CLASS_CODE_UNSIGNED_SMALL_INTEGER,		// UnsignedSmallInteger
	CLASS_CODE_SHORT_INTEGER,				// ShortInteger
	CLASS_CODE_UNSIGNED_SHORT_INTEGER,		// UnsignedShortInteger
	CLASS_CODE_INTEGER,						// Integer
	CLASS_CODE_UNSIGNED_INTEGER,			// UnsignedInteger
	CLASS_CODE_LONG_INTEGER,				// LongInteger
	CLASS_CODE_UNSIGNED_LONG_INTEGER,		// UnsignedLongInteger
	CLASS_CODE_LONG_LONG_INTEGER,			// LongLongInteger
	CLASS_CODE_UNSIGNED_LONG_LONG_INTEGER,	// UnsignedLongLongInteger
	CLASS_CODE_SINGLE_FLOAT,				// SingleFloat
	CLASS_CODE_DOUBLE_FLOAT,				// DoubleFloat
	CLASS_CODE_LONG_DOUBLE_FLOAT,			// LongDoubleFloat

	CLASS_CODE_ARRAY,						// Array
	CLASS_CODE_STATIC_ARRAY,				// StaticArray
	CLASS_CODE_DYNAMIC_ARRAY,				// DynamicArray
	CLASS_CODE_LINKED_LIST,					// LinkedList
	CLASS_CODE_SINGLE_LINKED_LIST,			// SingleLinkedList
	CLASS_CODE_CIRCULAR_LINKED_LIST,		// CircularLinkedList
	CLASS_CODE_DOUBLE_LINKED_LIST,			// DoubleLinkedList
	CLASS_CODE_STACK,						// Stack
	CLASS_CODE_ARRAY_STACK,					// ArrayStack
	CLASS_CODE_LIST_STACK,					// ListStack
	CLASS_CODE_BINARY_TREE,					// BinaryTree
	CLASS_CODE_BINARY_SORT_TREE,			// BinarySortTree

	CLASS_CODE_STRING,						// String
	CLASS_CODE_THREAD,						// Thread
	CLASS_CODE_MUTEX,						// Mutex
	CLASS_CODE_CRITICAL_SECTION,			// CriticalSection

	CLASS_CODE_SOCKET_ADDRESS,				// SockAddress
	CLASS_CODE_SOCKET,						// Socket
	CLASS_CODE_TCPSOCKET,					// TcpSocket
	CLASS_CODE_UDPSOCKET,					// UdpSocket
	CLASS_CODE_VECTOR,						// Vector
	CLASS_CODE_LIST,						// List
	CLASS_CODE_MAP,							// Map
	CLASS_CODE_TABLE,						// Table
	CLASS_CODE_FILE,						// File

	CLASS_CODE_DATE_TIME,					// DateTime
	CLASS_CODE_DATE,						// Date
	CLASS_CODE_TIME,						// Time
	CLASS_CODE_GEOMETRY,
};

/****************************************************************************
**
** gobject.h
**
** @class		GObject
** @brief		������������
** @module		GCore
**
** ��������������������Դ����Ļ����ͣ����ڷ���Դ�Ͷ�����ں˶������Ƽ��̳и��ࡣ
** ��Ϊ���������һ������������ԣ�
** 1���ɸ��ƣ����ƶ������и��ƹ��캯����������������ƶ����캯�����ƶ������
** 2������ת��Ϊ�ֽڴ����ַ���
**
****************************************************************************/
class GAPI GObject
{
public:
	enum { CLASS_CODE = CLASS_CODE_OBJECT, };

public:
	/****************************************************************************
	**
	** GObject
	**
	** @name	~GObject
	** @brief	����������destructor��
	**
	** ����GObject��Ҫ��Ϊ������Դ��Ļ��࣬�����������������������ģ�virtual����
	**
	****************************************************************************/
	virtual ~GObject() = 0;

	/****************************************************************************
	**
	** GObject
	**
	** @name	Clone
	** @brief	������һ���µ�ʵ��
	** @return	{GObjectP} ��������ʵ������һ������ָ�루GSharedPointer��
	** @exception
	** @see		GSharedPointer<T>
	** @see		GObjectP
	**
	****************************************************************************/
	virtual GObjectP Clone() const;

	/****************************************************************************
	**
	** GObject
	**
	** @name	Boxing
	** @brief	����
	** @return	{const GObject *} �Ե�ǰ����ķ���
	**
	** ��������ǽ���ǰ����ת��Ϊ�������͵ķ��������Ǵ������µ�ʵ����
	**
	****************************************************************************/
	virtual const GObject *Boxing() const;

	/****************************************************************************
	**
	** GObject
	**
	** @name		Unboxing
	** @brief		����
	** @param[in]	obj {const GObject *} ���������ָ��
	** @return		{gbool} ��������Ƿ�ɹ�
	**
	** ��һ�����������ָ����䵽��ǰ�ࡣ
	**
	****************************************************************************/
	virtual gbool Unboxing(const GObject *obj);

	/****************************************************************************
	**
	** GObject
	**
	** @name	ToString
	** @brief	�����ڶ���ת��Ϊ�ַ���
	** @return	{GString} ת���ɵ��ַ������ͣ�GString��
	** @see		GString
	**
	****************************************************************************/
	virtual GString ToString() const;

	/****************************************************************************
	**
	** GObject
	**
	** @name	ToBytes
	** @brief	�����ڶ���ת��Ϊ����������
	** @return	{GBytes} ת���ɵĶ������������ͣ�GBytes��
	** @see		GBytes
	**
	****************************************************************************/
	virtual GBytes ToBytes() const;

	/*
	virtual gbool FromString(const GString &str);
	virtual GBytes ToBytes() const;
	virtual gbool FromBytes(const GBytes &bytes);
	*/

	/****************************************************************************
	**
	** GObject
	**
	** @name	ClassCode
	** @brief	��ȡ��ǰ����������кţ�ClassCode��
	** @return	{guint} �����к�
	**
	****************************************************************************/
	virtual guint ClassCode() const;

	/****************************************************************************
	**
	** GObject
	**
	** @name	ClassCode
	** @brief	��ȡ��ǰ����Ĺ�ϣ�루HashCode��
	** @return	{guint} ��ϣ��ֵ
	**
	****************************************************************************/
	virtual guint HashCode() const;

	/****************************************************************************
	**
	** GObject
	**
	** @name		Equals
	** @brief		�ж϶����Ƿ�ֵ���
	** @param[in]	obj {const GObject *} ���������ָ��
	** @return		{gbool} ����ȣ��򷵻�true�����򷵻�false
	**
	****************************************************************************/
	virtual gbool Equals(const GObject *obj) const;

	/****************************************************************************
	**
	** GObject
	**
	** @name	Serializable
	** @brief	��ǰ�����Ƿ�֧�����л�
	** @return	{gbool} ��֧�����л����򷵻�true�����򷵻�false
	**
	** ������֧�����л�����Ӧ�ṩ���л���Serialize���ͷ����л���Deserialize���ķ�����
	** ������������ģ�巽����template������Ҫ�������л��ĵ����ࣨArchiveT��������Ҫ
	** ģ��GSerialization��֧�֡�
	**
	****************************************************************************/
	virtual gbool Serializable() const;

	/****************************************************************************
	**
	** GObject
	**
	** @name		Serialize
	** @brief		���л�
	** @param[out]	archive {ArchiveT &} �鵵��
	** @return		{gbool} ���л��Ƿ�ɹ�
	** @see			GArchive
	**
	** ����ǰ������������л��������У���Ҫ���л�ģ��GSerialization��֧��
	**
	****************************************************************************/
	//template<typename ArchiveT> gbool Serialize(ArchiveT &archive) const;

	/****************************************************************************
	**
	** GObject
	**
	** @name		Deserialize
	** @brief		�����л�
	** @param[in]	archive {ArchiveT &} �鵵��
	** @return		{gbool} �����л��Ƿ�ɹ�
	** @see			GArchive
	**
	** �����������л�Ϊ��ǰ��������ݣ���Ҫ���л�ģ��GSerialization��֧��
	**
	****************************************************************************/
	//template<typename ArchiveT> gbool Deserialize(ArchiveT &archive);
};

G_END_NAMESPACE

#endif // _CORE_OBJECT_H_
