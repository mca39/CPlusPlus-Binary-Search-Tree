###############################################################
# Program:
#     Week 09, Binary Search Tree
#     Brother Ercanbrack, CS235
# Author:
#     Mariah Ashley
# Summary:
#     This program creates a binary search tree which is 
#     implemented in the sort binary function
# Time:
#     <how long did it take to complete this program>? 7 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week09.o
	g++ -o a.out week09.o
	tar -cf week09.tar *.h *.cpp makefile

##############################################################
# The individual components
#      lesson08.o     : the driver program
##############################################################
week09.o: bnode.h bst.h stack.h week09.cpp sortBinary.h
	g++ -c week09.cpp

##############################################################
#clean up
##############################################################
clean:
	rm a.out *.o *.tar

