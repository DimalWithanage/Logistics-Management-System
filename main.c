#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define MAX_NAME_LENGTH 50

char cities[MAX_CITIES][MAX_NAME_LENGTH];
int cityCount = 0;

int distances[MAX_CITIES][MAX_CITIES];

void mainMenu();
void cityManagement();
void addCity();
void removeCity();
//void renameCity();
void displayCities();
//void distanceManagement();
//void vehicleManagement();
//void deliveryRequestHandling();
//void saveToFile();
//void performanceReports();

int main()
{
    int choice;
    do
    {
        mainMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            cityManagement();
            break;
        case 2:
//            distanceManagement();
            break;
        case 3:
//            vehicleManagement();
            break;
        case 4:
//            deliveryRequestHandling();
            break;
        case 5:
//            performanceReports();
            break;
        case 6:
//            saveToFile();
            printf("\nData saved successfully!\n");
            break;
        case 7:
//            saveToFile();
            printf("\nThank you for using the Logistics Management System!\n");
            break;
        default:
            printf("\nInvalid choice! Please try again.\n");
        }

        if(choice != 7)
        {
            printf("\nPress Enter to continue...");
            getchar();
        }

    }
    while(choice != 7);

    return 0;
}

void mainMenu()
{
    printf("\n");
    printf("========================================\n");
    printf("   LOGISTICS MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("1. City Management\n");
    printf("2. Distance Management\n");
    printf("3. View Vehicle Information\n");
    printf("4. Delivery Request\n");
    printf("5. Performance Reports\n");
    printf("6. Save Data\n");
    printf("7. Exit\n");
    printf("========================================\n");
}

void cityManagement() {
    int choice;
    printf("\n");
    printf("========================================\n");
    printf("        CITY MANAGEMENT\n");
    printf("========================================\n");
    printf("1. Add City\n");
    printf("2. Remove City\n");
    printf("3. Rename City\n");
    printf("4. Display All Cities\n");
    printf("5. Back to Main Menu\n");
    printf("========================================\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            addCity();
            break;
        case 2:
            removeCity();
            break;
        case 3:
//            renameCity();
            break;
        case 4:
//            displayCities();
            break;
        case 5:
            break;
        default:
            printf("\nInvalid choice!\n");
    }
}

void addCity() {
    char newCity[MAX_NAME_LENGTH];

    if(cityCount >= MAX_CITIES) {
        printf("\nMaximum city limit reached!\n");
        return;
    }

    printf("\nEnter city name: ");
    fgets(newCity, MAX_NAME_LENGTH, stdin);
    newCity[strcspn(newCity, "\n")] = 0;

    for(int i = 0; i < cityCount; i++) {
        if(strcasecmp(cities[i], newCity) == 0) {
            printf("\nCity already exists!\n");
            return;
        }
    }

    strcpy(cities[cityCount], newCity);
    cityCount++;
    printf("\n'%s' added successfully!\n", newCity);
}

void removeCity() {
    if(cityCount == 0) {
        printf("\nNo cities to remove!\n");
        return;
    }

    displayCities();
    printf("\nEnter city index to remove (0-%d): ", cityCount-1);
    int index;
    scanf("%d", &index);

    if(index < 0 || index >= cityCount) {
        printf("\nInvalid city index!\n");
        return;
    }

    printf("\nRemoving city '%s'...\n", cities[index]);

    for(int i = index; i < cityCount-1; i++) {
        strcpy(cities[i], cities[i+1]);
    }

    cityCount--;
    printf("\nCity removed successfully!\n");
}

