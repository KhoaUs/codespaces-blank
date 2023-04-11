#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
};

typedef struct Node* node;

//Cap phat dong mot node vs data x
node makeNode(int x)
{
    node temp = new Node();
    temp->data = x;
    temp->next = NULL;
    return temp;
}

//Kiem tra rong
bool empty (node a)
{
    return a == NULL;
}

//Ham tinh so luong node trong danh sach lien ket
int Size (node a)
{
    int size = 0;
    //Ctr dung khi con tro chay den cuoi danh sach
    while (a != NULL)
    {
        size++;
        a = a->next;        //Gan dia chi cua node tiep theo cho node hien tai. 
    }
    return size;
}

//Them mot phtu vao dau danh sach lien ket
void insertHead (node& a, int x)
{
    node temp = makeNode(x);
    if(a == NULL)
    {
        a = temp;
    }
    else
    {
        temp->next = a;
        a = temp;
    }
}

//Them phan tu vao cuoi danh sach
void insertLast (node &a, int x)
{
    node temp = makeNode(x);
    if(a == NULL)
    {
        a = temp;
    }
    else
    {
        node p = a;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = temp;
    }
}

//Chen phan tu vao giua danh sach lien ket, head = 1;
void insertMiddle (node& a, int x, int pos)
{
    int n = Size(a);
    if(pos < 1 || pos > n + 1)
    {
        cout << "Vi tri chen khong hop le!" << endl;
    }
    else if (pos == 1)
    {
        insertHead(a, x);
        return;
    }
    else if (pos == n + 1)
    {
        insertLast(a, x);
        return;
    }
    else
    {
        node temp = makeNode(x);
        node p = a;

        for (int i = 1; i < pos - 1; i++)
        {
            p = p->next;
        }
        temp->next = p->next;
        p->next = temp;
    }
}

//Xoa phan tu o dau
void deleteFirst (node& a)
{
    if (a == NULL) return;
    node p = a;
    a = a->next;
    delete p;
}

//Xoa phan tu o cuoi
void deleteLast (node& a)
{
    if (a == NULL) return;

    if (a->next == NULL)
    {
        delete a;
        a = NULL;
        return;
    }

    node p = a;
    while (p->next->next != NULL)
    {
        p = p->next;
    }
    delete p->next;
    p->next = NULL;
}

void deleteMiddle (node& a, int pos)
{
    if (pos < 1 || pos > Size(a)) return;

    if (pos == 1)
    {
        deleteFirst(a);
        return;
    }

    if (pos == Size(a))
    {
        deleteLast(a);
        return;
    }

    node p = a;
    for (int i = 1; i < pos - 1; i++)
    {
        p = p->next;
    }
    node temp = p->next;
    p->next = p->next->next;
    delete temp;
}

void in(node a)
{
    cout << "------------------------------" << endl;
    while (a != NULL)
    {
        cout << a->data << endl;
        a = a->next;
    }
}


int main()
{
    int i = 1, pos, x;
    node head = NULL;
    while (i != 0)
    {
        int n;
        cout << "1. Chen phtu vao dau! \n";
        cout << "2. Chen phtu vao cuoi \n";
        cout << "3. Chen phtu vao giua! \n";
        cout << "4. Xoa phtu o dau! \n";
        cout << "5. Xoa phtu o giua! \n";
        cout << "6. Xoa phtu o cuoi! \n";
        cout << "7. In danh sach lien ket! \n";
        cout << "--------------@--------------\n";
        cin >> n;
        switch (n)
        {
            case 1:
                cout << "Nhap data: ";
                cin >> x;
                insertHead(head, x);
                break;
            case 2:
                cout << "Nhap data: ";
                cin >> x;
                insertLast(head, x);
                break;
            case 3:
                cout << "Nhap data va pos: ";
                cin >> x >> pos;
                insertMiddle (head, x, pos);
                break;
            case 4:
                deleteFirst(head);
                break;
            case 5:
                deleteLast(head);
                break;
            case 6:
                cout << "Nhap pos: ";
                cin >> pos;
                deleteMiddle(head, pos);
                break;
            case 7:
                in(head);
                break;
            default:
                i = 0;     
        }
    }

    return 0;
}