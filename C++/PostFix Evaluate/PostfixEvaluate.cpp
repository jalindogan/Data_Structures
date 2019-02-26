///Postfix Evaluation

/*
Jeremiah Alindogan
CISP 430
MW 5:30PM
02/13/2018
*/

#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

ifstream in("input.txt");

struct node{
    char item;
    struct node *next;
};

void traverse(node* mylist){ //traverse through nodes and displays their data
    node* curr = mylist;
    while(curr->next)
    {
        cout << curr->item;
        curr = curr->next;
    }
    cout << curr->item;
}


char pop(struct node *&top){
    struct node *temp;
    char item;
    item = top->item;

    if(top){
        temp=top;
        top=top->next;
        delete temp;
    }
    return item;
}

void push(int item, struct node *&top){
    struct node *newNode=new node;

    newNode->item=item;
    newNode->next=top;
    top=newNode;
}



int main(){
    struct node *top = 0;
    char item = '5';
    int value1 = 0, value2 = 0, result = 0;


    cout << "Postfix equation (with only + - * /): \n";

    //create stack with equation
    while(in.good() && (in >> item)){
        cout << item;
        if(isdigit(item))
            push(item, top);
        else{
            value1 = (int)(pop(top) - '0');
            value2 = (int)(pop(top) - '0');
            result = 0;

            switch(item){
                case '+':
                    result = value2 + value1;
                    push((char)(result + '0'), top);
                    break;
                case '-':
                    result = value2 - value1;
                    push((char)(result + '0'), top);
                    break;
                case '*':
                    result = value2 * value1;
                    push((char)(result + '0'), top);
                    break;
                case '/':
                    result = value2/value1;
                    push((char)(result + '0'), top);
                    break;
            }
            //cout << value2 << " " << value1 << " = " << result << endl; ///used to check math
        }
    }
    cout << "\n\n\nResult:\n";
    cout << result;
    cout << endl;
}
