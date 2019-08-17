#include<bits/stdc++.h>

using namespace std;

int n = 0;

struct travel {
    int tDate;
    int cost;
    string from;
    string to;
    travel *next = NULL;
};

struct node {
    string name;
    string family;
    int joinDate;
    int credit;
    int travels = 0;
    node *link = NULL;
    travel *firstTravel = NULL;
    travel *lastTravel = NULL;
};

bool compare(const void *a, const void *b) {
    struct node *orderA = (struct node *) a;
    struct node *orderB = (struct node *) b;
    if (orderA->travels > orderB->travels)
        return true;
    else
        return false;
}

node *SortedMerge(node *a, node *b);

void FrontBackSplit(node *source,
                    node **frontRef, node **backRef);

/* sorts the linked list by changing next pointers (not data) */
void MergeSort(node **headRef) {
    node *head = *headRef;
    node *a;
    node *b;

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

node *SortedMerge(node *a, node *b) {
    node *result = NULL;

    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    /* Pick either a or b, and recur */
    if (compare(a, b)) {
        result = a;
        result->link = SortedMerge(a->link, b);
    } else {
        result = b;
        result->link = SortedMerge(a, b->link);
    }
    return (result);
}

void FrontBackSplit(node *source,
                    node **frontRef, node **backRef) {
    node *fast;
    node *slow;
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

void swap(node **head, node *previousA, node *currA, node *previousB, node *currB) {
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

void printNodes(node *head);

void BubbleSort(node **head, int k) {
    node *temp = *head;
    node *previous = NULL;
    cout << n << endl;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n - i - 1; j++) {

            //printNodes(temp);
            //cout<<"swap:"<<endl;
            if (compare(temp, temp->link))
                swap(head, previous, temp, temp, temp->link);
            previous = temp;
            temp = temp->link;
        }
        previous = NULL;
        temp = *head;
    }
}


void pushBackNode(node **head, node **tail, string name, string family, int joinDate) {
    node *temp = new node;
    temp->name = name;
    temp->family = family;
    temp->joinDate = joinDate;
    temp->credit = 0;
    if (!*head) {
        *head = temp;
    }
    if (*tail) {
        (*tail)->link = temp;
    }
    *tail = temp;
    n++;
}

void pushBackTravel(node *user, int tDate, int cost, string from, string to) {
    travel **head = &user->firstTravel;
    travel **tail = &user->lastTravel;
    if (user->credit >= cost) {
        travel *temp = new travel;
        temp->tDate = tDate;
        temp->cost = cost;
        temp->from = from;
        temp->to = to;
        if (!*head) {
            *head = temp;
        }
        if (*tail) {
            (*tail)->next = temp;
        }
        *tail = temp;
        user->travels++;
    }
}

void printNodes(node *head, int k) {
    node *temp = head;
    if (k > n)
        k = n;
    for (int i = 0; i < k; ++i) {
        cout << "Name: " << temp->name << "\t" << "Family: " << temp->family << "\t" << "Credit: " << temp->credit
             << "\t" << "Join Date: " << temp->joinDate << "\t" << "Travels: " << temp->travels << endl;
        temp = temp->link;
    }
    cout << "---------------------------------------" << endl;
}

void printTRavels(travel *head) {
    travel *temp = head;
    while (temp) {
        cout << "cost: " << temp->cost << "\t" << "From: " << temp->from << "\t" << "to: " << temp->to << "\t"
             << "Join Date: " << temp->tDate << endl;
        temp = temp->next;
    }
}

node *findUser(node *head, string name) {
    node *temp = head;
    while (temp->name != name)
        temp = temp->link;
    return temp;
}
node *shiftHead(node *head, int date) {
    node *temp = head;
    while (temp->joinDate != date)
        temp = temp->link;
    return temp;
}

void increaseCredit(node *temp, int amount) {
    temp->credit += amount;
}

int main() {

    node *head = NULL, *tail = NULL;
    //pushBackNode(&head, &tail, "Saman", "hosieni", 1398);
    //pushBackNode(&head, &tail, "Mmd", "Rezai", 1398);
    //pushBackNode(&head, &tail, "ali", "Rezai", 1398);
    //node *mmd = head->link;
    //node *ali = mmd->link;
    //BubbleSort(&head, 3);
    //swap(&head,mmd,ali,NULL,head);

    cout
            << "1) Add User\n2) Increase Credit\n3) New Trip\n4) Generate Discounts\n5) Print Users\n6) Print Trips\n7) New Users Discount\n)8) Exit\n";
    int command;
    cin >> command;
    string name, family;
    int date;
    while (true) {
        switch (command) {
            case 1: {
                cout << "Name Family Date\n";
                cin >> name >> family >> date;
                pushBackNode(&head, &tail, name, family, date);
                break;
            }
            case 2:
                cout << "Name Amount\n";
                int amount;
                cin >> name >> amount;
                increaseCredit(findUser(head, name), amount);
                break;
            case 3: {
                cout << "Name Date Cost From To\n";
                int cost;
                string from, to;
                cin >> name >> date >> cost >> from >> to;
                pushBackTravel(findUser(head, name), date, cost, from, to);
                break;
            }
            case 4: {
                cout << "Enter K\n";
                int k;
                cin >> k;
                if (k < log(n))
                    BubbleSort(&head, k);
                else
                    MergeSort(&head);
                printNodes(head, k);
                break;
            }
            case 5:
                printNodes(head, n);
                break;
            case 6:
                cout << "Name \n";
                cin >> name;
                printTRavels(findUser(head, name)->firstTravel);
                break;
            case 7: {
                int k;
                cout << "Date K";
                cin >> date >> k;
                node* temp = shiftHead(head,date);
                if (k < log(n))
                    BubbleSort(&temp, k);
                else
                    MergeSort(&temp);
                printNodes(temp, k);
                break;
            }
            default:
                return 0;
        }
        cout
                << "1) Add User\n2) Increase Credit\n3) New Trip\n4) Generate Discounts\n5) Print Users\n6) Print Trips\n7) New Users Discount\n)8) Exit\n";
        cin >> command;
    }
}