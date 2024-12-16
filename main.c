#include <stdlib.h>
#include <stdio.h>
#include <time.h>

const int minSz = 1;
const int maxSz = 10;

struct ClassStruct {
    int rows;
    int** ClassList;
    float** ClassStats;
};

void createList(struct ClassStruct* CS) {
    int* i_values = calloc(CS->rows*2, sizeof(int));
    float* f_values = calloc(CS->rows*2, sizeof(float));
    CS->ClassList = malloc(CS->rows*sizeof(int*));
    CS->ClassStats = malloc(CS->rows*sizeof(float*));
    for (int i=0; i<CS->rows; ++i)
    {
        CS->ClassList[i] = i_values+i*2;
        CS->ClassStats[i] = f_values+i*2;
    }

    for(int i=0; i<CS->rows; i++) {
        CS->ClassList[i][1] = rand() % (maxSz - minSz + 1) + minSz;
        CS->ClassList[i][0] = rand() % (CS->ClassList[i][1] - minSz + 1) + minSz;
        CS->ClassStats[i][0] = (float)CS->ClassList[i][0]/(float)CS->ClassList[i][1];
        CS->ClassStats[i][1] = (float)(CS->ClassList[i][0]+1)/(float)(CS->ClassList[i][1]+1);
    }
}

void printList(struct ClassStruct* CS) {
    for(int i=0; i<CS->rows; i++) {
        printf("|");
        printf("%d,",CS->ClassList[i][0]);
        printf("%d,",CS->ClassList[i][1]); 
        printf("%f,",CS->ClassStats[i][0]);
        printf("%f",CS->ClassStats[i][1]);
        printf("|");
        printf("\n");
    }
}

// Bubble sort implementation
void bubbleSort(struct ClassStruct* CS) {
   for (int i = 0; i < CS->rows - 1; i++) {
        if (CS->ClassList[i][1] > CS->ClassList[i+1][1]) {
            int* temp_i = CS->ClassList[i];
            CS->ClassList[i] = CS->ClassList[i + 1];
            CS->ClassList[i + 1] = temp_i;

            float* temp_f = CS->ClassStats[i]; 
            CS->ClassStats[i] = CS->ClassStats[i + 1];
            CS->ClassStats[i + 1] = temp_f;
        }
    }
}

float magic(struct ClassStruct* CS, int ES) {
    float runningTotal = 0.0f;
    int ES_left = ES;
    float average;
    for(int i=0; i<CS->rows; i++) {
        while(CS->ClassList[i][0]<CS->ClassList[i][1] && ES_left > 0) {
            CS->ClassList[i][0]++;
            CS->ClassList[i][1]++;
            ES_left--;
        }
        runningTotal += (float)CS->ClassList[i][0]/CS->ClassList[i][1];
    }
    average = runningTotal/(float)CS->rows;

    return average*100;
}

int main() {
    srand ( time(NULL) );

    int extraStudents = rand() % (maxSz - minSz + 1) + minSz;
    
    struct ClassStruct mainList;
    
    mainList.rows = rand() % (maxSz - minSz + 1) + minSz;
    
    createList(&mainList);

    printf("Extra Students: %d\n",extraStudents);

    // printList(&mainList);

    bubbleSort(&mainList);

    // printf("\n");

    // float avg = magic(&mainList,extraStudents);

    printList(&mainList);

    printf("\n");

    // printf("%f\n",avg);

    return 0;
}