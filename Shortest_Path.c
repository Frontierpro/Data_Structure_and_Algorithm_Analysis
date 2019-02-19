#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Infinity 1e5

struct Node {
    int Length;
    int Last;
    int Degree;
    int Count;
    bool Flag;
};
typedef struct Node path;

int **Map_Create(int Num);
int Num_Count(int Num);
void Read_Map(int **Map, int Num, int Count);
path *Dijkstra_Algorithm(int **Map, int Num, int Head);
void Out_Put(path *Queue, int Num, int Head, int Tail, int Count);
void Memory_Clear(int **Map, int Num);

int main(void)
{
    int Num, Head, Tail, Count;
    int **Map;
    path *Queue;

    printf("Enter the number of nodes in the graph (positive): ");
    scanf("%d", &Num);
    Map = Map_Create(Num);
    Count = Num_Count(Num);
    printf("The random_created map is as follows.\n");
    Read_Map(Map, Num, Count + 1);

    printf("Enter the source node and destination node: ");
    scanf("%d %d", &Head, &Tail);
    Queue = Dijkstra_Algorithm(Map, Num, Head);
    if ((*(Queue + Tail)).Flag && Head != Tail) {
        if ((*(Queue + Tail)).Count > 1) {
            printf("There are %d different shortest paths from %d to %d.\n", (*(Queue + Tail)).Count, Head, Tail);
            printf("The way passes minimum nodes is as follows.\n");
        }
        else {
            printf("There is just one shortest path from %d to %d.\n", Head, Tail);
            printf("The way is as follows.\n");
        }
        Out_Put(Queue, Num, Head, Tail, Count);
        printf("And its length is %d.\n", (*(Queue + Tail)).Length);
    }
    else
        printf("The path from %d to %d is not available.\n", Head, Tail);

    printf("Press ENTER to quit.\n");
    Memory_Clear(Map, Num);
    free(Queue);
    getchar();
    getchar();

    return 0;
}

int **Map_Create(int Num)
{
    int row, col;
    int **map;

    map = (int **)malloc(Num * sizeof(int *));
    for (row = 0; row < Num; row++)
        *(map + row) = (int *)malloc(Num * sizeof(int));
    for (row = 0; row < Num; row++)
        for (col = 0; col < Num; col++)
            *(*(map + row) + col) = 0;
    srand((int)time(NULL));
    for (row = 0; row < Num; row++) {
        for (col = 0; col < row; col++) {
            if (*(*(map + col) + row))
                continue;
            *(*(map + row) + col) = rand() % (Num / 7 + 2);
            if (*(*(map + row) + col))
                *(*(map + row) + col) = 0;
            else
                *(*(map + row) + col) = rand() % 99 + 1;
        }
        col++;
        while (col < Num) {
            *(*(map + row) + col) = rand() % (Num / 7 + 2);
            if (*(*(map + row) + col))
                *(*(map + row) + col) = 0;
            else
                *(*(map + row) + col) = rand() % 99 + 1;
            col++;
        }
    }

    return map;
}

int Num_Count(int Num)
{
    int count = 0;

    while (Num) {
        count++;
        Num /= 10;
    }

    return count;
}

void Read_Map(int **Map, int Num, int Count)
{
    int row, col;

    for (row = 0; row < Num; row++)
        for (col = 0; col < Num; col++)
            if (*(*(Map + row) + col))
                printf("%*d->%-*d:%2d; ", Count, row, Count, col, *(*(Map + row) + col));
    putchar('\n');
}

path *Dijkstra_Algorithm(int **Map, int Num, int Head)
{
    path *queue;
    int pos, row, col;

    queue = (struct Node *)malloc(Num * sizeof(struct Node));
    for (pos = 0; pos < Num; pos++) {
        if (pos == Head) {
            (*(queue + pos)).Length = 0;
            (*(queue + pos)).Last = -1;
            (*(queue + pos)).Degree = 0;
            (*(queue + pos)).Count = 1;
        }
        else {
            (*(queue + pos)).Length = Infinity;
            (*(queue + pos)).Degree = Infinity;
        }
        (*(queue + pos)).Flag = false;
    }
    while (true) {
        row = -1;
        for (pos = 0; pos < Num; pos++) {
            if ((*(queue + pos)).Flag)
                continue;
            if ((*(queue + pos)).Length < Infinity) {
                if (row < 0)
                    row = pos;
                else if ((*(queue + pos)).Length < (*(queue + row)).Length)
                    row = pos;
            }
        }
        if (row < 0)
            break;
        (*(queue + row)).Flag = true;
        col = 0;
        while (col < Num) {
            if (*(*(Map + row) + col)) {
                if (*(*(Map + row) + col) + (*(queue + row)).Length < (*(queue + col)).Length) {
                    (*(queue + col)).Length = *(*(Map + row) + col) + (*(queue + row)).Length;
                    (*(queue + col)).Last = row;
                    (*(queue + col)).Degree = (*(queue + row)).Degree + 1;
                    (*(queue + col)).Count = (*(queue + row)).Count;
                }
                else if (*(*(Map + row) + col) + (*(queue + row)).Length == (*(queue + col)).Length) {
                    (*(queue + col)).Count++;
                    if ((*(queue + col)).Degree > (*(queue + row)).Degree + 1) {
                        (*(queue + col)).Degree = (*(queue + row)).Degree + 1;
                        (*(queue + col)).Last = row;
                    }
                }
            }
            col++;
        }
    }

    return queue;
}

void Out_Put(path *Queue, int Num, int Head, int Tail, int Count)
{
    int *stack;
    int top = 0, pos = Tail;

    stack = (int *)malloc(Num * sizeof(int));
    *(stack + top++) = Tail;
    while (pos != Head) {
        pos = (*(Queue + pos)).Last;
        *(stack + top++) = pos;
    }
    top--;
    while (top > 0) {
        printf("%*d->", Count, *(stack + top));
        top--;
    }
    printf("%*d\n", Count, *(stack + top));
    free(stack);
}

void Memory_Clear(int **Map, int Num)
{
    int row;

    for (row = 0; row < Num; row++)
        free(*(Map + row));
    free(Map);
}
