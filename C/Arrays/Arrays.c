#include <stdio.h>

int main()
{
    printf("Here are some basic array manipulations:\n\n");
    
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};

    //grabbing size of array
    int size = sizeof(arr)/sizeof(arr[0]);
    printf("Size of Array: %d\nArray = {", size);
    
    //Printing Array
    for(int i = 0; i < size; i++)
    {
        printf("%d", arr[i]);
        if (i+1 !=  size)
        {
            printf(",");
        }
    }
    printf("}\n");

    
}
