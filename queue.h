//Alp Kaan Özgül 2638096


//
// Created by alpka on 4.12.2023.
//

#ifndef UNTITLED12_QUEUE_H
#define UNTITLED12_QUEUE_H

#endif //UNTITLED12_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
struct worktask{   //node decleration
    int arrival_time;
    int service_time;
    int service_start_time;
    int id;
    char priority;
    struct worktask *next;
};

struct QueueRecord    //queue decleration
{
    struct worktask *front;
    struct worktask *rear;
    int size;

};


typedef struct QueueRecord *queue;

//here are the function declerations

struct worktask* parseInput(int argc, char *argv[]);
struct worktask* initialiseSimulator(int argc, char *argv[],struct worktask* l);
struct worktask* createTasksList(int noOfTasks,int noOfDevelopers,int maxArrivalTime,int maxServiceTime,struct worktask* l);
struct worktask* initializeList();
void newTask(struct QueueRecord* que,struct worktask*l);
void enqueue(struct QueueRecord* que, int arrival_time, int service_time, char priority, int id);
struct worktask* AccomplishTask(int* arr,struct QueueRecord* que,int no_of_devs,struct worktask* l);
void reportStatistics (struct worktask* returned_l,int argc, char *argv[]);
struct worktask* deque(struct QueueRecord* que,struct worktask* store_sended);



