//
// Created by kenneth on 11/18/2019.
//

#ifndef BST312_BST312_H
#define BST312_BST312_H
#include <cstdlib>  // Provides size_t
#include <iostream>
#include <vector>

using namespace std;

template<class ItemType>
class BST_312 {
public:

    BST_312();

    //Copy constructor
    BST_312(const BST_312 & src);

    ~BST_312();

/****************************
makeEmpty

Function: Removes all the items from the BST.
Preconditions: BST has been initialized
Postconditions: All the items have been removed
*****************************/
    void makeEmpty();

/****************************
isEmpty

Function: Checks to see if there are any items in the BST.
Preconditions: BST has been initialized
Postconditions: Returns true if there are no items in the BST, else false.
*****************************/
    bool isEmpty() const;

/****************************
isFull

Function: Determines if you have any more room to add items to the BST
Preconditions: BST has been initialized
Postconditions: Returns true if there is no more room to add items, else false
*****************************/
    bool isFull() const;

/****************************
insertItem

Function: Adds newItem to the BST.
Preconditions: BST has been initialized and is not full.
Postconditions: newItem is in the proper position for a BST.
*****************************/
    void insertItem(const ItemType &);

/****************************
deleteItem

Function: Removes target from BST.
Preconditions: BST has been initialized.
Postconditions: If found, element has been removed from BST.
*****************************/
    void deleteItem(const ItemType& newItem);

/****************************
countNodes

Function: Counts the number of nodes in the BST
Preconditions: BST has been initialized.
Postconditions: returns the number of nodes in the BST
*****************************/
    int countNodes();

/****************************
preOrderTraversal

Function: Returns the preOder (Node, Left, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> preOrderTraversal();

/****************************
inOrderTraversal

Function: Returns the inOder (Left, Node, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> inOrderTraversal();

/****************************
postOrderTraversal

Function: returns the postOder (Left, Right, Node) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> postOrderTraversal();

/********************
 isItemInTree

Function: Determines if a given Item is in tree.
Preconditions: BST has been initialized.
Postconditions: none
*****************************/

    bool isItemInTree(const ItemType& item);


private:
    struct TreeNode {
        ItemType data;
        TreeNode *left;
        TreeNode *right;
    };

    TreeNode * root;


    void insertItem(TreeNode*& t, const ItemType& newItem);
    void inOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    int countNodes(TreeNode* t) const;
    void deleteNode(TreeNode*& node);
    void makeEmpty(TreeNode*& t);
    void deleteItem(TreeNode*& t, const ItemType& newItem);
    void getPredecessor(TreeNode* t, ItemType& data);
    void preOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void postOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void copyTree(TreeNode*& copy, const TreeNode *originalTree);

    //template<class ItemType, class ItemType>
    bool inTree(TreeNode *node, const ItemType &item);
};

/*******************************
//Function implementations
********************************/

template<class ItemType>
BST_312<ItemType>::BST_312 ()
{
    root = NULL;
}

template<class ItemType>
BST_312<ItemType>::BST_312(const BST_312 & src)
{
    copyTree(root, src.root);
}

template<class ItemType>
BST_312<ItemType>::~BST_312()
{
    makeEmpty();

}


template<class ItemType>
void BST_312<ItemType>::copyTree(TreeNode*& copy, const TreeNode* originalTree)
{
    if (originalTree == NULL)
        copy = NULL;
    else
    {
        copy = new TreeNode;
        copy->data = originalTree->data;

        copyTree(copy->left, originalTree->left);
        copyTree(copy->right, originalTree->right);
    }
}


template<class ItemType>
void BST_312 <ItemType>::deleteNode(TreeNode*& node)
{
    ItemType info;
    TreeNode *tempPtr;

    tempPtr = node;

    if (node->left == NULL)
    {
        node = node->right;
        delete tempPtr;
    }
    else if (node->right == NULL)
    {
        node = node->left;
        delete tempPtr;
    }
    else
    {
        getPredecessor(node->left, info);
        node->data = info;
        deleteItem(node->left, info);
    }
}



//find largest in left subtree
template<class ItemType>
void BST_312 <ItemType>::getPredecessor(TreeNode* t, ItemType& data)
{
    while (t->right != NULL)
        t = t->right;

    data = t->data;

}


template<class ItemType>
void BST_312 <ItemType>::deleteItem(TreeNode*& t, const ItemType& newItem)
{
    if (t == NULL)
        return;
    else if (newItem < t->data)
        deleteItem(t->left, newItem);
    else if (newItem > t->data)
        deleteItem(t->right, newItem);
    else
        deleteNode(t);
}


template<class ItemType>
void BST_312 <ItemType>::deleteItem(const ItemType& newItem)
{
    deleteItem(root, newItem);

}

template<class ItemType>
void BST_312 <ItemType>::makeEmpty(TreeNode*& t)
{
  if (t == NULL)   //exit condition
      return;

 makeEmpty(t -> left);
 makeEmpty(t -> right);

 delete t;  //free the space
 t = NULL;  //change the node
}

template<class ItemType>
void BST_312 <ItemType>::makeEmpty()
{
    makeEmpty(root);
    root = NULL;
}

template<class ItemType>
bool BST_312 <ItemType>::isEmpty() const
{
    return root == NULL;
}



template<class ItemType>
bool BST_312 <ItemType>::isFull() const
{
    try
    {
        TreeNode *temp = new TreeNode;
        delete temp;
        return false;
    }
    catch (std::bad_alloc)
    {
        return true;
    }

}


template<class ItemType>
void BST_312 <ItemType>::insertItem(TreeNode*& t, const ItemType& newItem)
{
    if (t == NULL)
    {
        t = new TreeNode;
        t -> data = newItem;
        t -> right = NULL;
        t -> left = NULL;

    }

    else if (newItem > t -> data)
        insertItem(t -> right, newItem);

    else   //if they are equal (Duplicate)
        insertItem(t -> right, newItem);
}

template<class ItemType>
void BST_312 <ItemType>::insertItem(const ItemType& newItem)
{
    insertItem(root, newItem);
}



template<class ItemType>
int BST_312 <ItemType>::countNodes(TreeNode* t) const
{
    if (t == NULL)   //exit condition
        return 0;
    else
        return 1+countNodes(t -> left) + countNodes(t -> right);

}


template<class ItemType>
int BST_312 <ItemType>::countNodes()   //default to the root
{
    int count = countNodes(root);
    return count;
}

template<class ItemType>
void BST_312 <ItemType>::preOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    if (t == NULL)
        return;

    //order: (node, left, right)
    result.push_back(t -> data);
    preOrderTraversal(t -> left, result);
    preOrderTraversal(t -> right, result);

}

template<class ItemType>
void BST_312 <ItemType>::inOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    if (t == NULL)
        return;

    //order: (left, node, right)
    inOrderTraversal(t -> left, result);
    result.push_back(t -> data);
    inOrderTraversal(t -> right, result);


}

template<class ItemType>
vector<ItemType> BST_312 <ItemType>::preOrderTraversal()
{
    vector<ItemType> v;
    preOrderTraversal(root, v);
    // order: (node, left, right)
    return v;

}


template<class ItemType>
vector<ItemType> BST_312 <ItemType>::inOrderTraversal()
{
    //default to root
    vector<ItemType> v;
    inOrderTraversal(root, v);
    return v;
}

template<class ItemType>
void BST_312 <ItemType>::postOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    if (t == NULL)
        return;   //return nothing, exit
    postOrderTraversal(t -> left, result);
    postOrderTraversal(t -> right, result);
    result.push_back(t -> data);

}

template<class ItemType>
vector<ItemType> BST_312 <ItemType>::postOrderTraversal()
{
    vector<ItemType> v;
    postOrderTraversal(root, v);
    return v;
}

template<class ItemType>
bool BST_312 <ItemType>::inTree(TreeNode* node, const ItemType& item)
{
    if (node == NULL)
        return false;  //exit condition
    if (node -> data == item)
        return true;
    return inTree(node -> left, item)||inTree(node -> right, item);

}


template<class ItemType>
bool BST_312 <ItemType>::isItemInTree(const ItemType& item)
{
    return inTree(root, item);  //default to root

}
#endif