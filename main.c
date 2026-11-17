
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define TOTAL_QUESTIONS 10

// Structure to store student details
struct Student {
    char name[50];
    int rollNo;
    char answers[TOTAL_QUESTIONS];
    int score;
    float percentage;
    char grade;
};

// Sample questions
char questions[TOTAL_QUESTIONS][150] = {
    "Who developed the C programming language?",
    "Which header file is used for printf()?",
    "Which format specifier is used for an integer?",
    "Which data type stores a single character?",
    "Which loop checks the condition before execution?",
    "What is the index of the first array element?",
    "Which is the assignment operator in C?",
    "Which keyword is used to define a structure?",
    "Which statement is used for decision-making?",
    "What does return 0 usually indicate in main()?"
};

// Options for each question
char options[TOTAL_QUESTIONS][4][80] = {
    {"Bjarne Stroustrup", "Dennis Ritchie",
     "James Gosling", "Guido van Rossum"},

    {"stdio.h", "stdlib.h", "math.h", "string.h"},

    {"%f", "%c", "%d", "%s"},

    {"int", "char", "float", "double"},

    {"while loop", "do-while loop",
     "switch statement", "goto statement"},

    {"1", "-1", "0", "None of these"},

    {"==", "!=", "<=", "="},

    {"struct", "define", "class", "array"},

    {"break", "if", "continue", "printf()"},

    {"Invalid input", "Loop begins",
     "Successful program termination", "Variable declaration"}
};

// Correct answers
char answerKey[TOTAL_QUESTIONS] = {
    'B', 'A', 'C', 'B', 'A',
    'C', 'D', 'A', 'B', 'C'
};

// Remove extra input from keyboard
void clearInputBuffer() {
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        // Clear remaining characters
    }
}

// Read an integer safely
int readInteger(const char *message) {
    int number;

    while (1) {
        printf("%s", message);

        if (scanf("%d", &number) == 1) {
            clearInputBuffer();
            return number;
        }

        printf("Invalid input! Please enter a number.\n");
        clearInputBuffer();
    }
}

// Accept only A, B, C or D
char readAnswer() {
    char answer;

    while (1) {
        printf("Your answer (A/B/C/D): ");

        if (scanf(" %c", &answer) != 1) {
            clearInputBuffer();
            printf("Please enter a valid option.\n");
            continue;
        }

        clearInputBuffer();
        answer = toupper((unsigned char)answer);

        if (answer >= 'A' && answer <= 'D') {
            return answer;
        }

        printf("Invalid option! Enter A, B, C or D.\n");
    }
}

// Display instructions
void showInstructions() {
    printf("\n========== INSTRUCTIONS ==========\n");
    printf("1. There are 10 multiple-choice questions.\n");
    printf("2. Each correct answer gives 1 mark.\n");
    printf("3. There is no negative marking.\n");
    printf("4. Enter A, B, C or D for each question.\n");
    printf("5. Your percentage and grade are calculated automatically.\n");
    printf("6. This program stores the latest result during this session.\n");
    printf("==================================\n");
}

// Calculate the grade
char calculateGrade(float percentage) {
    if (percentage >= 90) {
        return 'A';
    }
    else if (percentage >= 75) {
        return 'B';
    }
    else if (percentage >= 60) {
        return 'C';
    }
    else if (percentage >= 40) {
        return 'D';
    }
    else {
        return 'F';
    }
}

// Start the examination
void takeExam(struct Student *s) {
    int i, j;

    printf("\n========== START EXAM ==========\n");

    printf("Enter student name: ");
    fgets(s->name, sizeof(s->name), stdin);

    // Remove the newline from the name
    s->name[strcspn(s->name, "\n")] = '\0';

    if (strlen(s->name) == 0) {
        strcpy(s->name, "Student");
    }

    do {
        s->rollNo = readInteger("Enter roll number: ");

        if (s->rollNo <= 0) {
            printf("Roll number must be positive.\n");
        }
    } while (s->rollNo <= 0);

    // Ask all questions
    for (i = 0; i < TOTAL_QUESTIONS; i++) {
        printf("\nQ%d. %s\n", i + 1, questions[i]);

        for (j = 0; j < 4; j++) {
            printf("%c. %s\n", 'A' + j, options[i][j]);
        }

        s->answers[i] = readAnswer();
    }

    // Calculate total correct answers
    s->score = 0;

    for (i = 0; i < TOTAL_QUESTIONS; i++) {
        if (s->answers[i] == answerKey[i]) {
            s->score++;
        }
    }

    // Calculate percentage
    s->percentage =
        (s->score * 100.0f) / TOTAL_QUESTIONS;

    // Calculate grade
    s->grade = calculateGrade(s->percentage);

    printf("\nExam completed successfully!\n");

    // Display result and answer review
    // (defined below)
    printf("\n========== YOUR RESULT ==========\n");
    printf("Student Name: %s\n", s->name);
    printf("Roll Number: %d\n", s->rollNo);
    printf("Correct Answers: %d/%d\n",
           s->score, TOTAL_QUESTIONS);
    printf("Percentage: %.2f%%\n", s->percentage);
    printf("Grade: %c\n", s->grade);
    printf("=================================\n");
}

// View the latest result
void viewResult(struct Student s) {
    int i;

    printf("\n========== LAST RESULT ==========\n");
    printf("Student Name: %s\n", s.name);
    printf("Roll Number: %d\n", s.rollNo);
    printf("Score: %d out of %d\n",
           s.score, TOTAL_QUESTIONS);
    printf("Percentage: %.2f%%\n", s.percentage);
    printf("Grade: %c\n", s.grade);

    printf("\n-------- ANSWER REVIEW --------\n");

    for (i = 0; i < TOTAL_QUESTIONS; i++) {
        printf("Question %d: Your answer = %c",
               i + 1, s.answers[i]);

        if (s.answers[i] == answerKey[i]) {
            printf(" (Correct)\n");
        }
        else {
            printf(" | Correct answer = %c\n",
                   answerKey[i]);
        }
    }

    printf("=================================\n");
}

int main() {
    struct Student student;
    int choice;
    int hasResult = 0;

    printf("************************************\n");
    printf("  ONLINE EXAMINATION GRADING SYSTEM\n");
    printf("************************************\n");

    // Repeat menu until the user exits
    while (1) {
        printf("\n========== MAIN MENU ==========\n");
        printf("1. Start New Exam\n");
        printf("2. View Last Result\n");
        printf("3. View Instructions\n");
        printf("4. Exit\n");
        printf("===============================\n");

        choice = readInteger("Enter your choice: ");

        switch (choice) {
            case 1:
                takeExam(&student);
                hasResult = 1;
                break;

            case 2:
                if (hasResult == 1) {
                    viewResult(student);
                }
                else {
                    printf("\nNo result available.\n");
                    printf("Please take an exam first.\n");
                }
                break;

            case 3:
                showInstructions();
                break;

            case 4:
                printf("\nThank you for using the system!\n");
                printf("Exiting program...\n");
                return 0;

            default:
                printf("\nInvalid choice!\n");
                printf("Please select from 1 to 4.\n");
        }
    }

    return 0;
}
