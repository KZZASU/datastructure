#include <iostream>

using namespace std;
class stack
{
private:
	int size;
	int top;
	int* arr;

public:
	stack(int sz) :size{ sz }, top{ -1 }, arr{ new int[sz] }{};
	~stack() { delete arr; };

	bool isFull() { if (top == size - 1) { return true; } return false; }
	bool isEmpty() { if (top == -1) { return true; } return false; }
	void push(int x)
	{
		if (isFull()) { cout << "stack overflow\n"; return; };
		top++;
		arr[top] = x;
	}
	
	int  pop()
	{
		int x = INT_MIN;
		if (isEmpty()) { cout << "stack underflow\n";}
		else { x = arr[top]; top--;}
		return x;
	}
};


int main()
{
	stack s{ 100 };
	s.push(3);
	s.push(11);
	s.push(4);	
	while (s.isEmpty()==false){ cout << s.pop() << ' '; }

	return 0;
}