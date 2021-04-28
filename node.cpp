#include <iostream>
#include <initializer_list>

using namespace std;

class LinkedList;
class Node
{
private:
	int m_value;
	Node* m_next;

public:
	Node() :m_value{ 0 }, m_next{ nullptr }{};
	Node(int value) :m_value{ value }, m_next{ nullptr }{};
	friend class LinkedList;
};


class LinkedList
{
public:
	typedef size_t size_type;

	LinkedList(size_type n) :m_size{ n }
	{
		first = new Node;
		last = first;
		for (size_type i{ 0 }; i < n; i++)
		{
			Node* temp = new Node;
			last->m_next = temp;
			last = temp;
			i++;
		}
	};

	LinkedList(initializer_list<int> init_):m_size{init_.size()}
	{
		first = new Node{ *(init_.begin()) };
		last = first;
		for (size_type i{ 1 }; i < m_size; i++)
		{
			Node* temp = new Node;
			temp->m_value = *(init_.begin() + i);
			last->m_next = temp;
			last = temp;
		}
	};

	~LinkedList()
	{
		Node* toggle = first;
		while (first)
		{
			first = first->m_next;
			delete toggle;
			toggle = first;
		}
	}

	void display()
	{
		Node* toggle = first;
		while (toggle)
		{
			cout << toggle->m_value << ' ';
			toggle = toggle->m_next;
		}
		cout << '\n';
	}

	void append(int x)
	{
		Node* temp = new Node{ x };
		last->m_next = temp;
		last = temp;
		++m_size;
	}

private:
	Node* first;
	Node* last;
	size_type m_size;
};