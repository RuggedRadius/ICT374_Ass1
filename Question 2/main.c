/* name:          memory.c
 * aims:          to see how the compiler allocates memory to each region of
 *                the process (user visible part), including text region (program instructions), 
 *                data region, heap, stack, command line arguments and process environment region

 * author:        HX
 * updated: 	  2023.08.31
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>

extern char **environ;

int gx = 10;   // initialised global
int gy;  // uninitialised global
char gname1[] = "Hi, there!";
char *gname2  = "Computer Science";  
const int gc = 100;
int gz;

void printAddress(char *description, void *addr)
{
    unsigned long a = (unsigned long) addr;

    unsigned long b  = a & 0x3ff;
    unsigned long kib = a >> 10; kib = kib & 0x3ff;
    unsigned long mib = a >> 20; mib = mib & 0x3ff;
    unsigned long gib = a >> 30; gib = gib & 0x3ff;
    unsigned long tib = a >> 40; tib = tib & 0x3ff;
    printf("%70s: %16p (%luTiB, %luGiB, %luMiB, %luKiB, %luB)\n", description, addr, tib, gib, mib, kib, b);

    return;
}

int f1(int x1, int x2, float x3, double x4, char x5, int x6 )
{
    int     f1_l1;
    float   f1_l2;
    char    f1_l3;
    char    f1_l3b;
    double  f1_l4;
    int     f1_l5;
    int     f1_l6;

    // TO DO: 
    // print the addresses of all formal parameters of function f1
    printf("Formal parameters of function f1:\n");
    printf("x1 = %p\n", &x1);
    printf("x2 = %p\n", &x2);
    printf("x3 = %p\n", &x3);
    printf("x4 = %p\n", &x4);
    printf("x5 = %p\n", &x5);
    printf("x6 = %p\n", &x6);
    
    // print the addresses of all local variables of function f1
    printf("Local variables of function f1:\n");
    printf("f1_l1 = %p\n", &f1_l1);
    printf("f1_l2 = %p\n", &f1_l2);
    printf("f1_l3 = %p\n", &f1_l3);
    printf("f1_l3b = %p\n", &f1_l3b);
    printf("f1_l4 = %p\n", &f1_l4);
    printf("f1_l5 = %p\n", &f1_l5);
    printf("f1_l6 = %p\n", &f1_l6);

    return 0;
}

void f2()
{
    #define BUFSIZE 1024*1024
    char buf[BUFSIZE];
    char *p;
    p = malloc(BUFSIZE);
    if (p==NULL) {
         perror("mallc memory");
         exit(1);
    }

    // TO DO: 
    // print the addresses of local variables buf and p of function f2
    printf("Local variables of function f2:\n");
    printf("buf = %p", &buf);
    printf("p = %p", &p);

    // print the addresses of heap allocated memory pointed to by p in function f2
    printf("Heap allocated memory pointed to by p in function f2:\n");
    printf("buf = %p", &buf); // CONFIRM THIS!!!!!!!!! *****************************************************************************************************************************
    printf("p = %p", &p);

    printf("\n==== call function f1 in function f2  ====\n");
    f1(10, 20, 10.2, 20.3, 'a', 100);

    return;
}

int main(int argc, char *argv[], char *env[])
{
    printf("==== program text ====\n");
    printAddress("start address of function printAddress", printAddress);
    // TO DO: 
    // print the addresses of function f1, f2 and main
    printf("f1 = %p\n", &f1);
    printf("f1 = %p\n", &f2);
    printf("f1 = %p\n", &main);

    printf("\n==== constants and initialised globals ====\n");
    // TO DO: 
    // print the addresses of constant gc and string literal "Computer Science"
    printf("gc = %p\n", &gc);
    printf("gname2 = %p\n", &gname2);

    // print the addresses of initialised global variables gx, gname1, gname2 
    printf("gx = %p\n", &gx);
    printf("gname1 = %p\n", &gname1);
    printf("gname2 = %p\n", &gname2);
 
    printf("\n==== uninitialised globals ====\n");
    // print the addresses of uninitialised global variables gy, gz
    printf("gy = %p\n", &gy);
    printf("gz = %p\n", &gz);

    printf("\n==== formal parameters in function main ====\n");
    // TO DO:
    // print the addresses of formal parameters argv, argv and env
    printf("argc = %p\n", &argc);
    printf("argv = %p\n", &argv);
    printf("env = %p\n", &env);
 
    printf("\n==== heap ====\n");
    char *p1 = malloc(200);
    char *p2 = malloc(10000);

    printf("\n==== local variables in main ====\n");
    // TO DO:
    // print the addresses of local variables p1, p2
    printf("p1 = %p\n", &p1);
    printf("p2 = %p\n", &p2);
 
    printf("\n==== heap ====\n");
    // TO DO:
    // print the addresses of heap allocated memmory pointed to by p1 and p2

    printf("\n==== call function f2 from main function ====\n");
    f2();

    printf("\n==== arrays of pointers to cmd line arguments and env variables ====\n");
    // TO DO:
    // print the addresses of arrays of pointers point to cmd line arguments and env variables 

    printf("\n==== command line arguments ====\n");
    // TO DO:
    // print start and end addresses of cmd line arguments 

    printf("\n==== environment ====\n");
    // TO DO:
    // print start and end addresses of environment variables 

    exit(0);
}