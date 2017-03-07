#ifndef _CORE_B_TREE_H_
#define _CORE_B_TREE_H_

template<typename KeyT, typename ValueT, gsize KEY_MAX, gsize CHILD_MAX>
struct GBTreeNode
	: public GNewT<GBTreeNode<KeyT, ValueT, KEY_MAX, CHILD_MAX>>
{
	gbool m_bIsLeaf;					// �Ƿ���Ҷ�ӽڵ�  
	gsize m_nKeyNum;					// �ڵ�����Ĺؼ�������  
	KeyT m_tKeys[KEY_MAX];				// �ؼ�������
	ValueT m_tValues[KEY_MAX];			// ֵ����
	GBTreeNode *m_pChild[CHILD_MAX];	// ����ָ������  

	GBTreeNode(gbool b = true, gsize n = 0)
		:m_bIsLeaf(b), m_nKeyNum(n) {}
};

template<typename KeyT,
	typename ValueT,
	gsize M = 3, 
	gsize KEY_MAX = 2 * M - 1, 
	gsize KEY_MIN = M - 1,
	gsize CHILD_MAX = KEY_MAX + 1, 
	hugsize CHILD_MIN = KEY_MIN + 1,
	typename NodeT = GBTreeNode<KeyT, ValueT, KEY_MAX, CHILD_MAX>>
class GBTree
{
public:
	GBTree()
	{
		m_pRoot = NULL;  //����һ�ÿյ�B��  
	}

	~GBTree()
	{
		Clear();
	}

	gbool Insert(const KeyT &key, const ValueT &value)    //��B���в����½��key  
	{
		if (Contains(key))  //���ùؼ����Ƿ��Ѿ�����  
		{
			return false;
		}
		else
		{
			if (m_pRoot == NULL)//����Ƿ�Ϊ����  
			{
				m_pRoot = new NodeT();
			}
			if (m_pRoot->m_nKeyNum == KEY_MAX) //�����ڵ��Ƿ�����  
			{
				NodeT *pNode = new NodeT();  //�����µĸ��ڵ�  
				pNode->m_bIsLeaf = false;
				pNode->m_pChild[0] = m_pRoot;
				SplitChild(pNode, 0, m_pRoot);
				m_pRoot = pNode;  //���¸��ڵ�ָ��  
			}
			InsertNonFull(m_pRoot, key, value);
			return true;
		}
	}

	gbool Delete(const KeyT &key)    //��B��ɾ�����key  
	{
		if (!Search(m_pRoot, key))  //������  
		{
			return false;
		}
		if (m_pRoot->m_nKeyNum == 1)//�����������  
		{
			if (m_pRoot->m_bIsLeaf)
			{
				Clear();
				return true;
			}
			else
			{
				NodeT *pChild1 = m_pRoot->m_pChild[0];
				NodeT *pChild2 = m_pRoot->m_pChild[1];
				if (pChild1->m_nKeyNum == KEY_MIN&&pChild2->m_nKeyNum == KEY_MIN)
				{
					MergeChild(m_pRoot, 0);
					DeleteNode(m_pRoot);
					m_pRoot = pChild1;
				}
			}
		}
		Recursive_remove(m_pRoot, key);
		return true;
	}
	gvoid Display()const //��ӡ���Ĺؼ���  
	{
		DisplayInConcavo(m_pRoot, KEY_MAX * 10);
	}
	gbool Contains(const KeyT &key)const   //����key�Ƿ������B����  
	{
		return Search(m_pRoot, key);
	}
	gvoid Clear()                      //���B��  
	{
		Recursive_clear(m_pRoot);
		m_pRoot = NULL;
	}
private:
	//ɾ����  
	gvoid Recursive_clear(NodeT *pNode)
	{
		if (pNode != NULL)
		{
			if (!pNode->m_bIsLeaf)
			{
				for (int i = 0; i <= pNode->m_nKeyNum; ++i)
					Recursive_clear(pNode->m_pChild[i]);
			}
			DeleteNode(pNode);
		}
	}

	//ɾ���ڵ�  
	gvoid DeleteNode(NodeT *&pNode)
	{
		if (pNode != NULL)
		{
			delete pNode;
			pNode = NULL;
		}
	}

	//���ҹؼ���  
	gbool Search(NodeT *pNode, const KeyT &key)const
	{
		if (pNode == NULL)  //���ڵ�ָ���Ƿ�Ϊ�գ���ýڵ��Ƿ�ΪҶ�ӽڵ�  
		{
			return false;
		}
		else
		{
			int i;
			for (i = 0; i<pNode->m_nKeyNum && key>*(pNode->m_tKeys + i); ++i)//�ҵ�ʹkey<=pNode->keyValue[i]��������С�±�i  
			{
			}
			if (i < pNode->m_nKeyNum && key == pNode->m_tKeys[i])
			{
				return true;
			}
			else
			{
				if (pNode->m_bIsLeaf)   //���ýڵ��Ƿ�ΪҶ�ӽڵ�  
				{
					return false;
				}
				else
				{
					return Search(pNode->m_pChild[i], key);
				}
			}
		}
	}

	//�����ӽڵ�  
	gvoid SplitChild(NodeT *pParent, int nChildIndex, NodeT *pChild)
	{
		//��pChild���ѳ�pLeftNode��pChild�����ڵ�  
		NodeT *pRightNode = new NodeT();//���Ѻ���ҽڵ�  
		pRightNode->m_bIsLeaf = pChild->m_bIsLeaf;
		pRightNode->m_nKeyNum = KEY_MIN;
		int i;
		for (i = 0; i < KEY_MIN; ++i)//�����ؼ��ֵ�ֵ  
		{
			pRightNode->m_tKeys[i] = pChild->m_tKeys[i + CHILD_MIN];
		}
		if (!pChild->m_bIsLeaf)  //�������Ҷ�ӽڵ㣬�������ӽڵ�ָ��  
		{
			for (i = 0; i < CHILD_MIN; ++i)
			{
				pRightNode->m_pChild[i] = pChild->m_pChild[i + CHILD_MIN];
			}
		}

		pChild->m_nKeyNum = KEY_MIN;  //�����������Ĺؼ��ָ���  

		for (i = pParent->m_nKeyNum; i > nChildIndex; --i)//�����ڵ��е�nChildIndex������йؼ��ֵ�ֵ������ָ�������һλ  
		{
			pParent->m_pChild[i + 1] = pParent->m_pChild[i];
			pParent->m_tKeys[i] = pParent->m_tKeys[i - 1];
		}
		++pParent->m_nKeyNum;  //���¸��ڵ�Ĺؼ��ָ���  
		pParent->m_pChild[nChildIndex + 1] = pRightNode;  //�洢������ָ��  
		pParent->m_tKeys[nChildIndex] = pChild->m_tKeys[KEY_MIN];//�ѽڵ���м�ֵ�ᵽ���ڵ�  
	}

	//�ڷ����ڵ��в���ؼ���  
	gvoid InsertNonFull(NodeT *pNode, const KeyT &key, const ValueT &value)
	{
		int i = pNode->m_nKeyNum;  //��ȡ�ڵ��ڹؼ��ָ���  
		if (pNode->m_bIsLeaf)      //pNode��Ҷ�ӽڵ�  
		{
			while (i > 0 && key < pNode->m_tKeys[i - 1])   //�Ӻ���ǰ�����ҹؼ��ֵĲ���λ��  
			{
				pNode->m_tKeys[i] = pNode->m_tKeys[i - 1];  //�����λ  
				--i;
			}
			pNode->m_tKeys[i] = key;		//����ؼ��ֵ�ֵ  
			pNode->m_tValues[i] = value;	//����ؼ��ֵ�ֵ  
			++pNode->m_nKeyNum; //���½ڵ�ؼ��ֵĸ���  
		}
		else//pNode���ڽڵ�  
		{
			while (i > 0 && key < pNode->m_tKeys[i - 1])   //�Ӻ���ǰ�����ҹؼ��ֵĲ��������  
				--i;
			NodeT *pChild = pNode->m_pChild[i];  //Ŀ���������ָ��   
			if (pChild->m_nKeyNum == KEY_MAX)  //�����ڵ�����  
			{
				SplitChild(pNode, i, pChild);//���������ڵ�  
				if (key > pNode->m_tKeys[i])   //ȷ��Ŀ������  
					pChild = pNode->m_pChild[i + 1];
			}
			InsertNonFull(pChild, key);  //����ؼ��ֵ�Ŀ�������ڵ�  
		}
	}

	//�����Ŵ�ӡ��  
	gvoid DisplayInConcavo(NodeT *pNode, int count)const
	{
		if (pNode != NULL)
		{
			int i, j;
			for (i = 0; i < pNode->m_nKeyNum; ++i)
			{
				if (!pNode->m_bIsLeaf)
				{
					DisplayInConcavo(pNode->m_pChild[i], count - 2);
				}
				for (j = count; j >= 0; --j)
				{
					cout << "-";
				}
				cout << pNode->m_tKeys[i] << endl;
			}
			if (!pNode->m_bIsLeaf)
			{
				DisplayInConcavo(pNode->m_pChild[i], count - 2);
			}
		}
	}

	//�ϲ������ӽڵ�  
	gvoid MergeChild(NodeT *pParent, int index)
	{
		NodeT *pChild1 = pParent->m_pChild[index];
		NodeT *pChild2 = pParent->m_pChild[index + 1];
		//��pChild2���ݺϲ���pChild1  
		pChild1->m_nKeyNum = KEY_MAX;
		pChild1->m_tKeys[KEY_MIN] = pParent->m_tKeys[index];//�����ڵ�index��ֵ����  
		int i;
		for (i = 0; i < KEY_MIN; ++i)
		{
			pChild1->m_tKeys[i + KEY_MIN + 1] = pChild2->m_tKeys[i];
		}
		if (!pChild1->m_bIsLeaf)
		{
			for (i = 0; i < CHILD_MIN; ++i)
			{
				pChild1->m_pChild[i + CHILD_MIN] = pChild2->m_pChild[i];
			}
		}

		//���ڵ�ɾ��index��key��index�����ǰ��һλ  
		--pParent->m_nKeyNum;
		for (i = index; i < pParent->m_nKeyNum; ++i)
		{
			pParent->m_tKeys[i] = pParent->m_tKeys[i + 1];
			pParent->m_pChild[i + 1] = pParent->m_pChild[i + 2];
		}
		DeleteNode(pChild2);  //ɾ��pChild2  
	}

	//�ݹ��ɾ���ؼ���  
	gvoid Recursive_remove(NodeT *pNode, const KeyT &key)
	{
		int i = 0;
		while (i<pNode->m_nKeyNum&&key>pNode->m_tKeys[i])
			++i;
		if (i < pNode->m_nKeyNum&&key == pNode->m_tKeys[i])//�ؼ���key�ڽڵ�pNode��  
		{
			if (pNode->m_bIsLeaf)//pNode�Ǹ�Ҷ�ڵ�  
			{
				//��pNode��ɾ��k  
				--pNode->m_nKeyNum;
				for (; i < pNode->m_nKeyNum; ++i)
				{
					pNode->m_tKeys[i] = pNode->m_tKeys[i + 1];
				}
				return;
			}
			else//pNode�Ǹ��ڽڵ�  
			{
				NodeT *pChildPrev = pNode->m_pChild[i];//�ڵ�pNode��ǰ��key���ӽڵ�  
				NodeT *pChildNext = pNode->m_pChild[i + 1];//�ڵ�pNode�к���key���ӽڵ�  
				if (pChildPrev->m_nKeyNum >= CHILD_MIN)//�ڵ�pChildPrev�����ٰ���CHILD_MIN���ؼ���  
				{
					T prevKey = GetPredecessor(pChildPrev); //��ȡkey��ǰ���ؼ���  
					Recursive_remove(pChildPrev, prevKey);
					pNode->m_tKeys[i] = prevKey;     //�滻��key��ǰ���ؼ���  
					return;
				}
				else if (pChildNext->m_nKeyNum >= CHILD_MIN)//�ڵ�pChildNext�����ٰ���CHILD_MIN���ؼ���  
				{
					T nextKey = getSuccessor(pChildNext); //��ȡkey�ĺ�̹ؼ���  
					Recursive_remove(pChildNext, nextKey);
					pNode->m_tKeys[i] = nextKey;     //�滻��key�ĺ�̹ؼ���  
					return;
				}
				else//�ڵ�pChildPrev��pChildNext�ж�ֻ����CHILD_MIN-1���ؼ���  
				{
					MergeChild(pNode, i);
					Recursive_remove(pChildPrev, key);
				}
			}
		}
		else//�ؼ���key���ڽڵ�pNode��  
		{
			NodeT *pChildNode = pNode->m_pChild[i];//����key���������ڵ�  
			if (pChildNode->m_nKeyNum == KEY_MIN)//ֻ��t-1���ؼ���  
			{
				NodeT *pLeft = i > 0 ? pNode->m_pChild[i - 1] : NULL;  //���ֵܽڵ�  
				NodeT *pRight = i < pNode->m_nKeyNum ? pNode->m_pChild[i + 1] : NULL;//���ֵܽڵ�  
				int j;
				if (pLeft&&pLeft->m_nKeyNum >= CHILD_MIN)//���ֵܽڵ�������CHILD_MIN���ؼ���  
				{
					//���ڵ���i-1�Ĺؼ���������pChildNode��  
					for (j = pChildNode->m_nKeyNum; j > 0; --j)
					{
						pChildNode->m_tKeys[j] = pChildNode->m_tKeys[j - 1];
					}
					pChildNode->m_tKeys[0] = pNode->m_tKeys[i - 1];

					if (!pLeft->m_bIsLeaf)
					{
						for (j = pChildNode->m_nKeyNum + 1; j > 0; --j) //pLeft�ڵ��к��ʵ���Ůָ����ֲ��pChildNode��  
						{
							pChildNode->m_pChild[j] = pChildNode->m_pChild[j - 1];
						}
						pChildNode->m_pChild[0] = pLeft->m_pChild[pLeft->m_nKeyNum];
					}
					++pChildNode->m_nKeyNum;
					pNode->m_tKeys[i] = pLeft->m_tKeys[pLeft->m_nKeyNum - 1];//pLeft�ڵ��е����ؼ���������pNode��  
					--pLeft->m_nKeyNum;
				}
				else if (pRight&&pRight->m_nKeyNum >= CHILD_MIN)//���ֵܽڵ�������CHILD_MIN���ؼ���  
				{
					//���ڵ���i�Ĺؼ���������pChildNode��  
					pChildNode->m_tKeys[pChildNode->m_nKeyNum] = pNode->m_tKeys[i];
					++pChildNode->m_nKeyNum;
					pNode->m_tKeys[i] = pRight->m_tKeys[0];//pRight�ڵ��е���С�ؼ���������pNode��  
					--pRight->m_nKeyNum;
					for (j = 0; j < pRight->m_nKeyNum; ++j)
					{
						pRight->m_tKeys[j] = pRight->m_tKeys[j + 1];
					}
					if (!pRight->m_bIsLeaf)
					{
						pChildNode->m_pChild[pChildNode->m_nKeyNum] = pRight->m_pChild[0];//pRight�ڵ��к��ʵ���Ůָ����ֲ��pChildNode��  
						for (j = 0; j <= pRight->m_nKeyNum; ++j)
						{
							pRight->m_pChild[j] = pRight->m_pChild[j + 1];
						}
					}
				}
				//�����ֵܽڵ㶼ֻ����CHILD_MIN-1���ڵ�  
				else if (pLeft)//�����ֵܺϲ�  
				{
					MergeChild(pNode, i - 1);
					pChildNode = pLeft;
				}
				else if (pRight)//�����ֵܺϲ�  
				{
					MergeChild(pNode, i);

				}
			}
			Recursive_remove(pChildNode, key);
		}
	}

	KeyT GetPredecessor(NodeT *pNode)//�ҵ�ǰ���ؼ���  
	{
		while (!pNode->m_bIsLeaf)
		{
			pNode = pNode->m_pChild[pNode->m_nKeyNum];
		}
		return pNode->m_tKeys[pNode->m_nKeyNum - 1];
	}

	KeyT GetSuccessor(NodeT *pNode)//�ҵ���̹ؼ���  
	{
		while (!pNode->m_bIsLeaf)
		{
			pNode = pNode->m_pChild[0];
		}
		return pNode->m_tKeys[0];
	}

private:
	NodeT * m_pRoot;  //B���ĸ��ڵ�  
};

#endif // _CORE_B_TREE_H_