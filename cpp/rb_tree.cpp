#include <iostream>
#include <queue>

enum Color { RED, BLACK };

template <typename T> struct Node {
    T data;
    bool color;
    Node *left, *right, *parent;

    Node(T data) {
        this->data = data;
        left = right = parent = nullptr;
        this->color = RED;
    }
};

template <typename T> class RBTree {
  private:
    Node<T> *root;

  protected:
    void rotateLeft(Node<T> *&, Node<T> *&);
    void rotateRight(Node<T> *&, Node<T> *&);
    void fixInsertRBTree(Node<T> *&, Node<T> *&);
    void fixDeleteRBTree(Node<T> *&, Node<T> *&);
    void inorderHelper(Node<T> *node);
    void levelOrderHelper(Node<T> *node);
    Node<T> *minValueNode(Node<T> *);
    Node<T> *maxValueNode(Node<T> *);
    Node<T> *insertBST(Node<T> *&, Node<T> *&);
    Node<T> *deleteBST(Node<T> *&, T);
    void transplant(Node<T> *&root, Node<T> *u, Node<T> *v);
    int getColor(Node<T> *&);
    void setColor(Node<T> *&, int);

  public:
    RBTree() { root = nullptr; }
    void insertValue(T);
    void deleteValue(T);
    void inorder();
    void levelOrder();
};

template <typename T> void RBTree<T>::rotateLeft(Node<T> *&root, Node<T> *&pt) {
    Node<T> *pt_right = pt->right;

    pt->right = pt_right->left;

    if (pt->right != nullptr)
        pt->right->parent = pt;

    pt_right->parent = pt->parent;

    if (pt->parent == nullptr)
        root = pt_right;
    else if (pt == pt->parent->left)
        pt->parent->left = pt_right;
    else
        pt->parent->right = pt_right;

    pt_right->left = pt;
    pt->parent = pt_right;
}

template <typename T>
void RBTree<T>::rotateRight(Node<T> *&root, Node<T> *&pt) {
    Node<T> *pt_left = pt->left;

    pt->left = pt_left->right;

    if (pt->left != nullptr)
        pt->left->parent = pt;

    pt_left->parent = pt->parent;

    if (pt->parent == nullptr)
        root = pt_left;
    else if (pt == pt->parent->left)
        pt->parent->left = pt_left;
    else
        pt->parent->right = pt_left;

    pt_left->right = pt;
    pt->parent = pt_left;
}

template <typename T>
void RBTree<T>::fixInsertRBTree(Node<T> *&root, Node<T> *&pt) {
    Node<T> *parent_pt = nullptr;
    Node<T> *grand_parent_pt = nullptr;

    while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {
        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;

        if (parent_pt == grand_parent_pt->left) {
            Node<T> *uncle_pt = grand_parent_pt->right;

            if (uncle_pt != nullptr && uncle_pt->color == RED) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            } else {
                if (pt == parent_pt->right) {
                    rotateLeft(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                rotateRight(root, grand_parent_pt);
                std::swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        } else {
            Node<T> *uncle_pt = grand_parent_pt->left;

            if (uncle_pt != nullptr && uncle_pt->color == RED) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            } else {
                if (pt == parent_pt->left) {
                    rotateRight(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                rotateLeft(root, grand_parent_pt);
                std::swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }
    }

    root->color = BLACK;
}

template <typename T>
void RBTree<T>::fixDeleteRBTree(Node<T> *&root, Node<T> *&pt) {
    if (pt == nullptr)
        return;

    if (pt == root) {
        root = nullptr;
        return;
    }

    if (getColor(pt) == RED || getColor(pt->left) == RED ||
        getColor(pt->right) == RED) {
        Node<T> *child = pt->left != nullptr ? pt->left : pt->right;

        if (pt == pt->parent->left) {
            pt->parent->left = child;
            if (child != nullptr)
                child->parent = pt->parent;
            setColor(child, BLACK);
            delete (pt);
        } else {
            pt->parent->right = child;
            if (child != nullptr)
                child->parent = pt->parent;
            setColor(child, BLACK);
            delete (pt);
        }
    } else {
        Node<T> *sibling = nullptr;
        Node<T> *parent = nullptr;
        Node<T> *ptr = pt;
        while (ptr != root && getColor(ptr) == BLACK) {
            parent = ptr->parent;
            if (ptr == parent->left) {
                sibling = parent->right;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateLeft(root, parent);
                    sibling = parent->right;
                }
                if (getColor(sibling->left) == BLACK &&
                    getColor(sibling->right) == BLACK) {
                    setColor(sibling, RED);
                    ptr = parent;
                } else {
                    if (getColor(sibling->right) == BLACK) {
                        setColor(sibling->left, BLACK);
                        setColor(sibling, RED);
                        rotateRight(root, sibling);
                        sibling = parent->right;
                    }
                    setColor(sibling, parent->color);
                    setColor(parent, BLACK);
                    setColor(sibling->right, BLACK);
                    rotateLeft(root, parent);
                    ptr = root;
                }
            } else {
                sibling = parent->left;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateRight(root, parent);
                    sibling = parent->left;
                }
                if (getColor(sibling->left) == BLACK &&
                    getColor(sibling->right) == BLACK) {
                    setColor(sibling, RED);
                    ptr = parent;
                } else {
                    if (getColor(sibling->left) == BLACK) {
                        setColor(sibling->right, BLACK);
                        setColor(sibling, RED);
                        rotateLeft(root, sibling);
                        sibling = parent->left;
                    }
                    setColor(sibling, parent->color);
                    setColor(parent, BLACK);
                    setColor(sibling->left, BLACK);
                    rotateRight(root, parent);
                    ptr = root;
                }
            }
        }
        setColor(ptr, BLACK);
    }
}

template <typename T> void RBTree<T>::insertValue(T data) {
    Node<T> *pt = new Node<T>(data);
    root = insertBST(root, pt);
    fixInsertRBTree(root, pt);
}

template <typename T> void RBTree<T>::deleteValue(T data) {
    Node<T> *pt = deleteBST(root, data);
    fixDeleteRBTree(root, pt);
}

template <typename T> void RBTree<T>::inorder() { inorderHelper(root); }

template <typename T> void RBTree<T>::levelOrder() { levelOrderHelper(root); }

template <typename T> void RBTree<T>::inorderHelper(Node<T> *root) {
    if (root == nullptr)
        return;

    inorderHelper(root->left);
    std::cout << root->data << " ";
    inorderHelper(root->right);
}

template <typename T> void RBTree<T>::levelOrderHelper(Node<T> *root) {
    if (root == nullptr)
        return;

    std::queue<Node<T> *> q;
    q.push(root);

    while (!q.empty()) {
        Node<T> *temp = q.front();
        std::cout << temp->data << " ";
        q.pop();

        if (temp->left != nullptr)
            q.push(temp->left);

        if (temp->right != nullptr)
            q.push(temp->right);
    }
}

template <typename T> Node<T> *RBTree<T>::minValueNode(Node<T> *node) {
    Node<T> *ptr = node;

    while (ptr->left != nullptr)
        ptr = ptr->left;

    return ptr;
}

template <typename T> Node<T> *RBTree<T>::maxValueNode(Node<T> *node) {
    Node<T> *ptr = node;

    while (ptr->right != nullptr)
        ptr = ptr->right;

    return ptr;
}

template <typename T>
Node<T> *RBTree<T>::insertBST(Node<T> *&root, Node<T> *&pt) {
    if (root == nullptr)
        return pt;

    if (pt->data < root->data) {
        root->left = insertBST(root->left, pt);
        root->left->parent = root;
    } else if (pt->data > root->data) {
        root->right = insertBST(root->right, pt);
        root->right->parent = root;
    }

    return root;
}

template <typename T>
void RBTree<T>::transplant(Node<T> *&root, Node<T> *u, Node<T> *v) {
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != nullptr)
        v->parent = u->parent;
}

template <typename T> Node<T> *RBTree<T>::deleteBST(Node<T> *&root, T data) {
    Node<T> *z = root;
    Node<T> *x, *y;

    while (z != nullptr) {
        if (z->data == data)
            break;
        else if (z->data < data)
            z = z->right;
        else
            z = z->left;
    }

    if (z == nullptr)
        return nullptr;

    y = z;
    int yOriginalColor = y->color;
    if (z->left == nullptr) {
        x = z->right;
        transplant(root, z, z->right);
    } else if (z->right == nullptr) {
        x = z->left;
        transplant(root, z, z->left);
    } else {
        y = minValueNode(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x != nullptr)
                x->parent = y;
        } else {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (yOriginalColor == BLACK)
        fixDeleteRBTree(root, x);
    return root;
}

template <typename T> int RBTree<T>::getColor(Node<T> *&node) {
    if (node == nullptr)
        return BLACK;

    return node->color;
}

template <typename T> void RBTree<T>::setColor(Node<T> *&node, int color) {
    if (node == nullptr)
        return;

    node->color = color;
}

int main() {
    RBTree<int> tree;

    tree.insertValue(10);
    tree.insertValue(20);
    tree.insertValue(30);
    tree.insertValue(15);

    std::cout << "Inorder Traversal of Created Tree\n";
    tree.inorder();

    std::cout << "\n\nLevel Order Traversal of Created Tree\n";
    tree.levelOrder();

    tree.deleteValue(20);
    std::cout << "\n\nInorder Traversal after Deletion of 20\n";
    tree.inorder();

    return 0;
}