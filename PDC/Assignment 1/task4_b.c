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

    // Sum array1 using atomic (it is used update variable only one thread at a time)
    #pragma omp parallel for num_threads(16)
    for(int i = 0; i < N; i++) 
    {
        #pragma omp atomic
        result1 += array1[i];
    }

    // If result1 > 10, sum array2
    if(result1 > 10) 
    {
        #pragma omp parallel for num_threads(16)
        for(int j = 0; j < N; j++) 
        {
            #pragma omp atomic
            result2 += array2[j];
        }
    }

    printf("Total sum: %d \n",result2);
    return 0;
}

/*Overall due to beauty of C language, you can not catch the difference but theoratically atomic is slower than reduction
because atomic make sure that variable can be update by only one thread at a time.*/