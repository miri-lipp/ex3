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
// void PrintCube(int day) {
//     printf("*****************************************\n\n");
//     for (int i = 0; i < NUM_OF_BRANDS; i++) {
//         printf("Sales for %s:\n", brands[i]);
//         for (int j = 0; j < day; j++) {
//             printf("Day %d-", j + 1);
//             for (int k = 0; k < NUM_OF_TYPES; k++) {
//                 if (cube[j][i][k] != 0)
//                     printf(" %s: %d ", types[k], cube[j][i][k]);
//                 else
//                     printf(" %s: ", types[k]);
//             }
//             printf("\n");
//         }
//     }
//     printf("\n*****************************************\n");
// }
void printBrands(int index) {
    printf(" ");
    for (int i = 0; i < BRANDS_NAMES; i++) {
        //printf(" ");
        if (brands[index][i] != '\0')
            printf("%c", brands[index][i]);
    }
    //printf(" ");
}
void printTypes(int index) {
    printf(" ");
    for (int i = 0; i < TYPES_NAMES; i++) {
        if (types[index][i] != '\0')
            printf("%c", types[index][i]);
    }
    //printf(" ");
}


int main() {
    //int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
   // int days[NUM_OF_BRANDS] = {0};
    int dailySum[NUM_OF_TYPES];
    int choice, index, day = 0;
    int brandEarning[DAYS_IN_YEAR][NUM_OF_BRANDS];
    InitArray(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES);
    //InitArray(dataForBrand, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES);
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
                        printf("No data for brands");
                        for (int j = 0; j < NUM_OF_BRANDS; j++) {
                            if (cube[day][j][i] == -1)
                                printBrands(j);
                                //printf("%s ", brands[j]);

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
                printf("The best sold brand with %d sales was", counter);
                printBrands(maxNum);
                printf("\n");
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
                printf("The best sold type with %d sales was", counter);
                printTypes(maxNum);
                printf("\n");
                break;
            }
            case print: {
                //PrintCube(day);
                printf("*****************************************\n\n");
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    printf("Sales for");
                    printBrands(i);
                    printf(":\n");
                    for (int j = 0; j < day; j++) {
                        printf("Day %d-", j + 1);
                        for (int k = 0; k < NUM_OF_TYPES; k++) {
                            if (cube[j][i][k] != 0) {
                                printTypes(k);
                                printf(": %d", cube[j][i][k]);
                            }
                            else {
                                printTypes(k);
                                printf(":");
                            }
                        }
                        printf("\n");
                    }
                }
                printf("\n*****************************************\n");
                break;
            }
            case insights: {
                int counter = 0;
                int maxNum = 0; //checking place with biggest counter
                int current[NUM_OF_BRANDS] = {0};//buffer array for brands
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    for (int j = 0; j < day; j++) {
                        for (int k = 0; k < NUM_OF_TYPES; k++) {
                            current[i] += cube[j][i][k];
                        }
                    }
                }
                counter = current[0];
                for (int i = 1; i < NUM_OF_BRANDS; i++) {
                    if (counter < current[i]) {
                        counter = current[i];
                        maxNum = i;
                    }
                }
                printf("The best selling brand overall is");
                printBrands(maxNum);
                printf(": %d$\n", counter);
                int current2[NUM_OF_TYPES] = {0};//buffer for checking types
                for (int i = 0; i < NUM_OF_TYPES; i++) {
                    for (int j = 0; j < day; j++) {
                        for (int k = 0; k < NUM_OF_BRANDS; k++) {
                            current2[i] += cube[j][k][i];
                        }
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
                //printf("The best selling type of car is %s: %d$\n", types[maxNum], counter);
                printf("The best selling car type is");
                printTypes(maxNum);
                printf(": %d$\n", counter);
                int current3[DAYS_IN_YEAR] = {0};
                for (int i = 0; i < day; i++) {
                    for (int j = 0; j < NUM_OF_BRANDS; j++) {
                         for (int k = 0; k < NUM_OF_TYPES; k++) {
                             current3[i] += cube[i][j][k];
                         }
                     }
                 }
                 counter = current3[0];
                 maxNum = 0;
                 for (int i = 1; i < day; i++) {
                     if (current3[i] > counter) {
                         counter = current3[i];
                         maxNum = i;
                     }
                }
                maxNum = maxNum + 1;
                printf("The most profitable day was day number %d: %d$\n", maxNum, counter);
                break;
            }
            case deltas: {
                float delta[NUM_OF_BRANDS] = {0};
                int counter[DAYS_IN_YEAR][NUM_OF_BRANDS] = {0};
                for (int i = 0; i < DAYS_IN_YEAR; i++) {
                    for (int j = 0; j < NUM_OF_TYPES; j++) {
                        for (int k = 0; k < NUM_OF_BRANDS; k++) {
                            counter[i][k] += cube[i][k][j];
                            delta[k] = counter[i][k]
                        }
                    }
                }

                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    printf("Brand: ");
                    printBrands(i);
                    printf(", Average Delta: ,%f.6");
                }
                break;
            }
            default:
                printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}


