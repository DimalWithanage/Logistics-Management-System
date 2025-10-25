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

void initializeSystem();
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
void performanceReports();
void saveToFile();
void loadFromFile();

int main()
{
    initializeSystem();
    loadFromFile();

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
            performanceReports();
            break;
        case 6:
            saveToFile();
            printf("\nData saved successfully!\n");
            break;
        case 7:
            saveToFile();
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

void initializeSystem()
{
    for(int i = 0; i < MAX_CITIES; i++)
    {
        for(int j = 0; j < MAX_CITIES; j++)
        {
            distances[i][j] = 0;
        }
    }

    for(int i = 0; i < MAX_CITIES; i++)
    {
        strcpy(cities[i], "");
    }
}

void mainMenu()
{
    system("cls");
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
    do
    {
        system("cls");
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
        if(choice != 5)
        {
            printf("\nPress Enter to continue...");
            getchar();
        }
    }
    while(choice != 5);
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
    printf("\nEnter city index to remove (1-%d): ", cityCount);
    int index;
    scanf("%d", &index);
    getchar();
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

    for(int i = index; i < cityCount-1; i++)
    {
        for(int j = 0; j < cityCount; j++)
        {
            distances[i][j] = distances[i+1][j];
        }
    }
    for(int i = 0; i < cityCount; i++)
    {
        for(int j = index; j < cityCount-1; j++)
        {
            distances[i][j] = distances[i][j+1];
        }
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
    printf("\nEnter city index to rename (1-%d): ", cityCount);
    int index;
    scanf("%d", &index);
    getchar();
    index--;

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

    system("cls");
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
    do
    {
        system("cls");
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
        getchar();

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
        if(choice != 3)
        {
            printf("\nPress Enter to continue...");
            getchar();
        }
    }
    while(choice != 3);
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
    getchar();
    city1--;

    printf("Enter second city index: ");
    scanf("%d", &city2);
    getchar();
    city2--;

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
    getchar();

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

    system("cls");
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
    system("cls");
    printf("\n=================================================================\n");
    printf("                      VEHICLE INFORMATION\n");
    printf("=================================================================\n");
    printf("%-5s %-10s %-12s %-12s %-12s %-15s\n",
           "No.", "Type", "Capacity", "Rate/km", "Speed", "Fuel Eff.");
    printf("%-5s %-10s %-12s %-12s %-12s %-15s\n",
           "", "", "(kg)", "(LKR)", "(km/h)", "(km/l)");
    printf("-----------------------------------------------------------------\n");

    for(int i = 0; i < 3; i++)
    {
        printf("%-5d %-10s %-12d %-12d %-12d %-15d\n",
               i+1, vehicleTypes[i], vehicleCapacity[i],
               vehicleRatePerKm[i], vehicleAvgSpeed[i],
               vehicleFuelEfficiency[i]);
    }
    printf("=================================================================\n");
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
    source--;
    getchar();

    printf("Enter destination city index: ");
    scanf("%d", &dest);
    dest--;
    getchar();

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
    getchar();

    printf("\nSelect vehicle type:\n");
    for(int i = 0; i < 3; i++)
    {
        printf("%d. %s (Capacity: %d kg)\n", i+1, vehicleTypes[i], vehicleCapacity[i]);
    }
    printf("Enter choice (1-3): ");
    scanf("%d", &vehicleType);
    getchar();

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
    int minDistance = 999999;
    int bestRoute[10];
    int bestRouteLength = 0;

    if(distances[source][dest] > 0)
    {
        minDistance = distances[source][dest];
        bestRoute[0] = source;
        bestRoute[1] = dest;
        bestRouteLength = 2;
    }

    int intermediateCities[MAX_CITIES];
    int intermediateCount = 0;

    for(int i = 0; i < cityCount; i++)
    {
        if(i != source && i != dest)
        {
            intermediateCities[intermediateCount++] = i;
        }
    }

    if(intermediateCount == 0)
    {
        if(minDistance < 999999)
        {
            calculateAndDisplayCost(source, dest, weight, vehicleType);
            return;
        }
        else
        {
            printf("\nNo route available between selected cities!\n");
            return;
        }
    }

    if(intermediateCount > 4)
    {
        intermediateCount = 4;
    }

    for(int i = 0; i < intermediateCount; i++)
    {
        int mid = intermediateCities[i];
        if(distances[source][mid] > 0 && distances[mid][dest] > 0)
        {
            int totalDist = distances[source][mid] + distances[mid][dest];
            if(totalDist < minDistance)
            {
                minDistance = totalDist;
                bestRoute[0] = source;
                bestRoute[1] = mid;
                bestRoute[2] = dest;
                bestRouteLength = 3;
            }
        }
    }

    if(intermediateCount >= 2)
    {
        for(int i = 0; i < intermediateCount; i++)
        {
            for(int j = 0; j < intermediateCount; j++)
            {
                if(i != j)
                {
                    int mid1 = intermediateCities[i];
                    int mid2 = intermediateCities[j];
                    if(distances[source][mid1] > 0 &&
                            distances[mid1][mid2] > 0 &&
                            distances[mid2][dest] > 0)
                    {
                        int totalDist = distances[source][mid1] +
                                        distances[mid1][mid2] +
                                        distances[mid2][dest];
                        if(totalDist < minDistance)
                        {
                            minDistance = totalDist;
                            bestRoute[0] = source;
                            bestRoute[1] = mid1;
                            bestRoute[2] = mid2;
                            bestRoute[3] = dest;
                            bestRouteLength = 4;
                        }
                    }
                }
            }
        }
    }

    if(intermediateCount >= 3)
    {
        for(int i = 0; i < intermediateCount; i++)
        {
            for(int j = 0; j < intermediateCount; j++)
            {
                for(int k = 0; k < intermediateCount; k++)
                {
                    if(i != j && j != k && i != k)
                    {
                        int mid1 = intermediateCities[i];
                        int mid2 = intermediateCities[j];
                        int mid3 = intermediateCities[k];
                        if(distances[source][mid1] > 0 &&
                                distances[mid1][mid2] > 0 &&
                                distances[mid2][mid3] > 0 &&
                                distances[mid3][dest] > 0)
                        {
                            int totalDist = distances[source][mid1] +
                                            distances[mid1][mid2] +
                                            distances[mid2][mid3] +
                                            distances[mid3][dest];
                            if(totalDist < minDistance)
                            {
                                minDistance = totalDist;
                                bestRoute[0] = source;
                                bestRoute[1] = mid1;
                                bestRoute[2] = mid2;
                                bestRoute[3] = mid3;
                                bestRoute[4] = dest;
                                bestRouteLength = 5;
                            }
                        }
                    }
                }
            }
        }
    }

    if(intermediateCount >= 4)
    {
        for(int i = 0; i < intermediateCount; i++)
        {
            for(int j = 0; j < intermediateCount; j++)
            {
                for(int k = 0; k < intermediateCount; k++)
                {
                    for(int m = 0; m < intermediateCount; m++)
                    {
                        if(i != j && i != k && i != m &&
                                j != k && j != m && k != m)
                        {
                            int mid1 = intermediateCities[i];
                            int mid2 = intermediateCities[j];
                            int mid3 = intermediateCities[k];
                            int mid4 = intermediateCities[m];
                            if(distances[source][mid1] > 0 &&
                                    distances[mid1][mid2] > 0 &&
                                    distances[mid2][mid3] > 0 &&
                                    distances[mid3][mid4] > 0 &&
                                    distances[mid4][dest] > 0)
                            {
                                int totalDist = distances[source][mid1] +
                                                distances[mid1][mid2] +
                                                distances[mid2][mid3] +
                                                distances[mid3][mid4] +
                                                distances[mid4][dest];
                                if(totalDist < minDistance)
                                {
                                    minDistance = totalDist;
                                    bestRoute[0] = source;
                                    bestRoute[1] = mid1;
                                    bestRoute[2] = mid2;
                                    bestRoute[3] = mid3;
                                    bestRoute[4] = mid4;
                                    bestRoute[5] = dest;
                                    bestRouteLength = 6;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if(minDistance == 999999)
    {
        printf("\nNo valid route found between selected cities!\n");
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
    printf("Base Cost: %d * %d * (1 + %d/10000) = %.2f LKR\n",
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

void calculateAndDisplayCost(int source, int dest, int weight, int vehicleType)
{
    int D = distances[source][dest];
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
    printf("Minimum Distance: %d km\n", D);
    printf("Vehicle: %s\n", vehicleTypes[vehicleType]);
    printf("Weight: %d kg\n", W);
    printf("------------------------------------------------------\n");
    printf("Base Cost: %d * %d * (1 + %d/10000) = %.2f LKR\n",
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

void performanceReports()
{
    if(deliveryCount == 0)
    {
        printf("\nNo deliveries completed yet!\n");
        return;
    }

    int totalDistance = 0;
    float totalTime = 0;
    float totalRevenue = 0;
    float totalProfit = 0;
    int longestRoute = 0;
    int shortestRoute = 999999;

    for(int i = 0; i < deliveryCount; i++)
    {
        totalDistance += deliveryDistance[i];
        totalTime += deliveryEstimatedTime[i];
        totalRevenue += deliveryCustomerCharge[i];
        totalProfit += deliveryProfit[i];

        if(deliveryDistance[i] > longestRoute)
        {
            longestRoute = deliveryDistance[i];
        }
        if(deliveryDistance[i] < shortestRoute)
        {
            shortestRoute = deliveryDistance[i];
        }
    }

    float avgTime = totalTime / deliveryCount;

    printf("\n======================================================\n");
    printf("           PERFORMANCE REPORT\n");
    printf("======================================================\n");
    printf("Total Deliveries Completed: %d\n", deliveryCount);
    printf("Total Distance Covered: %d km\n", totalDistance);
    printf("Average Delivery Time: %.2f hours\n", avgTime);
    printf("Total Revenue: %.2f LKR\n", totalRevenue);
    printf("Total Profit: %.2f LKR\n", totalProfit);
    printf("Longest Route: %d km\n", longestRoute);
    printf("Shortest Route: %d km\n", shortestRoute);
    printf("======================================================\n");
}

void saveToFile()
{
    FILE* routesFile = fopen("routes.txt", "w");
    if(routesFile != NULL)
    {
        fprintf(routesFile, "%d\n", cityCount);
        for(int i = 0; i < cityCount; i++)
        {
            fprintf(routesFile, "%s\n", cities[i]);
        }

        for(int i = 0; i < cityCount; i++)
        {
            for(int j = 0; j < cityCount; j++)
            {
                fprintf(routesFile, "%d ", distances[i][j]);
            }
            fprintf(routesFile, "\n");
        }
        fclose(routesFile);
    }

    FILE* deliveriesFile = fopen("deliveries.txt", "w");
    if(deliveriesFile != NULL)
    {
        fprintf(deliveriesFile, "%d\n", deliveryCount);
        for(int i = 0; i < deliveryCount; i++)
        {
            fprintf(deliveriesFile, "%s|%s|%d|%d|%d|%.2f|%.2f|%.2f|%.2f|%.2f|%.2f\n",
                    deliverySource[i], deliveryDest[i],
                    deliveryDistance[i], deliveryWeight[i],
                    deliveryVehicleType[i], deliveryBaseCost[i],
                    deliveryFuelCost[i], deliveryTotalCost[i],
                    deliveryProfit[i], deliveryCustomerCharge[i],
                    deliveryEstimatedTime[i]);
        }
        fclose(deliveriesFile);
    }
}

void loadFromFile()
{
    FILE* routesFile = fopen("routes.txt", "r");
    if(routesFile != NULL)
    {
        fscanf(routesFile, "%d\n", &cityCount);
        for(int i = 0; i < cityCount; i++)
        {
            fgets(cities[i], MAX_NAME_LENGTH, routesFile);
            cities[i][strcspn(cities[i], "\n")] = 0;
        }

        for(int i = 0; i < cityCount; i++)
        {
            for(int j = 0; j < cityCount; j++)
            {
                fscanf(routesFile, "%d", &distances[i][j]);
            }
        }
        fclose(routesFile);
        printf("Routes data loaded successfully!\n");
    }

    FILE* deliveriesFile = fopen("deliveries.txt", "r");
    if(deliveriesFile != NULL)
    {
        fscanf(deliveriesFile, "%d\n", &deliveryCount);
        for(int i = 0; i < deliveryCount; i++)
        {
            fscanf(deliveriesFile, "%[^|]|%[^|]|%d|%d|%d|%f|%f|%f|%f|%f|%f\n",
                   deliverySource[i], deliveryDest[i],
                   &deliveryDistance[i], &deliveryWeight[i],
                   &deliveryVehicleType[i], &deliveryBaseCost[i],
                   &deliveryFuelCost[i], &deliveryTotalCost[i],
                   &deliveryProfit[i], &deliveryCustomerCharge[i],
                   &deliveryEstimatedTime[i]);
        }
        fclose(deliveriesFile);
        printf("Delivery data loaded successfully!\n");
    }
}
