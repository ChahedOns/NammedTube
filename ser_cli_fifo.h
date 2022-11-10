#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

const int NMAX=10;

// FIFO file path
const char * fifo1 = "./fifo1";
const char * fifo2 = "./fifo2";
// Creating the named file(FIFO)
int f1 = mkfifo(fifo1,S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH);
int f2 = mkfifo(fifo2,S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH);

// Structs

typdef struct request
{
	int id; 
	int n;
};
typdef struct request request; 

typdef struct response
{
	int idc;
	int ids;
	int * t ;
};
typdef struct response response; 
