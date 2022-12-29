#include <iostream>
#include <cmath>

using namespace std;

struct node {
    int data;
    node* left;
    node* right;
    node* up;
};

void print_ttree(node* tree)
{
    if(tree == NULL)
        return;

    print_ttree(tree->left);
    cout << tree->data << endl;
    print_ttree(tree->right);
}

// Ex. 1
node* findMinNode(node* tree)
{
    if(tree->left == NULL)
        return tree;

    return findMinNode(tree->left);
}

void delete_node(node* root, int s)
{
    if(root == NULL)
        return;

    if(root->data == s)
    {
        // P1
        if(root->left == NULL && root->right == NULL)
        {
            if((root->up)->left == root)
                (root->up)->left = NULL;
            else
                (root->up)->right = NULL;

            delete root;
            root = NULL;
            return;
        }

        // P2
        if(root->left != NULL && root->right == NULL)
        {
            node* tmpNode = root->left;

            root->data = tmpNode->data;
            root->left = tmpNode->left;
            root->right = tmpNode->right;

            delete tmpNode;
            tmpNode = NULL;

            return;
        } else if(root->left == NULL && root->right != NULL)
        {
            node* tmpNode = root->right;

            root->data = tmpNode->data;
            root->left = tmpNode->left;
            root->right = tmpNode->right;

            delete tmpNode;
            tmpNode = NULL;

            return;
        }

        // P3
        node* minNode = findMinNode(root->right);

        root->data = minNode->data;

        if(minNode->right != NULL)
        {
            node* tmpNode = minNode->right;

            minNode->data = tmpNode->data;
            minNode->left = tmpNode->left;
            minNode->right = tmpNode->right;

            delete tmpNode;
            tmpNode = NULL;

            return;
        } else
        {
            delete minNode;
            minNode = NULL;
        }

        return;
    }

    delete_node(root->left, s);
    delete_node(root->right, s);
}

// Ex. 2
int tree_size(node* tree)
{
    if(tree == NULL)
        return 0;

    return 1 + tree_size(tree->left) + tree_size(tree->right);
}

int walk_tree_in_order(node* tree, int* data)
{
    if(tree == NULL)
        return 0;

    int i = walk_tree_in_order(tree->left, data);
    data[i++] = tree->data;
    i += walk_tree_in_order(tree->right, &data[i]);
    return i;
}

node* create_perfect_tree(int* a, const int n)
{
    if(n == 0)
        return NULL;

    int i = (n - 1) / 2;
    node* root = new node{ a[i] };

    root->left = create_perfect_tree(a, i);
    root->right = create_perfect_tree(&a[i + 1], (n - 1) - i);

    return root;
}

// Ex. 3
bool search(node* tree, int s)
{
    if(tree == NULL)
        return false;

    if(tree->data == s)
        return true;
    else if(tree->data > s)
        return search(tree->left, s);
    else
        return search(tree->right, s);
}

// Ex. 7 | floor( log2 n )

int main()
{
    /*node* root = new node {5};

    root->left = new node {3};
    root->left->left = new node {2};
    root->left->right = new node {4};

    root->right = new node {7};
    root->right->left = new node {6};
    root->right->right = new node {8};

    cout << search(root, 4) << endl;*/

    node* root = new node{5};

    root->left = new node{3};
    root->left->up = root;

    root->left->left = new node{2};
    root->left->left->up = root->left;

    root->left->left->left = new node{1};
    root->left->left->left->up = root->left->left;

    root->right = new node{6};
    root->right->up = root;

    root->right->right = new node{7};
    root->right->right->up = root->right;

    int n = tree_size(root);
    int data[n];

    walk_tree_in_order(root, data);

    node* root2 = create_perfect_tree(data, n);

    print_ttree(root);

    cout << "===" << endl;
    delete_node(root, 7);
    print_ttree(root);

    return 0;
}
