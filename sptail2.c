#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for the linked list
typedef struct Node {
    char *data;
    struct Node *next;
} Node;

// Function to create a new node
Node *createNode(const char *line) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    newNode->data = strdup(line);
    newNode->next = NULL;
    return newNode;
}

// Function to free the linked list
void freeList(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    Node *head = NULL;
    char buffer[256];
    int linesCount = 0;

    while (fgets(buffer, sizeof(buffer), stdin)) {
        if (head == NULL) {
            head = createNode(buffer);
        } else {
            Node *newNode = createNode(buffer);
            Node *temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            if (linesCount >= n) {
                Node *toDelete = head;
                head = head->next;
                free(toDelete->data);
                free(toDelete);
            }
            temp->next = newNode;
        }
        linesCount++;
    }

    // Print the last n lines
    Node *temp = head;
    while (temp != NULL) {
        printf("%s", temp->data);
        temp = temp->next;
    }

    // Free the linked list before exiting
    freeList(head);

    return EXIT_SUCCESS;
}
