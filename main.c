#include "queue.h"
#include <string.h>

void Panel();
void FCFS(Queue *rq,Queue *pq,Process pro[],int proNum);
void SJF(LinkedList *list,Queue *pq,Process pro[],int proNum);
void RR(Queue *rq,Queue *pq,Process pro[],int proNum);
void PSA(LinkedList *list,Queue *pq,Process pro[],int proNum);

int main(void) {
    Panel();
    return 0;
}

void Panel() {
    int processNum = 0;
    int i;
    LinkedList linkedList;
    Queue readyQueue;
    Queue printQueue;
    printf("请输入进程的数量: ");
    scanf("%d",&processNum);
    Process *process = (Process *)malloc(sizeof(Process) * processNum);
    memset(process,0,sizeof(Process) * processNum);
    for(i = 0;i < processNum;i++) {
        printf("请输入进程的名称: ");
        scanf(" %c",&(process[i].id));
        printf("请输入进程的到达时间: ");
        scanf("%d",&(process[i].arriveTime));
        printf("请输入进程的服务时间: ");
        scanf("%d",&(process[i].serviceTime));
        process[i].remainServiceTime = process[i].serviceTime;
        printf("请输入进程的优先级: ");
        scanf("%d",&(process[i].priority));
    }
    int choice;
    InitQueue(&readyQueue);
    InitQueue(&printQueue);
    InitLinkedList(&linkedList);
    printf("请输入你要选择的调度算法: ");
    printf("1.先来先服务  2.短作业优先  3.时间片轮转  4.优先级调度  5.end\n");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            FCFS(&readyQueue, &printQueue, process, processNum);
            break;
        case 2:
            SJF(&linkedList, &printQueue, process, processNum);
            break;
        case 3:
            RR(&readyQueue, &printQueue, process, processNum);
            break;
        case 4:
            PSA(&linkedList, &printQueue, process, processNum);
            break;
        case 5: printf("quit");
            break;
        default: printf("error!");
            break;
    }
    DestroyQueue(&readyQueue);
    DestroyQueue(&printQueue);
    DestroyLinkedList(&linkedList);
}

void FCFS(Queue *rq,Queue *pq,Process pro[],int proNum) {
    int processNum = proNum;
    int currentTime = 0;
    while(true) {
        int i;
        for(i = 0;i < proNum;i++) {
            if(pro[i].arriveTime == currentTime) {
                EnQueue(rq,pro[i]);
                processNum -= 1;
            }
        }
        if(IsQueueEmpty(rq) && processNum == 0) {
            printQueue(pq);
            printf("全部进程已执行结束\n");
            break;
        }
        if(!IsQueueEmpty(rq) && GetFront(rq)->data.remainServiceTime == 0) {
            GetFront(rq)->data.finishTime = currentTime;
            EnQueue(pq,GetFront(rq)->data);
            DeQueue(rq);
        }
        if(!IsQueueEmpty(rq)) {
            GetFront(rq)->data.remainServiceTime -= 1;
        }
        currentTime += 1;
    }
}

void SJF(LinkedList *list,Queue *pq,Process pro[],int proNum) {
    int currentTime = 0;
    int processNum = proNum;
    Node *current = NULL;
    Node *shortest = NULL;
    while(true) {
        int i;
        for(i = 0;i < proNum;i++) {
            if(pro[i].arriveTime == currentTime) {
                AddNode(list,pro[i]);
                processNum -= 1;
            }
        }
        if(IsListEmpty(list) && processNum == 0) {
            printQueue(pq);
            printf("全部进程已执行结束\n");
            break;
        }
        if(shortest != NULL && (shortest->data).remainServiceTime == 0) {
            (shortest->data).finishTime = currentTime;
            EnQueue(pq,shortest->data);
            DeleteNode(list,shortest);
            shortest = NULL;
        }
        if(!IsListEmpty(list) && shortest == NULL) {
            current = list->head;
            while(current != NULL) {
                if(shortest == NULL || current->data.serviceTime < shortest->data.serviceTime) {
                    shortest = current;
                }
                current = current->next;
            }
        }
        if(shortest != NULL) {
            shortest->data.remainServiceTime -= 1;
        }
        currentTime++;
    }
}

void RR(Queue *rq,Queue *pq,Process pro[],int proNum) {
    int processNum = proNum;
    int currentTime = 0;
    int timeSlice = 0;
    int remainSlice = 0;
    printf("请输入时间片的大小: ");
    scanf("%d",&timeSlice);
    while(true) {
        int i;
        for(i = 0;i < proNum;i++) {
            if(pro[i].arriveTime == currentTime) {
                EnQueue(rq,pro[i]);
                processNum -= 1;
            }
        }
        if(IsQueueEmpty(rq) && processNum == 0) {
            printQueue(pq);
            printf("全部进程已执行结束\n");
            break;
        }
        if(remainSlice == 0) {
            if(!IsQueueEmpty(rq) && GetFront(rq)->data.remainServiceTime == 0) {
                GetFront(rq)->data.finishTime = currentTime;
                EnQueue(pq,GetFront(rq)->data);
                DeQueue(rq);
            }
            else {
                if(!IsQueueEmpty(rq) && (GetFront(rq)->data.remainServiceTime != GetFront(rq)->data.serviceTime)) {
                    rq->rear->next = rq->front;
                    rq->rear = rq->rear->next;
                    rq->front = rq->front->next;
                    rq->rear->next = NULL;
                }
            }
            remainSlice = timeSlice;
        }
        else {
            if(!IsQueueEmpty(rq) && GetFront(rq)->data.remainServiceTime == 0) {
                GetFront(rq)->data.finishTime = currentTime;
                EnQueue(pq,GetFront(rq)->data);
                DeQueue(rq);
                remainSlice = timeSlice;
            }
        }
        if(!IsQueueEmpty(rq)) {
            GetFront(rq)->data.remainServiceTime -= 1;
        }
        remainSlice -= 1;
        currentTime += 1;
    }
}

void PSA(LinkedList *list,Queue *pq,Process pro[],int proNum) {
    int currentTime = 0;
    int processNum = proNum;
    Node *current = NULL;
    Node *shortest = NULL;
    while(true) {
        int i;
        for(i = 0;i < proNum;i++) {
            if(pro[i].arriveTime == currentTime) {
                AddNode(list,pro[i]);
                processNum -= 1;
            }
        }
        if(IsListEmpty(list) && processNum == 0) {
            printQueue(pq);
            printf("全部进程已执行结束\n");
            break;
        }
        if(shortest != NULL && (shortest->data).remainServiceTime == 0) {
            (shortest->data).finishTime = currentTime;
            EnQueue(pq,shortest->data);
            DeleteNode(list,shortest);
            shortest = NULL;
        }
        if(!IsListEmpty(list) && shortest == NULL) {
            current = list->head;
            while(current != NULL) {
                if(shortest == NULL || current->data.priority < shortest->data.priority) {
                    shortest = current;
                }
                current = current->next;
            }
        }
        if(shortest != NULL) {
            shortest->data.remainServiceTime -= 1;
        }
        currentTime += 1;
    }
}