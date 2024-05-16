# This sample Makefile allows you to make an OpenGL application
#   whose source is exactly one .c file.
#
#
# To use this Makefile, you type:
#
#        make xxxx
#                  
# where
#       xxxx.c is the name of the file you wish to compile 
#       
# A binary named xxxx will be produced
# Libraries are assumed to be in the default search paths
# as are any required include files
#
# For linux replace the next line with
# CC =  gcc
# and you may have to add -L/usr/X11R6/lib to LDLIBS

CC = cc 

LDLIBS = -lglut -lGL -lGLU -lXmu -lX11  -lm

.c:
	$(CC)  $@.c $(LDLIBS) -o $@

