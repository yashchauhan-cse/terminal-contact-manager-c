#include <stdio.h>
#include <string.h>
#define MAX_CONTACTS 100

typedef struct {
    char name[30];
    char number[15];
} contact;

void deleteContact(char name[]);

int totalContacts = 0;
contact c[MAX_CONTACTS];

int main() {
    int menuChoice = 0;

    while (1) {
        printf("\n\n\t========== MENU ==========\n\n");
        printf("\t1. New Contact\n");
        printf("\t2. Edit an existing Contact\n");
        printf("\t3. Delete a Contact\n");
        printf("\t4. Search for a Contact\n");
        printf("\t5. View all Contacts\n");
        printf("\t6. Total Contacts\n");
        printf("\t7. Exit\n\n");
        printf("\tEnter Choice : ");
        scanf("%d", &menuChoice);

        /* EXIT */
        if (menuChoice == 7) {
            return 0;
        }

        /* ADD CONTACT */
        else if (menuChoice == 1) {
            if (totalContacts < MAX_CONTACTS) {
                printf("\n\tEnter Name : ");
                scanf(" %[^\n]", c[totalContacts].name);
                printf("\tEnter Phone Number : ");
                scanf(" %[^\n]", c[totalContacts].number);
                totalContacts++;
                printf("\n\tContact added successfully\n");
            } else {
                printf("\n\tMax limit reached. Contact not added.\n");
            }
        }

        /* EDIT CONTACT */
        else if (menuChoice == 2) {
            char old[30], newVal[30];
            int count = 0, editSelect = -1;

            printf("\n\tEnter Old Name : ");
            scanf(" %[^\n]", old);

            for (int i = 0; i < totalContacts; i++)
                if (strcmp(old, c[i].name) == 0)
                    count++;

            if (count == 0) {
                printf("\n\tContact Not Found\n");
            } else {
                printf("\n\tTotal Matches:\n");
                for (int i = 0; i < totalContacts; i++)
                    if (strcmp(old, c[i].name) == 0)
                        printf("\t%d] %s %s\n", i + 1, c[i].name, c[i].number);

                printf("\tSelect which one to edit : ");
                scanf("%d", &editSelect);

                if (editSelect >= 1 && editSelect <= totalContacts &&
                    strcmp(old, c[editSelect - 1].name) == 0) {

                    int editChoice;
                    printf("\n\t1. Edit Name\n");
                    printf("\t2. Edit Number\n");
                    printf("\tEnter Choice : ");
                    scanf("%d", &editChoice);

                    if (editChoice == 1) {
                        printf("\tEnter New Name : ");
                        scanf(" %[^\n]", newVal);
                        strcpy(c[editSelect - 1].name, newVal);
                        printf("\n\tContact edited successfully\n");
                    }
                    else if (editChoice == 2) {
                        printf("\tEnter New Number : ");
                        scanf(" %[^\n]", newVal);
                        strcpy(c[editSelect - 1].number, newVal);
                        printf("\n\tContact edited successfully\n");
                    }
                    else {
                        printf("\n\tInvalid Choice\n");
                    }
                } else {
                    printf("\n\tInvalid Selection\n");
                }
            }
        }

        /* DELETE CONTACT */
        else if (menuChoice == 3) {
            char name[30];
            printf("\n\tEnter Name : ");
            scanf(" %[^\n]", name);
            deleteContact(name);
        }

        /* SEARCH CONTACT */
        else if (menuChoice == 4) {
            char search[30];
            int count = 0;

            printf("\n\tEnter Name to search : ");
            scanf(" %[^\n]", search);

            for (int i = 0; i < totalContacts; i++) {
                if (strcmp(search, c[i].name) == 0) {
                    count++;
                    printf("\t%d] %s %s\n", count, c[i].name, c[i].number);
                }
            }

            if (count == 0)
                printf("\n\tNo matches found\n");
            else
                printf("\n\t%d Matches Found\n", count);
        }

        /* VIEW ALL */
        else if (menuChoice == 5) {
            if (totalContacts == 0)
                printf("\n\tNo contacts available\n");
            else {
                printf("\n\tContacts List:\n");
                for (int i = 0; i < totalContacts; i++)
                    printf("\t%d] %s %s\n", i + 1, c[i].name, c[i].number);
            }
        }

        /* TOTAL COUNT */
        else if (menuChoice == 6) {
            printf("\n\tTotal Contacts: %d\n", totalContacts);
        }

        else {
            printf("\n\tInvalid Choice\n");
        }
    }
}

/* DELETE FUNCTION */
void deleteContact(char name[]) {
    int count = 0;

    for (int i = 0; i < totalContacts; i++)
        if (strcmp(name, c[i].name) == 0)
            count++;

    if (count == 0) {
        printf("\n\tContact Not Found\n");
    }
    else if (count == 1) {
        for (int i = 0; i < totalContacts; i++) {
            if (strcmp(name, c[i].name) == 0) {
                for (int j = i; j < totalContacts - 1; j++)
                    c[j] = c[j + 1];
                totalContacts--;
                printf("\n\tContact Deleted Successfully\n");
                break;
            }
        }
    }
    else {
        int deleteSelect;
        printf("\n\tTotal Matches:\n");

        for (int i = 0; i < totalContacts; i++)
            if (strcmp(name, c[i].name) == 0)
                printf("\t%d] %s %s\n", i + 1, c[i].name, c[i].number);

        printf("\tSelect which one to delete : ");
        scanf("%d", &deleteSelect);

        if (deleteSelect >= 1 && deleteSelect <= totalContacts &&
            strcmp(name, c[deleteSelect - 1].name) == 0) {

            for (int j = deleteSelect - 1; j < totalContacts - 1; j++)
                c[j] = c[j + 1];

            totalContacts--;
            printf("\n\tContact Deleted Successfully\n");
        }
        else {
            printf("\n\tInvalid Selection\n");
        }
    }
}

