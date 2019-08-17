#include<bits/stdc++.h>

using namespace std;

void Merge(int arr[], int l, int mid, int r)
{
    int temp[r - l];
    for (int i = l; i < r; i++)
        temp[i - l] = arr[i];
    int cnt1 = 0, cnt2 = 0;
    while (cnt1 + cnt2 < r - l)
        if ((cnt2 == r - mid) || (cnt1 < mid - l && temp[cnt1] < temp[cnt2 + mid - l]))
            arr[l + cnt1 + cnt2] = temp[cnt1++];
        else
            arr[l + cnt1 + cnt2] = temp[(cnt2++) + mid - l];
}

void MergeSort(int arr[], int l, int r)
{
    if (r - l == 1)
        return;
    MergeSort(arr, l, (r + l) / 2);
    MergeSort(arr, (r + l) / 2, r);
    Merge(arr, l, (r + l) / 2, r);
}

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
    node* link = NULL;
    travel* firstTravel = NULL;
    travel* lastTravel = NULL;
};


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