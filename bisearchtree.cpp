#include "bisearchtree.h"
#include <iostream>

BiSearchTree::BiSearchTree()
{
    root = nullptr;
}

BiSearchTree::node *BiSearchTree::CreateLeaf(int m_key)
{
    node* newNode = new node;
    newNode->key = m_key;
    newNode->left = nullptr;
    newNode->right = nullptr;

    return newNode;
}

void BiSearchTree::AddLeaf(int m_key)
{
    AddLeafPrivate(m_key, root);
}



void BiSearchTree::AddLeafPrivate(int m_key, node *Ptr)
{
    //sjekker om root peker på noe
    if(root == nullptr)
    {
        root = CreateLeaf(m_key);
    }
    //hvis m_key er mindre en key
    else if (m_key < Ptr->key)
    {
        if(Ptr->left != nullptr)
        {   // hvis den peker på noe til venstre og vi må mer til venstre brukes en rekursiv funksjon.
            AddLeafPrivate(m_key, Ptr->left);
        }
        else
        {
            Ptr->left = CreateLeaf(m_key);
        }
    }
    // hvis m_key er større en key
    else if (m_key > Ptr->key)
    {
        if(Ptr->right != nullptr)
        {   // hvis den peker på noe til høyre og vi må mer til høyre brukes en rekursiv funksjon.
            AddLeafPrivate(m_key, Ptr->right);
        }
        else
        {
            Ptr->right = CreateLeaf(m_key);
        }
    }
    else
    {
        // hvis key er lik som en key i treet
        std::cout << "The key " << m_key << "has already been added to the tree\n";
    }
}



void BiSearchTree::PrintInOrder()
{
    PrintInOrderPrivate(root);
}


void BiSearchTree::PrintInOrderPrivate(node *Ptr)
{
    if(root != nullptr)
    {
        if(Ptr->left != nullptr)
        {
            PrintInOrderPrivate(Ptr->left);
        }
        std::cout << Ptr->key << " ";
        if(Ptr->right != nullptr)
        {
            PrintInOrderPrivate(Ptr->right);
        }
    }
    else
    {
        std::cout << "The tree is empty\n";
    }
}

BiSearchTree::node *BiSearchTree::ReturnNode(int m_key)
{
    return ReturnNodePrivate(m_key, root);
}

BiSearchTree::node *BiSearchTree::ReturnNodePrivate(int m_key, node *Ptr)
{
    if(Ptr != nullptr)
    {
        if(Ptr->key == m_key)
        {
            return Ptr;
        }
        else
        {
            if( m_key < Ptr->key)
            {
                return ReturnNodePrivate(m_key, Ptr->left);
            }
            else
            {
                return ReturnNodePrivate(m_key, Ptr->right);
            }
        }
    }
    else
    {
        return nullptr;
    }
}



int BiSearchTree::ReturnRootKey()
{
    if(root != nullptr)
    {
        return root->key;
    }
    else
    {
        return -1000;
    }

}

void BiSearchTree::PrintChildren(int m_key)
{
    //returnerer en pointer som peker på den noden
    node* Ptr = ReturnNode(m_key);

    if( Ptr != nullptr)
    {
        std::cout << "Parent Node = " << Ptr->key << std::endl;

        Ptr->left == nullptr ?
                    std::cout << "Left Child = nullptr\n":
                                 std::cout << "Left Child = " << Ptr->left->key << std::endl;

        Ptr->right == nullptr ?
                    std::cout << "Right Child = nullptr\n":
                                 std::cout << "Right Child = " << Ptr->right->key << std::endl;
    }
    else
    {
        std::cout << "Key " << m_key << " is not in the tree\n";
    }
}
int BiSearchTree::FindSmallest()
{
    return FindSmallestPrivate(root);
}


int BiSearchTree::FindSmallestPrivate(node *Ptr)
{
    if(root == nullptr)
    {
        std::cout << "The treei s empty\n";
        return -1000; //må sette negativ int value fordi, det ikke er en del av key values i treet
    }
    else
    {
        if(Ptr->left != nullptr)
        {
            return FindSmallestPrivate(Ptr->left);
        }
        else
        {
            return Ptr->key;
        }
    }
}
void BiSearchTree::RemoveNode(int m_key)
{
    //starter ved root
    RemoveNodePrivate(m_key, root);
}
void BiSearchTree::RemoveNodePrivate(int m_key, node *parent)
{
    if(root != nullptr)
    {
        if(root->key == m_key)
        {
            RemoveRootMatch();
        }
        else
        {
            if(m_key < parent->key && parent->left != nullptr)
            {
                parent->left->key == m_key ? //boolean check - turnery conditional
                                             RemoveMatch(parent, parent->left, true):
                                             RemoveNodePrivate(m_key, parent->left);
            }
            else if(m_key > parent->key && parent->right != nullptr)
            {
                parent->right->key == m_key ? //boolean check - turnery conditional
                                              RemoveMatch(parent, parent->right, false):
                                              RemoveNodePrivate(m_key, parent->right);
            }
            else
            {
                std::cout << "The key " << m_key << "was not found in the tree\n";
            }
        }
    }
    else
    {
        std::cout << "The tree i sempty\n";
    }
}

void BiSearchTree::RemoveRootMatch()
{
    //tree not empty
    if(root != nullptr)
    {
        node* delPtr = root;
        int rootKey = root->key;
        int smallestInRightSubtree;

        //case 0 - 0 children
        if( root->left == nullptr && root->right == nullptr)
        {
            root = nullptr;
            delete delPtr;
        }
        //case 1 - 1 child
        // one right child
        else if(root->left == nullptr && root->right != nullptr)
        {
            root = root->right;
            //disconecting the old root from the tree, the child becomes the root
            delPtr->right = nullptr;
            delete delPtr;
            std:: cout << "The root node with key " << rootKey << " was deleted. " <<
                          "The new root contains key " << root->key << std::endl;
        }
        // one left child
        else if(root->left != nullptr && root->right == nullptr)
        {
            root = root->left;
            //disconecting the old root from the tree, the child becomes the root
            delPtr->left = nullptr;
            delete delPtr;
            std:: cout << "The root node with key " << rootKey << " was deleted. " <<
                          "The new root contains key " << root->key << std::endl;
        }

        //case 2 - 2 children
        else
        {
            smallestInRightSubtree = FindSmallestPrivate(root->right);
            //fjernet den minste,
            RemoveNodePrivate(smallestInRightSubtree, root);
            //puttet den minste inn i root
            root->key = smallestInRightSubtree;
            std::cout << "The root key containing key " << rootKey <<
                         " was overwritten with key " << root->key << std::endl;
        }
    }
    //tree empty
    else
    {
        std::cout << "Can not remove root, tree empty\n";
    }
}
//remove not root node
void BiSearchTree::RemoveMatch(BiSearchTree::node *parent, BiSearchTree::node *match, bool left)
{
    if(root != nullptr)
    {
        node* delPtr;
        int matchKey = match->key;
        int smallestInRightSubtree;

        //case 0 - 0 children
        if(match->left == nullptr && match->right == nullptr)
        {
            delPtr = match;
            left == true ?
                        parent->left = nullptr: //true
                        parent->right = nullptr; //false
            delete delPtr;
            std::cout << "The node containing key " << matchKey << " was removed\n";

        }
        //case 1- 1 child
        else if (match->left == nullptr && match->right != nullptr)
        {
            left == true ?
                        parent->left = match->right:
                        parent->right = match->right;

            match->right = nullptr;
            delPtr = match;
            delete delPtr;
            std::cout << "The node containing key " << matchKey << " was removed\n";
        }
        else if (match->left != nullptr && match->right == nullptr)
        {
            left == true ?
                        parent->left = match->left:
                        parent->right= match->left;

            match->left = nullptr;
            delPtr = match;
            delete delPtr;
            std::cout << "The node containing key " << matchKey << " was removed\n";
        }

        // Case 2 - 2 children
        else
        {
            smallestInRightSubtree = FindSmallestPrivate(match->right);
            RemoveNodePrivate(smallestInRightSubtree, match);
            match->key = smallestInRightSubtree;
        }
    }
    else
    {
        std::cout << "Can not remove match. The tree is empty.\n";
    }
}
