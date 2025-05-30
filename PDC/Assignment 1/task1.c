#include <stdio.h>
int main() {
    
    int N = 8; // Assuming the N is no of cores.

    for(int i=0; i<N; i++)
        printf("Hello, World! This is thread \n");

return 0;
}