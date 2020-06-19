#ifndef WET1__AVLTREE_H_
#define WET1__AVLTREE_H_

#include <iostream>

#define BALANCED_R 1
#define NOT_BALANCED_R -2
#define BALANCED_L -1
#define NOT_BALANCED_L 2
#define EMPTY_HEIGHT -1 //if one of the sons is nullptr

/*
 *  TreeNode
 */


template<class Key, class Data>
class TreeNode {
  Key key;
  Data data;
  int height;
  TreeNode<Key, Data> *parent;
  TreeNode<Key, Data> *rightSon; //  greater values
  TreeNode<Key, Data> *leftSon;  //   smaller values

  template<class otherKey, class otherData>// so we won't shadow TreeNode's parameters
  friend
  class AVLTree;

  void setParent(TreeNode<Key, Data> *new_parent);

  void setRightSon(TreeNode<Key, Data> *son);

  void setLeftSon(TreeNode<Key, Data> *son);

  void updateData(Data new_data); // maybe we'll need it
  void setHeight(int new_height);

  const int getHeight() const; // may change only by setHeight

 public:
  TreeNode()
      : key(), data(), height(0), rightSon(nullptr), leftSon(nullptr) {}

  TreeNode(Key key, Data data)
      : key(key),
        data(data),
        height(0),
        rightSon(nullptr),
        leftSon(nullptr) {}

  TreeNode(const TreeNode &old_tree_node)
      : key(old_tree_node.key),
        data(old_tree_node.data),
        height(old_tree_node.height),
        parent(old_tree_node.parent),
        rightSon(old_tree_node.rightSon),
        leftSon(old_tree_node.leftSon) {}

  ~TreeNode() = default;

  TreeNode<Key, Data> *getParent();

  TreeNode<Key, Data> *getRightSon() const;

  TreeNode<Key, Data> *getLeftSon() const;

  Data &getData();

  const Key &getKey() const; // once created, the key is unchangeable

  void printData() const;

  void printKey() const;
};

/*        IMPLEMENTATION        */

/*
 *      PRIVATE FUNCTIONS
 */

template<class Key, class Data>
void TreeNode<Key, Data>::setParent(TreeNode<Key, Data> *new_parent) {
  if (this == nullptr) return;
  this->parent = new_parent;
}

template<class Key, class Data>
void TreeNode<Key, Data>::setRightSon(TreeNode<Key, Data> *son) {
  if (this == nullptr) return;
  this->rightSon = son;
}

template<class Key, class Data>
void TreeNode<Key, Data>::setLeftSon(TreeNode<Key, Data> *son) {
  if (this == nullptr) return;
  this->leftSon = son;
}

template<class Key, class Data>
void TreeNode<Key, Data>::updateData(Data new_data) {
  this->data = new_data;
}

template<class Key, class Data>
void TreeNode<Key, Data>::setHeight(int new_height) {
  this->height = new_height;
}

template<class Key, class Data>
Data &TreeNode<Key, Data>::getData() {
  return this->data;
}

template<class Key, class Data>
TreeNode<Key, Data> *TreeNode<Key, Data>::getParent() {
  return (this->parent);
}

template<class Key, class Data>
TreeNode<Key, Data> *TreeNode<Key, Data>::getRightSon() const {
  return (this->rightSon);
}

template<class Key, class Data>
TreeNode<Key, Data> *TreeNode<Key, Data>::getLeftSon() const {
  return (this->leftSon);
}

template<class Key, class Data>
const int TreeNode<Key, Data>::getHeight() const {
  return this->height;
}

/*
 *      PUBLIC FUNCTIONS
 */

template<class Key, class Data>
const Key &TreeNode<Key, Data>::getKey() const {
  return this->key;
}

template<class Key, class Data>
void TreeNode<Key, Data>::printData() const {
  std::cout << this->data << " ";
}

template<class Key, class Data>
void TreeNode<Key, Data>::printKey() const {
  std::cout << this->key << " ";
}

/*
 * AVLTree
 */

typedef enum AVLTreeResult {
  AVL_SUCCESS,
  AVL_KeyAlreadyExists,
  AVL_KeyNotFound
} AVLTreeResult;
typedef enum AVLTreeOrderKind {
  Pre, In, Post, Rev
} AVLTreeOrderKind;

template<class Key, class Data>
class AVLTree {
  TreeNode<Key, Data> *root;

  int size;

  void setRoot(TreeNode<Key, Data> *tree_node);

  void printPreOrder(TreeNode<Key, Data> *tree_node) const;

  void printInOrder(TreeNode<Key, Data> *tree_node) const;

  void printPostOrder(TreeNode<Key, Data> *tree_node) const;

  AVLTreeResult updateData(const Key &key, Data &data);

  TreeNode<Key, Data> *findNodeInTree(const Key &key,
                                      TreeNode<Key, Data> *tree_node);

  int heightDifference(TreeNode<Key, Data> *tree_node);

  void swapBetweenNodes(TreeNode<Key, Data> *first_node,
                        TreeNode<Key, Data> *second_node);

  void updateTreeNodeHeight(TreeNode<Key, Data> *tree_node);

  TreeNode<Key, Data> *AVLTreeBalance(TreeNode<Key, Data> *tree_node);

  TreeNode<Key, Data> *LLrotation(TreeNode<Key, Data> *parent,
                                  TreeNode<Key, Data> *son);

  TreeNode<Key, Data> *LRrotation(TreeNode<Key, Data> *parent,
                                  TreeNode<Key, Data> *son);

  TreeNode<Key, Data> *RLrotation(TreeNode<Key, Data> *parent,
                                  TreeNode<Key, Data> *son);

  TreeNode<Key, Data> *RRrotation(TreeNode<Key, Data> *parent,
                                  TreeNode<Key, Data> *son);

  AVLTreeResult internalAdd(TreeNode<Key, Data> **root,
                            TreeNode<Key, Data> *new_node);

  AVLTreeResult internalRemove(TreeNode<Key, Data> **tree_node, Key &key);

  AVLTreeResult deleteTreeNode(TreeNode<Key, Data> **tree_node_ptr, TreeNode<Key, Data> *tree_node);

  void deleteNodesWithTwoSons(TreeNode<Key, Data> **tree_node);

 public:
  AVLTree();

  ~AVLTree();

  AVLTreeResult searchData(const Key &key, Data **data);

  AVLTreeResult searchNode(const Key &key, TreeNode<Key, Data> **node);

  AVLTreeResult add(Key key, Data data);

  AVLTreeResult remove(Key &key);

  void cleanTree(TreeNode<Key, Data> *tree_node);

  void print(AVLTreeOrderKind print_order) const;

  TreeNode<Key, Data> *getSmallest();

  TreeNode<Key, Data> *getRoot();

  bool isEmpty() const;

  int getSize();

};

/*        IMPLEMENTATION        */

/*
 *      PRIVATE FUNCTIONS
 */

template<class Key, class Data>
void AVLTree<Key, Data>::setRoot(TreeNode<Key, Data> *tree_node) {
  if (tree_node == nullptr) {
    return;
  }
  this->root = tree_node;
}

template<class Key, class Data>
void AVLTree<Key, Data>::cleanTree(TreeNode<Key, Data> *tree_node) {
  if (tree_node == nullptr) {
    return;
  }
  cleanTree(tree_node->rightSon);
  cleanTree(tree_node->leftSon);
  tree_node->setParent(nullptr);
  tree_node->setRightSon(nullptr);
  tree_node->setLeftSon(nullptr);
  if (this->root == tree_node) {
    delete tree_node;
    this->root = nullptr;
  } else {
    delete tree_node;
  }
}

template<class Key, class Data>
void AVLTree<Key, Data>::printPreOrder(TreeNode<Key, Data> *tree_node) const {
  if (tree_node == nullptr) return;
  tree_node->printKey();
  printPreOrder(tree_node->getLeftSon());
  printPreOrder(tree_node->getRightSon());
}

template<class Key, class Data>
void AVLTree<Key, Data>::printInOrder(TreeNode<Key, Data> *tree_node) const {
  if (tree_node == nullptr) return;
  printInOrder(tree_node->getLeftSon());
  tree_node->printKey();
  printInOrder(tree_node->getRightSon());
}

template<class Key, class Data>
void AVLTree<Key, Data>::printPostOrder(TreeNode<Key, Data> *tree_node) const {
  if (tree_node == nullptr) return;
  printPostOrder(tree_node->getLeftSon());
  printPostOrder(tree_node->getRightSon());
  tree_node->printKey();
}

template<class Key, class Data>
AVLTreeResult AVLTree<Key, Data>::updateData(const Key &key, Data &data) {
  TreeNode<Key, Data> *tree_node = findNodeInTree(key, this->root);
  if (tree_node == nullptr) {
    return AVL_KeyNotFound;
  }
  tree_node->updateData(data);
  return AVL_SUCCESS;
}

template<class Key, class Data>
TreeNode<Key, Data> *AVLTree<Key, Data>::findNodeInTree(const Key &key,
                                                        TreeNode<Key,
                                                                 Data> *tree_node) {
  if (tree_node == nullptr) {
    return nullptr; //subtree ended and key wasn't found
  }
  Key curr_key = tree_node->getKey();
  if (curr_key == key) {
    return tree_node; // we found it !
  }
  if (curr_key > key) {
    return findNodeInTree(key,
                          tree_node->leftSon); // it MAY BE in the left subtree
  } else {
    return findNodeInTree(key,
                          tree_node->rightSon); // it MAY BE in the right subtree
  }
  /* "it" refers to the Node we are searching */
}

template<class Key, class Data>
int AVLTree<Key, Data>::heightDifference(TreeNode<Key, Data> *tree_node) {
  int left_height = EMPTY_HEIGHT, right_height = EMPTY_HEIGHT;
  if (tree_node->getRightSon() != nullptr) {
    right_height = tree_node->getRightSon()->getHeight();
  }
  if (tree_node->getLeftSon() != nullptr) {
    left_height = tree_node->getLeftSon()->getHeight();
  }
  return (left_height - right_height);
}

template<class Key, class Data>
void AVLTree<Key, Data>::swapBetweenNodes(TreeNode<Key, Data> *first_node,
                                          TreeNode<Key, Data> *second_node) {
  if (first_node == nullptr || second_node == nullptr) {
    return;
  }
  TreeNode<Key, Data> *temp_node1;
  TreeNode<Key, Data> *temp_node2;

  // checking if the nodes are consecutive, and which one is first
  if ((second_node->rightSon != nullptr
      && second_node->rightSon->key == first_node->key)
      || (second_node->leftSon != nullptr
          && second_node->leftSon->key == first_node->key)) {
    temp_node1 = first_node;
    first_node = second_node;
    second_node = temp_node1;
  }
  if (first_node->rightSon != nullptr
      && first_node->rightSon->key == second_node->key) {
    temp_node1 = first_node->parent;
    first_node->parent = second_node;
    second_node->parent = temp_node1;
    temp_node1 = second_node->rightSon;
    temp_node2 = second_node->leftSon;
    second_node->rightSon = first_node;
    second_node->leftSon = first_node->leftSon;
    first_node->rightSon = temp_node1;
    first_node->leftSon = temp_node2;
  } else if (first_node->leftSon != nullptr
      && first_node->leftSon->key == second_node->key) {
    temp_node1 = first_node->parent;
    first_node->parent = second_node;
    second_node->parent = temp_node1;
    temp_node1 = second_node->rightSon;
    temp_node2 = second_node->leftSon;
    second_node->rightSon = first_node->rightSon;
    second_node->leftSon = first_node;
    first_node->rightSon = temp_node1;
    first_node->leftSon = temp_node2;
  } else {
    temp_node1 = first_node->parent;
    first_node->setParent(second_node->parent);
    second_node->setParent(temp_node1);
    temp_node1 = first_node->rightSon;
    temp_node2 = first_node->leftSon;
    first_node->setRightSon(second_node->rightSon);
    first_node->setLeftSon(second_node->leftSon);
    second_node->setRightSon(temp_node1);
    second_node->setLeftSon(temp_node2);
  }

  if (first_node->rightSon != nullptr) {
    first_node->rightSon->setParent(first_node);
  }
  if (first_node->leftSon != nullptr) {
    first_node->leftSon->setParent(first_node);
  }
  if (second_node->rightSon != nullptr) {
    second_node->rightSon->setParent(second_node);
  }
  if (second_node->leftSon != nullptr) {
    second_node->leftSon->setParent(second_node);
  }

  if (first_node->parent != nullptr) {
    if (first_node->parent->leftSon->key == second_node->key) {
      first_node->parent->setLeftSon(first_node);
    } else {
      first_node->parent->setRightSon(first_node);
    }
  }

  if (second_node->parent != nullptr) {
    if (second_node->parent->leftSon->key == first_node->key) {
      second_node->parent->setLeftSon(second_node);
    } else {
      second_node->parent->setRightSon(second_node);
    }
  }

  if (this->root->key == first_node->key) {
    this->setRoot(second_node);
  } else if (this->root->key == second_node->key) {
    this->setRoot(first_node);
  }

}

template<class Key, class Data>
void AVLTree<Key, Data>::updateTreeNodeHeight(TreeNode<Key, Data> *tree_node) {
  int left_height = EMPTY_HEIGHT, right_height = EMPTY_HEIGHT, new_height = 0;
  if (tree_node->leftSon != nullptr) {
    left_height = tree_node->leftSon->getHeight();
  }
  if (tree_node->rightSon != nullptr) {
    right_height = tree_node->rightSon->getHeight();
  }
  new_height = (left_height > right_height) ? left_height : right_height;
  tree_node->setHeight(new_height + 1);
}

template<class Key, class Data>
TreeNode<Key, Data> *AVLTree<Key, Data>::AVLTreeBalance(TreeNode<Key,
                                                                 Data> *tree_node) {
  // now we need to sort the kind of imbalance, if exists
  if (heightDifference(tree_node) == NOT_BALANCED_L) {
    if (heightDifference(tree_node->leftSon) == BALANCED_L) {
      tree_node = LRrotation(tree_node, tree_node->leftSon);
      return tree_node;
    }
    tree_node = LLrotation(tree_node, tree_node->leftSon);
    return tree_node;
  }
  if (heightDifference(tree_node) == NOT_BALANCED_R) {
    if (heightDifference(tree_node->rightSon) == BALANCED_R) {
      tree_node = RLrotation(tree_node, tree_node->rightSon);
      return tree_node;
    }
    tree_node = RRrotation(tree_node, tree_node->rightSon);
    return tree_node;
  }
  //the tree is balanced
  return tree_node;
}

template<class Key, class Data>
TreeNode<Key, Data> *AVLTree<Key, Data>::LLrotation(TreeNode<Key, Data> *parent,
                                                    TreeNode<Key, Data> *son) {
  parent->setLeftSon(son->rightSon);
  if (son->rightSon != nullptr) {
    son->rightSon->setParent(parent);
  }
  son->setRightSon(parent);
  son->setParent(parent->parent);
  parent->setParent(son);
  updateTreeNodeHeight(parent);
  updateTreeNodeHeight(son);
  return son;
}

template<class Key, class Data>
TreeNode<Key, Data> *AVLTree<Key, Data>::LRrotation(TreeNode<Key, Data> *parent,
                                                    TreeNode<Key, Data> *son) {
  parent->setLeftSon(RRrotation(son, son->rightSon));
  return LLrotation(parent, parent->leftSon);
}

template<class Key, class Data>
TreeNode<Key, Data> *AVLTree<Key, Data>::RLrotation(TreeNode<Key, Data> *parent,
                                                    TreeNode<Key, Data> *son) {
  parent->setRightSon(LLrotation(son, son->leftSon));
  return RRrotation(parent, parent->rightSon);
}

template<class Key, class Data>
TreeNode<Key, Data> *AVLTree<Key, Data>::RRrotation(TreeNode<Key, Data> *parent,
                                                    TreeNode<Key, Data> *son) {
  parent->setRightSon(son->leftSon);
  if (son->leftSon != nullptr) {
    son->leftSon->setParent(parent);
  }
  son->setLeftSon(parent);
  son->setParent(parent->parent);
  parent->setParent(son);
  updateTreeNodeHeight(parent);
  updateTreeNodeHeight(son);
  return son;
}

template<class Key, class Data>
AVLTreeResult AVLTree<Key, Data>::internalAdd(TreeNode<Key, Data> **root,
                                              TreeNode<Key, Data> *new_node) {
  Key root_key = (*root)->key, new_node_key = new_node->key;
  AVLTreeResult result = AVL_SUCCESS; //unless we'll find out otherwise...
  if (root_key == new_node_key) {
    return AVL_KeyAlreadyExists;
  }
  if (root_key > new_node_key) {
    if ((*root)->leftSon == nullptr) {
      (*root)->setLeftSon(new_node);
      new_node->setParent(*root);
      updateTreeNodeHeight(*root);
      return AVL_SUCCESS;
    }
    result = internalAdd(&((*root)->leftSon), new_node);
    updateTreeNodeHeight(*root);
    *root = AVLTreeBalance(*root);
    return result;
  }
  // if we got here, new_node_key must be greater than root_key
  if ((*root)->rightSon == nullptr) {
    (*root)->setRightSon(new_node);
    new_node->setParent(*root);
    updateTreeNodeHeight(*root);
    return AVL_SUCCESS;
  }
  result = internalAdd(&((*root)->rightSon), new_node);
  updateTreeNodeHeight(*root);
  *root = AVLTreeBalance(*root);
  return result;
}

template<class Key, class Data>
AVLTreeResult AVLTree<Key, Data>::internalRemove(TreeNode<Key,
                                                          Data> **tree_node,
                                                 Key &key) {
  if ((*tree_node) == nullptr) return AVL_KeyNotFound;
  Key curr_key = (*tree_node)->key;
  if (curr_key == key) {
    deleteTreeNode(tree_node, *tree_node);
  } else if (curr_key > key) {
    internalRemove(&((*tree_node)->leftSon), key);
    updateTreeNodeHeight((*tree_node));
    *tree_node = AVLTreeBalance((*tree_node));
  } else {
    internalRemove(&((*tree_node)->rightSon), key);
    updateTreeNodeHeight((*tree_node));
    *tree_node = AVLTreeBalance((*tree_node));
  }
  return AVL_SUCCESS;
}

template<class Key, class Data>
AVLTreeResult AVLTree<Key, Data>::deleteTreeNode(TreeNode<Key,
                                                          Data> **tree_node_ptr, TreeNode<Key,
                                                                                          Data> *tree_node) {
  TreeNode<Key, Data> *node_to_remove = tree_node;
  TreeNode<Key, Data> *parent_of_deleted_node = (tree_node->parent);
  Key curr_key = tree_node->getKey();
  if (tree_node->leftSon == nullptr && tree_node->rightSon == nullptr) {
    if (parent_of_deleted_node != nullptr && parent_of_deleted_node->getLeftSon() != nullptr
        && parent_of_deleted_node->getLeftSon()->key == curr_key) {
      parent_of_deleted_node->setLeftSon(nullptr);
    } else if (parent_of_deleted_node != nullptr) {
      parent_of_deleted_node->setRightSon(nullptr);
    }
    *tree_node_ptr = nullptr;
    delete node_to_remove;
  } else if (tree_node->getLeftSon() != nullptr
      && tree_node->getRightSon() == nullptr) {
    tree_node->getLeftSon()->setParent(parent_of_deleted_node);
    *tree_node_ptr = tree_node->leftSon;
    delete node_to_remove;
  } else if (tree_node->leftSon == nullptr
      && tree_node->rightSon != nullptr) {
    tree_node->rightSon->setParent(parent_of_deleted_node);
    *tree_node_ptr = tree_node->rightSon;
    delete node_to_remove;
  } else {
    deleteNodesWithTwoSons(tree_node_ptr);
  }
  return AVL_SUCCESS;
}

template<class Key, class Data>
void AVLTree<Key, Data>::deleteNodesWithTwoSons(TreeNode<Key,
                                                         Data> **tree_node) {
  TreeNode<Key, Data> *new_tree_node;
  Key key = (*tree_node)->key;
  new_tree_node = (*tree_node)->rightSon;
  while (new_tree_node->leftSon != nullptr) {
    new_tree_node = new_tree_node->leftSon;
  }
  swapBetweenNodes((*tree_node), new_tree_node);
  TreeNode<Key, Data> **subtree_root = &(new_tree_node->rightSon);
  internalRemove(subtree_root, key);
  updateTreeNodeHeight(new_tree_node);
  *tree_node = AVLTreeBalance(new_tree_node);
}

/*
 *      PRIVATE FUNCTIONS
 */

template<class Key, class Data>
AVLTree<Key, Data>::AVLTree():root(nullptr), size(0) {}

template<class Key, class Data>
AVLTree<Key, Data>::~AVLTree() {
  if (root != nullptr) {
    cleanTree(root);
  }
}

template<class Key, class Data>
AVLTreeResult AVLTree<Key, Data>::add(Key key, Data data) {
  TreeNode<Key, Data> *tree_node = new TreeNode<Key, Data>(key, data);
  if (this->root == nullptr) {
    this->root = tree_node;
    tree_node->parent = nullptr;
    this->size++;
    return AVL_SUCCESS;
  }
  if (internalAdd(&(this->root), tree_node) == AVL_KeyAlreadyExists) {
    delete tree_node;
    return AVL_KeyAlreadyExists;
  }
  this->size++;
  return AVL_SUCCESS;
}

template<class Key, class Data>
AVLTreeResult AVLTree<Key, Data>::remove(Key &key) {
  if (this->root == nullptr) {
    return AVL_KeyNotFound;
  }
  AVLTreeResult tmpResult;
  tmpResult = internalRemove(&(this->root), key);
  if (tmpResult == AVL_SUCCESS)
    this->size--;
  return tmpResult;
}

template<class Key, class Data>
AVLTreeResult AVLTree<Key, Data>::searchData(const Key &key, Data **data) {
  TreeNode<Key, Data> *tree_node = findNodeInTree(key, this->root);
  if (tree_node == nullptr) {
    *data = nullptr;
    return AVL_KeyNotFound;
  }
  Data *data_ptr = &(tree_node->data);
  *data = data_ptr;
  return AVL_SUCCESS;
}

template<class Key, class Data>
AVLTreeResult AVLTree<Key, Data>::searchNode(const Key &key,
                                             TreeNode<Key, Data> **node) {
  *node = findNodeInTree(key, this->root);
  if (*node == nullptr) {
    return AVL_KeyNotFound;
  }
  return AVL_SUCCESS;
}

template<class Key, class Data>
void AVLTree<Key, Data>::print(AVLTreeOrderKind print_order) const {
  if (print_order == Pre) {
    printPreOrder(this->root);
    return;
  }
  if (print_order == In) {
    printInOrder(this->root);
    return;
  }
  if (print_order == Post) {
    printPostOrder(this->root);
    return;
  }
}

template<class Key, class Data>
TreeNode<Key, Data> *AVLTree<Key, Data>::getSmallest() {
  if (this->root == nullptr) {
    return nullptr;
  }
  TreeNode<Key, Data> *tree_node = this->root;
  while (tree_node->leftSon != nullptr) {
    tree_node = tree_node->leftSon;
  }
  return tree_node;
}

template<class Key, class Data>
TreeNode<Key, Data> *AVLTree<Key, Data>::getRoot() {
  return this->root;
}

template<class Key, class Data>
bool AVLTree<Key, Data>::isEmpty() const {
  if (this->root == nullptr) {
    return true;
  }
  return false;
}

template<class Key, class Data>
int AVLTree<Key, Data>::getSize() {
  return this->size;
}

#endif //WET1__AVLTREE_H_
