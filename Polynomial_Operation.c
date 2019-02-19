#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node *item;
struct Node {
    int Coefficient;
    int Exponent;
    item Next;
};

item Polynomial_Read(int Num);
item Polynomial_Sum(item Alpha, item Beta);
item Polynomial_Product(item Alpha, item Beta);
void Equal_Merge(item head);
item Zero_Delete(item head);
void Selection_Sort(item head);
void Out_Put(item Head);
void Memory_Clear(item Head);

int main(void)
{
    int Num;
    item Alpha, Beta, Sum, Product;

    printf("Enter the number of the items (positive) in the first polynomial: ");
    scanf("%d", &Num);
    printf("Enter the coefficient and exponent for each item in this polynomial.\n");
    Alpha = Polynomial_Read(Num);
    printf("Enter the number of the items (positive) in the second polynomial: ");
    scanf("%d", &Num);
    printf("Enter the coefficient and exponent for each item in this polynomial.\n");
    Beta = Polynomial_Read(Num);

    Sum = Polynomial_Sum(Alpha, Beta);
    printf("The sum of two polynomials is as follows.\n");
    Out_Put(Sum);
    Product = Polynomial_Product(Alpha, Beta);
    printf("The product of two polynomials is as follows.\n");
    Out_Put(Product);

    printf("Press ENTER to quit.\n");
    Memory_Clear(Alpha);
    Memory_Clear(Beta);
    Memory_Clear(Sum);
    Memory_Clear(Product);
    getchar();
    getchar();

    return 0;
}

item Polynomial_Read(int Num)
{
    int count;
    item temp, head = NULL, tail;

    for (count = 0; count < Num; count++) {
        temp = (struct Node *)malloc(sizeof(struct Node));
        temp->Next = NULL;
        scanf("%d %d", &temp->Coefficient, &temp->Exponent);
        if (head == NULL)
            head = temp;
        else
            tail->Next = temp;
        tail = temp;
    }

    return head;
}

item Polynomial_Sum(item Alpha, item Beta)
{
    item sum, head = NULL, tail, temp;

    while (Alpha) {
        temp = (struct Node *)malloc(sizeof(struct Node));
        temp->Next = NULL;
        temp->Coefficient = Alpha->Coefficient;
        temp->Exponent = Alpha->Exponent;
        if (head == NULL) 
            head = temp;
        else
            tail->Next = temp;
        tail = temp;
        Alpha = Alpha->Next;
    }
    while (Beta) {
        temp = (struct Node *)malloc(sizeof(struct Node));
        temp->Next = NULL;
        temp->Coefficient = Beta->Coefficient;
        temp->Exponent = Beta->Exponent;
        if (head == NULL)
            head = temp;
        else
            tail->Next = temp;
        tail = temp;
        Beta = Beta->Next;
    }
    Equal_Merge(head);
    sum = Zero_Delete(head);
    Selection_Sort(sum);

    return sum;
}

item Polynomial_Product(item Alpha, item Beta)
{
    item product, head = NULL, tail, temp, prev;

    while (Alpha) {
        prev = Beta;
        while (prev) {
            temp = (struct Node *)malloc(sizeof(struct Node));
            temp->Next = NULL;
            temp->Coefficient = Alpha->Coefficient * prev->Coefficient;
            temp->Exponent = Alpha->Exponent + prev->Exponent;
            if (head == NULL)
                head = temp;
            else
                tail->Next = temp;
            tail = temp;
            prev = prev->Next;
        }
        Alpha = Alpha->Next;
    }
    Equal_Merge(head);
    product = Zero_Delete(head);
    Selection_Sort(product);

    return product;
}

void Equal_Merge(item head)
{
    item tail, temp;

    while (head) {
        temp = head;
        tail = head->Next;
        while (tail) {
            if (head->Exponent == tail->Exponent) {
                head->Coefficient += tail->Coefficient;
                temp->Next = tail->Next;
                free(tail);
                tail = temp->Next;
                continue;
            }
            temp = tail;
            tail = tail->Next;
        }
        head = head->Next;
    }
}

item Zero_Delete(item head)
{
    item pos = head, tail, temp;

    while (head) {
        if (head->Coefficient == 0) {
            head = head->Next;
            free(pos);
            pos = head;
        }
        else
            break;
    }
    if (head) {
        temp = head;
        head = head->Next;
        while (head) {
            if (head->Coefficient == 0) {
                head = head->Next;
                free(temp->Next);
                temp->Next = head;
            }
            else {
                temp = head;
                head = head->Next;
            }
        }
    }

    return pos;
}

void Selection_Sort(item head)
{
    int temp;
    item tail;

    while (head) {
        tail = head->Next;
        while (tail) {
            if (tail->Exponent > head->Exponent) {
                temp = tail->Exponent;
                tail->Exponent = head->Exponent;
                head->Exponent = temp;
                temp = tail->Coefficient;
                tail->Coefficient = head->Coefficient;
                head->Coefficient = temp;
            }
            tail = tail->Next;
        }
        head = head->Next;
    }
}

void Out_Put(item Head)
{
    if (Head == NULL) {
        printf("0\n");
        return;
    }
    if (Head->Coefficient < 0)
        printf("-");
    if (abs(Head->Coefficient) != 1 || Head->Exponent == 0)
        printf("%d", abs(Head->Coefficient));
    if (Head->Exponent) {
        if (Head->Exponent == 1)
            putchar('x');
        else
            printf("x^%d", Head->Exponent);
    }
    Head = Head->Next;
    while (Head) {
        if (Head->Coefficient > 0)
            printf(" + ");
        else
            printf(" - ");
        if (abs(Head->Coefficient) != 1 || Head->Exponent == 0)
            printf("%d", abs(Head->Coefficient));
        if (Head->Exponent) {
            if (Head->Exponent == 1)
                putchar('x');
            else
                printf("x^%d", Head->Exponent);
        }
        Head = Head->Next;
    }
    putchar('\n');
}

void Memory_Clear(item Head)
{
    item temp;

    while (Head) {
        temp = Head;
        Head = Head->Next;
        free(temp);
    }
}
