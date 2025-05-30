#include <stdio.h>
#include<omp.h>

int main() {
    int array1[16],array2[16],result[16];               // Initialization of arrays
    int i,N=16;                                         // Some neccessary variables

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

    // Parallel code for addition of arrays
    #pragma omp parallel for num_threads(4)
    for(i = 0; i < N; i++)
    {
        result[i] = array1[i] + array2[i];
    }
    
    #pragma omp parallel num_threads(4)
    {
        // Condition for master-thread to execute this.
        if(omp_get_thread_num() == 0)
        {
            for(i=0;i<N;i++)
            {
                printf("%d ",result[i]);
            }
        }    
    }
    printf("\n");
return 0;
}