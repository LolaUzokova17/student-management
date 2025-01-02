#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char phone[15];
    char email[50];
} Contact;

typedef struct {
    char name[50];
    Contact contact;
} Parent;

typedef struct {
    char first_name[50];
    char last_name[50];
    int age;
    Contact contact;
    Parent parent;
} Student;

typedef struct {
    int id;
    char name[50];
} Lesson;

typedef struct {
    Lesson lesson;
    Student student;
    int score;
} Score;

Student students[100];
Lesson lessons[100];
Score scores[100];

int student_count = 0;
int lesson_count = 0;
int score_count = 0;

void add_student();
void get_students();
void get_student_detail();
void get_student_by_name();
void add_lesson();
void add_score();
void get_lesson_statistics();
void menu();

void add_student() {
    Student new_student;
    
    printf("Enter first name: ");
    fgets(new_student.first_name, sizeof(new_student.first_name), stdin);
    new_student.first_name[strcspn(new_student.first_name, "\n")] = '\0'; 

    printf("Enter last name: ");
    fgets(new_student.last_name, sizeof(new_student.last_name), stdin);
    new_student.last_name[strcspn(new_student.last_name, "\n")] = '\0';  
    
    printf("Enter age: ");
    scanf("%d", &new_student.age);
    getchar(); 
    
    printf("Enter phone: ");
    fgets(new_student.contact.phone, sizeof(new_student.contact.phone), stdin);
    new_student.contact.phone[strcspn(new_student.contact.phone, "\n")] = '\0';
    
    printf("Enter email: ");
    fgets(new_student.contact.email, sizeof(new_student.contact.email), stdin);
    new_student.contact.email[strcspn(new_student.contact.email, "\n")] = '\0';
    
    printf("Enter parent's name: ");
    fgets(new_student.parent.name, sizeof(new_student.parent.name), stdin);
    new_student.parent.name[strcspn(new_student.parent.name, "\n")] = '\0'; 
    printf("Enter parent's phone: ");
    fgets(new_student.parent.contact.phone, sizeof(new_student.parent.contact.phone), stdin);
    new_student.parent.contact.phone[strcspn(new_student.parent.contact.phone, "\n")] = '\0';  
    
    printf("Enter parent's email: ");
    fgets(new_student.parent.contact.email, sizeof(new_student.parent.contact.email), stdin);
    new_student.parent.contact.email[strcspn(new_student.parent.contact.email, "\n")] = '\0';  
    
    students[student_count++] = new_student;
    
    printf("Student added successfully!\n");
}

void get_students() {
    printf("ID   | First Name | Last Name | Age | Phone        | Email                    | Parent's Name | Parent's Phone | Parent's Email\n");
    printf("----------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < student_count; i++) {
        printf("%d    | %s       | %s       | %d  | %s   | %s       | %s        | %s       | %s\n",
               i + 1, students[i].first_name, students[i].last_name, students[i].age,
               students[i].contact.phone, students[i].contact.email,
               students[i].parent.name, students[i].parent.contact.phone,
               students[i].parent.contact.email);
    }
}

void get_student_detail() {
    int id;
    printf("Enter student ID to get: ");
    scanf("%d", &id);
    
    if (id > 0 && id <= student_count) {
        Student student = students[id - 1];
        printf("First Name: %s\n", student.first_name);
        printf("Last Name: %s\n", student.last_name);
        printf("Age: %d\n", student.age);
        printf("Phone: %s\n", student.contact.phone);
        printf("Email: %s\n", student.contact.email);
        printf("Parent's Name: %s\n", student.parent.name);
        printf("Parent's Phone: %s\n", student.parent.contact.phone);
        printf("Parent's Email: %s\n", student.parent.contact.email);
    } else {
        printf("Invalid student ID!\n");
    }
}

void get_student_by_name() {
    char name[50];
    printf("Enter student first name to search: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    
    int found = 0;
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].first_name, name) == 0) {
            Student student = students[i];
            printf("ID: %d\n", i + 1);
            printf("First Name: %s\n", student.first_name);
            printf("Last Name: %s\n", student.last_name);
            printf("Age: %d\n", student.age);
            printf("Phone: %s\n", student.contact.phone);
            printf("Email: %s\n", student.contact.email);
            printf("Parent's Name: %s\n", student.parent.name);
            printf("Parent's Phone: %s\n", student.parent.contact.phone);
            printf("Parent's Email: %s\n", student.parent.contact.email);
            found = 1;
        }
    }
    if (!found) {
        printf("Student not found!\n");
    }
}

void add_lesson() {
    Lesson new_lesson;
    
    printf("Enter lesson ID: ");
    scanf("%d", &new_lesson.id);
    getchar();
    
    printf("Enter lesson name: ");
    fgets(new_lesson.name, sizeof(new_lesson.name), stdin);
    new_lesson.name[strcspn(new_lesson.name, "\n")] = '\0';
    
    lessons[lesson_count++] = new_lesson;
    
    printf("Lesson added successfully!\n");
}

void add_score() {
    int student_id, lesson_id, score;
    
    printf("Enter student ID: ");
    scanf("%d", &student_id);
    printf("Enter lesson ID: ");
    scanf("%d", &lesson_id);
    printf("Enter score: ");
    scanf("%d", &score);
    
    if (student_id > 0 && student_id <= student_count && lesson_id > 0 && lesson_id <= lesson_count) {
        Score new_score;
        new_score.student = students[student_id - 1];
        new_score.lesson = lessons[lesson_id - 1];
        new_score.score = score;
        
        scores[score_count++] = new_score;
        
        printf("Score added successfully!\n");
    } else {
        printf("Invalid student or lesson ID!\n");
    }
}

void get_lesson_statistics() {
    printf("Lesson Statistics:\n");
    for (int i = 0; i < lesson_count; i++) {
        printf("Lesson: %s\n", lessons[i].name);
        int total_score = 0, count = 0;
        for (int j = 0; j < score_count; j++) {
            if (scores[j].lesson.id == lessons[i].id) {
                total_score += scores[j].score;
                count++;
            }
        }
        if (count > 0) {
            printf("Average score: %.2f\n", (float)total_score / count);
        } else {
            printf("No scores available\n");
        }
    }
}

void menu() {
    int choice;
    
    do {
        printf("\n1. Add Student\n");
        printf("2. View Students\n");
        printf("3. View Student Details\n");
        printf("4. Find Student by Name\n");
        printf("5. Add Lesson\n");
        printf("6. Add Score\n");
        printf("7. Get Lesson Statistics\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 
        
        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                get_students();
                break;
            case 3:
                get_student_detail();
                break;
            case 4:
                get_student_by_name();
                break;
            case 5:
                add_lesson();
                break;
            case 6:
                add_score();
                break;
            case 7:
                get_lesson_statistics();
                break;
            case 8:
                printf("Exiting...\n"); 
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 8);
}

int main() {
    menu();
    return 0;
}
