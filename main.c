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
    printf("��������̵�����: ");
    scanf("%d",&processNum);
    Process *process = (Process *)malloc(sizeof(Process) * processNum);
    memset(process,0,sizeof(Process) * processNum);
    for(i = 0;i < processNum;i++) {
        printf("��������̵�����: ");
        scanf(" %c",&(process[i].id));
        printf("��������̵ĵ���ʱ��: ");
        scanf("%d",&(process[i].arriveTime));
        printf("��������̵ķ���ʱ��: ");
        scanf("%d",&(process[i].serviceTime));
        process[i].remainServiceTime = process[i].serviceTime;
        printf("��������̵����ȼ�: ");
        scanf("%d",&(process[i].priority));
    }
    int choice;
    InitQueue(&readyQueue);
    InitQueue(&printQueue);
    InitLinkedList(&linkedList);
    printf("��������Ҫѡ��ĵ����㷨: ");
    printf("1.�����ȷ���  2.����ҵ����  3.ʱ��Ƭ��ת  4.���ȼ�����  5.end\n");
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
            printf("ȫ��������ִ�н���\n");
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
            printf("ȫ��������ִ�н���\n");
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
    printf("������ʱ��Ƭ�Ĵ�С: ");
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
            printf("ȫ��������ִ�н���\n");
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
            printf("ȫ��������ִ�н���\n");
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