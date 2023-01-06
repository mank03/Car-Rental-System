/**
 * Name: Manu Konnur
 * ID: 1178498
 * 22/10/22
 * Assignment #2 - Question 2: Car Rental System
 **/


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX 100

float stack[MAX];
int front = 0;

//returns the makeEmpty function
bool empty()
{
	return front == 0;
}

//makes the stack empty
void makeEmpty()
{
	front = 0;	
}

//push the node
void push(float value)
{
	stack[front++] = value;
}

//pop the node
float pop()
{
	if(empty())
	{
		printf("Not enough operands in expression\n");
		exit(EXIT_FAILURE);
	}
	return stack[--front];	
}

//get the size of the stack
float size()
{
	return front;
}

//check if stack is full
bool isFull()
{
	return front == MAX;	
}

//adds 2 numbers
float add(float a, float b)
{
	return a + b;
}

//subtracts 2 numbers
float sub(float a, float b)
{
	return b - a;
}

//multiplies 2 numbers
float multiply(float a, float b)
{
	return a*b;
}

//divides 2 numbers
float divide(float a, float b)
{
	return a / b;
}


//read expression from user
void run(char arr[50], float sizeOfArray)
{
    float userInput;
    //get user input
    sscanf(arr, "%.2f", &userInput);

    for(int i = 0; i < sizeOfArray+1; i++){
        if(arr[i] == '\n'){
            break;      
        } 
        
        //check if chracter is a number
        if(arr[i] >= 48 && arr[i] <= 57)
        {
            if(!isFull())
            {
                //convert char to float and push number floato stack
                push(arr[i] - 48);
            } else
            {
                //if stack runs out of space, exit program
                printf("Expression is too complex\n");
                exit(EXIT_FAILURE);
            }
            
        }else if(arr[i] == 0){
            //prfloated the final result
            printf("pop: %.2f\n", pop());
        }

        //using series of switch statements to conduct the operations
        switch(arr[i])
        {
            case '+':
                push(add(pop(), pop()));
                break;
            case '-':
                push(sub(pop(), pop()));
                break;
            case '*':
                push(multiply(pop(), pop()));
                break;
            case '/':
                push(divide(pop(), pop()));
                break;
            case '\n':
                printf("pop: %.2f\n", pop());
                break;
        }
    }
}

int main(int argc, char *argv[])
{
    if( argc == 2 ) {
      printf("The argument is %s\n", argv[1]);
    }
    size_t Size = strlen( argv[1] );
	run(argv[1], Size);
	return 0;
}
