#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//constant variables
#define MAX_NUMBER 20
#define PLATE_NUMBER 6
#define MAX_DATE 10
#define MAX_SERVICE 30

//structs
char cards[2][4] = {"Cash", "Card"};

struct Customer { //customer structures 
    char first_name[MAX_NUMBER];
    char last_name[MAX_NUMBER];
    char transaction_date[MAX_DATE];
    char liscense_plate[PLATE_NUMBER];
    char *card_type;
    const char *service;
    float user_cost;
};

void customer_list();

int discount, wash_bay = 0, park_lot = 0, total_car = 0,wash_choice; // Globol scobe declarartion

void Wash_car(); // function declaration


enum Service {
    WASH_VACUUM = 2500,
    ENGINE_WASH = 2000,
    POLISHING = 3500,
    BUFFING = 5500,
    ROOF_CLEANING = 3200,
    INTERIOR = 7500
};


const char* service_type[] = { //array containing service types
    "Wash and Vacuum",
    "Engine Wash",
    "Polishing",
    "Buffing",
    "Roof Cleaning",
    "Detailing/Interior Shampooing"
};

struct Customer user_array[100] = {};  //array for users declaration

struct Customer Add_User(); //declaration for add_user funtion

int Is_Plate_Valid(char liscense_plate[PLATE_NUMBER]); //declaration for a function thats checks if user's license plate is valid

int check_customer(char first_name[MAX_NUMBER], char last_name[MAX_NUMBER]);  // declaration of check_customer function



int main(){ //Main function
    int choice = 0;
    int count = 0, total_amount_users = 0;
    while (choice != 5){ // loop thats runs till the program is exited
        do {
            printf("\n------------------------------------------------------------");
            printf("\n       Welcome to Trish & Shawn's Auto Wash Services        \n");
            printf("------------------------------------------------------------");
            printf("\n1) Accept Customer's Information and Payment\n2) Wash Car\n3) Display Returning Customers\n4) Display Day's Sales Report\n5) Exit program\nEnter Here: ");
            scanf("%d", &choice);
        }
        while(choice < 1 || choice > 5);
        
        switch (choice){
            case 1:
            if (wash_bay == 3 && park_lot == MAX_NUMBER){
                printf("This option cant be selected, Capacity has been met.");
                break;
            }
                struct Customer customer = Add_User();
                total_amount_users++;
                user_array[count] = customer;
                printf("Transaction Complete\n");
                count++;
                break;
            case 2:
                Wash_car();
               break; 
            case 3:
            if(wash_bay == 0 && park_lot == 0){
                printf("This option cant be selected, No customers has yet.");
                break;
            }
                customer_list(total_amount_users);
                break;
            case 4:
            if(wash_bay == 0 && park_lot == 0){
                printf("This option cant be selected, No customers has yet.");
                break;
            }
                break;
            case 5:
                printf("Exiting.........");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }

    return 0;
}



struct Customer Add_User(){ //Function to add users informations
    int choice, cardmethod;
    float pre_cost = 0, post_cost = 0, discount = 0, tip = 0, total_cost = 0,tip_number,tip_cost, post_discount;
    char service_selected[25];
    srand(time(NULL)); 
    struct Customer customer;
    printf("\n************************************************************\n");
    
    printf("Customer's First Name: ");
    scanf("%s", customer.first_name);
    printf("Customer's Last Name: ");
    scanf("%s", customer.last_name);
    if (wash_bay < 3)
    {
        wash_bay++;
    }else if (park_lot < MAX_NUMBER)
    {
        park_lot++;
    }else{
        printf("Capcity is full....\n");
        return customer;
    }
    
    
    
    
    if (check_customer(customer.first_name, customer.last_name) == 0){
        discount = 0.1;
    }
    
    do{
    printf("************************************************************\n");
    printf("Cusotmer's liscense plate: ");
    scanf("%s", customer.liscense_plate);
} while (Is_Plate_Valid(customer.liscense_plate) == 1);
    printf("\n************************************************************\n");
    printf("Enter today's date (eg.dd/mm/yyyy)\nEnter Here: ");
    scanf("%s", customer.transaction_date);
    do{
    printf("************************************************************\n");
    printf("\nType of service customer choose?\n");
    printf("------------------------------------------------\n");
    printf("|              Service              |   Cost   |\n");
    printf("|-----------------------------------|----------|\n");
    printf("|1.         Wash and Vacuum         | $2500.00 |\n");
    printf("|2.           Engine Wash           | $2000.00 |\n");
    printf("|3.            Polishing            | $3500.00 |\n");
    printf("|4.             Buffing             | $5500.00 |\n");
    printf("|5.           Roof Cleaning         | $3200.00 |\n");
    printf("|6.  Detailing/Interior Shampooing  | $7500.00 |\n");
    printf("------------------------------------------------\n");
    printf("select: ");
    scanf("%d",&choice);

    switch (choice)
    {
    case 1:
        pre_cost = WASH_VACUUM;
        break;
    case 2:
        pre_cost = ENGINE_WASH;
        break;
    case 3:
        pre_cost = POLISHING;
        break;
    case 4:
        pre_cost = BUFFING;
        break;
    case 5:
        pre_cost = ROOF_CLEANING;
        break;
    case 6:
        pre_cost = INTERIOR;
        break;
    default:
        break;
    }



} while (choice < 0 || choice > 6);
    printf("************************************************************\n");
    printf("Customer payment type? \n1. Cash\n2. Card\nEnter Here: ");
    scanf("%d", &cardmethod);
    customer.card_type = cards[cardmethod];
    customer.service = service_type[choice - 1];
    if (cardmethod == 2)
    {
        post_cost = (pre_cost * 0.03);
    }else{
        post_cost = 0;
    }
    post_discount = (pre_cost * discount);
    tip_number = rand() % 2 + 1;
    if (tip_number == 1){
        tip = 0.02;
    }else{
        tip = 0;
    }
    tip_cost = pre_cost * tip;
    total_cost = pre_cost + post_cost + tip_cost - (post_discount);

    customer.user_cost = total_cost;
    
    printf("\n--------------------------------------------\n");
    printf("              %s's Sale Summary               \n", customer.last_name);
    printf("----------------------------------------------\n");
    printf("Date: %s                                      \n", customer.transaction_date);
    printf("Name: %s %s                                   \n", customer.first_name, customer.last_name);
    printf("Service Type: %s                                      \n", customer.service);
    printf("Tip: $ %.1f                             \n", tip_cost);
    printf("Total Cost: $ %.2f                             \n", total_cost);
    printf("----------------------------------------------\n\n");
    return customer;
}


int Is_Plate_Valid(char liscense_plate[PLATE_NUMBER]){
    for (int i = 0; i < 4; i++){
        if (liscense_plate[i] < '0' || liscense_plate[i] > '9'){
            return 1;
        }
    }
    if (liscense_plate[4]  < 'A' || liscense_plate[4] > 'Z' || liscense_plate[5] < 'A' || liscense_plate[5] > 'Z'){
        return 1;
    }
    return 0;
}

void Wash_car(){
     
    total_car = wash_bay + park_lot;
    do{
        printf("\nCar at Wash Bay: %d cars\nCar at Parking Lot: %d cars\nTotal Cars: %d cars",wash_bay,park_lot,total_car);
        printf("\n1. Add Car to Wash Bay\n2. Wash Car\nEnter Here: ");
        scanf("%d", &wash_choice);

        switch (wash_choice)
        {
        case 1:
            park_lot++;
            wash_bay--;
            printf("Adding Car to Washing Bay......");
            break;
        case 2:
            wash_bay--;
            printf("Washing Car....\nFinish Washing Car");
            break;
        default:
            printf("Error");
            break;
        }
    }while (wash_choice == 1);
    
}

int check_customer( char firstname[MAX_NUMBER], char lastname[MAX_NUMBER] ){
 for (int i = 0; i < sizeof(user_array)/sizeof(struct Customer); i++)
 {
         if (strcmp(user_array[i].first_name, firstname) == strcmp(user_array[i].last_name, lastname))
         {
            printf("%s is available for discount\n", firstname);
            return 0;
         }
 }
 return 1;
}

void customer_list(int total_amount_users){
    for (int i = 0; i < total_amount_users; i++){
    printf("\n--------------------------------------------\n");    
        printf("\nFirst Name: %s\nLast Name: %s\nTransacation Date: %s\nService Type: %s\nTotal Spending: $ %.2f\n", user_array[i].first_name, user_array[i].last_name, user_array[i].transaction_date, user_array[i].service, user_array[i].user_cost);
    printf("--------------------------------------------\n");
    }
}