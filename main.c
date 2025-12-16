#include <stdio.h>
#include <string.h>

#define MAX_CONTACTS 100
#define FILE_NAME "contacts.txt"

typedef struct {
    char name[30];
    char number[15];
} contact;

contact c[MAX_CONTACTS];
int totalContacts = 0;

void loadContacts();
void saveContacts();
void deleteContact(char delete[]);

int main() {
    int menuChoice = 0;
    loadContacts();

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

        if (menuChoice == 7) {
            saveContacts();
            return 0;
        }

        else if (menuChoice == 1) {
            if (totalContacts < MAX_CONTACTS) {
                printf("\n\tEnter Name : ");
                scanf(" %[^\n]", c[totalContacts].name);
                printf("\n\tEnter Phone Number : ");
                scanf(" %[^\n]", c[totalContacts].number);
                totalContacts++;
                saveContacts();
                printf("\n\tContact added successfully\n");
            } else {
                printf("\n\tMax limit reached\n");
            }
        }

        else if (menuChoice == 2) {
            char old[30], newVal[30];
            int count = 0;

            printf("\n\tEnter Old Name : ");
            scanf(" %[^\n]", old);

            for (int i = 0; i < totalContacts; i++)
                if (strcmp(old, c[i].name) == 0)
                    count++;

            if (count == 0) {
                printf("\n\tContact Not Found\n");
                continue;
            }

            printf("\n\tTotal Matches:\n");
            for (int i = 0; i < totalContacts; i++)
                if (strcmp(old, c[i].name) == 0)
                    printf("\t%d] %s %s\n", i + 1, c[i].name, c[i].number);

            int sel;
            printf("\n\tSelect which one to edit: ");
            scanf("%d", &sel);

            if (sel < 1 || sel > totalContacts || strcmp(old, c[sel - 1].name) != 0) {
                printf("\n\tInvalid Selection\n");
                continue;
            }

            int choice;
            printf("\n\t1. Edit Name\n\t2. Edit Number\n\tEnter Choice: ");
            scanf("%d", &choice);

            if (choice == 1) {
                printf("\n\tEnter New Name: ");
                scanf(" %[^\n]", newVal);
                strcpy(c[sel - 1].name, newVal);
            } else if (choice == 2) {
                printf("\n\tEnter New Number: ");
                scanf(" %[^\n]", newVal);
                strcpy(c[sel - 1].number, newVal);
            } else {
                printf("\n\tInvalid Choice\n");
                continue;
            }

            saveContacts();
            printf("\n\tContact updated successfully\n");
        }

        else if (menuChoice == 3) {
            char del[30];
            printf("\n\tEnter Name : ");
            scanf(" %[^\n]", del);
            deleteContact(del);
            saveContacts();
        }

        else if (menuChoice == 4) {
            char search[30];
            int found = 0;
            printf("\n\tEnter Name to search : ");
            scanf(" %[^\n]", search);

            for (int i = 0; i < totalContacts; i++) {
                if (strcmp(search, c[i].name) == 0) {
                    printf("\t%s %s\n", c[i].name, c[i].number);
                    found = 1;
                }
            }

            if (!found)
                printf("\n\tNo matches found\n");
        }

        else if (menuChoice == 5) {
            if (totalContacts == 0) {
                printf("\n\tNo contacts available\n");
            } else {
                for (int i = 0; i < totalContacts; i++)
                    printf("\t%d] %s %s\n", i + 1, c[i].name, c[i].number);
            }
        }

        else if (menuChoice == 6) {
            printf("\n\tTotal Contacts: %d\n", totalContacts);
        }

        else {
            printf("\n\tInvalid Choice\n");
        }
    }
}

void loadContacts() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL)
        return;

    totalContacts = 0;
    while (fscanf(fp, "%[^,],%[^\n]\n",
                  c[totalContacts].name,
                  c[totalContacts].number) != EOF) {
        totalContacts++;
        if (totalContacts >= MAX_CONTACTS)
            break;
    }

    fclose(fp);
}

void saveContacts() {
    FILE *fp = fopen(FILE_NAME, "w");
    if (fp == NULL)
        return;

    for (int i = 0; i < totalContacts; i++)
        fprintf(fp, "%s,%s\n", c[i].name, c[i].number);

    fclose(fp);
}

void deleteContact(char delete[]) {
    int count = 0;

    for (int i = 0; i < totalContacts; i++)
        if (strcmp(delete, c[i].name) == 0)
            count++;

    if (count == 0) {
        printf("\n\tContact Not Found\n");
        return;
    }

    if (count == 1) {
        for (int i = 0; i < totalContacts; i++) {
            if (strcmp(delete, c[i].name) == 0) {
                for (int j = i; j < totalContacts - 1; j++)
                    c[j] = c[j + 1];
                totalContacts--;
                printf("\n\tContact Deleted\n");
                return;
            }
        }
    }

    printf("\n\tMultiple matches found:\n");
    for (int i = 0; i < totalContacts; i++)
        if (strcmp(delete, c[i].name) == 0)
            printf("\t%d] %s %s\n", i + 1, c[i].name, c[i].number);

    int sel;
    printf("\n\tSelect which one to delete: ");
    scanf("%d", &sel);

    if (sel < 1 || sel > totalContacts || strcmp(delete, c[sel - 1].name) != 0) {
        printf("\n\tInvalid Selection\n");
        return;
    }

    for (int j = sel - 1; j < totalContacts - 1; j++)
        c[j] = c[j + 1];

    totalContacts--;
    printf("\n\tContact Deleted\n");
}
