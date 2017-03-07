#ifndef _CORE_STRUCTURE_H_
#define _CORE_STRUCTURE_H_

#include "gglobal.h"

/// һά��ͨ��ģʽ����
template<typename ListT>
struct GListT
{
	static const gsize MAX_SIZE = G_LIST_MAX_SIZE;
	static const gsize NULL_POS = G_LIST_NULL_POS;
};

/// ��ά��ͨ��ģʽ����
template<typename TableT>
struct GTableT
{
	static const gsize MAX_ROW_SIZE = G_LIST_MAX_SIZE;
	static const gsize NULL_ROW_POS = G_LIST_NULL_POS;
	static const gsize MAX_COLUMN_SIZE = G_LIST_MAX_SIZE;
	static const gsize NULL_COLUMN_POS = G_LIST_NULL_POS;
};

/// ��������ڵ�
template<typename NodeT>
struct GNextNodeT
{
	NodeT *m_pNext;

	GNextNodeT(NodeT *);
};

/// ˫������ڵ�
template<typename NodeT>
struct GPreviousNextNodeT
{
	NodeT *m_pPrevious;
	NodeT *m_pNext;

	GPreviousNextNodeT(NodeT *previous, NodeT *next);
};

/// �������ڵ�
template<typename NodeT>
struct GBinaryTreeNodeT
{
	NodeT *m_pParent;	// ˫��
	NodeT *m_pLeft;		// ����
	NodeT *m_pRight;	// �Һ���

	GBinaryTreeNodeT(NodeT *parent, NodeT *left, NodeT *right);

	// ���ֵ�
	const NodeT *LeftSibling() const;

	// ���ֵ�
	const NodeT *RightSibling() const;

	// ���������ǰ���ڵ�
	const NodeT *Next() const;
	NodeT *Next();

	// ��������ĺ�̽ڵ�
	const NodeT *Previous() const;
	NodeT *Previous();

	// ����������׽ڵ�
	const NodeT *First() const;
	NodeT *First();

	// ���������β�ڵ�
	const NodeT *Last() const;
	NodeT *Last();
};

/// ���ݽڵ�
template<typename DataT>
struct GDataNodeT
{
	DataT m_tData;

	GDataNodeT(const DataT &);
};

/// �����ӽڵ�
template<typename NodeT>
struct GChildNodeT
{
	NodeT *m_pChild;

	GChildNodeT(const NodeT *);
};

/// ��ֵ�Խڵ�
template<typename KeyT, typename ValueT>
struct GPairNodeT
{
	KeyT m_tKey;
	ValueT m_tValue;

	GPairNodeT(const KeyT &key, const ValueT &value);
	GPairNodeT(const KeyT &key, ValueT &&value);
};

// �ƽڵ�
struct GDummyNodeT
{

};

#include "gstructure.inl"

#endif // _CORE_STRUCTURE_H_