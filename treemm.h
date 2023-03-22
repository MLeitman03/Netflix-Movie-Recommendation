#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <iostream>


template <typename KeyType, typename ValueType>
class TreeMultimap //binary search tree-based map to map any type of data to any other type of data
{
private:
    struct Node
    {
        Node (const KeyType& key, const ValueType& value)
        {
            m_key = key;
            m_values.push_back(value);
            left = nullptr;
            right = nullptr;
        }
        KeyType m_key;
        std::vector<ValueType> m_values;
        Node *left, *right;
    };
public:
    class Iterator
    {
      public:
        Iterator()
        {
            index = 0;
            isValid = false;
            m_node = nullptr;
        }
        
        Iterator(bool valid, Node* node)
        {
            isValid = valid;
            m_node = node;
            index = 0;
        }

        ValueType& get_value() const
        {
            return m_node->m_values[index];
        }

        bool is_valid() const
        {
            return isValid;
        }

        void advance()
        {
            index++;
            if (index >= m_node->m_values.size())
                isValid = false;
            else
                isValid = true;
        }

      private:
        bool isValid;
        int index;
        Node* m_node;
    };
    
    TreeMultimap()
    {
        m_root = nullptr;
    }

    ~TreeMultimap()
    {
        FreeTree(m_root);
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        if (m_root == nullptr)
        {
            m_root = new Node(key,value);
            return;
        }
        Node *cur = m_root;
        for (;;)
        {
            if (key == cur->m_key)
            {
                cur->m_values.push_back(value);
                return;
            }
            if (key < cur->m_key)
            {
                if (cur->left != nullptr)
                    cur = cur->left;
                else
                {
                    cur->left = new Node(key,value);
                    return;
                }
            }
            else if (key > cur->m_key)
            {
                if (cur->right != nullptr)
                    cur = cur->right;
                else
                {
                    cur->right = new Node(key,value);
                    return;
                }
            }
        }
    }

    Iterator find(const KeyType& key) const
    {
        Node *ptr = m_root;
        
        while (ptr != nullptr)
        {
            if (key == ptr->m_key)
            {
                Iterator it = Iterator(true, ptr);
                return it;
            }
            else if (key < ptr->m_key)
                ptr = ptr->left;
            else
                ptr = ptr->right;
        }
        
        
        Iterator it2 = Iterator();
        return it2;
    }

  private:
    Node *m_root;
    void FreeTree(Node *cur)
    {
        if (cur == nullptr)
            return;
        FreeTree(cur->left);
        FreeTree(cur->right);
        delete cur;
    }
};

#endif // TREEMULTIMAP_INCLUDED
