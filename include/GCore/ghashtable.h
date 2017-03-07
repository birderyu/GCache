#ifndef _CORE_HASH_TABLE_H_
#define _CORE_HASH_TABLE_H_

#include "ghash.h"
#include "glist.h"
#include "gdynamicarray.h"
#include "gstructure.h"
#include "gnocopyable.h"

#define G_HASH_TABLE_DEFAULT_MODULE_SIZE		0x10
#define G_HASH_TABLE_MAX_MODULE_SIZE			0x40000000 // 2 30
#define G_HASH_TABLE_DEFAULT_LOAD_FACTOR		0.75f

// һ��Ĭ�ϵ�hash�ڵ�
template<typename KeyT, typename ValueT>
struct GHashTableNode 
	: public GNextNodeT<GHashTableNode<KeyT, ValueT>>
	, public GPairNodeT<KeyT, ValueT>
	, public GNewT<GHashTableNode<KeyT, ValueT>>
{
	GHashTableNode(const KeyT &key = KeyT(),
		const ValueT &value = ValueT(),
		GHashTableNode<KeyT, ValueT> *next = GNULL);
};

/// ��ϣ��
template<typename KeyT, typename ValueT,
	typename HashT = GHashF<KeyT>,
	typename CompareT = GEqualToF<KeyT>,
	typename NodeT = GHashTableNode<KeyT, ValueT>>
class GHashTable
	: public GObject
{
public:
	typedef GHashTable<KeyT, ValueT, HashT, CompareT, NodeT> Table;
	typedef NodeT Node;
	typedef GList<NodeT *> Nodes;
	typedef GList<const NodeT *> ConstNodes;

private:
	static const Table m_gTable;

private:
	// ��ϣ��ͻ
	// ��������
	class GHashSlot
		: public GNewT<GHashSlot>
		, private GNocopyable
	{
	public:
		NodeT *m_pHead;
		gsize m_nSize;

		GHashSlot() 
			: m_pHead(GNULL), m_nSize(0), m_rCompare(m_gTable.m_fCompare) {}
		~GHashSlot() { Free(); }

		GHashSlot &operator=(const GHashSlot &slot)
		{
			m_pHead = slot.m_pHead;
			m_nSize = slot.m_nSize;
			return *this;
		}

		gvoid Free()
		{
			if (!m_pHead)
			{
				return;
			}
			NodeT *pNode = m_pHead;
			while (pNode)
			{
				m_pHead = pNode;
				pNode = pNode->m_pNext;
				delete m_pHead;
			}
			m_pHead = GNULL;
			m_nSize = 0;
		}
		gsize Size()
		{
			return m_nSize;
		}
		gbool IsEmpty()
		{
			return m_pHead == GNULL || m_nSize == 0;
		}
		
		gbool Search(const KeyT &key, gbool unique, Nodes &nodes)
		{
			if (!m_pHead)
			{
				return false;
			}
			NodeT *pNode = m_pHead;
			while (pNode)
			{
				if (m_rCompare(pNode->m_tKey, key))
				{
					nodes.PushBack(pNode);
					if (unique)
					{
						// ���������ظ�Ԫ��
						return true;
					}
				}
				pNode = pNode->m_pNext;
			}
			return !nodes.IsEmpty();
		}
		gbool Search(const KeyT &key, gbool unique, ConstNodes &nodes) const
		{
			if (!m_pHead)
			{
				return false;
			}
			const NodeT *pNode = m_pHead;
			while (pNode)
			{
				if (m_rCompare(pNode->m_tKey, key))
				{
					nodes.PushBack(pNode);
					if (unique)
					{
						// ���������ظ�Ԫ��
						return true;
					}
				}
				pNode = pNode->m_pNext;
			}
			return !nodes.IsEmpty();
		}
				
		// ֻ������һ��
		NodeT *SearchFirst(const KeyT &key)
		{
			if (!m_pHead)
			{
				return false;
			}
			NodeT *pNode = m_pHead;
			while (pNode)
			{
				if (m_rCompare(pNode->m_tKey, key))
				{
					return pNode;
				}
				pNode = pNode->m_pNext;
			}
			return GNULL;
		}
		const NodeT *SearchFirst(const KeyT &key) const
		{
			if (!m_pHead)
			{
				return false;
			}
			const NodeT *pNode = m_pHead;
			while (pNode)
			{
				if (m_rCompare(pNode->m_tKey, key))
				{
					return pNode;
				}
				pNode = pNode->m_pNext;
			}
			return GNULL;
		}
		gbool Contains(const KeyT &key) const
		{
			if (!m_pHead)
			{
				return false;
			}
			NodeT *pNode = m_pHead;
			while (pNode)
			{
				if (m_rCompare(pNode->m_tKey, key))
				{
					return true;
				}
			}
			return false;
		}

		NodeT *Insert(const KeyT &key, const ValueT &value, gbool unique, gbool &realInsert)
		{
			if (!unique)
			{
				// unique = false���������ظ�Ԫ��
				// ֱ�Ӳ��뵽����
				NodeT *node = new NodeT(key, value);
				node->m_pNext = m_pHead;
				m_pHead = node;
				m_nSize++;
				realInsert = true;
				return node; // �����ɹ�
			}
			else
			{
				// unique = true�����������ظ�Ԫ��
				NodeT *pnode = SearchFirst(key);
				if (!pnode)
				{
					// �����ڣ����뵽����
					NodeT *node = new NodeT(key, value);
					node->m_pNext = m_pHead;
					m_pHead = node;
					m_nSize++;
					realInsert = true;
					return node;
				}
				else
				{
					// �Ѵ��ڣ�������ͬ�Ľڵ�
					pnode->m_tValue = value;
					realInsert = false;
					return pnode;
				}
			}
		}
		NodeT *Insert(const KeyT &key, ValueT &&value, gbool unique, gbool &realInsert)
		{
			if (!unique)
			{
				// unique = false���������ظ�Ԫ��
				// ֱ�Ӳ��뵽����
				NodeT *node = new NodeT(key, GForward<ValueT>(value));
				node->m_pNext = m_pHead;
				m_pHead = node;
				m_nSize++;
				realInsert = true;
				return node; // �����ɹ�
			}
			else
			{
				// unique = true�����������ظ�Ԫ��
				NodeT *pnode = SearchFirst(key);
				if (!pnode)
				{
					// �����ڣ����뵽����
					NodeT *node = new NodeT(key, GForward<ValueT>(value));
					node->m_pNext = m_pHead;
					m_pHead = node;
					m_nSize++;
					realInsert = true;
					return node;
				}
				else
				{
					// �Ѵ��ڣ�������ͬ�Ľڵ�
					pnode->m_tValue = GForward<ValueT>(value);
					realInsert = false;
					return pnode;
				}
			}
		}
		// ����ɾ�����ݵ����������򷵻�0
		gsize Delete(const KeyT &key, gbool unique)
		{
			if (!m_pHead)
			{
				return 0;
			}

			if (!unique)
			{
				// unique = false���������ظ�Ԫ��
				gsize node_size = 0;
				NodeT *pNode = m_pHead;
				NodeT *preNode = GNULL;
				while (pNode)
				{
					if (m_rCompare(pNode->m_tKey, key))
					{
						// ɾ���ڵ�
						if (DeleteAt(pNode, preNode))
						{
							node_size++;
						}
						pNode = preNode->m_pNext;
					}
					else
					{
						preNode = pNode;
						pNode = pNode->m_pNext;
					}
				}
				return node_size;
			}
			else
			{
				// unique = true�����������ظ�Ԫ��
				NodeT *pNode = m_pHead;
				NodeT *preNode = GNULL;
				while (pNode)
				{
					if (m_rCompare(pNode->m_tKey, key))
					{
						// ɾ���ڵ㲢����
						if (DeleteAt(pNode, preNode))
						{
							return 1;
						}
					}
					preNode = pNode;
					pNode = pNode->m_pNext;
				}
				return 0;
			}
			return 0;
		}

		// node :��ɾ���Ľڵ�
		// preNode����ɾ���ڵ��ǰ���ڵ�
		gbool DeleteAt(NodeT *node, NodeT *preNode)
		{
			if (!node)
			{
				return false;
			}

			if (preNode)
			{
				preNode->m_pNext = node->m_pNext;
			}
			else
			{
				m_pHead = node->m_pNext;
			}
			
			delete node;
			m_nSize--;
			return true;
		}

		const CompareT &m_rCompare;
	};

public:
	GHashTable(gsize module = G_HASH_TABLE_DEFAULT_MODULE_SIZE, 
		gfloat factor = G_HASH_TABLE_DEFAULT_LOAD_FACTOR,
		gbool unique = true);
	GHashTable(const GHashTable<KeyT, ValueT, HashT, CompareT, NodeT> &table);
	GHashTable(GHashTable<KeyT, ValueT, HashT, CompareT, NodeT> &&table);
	~GHashTable();

	GHashTable<KeyT, ValueT, HashT, CompareT, NodeT> &operator=(const GHashTable<KeyT, ValueT, HashT, CompareT, NodeT> &table);
	GHashTable<KeyT, ValueT, HashT, CompareT, NodeT> &operator=(GHashTable<KeyT, ValueT, HashT, CompareT, NodeT> &&table);

	gsize Size() const;
	gbool IsEmpty() const;

	gvoid Dispose();

	gbool Contains(const KeyT &key) const;

	NodeT *FirstNode();
	const NodeT *FirstNode() const;

	NodeT *NextNode(NodeT *node);
	const NodeT *NextNode(const NodeT *node) const;

	NodeT *Find(const KeyT &key);
	const NodeT *Find(const KeyT &key) const;
	gbool Find(const KeyT &key, Nodes &nodes);
	gbool Find(const KeyT &key, ConstNodes &nodes) const;

	NodeT *Insert(const KeyT &key, const ValueT &value);
	NodeT *Insert(const KeyT &key, ValueT &&value);
	gvoid Delete(const KeyT &key);

	gbool operator==(const GHashTable<KeyT, ValueT, HashT, CompareT, NodeT> &table) const;
	gbool operator!=(const GHashTable<KeyT, ValueT, HashT, CompareT, NodeT> &table) const;

protected:
	/// �ж�����GHashSlot�Ƿ����
	gbool HashSlotEquals(const GHashSlot *slot1, const GHashSlot *slot2) const;

	/// ������
	gvoid Inflate(gsize module);

	/// ���� >= n����С2��n�η�ֵ����n = 30���򷵻�32
	/// ���⴦�������ֵһ��λ��2��4�η���2��30�η�֮��
	gsize RoundUpToPowerOf2(gsize module) const;

	/// ��ȡkey���±�
	gsize IndexOf(const KeyT &key, gsize module) const;

private:
	gfloat m_nFactor;						// �������ӣ�һ��ȷ���˾Ͳ����޸�
	gbool m_bUnique;						// �����Ƿ�Ψһ��һ��ȷ���˾Ͳ����޸�

	gsize m_nSize;							// ʵ��Ԫ�صĸ���
	gsize m_nThreshold;						// ������ֵ����ֵ����ģֵ*m_nFactor��Ϊ�˼��ٸ������㣬�����ֵ�洢����
	GDynamicArray<GHashSlot*> m_tBuckets;	// ��ϣͰ
	static const HashT m_fHash;
	static const CompareT m_fCompare;
};

#include "ghashtable.inl"

#undef G_HASH_TABLE_DEFAULT_LOAD_FACTOR
#undef G_HASH_TABLE_MAX_MODULE_SIZE
#undef G_HASH_TABLE_DEFAULT_MODULE_SIZE

#endif // _CORE_HASH_TABLE_H_