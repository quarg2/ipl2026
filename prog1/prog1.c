// Store records in a binary file
// Write a function to geta specific record using fseek
// Write a function to delete a record

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    float marks;
} Mark;

size_t writeToFile(Mark *marks, int n, char *filename);
int getRecord(Mark *mark, long index, char *filename);
int deleteRecord(int id, char *filename);

int main(void) {
    Mark marks[] = {
        {3, 10},
        {1, 9 },
        {2, 7 },
        {4, 8 },
        {5, 9 },
    };

    Mark *mark = (Mark *)malloc(sizeof(Mark));

    writeToFile(marks, sizeof(marks) / sizeof(Mark), ".dat");
    getRecord(mark, 2, ".dat");

    printf("%d: %f\n", mark->id, mark->marks);

    deleteRecord(3, ".dat");
    free(mark);

    return 0;
}

int deleteRecord(int id, char *filename) {
    FILE *fp    = fopen(filename, "rb");
    Mark *marks = NULL;
    Mark buf;
    int i = 0;

    fseek(fp, 0, SEEK_END);
    int count = ftell(fp) / sizeof(Mark);
    rewind(fp);

    marks = malloc(count * sizeof(Mark));

    while (1) {
        if (fread(&buf, sizeof(Mark), 1, fp) == 1) {
            if (buf.id != id) {
                marks[i++] = buf;
            }
        } else {
            break;
        }
    }

    fclose(fp);

    fp = fopen(filename, "wb");
    fwrite(marks, sizeof(Mark), i, fp);

    fclose(fp);
    free(marks);

    return i;
}

int getRecord(Mark *mark, long index, char *filename) {
    FILE *fp = fopen(filename, "rb");

    fseek(fp, 0, SEEK_END);
    int count = ftell(fp) / sizeof(Mark);
    rewind(fp);

    if (index > count || index < 0) {
        fclose(fp);
        return 1;
    }

    fseek(fp, index * sizeof(Mark), SEEK_SET);

    fread(mark, sizeof(Mark), 1, fp);

    fclose(fp);

    return 0;
}

size_t writeToFile(Mark *marks, int n, char *filename) {
    FILE *fp = fopen(filename, "wb");

    size_t r = fwrite((void *)marks, sizeof(Mark), n, fp);

    fclose(fp);

    return r;
}
