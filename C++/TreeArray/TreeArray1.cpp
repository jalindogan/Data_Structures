/**************
Jeremiah Alindogan
CISP 430
Sabzevary
04/25/18
**************/
#include <iostream>
#include <fstream>
#include <cmath>
#include <queue>
using namespace std;

#define MAX 10 //max size of file

ifstream in("input.txt");

struct Tree
{
    int value;
    int height;
    Tree *left;
    Tree *right;
};

struct node
{
    Tree *t;
    node *next;
};

int clean()
{
      string comments;  //store the comments in this variable
       while (in.peek()=='\n' || in.peek()=='/' || in.peek() == ' ' || in.peek()=='\t'){
           if (in.peek()=='/' )
              getline(in, comments);  //read the entire line because it is a comment
           else
              in.get();    //eat the newline, space and tab characters
      }
      return 1;
}

int getmax(int leftvalue, int rightvalue)
{
    if(leftvalue > rightvalue)
        return leftvalue;
    return rightvalue;
}

int height(Tree *leaf)
{
    if(!leaf)
        return -1;
    return leaf->height;
}

int getBalance(Tree *leaf)
{
    return(height(leaf->left) - height(leaf->right));
}

Tree* leftrotate(Tree *x)
{
    Tree *y = x->right;
    x->right = y->left;
    y->left = x;
    x->height = getmax(height(x->left), height(x->right)) + 1;
    y->height = getmax(height(x->left), height(x->right)) + 1;
    return y;
}

Tree* rightrotate(Tree *x)
{
    Tree *y = x->left;
    x->left = y->right;
    y->right = x;
    x->height = getmax(height(x->left), height(x->right)) + 1;
    y->height = getmax(height(x->left), height(x->right)) + 1;
    return y;
}

void rebalance(Tree *&leaf)
{
    leaf->height = getmax(height(leaf->left), height(leaf->right)) + 1;
    int balance = getBalance(leaf);
    if (balance > 1)
    {
        if (getBalance(leaf->left) < 0)
        {
            leaf->left = leftrotate(leaf->left);
            leaf = rightrotate(leaf);
        }else
            leaf = rightrotate(leaf);
    }
    else if (balance < -1)
    {
        if (getBalance(leaf->right) > 0)
        {
            leaf->right = rightrotate(leaf->right);
            leaf = leftrotate(leaf);
        }else
            leaf = leftrotate(leaf);
    }
}

//inputs item into the rear
void enqueue(Tree* root, struct node *&front, struct node*&rear)
{
    struct node *newNode=new node;

    newNode->t = root;
    newNode->next=NULL;
    if (rear){
        rear->next=newNode;
        rear = newNode;
    }else
        front = rear =newNode;
}

//takes off item from the front
void dequeue(struct node *& front, struct node *& rear)
{
    struct node *temp;

    if(front){
        temp = front;
        front = front->next;
        delete temp;
        if (!front)
            rear=NULL;
    }
}

void PrintLevel(struct Tree* root)
{
    node *frontroot, *rearroot, *nextfront, *nextrear;
    Tree* temp = root;
    frontroot = rearroot = nextfront = nextrear = 0;

    enqueue(temp, frontroot, rearroot); //taking in first tree
    while(frontroot) //while 1st queue is not empty
    {
        cout << frontroot->t->value << "(" << frontroot->t->height << ", " << getBalance(frontroot->t) << ") "; //prints value inside current tree in 1st queue
        temp = frontroot->t; //grabbing queued tree for left and right leaves
        dequeue(frontroot, rearroot); //removes first tree from 1st queue

        if (temp->left) //if there is a left root, add to 2nd queue
        {
            enqueue(temp->left, nextfront, nextrear);
        }
        if (temp->right) //if there is a right root, add to 2nd queue
        {
            enqueue(temp->right, nextfront, nextrear);
        }
        if (!frontroot) //if 1st queue is empty, set 2nd queue, as the first queue
        {
            frontroot = nextfront;
            rearroot = nextrear;
            while(nextfront)
                dequeue(nextfront, nextrear);
            cout << endl;
        }
    }
}

void inserttree(Tree *&leaf, int key)
{
    if(!leaf)
    {
        leaf = new Tree;
        leaf->value = key;
        leaf->height = 0;
        leaf->right = 0;
        leaf->left = 0;
        return;
    }

    if(key < leaf->value)
        inserttree(leaf->left, key);
    else
        inserttree(leaf->right, key);
    rebalance(leaf);
}

//Sorted Array to Binary Tree
void sarr_to_tree(Tree *&root, int arr[], int Start, int End)
{
    int Middle = (Start + End)/2;

    if (Start > End) //Base
        return;
    inserttree(root, arr[Middle]);
    sarr_to_tree(root, arr, Start, Middle-1);
    sarr_to_tree(root, arr, Middle+1, End);
}

void leftrightindex (Tree *root, int arr[], int arraysize, int i)
{
    if (root->left)
        arr[2*i + 1] = root->left->value;
    if (root->right)
        arr[2*i + 2] = root->right->value;
}

int maxDepth(struct Tree* node) {
  if (node==NULL) {
    return(-1);
  }
  else {
    // compute the depth of each subtree
    int LDepth = maxDepth (node->left);
    int RDepth = maxDepth (node->right);
    // use the larger one
    if (LDepth > RDepth)
        return(LDepth +1);
    else
        return(RDepth +1);
  }
}

//Binary Tree to Unsorted Array
int* tree_to_uarr(Tree *&root, int sizeofarray)
{
    int i = 0;
    int *arr = new int[sizeofarray];
    queue<Tree*> q;
    q.push(root);
    arr[i] = root->value;
    while(1)
    {
        int size = q.size();
        if(!size) break;
        while(size)
        {
            Tree *n = q.front();
            q.pop();
            if (n->left)
            {
                q.push(n->left);
                arr[2*i+1] = n->left->value;
            }
            else if (!n->left && height(n))
                arr[2*i+1] = 0;
            if (n->right)
            {
                q.push(n->right);
                arr[2*i+2] = n->right->value;
            }
            else if (!n->right && height(n))
                arr[2*i+2] = 0;
            size--;
            i++;
        }
    }
    return arr;
}

void uarr_to_tree(Tree *&root, int *uarr, int SIZE)
{
    for(int i = 0; i < SIZE; i++)
    {
        if (uarr[i])
            inserttree(root, uarr[i]);
    }
}

void InOrderPrint(Tree* leaf) //left, root, right
{
    if (!leaf)
        return;
    InOrderPrint(leaf->left);
    cout << leaf->value << " ";
    InOrderPrint(leaf->right);
}

int main()
{
    Tree *root = 0, *root1 = 0;
    int arr[MAX] = {};
    int *uarr = 0;
    int SIZE = 0;

    //grabbing input.txt
    cout << "Sorted array from input.txt: \n";
    while(clean() && in.good())
    {
        in >> arr[SIZE];
        cout << arr[SIZE++] << " ";
    }

    //sorted array to binary tree
    //sarr_to_tree(root, arr, 0, SIZE-1);
    //cout << "\n\nSorted Array to Tree: \n";
    //PrintLevel(root);

    //binary tree to unsorted array
    SIZE = pow(maxDepth(root)+1, 2.0) - 1;
    uarr = tree_to_uarr(root, SIZE);
    cout << "\nBinary Tree to Unsorted Array: \n";
    for(int i = 0; i < SIZE-1; i++)
    {
        cout << uarr[i] << " ";
    }

    //unsorted array to binary tree
    uarr_to_tree(root1, uarr, SIZE);
    cout << "\n\nUnsorted array to Binary Tree: \n";
    PrintLevel(root1);

    cout << "\nIn Order Format of Above Tree: \n";
    InOrderPrint(root1);
    return 0;
}
