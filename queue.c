//Alp Kaan Özgül 2638096

#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct worktask* parseInput(int argc, char *argv[]){
    // this function Parses command-line arguments and returnes the linked list of tasks which are ordered in ascending order of arrival times
    int noOfTasks = atoi(argv[1]);
    int noOfDevelopers = atoi(argv[2]);
    int maxArrivalTime = atoi(argv[3]);
    int maxServiceTime = atoi(argv[4]);


    struct worktask* l= initializeList(); //here it initializes an empty linked list
    struct worktask* trav_l=l;

    return createTasksList(noOfTasks,noOfDevelopers,maxArrivalTime,maxServiceTime,l);


}
struct worktask* initializeList(){ //this function is for creation of an empty linked list first it allocates memory for worktask type pointer and set it's next pointer to NULL

    struct worktask* l = (struct worktask*) malloc(sizeof (struct worktask));
    if (l==NULL){
        printf("out of memory");
    }
    l->next=NULL;
    return l;
}
struct worktask* createTasksList(int noOfTasks, int noOfDevelopers, int maxArrivalTime, int maxServiceTime, struct worktask* l){
    srand(time(NULL));
    struct worktask* current = l;
    struct worktask* prev = NULL;

    for(int x =0;x<noOfTasks;x++){
        struct worktask* newnode = (struct worktask*)malloc(sizeof(struct worktask));
        newnode->next=NULL;

        // Generate random value between 1 and maxArrivalTime - 1
        newnode->arrival_time = rand() % (maxArrivalTime - 1) + 1;
        newnode->service_time = rand() % (maxServiceTime - 1)+1;
        newnode->id = 0;
        newnode->service_start_time = 0;
        int randomIndex = rand() % 4;
        char chars[] = {'C', 'H', 'M', 'N'};
        newnode->priority = chars[randomIndex];

        current = l->next;
        prev = l;

        while (current != NULL && current->arrival_time <= newnode->arrival_time) {  // here also it makes sure that if first node after// dummy node's arrival time is >newnode arrival time
            // it breaks and inserts at the begininng (dummy->next)
            // or last node has smaller value then the new added it adds at current-> next by this we can make sure that it is in ascending order
            prev = current;
            current = current->next;
        }

        prev->next = newnode;
        newnode->next = current;
    }



    return l;

}




struct worktask* initialiseSimulator(int argc, char *argv[],struct worktask* l){

    queue q = (struct QueueRecord*) malloc(sizeof (struct QueueRecord));  //here memmory is allocated for the queue
    struct worktask* returned_list;
    if (q == NULL){
        printf("out of memory");
    }
    q->size =0;
    q->front = (struct worktask*)malloc(sizeof (struct worktask));    //here memory allocated for que's worktask type pointer
    q->front->next = NULL;
    q->rear = q->front;

    int size = atoi(argv[2]);

    int *arr = malloc(size * sizeof(int));    //here is array created and memory allocated for the delevoper amount
    if (arr==NULL){
        printf("out of memory");
    }


    for(int x =0;x<size;x++){
        arr[x]= 1;                   //here is array is firstly assigned to 1 this indicates that the all developer's are available
    }

    newTask(q,l);                   //here is the que and linked list which is in ascending order is passed to the function to add new tasks to queue in priority order

    struct worktask* return_1;
    return_1 = AccomplishTask(arr,q,size,l);   //here in this function the availability of programmers array, the queue which is ordered by the priority, amount of programmer,
    //the linked list which has arrival in ascending order is passed to process and this function will inside execute few function's and it will return a newly linked list
    //inorder to be processed for the reporting statistics.


    return return_1;
}


void newTask(struct QueueRecord* que, struct worktask* l) {

    struct worktask* current = l->next;

    while (current != NULL) {
        // Enqueue the tasks into the queue based on their arrival time
        enqueue(que, current->arrival_time, current->service_time, current->priority, current->id);
        current = current->next;
    }
}

void enqueue(struct QueueRecord* que, int arrival_time, int service_time, char priority, int id) {
    struct worktask* newnode = (struct worktask*)malloc(sizeof(struct worktask));     //here is memory allocated for the new node that will be added to the que
    if (newnode == NULL) {
        printf("out of memory");
        return;
    }

    newnode->arrival_time = arrival_time;                           //here is newnode's data is added
    newnode->service_time = service_time;
    newnode->priority = priority;
    newnode->id = id;
    newnode->service_start_time = 0;
    newnode->next = NULL;

    // Find the correct position to insert based on priority in the opposite order
    struct worktask* current = que->front;
    while (current->next != NULL && current->next->priority >= priority) {
        current = current->next;
    }

    newnode->next = current->next;
    current->next = newnode;

    // If the new node is added at the end, update rear
    if (newnode->next == NULL) {
        que->rear = newnode;
    }

    que->size++;
}
struct worktask* AccomplishTask(int* arr,struct QueueRecord* que,int no_of_devs,struct worktask* l) {

    struct worktask *traverse = que->front->next;   //some pointers to traverse the data to test the list,queue
    struct worktask *traverse1 = que->front->next;

    struct worktask *deque_return;                                   // 3 1 8 7 9
    int inital =0;

    struct worktask* travlistadd2 =l->next;
    struct worktask* store_sended = (struct worktask*) malloc(sizeof (struct worktask));//dummy node
    if(store_sended==NULL){
        printf("out of memory");
    }
    store_sended->next=NULL;



    struct worktask* processedlinkedlist = (struct worktask*)malloc(sizeof (struct worktask)); //dummy node for processed nodes
    struct worktask* head_processed = processedlinkedlist;
    struct worktask* trav_head = head_processed;
    trav_head->next=NULL;


    // x x x x x                       x    x x x x

    //in this while loop it will continue to loop untill no task is left in the que
    while(que->size!=1){

        int smallest = 0;
        int availability_count=0;

        // Initialize smallest outside the loop
        struct worktask* smallest_node;
        for(int c =0;c<no_of_devs;c++){
            if(arr[c]==1){
                availability_count++;
            }
        }
        //to update and track the que->rear in each itaration to understand which task is processed
        for (int x = 0; x < availability_count; x++) {
            que->rear->id = x+1;
            arr[x] = 0;
            if (smallest==0){
                smallest = que->rear->service_time;
                smallest_node = que->rear;
            }
            deque_return = deque(que,store_sended);  //this function will decrease que->rear and return the node which is being  processed in each iteration

            if (deque_return->service_time < smallest  ) {

                smallest = deque_return->service_time;
                smallest_node = deque_return;
            }
        }

        struct worktask* newnode_add = (struct worktask*)malloc(sizeof(struct worktask));
        if(newnode_add==NULL){
            printf("out of memory");
        }
        //in here returned node from deque function will be copied to a new node and be added at the linked list in order to report statistics
        newnode_add->service_time =smallest_node->service_time;
        newnode_add->id=smallest_node->id;
        newnode_add->arrival_time=smallest_node->arrival_time;
        newnode_add->priority=smallest_node->priority;
        newnode_add->service_start_time =smallest_node->service_start_time;
        newnode_add->next=NULL;
        while (trav_head->next !=NULL){
            trav_head = trav_head->next;
        }
        trav_head->next = newnode_add;

        arr[(smallest_node->id)-1]=1;

    }
    return store_sended;
}

struct worktask* deque(struct QueueRecord* que,struct worktask* store_sended){

    struct worktask* prev_rear = que->front->next;
    struct worktask* node_return;
    for (int i =0;i<(que->size)-2;i++){    //this for loop will find the previous of the last node inorder to remove from last
        prev_rear=prev_rear->next;

    }
    // x x x x x
    //here it will update some data of the queue
    node_return = prev_rear->next;
    prev_rear->next=NULL;
    que->rear = prev_rear;
    que->size--;

    //here it will copy the processed node to a newnode to add in processed task linked list
    struct worktask* store_sended_newnode = (struct worktask*)malloc(sizeof (struct worktask));

    store_sended_newnode->service_time=node_return->service_time;
    store_sended_newnode->arrival_time=node_return->arrival_time;
    store_sended_newnode->id=node_return->id;
    store_sended_newnode->priority=node_return->priority;
    store_sended_newnode->service_start_time=node_return->service_start_time;
    store_sended_newnode->next=NULL;
    struct worktask* head_sotre_sended =store_sended;
    while(head_sotre_sended->next!=NULL){
        head_sotre_sended=head_sotre_sended->next;
    }

    head_sotre_sended->next=store_sended_newnode;

    return node_return;

}







void reportStatistics (struct worktask* returned_l,int argc, char *argv[]){
    printf("\n****************Report*****************\n");
    printf("The number of Developers is: %d\n",atoi(argv[2]));
    printf("The number of Tasks: %d\n", atoi(argv[1]));
    printf("Number of Tasks for each Label:\n");
    struct worktask* trav_list2 = returned_l->next;
    while (trav_list2!=NULL){
        printf("Priority is: %c\n",trav_list2->priority);
        trav_list2=trav_list2->next;
    }
    //here it will traverse the processed task linked list and incriment the counters acording the amount of different priorities
    int c=0,h=0,m=0,n=0;
    struct worktask* trav_list = returned_l->next;
    while(trav_list!=NULL){
        if(trav_list->priority=='C'){
            c++;
        }
        else if(trav_list->priority=='H'){
            h++;
        }
        else if(trav_list->priority=='M'){
            m++;
        }
        else if(trav_list->priority=='N'){
            n++;
        }

        trav_list=trav_list->next;
    }
    printf("Crictical: %d\nHigh Priority: %d\nMedium: %d\nNormal: %d\n",c,h,m,n);
    printf("\nNumber of Tasks for each Developer:\n");

    //here new array is created inorder to clearly see which task has which id
    int dev_task[atoi(argv[2])];
    for(int r=0;r<atoi(argv[2]);r++){
        dev_task[r]=0;
    }
    //traverses the processed task linked list and if a matching id is found the amount of task for that developer will be increased
    struct worktask* trav_dev_task = returned_l->next;
    while(trav_dev_task!=NULL){
        for(int y=0;y<atoi(argv[2]);y++){
            if(y+1== trav_dev_task->id){
                dev_task[y] =dev_task[y]+1;
            }
        }

        trav_dev_task=trav_dev_task->next;
    }
    for(int x=0;x<atoi(argv[2]);x++){
        printf("Developer %d Accomplished; %d\n",x+1,dev_task[x]);
    }
    struct worktask* completion = returned_l;
    int completion_tot =0;
    while(completion!=NULL){
        completion_tot= completion_tot +completion->service_time;
        completion=completion->next;
    }
    printf("\nCompletion time: %d\n",completion_tot);
    printf("\nAverage time spent in the queue: %d\n",completion_tot/atoi(argv[1]));
    struct worktask* maxwait = returned_l->next;

    int max =0;
    while(maxwait->next!=NULL){
        if (max<maxwait->service_time || max ==0){
            max = maxwait->service_time;
        }
        maxwait=maxwait->next;
    }
    printf("Maximum waiting time:%d\n",max);
}

