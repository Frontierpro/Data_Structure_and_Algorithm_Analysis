#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node *child;
struct Node {
    int Value;
    child Left;
    child Right;
};
typedef child leaf;

void Build_Tree(int *Inorder, int *Postorder, int Num);
int Num_Count(int Num);
leaf Prefix_Order(int *Inorder, int *Postorder, int Num);
void Preorder_Traversal(leaf Root, int Count);
void Out_Put(int *Tree, int Num, int Count);
void Memory_Clear(leaf Root);

int main(void)
{
    int Num, Count;
    int *Inorder, *Postorder;
    leaf Root;

    printf("Enter the number of nodes (positive) in the binary tree: ");
    scanf("%d", &Num);
    Inorder = (int *)malloc(Num * sizeof(int));
    Postorder = (int *)malloc(Num * sizeof(int));
    Build_Tree(Inorder, Postorder, Num);
    Count = Num_Count(Num);

    printf("The inorder of the random_created binary tree is as follows.\n");
    Out_Put(Inorder, Num, Count + 1);
    printf("The postorder of the random_created binary tree is as follows.\n");
    Out_Put(Postorder, Num, Count + 1);
    Root = Prefix_Order(Inorder, Postorder, Num);
    printf("The preorder obtained from inorder and postorder is as follows.\n");
    Preorder_Traversal(Root, Count + 1);
    putchar('\n');

    printf("Press ENTER to quit.\n");
    free(Inorder);
    free(Postorder);
    Memory_Clear(Root);
    getchar();
    getchar();

    return 0;
}

void Build_Tree(int *Inorder, int *Postorder, int Num)
{
    int *stack;
    int top = 0, front = 0, rear = 0, pos = 0;

    stack = (int *)malloc(Num * sizeof(int));
    for (rear = 0; rear < Num; rear++)
        *(Inorder + rear) = rear + 1;
    *(stack + top++) = *(Inorder + front++);
    srand((int)time(NULL));
    while (top != 0 || front < rear) {
        if (top == 0)
            *(stack + top++) = *(Inorder + front++);
        else {
            if (front < rear && rand() % 2)
                *(stack + top++) = *(Inorder + front++);
            else {
                top--;
                *(Postorder + pos++) = *(stack + top);
            }
        }
    }
    free(stack);
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

leaf Prefix_Order(int *Inorder, int *Postorder, int Num)
{
    int pos;
    leaf temp;

    if (Num == 0)
        return NULL;
    for (pos = 0; pos < Num; pos++)
        if (*(Inorder + pos) == *(Postorder + Num - 1))
            break;
    temp = (struct Node *)malloc(sizeof(struct Node));
    temp->Value = *(Inorder + pos);
    temp->Left = Prefix_Order(Inorder, Postorder, pos);
    temp->Right = Prefix_Order(Inorder + pos + 1, Postorder + pos, Num - pos - 1);

    return temp;
}

void Preorder_Traversal(leaf Root, int Count)
{
    if (Root) {
        printf("%-*d", Count, Root->Value);
        Preorder_Traversal(Root->Left, Count);
        Preorder_Traversal(Root->Right, Count);
    }
}

void Out_Put(int *Tree, int Num, int Count)
{
    int pos;

    for (pos = 0; pos < Num; pos++)
        printf("%-*d", Count, *(Tree + pos));
    putchar('\n');
}

void Memory_Clear(leaf Root)
{
    if (Root) {
        Memory_Clear(Root->Left);
        Memory_Clear(Root->Right);
        free(Root);
    }
}
