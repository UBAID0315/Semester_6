#include <stdio.h>
int main() {
    int array1[16],array2[16];
    int result1 = 0, result2 = 0,i,j,N=16;

    #pragma omp parallel sections num_threads(2)        // Storing some values in arrays
    {

        // Storing value 1-16 in array1
        #pragma omp section 
        {
            for(i=0;i<N;i++)
            {
                array1[i] = i+1;
            }
        }

        // Storing values 16-1 in array2
        #pragma omp section
        {
            for(i=0;i<N;i++)
            {
                array2[i] = N-i;
            }
        }
    }

    // Sum array1 using reduction (it is used to sum all the final thread value into one variable)
    #pragma omp parallel for reduction(+:result1) num_threads(16)
    for(int i = 0; i < N; i++) 
    {
        result1 += array1[i];
    }

    // If result1 > 10, sum array2
    if(result1 > 10) 
    {
        #pragma omp parallel for reduction(+:result2) num_threads(16)
        for(int j = 0; j < N; j++) 
        {
            result2 += array2[j];
        }
    }

    printf("Total sum: %d \n",result2);
    return 0;
}