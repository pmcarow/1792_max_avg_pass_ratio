#include <stdlib.h>
#include <stdio.h>
#include <time.h>

const int minSz = 1;
const int maxSz = 10;

int** createList(int rows) {
    int* values = calloc(rows*2, sizeof(int));
    int** arrRows = malloc(rows*sizeof(int*));
    for (int i=0; i<rows; ++i)
    {
        arrRows[i] = values + i*2;
    }

    for(int i=0; i<rows; i++) {
        arrRows[i][1] = rand() % (maxSz - minSz + 1) + minSz;
        arrRows[i][0] = rand() % (arrRows[i][1] - minSz + 1) + minSz;
    }
    return arrRows;
}

void printList(int rows, int** CL) {
    for(int i=0; i<rows; i++) {
        printf("|");
        for(int j=0; j<2; j++) {
            printf("%d",CL[i][j]);
            if(j<1) {
                printf(",");
            }  
        }
    printf("|");
    printf("\n");
    }
}

// Bubble sort implementation
void bubbleSort(int rows,int** CL) {
   for (int i = 0; i < rows - 1; i++) {
        if (CL[i][1] > CL[i+1][1]) {
            int* temp = CL[i];
            CL[i] = CL[i + 1];
            CL[i + 1] = temp;
        }
    }
}

float magic(int rows, int ES, int** CL) {
    float runningTotal = 0.0f;
    int ES_left = ES;
    float average;
    for(int i=0; i<rows; i++) {
        while(CL[i][0]<CL[i][1] && ES_left > 0) {
            CL[i][0]++;
            ES_left--;
        }
        runningTotal += (float)CL[i][0]/(float)CL[i][1];
    }
    average = runningTotal/(float)rows;

    return average*100;
}

int main() {
    srand ( time(NULL) );
    int nClasses = rand() % (maxSz - minSz + 1) + minSz;
    int extraStudents = rand() % (maxSz - minSz + 1) + minSz;
    int** classList = createList(nClasses);

    printf("Extra Students: %d\n",extraStudents);

    printList(nClasses,classList);

    bubbleSort(nClasses,classList);

    printf("\n");
    
    // printList(nClasses,classList);

    float avg = magic(nClasses,extraStudents,classList);

    printList(nClasses,classList);

    printf("\n");

    printf("%f\n",avg);

    return 0;
}