#include <stdio.h>
#include <stdlib.h>
#include <time.h>


float promedio(int a, int b, int c) {
    return (float)(a + b + c ) / 3;
}

int main () {
    srand(time(NULL));
    FILE* ent = fopen("sal.txt", "w");
    int k = 0;
    for (int i = 0 ; i < 10000000; i++) {
        k = (rand() % 90) + 34;
        fprintf(ent, "%c", k);
        //printf("%c", k);
        k++;
    }
    fclose(ent);

    return 0;
}