#include <iostream>
#include <cmath>

using namespace std;

struct node {
    int data;
    node* left;
    node* right;
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
bool search(node* tree, int x)
{
    if(tree == NULL)
        return false;

    if(
       tree->data == x ||
       search(tree->left, x) ||
       search(tree->right, x)
       )
        return true;

    return false;
}

// Ex. 2
int node_count(node* tree)
{
    if(tree == NULL)
        return 0;

    return 1 + node_count(tree->left) + node_count(tree->right);
}

int leaves_count(node* tree)
{
    if(tree == NULL)
        return 0;

    if(tree->left == NULL && tree->right == NULL)
        return 1;

    return leaves_count(tree->left) + leaves_count(tree->right);
}

int right_children_count(node* tree)
{
    if(tree == NULL)
        return 0;

    if(tree->right != NULL)
        return 1 + right_children_count(tree->left) + right_children_count(tree->right);

    return 0 + right_children_count(tree->left) + right_children_count(tree->right);
}

int tree_height(node* tree)
{
    if(tree == NULL)
        return 0;

    int l = tree_height(tree->left) + 1;
    int r = tree_height(tree->right) + 1;

    if(l >= r)
        return l;
    else
        return r;
}

// Ex. 3
bool is_balanced(node* tree)
{
    return (abs(tree_height(tree->left) - tree_height(tree->right)) <= 1);
}

// Ex. 4
int max_value(node* tree)
{
    if(tree == NULL)
        return INT_MIN;

    int value_l = max_value(tree->left);
    int value_r = max_value(tree->right);

    if(tree->data >= value_l && tree->data >= value_r)
        return tree->data;
    else if(value_l >= tree->data && value_l >= value_r)
        return value_l;
    else
        return value_r;
}

int min_value(node* tree)
{
    if(tree == NULL)
        return INT_MAX;

    int value_l = min_value(tree->left);
    int value_r = min_value(tree->right);

    if(tree->data <= value_l && tree->data <= value_r)
        return tree->data;
    else if(value_l <= tree->data && value_l <= value_r)
        return value_l;
    else
        return value_r;
}

bool is_BST(node* tree)
{
    if(tree == NULL)
        return true;

    return (
            tree->data >= max_value(tree->left) &&
            tree->data < min_value(tree->right) &&
            is_BST(tree->left) &&
            is_BST(tree->right)
            );
}

// Ex. 5
void delete_leaves(node* &tree)
{
    if(tree == NULL)
        return;

    if(
       tree->left != NULL &&
       tree->left->left == NULL &&
       tree->left->right == NULL
       )
    {
        delete tree->left;
        tree->left = NULL;
    }

    if(
       tree->right != NULL &&
       tree->right->left == NULL &&
       tree->right->right == NULL
       )
    {
        delete tree->right;
        tree->right = NULL;
    }

    delete_leaves(tree->left);
    delete_leaves(tree->right);
}

// Ex. 6
void preorder(node* p)
{
    if(p == NULL)
        return;

    if(p->left != 0 && p->data - p->left->data < 2)
        p->left->data += 2;

    preorder(p->left);
    preorder(p->right);
}

void inorder(node* p)
{
    if(p == NULL)
        return;

    inorder(p->left);

    if(p->left != 0 && p->data - p->left->data < 2)
        p->left->data += 2;

    inorder(p->right);
}
void postorder(node* p)
{
    if(p == NULL)
        return;

    postorder(p->left);
    postorder(p->right);

    if(p->left != 0 && p->data - p->left->data < 2)
        p->left->data += 2;
}

// Ex. 7 same sequence with preorder and inorder
//              [1]                                OR                [1] 
//           /       \                                             [1]
//        NULL         [2]                                       [1]
//                  /       \                                  [1]
//               NULL        [3]                             [1]
//                         /      \
//                     NULL         [4]
//                               /       \
//                           NULL         [5]

// Ex. 8
node* mirror_tree(node* tree)
{
    if(tree == NULL)
        return NULL;

    node* mirror = new node{tree->data};
    mirror->left = mirror_tree(tree->right);
    mirror->right = mirror_tree(tree->left);

    return mirror;
}

// Ex. 9
void print_tree(node* tree, int depth = 0, char prefix = '.')
{
    if(tree == NULL)
        return;

    for(int i = 0; i < depth; i++)
        cout << prefix;
    cout << tree->data << endl;

    print_tree(tree->left, depth + 1, prefix);
    print_tree(tree->right, depth + 1, prefix);
}

// Ex. 10
struct node_calc {
    char op;
    int number;
    node_calc* left;
    node_calc* right;
};

int eval(node_calc* tree)
{
    if(tree->left == NULL && tree->right == NULL)
        return tree->number;

    int l = eval(tree->left);
    int r = eval(tree->right);
    int res;

    if(tree->op == '-')
        res = l - r;
    else if(tree->op == '*')
        res = l * r;
    else if(tree->op == '/')
        res = l / r;
    else // if(tree->op == '+')
        res = l + r;

    return res;
}

// Ex. 11 | k > 0
node* create_perfect_tree(int* a, const int k)
{
    if(k == 1)
        return new node{ a[0] };

    int n = pow(2,k) - 1;
    int i = (n - 1) / 2;
    node* tree = new node{ a[i] };

    tree->left = create_perfect_tree(a, k - 1);
    tree->right = create_perfect_tree(&a[i + 1], k - 1);

    return tree;
}

int main()
{
    /*node* root = new node{50};

    root->left = new node{20};
    root->right = new node{70};

    root->left->left = new node{10};
    root->left->left->left = new node{5};
    root->left->left->right = new node{15};
    root->left->right = new node{30};
    root->left->right->right = new node{35};

    root->right->left = new node{60};
    root->right->right = new node{70};
    root->right->right->right = new node{100};

    root->right->right->right->left = new node{90};*/

    /*cout << search(root, 32) << endl;

    cout << node_count(root) << endl;
    cout << leaves_count(root) << endl;
    cout << right_children_count(root) << endl;
    cout << tree_height(root) << endl;

    cout << is_balanced(root) << endl;

    cout << is_BST(root) << endl;

    delete_leaves(root);*/



    /*node* root = new node{10};

    root->left = new node{5};
    root->left->left = new node{4};
    root->left->left->left = new node{0};
    root->left->right = new node{6};
    root->left->right->right = new node{7};
    root->left->right->right->right = new node{9};

    root->right = new node{20};
    root->right->left = new node{15};
    root->right->left->left = new node{13};
    root->right->right = new node{30};*/


    /*print_tree(root);
    cout << "===" << endl;
    //preorder(root);
    //inorder(root);
    postorder(root);
    print_tree(root);*/


    /*print_tree(root);
    node* root2 = mirror_tree(root);
    cout << "===" << endl;
    print_tree(root2);*/

    //print_tree(root);



    // Ex. 10
    /*node_calc* root = new node_calc{'*'};

    root->left = new node_calc{'+'};
    root->left->left = new node_calc{' ', 7};
    root->left->right = new node_calc{' ', 8};

    root->right = new node_calc{'-'};
    root->right->left = new node_calc{' ', 3};
    root->right->right = new node_calc{' ', 2};

    cout << eval(root) << endl;*/



    // Ex. 11
    int a[] = {1, 2, 58, 67, 88, 99, 100, 101, 123, 111, 6, 4, 3, 32, 59};

    node* root = create_perfect_tree(a, 4);

    print_ttree(root);

    return 0;
}
