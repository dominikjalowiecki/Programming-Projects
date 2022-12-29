#include <iostream>

using namespace std;

struct elem {
    int dane;
    elem* nast;
};

// ex. 1
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

int topEl(elem* stos)
{
    if(stos == NULL) throw runtime_error("Pop error! Stack is empty...");

    return stos->dane;
}

bool isEmpty(elem* stos)
{
    return (stos == NULL);
}

// ex. 2
void add(elem* &pocz_kolejki, elem* &kon_kolejki, int x)
{
    if(
       (pocz_kolejki == NULL && kon_kolejki != NULL) ||
       (pocz_kolejki != NULL && kon_kolejki == NULL)
    )
        throw runtime_error("Queue add error! Invalid pointers...");

    elem* newElement = new elem{x};

    if(pocz_kolejki == NULL && kon_kolejki == NULL)
    {
        pocz_kolejki = kon_kolejki = newElement;
        return;
    }

    kon_kolejki->nast = newElement;
    kon_kolejki = newElement;
}

int next(elem* &pocz_kolejki, elem* &kon_kolejki)
{
    if(
       (pocz_kolejki == NULL && kon_kolejki != NULL) ||
       (pocz_kolejki != NULL && kon_kolejki == NULL)
    )
        throw runtime_error("Queue next error! Invalid pointers...");

    if(pocz_kolejki == NULL && kon_kolejki == NULL)
        throw runtime_error("Queue next error! Queue is empty...");

    int dane;

    if(pocz_kolejki == kon_kolejki)
    {
        dane = pocz_kolejki->dane;

        delete pocz_kolejki;
        pocz_kolejki = kon_kolejki = NULL;

        return dane;
    }

    elem* tmpElement = pocz_kolejki->nast;
    dane = pocz_kolejki->dane;

    delete pocz_kolejki;
    pocz_kolejki = tmpElement;

    return dane;
}

int firstEl(elem* pocz_kolejki)
{
    return pocz_kolejki->dane;
}

/*bool isEmpty(elem* pocz_kolejki)
{
    return (pocz_kolejki == NULL);
}*/

// ex. 5
void enqueue(elem* &stack1, elem* &stack2, int dane)
{
    push(stack1, dane);
}

int dequeue(elem* &stack1, elem* &stack2)
{
    if(stack1 == NULL) throw runtime_error("Dequeue error! Stack is empty...");

    while(!isEmpty(stack1))
        push(stack2, pop(stack1));

    int dane = pop(stack2);

    while(!isEmpty(stack2))
        push(stack1, pop(stack2));

    return dane;
}

// ex. 6
void enqueue_array(int array[], int n, int &back, int data)
{
    cout << sizeof(array) << endl;
    if(back == n) throw runtime_error("Enqueue array error! Queue is full...");
    array[back] = data;
    ++back;
}

int dequeue_array(int array[], int front, int &back)
{
    if(front == back) throw runtime_error("Dequeue array error! Queue is empty...");
    int data = array[0];
    int x = back - 1;

    for(int i = 0; i < x; i++)
        array[i] = array[i + 1];

    --back;

    return data;
}

int firstEl_array(int array[], int front, int back)
{
    if(front == back) throw runtime_error("Queue first element error! Queue is empty...");
    return array[0];
}

bool isEmpty_array(int front, int back)
{
    return (front == back);
}

// ex. 8
void sortStack(elem* &stack1)
{
    if(isEmpty(stack1)) return;

    int n = 1;
    elem* tmpElement = stack1;
    while(tmpElement->nast != NULL)
    {
        tmpElement = tmpElement->nast;
        ++n;
    }

    if(n == 1) return;

    elem* stack2 = NULL;

    for(int i = 0; i < n; i++)
    {
        int j = (n - i - 1);

        int x = pop(stack1); // Min. value

        for(int k = 0; k < j; k++)
        {
            int y = pop(stack1);

            if(x > y)
            {
                push(stack2, x);
                x = y;
            } else
            {
                push(stack2, y);
            }
        }

        push(stack1, x);

        for(int k = 0; k < j; k++)
            push(stack1, pop(stack2));
    }
}

int main()
{
    //elem* top = NULL;

    // ex. 3
    /*elem* top = NULL;
    push(top, (int)'E');
    push(top, (int)'A');
    push(top, (int)'S');
    cout << (char)pop(top) << endl;
    push(top, (int)'Y');
    cout << (char)pop(top) << endl;
    push(top, (int)'Q');
    push(top, (int)'U');
    push(top, (int)'E');
    cout << (char)pop(top) << endl;
    cout << (char)pop(top) << endl;
    cout << (char)pop(top) << endl;
    push(top, (int)'S');
    push(top, (int)'T');
    cout << (char)pop(top) << endl;
    cout << (char)pop(top) << endl;
    cout << (char)pop(top) << endl;
    push(top, (int)'I');
    push(top, (int)'O');
    cout << (char)pop(top) << endl;
    push(top, (int)'N');
    cout << (char)pop(top) << endl;
    cout << (char)pop(top) << endl;
    cout << (char)pop(top) << endl;*/

    elem* fronte = NULL;
    elem* backe = NULL;
    add(fronte, backe, (char)'E');
    add(fronte, backe, (char)'A');
    add(fronte, backe, (char)'S');
    cout << (char)next(fronte, backe) << endl;
    add(fronte, backe, (char)'Y');
    cout << (char)next(fronte, backe) << endl;
    add(fronte, backe, (char)'Q');
    add(fronte, backe, (char)'U');
    add(fronte, backe, (char)'E');
    cout << (char)next(fronte, backe) << endl;
    cout << (char)next(fronte, backe) << endl;
    cout << (char)next(fronte, backe) << endl;
    add(fronte, backe, (char)'S');
    add(fronte, backe, (char)'T');
    cout << (char)next(fronte, backe) << endl;
    cout << (char)next(fronte, backe) << endl;
    cout << (char)next(fronte, backe) << endl;
    add(fronte, backe, (char)'I');
    add(fronte, backe, (char)'O');
    cout << (char)next(fronte, backe) << endl;
    add(fronte, backe, (char)'N');
    cout << (char)next(fronte, backe) << endl;
    cout << (char)next(fronte, backe) << endl;
    cout << (char)next(fronte, backe) << endl;



    // ex. 4
    /*elem* top = NULL;
    push(top, (int)'E');
    push(top, (int)'A');
    cout << (char)pop(top) << endl;
    push(top, (int)'S');
    cout << (char)pop(top) << endl;
    push(top, (int)'Y');
    cout << (char)pop(top) << endl;
    cout << (char)pop(top) << endl;
    push(top, (int)'Q');
    push(top, (int)'U');
    push(top, (int)'E');
    cout << (char)pop(top) << endl;
    push(top, (int)'S');
    push(top, (int)'T');
    cout << (char)pop(top) << endl;
    cout << (char)pop(top) << endl;
    cout << (char)pop(top) << endl;
    push(top, (int)'I');
    push(top, (int)'O');
    cout << (char)pop(top) << endl;
    push(top, (int)'N');
    cout << (char)pop(top) << endl;
    cout << (char)pop(top) << endl;
    cout << (char)pop(top) << endl;*/



    // ex. 5
    /*elem* stack1 = NULL;
    elem* stack2 = NULL;

    enqueue(stack1, stack2, 5);
    enqueue(stack1, stack2, 4);
    enqueue(stack1, stack2, 3);
    enqueue(stack1, stack2, 2);
    enqueue(stack1, stack2, 1);
    cout << dequeue(stack1, stack2) << endl;
    cout << dequeue(stack1, stack2) << endl;
    enqueue(stack1, stack2, 50);
    cout << dequeue(stack1, stack2) << endl;
    cout << dequeue(stack1, stack2) << endl;
    cout << dequeue(stack1, stack2) << endl;
    cout << dequeue(stack1, stack2) << endl;*/



    // ex. 6
    /*int n = 10;
    int front = 0;
    int back = 0;
    int tablica[n];
    // front <--- back

    cout << isEmpty_array(front, back) << endl;
    enqueue_array(tablica, n, back, 102);
    cout << isEmpty_array(front, back) << endl;
    cout << firstEl_array(tablica, front, back) << endl;
    enqueue_array(tablica, n, back, 15);
    enqueue_array(tablica, n, back, 10);
    enqueue_array(tablica, n, back, 403);

    cout << "===" << endl;
    cout << dequeue_array(tablica, front, back) << endl;
    cout << dequeue_array(tablica, front, back) << endl;
    cout << dequeue_array(tablica, front, back) << endl;
    cout << dequeue_array(tablica, front, back) << endl;*/



    // ex. 7.1
    /*elem* stack1 = NULL;
    push(stack1, 23);
    push(stack1, 465);
    push(stack1, 123);

    elem* stack2 = NULL;
    push(stack2, pop(stack1));
    push(stack2, pop(stack1));
    push(stack2, pop(stack1));
    stack1 = stack2;

    cout << pop(stack1) << endl;
    cout << pop(stack1) << endl;
    cout << pop(stack1) << endl;*/

    // ex. 7.2
    /*elem* stack1 = NULL;
    push(stack1, 23);
    push(stack1, 465);
    push(stack1, 123);

    elem* fronte = NULL;
    elem* backe = NULL;
    add(fronte, backe, pop(stack1));
    add(fronte, backe, pop(stack1));
    add(fronte, backe, pop(stack1));
    push(stack1, next(fronte, backe));
    push(stack1, next(fronte, backe));
    push(stack1, next(fronte, backe));

    cout << pop(stack1) << endl;
    cout << pop(stack1) << endl;
    cout << pop(stack1) << endl;*/



    // ex. 8
    /*elem* stack1 = NULL;
    push(stack1, 105);
    push(stack1, 2);
    push(stack1, 255);
    push(stack1, 1);
    push(stack1, 1075);

    sortStack(stack1);

    cout << pop(stack1) << endl;
    cout << pop(stack1) << endl;
    cout << pop(stack1) << endl;
    cout << pop(stack1) << endl;
    cout << pop(stack1) << endl;*/



    // ex. 9
    /*elem* stack1 = NULL;
    elem* stack2 = NULL;
    elem* stackTmp = NULL;

    push(stack1, 32);
    push(stack1, 57);
    push(stack1, 103);
    push(stack1, 2);
    push(stack1, 5);*/

    // ex. 9.1
    /*push(stackTmp, pop(stack1));
    push(stackTmp, pop(stack1));
    push(stackTmp, pop(stack1));
    push(stackTmp, pop(stack1));
    push(stackTmp, pop(stack1));

    push(stack2, pop(stackTmp));
    push(stack2, pop(stackTmp));
    push(stack2, pop(stackTmp));
    push(stack2, pop(stackTmp));
    push(stack2, pop(stackTmp));

    cout << pop(stack2) << endl;
    cout << pop(stack2) << endl;
    cout << pop(stack2) << endl;
    cout << pop(stack2) << endl;
    cout << pop(stack2) << endl;*/

    // ex. 9.2
    //if(isEmpty(stack1)) return;

    /*int n = 1;
    elem* tmpElement = stack1;
    while(tmpElement->nast != NULL)
    {
        tmpElement = tmpElement->nast;
        ++n;
    }

    if(n == 1)
        push(stack2, pop(stack1));

    for(int i = 0; i < n; i++)
    {
        int dane;
        int x = n - i - 1;

        for(int j = 0; j < x; j++)
        {
            push(stack2, pop(stack1));
        }

        dane = pop(stack1);

        for(int j = 0; j < x; j++)
        {
            push(stack1, pop(stack2));
        }

        push(stack2, dane);
    }

    cout << pop(stack2) << endl;
    cout << pop(stack2) << endl;
    cout << pop(stack2) << endl;
    cout << pop(stack2) << endl;
    cout << pop(stack2) << endl;*/

    return 0;
}
