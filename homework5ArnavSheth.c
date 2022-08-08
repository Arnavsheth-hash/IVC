
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
struct person
{
    char name[20];
    float rate;
    float hours;
    float grossPay;
    float basePay;
    float overtime;
    float taxes;
    float netPay;
};
// Struct to empty a persons values
static const struct person EmptyStruct;
// Structure with people
struct person people[10];
// People currently inputted into the function
int peopleCount = 0;
int fileopened = 0;
char filename[20];
int main();
void mainMenu();
void calculatePay(int i);
bool fileloaded;
void loadFile(){
    for (int i = 0; i < peopleCount; i++){
        people[i] = EmptyStruct;
    }
    FILE* loadptr;
    printf("Enter Filename:\n");
    scanf("%s", filename);
    loadptr = fopen(filename, "r");
    if (loadptr == NULL){
        printf("Couldn't Read File\n");
        mainMenu();
    }
    fileloaded = true;
    char temp[10];
    fgets(temp, 10, loadptr);
    peopleCount = atoi(temp);
    for(int i = 0; i < peopleCount; i++){
        fgets(people[i].name, 20, loadptr);
        char ratetemp[100];
        fgets(ratetemp, 100, loadptr);
        people[i].rate = atof(ratetemp);
        char hourstemp[100];
        fgets(hourstemp, 100, loadptr);
        people[i].hours = atof(hourstemp);
        calculatePay(i);
    }
    fclose(loadptr);
    mainMenu();
}
void saveToFile(){
    FILE* fileptr;
    if (!fileloaded){
        printf("Enter Filename:\n");
        scanf("%s", filename);
    }
    printf("FILE SAVED\n");
    fileptr = fopen(filename, "w");
    fileopened = 1;
    fprintf(fileptr, "%d\n", peopleCount);
    for(int i = 0; i < peopleCount; i++){
        fprintf(fileptr,"%s\n%f\n%f\n", people[i].name, people[i].rate, people[i].hours);
    }
}
void getInfo(int i)
{
    // Gets info from option 1
    printf("\nEnter name: ");
    scanf("%s", people[i].name);
    int cmp = strcmp(people[i].name, "-1");
    if (cmp == 0)
    {
        people[i] = EmptyStruct;
        mainMenu();
    }

    printf("Enter hourly rate: ");
    scanf("%f", &people[i].rate);
    if (people[i].rate == -1)
    {
        people[i] = EmptyStruct;
        mainMenu();
    }

    printf("Enter hours worked: ");
    scanf("%f", &people[i].hours);
    if (people[i].hours == -1)
    {
        people[i] = EmptyStruct;
        mainMenu();
    }

    puts("\n");

    peopleCount++;
    calculatePay(i);
    mainMenu();
}
void editInfo(int i)
{
    // Edits info from option 2
    printf("\nEnter name: ");
    scanf("%s", people[i].name);
    int cmp = strcmp(people[i].name, "-1");
    if (cmp == 0)
    {
        people[i] = EmptyStruct;
        mainMenu();
    }

    printf("Enter hourly rate: ");
    scanf("%f", &people[i].rate);
    if (people[i].rate == -1)
    {
        people[i] = EmptyStruct;
        mainMenu();
    }

    printf("Enter hours worked: ");
    scanf("%f", &people[i].hours);
    if (people[i].hours == -1)
    {
        people[i] = EmptyStruct;
        mainMenu();
    }

    puts("\n");
    calculatePay(i);
    mainMenu();
}
int calculateTax(int grossPay)
{
    // Calculate Tax
    return grossPay * 0.2;
}
void calculatePay(int i)
{
    float totalPaidtoAll = 0;
    // Loop over every person
    for (int i = 0; i < peopleCount; i++)
    {
        // Checl for overtime
        if (people[i].hours > 40)
        {
            people[i].overtime = (people[i].hours - 40) * people[i].rate * 1.5;
            people[i].basePay = (40 * people[i].rate);
        }
        else
        {
            people[i].basePay = people[i].hours * people[i].rate;
            people[i].overtime = 0;
        }
        // Calculate gross pay
        people[i].grossPay = people[i].overtime + people[i].basePay;
        // Calculate Tax
        people[i].taxes = calculateTax(people[i].grossPay);
        // Calculate net pay
        people[i].netPay = people[i].grossPay - people[i].taxes;
    }
}
void printInfo(int i)
{
    // Print out the individual persons info
    printf("\nPay to: %s\n", people[i].name);
    printf("Hours worked: %.1f\n", people[i].hours);
    printf("Hourly rate: $ %.2f\n", people[i].rate);
    printf("Gross pay $%.2f\n", people[i].grossPay);
    printf("Overtime pay: $ %.2f\n", people[i].overtime);
    printf("Taxes paid $ %.2f\n", people[i].taxes);
    printf("Net pay: $ %.2f\n", people[i].netPay);
    puts("\n");
    mainMenu();
}
void printAllInfo()
{
    int tmp = strcmp(people[0].name, "");
    if (tmp == 0)
    {
        printf("\nNo Info\n\n");
        mainMenu();
    }
    for (int i = 0; i < peopleCount; i++)
    {
        // Print out the individual persons info
        printf("\nPay to: %s\n", people[i].name);
        printf("Hours worked: %.1f\n", people[i].hours);
        printf("Hourly rate: $ %.2f\n", people[i].rate);
        printf("Gross pay $%.2f\n", people[i].grossPay);
        printf("Overtime pay: $ %.2f\n", people[i].overtime);
        printf("Taxes paid $ %.2f\n", people[i].taxes);
        printf("Net pay: $ %.2f\n", people[i].netPay);
        puts("\n");
    }
    mainMenu();
}
int editPerson()
{
    int personChoice;
    do
    {
        for (int i = 0; i < peopleCount; i++)
        {
            // Print users names as choices
            printf("%d: %s\n", i + 1, people[i].name);
            scanf("%d", &personChoice);
        }
    } while (personChoice > peopleCount || personChoice <= 0);
    return personChoice - 1;
}
int query()
{
    int option;
    // Prints the main menu and returns the option
    printf("Main Menu\n");
    printf("1. Load From File\n");
    printf("2. Add Employee\n");
    printf("3. Edit Employee\n");
    printf("4. Print Employee\n");
    printf("5. Print All Employees\n");
    printf("6. Quit\n");
    scanf("%d", &option);
    return option;
}
void mainMenu(){
    // Switches through options on the menu
    int option = query();
    if (option == 1){
        loadFile();
    }
    if (option == 2)
    {
        getInfo(peopleCount);
    }
    if (option == 3)
    {
        int choice = editPerson();
        editInfo(choice);
    }
    if (option == 4)
    {
        int choice = editPerson();
        printInfo(choice);
    }
    if (option == 5)
    {
        printAllInfo();
    }
    if (option == 6){
        saveToFile();
    }
}
int main()
{
    mainMenu();
}
/*
SAMPLE OUTPUT
Main Menu
1. Add Employee
2. Edit Employee
3. Print Employee
4. Print all Employees
5. Quit

1

Enter Name: Arnav

Enter Hourly Rate: 4

Enter Hours Worked: 10

Main Menu
1. Add Employee
2. Edit Employee
3. Print Employee
4. Print all Employees
5. Quit

2

1. Arnav

1

Enter Name: Arnav

Enter Hourly Rate: 5

Enter Hours Worked: 10

Main Menu
1. Add Employee
2. Edit Employee
3. Print Employee
4. Print all Employees
5. Quit

3

1. Arnav

1

Pay to: Arnav
Hours worked: 10.0
Hourly rate: $ 4.00
Gross pay $40.00
Overtime pay: $ 0.00
Taxes paid $ 8.00
Net pay: $ 32.00

Main Menu
1. Add Employee
2. Edit Employee
3. Print Employee
4. Print all Employees
5. Quit

5
*/