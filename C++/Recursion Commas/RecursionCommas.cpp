///Recursion Commas *adds commas to large digits
/*
Jeremiah Alindogan
CISP 430 MW 5:30 - 6:50 PM
Sabzevary
03/05/2018
*/

#include <iostream>
#include <cstring>
using namespace std;

void commas(long long user) //recursive
{
    long long trip = user%1000; //takes last 3 of number

    if((trip < 10) && trip) //base case
    {
        if(trip) //does not print triple if equal to 0
            cout << trip;
        return;
    }
    else if (user < 1000) //if input is less than 1000
        cout << trip;
    else{
        commas((user - user%1000)/1000); //takes off last three digits
        cout << ",";
        if (trip == 0) // if trip is 0
            cout << "000";
        else
            cout << trip;
    }
}

int main()
{
    long long user = 0;
    cout << "Enter number w/o commas: ";
    cin >> user;
    commas(user);
}
