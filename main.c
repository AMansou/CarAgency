#include "functions.h"
int main()
{
    strcpy(orderFileName,"orders.txt");
    strcpy(logFileName,"lastSold.txt");
    strcpy(carFileName,"cars.txt");
    loadAllCars(carFileName);
    loadAllOrders(orderFileName);
    loadAllLastSold(logFileName);
    menuScreen();

    return 0;
}
