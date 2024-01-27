//Alp Kaan Özgül 2638096

#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//in queue.c source code every function is ordered in the rightway inorder to make it easy to trace

int main(int argc, char *argv[]) {
    struct worktask* l;
    struct worktask* returned_l;

    struct QueueRecord* que;
    l = parseInput(argc,argv); // this function parses the input from argument and when the function is executed few
    // other functions are executed at the end it returns a linked list which is in ascending order of arrival time
    returned_l = initialiseSimulator(argc,argv,l); //this function creates queue and processes the linked list and que with the
    // few of other functions at the end it returnes a processed task's linked list inorder to report the statistics
    printf("test1");

    reportStatistics(returned_l,argc,argv); //this function gets the processed linked list and at the end reports the statistics
    printf("test");


    return 0;
}














