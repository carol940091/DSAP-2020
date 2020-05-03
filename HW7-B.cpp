#include<iostream>
#include<stdexcept>
#include<string>
using namespace std;

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
  virtual bool push( const char& newEntry) = 0;

  /** Removes the top of this stack.
      @post If the operation was successful, the top of the stack has been removed.
      @return True if the removal is successful or false if not. */
  virtual bool pop() = 0;

  /** Returns the top of this stack.
      @pre The stack is not empty.
      @post The top of the stack has been returned, and the stack is unchanged.
      @return The top of the stack. */
  virtual char peek() const = 0;
}; 


const int MAX_STACK = 999; // set a value by yourself


class ArrayStack : public StackInterface
{

private:
  char items[MAX_STACK]; // Array of stack items
  int top; // Index to top of stack
public:
  ArrayStack(); // Default constructor
  bool isEmpty() const;
  bool push(const char& newEntry);
  bool pop();
  char peek() const;
  int  getTop() const;
}; 


ArrayStack::ArrayStack() : top(-1)
{
} 


bool ArrayStack::isEmpty() const
{
  return top < 0;
} 


bool ArrayStack::push(const char& newEntry)
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


bool ArrayStack::pop()
{
  bool result = false ;
  if(!this->isEmpty())
  {
    top--;
    result = true ;
  }
  return result;
} 


char ArrayStack::peek() const
{
  if(!this->isEmpty()) // check precondition
    return items[top];

} 

int ArrayStack::getTop() const
{
	return top;
}


int main()
{
	string a;
	ArrayStack charStack;
	while(getline(cin, a))
	{
		for(int i = 0 ; i < a.length(); i++)
		{
		
			if(a[i] == '<')
			{
				if(!charStack.isEmpty())
				    charStack.pop();
			}
			else 
				charStack.push(a[i]);
		
		}
			//cout << "char length  " << charStack.getTop() << "\n"; 
		ArrayStack output;
		while(!charStack.isEmpty())
		{
			output.push(charStack.peek());
			charStack.pop();
		}

		while(!output.isEmpty())
		{
			cout << output.peek();
			output.pop();
		}
		cout << "\n";
	}
	

		 
	
	return 0;

} 
