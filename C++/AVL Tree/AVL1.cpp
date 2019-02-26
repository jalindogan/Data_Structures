///AVL Tree Assignment

/*
Jeremiah Alindogan
CISP 430
Sabzevary
04/21/2018
*/

#include <iostream>
#include <fstream>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

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

//for printing into output file
void PrintLevel(struct Tree* root)
{
    node *frontroot, *rearroot, *nextfront, *nextrear;
    Tree* temp = root;
    frontroot = rearroot = nextfront = nextrear = 0;
    enqueue(temp, frontroot, rearroot);
    while(frontroot)
    {
        out << frontroot->t->value << "(" << frontroot->t->height << ", " << getBalance(frontroot->t) << ")   ";
        temp = frontroot->t;
        dequeue(frontroot, rearroot);
        if (temp->left)
        {
            enqueue(temp->left, nextfront, nextrear);
        }
        if (temp->right)
        {
            enqueue(temp->right, nextfront, nextrear);
        }
        if (!frontroot)
        {
            frontroot = nextfront;
            rearroot = nextrear;
            while(nextfront)
                dequeue(nextfront, nextrear);
            out << endl;
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

int main()
{
    Tree *root = 0;
    int input = 0;
    while(in.good() && clean())
    {
        in >> input;
        inserttree(root, input);
    }
    PrintLevel(root);
}
