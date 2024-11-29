/******************
Name:
ID:
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2  
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};
int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
int dataForBrand[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];


void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}
void InitArray(int array[][NUM_OF_BRANDS][NUM_OF_TYPES], int size1, int size2, int size3) { //initializing array to -1
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            for (int k = 0; k < size3; k++) {
                array[i][j][k] = -1;
            }
        }
    }
}
void DailyData(int index, int dailySum[], int size) {
    int day = 0;
    //int dataForBrand[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
   // InitArray(dataForBrand, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES);
    for (int i = 0; i < size ;i++) {
        while (dataForBrand[day][index][i] != -1) {
            day++;
        }
        dataForBrand[day][index][i] = dailySum[i];
    }
}


int main() {
    //int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    int days[NUM_OF_BRANDS] = {0};
    int choice;
    InitArray(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES);
    InitArray(dataForBrand, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES);
    printMenu();
    scanf("%d", &choice);
    while(choice != done){
        switch(choice){
            case addOne: {
                int index;
                int dailySum[NUM_OF_TYPES];
                printf("Add data sales for brand: \n");
                scanf("%d", &index);
                if (index < 0 || index > NUM_OF_TYPES) {
                    printf("This brand is not valid\n");
                    break;
                }
                printf("Add sales:\n");
                for (int i = 0; i < NUM_OF_TYPES; i++) {
                    scanf("%d", &dailySum[i]);
                }
                DailyData(index, dailySum, NUM_OF_TYPES);
                break;
            }
            case addAll: {
                int day = 0;
                while (cube[day][NUM_OF_BRANDS][NUM_OF_TYPES] != -1) {
                    day++;
                }

                break;
            }
            case stats:
                break;
            case print:
                break;
            case insights:
                break;
            case deltas:
                break;
            default:
                printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}


