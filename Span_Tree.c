#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int Vertex;
    int Next;
    int Length;
};
typedef struct Node edge;

int **Map_Create(int Num);
int Byte_Count(int Num);
void Read_Map(int **Map, int Num, int Count);
int **Prim_Algorithm(int **Map, int Num);
int **Kruskal_Algorithm(int **Map, int Num);
void Build_Heap(int **Map, edge *heap, int Num);
void Percolate_Down(edge *heap, int pos, int count);
bool Is_Complete(int *relation, int Num);
int Out_Put(int **Map, int **Graph, int Num, int Count);
void Memory_Clear(int **Matrix, int Num);

int main(void)
{
    int Num, Sum, Count;
    int **Map, **Graph;

    printf("Enter the number of nodes in the graph (positive): ");
    scanf("%d", &Num);
    Map = Map_Create(Num);
    Count = Byte_Count(Num);
    printf("The random_created map (connected) is as follows.\n");
    Read_Map(Map, Num, Count);

    printf("The minimum_span_tree created by prim_algorithm is as follows.\n");
    Graph = Prim_Algorithm(Map, Num);
    Sum = Out_Put(Map, Graph, Num, Count);
    Memory_Clear(Graph, Num);
    printf("The minimum_span_tree created by kruskal_algorithm is as follows.\n");
    Graph = Kruskal_Algorithm(Map, Num);
    Sum = Out_Put(Map, Graph, Num, Count);
    printf("The minimum_span_tree maybe not unique.\n");
    printf("But the minimum weight of the tree is always %d.\n", Sum);

    printf("Press ENTER to quit.\n");
    Memory_Clear(Map, Num);
    Memory_Clear(Graph, Num);
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
    srand((int)time(NULL));
    for (row = 0; row < Num; row++)
        for (col = row; col < Num; col++) {
                if (row == col)
                    *(*(map + row) + col) = 0;
                else {
                    *(*(map + row) + col) = rand() % 99 + 1;
                    *(*(map + col) + row) = *(*(map + row) + col);
                }
            }

    return map;
}

int Byte_Count(int Num)
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
        for (col = row + 1; col < Num; col++)
                printf("%*d<->%-*d:%2d; ", Count, row, Count, col, *(*(Map + row) + col));
    putchar('\n');
}

int **Prim_Algorithm(int **Map, int Num)
{
    int **graph;
    int *relation;
    int row, col, pos, min = 1;

    graph = (int **)malloc(Num * sizeof(int *));
    for (row = 0; row < Num; row++)
        *(graph + row) = (int *)malloc(Num * sizeof(int));
    for (row = 0; row < Num; row++)
        for (col = 0; col < Num; col++)
            *(*(graph + row) + col) = 0;
    relation = (int *)malloc(Num * sizeof(int));
    for (pos = 0; pos < Num; pos++)
        *(relation + pos) = pos + 1;
    for (col = 1; col < Num; col++)
        if (*(*Map + col) < *(*Map + min))
            min = col;
    *(*graph + min) = **(graph + min) = 1;
    *relation = *(relation + min) = 0;
    while (!Is_Complete(relation, Num)) {
        for (pos = 0; pos < Num; pos++) {
            if (*(relation + pos))
                continue;
            for (min = 0; min < Num; min++) {
                if (min == pos)
                    continue;
                if (*(relation + min))
                    break;
            }
            if (min < Num)
                break;
        }
        row = 0;
        while (row < Num) {
            if (*(relation + row)) {
                row++;
                continue;
            }
            for (col = 0; col < Num; col++) {
                if (*(relation + col) == 0 || col == row)
                    continue;
                if (*(*(Map + row) + col) < *(*(Map + pos) + min)) {
                    pos = row;
                    min = col;
                }
            }
            row++;
        }
        *(relation + pos) = *(relation + min) = 0;
        *(*(graph + pos) + min) = *(*(graph + min) + pos) = 1;
    }
    free(relation);

    return graph;
}

int **Kruskal_Algorithm(int **Map, int Num)
{
    int **graph;
    int *relation;
    edge *heap;
    int row, col, pos, temp, count = 0;

    graph = (int **)malloc(Num * sizeof(int *));
    for (row = 0; row < Num; row++)
        *(graph + row) = (int *)malloc(Num * sizeof(int));
    for (row = 0; row < Num; row++)
        for (col = 0; col < Num; col++) {
            if (col > row && col < Num)
                count++;
            *(*(graph + row) + col) = 0;
        }
    heap = (struct Node *)malloc(count * sizeof(struct Node));
    relation = (int *)malloc(Num * sizeof(int));
    for (pos = 0; pos < Num; pos++)
        *(relation + pos) = -pos - 1;
    Build_Heap(Map, heap, Num);
    pos = count / 2 - 1;
    while (pos >= 0) {
        Percolate_Down(heap, pos, count);
        pos--;
    }
    while (!Is_Complete(relation, Num)) {
        row = (*heap).Vertex;
        col = (*heap).Next;
        if (*(relation + row) != *(relation + col)) {
            *(*(graph + row) + col) = *(*(graph + col) + row) = 1;
            if (*(relation + row) < 0)
                *(relation + row) = row;
            temp = *(relation + col);
            for (pos = 0; pos < Num; pos++)
                if (*(relation + pos) == temp)
                    *(relation + pos) = *(relation + row);
        }
        temp = (*heap).Vertex;
        (*heap).Vertex = (*(heap + count - 1)).Vertex;
        (*(heap + count - 1)).Vertex = temp;
        temp = (*heap).Next;
        (*heap).Next = (*(heap + count - 1)).Next;
        (*(heap + count - 1)).Next = temp;
        temp = (*heap).Length;
        (*heap).Length = (*(heap + count - 1)).Length;
        (*(heap + count - 1)).Length = temp;
        count--;
        Percolate_Down(heap, 0, count);
    }
    free(heap);
    free(relation);

    return graph;
}

void Build_Heap(int **Map, edge *heap, int Num)
{
    int row, col, pos = 0;

    for (row = 0; row < Num; row++)
        for (col = row + 1; col < Num; col++) {
            (*(heap + pos)).Vertex = row;
            (*(heap + pos)).Next = col;
            (*(heap + pos)).Length = *(*(Map + row) + col);
            pos++;
        }
}

void Percolate_Down(edge *heap, int pos, int count)
{
    int min, vertex, next, length;

    vertex = (*(heap + pos)).Vertex;
    next = (*(heap + pos)).Next;
    length = (*(heap + pos)).Length;
    while (2 * pos + 1 < count) {
        min = 2 * pos + 1;
        if ((min + 1 < count) && ((*(heap + min + 1)).Length < (*(heap + min)).Length))
            min++;
        if ((*(heap + min)).Length < length) {
            (*(heap + pos)).Length = (*(heap + min)).Length;
            (*(heap + pos)).Vertex = (*(heap + min)).Vertex;
            (*(heap + pos)).Next = (*(heap + min)).Next;
            pos = min;
        }
        else
            break;
    }
    (*(heap + pos)).Vertex = vertex;
    (*(heap + pos)).Next = next;
    (*(heap + pos)).Length = length;
}

bool Is_Complete(int *relation, int Num)
{
    int row;
    bool flag = true;

    for (row = 0; row < Num; row++)
        if (*(relation + row) != *relation) {
            flag = false;
            break;
        }

    return flag;
}

int Out_Put(int **Map, int **Graph, int Num, int Count)
{
    int row, col, sum = 0;

    for (row = 0; row < Num; row++)
        for (col = row; col < Num; col++)
            if (*(*(Graph + row) + col)) {
                printf("%*d<->%-*d:%2d; ", Count, row, Count, col, *(*(Map + row) + col));
                sum += *(*(Map + row) + col);
            }
    putchar('\n');

    return sum;
}

void Memory_Clear(int **Matrix, int Num)
{
    int row;

    for (row = 0; row < Num; row++)
        free(*(Matrix + row));
    free(Matrix);
}
