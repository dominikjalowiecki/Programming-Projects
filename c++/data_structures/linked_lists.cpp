#include <iostream>

using namespace std;

struct elem {
    int dane;
    elem* nast;
};

// ex. 1
void insert(int x, int i, elem* &a)
{
    if(i < 0) throw runtime_error("List insert - Index out of bound...");

    elem* newElement = new elem{x};

    if(a == NULL)
    {
        if(i != 0) throw runtime_error("List insert - Index out of bound...");
        a = newElement;
        return;
    }

    if(i == 0)
    {
        newElement->nast = a;
        a = newElement;
        return;
    }

    elem* tmpElement = a;
    for(int j = 1; j < i; j++)
    {
        tmpElement = tmpElement->nast;
        if(tmpElement == NULL) throw runtime_error("List insert - Index out of bound...");
    }

    newElement->nast = tmpElement->nast;
    tmpElement->nast = newElement;
}

void remove(int i, elem* &lista)
{
    if(i < 0 || lista == NULL) throw runtime_error("List remove - Index out of bound...");

    elem* elementToDelete;
    if(i == 0)
    {
        elementToDelete = lista;
        lista = lista->nast;
        delete elementToDelete;
        elementToDelete = NULL;
        return;
    }

    elem* tmpElement = lista;
    for(int j = 1; j < i; j++)
    {
        tmpElement = tmpElement->nast;
        if(tmpElement->nast == NULL) throw runtime_error("List remove - Index out of bound...");
    }


    elementToDelete = tmpElement->nast;
    tmpElement->nast = elementToDelete->nast;
    delete elementToDelete;
    elementToDelete = NULL;
}

int read(int i, elem* lista)
{
    if(i < 0 || lista == NULL) throw runtime_error("List read - Index out of bound...");

    for(int j = 1; j <= i; j++)
    {
        lista = lista->nast;
        if(lista == NULL) throw runtime_error("List read - Index out of bound...");
    }

    return lista->dane;
}

// ex. 2
template <typename T>
int size(T* lista)
{
    if(lista == NULL) return 0;

    int i = 1;
    for(i; lista->nast != NULL; i++) lista = lista->nast;

    return i;
}

// ex. 3
void print(elem* lista)
{
    while(lista != NULL)
    {
        cout << lista->dane << endl;
        lista = lista->nast;
    }
}

// ex. 4
void push(elem* &stos, int x)
{
    elem* newElement = new elem{x};
    newElement->nast = stos;
    stos = newElement;
}

int pop(elem* &stos)
{
    if(stos == NULL) throw runtime_error("Pop error! Stack is empty...");

    int dane = stos->dane;
    elem* tmpElement = stos->nast;
    delete stos;
    stos = tmpElement;

    return dane;
}

void printReverseStack(elem* lista)
{
    elem* stack = NULL;
    int listSize = size(lista);
    for(int i = 0; i < listSize; i++)
    {
        push(
             stack,
             read(i, lista)
        );
    }

    for(int i = 0; i < listSize; i++)
        cout << pop(stack) << endl;
}

// ex. 5
void printReverse(elem* lista)
{
    elem* element;
    int listSize = size(lista);

    for(int i = 0; i < listSize; i++)
    {
        element = lista;
        for(int j = 1; j <= (listSize - 1 - i); j++)
            element = element->nast;

        cout << element->dane << endl;
    }
}

// ex. 6
void destroy(elem* &lista)
{
    elem* elementToDelete = lista;
    lista = lista->nast;

    while(elementToDelete != NULL)
    {
        lista = lista->nast;
        delete elementToDelete;
        elementToDelete = lista;
    }
}

// ex. 7
elem* search(int x, elem* lista)
{
    elem* result = lista;

    while(result != NULL)
    {
        if(result->dane == x) break;
        result = result->nast;
    }

    return result;
}

// ex. 8
struct polynomial {
    int expo;
    int coef;
    polynomial* nast;
};

polynomial* polyadd(polynomial* l1, polynomial* l2)
{
    polynomial* res = NULL;
    polynomial* newEl = NULL;
    polynomial* prevEl = NULL;

    while(l1 != NULL || l2 != NULL)
    {
        if(l1 != NULL && (l2 == NULL || l1->expo > l2->expo))
        {
            newEl = new polynomial{l1->expo, l1->coef};

            l1 = l1->nast;
        } else if(l2 != NULL && (l1 == NULL || l1->expo < l2->expo))
        {
            newEl = new polynomial{l2->expo, l2->coef};

            l2 = l2->nast;
        } else
        {
            newEl = new polynomial{l1->expo, l1->coef + l2->coef};

            l1 = l1->nast;
            l2 = l2->nast;
        }

        if(res == NULL) res = newEl;
        else prevEl->nast = newEl;

        prevEl = newEl;
    }

    return res;
}

// ex. 9
struct elem_faray {
    int numerator;
    int denumerator;
    elem_faray* next;
};

elem_faray* ulamek_faraya(int n)
{
    elem_faray* faray = new elem_faray{0, 1};
    faray->next = new elem_faray{1, 1};

    elem_faray* pointer = NULL;
    elem_faray* newElement = NULL;

    for(int i = 1; i < n; i++)
    {
        pointer = faray;
        while(pointer->next != NULL)
        {
            if( (pointer->denumerator + (pointer->next)->denumerator) <= n )
            {
                newElement = new elem_faray{
                    (pointer->numerator + (pointer->next)->numerator),
                    (pointer->denumerator + (pointer->next)->denumerator)
                };

                newElement->next = pointer->next;
                pointer->next = newElement;
                pointer = newElement->next;
            } else
            {
                pointer = pointer->next;
            }
        }
    }

    return faray;
}

void print_faray(elem_faray* lista)
{
    while(lista != NULL)
    {
        cout << lista->numerator << "/" << lista->denumerator << endl;
        lista = lista->next;
    }
}

// ex. 3 double linked and cyclic
void to_cyclic(elem* lista)
{
    if(lista == NULL) return;

    elem* listEnd = lista;
    while(listEnd->nast != NULL)
        listEnd = listEnd->nast;

    listEnd->nast = lista;
}

// ex. 4 double linked and cyclic
void reverse_cyclic(elem* lista)
{
    if(lista == NULL || lista->nast == lista) return;

    elem* firstTmpElement = lista;
    elem* secondTmpElement = lista->nast;
    elem* thirdTmpElement = (lista->nast)->nast;

    while(secondTmpElement != lista)
    {
        secondTmpElement->nast = firstTmpElement;
        firstTmpElement = secondTmpElement;
        secondTmpElement = thirdTmpElement;
        thirdTmpElement = secondTmpElement->nast;
    }
    secondTmpElement->nast = firstTmpElement;
}

int main()
{
    elem* head = new elem{};

    insert(5, 0, head);
    insert(69, 1, head);
    insert(45, 1, head);
    insert(74, 3, head);
    insert(105, 3, head);



    /*remove(2, head);

    cout << read(2, head) << endl;

    print(head);
    cout << size<elem>(head) << endl;

    printReverse(head);

    destroy(head);
    cout << "==============" << endl;
    print(head);*/



    //cout << (search(5, head)->nast)->dane << endl;



    /*polynomial* l1 = new polynomial{4, 6};
    polynomial* l2 = new polynomial{16, 4, new polynomial};
    (l2->nast)->expo = 0;
    (l2->nast)->coef = 5;
    (l2->nast)->nast = NULL;

    polynomial* pol = polyadd(l1, l2);

    cout << pol->expo << " :: " << pol->coef << endl;
    cout << (pol->nast)->expo << " :: " << (pol->nast)->coef << endl;
    cout << ((pol->nast)->nast)->expo << " :: " << ((pol->nast)->nast)->coef << endl;*/



    /*elem_faray* lista = ulamek_faraya(4);
    print_faray(lista);*/



    /*elem* head = new elem{};

    insert(5, 0, head);
    insert(69, 1, head);
    insert(45, 1, head);
    insert(74, 3, head);
    insert(105, 3, head);

    to_cyclic(head);

    reverse_cyclic(head);

    print(head);*/



    print(head);
    cout << "===" << endl;
    printReverseStack(head);

    return 0;
}
