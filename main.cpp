//
//  users.c
//  dzInform
//
//  Created by MacBook_Elena on 07/06/2017.
//  Copyright © 2017 MacBook_Elena. All rights reserved.
//

#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

typedef struct {
    char user[MAX];
    char pass[MAX];
    int s;
    int b;
} USERS;

typedef struct {
    char nether[MAX];
    char recbook[MAX];
    char lastname[MAX];
    char firstname[MAX];
    char otchestvo[MAX];
    char fac[MAX];
    char prof[MAX];
} STUDENTS;

typedef struct {
    char nether[MAX];
    char isbn[MAX];
    char title[MAX];
    char author[MAX];
    int available;
    int total;
} BOOKS;

int signin(USERS* books, int k);

int books();
void addbook(BOOKS* books, int k);
int btest(char* test, BOOKS* books, int k);
int updatenumber(int n, BOOKS* books);
void bsave(BOOKS* books, int k);

int students();
int stest(STUDENTS* students, int k);
void add(STUDENTS* students, int k);
STUDENTS* edit(int n, STUDENTS* students);
void info(int n, STUDENTS* students);
void ssave(STUDENTS* students, int k);

int main() {
    int c, k = 0;

    USERS* users = new USERS;
        
    FILE* file;
    file = fopen("users.csv", "r");
    if ((c = fscanf(file, "%[^];];%[^];];%d;%d", users[k].user, users[k].pass, &users[k].s, &users[k].b)) == EOF)
        printf("file is empty\n");
    k++;
    while ((c = fscanf(file, "%[^];];%[^];];%d;%d", users[k].user, users[k].pass, &users[k].s, &users[k].b)) != EOF) k++;
    fclose(file);

    int n;
    n = signin(users, k);

    if (n >= 0) {
        if (users[n].s == 1 && users[n].b == 1) {
            int com;
            printf("choose file to work with:\n");
            printf("STUDENTS \t s\n");
            printf("BOOKS    \t b\n");
            com = getchar();
            com = getchar();
            printf("%d\n", com);
            if (com == 'b') {
                c = books();
                if (c == 1)
                    n = signin(users, k);
            }
            else if (com == 's') {
                c = students();
                if (c == 1)
                    n = signin(users, k);
            }
            else printf("INVALID COMMAND\n");
        }
        else if (users[n].s == 1)
            c = students();
        else if (users[n].b == 1)
            c = books();
    }
}

//////////////////

int signin(USERS* users, int k) {
    char log[MAX];
    char pass[MAX];
    int c, d;

    printf("enter login\n");
    scanf("%s", log);
    printf("enter password\n");
    scanf("%s", pass);

    for (int i = 0; i < k; i++)
        if (((c = strcmp(users[i].user, log)) == 0) && ((d = strcmp(users[i].pass, pass)) == 0))
            return i;
    printf("Faild. Login or password isn't correct\n");
    return -1;
}

///////////////////////

int books() {
    int c, k = 0;

    BOOKS* books = new BOOKS;

    FILE* file;
    file = fopen("books.csv", "r");
    if ((c = fscanf(file, " %[^];];%[^];];%[^];];%d;%d", books[k].isbn, books[k].title, books[k].author, &books[k].available, &books[k].total)) == EOF)
        printf("file is empty\n");
    k++;
    while ((c = fscanf(file, "%c%[^];];%[^];];%[^];];%d;%d", books[k].nether, books[k].isbn, books[k].title, books[k].author, &books[k].available, &books[k].total)) != EOF) k++;
    //   for (int i = 0; i < k; i++)
    //       printf("%s\n%s\n%s\n%d\n%d\n",  books[i].isbn, books[i].title, books[i].author, books[i].available, books[i].total);
    fclose(file);


    while (0 < 1) {

        char com[3];
        printf("MENU:\n add book \t\t\t a\n delete book \t\t\t d\n update book data \t\t ud\n update number of books \t un\n save changes \t\t\t s\nenter command\n");
        printf("RETURN \t 0\n");
        scanf("%s", com);

        int n;

        if (strcmp(com, "0") == 0)
            return 1;

        if (strcmp(com, "a") == 0) {
            addbook(books, k);
            //  printf("k = %d  %s\n", k, books[k].isbn);
            k += 1;
        }

        else if (strcmp(com, "d") == 0) {
            char del[MAX];
            printf("Enter ISBN of the book to be deleted\n");
            scanf("%s", del);
            n = btest(del, books, k);
            if (n >= 0)
                books[n].isbn[0] = '\\';
        }

        else if (strcmp(com, "ud") == 0) {
            char change[MAX];
            printf("Enter ISBN of the book to be updated\n");
            scanf("%s", change);
            n = btest(change, books, k);
            if (n >= 0) {
                char auth[MAX];
                char tit[MAX];
                printf("enter new version of author. If you don't want to change print 0\n");
                scanf("%s", auth);
                printf("enter new version of title. If you don't want to change print 0\n");
                scanf("%s", tit);
                int j = 0;
                if (auth[0] != '0') {
                    while (auth[j] != '\0') {
                        books[n].author[j] = auth[j];
                        j++;
                    }
                    books[n].author[j] = '\0';
                }
                j = 0;
                if (tit[0] != '0') {
                    while (tit[j] != '\0') {
                        books[n].title[j] = tit[j];
                        j++;
                    }
                    books[n].title[j] = '\0';
                }
            }
        }

        else if (strcmp(com, "un") == 0) {
            char s[MAX];
            printf("enter ISBN of the book\n");
            scanf("%s", s);
            n = btest(s, books, k);
            if (n >= 0)
                books[n].available = updatenumber(n, books);
        }

        else if (strcmp(com, "s") == 0) {
            bsave(books, k);
            exit(1);
        }

        else printf("INVALID COMMAND!\n");
    }
    return 0;
}

int btest(char* test, BOOKS* books, int k) {
    int c;
    for (int i = 0; i < k; i++)
        if ((c = strcmp(books[i].isbn, test)) == 0)
            return i;
    printf("no book was found\n");
    return -1;
}

void addbook(BOOKS* books, int k) {
    char add[MAX];
    int c;
    printf("enter ISBN of new book\n");
    scanf("%s", add);
    if ((c = strlen(add)) != 13)
        printf("INVALID ISBN\n");
    else {
        int g = 0;
        for (int i = 0; i < k; i++)
            if ((c = strcmp(add, books[i].isbn)) == 0) {
                g++;
                break;
            }
        if (g > 0) {
            printf("book with this ISBN already exists\n");
            exit(1);
        }
        for (int i = 0; i < 13; i++)
            books[k].isbn[i] = add[i];
        books[k].isbn[14] = '\0';
        printf("enter title of the book\n");
        scanf("%s", books[k].title);
        printf("enter author of the book\n");
        scanf("%s", books[k].author);
        printf("enter number of books\n");
        scanf_s("%d", &books[k].total);
        books[k].available = books[k].total;
        //printf("%s\n%s\n%s\n%d\n%d\n",  books[k].isbn, books[k].title, books[k].author, books[k].available, books[k].total);
    }
}

int updatenumber(int n, BOOKS* books) {
    int c, m;
    printf("CHOOSE COMMAND:\n get books \t g\n return books \t r\n");
    c = getchar();
    c = getchar();
    printf("%d\n", c);
    if (c == 103) {
        printf("enter number of books to be handed\n");
        scanf("%d", &m);
        if (m <= books[n].available)
            books[n].available -= m;
        else printf("too many books required!\n");
    }
    else if (c == 114) {
        printf("enter number of books to be returned\n");
        scanf("%d", &m);
        if (m <= (books[n].total - books[n].available))
            books[n].available += m;
        else printf("finite quantity of books outnumbers total amount!\n");
    }
    else printf("INVALID COMMAND!\n");
    // printf("books[n].available = %d\n", books[n].available);
    return books[n].available;
}

void bsave(BOOKS* books, int k) {
    FILE* file;
    file = fopen("books.csv", "w");
    for (int i = 0; i < k; i++)
        if (books[i].isbn[0] != '\\') {
            fprintf(file, "%s;%s;%s;%d;%d\n", books[i].isbn, books[i].title, books[i].author, books[i].available, books[i].total);
        }
}


/////////////////////////

int students() {
    int c, k = 0;

    STUDENTS* students = new STUDENTS;

    FILE* file;
    file = fopen("students.csv", "r");
    if ((c = fscanf(file, "%[^];];%[^];];%[^];];%[^];];%[^];];%s", students[k].recbook, students[k].lastname, students[k].firstname, students[k].otchestvo, students[k].fac, students[k].prof)) == EOF)
        printf("file is empty\n");
    k++;
    while ((c = fscanf(file, "%c%[^];];%[^];];%[^];];%[^];];%[^];];%s", students[k].nether, students[k].recbook, students[k].lastname, students[k].firstname, students[k].otchestvo, students[k].fac, students[k].prof)) != EOF) k++;
    //for (int i = 0; i < k; i++)
    //    printf("%s\n%s\n%s\n%s\n%s\n%s\n", students[k].recbook, students[k].lastname, students[k].firstname, students[k].otchestvo, students[k].fac, students[k].prof);
    fclose(file);

    while (0 < 1) {


        char com[3];
        int n;

        printf("MENU:\n");
        printf("ADD STUDENT \t a\n");
        printf("DELETE STUDENT \t d\n");
        printf("EDIT INFORMATION ABOUT STUDENT \t e\n");
        printf("SHOW INFORMATION ABOUT STUDENT \t i\n");
        printf("SAVE CHANGES \t s\n");
        printf("RETURN \t 0\n");

        scanf("%s", com);

        if ((c = strcmp(com, "0")) == 0)
            return 1;

        if ((c = strcmp(com, "a")) == 0) {
            add(students, k);
            k += 1;
        }

        else if ((c = strcmp(com, "d")) == 0) {
            n = stest(students, k);
            if (n >= 0)
                students[n].recbook[0] = '\\';
        }

        else if ((c = strcmp(com, "e")) == 0) {
            n = stest(students, k);
            students = edit(n, students);
        }
        else if ((c = strcmp(com, "i")) == 0) {
            n = stest(students, k);
            info(n, students);
        }
        else if ((c = strcmp(com, "s")) == 0) {
            ssave(students, k);
            exit(0);
        }
        else printf("INVALID COMMAND!\n");
    }
    return 0;
}

int stest(STUDENTS* students, int k) {
    char test[MAX];
    printf("enter student's recordbook index\n");
    scanf("%s", test);
    int c;
    if ((c = strlen(test)) != 6) {
        printf("INVALID INDEX OF RECORDBOOK\n");
        return -1;
    }
    for (int i = 0; i < k; i++)
        if ((c = strcmp(students[i].recbook, test)) == 0)
            return i;
    printf("no student was found\n");
    return -1;
}

void add(STUDENTS* students, int k) {
    char add[MAX];
    int c;
    printf("enter ISBN of new student\n");
    scanf("%s", add);
    if ((c = strlen(add)) != 6)
        printf("INVALID INDEX OF RECORDBOOK\n");
    else {
        int g = 0;
        for (int i = 0; i < k; i++)
            if ((c = strcmp(add, students[i].recbook)) == 0) {
                g++;
                break;
            }
        if (g > 0) {
            printf("student with this index of recordbook already exists\n");
            exit(1);
        }
        for (int i = 0; i < 6; i++)
            students[k].recbook[i] = add[i];
        students[k].recbook[7] = '\0';
        printf("enter lastname of the student\n");
        scanf("%s", students[k].lastname);
        printf("enter firtsname of the student\n");
        scanf("%s", students[k].firstname);
        printf("enter otchestvo of the student\n");
        scanf("%s", students[k].otchestvo);
        printf("enter faculty of the student\n");
        scanf("%s", students[k].fac);
        printf("enter profession of the student\n");
        scanf("%s", students[k].prof);
    }
}

STUDENTS* edit(int n, STUDENTS* students) {
    char stud[5][MAX];
    printf("Enter new name of the student\n");
    scanf("%s", stud[0]);
    printf("Enter new lastname of the student\n");
    scanf("%s", stud[1]);
    printf("Enter new otchestvo of the student\n");
    scanf("%s", stud[2]);
    printf("Enter new faculty of the student\n");
    scanf("%s", stud[3]);
    printf("Enter new prifession of the student\n");
    scanf("%s", stud[4]);
    int i = 0;
    while (stud[0][i] != '\0') {
        students[n].firstname[i] = stud[0][i];
        i++;
    }
    students[n].firstname[i] = '\0';
    i = 0;
    while (stud[1][i] != '\0') {
        students[n].lastname[i] = stud[1][i];
        i++;
    }
    students[n].lastname[i] = '\0';
    i = 0;
    while (stud[2][i] != '\0') {
        students[n].otchestvo[i] = stud[2][i];
        i++;
    }
    students[n].otchestvo[i] = '\0';
    i = 0;
    while (stud[3][i] != '\0') {
        students[n].fac[i] = stud[3][i];
        i++;
    }
    students[n].fac[i] = '\0';
    i = 0;
    while (stud[4][i] != '\0') {
        students[n].prof[i] = stud[4][i];
        i++;
    }
    students[n].prof[i] = '\0';
    return students;
}

void info(int n, STUDENTS* students) {
    printf("INFORMATION ABOUT STUDENT\n");
    printf("FIRST NAME: %s\n", students[n].firstname);
    printf("LAST NAME: %s\n", students[n].lastname);
    printf("OTCHESTVO: %s\n", students[n].otchestvo);
    printf("FACULTY: %s\n", students[n].fac);
    printf("PROFESSION: %s\n", students[n].prof);
}

void ssave(STUDENTS* students, int k) {
    FILE* file;
    file = fopen("students.csv", "w");
    for (int i = 0; i < (k - 1); i++)
        if (students[i].recbook[0] != '\\') {
            fprintf(file, "%s;%s;%s;%s;%s;%s\n", students[i].recbook, students[i].firstname, students[i].lastname, students[i].otchestvo, students[i].fac, students[i].prof);
        }
}

