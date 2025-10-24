#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define MAX_NAME_LENGTH 50

char cities[MAX_CITIES][MAX_NAME_LENGTH];
int cityCount = 0;

int distances[MAX_CITIES][MAX_CITIES];

char vehicleTypes[3][20] = {"Van", "Truck", "Lorry"};
int vehicleCapacity[3] = {1000, 5000, 10000};
int vehicleRatePerKm[3] = {30, 40, 80};
int vehicleAvgSpeed[3] = {60, 50, 45};
int vehicleFuelEfficiency[3] = {12, 6, 4};

void mainMenu();
void cityManagement();
void addCity();
void removeCity();
void renameCity();
void displayCities();
void distanceManagement();
void inputDistance();
void displayDistanceMatrix();
void vehicleManagement();
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
        getchar();

        switch(choice)
        {
        case 1:
            cityManagement();
            break;
        case 2:
            distanceManagement();
            break;
        case 3:
            vehicleManagement();
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

void cityManagement()
{
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
    getchar();

    switch(choice)
    {
    case 1:
        addCity();
        break;
    case 2:
        removeCity();
        break;
    case 3:
        renameCity();
        break;
    case 4:
        displayCities();
        break;
    case 5:
        break;
    default:
        printf("\nInvalid choice!\n");
    }
}

void addCity()
{
    char newCity[MAX_NAME_LENGTH];

    if(cityCount >= MAX_CITIES)
    {
        printf("\nMaximum city limit reached!\n");
        return;
    }

    printf("\nEnter city name: ");
    fgets(newCity, MAX_NAME_LENGTH, stdin);
    newCity[strcspn(newCity, "\n")] = 0;

    for(int i = 0; i < cityCount; i++)
    {
        if(strcasecmp(cities[i], newCity) == 0)
        {
            printf("\nCity already exists!\n");
            return;
        }
    }

    strcpy(cities[cityCount], newCity);
    cityCount++;
    printf("\n'%s' added successfully!\n", newCity);
}

void removeCity()
{
    if(cityCount == 0)
    {
        printf("\nNo cities to remove!\n");
        return;
    }

    displayCities();
    printf("\nEnter city index to remove (0-%d): ", cityCount-1);
    int index;
    scanf("%d", &index);
    index -= 1;

    if(index < 0 || index >= cityCount)
    {
        printf("\nInvalid city index!\n");
        return;
    }

    printf("\nRemoving city '%s'...\n", cities[index]);

    for(int i = index; i < cityCount-1; i++)
    {
        strcpy(cities[i], cities[i+1]);
    }

    cityCount--;
    printf("\nCity removed successfully!\n");
}
void renameCity()
{
    if(cityCount == 0)
    {
        printf("\nNo cities to rename!\n");
        return;
    }

    displayCities();
    printf("\nEnter city index to rename (0-%d): ", cityCount);
    int index;
    scanf("%d", &index);
    getchar();

    if(index < 0 || index >= cityCount)
    {
        printf("\nInvalid city index!\n");
        return;
    }

    char newName[MAX_NAME_LENGTH];
    printf("Enter new name for '%s': ", cities[index]);
    fgets(newName, MAX_NAME_LENGTH, stdin);
    newName[strcspn(newName, "\n")] = 0;

    for(int i = 0; i < cityCount; i++)
    {
        if(i != index && strcasecmp(cities[i], newName) == 0)
        {
            printf("\nCity name already exists!\n");
            return;
        }
    }

    strcpy(cities[index], newName);
    printf("\nCity renamed successfully!\n");
}

void displayCities()
{
    if(cityCount == 0)
    {
        printf("\nNo cities added yet!\n");
        return;
    }

    printf("\n========================================\n");
    printf("          LIST OF CITIES\n");
    printf("========================================\n");
    for(int i = 0; i < cityCount; i++)
    {
        printf("%2d. %s\n", i+1, cities[i]);
    }
    printf("========================================\n");
}

void distanceManagement()
{
    int choice;
    printf("\n");
    printf("========================================\n");
    printf("      DISTANCE MANAGEMENT\n");
    printf("========================================\n");
    printf("1. Input/Edit Distance\n");
    printf("2. Display Distance Table\n");
    printf("3. Back to Main Menu\n");
    printf("========================================\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
    case 1:
        inputDistance();
        break;
    case 2:
        displayDistanceMatrix();
        break;
    case 3:
        break;
    default:
        printf("\nInvalid choice!\n");
    }
}

void inputDistance()
{
    if(cityCount < 2)
    {
        printf("\nNeed at least 2 cities to set distances!\n");
        return;
    }

    displayCities();

    int city1, city2, dist;
    printf("\nEnter first city index: ");
    scanf("%d", &city1);
    printf("Enter second city index: ");
    scanf("%d", &city2);

    if(city1 < 0 || city1 >= cityCount || city2 < 0 || city2 >= cityCount)
    {
        printf("\nInvalid city index!\n");
        return;
    }

    if(city1 == city2)
    {
        printf("\nCannot set distance from a city to itself!\n");
        return;
    }

    printf("Enter distance (km): ");
    scanf("%d", &dist);

    if(dist < 0)
    {
        printf("\nDistance cannot be negative!\n");
        return;
    }

    distances[city1][city2] = dist;
    distances[city2][city1] = dist;

    printf("\nDistance between '%s' and '%s' set to %d km\n",
           cities[city1], cities[city2], dist);
}

void displayDistanceMatrix()
{
    if(cityCount == 0)
    {
        printf("\nNo cities added yet!\n");
        return;
    }

    printf("\n========================================\n");
    printf("        DISTANCE TABLE (km)\n");
    printf("========================================\n");

    printf("%-15s", "");
    for(int i = 0; i < cityCount; i++)
    {
        printf("%-8s", cities[i]);
    }
    printf("\n");

    for(int i = 0; i < cityCount; i++)
    {
        printf("%-15s", cities[i]);
        for(int j = 0; j < cityCount; j++)
        {
            printf("%-8d", distances[i][j]);
        }
        printf("\n");
    }
    printf("========================================\n");
}

void vehicleManagement()
{
    printf("\n========================================\n");
    printf("      VEHICLE INFORMATION\n");
    printf("========================================\n");
    printf("%-5s %-10s %-12s %-12s %-12s %-15s\n",
           "No.", "Type", "Capacity", "Rate/km", "Speed", "Fuel Eff.");
    printf("%-5s %-10s %-12s %-12s %-12s %-15s\n",
           "", "", "(kg)", "(LKR)", "(km/h)", "(km/l)");
    printf("----------------------------------------\n");

    for(int i = 0; i < 3; i++)
    {
        printf("%-5d %-10s %-12d %-12d %-12d %-15d\n",
               i+1, vehicleTypes[i], vehicleCapacity[i],
               vehicleRatePerKm[i], vehicleAvgSpeed[i],
               vehicleFuelEfficiency[i]);
    }
    printf("========================================\n");
}
