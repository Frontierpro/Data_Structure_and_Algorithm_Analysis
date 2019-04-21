#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node *child;
struct Node {
    int Value;
    child Left;
    child Right;
};
typedef child leaf;

leaf Element_Insert(leaf Root, int Num);
leaf Element_Delete(leaf Root, int Num);
leaf Splay_Rotation(leaf Root, int Num);
leaf Left_Rotation(leaf Root);
leaf Right_Rotation(leaf Root);
void Levelorder_Traversal(leaf Root);
void Memory_Clear(leaf Root);

int main(void)
{
    leaf Root = NULL;
    int Num;
    char *Command;

    Command = (char *)malloc(10 * sizeof(char));
    printf("Enter \"insert\", \"delete\", \"query\" or \"quit\" command!\n");
    printf("Enter command: ");
    scanf("%s", Command);
    while (strcmp(Command, "quit")) {
        if (strcmp(Command, "insert") == 0) {
            scanf("%d", &Num);
            Root = Element_Insert(Root, Num);
        }
        else if (strcmp(Command, "delete") == 0) {
            scanf("%d", &Num);
            Root = Element_Delete(Root, Num);
        }
        else if (strcmp(Command, "query") == 0) {
            if (Root) {
                printf("The binary_search_tree is as follows.\n");
                Levelorder_Traversal(Root);
            }
            else
                printf("The binary_search_tree is empty!\n");
        }
        else
            printf("Enter \"insert\", \"delete\", \"query\" or \"quit\" command!\n");
        printf("Enter command: ");
        scanf("%s", Command);
    }
    free(Command);
    Memory_Clear(Root);

    return 0;
}

leaf Element_Insert(leaf Root, int Num)
{
    leaf temp;

    Root = Splay_Rotation(Root, Num);
    if (Root == NULL) {
        Root = (struct Node *)malloc(sizeof(struct Node));
        Root->Value = Num;
        Root->Left = Root->Right = NULL;
    }
    else if (Num < Root->Value) {
        temp = (struct Node *)malloc(sizeof(struct Node));
        temp->Value = Num;
        temp->Left = Root->Left;
        temp->Right = Root;
        Root->Left = NULL;
        Root = temp;
    }
    else if (Num > Root->Value) {
        temp = (struct Node *)malloc(sizeof(struct Node));
        temp->Value = Num;
        temp->Right = Root->Right;
        temp->Left = Root;
        Root->Right = NULL;
        Root = temp;
    }
    else
        printf("This element has been in the binary_search_tree!\n");
    
    return Root;
}

leaf Element_Delete(leaf Root, int Num)
{
    leaf temp;

    Root = Splay_Rotation(Root, Num);
    if (Root && Num == Root->Value) {
        if (Root->Left == NULL)
            temp = Root->Right;
        else {
            temp = Root->Left;
            temp = Splay_Rotation(temp, Num);
            temp->Right = Root->Right;
        }
        free(Root);
        Root = temp;
    }
    else
        printf("There is no such element in the binary_search_tree!\n");
    
    return Root;
}

leaf Splay_Rotation(leaf Root, int Num)
{
    leaf left, right, head;

    head = (struct Node *)malloc(sizeof(struct Node));
    left = right = head;
    while (Root && Num != Root->Value) {
        if (Num < Root->Value) {
            if (Root->Left && Num < Root->Left->Value)
                Root = Left_Rotation(Root);
            if (Root->Left == NULL)
                break;
            right->Left = Root;
            right = Root;
            Root = Root->Left;
        }
        else {
            if (Root->Right && Num > Root->Right->Value)
                Root = Right_Rotation(Root);
            if (Root->Right == NULL)
                break;
            left->Right = Root;
            left = Root;
            Root = Root->Right;
        }
    }
    if (Root) {
        left->Right = Root->Left;
        right->Left = Root->Right;
        Root->Left = head->Right;
        Root->Right = head->Left;
    }
    free(head);

    return Root;
}

leaf Left_Rotation(leaf Root)
{
    leaf temp = Root->Left;

    Root->Left = temp->Right;
    temp->Right = Root;

    return temp;
}

leaf Right_Rotation(leaf Root)
{
    leaf temp = Root->Right;

    Root->Right = temp->Left;
    temp->Left = Root;

    return temp;
}

void Levelorder_Traversal(leaf Root)
{
    int front = 0, rear = 0;
    leaf temp = Root;
    leaf *queue;

    queue = (leaf *)malloc(100 * sizeof(leaf));
    if (temp)
        *(queue + rear++) = temp;
    while (front < rear) {
        printf("%-10d", temp->Value);
        if (temp->Left) {
            printf("%10d->%-10d", temp->Value, temp->Left->Value);
            *(queue + rear++) = temp->Left;
        }
        else
            printf("%10d->NULL      ", temp->Value);
        if (temp->Right) {
            printf("%10d->%-10d", temp->Value, temp->Right->Value);
            *(queue + rear++) = temp->Right;
        }
        else
            printf("%10d->NULL      ", temp->Value);
        putchar('\n');
        front++;
        temp = *(queue + front);
    }
    free(queue);
}

void Memory_Clear(leaf Root)
{
    if (Root) {
        Memory_Clear(Root->Left);
        Memory_Clear(Root->Right);
        free(Root);
    }
}
