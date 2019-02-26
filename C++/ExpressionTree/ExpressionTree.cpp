#include <iostream>
#include <cmath> //for power
using namespace std;

/*
1)  Read a postfix expression from the keyboard.
2)  Place it in an expression tree.
3)  Evaluate the expression tree.
4)  Display the expression tree in infix notation
    with the parentheses in the correct place.
*/

#define SIZE 30

struct Tree
{
    char value;
    Tree *left = 0; //initialize to zero
    Tree *right = 0;
};

struct stacktree
{
    Tree *pot;
    stacktree *prev;
};

void pop(stacktree *&top){
    stacktree *temp;
    if(top){
        temp = top;
        top = top->prev;
        delete temp;
    }
}

void push(Tree* item, stacktree *&top){
    stacktree *newNode = new stacktree;
    newNode->pot = new Tree;
    newNode->pot = item;
    newNode->prev = top;
    top=newNode;
}

void traverse(stacktree* mylist){ //traverse through nodes and displays their data
    stacktree* curr = mylist;
    while(curr)
    {
        cout << curr->pot->value;
        curr = curr->prev;
    }
}

bool isOperator(char key)
{
    return(key == '+' || key == '-' ||
           key == '*' || key == '/' ||
           key == '(' || key == ')' ||
           key == '^');
}

void InputToStack(char input[], stacktree *&top)
{
    Tree* temptree = 0;

    for(int i = 0; input[i] != 0; i++)
    {
        temptree = new Tree;
        temptree->value = input[i]; //stores value in tree
        if(isOperator(input[i])) //hits operator
        {
            temptree->right = top->pot;
            pop(top); //pop connected operand
            temptree->left = top->pot;
            pop(top); //pop connected operand
        }
        push(temptree, top); //pushes tree into stack
    }
}

void StackPrint(Tree *root)
{
    Tree* temp = root;
    //check left tree if holding operator
    // if T -> run func again
    // if F -> print operand
    if (isOperator(root->left->value))
    {
        cout << "(";
        StackPrint(root->left); //puts left operand into parenthesis
        cout << ")";
    }
    else
        cout << root->left->value;

    //print operator
    cout << root->value;

    //check right tree
    if (isOperator(root->right->value))
    {
        cout << "(";
        StackPrint(root->right); //puts right operand into parenthesis
        cout << ")";
    }
    else
        cout << root->right->value;
}

int EvaluateExpression(Tree *root)
{
    int result = 0, value1 = 0, value2 = 0;

    //check left operand
    if (isOperator(root->left->value))
        value2 = EvaluateExpression(root->left);
    else
        value2 = (int)root->left->value - '0';

    //check right operand
    if (isOperator(root->right->value))
        value1 = EvaluateExpression(root->right);
    else
        value1 = (int)root->right->value - '0';

    //creating result based off operator
    switch(root->value){
                case '+':
                    result = value2 + value1;
                    break;
                case '-':
                    result = value2 - value1;
                    break;
                case '*':
                    result = value2 * value1;
                    break;
                case '/':
                    result = value2/value1;
                    break;
                case '^':
                    result = pow(value2, value1);
                    break;
            }

    return result;
}

int main()
{
    char input[SIZE] = {};
    stacktree* top = 0; //stores expression tree

    //1) Read postfix notation from keyboard
    cout << "Enter Postfix Notation (no spaces): \n";
    cin >> input;

    //2) Place into expression tree
    InputToStack(input, top);

    cout << "Evaluated Expression in Infix Notation:\n";

    //4)Display expression tree in infix notation with parentheses
    StackPrint(top->pot);

    //3)Evaluate expression tree
    cout << "=" << EvaluateExpression(top->pot) << endl;
}
