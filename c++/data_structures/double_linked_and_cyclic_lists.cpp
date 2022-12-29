#include <iostream>

using namespace std;

struct elem {
    int dane;
    elem * poprz;
    elem * nast;
};


// ex. 1
void insert(int x, int i, elem* &a)
{
    if(i < 0) throw runtime_error("Insert error! Index out of bound...");

    elem* newElement = new elem{x};

    if(a == NULL)
    {
        if(i != 0) throw runtime_error("Insert error! Index out of bound...");
        a = newElement;
        return;
    }

    if(i == 0)
    {
        newElement->nast = a;
        a->poprz = newElement;
        a = newElement;
        return;
    }

    elem* tmpElement = a;
    for(int j = 1; j < i; j++)
    {
        tmpElement = tmpElement->nast;
        if(tmpElement == NULL) throw runtime_error("Insert error! Index out of bound...");
    }

    newElement->poprz = tmpElement;
    newElement->nast = tmpElement->nast;
    tmpElement->nast = newElement;
    if(newElement->nast != NULL) (newElement->nast)->poprz = newElement;
}

void remove(elem* &lista)
{
    if(lista == NULL) return;

    elem* deleteElement = lista;
    lista = lista->nast;
    delete deleteElement;
    deleteElement = NULL;
    lista->poprz = NULL;
}

void remove(int i, elem* &lista)
{
    if(i < 0 || lista == NULL) throw runtime_error("Remove error! Index out of bound...");

    elem* deleteElement;
    if(i == 0)
    {
        deleteElement = lista;
        lista = lista->nast;
        delete deleteElement;
        deleteElement = NULL;
        lista->poprz = NULL;
        return;
    }

    deleteElement = lista;
    for(int j = 1; j <= i; j++)
    {
        deleteElement = deleteElement->nast;
        if(deleteElement == NULL) throw runtime_error("Remove error! Index out of bound...");
    }

    (deleteElement->poprz)->nast = deleteElement->nast;
    if(deleteElement->nast != NULL)
        (deleteElement->nast)->poprz = deleteElement->poprz;

    delete deleteElement;
    deleteElement = NULL;
}

// ex. 2
void reverse(elem* &lista)
{
    elem* tmpElement = lista;

    while(tmpElement != NULL)
    {
        tmpElement = lista->nast;
        lista->nast = lista->poprz;
        lista->poprz = tmpElement;

        if(tmpElement != NULL ) lista = tmpElement;
    }
}

// ex. 3 in linked_lists.cpp
// ex. 4 in linked_lists.cpp

// ex. 5
struct elem2 {
    char dane;
    elem2* poprz;
    elem2* nast;
};

// "/ 10 - 4 2"
bool is_valid_pn(elem2* lista)
{
    if(lista == NULL) return false;

    while(lista->nast != NULL)
    {
        if(
           !(lista->dane == '+' ||
           lista->dane == '-' ||
           lista->dane == '*' ||
           lista->dane == '/') ||
           lista->nast == NULL ||
           (lista->nast)->nast == NULL
        )
            return false;

        lista = (lista->nast)->nast;
    }

    return true;
}

int main()
{
    /*elem* head = NULL;
    insert(39, 0, head);
    insert(5, 1, head);
    insert(41, 0, head);

    cout << ((head->nast)->poprz)->dane << endl;
    cout << (head->nast)->dane << endl;
    cout << ((((head->nast)->nast)->poprz)->nast)->dane << endl;

    cout << "=================" << endl;

    remove(head);
    remove(1, head);

    cout << head->dane << endl;
    cout << head->nast << endl;

    reverse(head);

    cout << ((head->nast)->poprz)->dane << endl;
    cout << (head->nast)->dane << endl;
    cout << ((((head->nast)->nast)->poprz)->nast)->dane << endl;*/



    /*elem2* head = new elem2{'/'};
    elem2* a = new elem2{10};
    elem2* b = new elem2{'-'};
    elem2* c = new elem2{4};
    elem2* d = new elem2{2};

    head->nast = a;
    a->poprz = head;

    a->nast = b;
    b->poprz = a;

    b->nast = c;
    c->poprz = b;

    c->nast = d;
    d->poprz = c;

    cout << is_valid_pn(head) << endl;*/

    return 0;
}
