#include <iostream>
#include <ctime>
using namespace std;


class Stack
{
    int* arr;
    int top;
    
    public:
        int capacity;
        Stack(int const capacity=10)
        {
            arr=new int[capacity];
            top=-1;
            this->capacity=capacity;
        }
        bool isEmpty()
        {
            return top==-1;
        }
        bool isFull()
        {
            return capacity-1==top;
        }
        void push_back(int element)
        {
            if (!isFull())
            {
                top++;
                arr[top]=element;
            }
            else
            {
                cout<<"Error: stack is full";
                return;
            }
        }
        int pop()
        {
            if (!isEmpty())
            {
                return arr[top--];
            }
            else
            {
                cout<<"Error: stack is empty";
                exit(EXIT_FAILURE);
            }

        }
        int peek()
        {
            if (!isEmpty())
            {
                return arr[top];
            }
        }
        void print_stack()
        {
            for (int i =0; i<capacity; i++)
            {
                cout<<arr[i]<<" ";
            }
            cout<<endl;
        }
};

int* span(Stack st)
{
    int capacity=st.capacity;
    int* arr = new int[capacity];
    for (int i=0; i<capacity; i++)
    {
        Stack temp = st;
        int el=st.pop();
        int counter=0;
        while (!temp.isEmpty() && el>=temp.pop())
        {
            counter++; 
        }
        arr[capacity-i-1]=counter;
        
    }
    return arr;
}

int main()
{
    srand(time(NULL));
    int capacity;
    cout<<"Input size of stack: "<<endl;
    cin>>capacity;
    Stack st(capacity);
    for (int i =0; i<capacity; i++)
    {
        st.push_back(rand()%200);
    }

    int *arr=span(st);
    st.print_stack();
    
    for (int i =0; i<capacity; i++)
    {
        cout<<arr[i]<<" ";
    }

    
    
}