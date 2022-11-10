#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

// FIFO file path
//const char * fifo1 = "./fifo1";
//const char * fifo2 = "./fifo2";
// Creating the named file(FIFO)
#define FILE1 "fifo1"
#define FILE2 "fifo2"
#define NMAX 100
// Structs

struct request
{
	int id; 
	int n;
};
struct response
{
	int idc;
	int ids;
	int t[];
};
