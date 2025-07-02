#include <iostream>
#include <ctime>

using namespace std;


template <typename T>
class List
{
    public:
        List();
        ~List();
        void push_back(T data);
        int Get_Size();
        void del(const T index);
        void pop_front();
        void clear();
        
        T& operator[](const int index)
        {
            int counter=0;
            Node* current = head;
            while (current!=nullptr && counter!=index)
            {
                
                current=current->pNext;
                counter++;
            }
            return current->data;
        }
    private:
        
        class Node
        {
            public:
                T data;
                Node* pNext;
                Node(T data=T(), Node* pNext=nullptr)
                {
                     this->data= data;
                     this->pNext=pNext;
                }
        };
        Node* head;
        int Size;
};
template <typename T>
List<T>::List()
{
    head = nullptr;
    Size=0;
}
template <typename T>
List<T> :: ~List()
{
    clear();
}
template <typename T>
void List <T> :: push_back(T data)
{
    if (head == nullptr)
    {
        head=new Node(data);
    }
    else{
        Node *current = head;
        while (current->pNext!= nullptr)
        {
            current=current->pNext;
        }
        current->pNext=new Node (data);
        
    }
    Size++;
}
template <typename T>
int List<T> :: Get_Size()
{
    return Size;
}
template <typename T>
void List<T> :: pop_front()
{
    if (Size>0)
    {
        Node* temp = head;
        head=head->pNext;
        Size--;
        delete temp;
    }
    else
    {
        cout<<"No elements";
        return;
    }

}

template <typename T>
void List<T> :: clear()
{
    while (Size)
    {
        pop_front();
    }
}

template <typename T>
void List<T> :: del(const T element)
{
    Node* prev = nullptr;
    Node* current = head;
    Node* prev_toDelete = nullptr;
    Node* current_toDelete = nullptr;

    while (current !=nullptr)
    {
        if (current->data == element)
        {
            prev_toDelete=prev;
            current_toDelete=current;
        }
        prev=current;
        current=current->pNext;
    }

    if (current_toDelete==nullptr)
    {
        cout<<"Element not found";
        return;
    }
    if (prev_toDelete==nullptr)
    {
        head=current_toDelete->pNext;
    }
    else
    {
        prev_toDelete->pNext=current_toDelete->pNext;
    }
    delete current_toDelete;
    Size--;


}


int main()
{
    List <int> lst;
    int size, k;
    cout<<"Input size of list: "<<endl;
    cin>>size;
    srand(time(NULL));
    for (int i =0; i<size; i++)
    {
        lst.push_back(rand()%10);
    }

    for (int i =0; i<size; i++)
    {
        cout<<lst[i]<<" ";
    }
    cout<<"Input element to delete: "<<endl;
    cin>>k;
    lst.del(k);
    for (int i =0; i<lst.Get_Size(); i++)
    {
        cout<<lst[i]<<" ";
    }
}