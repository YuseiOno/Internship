CC=gcc


all: edge

edge : edge.c imgfunc.o
	 $(CC) -o $@  $^ 

%.o:%c
	$(CC) -c $< 


clean:
	$(RM) *.o *~

