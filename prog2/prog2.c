// Write a program that stores an array of structures in ASCII format
// Write a function to create an array of seek positions of the beginning of
// each record
// Write a function to display the record given the position

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    float marks;
} Mark;

typedef struct {
    int count;
    int capacity;
    int *val;
} IntVec;

IntVec initIntVec(void);
void addElementToIntVec(IntVec *intvec, int val);

int writeStructToFile(Mark *marks, int n, char *filename);
void arrayOfSeeks(IntVec *seeks, char *filename);
void printStructAtPos(IntVec seeks, int target, char *filename);

int main(void) {
    Mark marks[] = {
        {2, 10},
        {3, 9 },
        {1, 2 },
        {4, 4 },
    };

    IntVec seeks = initIntVec();

    writeStructToFile(marks, 4, ".txt");
    arrayOfSeeks(&seeks, ".txt");

    printStructAtPos(seeks, 1, ".txt");

    return 0;
}

void printStructAtPos(IntVec seeks, int target, char *filename) {
    char buf[100];
    FILE *fp = fopen(filename, "r");

    if (seeks.count >= target) {
        fseek(fp, seeks.val[target], SEEK_SET);
        fgets(buf, 100, fp);
        printf("%s", buf);
    } else {
        fprintf(stderr, "Record does not exist!\n");
    }

    fclose(fp);
}

void arrayOfSeeks(IntVec *seeks, char *filename) {
    FILE *fp = fopen(filename, "r");

    char buf[100];

    addElementToIntVec(seeks, ftell(fp));

    while (fgets(buf, 100, fp) != NULL) {
        addElementToIntVec(seeks, ftell(fp));
    }
}

int writeStructToFile(Mark *marks, int n, char *filename) {
    FILE *fp = fopen(filename, "w");

    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d %f\n", marks[i].id, marks[i].marks);
    }

    fclose(fp);
    return n;
}

void addElementToIntVec(IntVec *intvec, int val) {
    if (intvec->count >= intvec->capacity) {
        if (intvec->capacity == 0) {
            intvec->val      = (int *)realloc(intvec->val, sizeof(int) * 1);
            intvec->capacity = 1;
        } else {
            intvec->val = (int *)realloc(intvec->val,
                                         sizeof(int) * (intvec->capacity * 2));
            intvec->capacity = intvec->capacity * 2;
        }
    }
    intvec->val[intvec->count++] = val;
}

void freeIntVec(IntVec *intvec) {
    free(intvec->val);
    *intvec = initIntVec();
}

IntVec initIntVec(void) {
    IntVec intvec = {0, 0, NULL};
    return intvec;
}
