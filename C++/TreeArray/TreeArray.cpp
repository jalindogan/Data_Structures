#include <iostream>
#include <fstream>
#include <cmath>
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
    x->left = y->left;
    y->left = x;
    return y;
}

Tree* rightrotate(Tree *x)
{
    Tree *y = x->left;
    x->right = y->right;
    x->right = x;
    return y;
}

void rebalance(Tree *&leaf)
{
    leaf->height = getmax(height(leaf->left), height(leaf->right)) + 1;
    int balance = getBalance(leaf);
    if (balance > 1)
    {
        if (getBalance(leaf->left) < 0)
            leaf->left = leftrotate(leaf->left);
    }
    else if (balance < -1)
    {
        if (getBalance(leaf->right) > 0)
            leaf->right = rightrotate(leaf->right);
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
        cout << frontroot->t->value << " (" << frontroot->t->height << ", " << getBalance(frontroot->t) << ") "; //prints value inside current tree in 1st queue
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

void sarr_to_tree(Tree *&root, int arr[], int Start, int End)
{
    int Middle = (Start + End)/2;

    if (Start > End) //Base
        return;
    inserttree(root, arr[Middle]);
    sarr_to_tree(root, arr, Start, Middle-1);
    sarr_to_tree(root, arr, Middle+1, End);
}

void tree_to_uarr(Tree *&root, int arr[])
{
    node *frontroot, *rearroot, *nextfront, *nextrear;

    Tree* temp = root;
    Tree* emp = new Tree;
    emp->value = 0;
    emp->left = 0;
    emp->right = 0;
    int i = 0;
    int arraysize = pow(root->height, 2.0) - 1;
    cout << arraysize;
    frontroot = rearroot = nextfront = nextrear = 0;

    enqueue(temp, frontroot, rearroot);
    while(frontroot)
    {
        arr[i++] = frontroot->t->value;
        temp = frontroot->t;
        dequeue(frontroot, rearroot);
        if (temp->left)
            enqueue(temp->left, nextfront, nextrear);
        if (temp->right)
            enqueue(temp->right, nextfront, nextrear);
        if (!frontroot)
        {
            frontroot = nextfront;
            rearroot = nextrear;
            while(nextfront)
                dequeue(nextfront, nextrear);
        }
    }
}

int main()
{
    Tree *root = 0;
    int arr[MAX] = {};
    int uarr[MAX] = {};
    int SIZE = 0;

    cout << "Sorted array from input.txt: \n";
    for(;clean() && in.good(); SIZE++)
    {
        in >> arr[SIZE];
        cout << arr[SIZE] << " ";
    }
    cout << endl;

    sarr_to_tree(root, arr, 0, SIZE-1);
    cout << "Sorted Array to Tree: \n";
    //PrintLevel(root);

    //tree_to_uarr(root, uarr);
    for(int i : uarr)
        cout << i;
}
