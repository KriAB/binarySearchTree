#ifndef BITREE_H
#define BITREE_H


class BiSearchTree
{

private:
    struct node
    {
        int key;
        node* left;
        node* right;

    };
    node* root;

    void AddLeafPrivate(int m_key, node* Ptr);
    void PrintInOrderPrivate(node* Ptr);
    node* ReturnNodePrivate(int m_key, node* Ptr);
    int FindSmallestPrivate(node* Ptr);
    void RemoveNodePrivate(int m_key, node* parent);
    void RemoveRootMatch();
    void RemoveMatch(node* parent, node* match, bool left); //not root
    public:
    BiSearchTree();
    node* CreateLeaf(int m_key);
    void AddLeaf(int m_key);
    void PrintInOrder();
    node* ReturnNode(int m_key);
    int ReturnRootKey();
    void PrintChildren(int m_key);
    int FindSmallest();
    void RemoveNode(int m_key);

    //vector<node> createdNodes;
};

#endif // BITREE_H
