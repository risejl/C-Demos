#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef PROCESSSCHEDULING_LINKEDLIST_H
#define PROCESSSCHEDULING_LINKEDLIST_H

#endif //PROCESSSCHEDULING_LINKEDLIST_H

typedef struct Process {
    char id;
    int priority;
    int arriveTime;
    int serviceTime;
    int finishTime;
    int remainServiceTime;
    double cyclingTime;
    double weightedCyclingTime;
}Process;

typedef struct Node {
    Process data;
    struct Node* next;
}Node;

typedef struct LinkedList {
    Node* head;
    Node* end;
    int length;
}LinkedList;

Node* CreateNode(Process data) {
    Node* node = (Node *)malloc(sizeof(Node));
    if(node == NULL) {
        exit(0);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void InitLinkedList(LinkedList *list) {
    list->head = NULL;
    list->end = NULL;
    list->length = 0;
}

void DestroyLinkedList(LinkedList *list) {
    Node* current = NULL;
    Node* delnode = NULL;
    if(list->head == NULL) {
        return;
    }
    current = list->head;
    while(current != NULL) {
        delnode = current;
        current = current->next;
        free(delnode);
        delnode = NULL;
    }
}

bool IsListEmpty(LinkedList *list) {
    return list->head == NULL;
}

int ListLength(LinkedList *list) {
    return list->length;
}

void AddNode(LinkedList *list,Process data) {
    Node* temp = CreateNode(data);
    if(list->head == NULL) {
        list->head = temp;
        list->end = temp;
        list->length += 1;
    }
    else {
        list->end->next = temp;
        list->end = list->end->next;
        list->length += 1;
    }
}

void DeleteNode(LinkedList *list,Node *node) {           
    Node* current = NULL;
    current = list->head;
    if((list->head) == NULL) {
        return;
    }
    if((list->head) == node) {
        list->head = node->next;
        free(node);
        node = NULL;
        list->length -= 1;
        return;
    }
    while(current != NULL) {
        if(current->next == node) {
            current->next = node->next;
            free(node);
            node = NULL;
            list->length -= 1;
            break;
        }
        current = current->next;
    }
}
