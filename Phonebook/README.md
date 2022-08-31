# PhoneBook

A short program that receives input and adds, removes, or finds it from the current registry. 
The input parameters to add a phonebook registry has to be in the following order: ACTION ID NAME AGE. An example would be; ADD 334 Sal Alhudais 32

FIND FUNCTION has three comparison operators; < > = and can be called the same way as ADD: FIND NAME OPERATOR INSERTCOMPARISON --------->> an example would be: FIND name = "Sal Alhudais"

REMOVE operator follows the same pattern. 

You call STOP when you want to exit the program and have all of your previous input saved into a file. This file can then be accessed automatically the next time you open the program(assuming you don't change the name from what it is currently or can manually change it through the DiskManagement class.
