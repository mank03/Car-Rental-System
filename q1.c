/**
 * Name: Manu Konnur
 * ID: 1178498
 * Date: 22/10/22
 * Assignment #2 - Question 1: Car Rental System
 **/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>	

typedef struct rentalData{
    char user[50]; 			// the plate number
    int text; 		        // the mileage
    int date;               // return date
    struct rentalData *next;  //dynamic connection to the next rental
}rental;

// menu functions 
rental * addNewCar(rental * availableList);
rental * returnedCar(rental *rentList);
rental * repairComplete(rental * repairList, rental * availableList);
rental * rentCar(rental * availableList);
void displayLists(rental * availableList, rental *repairList, rental *rentList);
void saveToFile(rental * availableList, rental * repairList, rental * rentList);
void loadFromFile(rental ** availableList, rental ** repairList, rental ** rentList);
void sortList (rental ** head);
int income (rental * list, rental * node);
void addNodeToList(rental**head,rental * node);
void deleteNode(rental**repairList,rental * theNode);
void deleteHeadNode(rental**availableList);

int main(int argc, char *argv[]){
    //declare and initialize required variables
    int menuOption = 0;
    rental * availableList = NULL; 
    rental * rental1;
    rental * rental2;
    rental * rental3;
    rental * repairList = NULL;
    rental * repair;
    rental * rentList = NULL;
    rental * rent;
    int total1 = 0;
    int total2 = 0;
    
    loadFromFile(&availableList, &repairList, &rentList);
    //do while loop to loop through menu options until user enter 7
    do{
        printf("\nMenu options: \n\n");
        printf("1. Add a Car\n");
        printf("2. Return a Car\n");
        printf("3. Return a Car to Repair\n");
        printf("4. Repair Complete\n");
        printf("5. Rent a Car\n");
        printf("6. Display Lists\n");
        printf("7. Exit Program\n");

        //ask user to choose menu option
        printf("Choose a menu option: ");
        scanf("%d", &menuOption);
        //switch statement that calls a function corresponding to user input
        switch(menuOption){
            case 1:
                rental1 = addNewCar(availableList);
                addNodeToList(&availableList,rental1);
                break;
            case 2:
                rental2 = returnedCar(rentList);
                total1 = total1 + income(rentList,rental2);
                if(strlen(rental2->user)!=0){
                    deleteNode(&rentList,rental2);
                    addNodeToList(&availableList,rental2);
                }
                break;
            case 3:
                repair = returnedCar(rentList);
                total2 = total2 + income(rentList, repair);
                if(strlen(repair->user)!=0){
                    deleteNode(&rentList,repair);
                    addNodeToList(&repairList,repair);
                }
                break;
            case 4:
                rental3 = repairComplete(repairList, availableList);
                break;
            case 5:
                rent = rentCar(availableList);
                addNodeToList(&rentList,rent);
                deleteHeadNode(&availableList);
                break;
            case 6:
                displayLists(availableList, repairList, rentList);
                break;
            case 7:
                printf("total income: %d\n", total1 + total2);
                saveToFile(availableList, repairList, rentList);
                break;
            default: printf ("That is an invalid choice\n");
        }
    }while(menuOption != 7);
    //while loop to free temp variables
    while(availableList != NULL){
        rental1 = availableList;
        availableList = availableList -> next;
        free(rental1);
    }
    while(rentList != NULL){
        rental2 = rentList;
        rentList = rentList -> next;
        free(rental2);
    }
    while(availableList != NULL){
        rent = availableList;
        availableList = availableList -> next;
        free(rent);
    }
    while(rentList != NULL){
        repair = rentList;
        rentList = rentList -> next;
        free(repair);
    }
    while(repairList != NULL){
        rental3 = repairList;
        repairList = repairList -> next;
        free(rental3);
    }
    return 0;
}

//this function adds a new car to the available list
rental* addNewCar(rental * availableList){
    //declare and initialize required variables
    rental *newNode;
    int mileage = 0;
    char plateNum[5000] = {0};
    int j = 0;
    int k = 0;

    //malloc temp variable
    newNode = malloc(sizeof(rental));
    getchar();  
    //taking user input for plate number
    while(k == 0){
        k = 1;
        printf("Enter plate number: ");
        fgets(plateNum, 5000, stdin); 
        plateNum[strlen(plateNum)-1] = '\0';
        if(strlen(plateNum) == 0 || strlen(plateNum) > 50){
            printf("Error! Please try again.\n");
            k = 0;
        }
    }
    //taking user input for mileage
    while(j == 0){
        j = 1;
        printf("Enter mileage: ");
        scanf("%d", &mileage);
        if(mileage < 0){
            printf("Error! Please enter valid mileage\n");
            j = 0;
        }
    }
    strcpy(newNode -> user, plateNum);
    newNode -> text = mileage;
    return newNode;
}

//helper function to add a node to the end of the list
void addNodeToList(rental**head,rental * node){
    //set a temp variable to head
    rental *a = *head;
    //if head is NULL, then set to node 
    if(*head == NULL){
        *head = node;
    }
    else{
        //otherwise add a to next node and loop to next node
        while(a -> next != NULL)
        {
            a = a -> next;
        }
        a -> next = node;
    }
    sortList(head);
}

//this function rents the car at head node of the available list and transfers to the rental list
rental * rentCar(rental * availableList){
    //declare and initialize required variables
    rental *newNode;
    int returnDate = 0;
    int j = 0;
    int count = 0;

    //malloc temp variable
    newNode = malloc(sizeof(rental));
    getchar();  
    //taking user input for return date
    while(j == 0){
        j = 1;
        printf("Enter expected return date (yymmdd): ");
        scanf("%d", &returnDate);
        if(returnDate < 0 || returnDate > 231231){
            printf("Error! Please enter valid return data\n");
            j = 0;
        }
    }
    while(availableList != NULL){
        count++;
        if(count == 1){
            strcpy(newNode -> user, availableList -> user);
            newNode -> text = availableList -> text;
            break;
        }
        availableList = availableList -> next;
    }
    availableList = newNode -> next;
    newNode -> date = returnDate;
    return newNode;
}

//this helper function delete the head node of the available list (required for menu 5)
void deleteHeadNode(rental**availableList){
    rental *node = *availableList;
    *availableList = node -> next;
    free(node);
}

//this method transfers a car from the repair list to the available-for-rent lis
rental * repairComplete(rental * repairList, rental * availableList){
    //declare and initialize required variables
    rental *newNode;
    char plateNum[5000] = {0};
    int k = 0;
    int c = 0;

    //malloc temp variable
    newNode = malloc(sizeof(rental));
    getchar();  
    //taking user input for plate number
    while(k == 0){
        k = 1;
        printf("Enter plate number: ");
        fgets(plateNum, 5000, stdin); 
        plateNum[strlen(plateNum)-1] = '\0';
        if(strlen(plateNum) == 0 || strlen(plateNum) > 50){
            printf("Error! Please try again.\n");
            k = 0;
        }
    }
    while(repairList != NULL){
        //loops through repairList to find if car exists in list
        if(strcmp(repairList->user, plateNum) == 0){
            printf("\nThis car exists!\n");
            strcpy(newNode -> user, plateNum);
            newNode -> text = repairList -> text;
            deleteNode(&repairList, newNode);
            addNodeToList(&availableList,newNode);
            c++;
        }
        repairList = repairList -> next;
    }
    if(c == 0){
        printf("This car does not exist in system.\n");
    }
    return newNode;
}
//helper function to delete a node that is not the head node
void deleteNode(rental**repairList,rental * theNode){
    //declare and initialize required variables
    int delete = 0;
    int count = 0;
    rental *node = *repairList;
    rental *node2;
    rental *a = *repairList;

    //while loop to count number of entries
    while(a != NULL){
        count++;
        delete++;
        if(strcmp(a->user,theNode->user) == 0 && delete == 1){

            break;
        }
        else if(strcmp(a->user,theNode->user) == 0 && delete > 1){
            break;
        }
        printf("\n");
        a = a -> next;
    }
    if(count == 0){
        return;
    }
    //if delete = 1, set head the next node
    if(delete == 1){
        *repairList = node -> next;
        free(node);
        return;
    }
    else if(delete > count || delete < 1){
        //check for invalid input
        printf("Invalid entry\n");
    }
    else{
        //otherwise, delete the user requested node using while loop
        while(--delete)
        {
            node2 = node;
            node = node -> next;
        }
        node2 -> next = node -> next;
    }
    //free node after dynamically allocated and return function
    free(node);
}

//this method transfers the returned car to the available list from the rentList
rental * returnedCar(rental *rentList){
    //declare and initialize required variables
    rental *newNode;
    int mileage = 0;
    char plateNum[5000] = {0};
    int j = 0;
    int k = 0;
    int c = 0;

    //malloc temp variable
    newNode = malloc(sizeof(rental));
    getchar();  
    //taking user input for plate number
    while(k == 0){
        k = 1;
        printf("Enter plate number: ");
        fgets(plateNum, 5000, stdin); 
        plateNum[strlen(plateNum)-1] = '\0';
        if(strlen(plateNum) == 0 || strlen(plateNum) > 50)
        {
            printf("Error! Please try again.\n");
            k = 0;
        }
    }
    //taking user input for mileage
    while(j == 0){
        j = 1;
        printf("Enter mileage: ");
        scanf("%d", &mileage);
        if(mileage < 0){
            printf("Error! Please enter valid mileage\n");
            j = 0;
        }
    }
    while(rentList != NULL){   
        if(strcmp(rentList->user, plateNum) == 0){
            printf("This car exists!\n");
            c++;
            strcpy(newNode -> user, plateNum);
            newNode -> text = mileage;
        }
        else if(strcmp(rentList->user, plateNum) != 0){
            //printf("This car does not exist in system.\n");
        }
        rentList = rentList -> next;
    }
    if(c == 0){
        printf("This car does not exist in system.\n");
    }
    return newNode;
}

//This method loads the disk file
void loadFromFile(rental ** availableList, rental ** rentList, rental ** repairList){
    //declare and initialize required variables
    FILE *file;
    rental *temp;
    rental *temp2;
    rental *temp3;
    char *token;
    int x = 0;
    char userInfo[1000];
    int available = 0;
    int rent = 0;
    int repair = 0;
    int a = 0;

    while(x==0){
        x = 1;
        file = fopen("rentalDatabase.csv", "r");
        if(file == NULL){
            printf("file is NULL\n");
            return;
        }
        //using while loop that loops to end of file to obtain user information
        while(fgets(userInfo, sizeof(userInfo), file)){
            //mallocing a temp variables to store user info
            temp = calloc(sizeof(rental),1);
            temp -> next = NULL;
            temp2 = calloc(sizeof(rental),1);
            temp2 -> next = NULL;
            temp3 = calloc(sizeof(rental),1);
            temp3 -> next = NULL;
            //using fgets to get each line of fine
            userInfo[strlen(userInfo)-1] = '\0';
            //strtok array with delimiter of ","
            token = strtok(userInfo, " ");

            //checking if strtok is NULL
            if(token == NULL){
                printf("token is NULL\n");
            }
            //while token is not equal to NULL, populate token into corresponding data
            while(token != NULL){
                a++;
                if(strcmp(token, "available") == 0){
                    available = 1;
                    rent = 0;
                    repair = 0;
                }
                else if(strcmp(token, "rent") == 0){
                    rent = 1;
                    available = 0;
                    repair = 0;
                }
                else if(strcmp(token, "repair") == 0){
                    repair = 1;
                    available = 0;
                    rent = 0;
                }
                if(a == 2 && available == 1){
                    strcpy(temp -> user, token);
                }
                else if(a == 2 && rent == 1){
                    strcpy(temp2 -> user, token);
                }
                else if(a == 2 && repair == 1){
                    strcpy(temp3 -> user, token);
                }
                else if(a == 3 && available == 1){
                    temp -> text = atoi(token);
                }
                else if(a == 3 && rent == 1){
                    temp2 -> text = atoi(token);
                }
                else if(a == 3 && repair == 1){
                    temp3 -> text = atoi(token);
                }
                else if(a == 4 && available == 1){
                    temp -> date = atoi(token);
                }
                else if(a == 4 && rent == 1){
                    temp2 -> date = atoi(token);
                }
                else if(a == 4 && repair == 1){
                    temp3 -> date = atoi(token);
                }    
                token = strtok(NULL, " ");
            }
            if(strlen(temp->user)!=0){
                addNodeToList(availableList, temp);
            }
            if(strlen(temp2->user)!=0){
                addNodeToList(repairList, temp2);
            }
            if(strlen(temp3->user)!=0){
                addNodeToList(rentList, temp3);
            }
            a = 0;
        }
    }
    //close the file once done
    fclose(file);
}

//this method saves the information to the disk file once the program quits
void saveToFile(rental * availableList, rental * repairList, rental * rentList){
    //declare and initialize required variables
    FILE *file;
    rental *temp;
    rental *temp2;
    rental *temp3;
    int x = 0;

    while(x==0){
        //open file in write mode
        x = 1;
        file = fopen("rentalDatabase.csv", "w");
        //check if file pointer is NULL
        if(file == NULL){
            printf("file is NULL\n");
            return;
        }
        //using for loop to obtain information of linked list
        for(temp = availableList; temp != NULL; temp = temp -> next){
            fprintf(file, "available %s ", temp -> user);
            fprintf(file, "%d ", temp -> text);
            fprintf(file, "%d,", temp -> date);
            fprintf(file, "\n");
        }
        for(temp2 = repairList; temp2 != NULL; temp2 = temp2 -> next){
            fprintf(file, "repair %s ", temp2 -> user);
            fprintf(file, "%d ", temp2 -> text);
            fprintf(file, "%d,", temp2 -> date);
            fprintf(file, "\n");
        }
        for(temp3 = rentList; temp3 != NULL; temp3 = temp3 -> next){
            fprintf(file, "rent %s ", temp3 -> user);
            fprintf(file, "%d ", temp3 -> text);
            fprintf(file, "%d,", temp3 -> date);
            fprintf(file, "\n");
        }
    }
    //close file once done
    free(temp);
    free(temp2);
    free(temp3);
    fclose(file);
}

//this method displays all 3 linked list information
void displayLists(rental * availableList, rental * repairList, rental * rentList){
    printf("********\n");
    printf("AVAILABLE TO RENT\n");
    //loops through each of node and prints username, user rental and List
    while(availableList != NULL){
        printf("Car Plate: %s, Mileage: %d, Return Date: %d", availableList->user, availableList->text, availableList->date);
        printf("\n");
        availableList = availableList -> next;
    }
    printf("\n");
    printf("********\n");
    printf("CARS IN REPAIR\n");
    //loops through each of node and prints username, user rental and List
    while(repairList != NULL){
        printf("Car Plate: %s, Mileage %d, Return Date: %d", repairList->user, repairList->text, repairList ->date);
        printf("\n");
        repairList = repairList -> next;
    }
    printf("\n");
    printf("********\n");
    printf("RENTED CARS\n");
    //loops through each of node and prints username, user rental and List
    while(rentList != NULL){
        printf("Car Plate: %s, Mileage: %d, Return Date %d", rentList->user, rentList->text, rentList->date);
        printf("\n");
        rentList = rentList -> next;
    }
}

//this method calculates the income of the returned cars
int income (rental * list, rental * node){
    //declare required variables
    int mileageOriginal = 0;
    int mileageAfter = 0;
    int rentalMileage = 0;
    float rentalCost = 0;
    float rentalCostExtra = 0;

    //while loop to calculate the income using the nodes
    while(list != NULL){
        if(strcmp(list->user, node->user) == 0){
            mileageOriginal = list-> text;
            mileageAfter = node->text;
            rentalMileage = mileageOriginal - mileageAfter;
            rentalCost = 80.00;
            rentalCostExtra = rentalCost + (rentalMileage - 200)*0.15;

            if(rentalMileage < 201){
                return rentalCost;
            }
            else if(rentalMileage > 200){
                return rentalCostExtra;
            }
        }
        printf("\n");
        list = list -> next;
    }
    return 0;
}

//this method sorts the linked lists in the order of mileage
void sortList (rental ** head){    
    //declare and initialize required variables
    rental* temp1;
    rental* temp2;

    //check if head is NULL
    if(*head == NULL){
        printf("head is NULL\n");
        return;
    }
    else{
        //otherwise, using for loop, set temp variable to head and loop through each node to perform bubble sort sorting method
        for(temp1 = *head; temp1 != NULL; temp1 = temp1 -> next){
            for(temp2 = temp1 -> next; temp2 != NULL; temp2 = temp2 -> next){ 
                if(temp1 -> text > temp2 -> text){   
                    //malloc a temp3 to store data in a temporary location
                    rental* temp3 = malloc(sizeof(rental));

                    temp3->date = temp1 ->date;
                    temp3->text = temp1->text;
                    strcpy(temp3->user, temp1->user);

                    temp1 ->date = temp2 -> date;
                    temp1 ->text = temp2 ->text;
                    strcpy(temp1->user, temp2->user);

                    temp2->date = temp3 -> date;
                    temp2 -> text = temp3->text;
                    strcpy(temp2->user, temp3->user);
                    //free temp3 once memory is dynamically allocated
                    free(temp3);
                }
            }
        }
    }
}  
