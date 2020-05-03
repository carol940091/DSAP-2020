#include<iostream>
#include<stdexcept>
#include<string>
#include<math.h>
using namespace std;

template<typename ItemType>
class StackInterface
{
public :
  /** Sees whether this stack is empty.
      @return True if the stack is empty, or false if not. */
  virtual bool isEmpty() const = 0;

  /** Adds a new entry to the top of this stack.
      @post If the operation was successful, newEntry is at the top of the stack.
      @param newEntry The object to be added as a new entry.
      @return True if the addition is successful or false if not. */
  virtual bool push( const ItemType& newEntry) = 0;

  /** Removes the top of this stack.
      @post If the operation was successful, the top of the stack has been removed.
      @return True if the removal is successful or false if not. */
  virtual bool pop() = 0;

  /** Returns the top of this stack.
      @pre The stack is not empty.
      @post The top of the stack has been returned, and the stack is unchanged.
      @return The top of the stack. */
  virtual ItemType peek() const = 0;
}; 


const int MAX_STACK = 3000; // set a value by yourself

template<typename ItemType>
class ArrayStack: public StackInterface<ItemType>
{

private:
  ItemType items[MAX_STACK]; // Array of stack items
  int top; // Index to top of stack
public:
  ArrayStack(); // Default constructor
  bool isEmpty() const;
  bool push(const ItemType& newEntry);
  bool pop();
  ItemType peek() const;
  int  getTop() const;
}; 

template<typename ItemType>
ArrayStack<ItemType>::ArrayStack() : top(-1)
{
} 

template<typename ItemType>
bool ArrayStack<ItemType>::isEmpty() const
{
  return top < 0;
} 

template<typename ItemType>
bool ArrayStack<ItemType>::push(const ItemType& newEntry)
{
  bool result = false ;
  if(this->top < MAX_STACK - 1) // still have room
  {
    top++;
    this->items[top] = newEntry;
    result = true ;
  } 
  return result;
} 

template<typename ItemType>
bool ArrayStack<ItemType>::pop()
{
  bool result = false ;
  if(!this->isEmpty())
  {
    top--;
    result = true ;
  }
  return result;
} 

template<typename ItemType>
ItemType ArrayStack<ItemType>::peek() const
{
  if(!this->isEmpty()) // check precondition
    return items[top];

} 

template<typename ItemType>
int ArrayStack<ItemType>::getTop() const
{
	return top;
}


int precedence(char a)
{
	if(a == '+' || a == '-')
		return 1;
	else if (a == '*' || a == '/')
		return 2;
	else if(a == '^')
		return 3;	
}

bool ifOperator(char a)
{
	if( a == '+' || a == '-' ||a == '*' || a == '/'|| a == '^' || a == ' ')
		return true;
	else
		return false;
}

int operating(int num1, int num2, char opt)
{
	int result = 0;
	if(opt == '+')
		result = num1 + num2;
	else if(opt =='-')
		result = num2 - num1;
	else if(opt == '*') 
		result = num1 * num2;
	else if(opt =='/')
		result = num2 / num1;
	else if(opt =='^')
		result = pow(num2,num1);
	return result;
}


int main()
{
	string a;
	ArrayStack<int>  Stack1;
	ArrayStack<char> Stack2;
	while(getline(cin, a))
	{   
		bool power = false;
		for(int i = 0 ; i < a.length(); i++)
		{
		    //if it's operand put it into Stack1 
			if(!ifOperator(a[i]))
			{   
				int temp = a[i] - 48;
				Stack1.push(temp);
				//if power = true which means the last operator is ^ and we need to do the calculating first
				if(power == true)
				{  
					int num1 = Stack1.peek();
					Stack1.pop();
					int num2 = Stack1.peek();
					Stack1.pop();
					char op = Stack2.peek();
					Stack2.pop();
					int result = operating(num1, num2, op);
					Stack1.push(result);
					power = false;
				}
			}
			else if(a[i] != ' ')
			{
				if(a[i] == '^')
				{
					Stack2.push(a[i]);
					power = true;
				}
				//if it's operator and Stack2 is empty, put the token into Stack2 directly
				if(Stack2.isEmpty())
					Stack2.push(a[i]);
				else if(a[i] != '^')
				{
					char opB = Stack2.peek();
					while(precedence(a[i]) <= precedence(opB))
					{
						char op = Stack2.peek();
						Stack2.pop();
						int num1 = Stack1.peek();
						Stack1.pop();
						int num2 = Stack1.peek();
						Stack1.pop();
						int result = operating(num1, num2, op); 
						Stack1.push(result);
						if(Stack2.isEmpty())
							break;
						else
							opB = Stack2.peek();
					}
					Stack2.push(a[i]);	
				}
			}
		}
		//stage2  calculate the final outcome
	    while(!Stack2.isEmpty())
	    {
	    	char op = Stack2.peek();
	    	Stack2.pop();
	    	int num1 = Stack1.peek();
	    	Stack1.pop();
	    	int num2 = Stack1.peek();
			Stack1.pop();	    	
			int result = operating(num1, num2, op);
			Stack1.push(result);
		}	
		cout << Stack1.peek() << "\n";
		Stack1.pop();
	}
	return 0;
} 
