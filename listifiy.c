/* This program allows users to create, manipulate, and store items in a linked list, 
featuring options to add, remove, search, import, and export list items, as well as print the
list to the screen. */
// Standard Library Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Defining structure for Nodes within the linked list.
struct Node {
    struct Node *next;
    char list_item[50];
};

// Initialize the head of the linked list.
struct Node* head = NULL;

// Function to add (push) item to the beginning of the list. 
void push(const char* str) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    strncpy(newNode->list_item, str, sizeof(newNode->list_item));
    newNode->next = head;
    head = newNode;
}

// Function to remove (pop) and return item at beginning of teh list. 
char* pop () {
    if (head == NULL) {
        printf("List is empty. Nothing to pop.");
        return NULL;
    }
    struct Node* temp = head;
    char* poppedItem = strdup(temp->list_item);
    head = head->next;
    free(temp);
    return poppedItem;
}

// Function to remove item from end of the list. 
void removeEnd() {
    if (head == NULL) {
        printf("List is empty. Nothing to remove.");
        return;
    }
    if (head->next == NULL) {
        free(head);
        head = NULL;
        return;
    }
    struct Node* current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
}

// Function to remove a specific item from the list. 
void removeItem(const char* str) {
    struct Node* current = head;
    struct Node* prev = NULL;

    while (current !=NULL && strcmp(current->list_item, str) !=0) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Item \"%s\" not found in the list.\n", str);
        return;
    }

    if (prev == NULL) {
        head = current->next;
    } 
    else {
        prev->next = current->next;
    }
    free(current);
}

int search(const char* str) {
    struct Node* current = head;
    while (current != NULL) {
        if (strcmp(current->list_item, str) == 0) {
            return 1;
        }
        current = current->next; // Move to the next node
    }
    return 0;
}

// Function to print the list. 
void printList() {
    struct Node* current = head;
    while (current != NULL) {
        printf("%s -> ", current->list_item);
        current = current->next;
    }
    printf("NULL\n");
}

// Function to import the list from a text file. 
int importList(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file.");
        return 0;
    }

    char lines[50][50];
    int lineCount = 0;

    while (fgets(lines[lineCount], sizeof(lines[lineCount]), file) != NULL) {
        lines[lineCount][strcspn(lines[lineCount], "\n")] = '\0';
        lineCount++;
    }

    fclose(file);

    for (int i = lineCount - 1; i >= 0; i--) {
        push(lines[i]);
    }

    return 1;
}

// Function to export items from list to a text file. 
int exportList(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("File failed to open.");
        return 0;
    }
    
    struct Node* current = head;

    while(current != NULL) {
        fprintf(file, "%s\n", current->list_item);
        current = current->next;
    }

    fclose(file);
    return 1;
    }

// Main function that displays menu and calls all functions
int main() {
    int option;
    char user_input[50];

    // Fake infinite loop to repeat showing the menu until the user exits the program.
    do {
        printf("Welcome to Listify.\n\nPlease enter a menu option:\n");
        printf("-----------------------------\n");
        printf("1. Add Item to front.\n");
        printf("2. Remove Item from front.\n");
        printf("3. Remove Item from end.\n");
        printf("4. Remove an specific item.\n");
        printf("5. Search list for an item.\n");
        printf("6. Print the list.\n");
        printf("7. Import from text file.\n");
        printf("8. Export to text file.\n");
        printf("9. Exit the program.\n");
        printf("-----------------------------\n");
        
        scanf("%d", &option);

        // Switch case statements to call functions depending on the option selected. 
        switch (option) {
            case 1:
                printf("Enter an item to add to the beginning of the list.\n");
                scanf("%s", &user_input);
                push(user_input);
                printf("\"%s\" was added to the list.\n", user_input);
                break;
            case 2:
                printf("Removing item from the beginning of list.\n");
                char* removed = pop();
                if (removed != NULL) {
                    printf("Removed: %s from the list.\n", removed);
                    free(removed);
                    }
                break;
            case 3:
                printf("Removing item from the end of list.\n");
                removeEnd();
                break;
            case 4:
                printf("Enter an item to remove from the list.\n");
                scanf("%s", &user_input);
                removeItem(user_input);
                printf("\"%s\" was removed from the list.\n", user_input);
                break;
            case 5:
                printf("Enter an item to search for in the list.\n");
                scanf("%s", &user_input);
                if (search(user_input)== 1) {
                    printf("\"%s\" was found in the list.\n", user_input);
                }
                else {
                    printf("\"%s\" was not found in the list.\n", user_input);
                }
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                break;
            case 6:
                printList();
                break;
            case 7:
                printf("Enter the file directory and name to import from: \n");
                scanf("%s", user_input);
                if (importList(user_input)) {
                    printf("List successfully imported from %s.\n\n", user_input);
                }
                else {
                    printf("Failed to import from %s\n\n", user_input);
                }
                break;
            case 8:
                printf("Enter the file directory and name to export to: \n");
                scanf("%s", user_input);
                if (exportList(user_input)) {
                    printf("List exported to %s.\n\n", user_input);
                }
                else {
                    printf("List failed to export to %s.\n\n", user_input);
                }
                break;
            case 9:
                exit(0);
            default:
                printf("Invalid option. Please try again.\n\n");
                break;
                
        }
    } while (true);

    
    return 0;

}