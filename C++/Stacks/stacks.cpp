///Stacks Assignment (Converting to Binary and Hexadecimal)
/*
Jeremiah Alindogan
CISP 430
MW 5:30 PM
02/09/2018
*/


#include <iostream>
using namespace std;

//Node structure
struct node{
    int item;
    node* next;
};

//Pops node off stack
void pop(struct node *&top){
    struct node *temp;
    if(top){
        temp=top;
        top=top->next;
        delete temp;
    }
}

//Pushes node onto stack
void push(int item, struct node *&top){
    struct node *newNode=new node;

    newNode->item = item;
    newNode->next = top;
    top = newNode;
}

//Converts decimal to binary, then displays said conversion
void binary(int user){
    struct node* head = new node;
    head->next = 0;
    int temp = user;
    do{
        push(temp%2, head);
        temp /= 2;
    }while (temp != 0);

    //display conversion
    cout << user << " in binary: ";
    while(head->next){
        cout << head->item;
        pop(head);
    }
}

//Converts decimal to hexadecimal, then displays said conversion
void hexadecimal(int user){
    struct node* head = new node;
    head->next = 0;
    int temp = user;
    do{
        push(temp%16, head);
        temp /= 16;
    }while (temp != 0);

    //display conversion
    cout << endl << user << " in hexadecimal: ";
    while(head->next){
        if(head->item < 10)
            cout << head->item;
        else
            cout << (char)(head->item + 55);
        pop(head);
    }
}


int main(){
    int user = 0;
    while(user <= 0){
        cout << "Enter positive integer: ";
        cin >> user;
        cout << endl;
    }

    binary(user); //call for binary conversion
    hexadecimal(user); //call for hexadecimal conversion
    return 0;
}
