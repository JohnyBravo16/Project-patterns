#include <iostream>
#define N 10

using namespace std;


class Stack;
class StackIterator;
class StackIteratorNonZero;

class Stack
{
    int items[N];
    int index_stack;
  public:
    friend class StackIterator;
    friend class StackIteratorNonZero;
    Stack()
    {
        index_stack =  0;
    }
    void push(int x)
    {
        items[index_stack++] = x;
    }
    int pop()
    {
        return items[index_stack--];
    }
    bool isEmpty()
    {
        return (index_stack == 0);
    }
    StackIterator *createIterator()const;
    StackIteratorNonZero *createIteratorNonZero()const;
};

class StackIterator
{
    const Stack *stack;
    int index;
  public:
    StackIterator(const Stack *s)
    {
        stack = s;
    }
    void first()
    {
        index = 0;
    }
    void next()
    {
        index++;
    }
    bool isDone()
    {
        return index == stack->index_stack >= N;
    }
    int currentItem()
    {
        return stack->items[index];
    }
};

class StackIteratorNonZero
{
    const Stack *stack;
    int index;
  public:
    StackIteratorNonZero(const Stack *s)
    {
        stack = s;
    }
    void first()
    {
        index = 0;
    }
    void next()
    {
      index++;
      if(stack->items[index] == 0)
        index++;
    }
    bool isDone()
    {
        return index == stack->index_stack >= N;
    }
    int currentItem()
    {
        return stack->items[index];
    }
};

StackIterator *Stack::createIterator()const
{
  return new StackIterator(this);
}

StackIteratorNonZero *Stack::createIteratorNonZero()const
{
  return new StackIteratorNonZero(this);
}

int main()
{
  Stack stack1;
  stack1.push(1);
  stack1.push(2);
  stack1.push(0);
  stack1.push(4);
  stack1.push(5);
  StackIterator *it = stack1.createIterator();
  StackIteratorNonZero *it2 = stack1.createIteratorNonZero();
  it->first();
  cout<<"Zawartosc: "<<it->currentItem()<<endl;
  it->next();
  cout<<"Zawartosc: "<<it->currentItem()<<endl;
  it2->first();
  it2->next();
  cout<<"Zawartosc non-zero: "<<it2->currentItem()<<endl;
  it2->next();
  cout<<"Zawartosc non-zero: "<<it2->currentItem()<<endl;

}