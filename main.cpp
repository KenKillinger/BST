#include <iostream>
#include "BST312.h"

using namespace std;

int main(int argc, const char * argv[]) {

    BST_312<int> tree;

    tree.insertItem(3);
    tree.insertItem(-3);
    tree.insertItem(9);
    tree.insertItem(5);
    tree.insertItem(100);
    tree.insertItem(0);
    tree.insertItem(-1);



    vector<int> vec = tree.postOrderTraversal();

    if (tree.isItemInTree(100))
        cout<<"oh god yeah!"<<endl;
    cout<<tree.countNodes()<<endl;

    for(auto it = vec.begin(); it!=vec.end(); it++){
        cout << *it << endl;
    }
    //cout<<tree.isItemInTree(9)<<endl;


    tree.makeEmpty();
    return 0;
}