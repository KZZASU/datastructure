#include <iostream>

using namespace std;

class queue
{
private:
	int size;
	int* q;
	int* front;
	int* end;

public:
	queue() = delete;
	queue(int _size);
	~queue();
	void enqueue(int x);
	int dequeue();
	bool isEmpty();
	bool isFull();
	void display();
};

queue::queue(int _size) : size{ _size }, q{ new int[_size] }
{
	front = q -1;
	end = q - 1;
}

queue::~queue()
{
	delete[] q;
}

void queue::enqueue(int x)
{
	if (isFull())
	{
		cout << "queue is full\n";
		return;
	}
	end++;
	*(this->end) = x;
}

int queue::dequeue()
{
	if (this->isEmpty())
	{
		cout << "queue is empty\n";
		return -1;
	}
	this->front++;
	int x = *(this->front);
	return x;
}

void queue::display()
{
	if (this->isEmpty())
	{
		return;
	}

	int* temp = front;
	while (temp!= end)
	{
		temp++;
		cout << *temp << ' ';
	};
	cout << '\n';
}

bool queue::isEmpty()
{
	if ((this->front == this->end))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool queue::isFull()
{
	if ((this->q + (this->size - 1)) == (this->end))
	{
		return true;
	}
	else
	{
		return false;
	};
}



int main()
{
	queue qq(4);
	qq.enqueue(3);
	qq.display();
	qq.enqueue(123);
	qq.enqueue(456);
	qq.display();
	qq.dequeue();
	qq.enqueue(5);
	qq.display();
}