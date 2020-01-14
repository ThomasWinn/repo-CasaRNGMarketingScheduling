

# How it works
I create a list of names and dates we want people to market our Chinese New Year event. I quickly sort the array in alphabetical order of names then I create the struct that will store all the information for each date needed. I have three arrays inside the struct, one contains the current day, and the other two arrays contain up to 3 names that tell the user who will share and/or add the Facebook frame. Shortly after I initialize two linked lists. One that is called availableList which stores all available names to use and removalList is a linked list full of names that have already been used. I would initialize the availableList by adding all names by their index inside the array, and the removalList is set to NULL. 

The process for assigning names to a date is as followed. When sharing the event, I would iterate through size of the array inside the struct. I would get a random index from 0 to (numberOfParticipants - 1) then would delete a number at that index inside the participantIdx array. The number that was deleted hold the person's name given by the keys inside the availableList Linked List. After checking that key exists inside the availableList, we delete it from there and add it to the removalList then copy the key's name into the array of the date currently at.

## How to use
This is particularly easy to use as it is easy to run.

'''
$ cd (PATH where the program can be found)/repo-CasaRNGMarketingScheduling
'''

From here, we will compile the code.

'''
$ gcc -o RNG main.c
'''

Then run it.

'''
$ ./RNG
'''

If it succeeds and runs everything successfully, nothing will pop up in terminal

However, If it is unsuccessful in compiling something you should 

'''
$ nodeCheck FAILED.
'''

### Editing the file for your use
When editing this file for your use, I tried to make it simple for you to follow along.
In the commented sections of this code I allowed you to see the key word 'EDITABLE.'

'CTRL-F or COMMAND-F' to find all sections for you to edit.

If you have troubles with editing, send an issue post to me :blush: 




