#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define MAX_NAME_LENGTH 50
#define MAX_DELIVERIES 50
#define FUEL_PRICE 310.0

char cities[MAX_CITIES][MAX_NAME_LENGTH];
int cityCount = 0;

int distances[MAX_CITIES][MAX_CITIES];

char vehicleTypes[3][20] = {"Van", "Truck", "Lorry"};
int vehicleCapacity[3] = {1000, 5000, 10000};
int vehicleRatePerKm[3] = {30, 40, 80};
int vehicleAvgSpeed[3] = {60, 50, 45};
int vehicleFuelEfficiency[3] = {12, 6, 4};

char deliverySource[MAX_DELIVERIES][MAX_NAME_LENGTH];
char deliveryDest[MAX_DELIVERIES][MAX_NAME_LENGTH];
int deliveryDistance[MAX_DELIVERIES];
int deliveryWeight[MAX_DELIVERIES];
int deliveryVehicleType[MAX_DELIVERIES]; // 0=Van, 1=Truck, 2=Lorry
float deliveryBaseCost[MAX_DELIVERIES];
float deliveryFuelCost[MAX_DELIVERIES];
float deliveryTotalCost[MAX_DELIVERIES];
float deliveryProfit[MAX_DELIVERIES];
float deliveryCustomerCharge[MAX_DELIVERIES];
float deliveryEstimatedTime[MAX_DELIVERIES];
int deliveryCount = 0;

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
void deliveryRequestHandling();
void calculateAndDisplayCost(int source, int dest, int weight, int vehicleType);
void findLeastCostRoute(int source, int dest, int weight, int vehicleType);
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
            deliveryRequestHandling();
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
    index--;

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

void deliveryRequestHandling()
{
    if(cityCount < 2)
    {
        printf("\nNeed at least 2 cities for delivery!\n");
        return;
    }

    displayCities();

    int source, dest, weight, vehicleType;

    printf("\nEnter source city index: ");
    scanf("%d", &source);
    printf("Enter destination city index: ");
    scanf("%d", &dest);

    if(source < 0 || source >= cityCount || dest < 0 || dest >= cityCount)
    {
        printf("\nInvalid city index!\n");
        return;
    }

    if(source == dest)
    {
        printf("\nSource and destination cannot be the same!\n");
        return;
    }

    printf("Enter weight (kg): ");
    scanf("%d", &weight);

    printf("\nSelect vehicle type:\n");
    for(int i = 0; i < 3; i++)
    {
        printf("%d. %s (Capacity: %d kg)\n", i+1, vehicleTypes[i], vehicleCapacity[i]);
    }
    printf("Enter choice (1-3): ");
    scanf("%d", &vehicleType);

    if(vehicleType < 1 || vehicleType > 3)
    {
        printf("\nInvalid vehicle type!\n");
        return;
    }

    vehicleType--;
    if(weight > vehicleCapacity[vehicleType])
    {
        printf("\nWeight exceeds vehicle capacity!\n");
        return;
    }

    findLeastCostRoute(source, dest, weight, vehicleType);
}

void findLeastCostRoute(int source, int dest, int weight, int vehicleType)
{
    if(distances[source][dest] > 0)
    {
        calculateAndDisplayCost(source, dest, weight, vehicleType);
        return;
    }

    int intermediateCities[MAX_CITIES];
    int intermediateCount = 0;

    for(int i = 0; i < cityCount; i++)
    {
        if(i != source && i != dest)
        {
            if(distances[source][i] > 0 && distances[i][dest] > 0)
            {
                intermediateCities[intermediateCount++] = i;
            }
        }
    }

    if(intermediateCount == 0)
    {
        printf("\nNo route available between selected cities!\n");
        return;
    }

    if(intermediateCount > 4)
    {
        intermediateCount = 4;
    }

    int minDistance = 999999;
    int bestRoute[10];
    int bestRouteLength = 0;

    int permCount = factorial(intermediateCount);
    int allPerms[120][10]; // Max 5! = 120 permutations

    int count = 0;
    permute(intermediateCities, 0, intermediateCount - 1, allPerms, &count);

    for(int p = 0; p < permCount; p++)
    {
        int totalDist = 0;
        int valid = 1;

        totalDist += distances[source][allPerms[p][0]];

        for(int i = 0; i < intermediateCount - 1; i++)
        {
            if(distances[allPerms[p][i]][allPerms[p][i+1]] == 0)
            {
                valid = 0;
                break;
            }
            totalDist += distances[allPerms[p][i]][allPerms[p][i+1]];
        }

        totalDist += distances[allPerms[p][intermediateCount-1]][dest];

        if(valid && totalDist < minDistance)
        {
            minDistance = totalDist;
            bestRoute[0] = source;
            for(int i = 0; i < intermediateCount; i++)
            {
                bestRoute[i+1] = allPerms[p][i];
            }
            bestRoute[intermediateCount + 1] = dest;
            bestRouteLength = intermediateCount + 2;
        }
    }


    if(minDistance == 999999)
    {
        printf("\nNo valid route found!\n");
        return;
    }


    int D = minDistance;
    int W = weight;
    int R = vehicleRatePerKm[vehicleType];
    int S = vehicleAvgSpeed[vehicleType];
    int E = vehicleFuelEfficiency[vehicleType];
    float F = FUEL_PRICE;

    float baseCost = D * R * (1 + W * 1.0 / 10000);
    float fuelUsed = (float)D / E;
    float fuelCost = fuelUsed * F;
    float totalCost = baseCost + fuelCost;
    float profit = baseCost * 0.25;
    float customerCharge = totalCost + profit;
    float estimatedTime = (float)D / S;

    printf("\n======================================================\n");
    printf("           DELIVERY COST ESTIMATION\n");
    printf("------------------------------------------------------\n");
    printf("From: %s\n", cities[source]);
    printf("To: %s\n", cities[dest]);
    printf("Route: ");
    for(int i = 0; i < bestRouteLength; i++)
    {
        printf("%s", cities[bestRoute[i]]);
        if(i < bestRouteLength - 1) printf(" -> ");
    }
    printf("\n");
    printf("Minimum Distance: %d km\n", D);
    printf("Vehicle: %s\n", vehicleTypes[vehicleType]);
    printf("Weight: %d kg\n", W);
    printf("------------------------------------------------------\n");
    printf("Base Cost: %d × %d × (1 + %d/10000) = %.2f LKR\n",
           D, R, W, baseCost);
    printf("Fuel Used: %.2f L\n", fuelUsed);
    printf("Fuel Cost: %.2f LKR\n", fuelCost);
    printf("Operational Cost: %.2f LKR\n", totalCost);
    printf("Profit: %.2f LKR\n", profit);
    printf("Customer Charge: %.2f LKR\n", customerCharge);
    printf("Estimated Time: %.2f hours\n", estimatedTime);
    printf("======================================================\n");

    if(deliveryCount < MAX_DELIVERIES)
    {
        strcpy(deliverySource[deliveryCount], cities[source]);
        strcpy(deliveryDest[deliveryCount], cities[dest]);
        deliveryDistance[deliveryCount] = D;
        deliveryWeight[deliveryCount] = W;
        deliveryVehicleType[deliveryCount] = vehicleType;
        deliveryBaseCost[deliveryCount] = baseCost;
        deliveryFuelCost[deliveryCount] = fuelCost;
        deliveryTotalCost[deliveryCount] = totalCost;
        deliveryProfit[deliveryCount] = profit;
        deliveryCustomerCharge[deliveryCount] = customerCharge;
        deliveryEstimatedTime[deliveryCount] = estimatedTime;
        deliveryCount++;
    }
}
