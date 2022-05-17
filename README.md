# CarAgency
The car agency system has the following main requirements: 1) There are many kinds of cars in the car agency’s inventory (at least fifteen cars). They may have more than one car from each kind. 2) The customers are organized as a Queue. 3) Retrieve data of the last sold car.
The program consists of the following specification:
  1) library implementing a linked list including the following functions:
    a) Insert
    b) InsertFirst
    c) InsertLast
    d) DeleteAtSpecificValue
    e) DeleteFirst
    f) DeleteLast
    g) Find
    h) Update
  2) A library implementing a stack and has the following functions:
    a. Push
    b. Pop
    c. Top
  3) A library implementing a queue and has the following functions:
    a) Enqueue
    b) Dequeue
    c) Front
 The program flow is as follows:
1. Load cars and orders. This command will load the list of cars from a file
(cars.dat). The information of cars include: Manufacturer, Model, Year,
Colour, and price. The data of cars will be loaded into a linked list. It will
also load the Customer orders, which will be served in a queue. These orders
are loaded from a file (orders.dat) that contains the Names, IDs, Phone
numbers, and the information of cars they want to order. Users of the system
should have the ability to add new orders which will be written to the output
orders file immediately. Or modifying existing orders.
2. Show car inventory. This command will print the car inventory (the existing
cars).
3. Serve orders. You should take the orders from the queue and search for the
cars in the linked list, if exist, delete them from the linked list and put the
sold cars with the buyers’ information in a stack. This stack will allow the
car agency to print the information of the last sold car and it’s buyer.
4. Unserved orders. This should display the list of orders that were not served
(because these cars are not in the inventory).
5. Show last sold car. This would print the information of the last sold car and
it’s buyer.
6. Update orders and car information. To update the input files with the cars
that have been sold and the orders that have been served.
7. Exit.
