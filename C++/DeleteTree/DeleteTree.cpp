/**************
Jeremiah Alindogan
CISP 430
Sabzevary
04/09/18
**************/
#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdio>
using namespace std;

#define SIZE 10
ifstream in("input.txt");
ofstream out("output.txt");

struct Tree
{
    int num;
    Tree* left; //lesser values
    Tree* right; //greater values
};

struct node //for print order (levels)
{
    Tree* t;
    node* next;
};

void enqueue(Tree* root, struct node *&front, struct node*&rear)
{ //inputs item into the rear
    struct node *newNode=new node;

    newNode->t = root;
    newNode->next=NULL;
    if (rear){
        rear->next=newNode;
        rear = newNode;
    }else
        front = rear =newNode;
}

void dequeue(struct node *& front, struct node *& rear)
{ //takes off item from the front
    struct node *temp;

    if(front){
        temp = front;
        front = front->next;
        delete temp;
        if (!front)
            rear=NULL;
    }
}

int clean()
{
      string comments;  //store the comments in this variable
       while (in.peek()=='\n' || in.peek()=='/' || in.peek()=='\t'){
           if (in.peek()=='/' )
              getline(in, comments);  //read the entire line because it is a comment
           else
              in.get();    //eat the newline, space and tab characters
      }
      return 1;
}

//creates new tree or inserts into tree
Tree* Inserttree(Tree* leaf, int item)
{
    if (!leaf) //finds place to insert
    {
        leaf = new Tree;
        leaf->right = 0;
        leaf->left = 0;
        leaf->num = item;
    }
    else if(item < leaf->num)//if item is less than key, place left
        leaf->left = Inserttree(leaf->left, item);
    else if(item > leaf->num) //if item is greater than key, place right
        leaf->right = Inserttree(leaf->right, item);
    return(leaf);
}

//finds minimum value in a tree
Tree* minvalue(Tree* leaf)
{
    Tree* curr = leaf;
    while (curr->left != NULL) //finding min value in left leaves
        curr = curr->left;
    return curr;
}

//deletes leaf in a tree and return new root
Tree* deleteleaf(Tree* root, int key)
{
    //base
    if (root == NULL)
    {
        root = Inserttree(root, key);
        return root;
    }
    if (key < root->num)
        root->left = deleteleaf(root->left, key);
    else if (key > root->num)
        root->right = deleteleaf(root->right, key);
    else if (key == root->num)//if found
    {
        // leaf with only one child or no child
        if (root->left == NULL)
        {
            Tree* temp = root->right;
            delete(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            Tree* temp = root->left;
            delete(root);
            return temp;
        }
        //leaf with two children
        Tree* temp = minvalue(root->right); //search for minimum to the right of root
        root->num = temp->num;
        root->right = deleteleaf(root->right, temp->num);
    }
    return root;
}

//grabs the int after keyword
int getint(char input[])
{
    int target = 0;
    sscanf(input, "%*s %d", &target);
    return target;
}

//checks whole input if it is a number
bool checkforint(char input[])
{
    for(int i = 0; i < strlen(input); i++)
    {
        if (!isdigit(input[i]))
            return false;
    }
    return true;
}

//checks input to check whether to add into tree or to delete
void checkinput(Tree *&root, char input[])
{
    int number = 0;
    cout << ">" << input << endl;
    if(checkforint(input)) //if just a number
    {
        sscanf(input, "%d", &number);
        root = Inserttree(root, number);
    }
    else if(strstr(input, "delete")) //searches for keyword
    {
        root = deleteleaf(root, getint(input));
    }
    else
        cout << "Invalid input\n";
}

void PreOrderPrint(Tree* leaf) //root, left, right
{
    if (!leaf)
        return;
    out << leaf->num << " ";
    PreOrderPrint(leaf->left);
    PreOrderPrint(leaf->right);
}

void InOrderPrint(Tree* leaf) //left, root, right
{
    if (!leaf)
        return;
    InOrderPrint(leaf->left);
    out << leaf->num << " ";
    InOrderPrint(leaf->right);
}

void PostOrderPrint(Tree* leaf) //left, right, root
{
    if (!leaf)
        return;
    PostOrderPrint(leaf->left);
    PostOrderPrint(leaf->right);
    out << leaf->num << " ";
}

void PrintLevel(struct Tree* root)
{
    node *frontroot, *rearroot, *nextfront, *nextrear;
    Tree* temp = root;
    frontroot = rearroot = nextfront = nextrear = 0;
    enqueue(temp, frontroot, rearroot);
    while(frontroot)
    {

        cout << "  "<< frontroot->t->num;
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
            nextfront = nextrear = 0;
            cout << endl;
        }
    }
}

int main()
{
    Tree *root = NULL;
    char input[SIZE];

    //Reading inputs and inserting to tree
    cout << "Reading...\n";
    while(in.good() && clean())
    {
        in.getline(input, sizeof(input));
        checkinput(root, input);
    }

    out << "PreOrder: ";
    PreOrderPrint(root);

    out << "\nIn Order: ";
    InOrderPrint(root);

    out << "\nPost Order: ";
    PostOrderPrint(root);

    out << "\nPrint Order: \n";
    PrintLevel(root);
}
