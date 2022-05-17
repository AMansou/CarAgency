#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
/*************************************** file name strings*********************/
    char orderFileName [30];
    char logFileName [30];
    char carFileName [30];
/******************************************************************************/
typedef struct Car Car;
typedef struct Order Order;
typedef struct lastSold lastSold;
/*******************************prototypes********************************/
Car *carSearch(char manufacturer[],char model[],int year,char colour[]);
void InsertCarFirst(Car A);
int numberOfInputs(char fileName[30]);
void displayCarsLibrary();
void addCarFromUser();
void loadAllCars(char *fileName);
void loadCar(FILE *CarsFile);
Car *deleteCar(Car *pos);
int isEmptyCars();
Car *findPreviousCar(Car *pos);
void deleteALLCars();
void loadOrder(FILE *OrdersFile);
Order *dequeueOrder();
Order *dequeueunserved();
Order *dequeueTempQueue();
lastSold *popLastSold();
lastSold *popTempStack();


/*********************************STRUCTS****************************************/
struct Car
{
    char manufacturer [30];
    char model [30];
    int year;
    char colour [30];
    long price;
    int carID; // the number of cars of this kind that is available
    struct Car *next;
}*carsHead;
struct Order
{
    char manufacturer [30];
    char model [30];
    int year;
    char colour [30];
    char Name [30];
    long id;
    long PN;//phone number
    struct Order *nextt;
}*ordersHead; Order *ordersTail;
Order *tempQueueHead; Order *tempQueueTail;
struct lastSold
{
    int carID;
    char manufacturer [30];
    char model [30];
    int year;
    char colour [30];
    char Name [30];
    long id;
    long PN;//phone number
    char date [30];
    long price;
    struct lastSold *nextt;
};lastSold *lastSoldHead;
lastSold *tempStackHead;
struct Date
{
    int tm_mday;
    int tm_mon;
    int tm_year;
};
typedef struct Date Date;
/**********************************************************************/
int numberOfInputs(char fileName[30])//Takes number of inputs in a given file name
{
    FILE *File=fopen(fileName,"r");
    int i=0;
    char arr[300];
    int A=fgets(arr,300,File);
    while(A)
    {
        A=fgets(arr,300,File);
        i++;

    }
    return i;
}
/***************************cars Linked List**********************/
void loadCar(FILE *CarsFile)//inserts one student from file
{
    Car A;
    fscanf(CarsFile,"%[^,],",&A.manufacturer);
    fscanf(CarsFile,"%[^,],",&A.model);
    fscanf(CarsFile,"%d%*c",&A.year);
    fscanf(CarsFile,"%[^,],",&A.colour);
    fscanf(CarsFile,"%lld%*c",&A.price);
    fscanf(CarsFile,"%d%*c",&A.carID);
    InsertCarFirst(A);
}
void loadAllCars(char *fileName)//reads All Cars from file by using the function loadStudent (FILE *carsFile)
{
    int x=numberOfInputs(fileName);
    FILE *carsFile=fopen(fileName,"r");
    for(int i=0; i<x; i++)
    {
        loadCar(carsFile);
    }
    fclose(carsFile);

    return ;
}
void InsertCarFirst(Car A)
{
    if (carsHead==NULL)
    {
        carsHead=(Car*)malloc(sizeof(Car));
        if(carsHead!=NULL)
        {
            strcpy(carsHead->manufacturer,A.manufacturer);
            strcpy(carsHead->model,A.model);
            carsHead->year=A.year;
            strcpy(carsHead->colour,A.colour);
            carsHead->price=A.price;
            carsHead->carID=A.carID;
            carsHead->next=NULL;

        }
        else
            printf("The system is out of memory!\n");
    }
    else
    {
        Car *newCar= (Car*)malloc(sizeof(Car));
        if(newCar!=NULL)
        {
            strcpy(newCar->manufacturer,A.manufacturer);
            strcpy(newCar->model,A.model);
            newCar->year=A.year;
            strcpy(newCar->colour,A.colour);
            newCar->price=A.price;
            newCar->carID=A.carID;
            newCar->next=carsHead;
            carsHead=newCar;
        }
        else
            printf("The system is out of memory!\n");
    }
}
int isUniqueID(int ID)
{
    Car *tempCar=carsHead;
    while(tempCar!=NULL)
    {
        if(tempCar->carID==ID)
            return 0;
        tempCar=tempCar->next;
    }
    return 1;
}
void addCarFromUser()
{
    system("cls");
    printf("ADD CAR TO LIBRARY\n\n\n");
    Car A;
    int x; //FUCK c
    Car *tempCar;//used to know if there is a car of the same properties
    printf("Please enter car ID:\n");
    scanf(" %d",&A.carID);
    x=A.carID;
    if(!isUniqueID(A.carID))
        {
            printf("This car ID already exists! Please try again.\n");
            return;
        }
    printf("Please Enter the Manufacturer:\n");
    scanf(" %255[^\n]",A.manufacturer);
    printf("Please Enter the model:\n");
    scanf(" %255[^\n]",A.model);
    printf("Please Enter the year:\n");
    scanf(" %d",&A.year);
    printf("Please Enter the colour:\n");
    scanf(" %255[^\n]",A.colour);
    printf("Please Enter the price:\n");
    scanf(" %lld",&A.price);
    A.carID=x;
    InsertCarFirst(A);
    saveCars(carFileName);
}
void displayCarsLibrary()
{
    printf("DISPLAY CARS LIBRARY\n");
    Car *tempCar=carsHead;
    while (tempCar!=NULL)
    {
        printf("Manufacturer: %s, Model: %s, Year:%d, Colour: %s, Price: %ld, carID: %d\n",tempCar->manufacturer,tempCar->model,tempCar->year,tempCar->colour,tempCar->price,tempCar->carID);
        tempCar=tempCar->next;
    }
}
Car *carSearch(char manufacturer[],char model[],int year,char colour[])
{
    Car *tempCar=carsHead;
    while(tempCar!=NULL)
    {
        if(strcasecmp(tempCar->manufacturer,manufacturer)==0&&strcasecmp(tempCar->model,model)==0&&strcasecmp(tempCar->colour,colour)==0&&tempCar->year==year)
            return tempCar;
        tempCar=tempCar->next;
    }
    return NULL;
}
int isEmptyCars()
{
    return carsHead==NULL;
}
Car *deleteCar(Car *pos)
{
    Car *tempCar;
    Car *prev;
    if (pos==carsHead)
    {
        carsHead=carsHead->next;
        tempCar=(Car *)malloc(sizeof(Car));
        tempCar->next=NULL;
        tempCar->carID=0;
        strcpy(tempCar->model,pos->model);
        strcpy(tempCar->manufacturer,pos->manufacturer);
        tempCar->year=pos->year;
        strcpy(tempCar->colour,pos->colour);
        tempCar->price=pos->price;
        free(pos);
        return tempCar;

    }

    if(pos!=carsHead)
    {
        tempCar=(Car *)malloc(sizeof(Car));
        tempCar->next=NULL;
        tempCar->carID=0;
        strcpy(tempCar->model,pos->model);
        strcpy(tempCar->manufacturer,pos->manufacturer);
        tempCar->year=pos->year;
        strcpy(tempCar->colour,pos->colour);
        tempCar->price=pos->price;
        prev=findPreviousCar(pos);
        prev->next=pos->next;
        free(pos);
        return tempCar;

    }
    return NULL;
}
Car *findPreviousCar(Car *pos)
{
    Car *tempCar=carsHead;
    while(tempCar!=NULL)
    {
        if(tempCar->next==pos)
            return tempCar;
        tempCar=tempCar->next;
    }
    return NULL;
}
void deleteALLCars()
{
    Car *tempCar;
    while(carsHead!=NULL)
    {
        tempCar=carsHead;
        carsHead=carsHead->next;
        free(tempCar);
    }
}
void saveCars(char fileName [])
{
    FILE *carsFile=fopen(fileName,"w");
    Car *tempCar=carsHead;
    while (tempCar!=NULL)
    {
        fprintf(carsFile,"%s,%s,%d,%s,%ld,%d\n",tempCar->manufacturer,tempCar->model,tempCar->year,tempCar->colour,tempCar->price,tempCar->carID);
        tempCar=tempCar->next;
    }
    fclose(carsFile);
}
void modifyCar()
{
    printf("please enter the ID for the car you would like to modify:\n");
    int carID;
    long price;
    char colour [30];
    scanf(" %d",&carID);
    Car *tempCar=carsHead;
    while(tempCar!=NULL)
    {
        if(tempCar->carID==carID)
            break;
        tempCar=tempCar->next;
    }
    if(tempCar==NULL)
    {
        printf("This car ID does not exist!\n");
        return;
    }
    printf("Please enter the information:\nPrice: ");
    scanf(" %lld",&price);
    printf("\nColour: ");
    scanf(" %[^\n]",colour);
    strcpy(tempCar->colour,colour);
    tempCar->price=price;
    saveCars(carFileName);
    printf("Success!\n");
}
void deleteCarFromUser()
{
    printf("************************DELETE CAR*********************\n");/******************interface********//***********untested************/
    Car *tempCar=carsHead;
    int carID;
    printf("Please enter the cars ID number:\n");
    scanf(" %d",&carID);
    while(tempCar!=NULL)
    {
        if(tempCar->carID==carID)
            break;
        tempCar=tempCar->next;
    }
    if(tempCar==NULL)
    {
        printf("This car ID does not exist!\n");
        return;
    }
    deleteCar(tempCar);
    printf("Car successfully deleted!\n");
    saveCars(carFileName);
}
/************************Orders queue*************************/
void enqueueOrders(Order A)
{
    Order *newOrder;
    if (ordersHead==NULL)
    {
        ordersHead=(Order*)malloc(sizeof(Order));
        if(ordersHead!=NULL)
        {
            strcpy(ordersHead->Name,A.Name);
            strcpy(ordersHead->manufacturer,A.manufacturer);
            strcpy(ordersHead->model,A.model);
            strcpy(ordersHead->colour,A.colour);
            ordersHead->id=A.id;
            ordersHead->PN=A.PN;
            ordersHead->year=A.year;
            ordersHead->nextt=NULL;
            ordersTail=ordersHead;
            return;

        }
        else
            printf("The system is out of memory!\n");
    }
    else
    {
        newOrder= (Order*)malloc(sizeof(Order));
        if(newOrder!=NULL)
        {
            strcpy(newOrder->Name,A.Name);
            strcpy(newOrder->manufacturer,A.manufacturer);
            strcpy(newOrder->model,A.model);
            strcpy(newOrder->colour,A.colour);
            newOrder->id=A.id;
            newOrder->PN=A.PN;
            newOrder->year=A.year;
            newOrder->nextt=NULL;
            ordersTail->nextt=newOrder;
            ordersTail=newOrder;

        }
        else
            printf("The system is out of memory!\n");
    }
}
void loadOrder(FILE *OrdersFile)//inserts one student from file
{
    Order A;
    fscanf(OrdersFile,"%[^,],",A.Name);
    fscanf(OrdersFile,"%lld%*c",&A.id);
    fscanf(OrdersFile,"%lld%*c",&A.PN);
    fscanf(OrdersFile,"%[^,],",A.manufacturer);
    fscanf(OrdersFile,"%[^,],",A.model);
    fscanf(OrdersFile,"%[^,],",A.colour);
    fscanf(OrdersFile,"%d%*c",&A.year);
    enqueueOrders(A);
}
void loadAllOrders(char *fileName)//reads All Cars from file by using the function loadStudent (FILE *carsFile)
{
    int x=numberOfInputs(fileName);
    FILE *ordersFile=fopen(fileName,"r");
    for(int i=0; i<x; i++)
    {
        loadOrder(ordersFile);
    }
    fclose(ordersFile);

    return ;
}
void displayOrders()/*******interface*******/
{
    Order *tempOrder;
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~DISPLAY UNSERVED ORDERS~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    while(ordersHead!=NULL)
    {
        tempOrder=dequeueOrder();
        printf("~~~~~~~~~~~~~~~~~~~ORDER~~~~~~~~~~~~~~~~~~~~\n");
        printf("Name: %s | ID: %ld | Phone Number: %ld | Manufacturer: %s | Model: %s | Year: %d | Colour: %s\n",tempOrder->Name,tempOrder->id,tempOrder->PN,tempOrder->manufacturer,tempOrder->model,tempOrder->year,tempOrder->colour);
        enqueueTempQueue(tempOrder);
    }
    while(tempQueueHead!=NULL)
    {
        tempOrder=dequeueTempQueue();
        enqueueOrdersFromQueue(tempOrder);
    }

}
void saveOrders(char fileName [])
{
    FILE *ordersFile=fopen(fileName,"w");
    Order *tempOrder;
    while(ordersHead!=NULL)
    {
        tempOrder=dequeueOrder();
        fprintf(ordersFile,"%s,%ld,%ld,%s,%s,%s,%d\n",tempOrder->Name,tempOrder->id,tempOrder->PN,tempOrder->manufacturer,tempOrder->model,tempOrder->colour,tempOrder->year);
        enqueueTempQueue(tempOrder);
    }
    fclose(ordersFile);
    while(tempQueueHead!=NULL)
    {
        tempOrder=dequeueTempQueue();
        enqueueOrdersFromQueue(tempOrder);
    }
}
Order *dequeueOrder()
{
    Order *tempOrder=ordersHead;
    Order *returnOrder;
    if(ordersHead!=NULL)
    {
        ordersHead=ordersHead->nextt;
        returnOrder=(Order*)malloc(sizeof(Order));
        strcpy(returnOrder->Name,tempOrder->Name);
        strcpy(returnOrder->manufacturer,tempOrder->manufacturer);
        strcpy(returnOrder->model,tempOrder->model);
        strcpy(returnOrder->colour,tempOrder->colour);
        returnOrder->id=tempOrder->id;
        returnOrder->PN=tempOrder->PN;
        returnOrder->year=tempOrder->year;
        free(tempOrder);
        return returnOrder;
    }
    return NULL;
}
void enqueueOrdersFromQueue(Order *A)
{
    Order *newOrder;
    if (ordersHead==NULL)
    {
        ordersHead=A;
        ordersHead->nextt=NULL;
        ordersTail=ordersHead;
        return;
    }
    else
    {
        A->nextt=NULL;
        ordersTail->nextt=A;
        ordersTail=A;
    }
}
void addOrderFromUser()/********************interface***************/
{
    Order A;
    system("cls");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ADD NEW ORDER~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Please enter the customer's name:\n");
    scanf(" %[^\n]",A.Name);
    printf("Please enter the customer's ID number:\n");
    scanf("%lld",&A.id);
    printf("Please enter the customer's phone number:\n");
    scanf("%ld",&A.PN);
    printf("Please enter the Customer's order:\nManufacturer: ");
    scanf(" %[^\n]",A.manufacturer);
    printf("\nModel: ");
    scanf(" %[^\n]",A.model);
    printf("\nColour: ");
    scanf(" %[^\n]",A.colour);
    printf("\nYear: ");
    scanf(" %d",&A.year);
    printf("\n");
    enqueueOrders(A);
    saveOrders(orderFileName);
}
void modifyOrder()/********************interface*****************///untested
{
    Order *tempOrder, *tempOrder2;//the second one is to hold the order and add it to at the end of the queue
    long id;
    int flag=0;//to check if ID exists
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~MODIFY ORDER~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Please enter the ID number of the customer whose order you'd like to modify:\n");
    scanf(" %ld",&id);
    while(ordersHead!=NULL)
    {
        tempOrder=dequeueOrder();
        if(tempOrder->id==id)
        {
            flag=1;
            printf("Please enter the car's information\nManufacturer: ");
            scanf(" %[^\n]",tempOrder->manufacturer);
            printf("\nModel: ");
            scanf(" %[^\n]",tempOrder->model);
            printf("\nYear: ");
            scanf(" %d",&tempOrder->year);
            printf("\nColour: ");
            scanf(" %[^\n]", tempOrder->colour);
            printf("\n");
            tempOrder2=tempOrder;
            continue;
        }
        enqueueTempQueue(tempOrder);
    }
    while(tempQueueHead!=NULL)
    {
        tempOrder=dequeueTempQueue();
        enqueueOrdersFromQueue(tempOrder);
    }
    if(flag==0)
        {
            printf("This customer does not exist in this system!\n");
            return;
        }
    enqueueOrdersFromQueue(tempOrder2);//Add the modified order to the end of the queue
    saveOrders(orderFileName);
}
void deleteOrders()
{
    while(ordersHead!=NULL)
    {
        dequeueOrder();
    }
}
void deleteOrderFromUser()/********************interface***************//***************untested************/
{
    printf("************************DELETE ORDER***************************\n");
    Order *tempOrder;
    int flag=0;//has value 1 if an order was deleted, 0 otherwise
    long id;
    printf("Please enter the customer's ID:\n");
    scanf(" %ld",&id);
    while(ordersHead!=NULL)
    {
        tempOrder=dequeueOrder();
        if(tempOrder->id!=id)
        {
            enqueueTempQueue(tempOrder);
        }
        else
            flag=1;
    }
    while(tempQueueHead!=NULL)
    {
        tempOrder=dequeueTempQueue();
        enqueueOrdersFromQueue(tempOrder);
    }
    if(flag)
        printf("Order successfully deleted!\n");
    else
        printf("The ID entered does not exist!\n");
    saveOrders(orderFileName);

}
/***************************temporary queue************************/
void enqueueTempQueue(Order *A)
{
    Order *newOrder;
    if (tempQueueHead==NULL)
    {
        tempQueueHead=A;
        tempQueueHead->nextt=NULL;
        tempQueueTail=tempQueueHead;
        return;
    }
    else
    {
        A->nextt=NULL;
        tempQueueTail->nextt=A;
        tempQueueTail=A;
    }
}
Order *dequeueTempQueue()
{
    Order *tempOrder=tempQueueHead;
    Order *returnOrder;
    if(tempQueueHead!=NULL)
    {
        tempQueueHead=tempQueueHead->nextt;
        returnOrder=(Order*)malloc(sizeof(Order));
        strcpy(returnOrder->Name,tempOrder->Name);
        strcpy(returnOrder->manufacturer,tempOrder->manufacturer);
        strcpy(returnOrder->model,tempOrder->model);
        strcpy(returnOrder->colour,tempOrder->colour);
        returnOrder->id=tempOrder->id;
        returnOrder->PN=tempOrder->PN;
        returnOrder->year=tempOrder->year;
        free(tempOrder);
        return returnOrder;
    }
    return NULL;
}
/***************************Last sold stack*************************************/
void pushLastSold(lastSold A)
{
    lastSold *newLastSold;
    if (lastSoldHead==NULL)
    {
        lastSoldHead=(lastSold*)malloc(sizeof(lastSold));
        if(lastSoldHead!=NULL)
        {
            strcpy(lastSoldHead->Name,A.Name);
            strcpy(lastSoldHead->manufacturer,A.manufacturer);
            strcpy(lastSoldHead->model,A.model);
            strcpy(lastSoldHead->colour,A.colour);
            lastSoldHead->id=A.id;
            lastSoldHead->PN=A.PN;
            lastSoldHead->year=A.year;
            lastSoldHead->price=A.price;
            lastSoldHead->carID=A.carID;
            strcpy(lastSoldHead->date,A.date);
            lastSoldHead->nextt=NULL;

            return;

        }
        else
            printf("The system is out of memory!\n");
    }
    else
    {
        newLastSold= (lastSold*)malloc(sizeof(lastSold));
        if(newLastSold!=NULL)
        {
            strcpy(newLastSold->Name,A.Name);
            strcpy(newLastSold->manufacturer,A.manufacturer);
            strcpy(newLastSold->model,A.model);
            strcpy(newLastSold->colour,A.colour);
            newLastSold->id=A.id;
            newLastSold->PN=A.PN;
            newLastSold->year=A.year;
            newLastSold->price=A.price;
            newLastSold->carID=A.carID;
            strcpy(newLastSold->date,A.date);
            newLastSold->nextt=lastSoldHead;
            lastSoldHead=newLastSold;

        }
        else
            printf("The system is out of memory!\n");
    }
}
void loadLastSold(FILE *lastSoldFile)//inserts one student from file
{

    lastSold A;
    char B [30];
    fscanf(lastSoldFile, "%d%*c",&A.carID);
    fscanf(lastSoldFile,"%[^,],",A.Name);
    fscanf(lastSoldFile,"%lld%*c",&A.id);
    fscanf(lastSoldFile,"%lld%*c",&A.PN);
    fscanf(lastSoldFile,"%[^,],",A.manufacturer);
    fscanf(lastSoldFile,"%[^,],",A.model);
    fscanf(lastSoldFile,"%[^,],",A.colour);
    fscanf(lastSoldFile,"%d%*c",&A.year);
    fscanf(lastSoldFile,"%d%*c",&A.price);
    fscanf(lastSoldFile,"%[^\n]\n",A.date);

    pushLastSold(A);
}
void loadAllLastSold(char *fileName)//reads All Cars from file by using the function loadStudent (FILE *carsFile)
{
    int x=numberOfInputs(fileName);
    FILE *lastSoldFile=fopen(fileName,"r");
    for(int i=0; i<x; i++)
    {
        loadLastSold(lastSoldFile);
    }
    fclose(lastSoldFile);

    return ;
}
void pushLastSoldFromQueue(lastSold *A)
{
    if (lastSoldHead==NULL)
    {
        lastSoldHead=A;
        lastSoldHead->nextt=NULL;
        return;
    }
    else
    {
        A->nextt=lastSoldHead;
        lastSoldHead=A;
    }
}
lastSold *popLastSold()
{
    lastSold *tempLastSold=lastSoldHead;
    lastSold *returnLastSold;
    if(lastSoldHead!=NULL)
    {
        lastSoldHead=lastSoldHead->nextt;
        returnLastSold=(lastSold*)malloc(sizeof(lastSold));
        strcpy(returnLastSold->Name,tempLastSold->Name);
        strcpy(returnLastSold->manufacturer,tempLastSold->manufacturer);
        strcpy(returnLastSold->model,tempLastSold->model);
        strcpy(returnLastSold->colour,tempLastSold->colour);
        returnLastSold->id=tempLastSold->id;
        returnLastSold->PN=tempLastSold->PN;
        returnLastSold->year=tempLastSold->year;
        returnLastSold->price=tempLastSold->price;
        returnLastSold->carID=tempLastSold->carID;
        strcpy(returnLastSold->date,tempLastSold->date);
        free(tempLastSold);
        return returnLastSold;
    }
    return NULL;
}
void SaveLastSold(char fileName [])
{
    FILE *lastSoldFile=fopen(fileName,"w");
    lastSold *tempLastSold;
    while(lastSoldHead!=NULL)
    {
        tempLastSold=popLastSold();
        pushTempStack(tempLastSold);
    }
    while(tempStackHead!=NULL)
    {
        tempLastSold=popTempStack();
        fprintf(lastSoldFile,"%d,%s,%ld,%ld,%s,%s,%s,%d,%ld,%s\n",tempLastSold->carID,tempLastSold->Name,tempLastSold->id,tempLastSold->PN,tempLastSold->manufacturer,tempLastSold->model,tempLastSold->colour,tempLastSold->year,tempLastSold->price,tempLastSold->date);
        pushLastSoldFromQueue(tempLastSold);
    }
    fclose(lastSoldFile);
}
void displayLastSold()/*********************************interface****************************/
{
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~LAST CAR SOLD~~~~~~~~~~~~~~~~~~~~~~~~\n");
    if(lastSoldHead==NULL)
    {
        printf("Empty List!\n");
        return;
    }
    lastSold *tempLastSold;
    tempLastSold=popLastSold();
    if(tempLastSold!=NULL)
        {
            printf("Buyer: %s | Buyer's ID: %ld | Buyer's phone no: %ld | CarID: %d | Manufacturer: %s | Model: %s | Colour: %s | Year: %d | Price: %ld | date: %s\n",tempLastSold->Name,tempLastSold->id,tempLastSold->PN,tempLastSold->carID,tempLastSold->manufacturer,tempLastSold->model,tempLastSold->colour,tempLastSold->year,tempLastSold->price,tempLastSold->date);
            pushLastSoldFromQueue(tempLastSold);
        }
}
void testDisplay()
{
    lastSold *tempLastSold=lastSoldHead;
    while(tempLastSold!=NULL)
    {
        printf("Buyer: %s | Buyer's ID: %ld | Buyer's phone no: %ld | Manufacturer: %s | Model: %s | Colour: %s | Year: %d | Price: %ld | date: %s\n",tempLastSold->Name,tempLastSold->id,tempLastSold->PN,tempLastSold->manufacturer,tempLastSold->model,tempLastSold->colour,tempLastSold->year,tempLastSold->price,tempLastSold->date);
        tempLastSold=tempLastSold->nextt;
    }
}
void deleteLastSold()
{
    while(lastSoldHead!=NULL)
    {
        popLastSold();
    }
}
/**********************************Temp Stack******************************/
void pushTempStack(lastSold *A)
{
    if (tempStackHead==NULL)
    {
        tempStackHead=A;
        tempStackHead->nextt=NULL;
        return;
    }
    else
    {
        A->nextt=tempStackHead;
        tempStackHead=A;
    }
}
lastSold *popTempStack()
{
    lastSold *tempLastSold=tempStackHead;
    lastSold *returnLastSold;
    if(tempStackHead!=NULL)
    {
        tempStackHead=tempStackHead->nextt;
        returnLastSold=(lastSold*)malloc(sizeof(lastSold));
        strcpy(returnLastSold->Name,tempLastSold->Name);
        strcpy(returnLastSold->manufacturer,tempLastSold->manufacturer);
        strcpy(returnLastSold->model,tempLastSold->model);
        strcpy(returnLastSold->colour,tempLastSold->colour);
        returnLastSold->id=tempLastSold->id;
        returnLastSold->PN=tempLastSold->PN;
        returnLastSold->year=tempLastSold->year;
        returnLastSold->price=tempLastSold->price;
        returnLastSold->carID=tempLastSold->carID;
        strcpy(returnLastSold->date,tempLastSold->date);
        free(tempLastSold);
        return returnLastSold;
    }
    return NULL;
}
/*********************serve cars*****************************/
void serveCars()
{
    Date A;
    char B[30] ;
    Car *tempCar;
    Order *tempOrder;
    lastSold *tempLastSold;
    printf("*****************************SERVING ORDERS...***************************\n");
    if(carsHead==NULL)
    {
        printf("No cars in the system at the moment!\n");
        return;
    }
    if(ordersHead==NULL)
    {
        printf("There are no orders to serve at the moment!\n");
        return;
    }
    while(ordersHead!=NULL)
    {
        tempOrder=dequeueOrder();
        tempCar=carSearch(tempOrder->manufacturer,tempOrder->model,tempOrder->year,tempOrder->colour);
        if(tempCar!=NULL)
        {

            printf("Please enter the date sold for customer with the ID %ld:\nyear: ",tempOrder->id);
            scanf(" %d",&A.tm_year);
            printf("\nMonth: ");
            scanf(" %d",&A.tm_mon);
            printf("\nDay: ");
            scanf(" %d",&A.tm_mday);
            if(!isLegitDate(A))
            {
                printf("This is not a legit date. Please try again later.\n");
                printf("The customer with the ID: %ld was not served\n",tempOrder->id);
                enqueueTempQueue(tempOrder);
                continue;
            }
            tempLastSold=(lastSold *)malloc(sizeof(lastSold));
            /********************************************************/
            strcpy(tempLastSold->manufacturer,tempOrder->manufacturer);
            strcpy(tempLastSold->model,tempOrder->model);
            strcpy(tempLastSold->colour,tempOrder->colour);
            char year[30],month[30],day[30];
            itoa(A.tm_mday,day,10);
            itoa(A.tm_mon,month,10);
            itoa(A.tm_year,year,10);
            strcpy(tempLastSold->date,day);
            strcat(tempLastSold->date, "/");
            strcat(tempLastSold->date,month);
            strcat(tempLastSold->date,"/");
            strcat(tempLastSold->date,year);
            strcpy(tempLastSold->Name,tempOrder->Name);
            tempLastSold->id=tempOrder->id;
            tempLastSold->PN=tempOrder->PN;
            tempLastSold->price=tempCar->price;
            tempLastSold->year=tempOrder->year;
            tempLastSold->carID=tempCar->carID;
            /*******************************************************/
            pushLastSoldFromQueue(tempLastSold);
            deleteCar(tempCar);
            printf("The customer with the ID: %ld was served!\n",tempOrder->id);
        }
        else
        {
            printf("The customer with the ID: %ld was not served because the car is unavailable at the moment!\n",tempOrder->id);
            enqueueTempQueue(tempOrder);
        }
    }
    while(tempQueueHead!=NULL)
    {
        tempOrder=dequeueTempQueue();
        enqueueOrdersFromQueue(tempOrder);
    }
}
void loadEverything()
{
    printf("Warning: Any unsaved data will be lost after loading! press 'y' to continue, and anything else to abandon.\n");
    char y;
    scanf(" %c",&y);
    if(y=='y'||y=='Y')
    {
        printf("Please enter the files you want to load data from:\nCars: ");
        scanf(" %s",carFileName);
        printf("\nOrders: ");
        scanf(" %s",orderFileName);
        printf("\nList of sold cars: ");
        scanf(" %s",logFileName);
        printf("\n");
        deleteALLCars();
        deleteOrders();
        deleteLastSold();
        loadAllCars(carFileName);
        loadAllOrders(orderFileName);
        loadAllLastSold(logFileName);
    }
}
void EXITING()
{
    printf("Warning: Any unsaved data will be lost after exiting! press 'y' to continue, and anything else to abandon.\n");
    char y;
    scanf(" %c",&y);
    if(y=='y'|| y=='Y')
    {
        deleteALLCars();
        deleteOrders();
        deleteLastSold();
        free(logFileName);
        free(orderFileName);
        free(carFileName);
        system("cls");
        exit(0);
    }
    else
        return;
}
void saveEverything()
{
    saveCars(carFileName);
    saveOrders(orderFileName);
    SaveLastSold(logFileName);
}
void menuScreen()
{
    system("cls");
    char x;
    do
    {
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Please enter a choice~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        printf("1-LOAD                                            ****Load data**************************************\n\n");
        printf("2-INSERT                                          ****Insert a new car or order to the system********\n\n");
        printf("3-DELETE                                          ****Delete a certain car or order******************\n\n");
        printf("4-MODIFY                                          ****Modify a certain car or order in the system***\n\n");
        printf("5-SERVE ORDERS                                    ****Serve all orders for available cars************\n\n");
        printf("6-SAVE                                            ****Save data and update files*********************\n\n");
        printf("7-DISPLAY                                         ****Display cars, orders or the last sold car******\n\n");
        printf("8-EXIT                                            ****Exit from the system***************************\n\n");
        scanf(" %c",&x);
        switch (x)
        {
        case '1':
            system("cls");
            loadEverything();
            printf("Enter anything to continue\n");
            scanf(" %s");
            system("cls");
            break;
        case '2':
            system("cls");
            insertScreen();
            printf("Enter anything to continue\n");
            scanf(" %s");
            system("cls");
            break;
        case '3':
            system("cls");
            deleteScreen();
            printf("Enter anything to continue\n");
            scanf(" %s");
            system("cls");
            break;
        case '4':
            system("cls");
            modifyScreen();
            printf("Enter anything to continue\n");
            scanf(" %s");
            system("cls");
            break;
        case '5':
            system("cls");
            serveCars();
            printf("Enter anything to continue\n");
            scanf(" %s");
            system("cls");
            break;
        case '6':
            system("cls");
            saveEverything();
            printf("Enter anything to continue\n");
            scanf(" %s");
            system("cls");
            break;
        case '7':
            system("cls");
            displayscreen();
            printf("Enter anything to continue\n");
            scanf(" %s");
            system("cls");
            break;
        case '8':
            system("cls");
            EXITING();
            system("cls");
            break;
        default:
            system("cls");
            printf("Please enter a valid choice\n");
            printf("Enter anything to continue\n");
            scanf(" %s");
            system("cls");
            break;
        }
    }
    while(1);
}
void insertScreen()
{
    int x;
    system("cls");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Please choose an option:~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("1-INSERT CAR\n2-INSERT ORDER\n");
    scanf(" %d",&x);
    if(x==1)
        {
            system("cls");
            addCarFromUser();
        }
    else if(x==2)
        {
            system("cls");
            addOrderFromUser();
        }
}
void deleteScreen()
{
    int x;
    system("cls");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Please choose an option:~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("1-DELETE CAR\n2-DELETE ORDER\n");
    scanf(" %d",&x);
    if(x==1)

        {
            system("cls");
            deleteCarFromUser();
        }
    else if(x==2)
        {
            system("cls");
            deleteOrderFromUser();
        }
}
void displayscreen()
{
    int x;
    system("cls");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Please choose an option:~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("1-DISPLAY CARS\n2-DISPLAY ORDERS\n3-DISPLAY LAST SOLD CAR\n");
    scanf(" %d",&x);
    if(x==1)
        {
            system("cls");
            displayCarsLibrary();
        }
    else if(x==2)
        {
            system("cls");
            displayOrders();

        }
    else if(x==3)
        {
            system("cls");
            displayLastSold();
        }
}
void modifyScreen()
{
    int x;
    system("cls");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Please choose an option:~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("1-MODIFY CAR\n2-MODIFY ORDER\n");
    scanf(" %d",&x);
    if(x==1)
        {
            system("cls");
            modifyCar();
        }
    else if(x==2)
        {
            system("cls");
            modifyOrder();

        }

}
/****************************Date Handling functions*********************************/
Date dayAddition(Date date,int n)//adds n days to Date d
{
    int daysPerMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    Date d;
    d.tm_mday=date.tm_mday;
    d.tm_mon=date.tm_mon;
    d.tm_year=date.tm_year;
    for (int i=0; i<n; i++)
    {
        d.tm_mday++;
        if (d.tm_mday > daysPerMonth[d.tm_mon-1] || ( d.tm_mon==2 && d.tm_mday==29 && !isLeapYear(d.tm_year) ) )
        {
            d.tm_mday = 1;
            d.tm_mon++;
            if (d.tm_mon==13)
            {
                d.tm_mon = 1;
                d.tm_year++;
            }
        }
    }

    return d;
}

int isLeapYear(int year)
{
    if (year%400==0)
        return 1;
    if (year%100==0)
        return 0;
    return (year%4==0);
}
Date turnStringToDate(char dateString[])
{
    Date d;
    int cnt=0;
    char *tsu=strtok(dateString," ");
    while(tsu!=NULL)
    {
        cnt++;
        if(cnt==2)
        {
            if(strcasecmp(tsu,"jan")==0)
                d.tm_mon=1;
            else if(strcasecmp(tsu,"feb")==0)
                d.tm_mon=2;
            else if(strcasecmp(tsu,"mar")==0)
                d.tm_mon=3;
            else if(strcasecmp(tsu,"apr")==0)
                d.tm_mon=4;
            else if(strcasecmp(tsu,"may")==0)
                d.tm_mon=5;
            else if(strcasecmp(tsu,"jun")==0)
                d.tm_mon=6;
            else if(strcasecmp(tsu,"jul")==0)
                d.tm_mon=7;
            else if(strcasecmp(tsu,"aug")==0)
                d.tm_mon=8;
            else if(strcasecmp(tsu,"sept")==0)
                d.tm_mon=9;
            else if(strcasecmp(tsu,"oct")==0)
                d.tm_mon=10;
            else if(strcasecmp(tsu,"nov")==0)
                d.tm_mon=11;
            else if(strcasecmp(tsu,"dec")==0)
                d.tm_mon=12;
        }
        else if(cnt==3)
            d.tm_mday=atoi(tsu);
        else if(cnt==5)
            d.tm_year=atoi(tsu);
        tsu=strtok(NULL," ");
    }
    return d;
}
void isLegitDate(Date A)
{
    Date B;
    time_t t;
    time(&t);
    B=turnStringToDate(ctime(&t));
    for(int i=0;i<900;i++)
    {
        if(dayAddition(B,i).tm_mday==A.tm_mday&&dayAddition(B,i).tm_mon==A.tm_mon&&dayAddition(B,i).tm_year==A.tm_year)
        {
            return 1;
        }

    }
    printf(" \n");
    return 0;
}
