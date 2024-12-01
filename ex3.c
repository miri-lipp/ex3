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
//int dailySales[DAYS_IN_YEAR][NUM_OF_BRANDS];


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
void DailyData(int index, int dailySum[], int size , int array[][NUM_OF_BRANDS][NUM_OF_TYPES], int size1, int size2, int size3) {
    int day = 0;
    for (int i = 0; i < size ;i++) {
        while (array[day][index][i] != -1) {
            day++;
        }
        array[day][index][i] = dailySum[i];
    }
}
void PrintCube(int day) {
    printf("*****************************************\n\n");
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        printf("Sales for %s:\n", brands[i]);
        for (int j = 0; j < day; j++) {
            printf("Day %d-", j + 1);
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                printf(" %s: %d ", types[k], cube[j][i][k]);
            }
            printf("\n");
        }
    }
    printf("\n*****************************************\n");
}


int main() {
    //int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
   // int days[NUM_OF_BRANDS] = {0};
    int dailySum[NUM_OF_TYPES];
    int choice, index, day = 0;
    InitArray(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES);
    InitArray(dataForBrand, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES);
    printMenu();
    scanf("%d", &choice);
    while(choice != done) {
        switch(choice){
            case addOne: {
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
                DailyData(index, dailySum, NUM_OF_TYPES, dataForBrand, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES);
                break;
            }
            case addAll: {
                index = 0;
                int check = 0;
                for (int i = 0; i < NUM_OF_TYPES; i++) {
                    while (check < NUM_OF_BRANDS) {
                        printf("No data for brands ");
                        for (int j = 0; j < NUM_OF_BRANDS; j++) {
                            if (cube[day][j][i] == -1)
                                printf("%s ", brands[j]);
                        }
                        printf("\nPlease complete the data \n");
                        scanf("%d", &index);
                        if (index < 0 || index >= NUM_OF_BRANDS || cube[day][index][i] != -1) {
                            printf("This brand is not valid\n");
                            continue;
                        }
                        for (int j = 0; j < NUM_OF_TYPES; j++) {
                            scanf("%d", &dailySum[j]);
                        }
                        //DayOfSales(index, dailySum, NUM_OF_TYPES);
                        DailyData(index, dailySum, NUM_OF_TYPES, cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES);
                        check++;
                    }
                }
                day++;
                break;
            }
            case stats: {
                int dayUser, counter = 0;
                while (1) {
                    printf("What day would you like to analyze?\n");
                    scanf("%d", &dayUser);
                    if (dayUser <= 0 || dayUser > day + 1)
                        printf("Please enter a valid day.\n");
                    else
                        break;
                }
                printf("In day number %d: \n", dayUser);
                dayUser--;
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    for (int j = 0; j < NUM_OF_TYPES; j++)
                        counter += cube[dayUser][i][j];
                }
                printf("The sales total was %d\n", counter);
                int current[NUM_OF_BRANDS] = {0}; //buffer array for brands sum
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    for (int j = 0; j < NUM_OF_TYPES; j++) {
                        current[i] += cube[dayUser][i][j];
                    }
                }
                counter = current[0];
                int maxNum = 0; //checking place in array with biggest counter
                for (int i = 1; i < NUM_OF_BRANDS; i++) {
                    if (current[i] > counter) {
                        counter = current[i];
                        maxNum = i;
                    }
                }
                printf("The best sold brand with %d sales was %s\n", counter, brands[maxNum]);
                int current2[NUM_OF_TYPES] = {0}; //buffer array for types sum
                for (int i = 0; i < NUM_OF_TYPES; i++) {
                    for (int j = 0; j < NUM_OF_BRANDS; j++) {
                        current2[i] += cube[dayUser][j][i];
                    }
                }
                counter = current2[0];
                maxNum = 0;
                for (int i = 1; i < NUM_OF_TYPES; i++) {
                    if (current2[i] > counter) {
                        counter = current2[i];
                        maxNum = i;
                    }
                }
                printf("The best sold type with %d sales was %s\n", counter, types[maxNum]);
                break;
            }
            case print: {
                PrintCube(day);
                break;
            }
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


