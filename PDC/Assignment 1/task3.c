#include <stdio.h>
#include<omp.h>

int main() {
    int array1[16],array2[16],result[16];               // Initialization of arrays
    int i,N=16;                                         // Some neccessary variables


    // Using only 2 threads for the whole code
    #pragma omp parallel num_threads(2)
    {
        // Single is used to execute below code using single thread
        #pragma omp single
        {
            // Now there is two tasks both are independent to eachother
            #pragma omp task
            {
                // Storing values in array1
                for(int i=0;i<N;i++)
                {
                    array1[i] = i+1;
                }
            }

            // Second task now it can be handle by seperate thread
            #pragma omp task
            {
                // Storing values in array2
                for(int i=0;i<N;i++)
                {
                    array2[i] = N-i;
                }
            }        
        }

        // Barrier for tasks (to make sure they wait for others after finish)
        #pragma omp taskwait
        
        // Again single to create two more tasks
        #pragma omp single
        {
            // One task is for addition
            #pragma omp task
            {
                for(int i=0;i<N;i++)
                {
                    result[i] = array1[i] + array2[i];
                }
            }
            
            // Barrier (to make sure display result after addition operation)
            #pragma omp taskwait


            // Second is for display the result
            #pragma omp task
            {
                for(int i=0;i<N;i++)
                {
                    printf("%d ", result[i]);
                }
            }
        }        

    }
    printf("\nFinish");
}