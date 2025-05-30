#include <stdio.h>
#include<omp.h>

int main() {
    int array1[16],array2[16],result[16];               // Initialization of arrays
    int i,j,N=16;                                       // Some neccessary variables

    // Storing value 1-16 in array1
    
        for(i=0;i<N;i++){
            array1[i] = i+1;
        }
    
    // Storing values 16-1 in array2
    
        for(i=0;i<N;i++){
            array2[i] = N-i;
        }

    // Parallelized code for addition of two arrays
    #pragma omp parallel for
    {
        for(int i = 0; i < N; i++)
            result[i] = array1[i] + array2[i];
    }

    for (int i = 0; i < N; i++)
    { 
        printf("%d ", result[i]);
    }
    printf("\n");
    return 0;
}