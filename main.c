/*
Created by Thomas Nguyen
12/30/2019
https://github.com/ThomasWinn


NOTE: 

I create a linked list of available (based on array indexes) cny participants and initialize a linkedlist for removal.
Everytime we use the random number generator, we remove participant from the available list to removal list.
We do all this to randomly get participants to market on certain days.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

// All CASA CNY Marketing Participants
// Can be edited for future use 

/***********************************************************************************************************************                                      
GLOBAL ARRAYS
***********************************************************************************************************************/

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


int participantIdx[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 
                        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
                        29, 30, 31, 32};





/***********************************************************************************************************************                                      
GLOBAL VARIABLES
***********************************************************************************************************************/


int idxArraySize = sizeof(participantIdx) / sizeof(participantIdx[0]); // 33

struct Node* availableListHead;
struct Node* removalListHead;

/***********************************************************************************************************************                                      
GLOBAL STRUCTURES
***********************************************************************************************************************/

// Linked list initialization 
struct Node 
{
    int data;
    struct Node* next;
};

struct Date 
{
    char day[15];
    char* eventSharing[3][50];
    char* facebookFrame[3][50];
};

struct Student 
{
    char name[50];
    int number;
};

/***********************************************************************************************************************                                      
FUNCTIONS
***********************************************************************************************************************/

// Quick sort function
int sorter(const void* a, const void* b) 
{
    return strcmp(*(const char**)a, *(const char**)b);
}

int getRandomIdx(int lower, int higher) 
{
    //srand(time(0));
    int idx = (rand() % (higher - lower + 1)) + lower;
    //srand(time(0));
    return idx;
}

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
        
        for (int c = idx; c < arraySize; c++) // c = index
        {
            array[c] = array[c+1];
        }
    }
    

    return target;
}

// adds a new node to end
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
        //printf("First Node: %d\n", num);
        return;
    }
    while (last->next != NULL)
    {
        last = last->next;
    }
    last->next = newNode;
    //printf("Node added: %d\n", num);
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
    idxArraySize = 33;
    int step = 0;
    for(int i = 0; i < idxArraySize; i++) // {0,1,2,3,...,32}
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

    int randomNumOne;
    int randomNumTwo;
    int randomNumThree;
    int randomNumFour;
    int randomNumFive;


    int lowerIdx = 0;
    int higherIdx = 32;

    

    // Gets number of cny participants and number of scheduling days
    int numberOfParticipants = sizeof(CNYParticipants) / sizeof(CNYParticipants[0]); //33
    int numberOfDays = sizeof(schedulingDates) / sizeof(schedulingDates[0]); //17

    // Sorts the list of people alphabetically by first name
    qsort(CNYParticipants, numberOfParticipants, sizeof(CNYParticipants[0]), sorter);

    // initializing linked list 
    // NULL
    // struct Node* availableListHead = NULL;
    // struct Node* removalListHead = NULL;

    // setup linked list of participants 
    // data = index of array
    setLinkedListsAndIdxArray(availableListHead, removalListHead, numberOfParticipants);

    // // PROBABLY DON'T NEED THIS
    // // One full new sorted copy of CNYParticipants array
    // for(int i = 0; i < numberOfParticipants; i++) 
    // {
    //     CNYParticipantsCopy[i] = CNYParticipants[i];
    // }
    // int numberOfParticipantsCopy = sizeof(CNYParticipantsCopy) / sizeof(CNYParticipantsCopy[0]);
    // qsort(CNYParticipantsCopy, numberOfParticipantsCopy, sizeof(CNYParticipantsCopy[0]), sorter);

    // Assign number to everyone
    struct Student participant[numberOfParticipants];
    for(int l = 0; l < numberOfParticipants; l++)
    {
        strcpy(participant[l].name, CNYParticipants[l]);
        participant[l].number = l + 1;
    }

    /*
    
    TODO: 
    
    Get Random Num between date numbers !!!!!
    
    */

    // Date is our main struct we are using to finalize our layout
    struct Date d[numberOfDays];


    int remainderEventSharing = numberOfParticipants % numberOfDays; // should be 1 
    int remainderFacebookFrame = numberOfParticipants % (numberOfDays - 2); // should be 5

    int eventSharingSize = sizeof(d[numberOfDays].eventSharing) / sizeof(d[numberOfDays].eventSharing[0]); // 3
    int facebookFrameSize = sizeof(d[numberOfDays].facebookFrame) / sizeof(d[numberOfDays].facebookFrame[0]); // 3
    //printf("eventSharingSize: %d\n", eventSharingSize)

    // Initializing both event sharing & facebook frame array values
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

    higherIdx = numberOfDays;
    randomNumOne = getRandomIdx(lowerIdx, higherIdx);
    higherIdx = 32;
    //printf("Random Number One = %d\n", randomNumOne);

    for(int m = 0; m < numberOfDays; m++) 
    {
        strcpy(d[m].day, schedulingDates[m]);
        //printf("day: %s\n", d[m].day);
        
        // fill struct for event sharing
        // to only take in up to 3 people at half way point
        if(m == randomNumOne) 
        {
            //break;
            for(int i = 0; i < eventSharingSize; i++) 
            {
                int flag = 1;
                int randomIdx;
                while(flag == 1)
                {
                    //printf("Attempting to get random idx number...\n");
                    randomIdx = getRandomIdx(lowerIdx,higherIdx); // 0 - 32
                    //printf("randomIdx: %d\n", randomIdx);

                    int numToDeleteOrAdd = deleteElementFromArray(participantIdx, randomIdx, idxArraySize);
                    higherIdx--; // after we delete element in array, we decrease the highest value it can get a random idx from
                    //printf("higheridx: %d\n", higherIdx);

                    // check to see if it is in the available list, if it is, delete in idx array, avail ,and add it to removal list, else select a new rando idx
                    bool nodeCheck = checkNode(availableListHead, numToDeleteOrAdd);

                    if(nodeCheck == true)
                    {
                        //printf("nodeCheck Passes for idx: \t%d which is: \t%d\n", randomIdx, numToDeleteOrAdd);
                        deleteNode(&availableListHead, numToDeleteOrAdd);
                        addNodeToEnd(&removalListHead, numToDeleteOrAdd);
                        strcpy(d[m].eventSharing[i], CNYParticipants[numToDeleteOrAdd]);

                        // DEBUG - 
                        // printf("Available List: \n");
                        // printList(availableListHead);
                        // printf("\n");
                        // printf("\n");
                        // printf("\n");
                        // printf("Removal List: \n");
                        // printList(removalListHead);
                        // printf("\n");
                        // printf("\n");
                        // printf("\n");
                        // printf("The name that was added: %s\n", d[m].eventSharing[i] );


                        flag = 0;
                    }
                    else 
                    {
                        printf("nodeCheck FAILED.\n");
                        exit(0);
                    }
                }
            }
            continue;
        }
        
        // 2 people per day. -1 because sharing size = 3 and we make it 2
        for(int i = 0; i < (eventSharingSize - 1); i++) 
        {
            int flag = 1;
            int randomIdx;
            while(flag == 1)
            {
                //printf("Attempting to get random idx number...\n");
                randomIdx = getRandomIdx(lowerIdx,higherIdx); // 0 - 32
                //printf("randomIdx: %d\n", randomIdx);

                int numToDeleteOrAdd = deleteElementFromArray(participantIdx, randomIdx, idxArraySize);
                higherIdx--; // after we delete element in array, we decrease the highest value it can get a random idx from
                //printf("higheridx: %d\n", higherIdx);

                // check to see if it is in the available list, if it is, delete in idx array, avail ,and add it to removal list, else select a new rando idx
                bool nodeCheck = checkNode(availableListHead, numToDeleteOrAdd);

                if(nodeCheck == true)
                {
                    //printf("nodeCheck Passes for idx: \t%d which is: \t%d\n", randomIdx, numToDeleteOrAdd);
                    deleteNode(&availableListHead, numToDeleteOrAdd);
                    addNodeToEnd(&removalListHead, numToDeleteOrAdd);
                    strcpy(d[m].eventSharing[i], CNYParticipants[numToDeleteOrAdd]);

                    // //DEBUG - Checking the linked lists to see what is happening
                        // printf("Available List: \n");
                        // printList(availableListHead);
                        // printf("\n");
                        // printf("\n");
                        // printf("\n");
                        // printf("Removal List: \n");
                        // printList(removalListHead);
                        // printf("\n");
                        // printf("\n");
                        // printf("\n");
                        // printf("The name that was added: %s\n", d[p].eventSharing[i] );
                        // printf("\n ---------------------------------------------------------------------------------- \n");


                    flag = 0;
                }
                else 
                {
                    printf("nodeCheck FAILED.\n");
                    exit(0);
                }
            }
        }
    }   

    // //DEBUG - check to see if nothing in available list and all values used in removal list ~~ array index should be all 32's
    // printf("Available List: \n");
    // printList(availableListHead);
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("Removal List: \n");
    // printList(removalListHead);
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("Array Index: \n");
    // for(int lol = 0; lol  < idxArraySize; lol++)
    // {
    //     printf("%d\t", participantIdx[lol]);
    // }
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("\n");

    // for(int check = 0; check < numberOfDays; check++)
    // {
    //     printf("Day: %s\n", d[check].day);
    //     printf("Event Sharing Names: ");
    //     for(int i = 0; i < eventSharingSize; i++) 
    //     {
    //         printf("%s, ", d[check].eventSharing[i]);
    //     }
    //     printf("\n");
    //     printf("\n");
    //     printf("\n");
    // }
    


    // Reset all values before doing the next one
    // sorted array stays the same
    // higherIdx needs resetting as it was decremented to 0
    // global idxArray needs resetting and available/removal linked list
    higherIdx = 32;
    //setGlobalIdxArray();
    setLinkedListsAndIdxArray(availableListHead, removalListHead, numberOfParticipants);

    // for(int ck = 0; ck < numberOfParticipants; ck++)
    // {
    //     addNodeToEnd(&availableListHead, ck);

    // }
    // removalListHead = NULL;

    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("HigherIdx: %d\n", higherIdx);
    // printf("Available List: \n");
    // printList(availableListHead);
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("Removal List: \n");
    // printList(removalListHead);
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("Array Index: \n");
    // for(int lol = 0; lol  < idxArraySize; lol++)
    // {
    //     printf("%d\t", participantIdx[lol]);
    // }
    // printf("\n");

    // printf("\n\n\n\n\n");
    // printf("SECOND PHASE\n");
    // printf("\n\n\n\n\n");

    // printf("Array Index: \n");
    // for(int lol = 0; lol  < idxArraySize; lol++)
    // {
    //     printf("%d\t", participantIdx[lol]);
    // }

    // printf("\n");

    // printList(availableListHead);
    // printf("\n");
    // printList(removalListHead);
    // printf("\n");
    // printf("\n\n");


  

    // This will get us 5 different indexes where we can have max struct elements filled in the facebook sharing field

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
    higherIdx = 32;
    setLinkedListsAndIdxArray(availableListHead, removalListHead, numberOfParticipants);

    printf("randomNum1: %d\n", randomNumOne);
    printf("randomNum2: %d\n", randomNumTwo);
    printf("randomNum3: %d\n", randomNumThree);
    printf("randomNum4: %d\n", randomNumFour);
    printf("randomNum5: %d\n", randomNumFive);


    for (int p = 0; p < numberOfDays; p++)
    {

        //printf("Date: %s\n", d[p].day);

        if(p == 0 || p == 1) 
        {
            continue;
        }

        // fill struct for facebook sharing
        if(p == randomNumOne || p == randomNumTwo || p == randomNumThree || p == randomNumFour || p == randomNumFive) 
        {
            //printf("3 IN STRUCT\n");
            // if condition for 3 people in struct
            for(int i = 0; i < facebookFrameSize; i++) 
            {
                int flag = 1;
                int randomIdx;
                while(flag == 1)
                {
                    //printf("Attempting to get random idx number...\n");
                    randomIdx = getRandomIdx(lowerIdx,higherIdx); // 0 - 32
                    //printf("randomIdx: %d\n", randomIdx);

                    int numToDeleteOrAdd = deleteElementFromArray(participantIdx, randomIdx, idxArraySize);
                    higherIdx--; // after we delete element in array, we decrease the highest value it can get a random idx from
                    //printf("higheridx: %d\n", higherIdx);

                    // check to see if it is in the available list, if it is, delete in idx array, avail ,and add it to removal list, else select a new rando idx
                    bool nodeCheck = checkNode(availableListHead, numToDeleteOrAdd);

                    if(nodeCheck == true)
                    {
                        //printf("nodeCheck Passes for idx: \t%d which is: \t%d\n", randomIdx, numToDeleteOrAdd);
                        deleteNode(&availableListHead, numToDeleteOrAdd);
                        addNodeToEnd(&removalListHead, numToDeleteOrAdd);
                        strcpy(d[p].facebookFrame[i], CNYParticipants[numToDeleteOrAdd]);

                        // //DEBUG - Checking the linked lists to see what is happening
                        // printf("Available List: \n");
                        // printList(availableListHead);
                        // printf("\n");
                        // printf("\n");
                        // printf("\n");
                        // printf("Removal List: \n");
                        // printList(removalListHead);
                        // printf("\n");
                        // printf("\n");
                        // printf("\n");
                        // printf("The name that was added: %s\n", d[p].facebookFrame[i] );
                        // printf("\n ---------------------------------------------------------------------------------- \n");


                        flag = 0;
                    }
                    else 
                    {
                        printf("nodeCheck FAILED.\n");
                        exit(0);
                    }
                }
            }
            continue;

        }
    
        // fill struct for more than 2 people 
        else
        {
            // if condition for 2 people in struct
            for(int i = 0; i < (facebookFrameSize-1); i++) 
            {
                int flag = 1;
                int randomIdx;
                while(flag == 1)
                {
                    //printf("Attempting to get random idx number...\n");
                    randomIdx = getRandomIdx(lowerIdx,higherIdx); // 0 - 32
                    //printf("randomIdx: %d\n", randomIdx);

                    int numToDeleteOrAdd = deleteElementFromArray(participantIdx, randomIdx, idxArraySize);
                    higherIdx--; // after we delete element in array, we decrease the highest value it can get a random idx from
                    //printf("higheridx: %d\n", higherIdx);

                    // check to see if it is in the available list, if it is, delete in idx array, avail ,and add it to removal list, else select a new rando idx
                    bool nodeCheck = checkNode(availableListHead, numToDeleteOrAdd);

                    if(nodeCheck == true)
                    {
                        //printf("nodeCheck Passes for idx: \t%d which is: \t%d\n", randomIdx, numToDeleteOrAdd);
                        deleteNode(&availableListHead, numToDeleteOrAdd);
                        addNodeToEnd(&removalListHead, numToDeleteOrAdd);
                        strcpy(d[p].facebookFrame[i], CNYParticipants[numToDeleteOrAdd]);

                        // //DEBUG - Checking the linked lists to see what is happening
                        // printf("Available List: \n");
                        // printList(availableListHead);
                        // printf("\n");
                        // printf("\n");
                        // printf("\n");
                        // printf("Removal List: \n");
                        // printList(removalListHead);
                        // printf("\n");
                        // printf("\n");
                        // printf("\n");
                        // printf("The name that was added: %s\n", d[p].facebookFrame[i] );
                        // printf("\n ---------------------------------------------------------------------------------- \n");

                        flag = 0;
                    }
                    else 
                    {
                        printf("nodeCheck FAILED.\n");
                        exit(0);
                    }
                }
            }
        }
        
    }

    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("HigherIdx: %d\n", higherIdx);
    // printf("Available List: \n");
    // printList(availableListHead);
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("Removal List: \n");
    // printList(removalListHead);
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("Array Index: \n");
    // for(int lol = 0; lol  < idxArraySize; lol++)
    // {
    //     printf("%d\t", participantIdx[lol]);
    // }
    // printf("\n");
    
  

    // Printing out everything now to a txt file

    //DEBUG - see if all struct values print out
    for(int check = 0; check < numberOfDays; check++)
    {
        printf("Day: %s\n", d[check].day);
        printf("Event Sharing Names: ");
        for(int i = 0; i < eventSharingSize; i++) 
        {
            printf("%s, ", d[check].eventSharing[i]);
        }
        printf("\n");
        printf("Facebook Frame Names: ");
        for(int j = 0; j < facebookFrameSize; j++)
        {
            printf("%s, ", d[check].facebookFrame[j]);
        }
        printf("\n");
        printf("\n");
    }


    FILE *fp = fopen("Marketing Schedule.txt", "w");

    if(fp == NULL)
    {
        printf("Could not open file");
    }

    // 1 = true 0 = false
    int dayNumber = 0;
    int dateFlag = 1;
    int datePerson1 = 1;
    int datePerson2 = 0;
    int datePerson3 = 0;
    
    for(int s = 0; s < (2 + (4 * 17)); s++) //70
    {
        // I know this is long... I am not sure an equation that can simplify this pattern
        if(s == 0 || s == 2 || s == 6 || s == 10 ||
            s == 14 || s == 18 || s == 22 || s == 26 ||
            s == 30 || s == 34 || s == 38 || s == 42 ||
            s == 46 || s == 50 || s == 54 || s == 58 ||
            s == 62 || s == 66 || s == 70) 
        {
            fprintf(fp, "---------------------------------------------------------------------------------------");
            fprintf(fp, "\n");
            continue;
        }

        if(s == 1)
        {
            fprintf(fp, "%-10s | %-25s | %-25s", "Date", "Sharing Event", "Sharing Facebook Frame");
            fprintf(fp, "\n");
            continue;
        }

        // Flag check for if date needs to be implemented
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

    fclose(fp);

    return 0;
}