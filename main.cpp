#include<bits/stdc++.h>

using namespace std;

int n = 0;

struct travel
{
    string tDate;
    int cost;
    string from;
    string to;
    travel* next;
};

struct node
{
    string name;
    string family;
    string joinDate;
    int credit;
    int travels = 0;
    node* link = NULL;
    travel* firstTravel = NULL;
    travel* lastTravel = NULL;
};

int compare (const void * a, const void * b)
{
    struct node *orderA = (struct node *)a;
    struct node *orderB = (struct node *)b;
    if( orderA->travels>orderB->travels)
        return(1);
    else
        return (0);
}

node* SortedMerge(node* a, node* b);
void FrontBackSplit(node* source,
                    node** frontRef, node** backRef);

/* sorts the linked list by changing next pointers (not data) */
void MergeSort(node** headRef)
{
    node* head = *headRef;
    node* a;
    node* b;

    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->link == NULL)) {
        return;
    }

    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);

    /* Recursively sort the sublists */
    MergeSort(&a);
    MergeSort(&b);

    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b);
}

node* SortedMerge(node* a, node* b)
{
    node* result = NULL;

    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    /* Pick either a or b, and recur */
    if (compare(a,b)) {
        result = a;
        result->link = SortedMerge(a->link, b);
    }
    else {
        result = b;
        result->link = SortedMerge(a, b->link);
    }
    return (result);
}

void FrontBackSplit(node* source,
                    node** frontRef, node** backRef)
{
    node* fast;
    node* slow;
    slow = source;
    fast = source->link;

    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL) {
        fast = fast->link;
        if (fast != NULL) {
            slow = slow->link;
            fast = fast->link;
        }
    }

    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->link;
    slow->link = NULL;
}

void swap(node** head,node* previousA, node* currA,node* previousB,node* currB)
{
    if(previousA)
        currA=previousA->link;
    if(previousB)
        currB=previousB->link;
    if (currA == NULL || currB == NULL)
        return;

    if (previousA != NULL)
        previousA->link = currB;
    else
        *head = currB;

    if (previousB != NULL)
        previousB->link = currA;
    else
        *head = currA;

    node *temp = currB->link;
    currB->link = currA->link;
    currA->link = temp;

}

void BubbleSort(node** head,int k)
{
    node* temp = *head;
    node* previous = NULL;
    for(int i=0;i<k;i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compare(temp, temp->link))
                swap(head,previous,temp, temp,temp->link);
            previous = temp;
            temp = temp->link;
        }
        temp=*head;
    }
}


void pushBackNode(node** head, node** tail, string name, string family, string joinDate)
{
    node* temp = new node;
    temp->name = name;
    temp->family = family;
    temp->joinDate = joinDate;
    temp->credit = 0;
    if (!*head)
    {
        *head = temp;
    }
    if (*tail)
    {
        (*tail)->link = temp;
    }
    *tail = temp;
    n++;
}

void pushBackTravel(int credit,travel** head, travel** tail, string tDate, int cost, string from,string to)
{
    if (credit > cost)
    {
        travel* temp = new travel;
        temp->tDate = tDate;
        temp->cost = cost;
        temp->from = from;
        temp->to = to;
        if (!*head)
        {
            *head = temp;
        }
        if (*tail)
        {
            (*tail)->next = temp;
        }
        *tail = temp;
    }
}

void printNodes(node* head)
{
    node* temp = head;
    while (temp)
    {
        cout << "Name: " << temp->name << "\t" << "Family: " << temp->family << "\t" << "Credit: " << temp->credit << "\t" << "Join Date: " << temp->joinDate << endl;
        temp = temp->link;
    }
}

int main()
{
    node* head = NULL, * tail = NULL;
    pushBackNode(&head, &tail, "Saman", "hosieni", "1398");
    pushBackNode(&head, &tail, "Mmd", "Rezai", "1398");
    printNodes(head);
    return 0;
}