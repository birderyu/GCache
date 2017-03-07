#ifndef _CORE_RED_BLACK_TREE_INLINE_
#define _CORE_RED_BLACK_TREE_INLINE_

#define G_RED_BLACK_TREE_NODE_TEMPLATE	template<typename KeyT, typename ValueT>
#define G_RED_BLACK_TREE_NODE_QUAL		GReadBlackTreeNode<KeyT, ValueT>
#define G_RED_BLACK_TREE_TEMPLATE		template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
#define G_RED_BLACK_TREE_QUAL			GReadBlackTree<KeyT, ValueT, CompareT, NodeT>

G_RED_BLACK_TREE_NODE_TEMPLATE
GINLINE G_RED_BLACK_TREE_NODE_QUAL::GReadBlackTreeNode(
	const KeyT &key,
	const ValueT &value,
	G_RED_BLACK_TREE_NODE_QUAL *parent,
	G_RED_BLACK_TREE_NODE_QUAL *left,
	G_RED_BLACK_TREE_NODE_QUAL *right,
	gsmall color)
	: GBinaryTreeNodeT<G_RED_BLACK_TREE_NODE_QUAL>(parent, left, right)
	, GPairNodeT<KeyT, ValueT>(key, value)
	, m_nColor(color)
{

}

G_RED_BLACK_TREE_NODE_TEMPLATE
GINLINE G_RED_BLACK_TREE_NODE_QUAL::GReadBlackTreeNode(
	const KeyT &key, ValueT &&value,
	G_RED_BLACK_TREE_NODE_QUAL *parent,
	G_RED_BLACK_TREE_NODE_QUAL *left,
	G_RED_BLACK_TREE_NODE_QUAL *right,
	gsmall color)
	: GBinaryTreeNodeT<G_RED_BLACK_TREE_NODE_QUAL>(parent, left, right)
	, GPairNodeT<KeyT, ValueT>(key, GForward<ValueT>(value))
	, m_nColor(color)
{

}

G_RED_BLACK_TREE_TEMPLATE
GINLINE G_RED_BLACK_TREE_QUAL::~GReadBlackTree()
{

}

G_RED_BLACK_TREE_TEMPLATE
GINLINE NodeT *G_RED_BLACK_TREE_QUAL::Insert(const KeyT &key, const ValueT &value, gbool *realInsert)
{
	NodeT *insert_point = GNULL; // ����λ�õ�˫�׽ڵ�
	NodeT *node = m_pRoot;
	while (node)
	{
		insert_point = node;
		gint ret = m_fCompare(key, node->m_tKey);
		if (ret < 0)
		{
			node = node->m_pLeft;
		}
		else if (ret > 0)
		{
			node = node->m_pRight;
		}
		else
		{
			if (realInsert)
			{
				*realInsert = false;
			}
			insert_point->m_tValue = value;
			return insert_point;
		}
	}

	// ��������ڵ�
	NodeT* insert_node = new NodeT(key, value);
	if (!insert_point)
	{
		//�������һ�ſ���
		m_pRoot = insert_node;
		insert_node->m_nColor = G_RED_BLACK_TREE_NODE_BLACK;
	}
	else
	{
		// �ҵ�����Ĳ���λ��
		gint ret = m_fCompare(key, insert_point->m_tKey);
		if (ret < 0)
		{
			insert_point->m_pLeft = insert_node;
		}
		else if (ret > 0)
		{
			insert_point->m_pRight = insert_node;
		}
		else
		{
			// ����������ͬ�����
		}
		insert_node->m_pParent = insert_point;

		// �����޸�
		InsertFixUp(insert_node);
	}

	if (realInsert)
	{
		*realInsert = true;
	}
	return insert_node;
}

G_RED_BLACK_TREE_TEMPLATE
GINLINE NodeT *G_RED_BLACK_TREE_QUAL::Insert(const KeyT &key, ValueT &&value, gbool *realInsert)
{
	NodeT *insert_point = GNULL; // ����λ�õ�˫�׽ڵ�
	NodeT *node = m_pRoot;
	while (node)
	{
		insert_point = node;
		gint ret = m_fCompare(key, node->m_tKey);
		if (ret < 0)
		{
			node = node->m_pLeft;
		}
		else if (ret > 0)
		{
			node = node->m_pRight;
		}
		else
		{
			if (realInsert)
			{
				*realInsert = false;
			}
			insert_point->m_tValue = GForward<ValueT>(value);
			return insert_point;
		}
	}

	// ��������ڵ�
	NodeT* insert_node = new NodeT(key, GForward<ValueT>(value));
	if (!insert_point)
	{
		//�������һ�ſ���
		m_pRoot = insert_node;
		insert_node->m_nColor = G_RED_BLACK_TREE_NODE_BLACK;
	}
	else
	{
		// �ҵ�����Ĳ���λ��
		gint ret = m_fCompare(key, insert_point->m_tKey);
		if (ret < 0)
		{
			insert_point->m_pLeft = insert_node;
		}
		else if (ret > 0)
		{
			insert_point->m_pRight = insert_node;
		}
		else
		{
			// ����������ͬ�����
		}
		insert_node->m_pParent = insert_point;

		// �����޸�
		InsertFixUp(insert_node);
	}

	if (realInsert)
	{
		*realInsert = true;
	}
	return insert_node;
}

G_RED_BLACK_TREE_TEMPLATE
GINLINE gvoid G_RED_BLACK_TREE_QUAL::Delete(const KeyT &key, gbool *realDelete)
{
	NodeT* delete_point = Find(key);
	Delete(delete_point, realDelete);
}

G_RED_BLACK_TREE_TEMPLATE
GINLINE gvoid G_RED_BLACK_TREE_QUAL::Delete(NodeT *delete_point, gbool *realDelete)
{
	if (!delete_point)
	{
		if (realDelete)
		{
			*realDelete = false;
		}
		return;
	}
	if (delete_point->m_pLeft && delete_point->m_pRight)
	{
		// �ҵ��ڵ㣬�Ҹýڵ���������������
		NodeT *successor = delete_point->m_pRight->First();
		SwitchNode(delete_point, successor);
	}

	NodeT *delete_point_child = GNULL;
	if (!delete_point->m_pLeft)
	{
		delete_point_child = delete_point->m_pRight;
	}
	else if (!delete_point->m_pRight)
	{
		delete_point_child = delete_point->m_pLeft;
	}

	NodeT *delete_point_parent = delete_point->m_pParent;
	if (delete_point_child)
	{
		delete_point_child->m_pParent = delete_point_parent;
	}

	if (!delete_point_parent)
	{
		m_pRoot = delete_point_child;
	}
	else
	{
		if (delete_point == delete_point_parent->m_pLeft)
		{
			delete_point_parent->m_pLeft = delete_point_child;
		}
		else
		{
			delete_point_parent->m_pRight = delete_point_child;
		}
	}

	if (delete_point->m_nColor == G_RED_BLACK_TREE_NODE_BLACK)
	{
		if (delete_point_child && delete_point_child != m_pRoot)
		{
			DeleteFixUp(delete_point_child);
		}
	}

	if (realDelete)
	{
		*realDelete = true;
	}
	delete delete_point;
}

G_RED_BLACK_TREE_TEMPLATE
GINLINE gvoid G_RED_BLACK_TREE_QUAL::InsertFixUp(NodeT *node)
{
	while (node->m_pParent &&
		node->m_pParent->m_nColor == G_RED_BLACK_TREE_NODE_RED)
	{
		if (node->m_pParent == node->m_pParent->m_pParent->m_pLeft)
		{
			NodeT *uncle = node->m_pParent->m_pParent->m_pRight;
			if (!uncle || uncle->m_nColor == G_RED_BLACK_TREE_NODE_BLACK)
			{
				if (node == node->m_pParent->m_pRight)
				{
					node = node->m_pParent;
					RotateLeft(node);
				}
				else
				{
					node->m_pParent->m_nColor = G_RED_BLACK_TREE_NODE_BLACK;
					node->m_pParent->m_pParent->m_nColor = G_RED_BLACK_TREE_NODE_RED;
					RotateRight(node->m_pParent->m_pParent);
				}
			}
			else if (uncle->m_nColor == G_RED_BLACK_TREE_NODE_RED)
			{
				node->m_pParent->m_nColor = G_RED_BLACK_TREE_NODE_BLACK;
				uncle->m_nColor = G_RED_BLACK_TREE_NODE_BLACK;
				node->m_pParent->m_pParent->m_nColor = G_RED_BLACK_TREE_NODE_RED;
				node = node->m_pParent->m_pParent;
			}
		}
		else
		{
			NodeT *uncle = node->m_pParent->m_pParent->m_pLeft;
			if (!uncle || uncle->m_nColor == G_RED_BLACK_TREE_NODE_BLACK)
			{
				if (node == node->m_pParent->m_pLeft)
				{
					node = node->m_pParent;
					RotateRight(node);
				}
				else
				{
					node->m_pParent->m_nColor = G_RED_BLACK_TREE_NODE_BLACK;
					node->m_pParent->m_pParent->m_nColor = G_RED_BLACK_TREE_NODE_RED;
					RotateLeft(node->m_pParent->m_pParent);
				}
			}
			else if (uncle->m_nColor == G_RED_BLACK_TREE_NODE_RED)
			{
				node->m_pParent->m_nColor = G_RED_BLACK_TREE_NODE_BLACK;
				uncle->m_nColor = G_RED_BLACK_TREE_NODE_BLACK;
				uncle->m_pParent->m_nColor = G_RED_BLACK_TREE_NODE_RED;
				node = node->m_pParent->m_pParent;
			}
		}
	}
	m_pRoot->m_nColor = G_RED_BLACK_TREE_NODE_BLACK;
}

G_RED_BLACK_TREE_TEMPLATE
GINLINE gvoid G_RED_BLACK_TREE_QUAL::DeleteFixUp(NodeT *node)
{
	while (node != m_pRoot && node->m_nColor == G_RED_BLACK_TREE_NODE_BLACK)
	{
		if (node == node->m_pParent->m_pLeft)
		{
			NodeT *brother = node->m_pParent->m_pRight;
			if (brother->m_nColor == G_RED_BLACK_TREE_NODE_RED)
			{
				brother->m_nColor = G_RED_BLACK_TREE_NODE_BLACK;
				node->m_pParent->m_nColor = G_RED_BLACK_TREE_NODE_RED;
				RotateLeft(node->m_pParent);
			}
			else
			{
				if (brother->m_pLeft->m_nColor == G_RED_BLACK_TREE_NODE_BLACK
					&& brother->m_pRight->m_nColor == G_RED_BLACK_TREE_NODE_BLACK)
				{
					brother->m_nColor = G_RED_BLACK_TREE_NODE_RED;
					node = node->m_pParent;
				}
				else if (brother->m_pRight->m_nColor == G_RED_BLACK_TREE_NODE_BLACK)
				{
					brother->m_nColor = G_RED_BLACK_TREE_NODE_RED;
					brother->m_pLeft->m_nColor = G_RED_BLACK_TREE_NODE_BLACK;
					RotateRight(brother);
				}
				else if (brother->m_pRight->m_nColor == G_RED_BLACK_TREE_NODE_RED)
				{
					brother->m_nColor = node->m_pParent->m_nColor;
					node->m_pParent->m_nColor = G_RED_BLACK_TREE_NODE_BLACK;
					brother->m_pRight->m_nColor = G_RED_BLACK_TREE_NODE_BLACK;
					RotateLeft(node->m_pParent);
					node = m_pRoot;
				}
			}
		}
		else
		{
			NodeT *brother = node->m_pParent->m_pLeft;
			if (brother->m_nColor == G_RED_BLACK_TREE_NODE_RED)
			{
				brother->m_nColor = G_RED_BLACK_TREE_NODE_BLACK;
				node->m_pParent->m_nColor = G_RED_BLACK_TREE_NODE_RED;
				RotateRight(node->m_pParent);
			}
			else
			{
				if (brother->m_pLeft->m_nColor == G_RED_BLACK_TREE_NODE_BLACK
					&& brother->m_pRight->m_nColor == G_RED_BLACK_TREE_NODE_BLACK)
				{
					brother->m_nColor = G_RED_BLACK_TREE_NODE_RED;
					node = node->m_pParent;
				}
				else if (brother->m_pLeft->m_nColor == G_RED_BLACK_TREE_NODE_BLACK)
				{
					brother->m_nColor = G_RED_BLACK_TREE_NODE_RED;
					brother->m_pRight->m_nColor = G_RED_BLACK_TREE_NODE_BLACK;
					RotateLeft(brother);
				}
				else if (brother->m_pLeft->m_nColor == G_RED_BLACK_TREE_NODE_RED)
				{
					brother->m_nColor = node->m_pParent->m_nColor;
					node->m_pParent->m_nColor = G_RED_BLACK_TREE_NODE_BLACK;
					brother->m_pLeft->m_nColor = G_RED_BLACK_TREE_NODE_BLACK;
					RotateRight(node->m_pParent);
					node = m_pRoot;
				}
			}
		}
	}
	//���node��Ϊ����㣬
	node->m_nColor = G_RED_BLACK_TREE_NODE_BLACK;    //����Ϊ��ɫ��
}

G_RED_BLACK_TREE_TEMPLATE
GINLINE gvoid G_RED_BLACK_TREE_QUAL::RotateLeft(NodeT *node)
{
	if (!node || !node->m_pRight)
	{
		return;
	}
	NodeT *lower_right = node->m_pRight;
	lower_right->m_pParent = node->m_pParent;
	node->m_pRight = lower_right->m_pLeft;
	if (lower_right->m_pLeft)
	{
		lower_right->m_pLeft->m_pParent = node;
	}
	if (!node->m_pParent)
	{
		// nodeΪ���ڵ�
		m_pRoot = lower_right;
	}
	else
	{
		if (node == node->m_pParent->m_pLeft)
		{
			node->m_pParent->m_pLeft = lower_right;
		}
		else
		{
			node->m_pParent->m_pRight = lower_right;
		}
	}
	node->m_pParent = lower_right;
	lower_right->m_pLeft = node;
}

G_RED_BLACK_TREE_TEMPLATE
GINLINE gvoid G_RED_BLACK_TREE_QUAL::RotateRight(NodeT *node)
{
	if (!node || !node->m_pLeft)
	{
		return;
	}
	NodeT *lower_left = node->m_pLeft;
	node->m_pLeft = lower_left->m_pRight;
	lower_left->m_pParent = node->m_pParent;
	if (lower_left->m_pRight)
	{
		lower_left->m_pRight->m_pParent = node;
	}
	if (!node->m_pParent)
	{
		// nodeΪ���ڵ�
		m_pRoot = lower_left;
	}
	else
	{
		if (node == node->m_pParent->m_pRight)
		{
			node->m_pParent->m_pRight = lower_left;
		}
		else
		{
			node->m_pParent->m_pLeft = lower_left;
		}
	}
	node->m_pParent = lower_left;
	lower_left->m_pRight = node;
}

#undef G_RED_BLACK_TREE_QUAL
#undef G_RED_BLACK_TREE_TEMPLATE	
#undef G_RED_BLACK_TREE_NODE_QUAL	
#undef G_RED_BLACK_TREE_NODE_TEMPLATE

#endif // _CORE_RED_BLACK_TREE_INLINE_