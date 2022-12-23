#**************This is a simple way***********

# Declaring the path of source
# DIR := c_makefile/another
# final:	# Run the another task with the command below
# 	gcc $(DIR)/degree.c -o final

# Method 2
# gcc = gcc
# method:
# 	gcc $(DIR)/degree.c -o method


# Syntax:
# label: <dependency>
#	command

# date folder path
DIR_DATE := c_makefile/date/
DIR := c_makefile/another/

# Label:	<dependency object files>
project:	degree.o	date.o
	gcc degree.o date.o -o project

# create date object file
date.o: $(DIR_DATE)/date.h $(DIR_DATE)/date.c
	gcc -c $(DIR_DATE)/date.c

degree.o: $(DIR)/degree.c
	gcc -c $(DIR)degree.c 

# Cleaning file
clean:
	rm *.o project
