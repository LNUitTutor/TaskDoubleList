#pragma once
#include <iostream>
#include <fstream>
#include <exception>

template <typename Type>
class DoubleLinkedList
{
private:
	struct Node
	{
		Type value;
		Node* prev;
		Node* next;
		Node(Type x = Type(), Node* p = nullptr, Node* n = nullptr)
			:value(x), prev(p), next(n) { }
		~Node() { delete next; }
	};
	Node* head;
	Node* tail;
	unsigned count;
public:
	DoubleLinkedList() :head(nullptr), tail(nullptr), count(0) { }
	DoubleLinkedList(const DoubleLinkedList& list);
	DoubleLinkedList(std::ifstream& fin);
	~DoubleLinkedList() { delete head; }
	DoubleLinkedList& operator=(const DoubleLinkedList& list);
	DoubleLinkedList& addFirst(const Type& data);
	DoubleLinkedList& addLast(const Type& data);
	Type& delFirst();
	Type& delLast();
	void printOn(std::ostream& os) const;
	void reversePrintOn(std::ostream& os) const;
	bool isEmpty() const { return count == 0; }
	unsigned size() const { return count; }
	DoubleLinkedList& removeDoubles();
	DoubleLinkedList& sort();

	typedef void (*Action)(Type& x);
	DoubleLinkedList& forEach(Action act);
	DoubleLinkedList& forEachReverse(Action act);
};

template<typename Type>
inline DoubleLinkedList<Type>::DoubleLinkedList(const DoubleLinkedList& list)
	:count(list.count)
{
	if (list.head == nullptr)
	{
		head = tail = nullptr; return;
	}
	tail = head = new Node(list.head->value);
	Node* curr = list.head->next;
	while (curr != nullptr)
	{
		tail->next = new Node(curr->value, tail);
		tail = tail->next;
		curr = curr->next;
	}
}

template<typename Type>
inline DoubleLinkedList<Type>::DoubleLinkedList(std::ifstream& fin)
	:head(nullptr), tail(nullptr), count(0)
{
	if (!fin.is_open()) throw std::runtime_error("The file is not opened for input");
	Type data;
	if (fin >> data)
	{
		head = tail = new Node(data);
		++count;
	}
	while (fin >> data)
	{
		tail = tail->next = new Node(data, tail);
	}
}

template<typename Type>
inline DoubleLinkedList<Type>& DoubleLinkedList<Type>::operator=(const DoubleLinkedList<Type>& list)
{
	if (this != &list)
	{
		delete head;
		count = list.count;
		if (list.head == nullptr) head = tail = nullptr;
		else
		{
			tail = head = new Node(list.head->value);
			Node* curr = list.head->next;
			while (curr != nullptr)
			{
				tail->next = new Node(curr->value, tail);
				tail = tail->next;
				curr = curr->next;
			}
		}
	}
	return *this;
}

template<typename Type>
inline DoubleLinkedList<Type>& DoubleLinkedList<Type>::addFirst(const Type& data)
{
	if (this->isEmpty()) head = tail = new Node(data);
	else head = head->prev = new Node(data, nullptr, head);
	++count;
	return *this;
}

template<typename Type>
inline DoubleLinkedList<Type>& DoubleLinkedList<Type>::addLast(const Type& data)
{
	if (this->isEmpty()) head = tail = new Node(data);
	else tail = tail->next = new Node(data, tail);
	++count;
	return *this;
}

template<typename Type>
inline void DoubleLinkedList<Type>::printOn(std::ostream& os) const
{
	if (this->isEmpty()) os << "<Empty List>";
	else
	{
		os << this->head->value;
		Node* curr = this->head->next;
		while (curr != nullptr)
		{
			os << " -> " << curr->value;
			curr = curr->next;
		}
	}
}

template<typename Type>
inline void DoubleLinkedList<Type>::reversePrintOn(std::ostream& os) const
{
	if (this->isEmpty()) os << "<Empty List>";
	else
	{
		os << this->tail->value;
		Node* curr = this->tail->prev;
		while (curr != nullptr)
		{
			os << " <- " << curr->value;
			curr = curr->prev;
		}
	}
}