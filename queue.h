#include "linkedlist.h"

#ifndef PROCESSSCHEDULING_QUEUE_H
#define PROCESSSCHEDULING_QUEUE_H

#endif //PROCESSSCHEDULING_QUEUE_H

typedef struct Queue {
    Node* front;
    Node* rear;
    int length;
}Queue;

void InitQueue(Queue *queue) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->length = 0;
}

void DestroyQueue(Queue *queue) {
    Node* current = NULL;
    Node* delnode = NULL;
    if(queue->front == NULL) {
        return;
    }
    current = queue->front;
    while(current != NULL) {
        delnode = current;
        current = current->next;
        free(delnode);
        delnode = NULL;
    }
}

bool IsQueueEmpty(Queue *queue) {
    return queue->front == NULL;
}

int QueueLength(Queue *queue) {
    return queue->length;
}

void EnQueue(Queue *queue,Process data) {
    Node* temp = CreateNode(data);
    if(queue->front == NULL) {
        queue->front = temp;
        queue->rear = temp;
        queue->length += 1;
    }
    else {
        queue->rear->next = temp;
        queue->rear = queue->rear->next;
        queue->length += 1;
    }
}

void DeQueue(Queue *queue) {
    Node *delnode = NULL;
    if(queue->front == NULL) {
        return;
    }
    delnode = queue->front;
    queue->front = queue->front->next;
    free(delnode);
    delnode = NULL;
    queue->length -= 1;
}

Node* GetFront(Queue *queue) {
    return queue->front;
}

void printQueue(Queue *queue) {                     
    Node* current = NULL;
    Node* next = NULL;
    if(queue->front == NULL) {
        return;
    }
    current = queue->front;
    while(current != NULL) {
        next = current;
        current->data.cyclingTime = current->data.finishTime - current->data.arriveTime;
        current->data.weightedCyclingTime = current->data.cyclingTime / current->data.serviceTime;
        printf("进程的名称:%c\t进程的到达时间:%d\t进程的终止时间:%d\t进程的周转时间:%lf\t进程的带权周转时间:%lf\n",current->data.id,current->data.arriveTime,current->data.finishTime,current->data.cyclingTime,current->data.weightedCyclingTime);
        current = current->next;
        free(next);
        next = NULL;
    }
}
