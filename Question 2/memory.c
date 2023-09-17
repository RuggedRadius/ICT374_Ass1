/* name:          memory.c
 * aims:          to see how the compiler allocates memory to each region of
 *                the process (user-visible part), including text region (program instructions), 
 *                data region, heap, stack, command line arguments, and process environment region
 *
 * author:        HX
 * updated:       2023.08.31
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>

extern char **environ;

int gx = 10;                  // initialized global
int gy;                        // uninitialized global
char gname1[] = "Hi, there!";
char *gname2 = "Computer Science";
const int gc = 100;
int gz;

void printAddress(char *description, void *addr)
{
    unsigned long a = (unsigned long)addr;

    unsigned long b = a & 0x3ff;
    unsigned long kib = a >> 10;
    kib = kib & 0x3ff;
    unsigned long mib = a >> 20;
    mib = mib & 0x3ff;
    unsigned long gib = a >> 30;
    gib = gib & 0x3ff;
    unsigned long tib = a >> 40;
    tib = tib & 0x3ff;
    printf("%70s: %16p (%luTiB, %luGiB, %luMiB, %luKiB, %luB)\n", description, addr, tib, gib, mib, kib, b);

    return;
}

int f1(int x1, int x2, float x3, double x4, char x5, int x6)
{
    int f1_l1;
    float f1_l2;
    char f1_l3;
    char f1_l3b;
    double f1_l4;
    int f1_l5;
    int f1_l6;

    printf("\n==== formal parameters in function f1 ====\n");
    // TO DO: 
    // print the addresses of all formal parameters of function f1
    printAddress("x1", &x1);
    printAddress("x2", &x2);
    printAddress("x3", &x3);
    printAddress("x4", &x4);
    printAddress("x5", &x5);
    printAddress("x6", &x6);

    printf("\n==== local variables in function f1 ====\n");
    // TO DO:
    // print the addresses of all local variables of function f1
    printAddress("f1_l1", &f1_l1);
    printAddress("f1_l2", &f1_l2);
    printAddress("f1_l3", &f1_l3);
    printAddress("f1_l3b", &f1_l3b);
    printAddress("f1_l4", &f1_l4);
    printAddress("f1_l5", &f1_l5);
    printAddress("f1_l6", &f1_l6);

    return 0;
}

void f2()
{
    #define BUFSIZE 1024*1024
    char buf[BUFSIZE];
    char *p;
    p = malloc(BUFSIZE);
    if (p == NULL)
    {
        perror("malloc memory");
        exit(1);
    }

    printf("\n==== local variables in function f2 ====\n");
    // TO DO: 
    // print the addresses of local variables buf and p of function f2
    printAddress("buf", &buf);
    printAddress("p", &p);

    printf("\n==== heap ====\n");
    // TO DO: 
    // print the addresses of heap allocated memory pointed to by p in function f2
    printAddress("Heap memory (p)", p);

    printf("\n==== call function f1 in function f2  ====\n");
    f1(10, 20, 10.2, 20.3, 'a', 100);

    return;
}

int main(int argc, char *argv[], char *env[])
{
    printf("==== program text ====\n");
    printAddress("start address of function printAddress", printAddress);
    // TO DO: 
    // print the addresses of function f1, f2, and main
    printAddress("main", main);
    printAddress("f1", f1);
    printAddress("f2", f2);

    printf("\n==== constants and initialized globals ====\n");
    // TO DO: 
    // print the addresses of constant gc and string literal "Computer Science"
    // print the addresses of initialized global variables gx, gname1, gname2 
    printAddress("gc", (void *)&gc);
    printAddress("gname2", &gname2);
    printAddress("gx", &gx);
    printAddress("gname1", gname1);

    printf("\n==== uninitialized globals ====\n");
    // print the addresses of uninitialized global variables gy, gz
    printAddress("gy", &gy);
    printAddress("gz", &gz);

    printf("\n==== formal parameters in function main ====\n");
    // TO DO:
    // print the addresses of formal parameters argv, argv, and env
    printAddress("argc", &argc);
    printAddress("argv", argv);
    printAddress("env", env);

    printf("\n==== heap ====\n");
    char *p1 = malloc(200);
    char *p2 = malloc(10000);

    printf("\n==== local variables in main ====\n");
    // TO DO:
    // print the addresses of local variables p1, p2
    printAddress("p1", p1);
    printAddress("p2", p2);

    printf("\n==== heap ====\n");
    // TO DO:
    // print the addresses of heap-allocated memory pointed to by p1 and p2
    printAddress("Heap memory (p1)", p1);
    printAddress("Heap memory (p2)", p2);

    printf("\n==== call function f2 from the main function ====\n");
    f2();

    printf("\n==== arrays of pointers to cmd line arguments and env variables ====\n");
    // TO DO:
    // print the addresses of arrays of pointers pointing to cmd line arguments and env variables
    printAddress("argv", argv);
    printAddress("env", env);

    printf("\n==== command line arguments ====\n");
    // TO DO:
    // print start and end addresses of cmd line arguments
    printAddress("argv[0]", argv[0]);
    printAddress("argv[argc-1]", argv[argc - 1]);

    printf("\n==== environment ====\n");
    // TO DO:
    // print start and end addresses of environment variables
    printAddress("env[0]", env[0]);
    printAddress("env[1]", env[1]);

    exit(0);
}
