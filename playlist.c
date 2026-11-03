
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for each song
struct Song {
    char name[50];
    struct Song *prev;
    struct Song *next;
};

// Head and tail pointers
struct Song *head = NULL, *tail = NULL;

// Function to add a song
void addSong() {
    struct Song *newSong = malloc(sizeof(struct Song));

    if (newSong == NULL) {
        printf("\nMemory allocation failed!\n");
        return;
    }

    printf("\nEnter song name: ");

    if (fgets(newSong->name, sizeof(newSong->name), stdin) == NULL) {
        free(newSong);
        return;
    }

    newSong->name[strcspn(newSong->name, "\n")] = '\0';

    if (strlen(newSong->name) == 0) {
        printf("\nSong name cannot be empty!\n");
        free(newSong);
        return;
    }

    newSong->next = NULL;
    newSong->prev = NULL;

    if (head == NULL) {
        head = tail = newSong;
    } else {
        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
    }

    printf("\n\"%s\" has been added to your playlist!\n",
           newSong->name);
}

// Function to display playlist
void displayPlaylist() {
    struct Song *temp = head;
    int count = 1;

    if (head == NULL) {
        printf("\nOops! Your playlist is empty.\n");
        return;
    }

    printf("\n========== YOUR PLAYLIST ==========\n");

    while (temp != NULL) {
        printf("%d. %s\n", count++, temp->name);
        temp = temp->next;
    }

    printf("===================================\n");
}

// Function to delete a song
void deleteSong() {
    char songName[50];
    struct Song *temp = head;

    if (head == NULL) {
        printf("\nPlaylist is empty.\n");
        return;
    }

    printf("\nEnter the song name to delete: ");

    if (fgets(songName, sizeof(songName), stdin) == NULL) {
        return;
    }

    songName[strcspn(songName, "\n")] = '\0';

    while (temp != NULL &&
           strcmp(temp->name, songName) != 0) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("\nSong not found!\n");
        return;
    }

    // Update head if first song is deleted
    if (temp == head) {
        head = temp->next;
    }

    // Update tail if last song is deleted
    if (temp == tail) {
        tail = temp->prev;
    }

    // Connect previous and next nodes
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    free(temp);

    printf("\nSong removed successfully!\n");
}

// Function to free all remaining songs
void freePlaylist() {
    struct Song *temp = head;

    while (temp != NULL) {
        struct Song *nextSong = temp->next;
        free(temp);
        temp = nextSong;
    }

    head = tail = NULL;
}

// Main function
int main() {
    int choice;
    char input[20];

    printf("\n====================================\n");
    printf("       MUSIC PLAYLIST MANAGER       \n");
    printf("====================================\n");

    while (1) {
        printf("\n----------- MENU -----------\n");
        printf("1. Add Song\n");
        printf("2. Display Playlist\n");
        printf("3. Delete Song\n");
        printf("4. Exit\n");
        printf("----------------------------\n");

        printf("Enter your choice: ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        if (sscanf(input, "%d", &choice) != 1) {
            printf("\nInvalid input! Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                addSong();
                break;

            case 2:
                displayPlaylist();
                break;

            case 3:
                deleteSong();
                break;

            case 4:
                freePlaylist();
                printf("\nThank you for using Music Playlist Manager!\n");
                printf("Goodbye!\n");
                return 0;

            default:
                printf("\nInvalid choice! Please select 1-4.\n");
        }
    }

    freePlaylist();
    printf("\nProgram terminated.\n");

    return 0;
}

