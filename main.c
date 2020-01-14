/*
Created by Thomas Nguyen
12/30/2019
https://github.com/ThomasWinn
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

/***********************************************************************************************************************                                      
GLOBAL ARRAYS
***********************************************************************************************************************/

// EDITABLE
// All CASA CNY Marketing Participants
char* CNYParticipants[] = 
{
    "Eileen Jiang",
    "Melody Markert",
    "Leia Liang",
    "Alvin Tan",
    "Michelle Lu",
    "Hannah Lin",
    "Helen Yu",
    "David Ma",
    "Christipher Lee",
    "Emily Lam",
    "Grace Ha",
    "Aeola Lu",
    "Thomas Nguyen",
    "Rachel Tan",
    "Clare Peterson",
    "Kenny Peng",
    "Eileen Chen",
    "Jacqueline Zhang",
    "Kay Rusch",
    "Jamie Wang",
    "Cindy Li",
    "Jerry Jiang",
    "Amanda Ngu",
    "Luke Chen",
    "Andrew Walker",
    "Ryan Jeo",
    "Shelly Tran",
    "Alexis Moy",
    "Stephanie Ye",
    "Evan Lin",
    "Fisher Chu",
    "Anna Blondin",
    "Mai Yang"
};

// EDITABLE
// Dates for marketing scheduling
char* schedulingDates[] = 
{
    "01/16/2020",
    "01/17/2020",
    "01/18/2020",
    "01/19/2020",
    "01/20/2020",
    "01/21/2020",
    "01/22/2020",
    "01/23/2020",
    "01/24/2020",
    "01/25/2020",
    "01/26/2020",
    "01/27/2020",
    "01/28/2020",
    "01/29/2020",
    "01/30/2020",
    "01/31/2020"
};

// EDITABLE
// A list of participant indexes
// Amount of participants must equal the amount of indexes
int participantIdx[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 
                        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
                        29, 30, 31, 32};

/***********************************************************************************************************************                                      
GLOBAL VARIABLES
***********************************************************************************************************************/

// Getting the array size of the ParticipantIdx array
int idxArraySize = sizeof(participantIdx) / sizeof(participantIdx[0]); 

// Initialization of our Linked List Data Structure
struct Node* availableListHead;
struct Node* removalListHead;

/***********************************************************************************************************************                                      
GLOBAL STRUCTURES
***********************************************************************************************************************/

// Linked list Fields 
struct Node 
{
    int data;
    struct Node* next;
};

// EDITABLE
struct Date 
{
    char day[15]; 
    char* eventSharing[3][50]; // EDITABLE - Change to max number of people scheduled per day
    char* facebookFrame[3][50]; // EDITABLE - Change to max number of people scheduled per day
};

/***********************************************************************************************************************                                      
FUNCTIONS
***********************************************************************************************************************/

// Quick sort function
int sorter(const void* a, const void* b) 
{
    return strcmp(*(const char**)a, *(const char**)b);
}

// Returns a random number from 0 - 32 inclusive meaning 0 and 32 are possibilities as well
// I tried to make this completely random after each seed, but when I add srand(time(0)), it does not randomize completely after each recompilation
int getRandomIdx(int lower, int higher) 
{
    int idx = (rand() % (higher - lower + 1)) + lower;
    return idx;
}

// Deletes an element out of the participantIdx array at the specified index then decrease the array size
// Returns the element that got deleted
int deleteElementFromArray (int array[], int idx, int arraySize)
{   
    int target = -1;

    // Deletion not possible if position wanting to be deleted is greater than size of array
    if(idx > arraySize || idx < 0)
    {
        printf("Deletion not possible\n");
        return -1;
    }
    else 
    {
        target = array[idx];
        
        arraySize--;
        
        for (int c = idx; c < arraySize; c++) 
        {
            array[c] = array[c+1];
        }
    }
    
    return target;
}

// adds a new node to end of a specified linked list also adds a number to the data part of that node
void addNodeToEnd (struct Node** head_ref, int num)
{
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    struct Node* last = *head_ref;

    newNode->data = num;
    newNode->next = NULL;

    // make newNode first thing in linked list if there is already nothing in linked list
    if(*head_ref == NULL)
    {
        *head_ref = newNode;
        return;
    }
    while (last->next != NULL)
    {
        last = last->next;
    }
    last->next = newNode;
    return;
}

// Deletes the node with the designated key data type
void deleteNode (struct Node **head_ref, int num)
{
    struct Node* temp = *head_ref;
    struct Node* prev;

    // if first node holds the key
    if (temp != NULL && temp->data == num)
    {
        //printf("Deleting first node in linked list\n");
        *head_ref = temp->next;
        free(temp);
        return;
    }

    // search the key to be deleted
    while (temp != NULL && temp->data != num)
    {
        prev = temp;
        temp = temp->next;
    }

    // if key is not present in linked list
    if (temp == NULL) 
    {
        return;
    }

    // the deletion part
    prev->next = temp->next;

    free(temp); 
}
    
// checks to see if node is in the node linked list
bool checkNode (struct Node *head, int num)
{
    struct Node* current = head;
    
    while(current != NULL) 
    {
        if(current->data == num)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}


// mainly for debugging purposes
// Prints out the designated linked list for you to see
void printList(struct Node *node) 
{
    struct Node *currentNode = node;
    if(currentNode == NULL)
    {
        printf("Nothing in linked list\n");
    }
    while(currentNode != NULL)
    {
        printf("  %d  ", currentNode->data);
        currentNode = currentNode->next;
    }
}

// EDITABLE
// Sets the LinkedLists and idxArray values to its default numbers
// idxArray = {0,1,2,3,...,32} SIZE 33
void setLinkedListsAndIdxArray(struct Node *aLLHead, struct Node *rLLHead, int participantTotal)
{
    availableListHead = NULL;
    removalListHead = NULL;

    for (int i = 0; i < participantTotal; i++)
    {
        addNodeToEnd(&availableListHead, i);
    }

    // resetting the particpantIdx array and idxArraySize global variables
    idxArraySize = 33; // EDITABLE - Change to number of paraticipants / people
    int step = 0;
    for(int i = 0; i < idxArraySize; i++) 
    {
        participantIdx[i] = step;
        step++;
    }
}


/***********************************************************************************************************************                                      
MAIN
***********************************************************************************************************************/


int main (int argc, const char* argv[]) 
{
    // EDITABLE - Do (numberOfParticpants % numberOfDays) = excess amount of randomNumX needed per day 
    // Initialize common variable that will be used later in the code
    // These values will tell us which dates to fill the max amount of names to the particular date
    int randomNumOne;
    int randomNumTwo;
    int randomNumThree;
    int randomNumFour;
    int randomNumFive;

    // Gets number of cny participants and number of scheduling days
    int numberOfParticipants = sizeof(CNYParticipants) / sizeof(CNYParticipants[0]); 
    int numberOfDays = sizeof(schedulingDates) / sizeof(schedulingDates[0]);

    // These represent the lowest and highest index to pick a random number from
    int lowerIdx = 0;
    int higherIdx = numberOfParticipants - 1; 

    // Sorts the list of people alphabetically by first name given an array
    qsort(CNYParticipants, numberOfParticipants, sizeof(CNYParticipants[0]), sorter);

    setLinkedListsAndIdxArray(availableListHead, removalListHead, numberOfParticipants);

    // Initialize the Date structure
    // array of structures, d
    struct Date d[numberOfDays];

    // Size of the amount of names that can be put into the char array's struct values
    int eventSharingSize = sizeof(d[numberOfDays].eventSharing) / sizeof(d[numberOfDays].eventSharing[0]);
    int facebookFrameSize = sizeof(d[numberOfDays].facebookFrame) / sizeof(d[numberOfDays].facebookFrame[0]); 

    // Initializing both event sharing & facebook frame array values to "-"
    // If we don't do this, "garbage" will print out 
    for (int r = 0; r < numberOfDays; r++)
    {
        for(int o = 0; o < eventSharingSize; o++)
        {
            strcpy(d[r].eventSharing[o], "-");
        }
        for(int k = 0; k < facebookFrameSize; k++)
        {
            strcpy(d[r].facebookFrame[k], "-");
        }
    }

    /***********************************************************************************************************************                                      
    SHARING EVENT
    ***********************************************************************************************************************/

    /*
    
    Change higher index to numberOfDays since we are trying to pick a random day to have 
    3 names filled in their array instead of 2 like everyother

    reinitialize higher index to 32 for future use

    */

    higherIdx = numberOfDays;
    randomNumOne = getRandomIdx(lowerIdx, higherIdx);
    higherIdx = numberOfParticipants - 1;

    /*
    
    Iterate through all the days and add the date to the struct.

    */

    for(int m = 0; m < numberOfDays; m++) 
    {
        strcpy(d[m].day, schedulingDates[m]);
        
        // Catches the case for when to add an extra name to array in struct
        if(m == randomNumOne) 
        {
            for(int i = 0; i < eventSharingSize; i++) 
            {
                int flag = 1;
                int randomIdx;
                while(flag == 1)
                {
                    // Keep track of a random Index to find in the participantIdx 
                    randomIdx = getRandomIdx(lowerIdx, higherIdx); 

                    // Keep track of the actual number to delete using the index it got randomly
                    int numToDeleteOrAdd = deleteElementFromArray(participantIdx, randomIdx, idxArraySize);

                    // After we delete element in array, we decrease the highest value it can get a random idx from
                    higherIdx--; 

                    bool nodeCheck = checkNode(availableListHead, numToDeleteOrAdd);

                    // If the student's number is found in the availableList it can delete it and add it to the removal list
                    // The student's name is then added into the struct
                    if(nodeCheck == true)
                    {
                        deleteNode(&availableListHead, numToDeleteOrAdd);
                        addNodeToEnd(&removalListHead, numToDeleteOrAdd);
                        strcpy(d[m].eventSharing[i], CNYParticipants[numToDeleteOrAdd]);
                        flag = 0;
                    }

                    // Error check
                    else 
                    {
                        printf("nodeCheck FAILED.\n");
                        exit(0);
                    }
                }
            }
            continue;
        }
        
        // This will have the hold the condition of holding one less name 
        // My example - 2 people per day. -1 because sharing size = 3 and we make it 2
        for(int i = 0; i < (eventSharingSize - 1); i++) 
        {
            int flag = 1;
            int randomIdx;
            while(flag == 1)
            {
                // Keep track of a random Index to find in the participantIdx 
                randomIdx = getRandomIdx(lowerIdx,higherIdx); 

                // Keep track of the actual number to delete using the index it got randomly
                int numToDeleteOrAdd = deleteElementFromArray(participantIdx, randomIdx, idxArraySize);

                // After we delete element in array, we decrease the highest value it can get a random idx from
                higherIdx--; 

                bool nodeCheck = checkNode(availableListHead, numToDeleteOrAdd);

                // If the student's number is found in the availableList it can delete it and add it to the removal list
                // The student's name is then added into the struct
                if(nodeCheck == true)
                {
                    deleteNode(&availableListHead, numToDeleteOrAdd);
                    addNodeToEnd(&removalListHead, numToDeleteOrAdd);
                    strcpy(d[m].eventSharing[i], CNYParticipants[numToDeleteOrAdd]);
                    flag = 0;
                }

                // Error Check
                else 
                {
                    printf("nodeCheck FAILED.\n");
                    exit(0);
                }
            }
        }
    }   

    /***********************************************************************************************************************                                      
    SHARING FACEBOOK FRAME 
    ***********************************************************************************************************************/

    // Reset all values before filling the next array in the struct
    // sorted array stays the same
    // higherIdx needs resetting as it was decremented to 0
    // global idxArray needs resetting and available/removal linked list

    higherIdx = numberOfParticipants - 1;
    setLinkedListsAndIdxArray(availableListHead, removalListHead, numberOfParticipants);

    /*
    
    The first two days is not allowed to have anyone sharing the facebook frame, so we increment the lowerIdx
    We also want the higherIdx to be the numberOfDays available

    When picking a random number we can't have the same values picked, so we need to 
    delete the number out of a list to prevent it being picked in a future call

    We pick 5 random indexes to fill the array struct completely

    Then reset all values to original

    This whole process is just like the sharing event section above except theres more days that require all 
    array valeus filled

    */

    lowerIdx = 2;
    higherIdx = numberOfDays;

    randomNumOne = getRandomIdx(lowerIdx, higherIdx);
    randomNumOne = deleteElementFromArray(participantIdx, randomNumOne, idxArraySize);
    
    randomNumTwo = getRandomIdx(lowerIdx, higherIdx);
    randomNumTwo = deleteElementFromArray(participantIdx, randomNumTwo, idxArraySize);
    
    randomNumThree = getRandomIdx(lowerIdx, higherIdx);
    randomNumThree = deleteElementFromArray(participantIdx, randomNumThree, idxArraySize);
    
    randomNumFour = getRandomIdx(lowerIdx, higherIdx);
    randomNumFour = deleteElementFromArray(participantIdx, randomNumFour, idxArraySize);
    
    randomNumFive = getRandomIdx(lowerIdx, higherIdx);
    randomNumFive = deleteElementFromArray(participantIdx, randomNumFive, idxArraySize);
    

    lowerIdx = 0;
    higherIdx = numberOfParticipants - 1;
    setLinkedListsAndIdxArray(availableListHead, removalListHead, numberOfParticipants);

    for (int p = 0; p < numberOfDays; p++)
    {

        // Skips the first two days not entering anything into their struct
        if(p == 0 || p == 1) 
        {
            continue;
        }

        // On the certain days, we have 3 names in the array fields in struct
        if(p == randomNumOne || p == randomNumTwo || p == randomNumThree || p == randomNumFour || p == randomNumFive) 
        {
            for(int i = 0; i < facebookFrameSize; i++) 
            {
                int flag = 1;
                int randomIdx;
                while(flag == 1)
                {
                    // Keep track of a random Index to find in the participantIdx 
                    randomIdx = getRandomIdx(lowerIdx,higherIdx); 

                    // Keep track of the actual number to delete using the index it got randomly
                    int numToDeleteOrAdd = deleteElementFromArray(participantIdx, randomIdx, idxArraySize);

                    // after we delete element in array, we decrease the highest value it can get a random idx from
                    higherIdx--; 

                    bool nodeCheck = checkNode(availableListHead, numToDeleteOrAdd);

                    // If the student's number is found in the availableList it can delete it and add it to the removal list
                    // The student's name is then added into the struct
                    if(nodeCheck == true)
                    {
                        deleteNode(&availableListHead, numToDeleteOrAdd);
                        addNodeToEnd(&removalListHead, numToDeleteOrAdd);
                        strcpy(d[p].facebookFrame[i], CNYParticipants[numToDeleteOrAdd]);
                        flag = 0;
                    }

                    // Error Check
                    else 
                    {
                        printf("nodeCheck FAILED.\n");
                        exit(0);
                    }
                }
            }
            continue;

        }
    
        // This will have the hold the condition of holding one less name 
        // My example - 2 people per day. -1 because sharing size = 3 and we make it 2
        else
        {
            for(int i = 0; i < (facebookFrameSize-1); i++) 
            {
                int flag = 1;
                int randomIdx;
                while(flag == 1)
                {
                    // Keep track of a random Index to find in the participantIdx 
                    randomIdx = getRandomIdx(lowerIdx,higherIdx); 

                    // Keep track of the actual number to delete using the index it got randomly
                    int numToDeleteOrAdd = deleteElementFromArray(participantIdx, randomIdx, idxArraySize);

                    // after we delete element in array, we decrease the highest value it can get a random idx from
                    higherIdx--; 

                    bool nodeCheck = checkNode(availableListHead, numToDeleteOrAdd);

                    // If the student's number is found in the availableList it can delete it and add it to the removal list
                    // The student's name is then added into the struct
                    if(nodeCheck == true)
                    {
                        deleteNode(&availableListHead, numToDeleteOrAdd);
                        addNodeToEnd(&removalListHead, numToDeleteOrAdd);
                        strcpy(d[p].facebookFrame[i], CNYParticipants[numToDeleteOrAdd]);
                        flag = 0;
                    }

                    // Error Check
                    else 
                    {
                        printf("nodeCheck FAILED.\n");
                        exit(0);
                    }
                }
            }
        }
        
    }

    /***********************************************************************************************************************                                      
    PRINTING TO TXT FILE
    ***********************************************************************************************************************/

    /*
    
    This section focuses on outputting the results all stored in the structures into a
    text file to be easily seen by the user. 
    
    */

    // Create a text file named "Marketing Schedule.txt" to be written to by the user
    FILE *fp = fopen("Marketing Schedule.txt", "w");

    // Error check in case the file was not able to be opened
    if(fp == NULL)
    {
        printf("Could not open file");
    }

    // Keep track of the Day number to keep track of the Day Number's results from the struct
    // Muliple flags are initialized to keep track when to output each char array value from the struct
    // 1 = true 0 = false
    int dayNumber = 0;
    int dateFlag = 1;
    int datePerson1 = 1;
    int datePerson2 = 0;
    int datePerson3 = 0;
    
    // EDITABLE - You might not have a total of 67 lines and not have the same layout as me
    // 67 because of the amount of lines I'll need to create the table
    for(int s = 0; s < 67; s++)
    {
        // I know this is long... I am not sure an equation that can simplify this pattern
        // Divider lines
        if(s == 0 || s == 2 || s == 6 || s == 10 ||
            s == 14 || s == 18 || s == 22 || s == 26 ||
            s == 30 || s == 34 || s == 38 || s == 42 ||
            s == 46 || s == 50 || s == 54 || s == 58 ||
            s == 62 || s == 66) 
        {
            fprintf(fp, "---------------------------------------------------------------------------------------");
            fprintf(fp, "\n");
            continue;
        }

        // This prints out the initial header of the table only executed once in for loop
        if(s == 1)
        {
            fprintf(fp, "%-10s | %-25s | %-25s", "Date", "Sharing Event", "Sharing Facebook Frame");
            fprintf(fp, "\n");
            continue;
        }

        /*

        When one if statement is triggered by a flag, the initial one will turn off and the next flag will turn on for the next
        iteration in the for loop. This helps when the printing names in each row.

        dateFlag ON -> print date -> dateflag OFF-> datePerson1 flag ON -> print first array struct's values -> 
        datePerson1 Flag OFF -> datePerson2 flag ON -> print second array struct's values -> datePerson2 OFF ->
        datePerson3 ON -> print -> datePerson3 OFF -> datePerson1 ON -> dateFlag ON -> dayNumber INCREMENT

        */

        // EDITABLE - desired layout may not look like mine
        if(dateFlag == 1) 
        {
            fprintf(fp, "%-10s ", d[dayNumber].day);
            dateFlag = 0;
        }
        
        if(datePerson1 == 1)
        {
            fprintf(fp, "| %-25s | %-25s ", d[dayNumber].eventSharing[0], d[dayNumber].facebookFrame[0]);
            fprintf(fp, "\n");
            datePerson1 = 0;
            datePerson2 = 1;
            continue;
        }

        if(datePerson2 == 1)
        {
            fprintf(fp, "           | %-25s | %-25s ", d[dayNumber].eventSharing[1], d[dayNumber].facebookFrame[1]);
            fprintf(fp, "\n");
            datePerson2 = 0;
            datePerson3 = 1;
            continue;
        }

        if(datePerson3 == 1) 
        {
            fprintf(fp, "           | %-25s | %-25s ", d[dayNumber].eventSharing[2], d[dayNumber].facebookFrame[2]);
            fprintf(fp, "\n");
            datePerson3 = 0;
            datePerson1 = 1;
            dateFlag = 1;
            dayNumber++;
            continue;
        }

    }

    // Close the file to stop editing
    fclose(fp);

    return 0;
}