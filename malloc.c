#include<stdio.h>
#include<stdlib.h> // for malloc() - Dynamic Memory Allocation

int main()
{
    int* ptr;
    
    int n = 9;
    
    ptr = (int*) malloc(n * sizeof(int));
    
    if (ptr == NULL)
    {
        printf("Memory not allocated\n");
        exit(0);
    }
    else
    {
        printf("Memory successfully allocated using malloc\n");
        for (int i=0; i<n; i++)
        {
            ptr[i] = i+1;
        }
        printf("The elements are: ");
        for (int j=0; j<n; j++)
        {
            printf("%d ", ptr[j]);
        }
    }
    
    return 0;
}
