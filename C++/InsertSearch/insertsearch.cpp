/***********
Jeremiah Alindogan
CISP 430
Sabzevary
04/06/2018
***********/

#include <string.h>
#include <fstream>
#include <cstring>
#include <iostream>
using namespace std;

#define SIZE 30 ///size of character arrays

struct node
{
    char name[SIZE];
    struct node* next;
};

struct Tree
{
    char name[SIZE];
    node *duplicates; //pointer to stack
    int dupecount; //# of iterations
    Tree *left;
    Tree *right;
};


ifstream in("input.txt");

int clean()
{
      string comments;  //store the comments in this variable
       while (in.peek()=='\n' || in.peek()=='/' || in.peek()==' ' || in.peek()=='\t'){
           if (in.peek()=='/' )
              getline(in, comments);  //read the entire line because it is a comment
           else
              in.get();    //eat the newline, space and tab characters
      }
      return 1;
}


/*using stack method*/
void pop(struct node *&top)
{
    struct node *temp;
    if(top)
    {
        temp=top;
        top=top->next;
        delete temp;
    }
}

void push(struct node *&top, char item[])
{
    struct node *newNode=new node;
    strcpy(newNode->name, item);
    newNode->next=top;
    top=newNode;
}

void traverse(node* mylist){ //traverse through nodes and displays their data
    node* curr = mylist;
    while(curr)
    {
        cout << curr->name << " ";
        curr = curr->next;
    }
}


int strcmpi(char const *a, char const *b) //no strcmpi in standard library
{
    for (;; a++, b++) {
        int d = tolower(*a) - tolower(*b);
        if (d != 0 || !*a)
            return d;
    }
}

//creates new tree
Tree* Inserttree(struct Tree *leaf, char item[])
{
    if (!leaf) //finds place to insert
    {
        leaf = new Tree;
        leaf->right = 0;
        leaf->left = 0;
        leaf->dupecount = 1; //1 iteration for one name
        strcpy(leaf->name, item); //copies item to names[]
    }
    /* opposite of actual binary search tree --- left > right */
    else if(strcmpi(item, leaf->name) > 0)//if item is great than key, place left
    {
        leaf->left = Inserttree(leaf->left, item);
    }
    else if(strcmpi(item, leaf->name) < 0) //if item is less than key, place right
    {
        leaf->right = Inserttree(leaf->right, item);
    }
    else if(strcmpi(item, leaf->name) == 0) //if duplicate, store in link list;
    {
        push(leaf->duplicates, item);
        leaf->dupecount++;
    }
    return(leaf);
}

void searchtree(Tree *leaf, char item[]) //searches tree for item and displays iterations
{
    bool found = 0;
    cout << "Search path: ";
    while (leaf && !found)
    {
        cout << leaf->name << " ";
        if (strcmpi(item, leaf->name) == 0)
        {
            found = true;
            cout << "\nName found. \n# of Iterations: " << leaf->dupecount;
        }
        else if (strcmpi(item, leaf->name) > 0)
        {
            cout << "-> ";
            leaf=leaf->left;
        }
        else
        {
            cout << "-> ";
            leaf=leaf->right;
        }
    }
    if (!found)
        cout << "\nNot found.";
}


void findandprint(Tree *leaf) //gets user input and calls search function
{
    char input[SIZE];
    bool found = 0;
    cout << "\nEnter name to search for: ";
    cin >> input;
    searchtree(leaf, input);
}

/*
void PreOrderPrint(Tree* leaf) //root, left, right
{
    if (!leaf)
        return;
    cout << leaf->name << " ";
    PreOrderPrint(leaf->left);
    PreOrderPrint(leaf->right);
}*/

int main()
{
    Tree *root = 0;
    char str[SIZE] = "";

    while(clean() && in.good()) //read input.txt
    {
        in >> str;
        root = Inserttree(root, str);
    }
    //cout << "List of names (Preorder): ";
    //PreOrderPrint(root);
    cout << endl;
    findandprint(root);
    return 0;
}
