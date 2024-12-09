/******************
Name:Miriam Lipkovich
ID: 336239652
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
void InitArray(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int size1, int size2, int size3) { //initializing array to -1
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            for (int k = 0; k < size3; k++) {
                cube[i][j][k] = -1;
            }
        }
    }
}
void DailyData(int index, int dailySum[], int size , int cube[][NUM_OF_BRANDS][NUM_OF_TYPES]) { //adding data to the array
    int day = 0;
    for (int i = 0; i < size ;i++) {
        while (cube[day][index][i] != -1) { //checking the number of the day in which data needs to go
            day++;
        }
        cube[day][index][i] = dailySum[i];
    }
}

void printBrands(int index) { //function to print brands
    printf(" "); //I did it before we were told that we can use %s, so I decided to live it as it is
    for (int i = 0; i < BRANDS_NAMES; i++) {
        if (brands[index][i] != '\0')
            printf("%c", brands[index][i]);
    }
}
void printTypes(int index) { //function to print types
    printf(" ");
    for (int i = 0; i < TYPES_NAMES; i++) {
        if (types[index][i] != '\0')
            printf("%c", types[index][i]);
    }
}
int InputDayValidation( int CurrentDay) { //function that validates that the day user entered is positive and is with data
    int UserInputDay;
    while (1) {
        printf("What day would you like to analyze?\n");
        scanf("%d", &UserInputDay);
        if (UserInputDay <= 0 || UserInputDay >= CurrentDay + 1)
            printf("Please enter a valid day.\n");
        else
            break;
    }
    return UserInputDay; //returns the day that user entered after validation
}
int TotalSumOfSales(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int UserInputDay) {
    int buffer = 0;
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        for (int j = 0; j < NUM_OF_TYPES; j++)
            buffer += cube[UserInputDay][i][j];
    }
    return buffer; //returns total sales of the day in all of brands
}
void BestSellingBrand(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int UserInputDay) {
    int maxSales = 0;
    int current[NUM_OF_BRANDS] = {0}; //buffer array for brands sum
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        for (int j = 0; j < NUM_OF_TYPES; j++) {
            current[i] += cube[UserInputDay][i][j];
        }
    }
    maxSales = current[0];
    int maxIndex = 0; //checking place in array with the biggest counter
    for (int i = 1; i < NUM_OF_BRANDS; i++) {
        if (current[i] > maxSales) {
            maxSales = current[i];
            maxIndex = i;
        }
    }
    printf("The best sold brand with %d sales was", maxSales);
    printBrands(maxIndex);
    printf("\n");
}
void BestSellingType(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int UserInputDay) {
    int current[NUM_OF_TYPES] = {0}; //buffer array for types sum
    int maxSales = 0;
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            current[i] += cube[UserInputDay][j][i];
        }
    }
    maxSales = current[0]; //checking place in array with the biggest counter
    int maxIndex = 0;
    for (int i = 1; i < NUM_OF_TYPES; i++) {
        if (current[i] > maxSales) {
            maxSales = current[i];
            maxIndex = i;
        }
    }
    printf("The best sold type with %d sales was", maxSales);
    printTypes(maxIndex);
    printf("\n");
}
void BestSellingBrandOverall(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int totalDays) {
    int maxIndex = 0; //checking place with the biggest counter
    int current[NUM_OF_BRANDS] = {0};//buffer array for brands sales
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        for (int j = 0; j < totalDays; j++) {
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                current[i] += cube[j][i][k];
            }
        }
    }
    int maxSales = current[0];
    for (int i = 1; i < NUM_OF_BRANDS; i++) {
        if (maxSales < current[i]) {
            maxSales = current[i];
            maxIndex = i;
        }
    }
    printf("The best-selling brand overall is");
    printBrands(maxIndex);
    printf(": %d$\n", maxSales);
}
void BestSellingTypeOverall(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int totalDays) {
    int current[NUM_OF_TYPES] = {0};//buffer for checking types
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        for (int j = 0; j < totalDays; j++) {
            for (int k = 0; k < NUM_OF_BRANDS; k++) {
                current[i] += cube[j][k][i];
            }
        }
    }
    int typeSales = current[0];
    int maxIndex = 0; // returning place with the biggest counter
    for (int i = 1; i < NUM_OF_TYPES; i++) {
        if (current[i] > typeSales) {
            typeSales = current[i];
            maxIndex = i;
        }
    }
    printf("The best-selling type of car is");
    printTypes(maxIndex);
    printf(": %d$\n", typeSales);
}
void MostProfitableDay(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int totalDay) {
    int current[DAYS_IN_YEAR] = {0}; //buffer array for storing daily sum
    for (int i = 0; i < totalDay; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                current[i] += cube[i][j][k];
            }
        }
    }
    int dailySales = current[0];
    int maxIndex = 0; // checking the highest place
    for (int i = 1; i < totalDay; i++) {
        if (current[i] > dailySales) {
            dailySales = current[i];
            maxIndex = i;
        }
    }
    printf("The most profitable day was day number %d: %d$\n", maxIndex + 1, dailySales); //+1 because in array the days start with 0 and client needs the day that start with 1
}
void CalculateDelta(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int totalDays) {
    float delta[NUM_OF_BRANDS] = {0};
    int counter[DAYS_IN_YEAR][NUM_OF_BRANDS] = {0};
    for (int i = 0; i < totalDays; i++) {
        for (int j = 0; j < NUM_OF_TYPES; j++) {
            for (int k = 0; k < NUM_OF_BRANDS; k++) {
                counter[i][k] += cube[i][k][j];
            }
        }
    }
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        if (totalDays > 0) {
            delta[i] = (float)(counter[totalDays - 1][i] - counter[0][i])/(float)(totalDays - 1);//according to math equations the average delta can be counted just by subsraction of last day of sales and first day
            printf("Brand:");
            printBrands(i);
            printf(", Average Delta: %f\n", delta[i]);
        }
        else {
            printf("Brand:");
            printBrands(i);
            printf(", Average Delta: -nan\n");
        }
    }
}
void PrintCube(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int totalDay) {
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        printf("Sales for");
        printBrands(i);
        printf(":\n");
        for (int j = 0; j < totalDay; j++) {
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
}
int AddDataToCube(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int totalDay) {
    int dailySum[NUM_OF_TYPES];
    int index = 0;
    int check = 0;
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        while (check < NUM_OF_BRANDS) {
            printf("No data for brands");
            for (int j = 0; j < NUM_OF_BRANDS; j++) {
                if (cube[totalDay][j][i] == -1)
                    printBrands(j);

            }
            printf("\nPlease complete the data \n");
            scanf("%d", &index);
            if (index < 0 || index >= NUM_OF_BRANDS || cube[totalDay][index][i] != -1) {
                printf("This brand is not valid\n");
                continue;
            }
            for (int j = 0; j < NUM_OF_TYPES; j++) {
                scanf("%d", &dailySum[j]);
            }
            DailyData(index, dailySum, NUM_OF_TYPES, cube);
            check++; //checking if there is 4 iterations as in 4 brands
        }
    }
    return totalDay + 1; //returning how many days in array are filled with data
}
void AddOneBrand(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    int dailySum[NUM_OF_BRANDS] = {0};
    int index = 0;
    printf("Add data sales for brand: \n");
    scanf("%d", &index);
    while (index < 0 || index > NUM_OF_TYPES) {
        printf("This brand is not valid\n");
        scanf("%d", &index);
    }
    printf("Add sales:\n");
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        scanf("%d", &dailySum[i]);
    }
    DailyData(index, dailySum, NUM_OF_TYPES, cube);
}



int main() {
    int choice, day = 0;
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    InitArray(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES);
    printMenu();
    scanf("%d", &choice);
    while(choice != done) {
        switch(choice){
            case addOne: {
                AddOneBrand(cube);
                break;
            }
            case addAll: {
                day = AddDataToCube(cube, day); //adding day to the array
                break;
            }
            case stats: {
                int UserInputDay = InputDayValidation(day);
                printf("In day number %d: \n", UserInputDay);
                UserInputDay--;     //user enters day by one bigger than actually there are in array because array starts with 0
                int totalSales = TotalSumOfSales(cube, UserInputDay);
                printf("The sales total was %d\n", totalSales);
                BestSellingBrand(cube, UserInputDay);
                BestSellingType(cube, UserInputDay);
                break;
            }
            case print: {
                printf("*****************************************\n\n");
                PrintCube(cube, day);
                printf("\n*****************************************\n");
                break;
            }
            case insights: {
                BestSellingBrandOverall(cube, day);
                BestSellingTypeOverall(cube, day);
                MostProfitableDay(cube, day);
                break;
            }
            case deltas: {
                CalculateDelta(cube, day);
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


