#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "database.txt"

struct Student {
    char name[50];
    int roll;
    float marks;
};

void addRecord();
void viewRecords();
void searchRecord();
void deleteRecord();
void updateRecord();
void clearInputBuffer();

int main() {
    int choice;
    do {
        printf("\n===== Student Record Management System =====\n");
        printf("1. Add Record\n");
        printf("2. View All Records\n");
        printf("3. Search Record\n");
        printf("4. Delete Record\n");
        printf("5. Update Record\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer(); // Clean buffer after scanf

        switch (choice) {
            case 1: addRecord(); break;
            case 2: viewRecords(); break;
            case 3: searchRecord(); break;
            case 4: deleteRecord(); break;
            case 5: updateRecord(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 6);

    return 0;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void addRecord() {
    FILE *fp = fopen(FILE_NAME, "ab");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    struct Student s;
    printf("Enter name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0'; // remove newline

    printf("Enter roll number: ");
    scanf("%d", &s.roll);
    printf("Enter marks: ");
    scanf("%f", &s.marks);
    clearInputBuffer();

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Record added successfully.\n");
}

void viewRecords() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    struct Student s;
    printf("\n%-20s %-10s %-10s\n", "Name", "Roll", "Marks");
    printf("---------------------------------------------\n");

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        printf("%-20s %-10d %-10.2f\n", s.name, s.roll, s.marks);
    }

    fclose(fp);
}

void searchRecord() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    int roll, found = 0;
    struct Student s;

    printf("Enter roll number to search: ");
    scanf("%d", &roll);
    clearInputBuffer();

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("Record Found:\nName: %s\nRoll: %d\nMarks: %.2f\n", s.name, s.roll, s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("No record found with roll number %d\n", roll);

    fclose(fp);
}

void deleteRecord() {
    FILE *fp = fopen(FILE_NAME, "rb");
    FILE *temp = fopen("temp.txt", "wb");
    if (!fp || !temp) {
        perror("Error opening files");
        return;
    }

    int roll, found = 0;
    struct Student s;

    printf("Enter roll number to delete: ");
    scanf("%d", &roll);
    clearInputBuffer();

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll != roll) {
            fwrite(&s, sizeof(s), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found)
        printf("Record deleted successfully.\n");
    else
        printf("No record found with roll number %d\n", roll);
}

void updateRecord() {
    FILE *fp = fopen(FILE_NAME, "rb+");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    int roll, found = 0;
    struct Student s;

    printf("Enter roll number to update: ");
    scanf("%d", &roll);
    clearInputBuffer();

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("Enter new name: ");
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = '\0';
            printf("Enter new marks: ");
            scanf("%f", &s.marks);
            clearInputBuffer();

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);
            found = 1;
            break;
        }
    }

    if (found)
        printf("Record updated successfully.\n");
    else
        printf("No record found with roll number %d\n", roll);

    fclose(fp);
}
