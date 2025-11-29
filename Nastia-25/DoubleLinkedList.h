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
	Type delFirst();
	Type delLast();
	void printOn(std::ostream& os) const;
	void reversePrintOn(std::ostream& os) const;
	bool isEmpty() const { return count == 0; }
	unsigned size() const { return count; }
	DoubleLinkedList& unique();
	DoubleLinkedList& sort();

	typedef void (*Action)(Type& x);
	DoubleLinkedList& forEach(Action act);
	DoubleLinkedList& forEachReverse(Action act);

	// case #1
	// У списку L з кожної групи розташованих підряд рівних елементів залишити лише один
	DoubleLinkedList& removeDuplicates();
	/* Видалити зі списку L після кожного елемента Е один елемент, якщо такий елемент існує
	   і не дорівнює Е */
	DoubleLinkedList& removeNextAfter(const Type& E);
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
		++count;
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
inline Type DoubleLinkedList<Type>::delFirst()
{
	if (this->isEmpty())
		throw std::runtime_error("Impossible to remove from empty list");
	Type data = this->head->value;
	if (this->count == 1)
	{
		delete head;
		head = tail = nullptr;
	}
	else
	{
		Node* victim = head;
		head = head->next;
		head->prev = nullptr;
		victim->next = nullptr;
		delete victim;
	}
	--count;
	return data;
}

template<typename Type>
inline Type DoubleLinkedList<Type>::delLast()
{
	if (this->isEmpty())
		throw std::runtime_error("Impossible to remove from empty list");
	Type data = this->tail->value;
	if (this->count == 1)
	{
		delete tail;
		head = tail = nullptr;
	}
	else
	{
		Node* victim = tail;
		tail = tail->prev;
		tail->next = nullptr;
		victim->prev = nullptr;
		delete victim;
	}
	--count;
	return data;
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

template<typename Type>
inline DoubleLinkedList<Type>& DoubleLinkedList<Type>::unique()
{
	if (this->count < 2) return *this;
	Node* result = head;
	tail = head;
	count = 1;
	head = head->next;
	result->next = nullptr;
	while (head != nullptr)
	{
		Node* check = result;
		while (check != nullptr && check->value != head->value) check = check->next;
		if (check == nullptr) // head->value is unique
		{
			tail->next = head;
			head->prev = tail;
			tail = tail->next;
			head = head->next;
			tail->next = nullptr;
			++count;
		}
		else
		{
			Node* victim = head;
			head = head->next;
			victim->next = nullptr;
			delete victim;
		}
	}
	head = result;
	return *this;
}

template<typename Type>
inline DoubleLinkedList<Type>& DoubleLinkedList<Type>::sort()
{
	if (this->count < 2) return *this;

	Node phantom(0, nullptr, head);
	tail = head;
	head = head->next;
	phantom.next->next = nullptr;
	while (head != nullptr)
	{
		Node* curr = &phantom;
		while (curr->next != nullptr && curr->next->value < head->value)
			curr = curr->next;

		Node* moved = head;
		head = head->next;
		if (curr->next == nullptr)
		{
			moved->prev = curr;
			tail = moved;
		}
		else
		{
			moved->prev = curr->next->prev;
			curr->next->prev = moved;
		}
		moved->next = curr->next;
		curr->next = moved;
	}
	head = phantom.next;
	phantom.next = nullptr;
	return *this;
}

template<typename Type>
inline DoubleLinkedList<Type>& DoubleLinkedList<Type>::forEach(Action act)
{
	Node* curr = this->head;
	while (curr != nullptr)
	{
		act(curr->value);
		curr = curr->next;
	}
	return *this;
}

template<typename Type>
inline DoubleLinkedList<Type>& DoubleLinkedList<Type>::forEachReverse(Action act)
{
	Node* curr = this->tail;
	while (curr != nullptr)
	{
		act(curr->value);
		curr = curr->prev;
	}
	return *this;
}

template<typename Type>
inline DoubleLinkedList<Type>& DoubleLinkedList<Type>::removeDuplicates()
{
	if (this->count < 2) return *this;
	Node* curr = head;
	while (curr != nullptr)
	{
		while (curr->next != nullptr && curr->next->value == curr->value)
		{
			Node* victim = curr->next;
			curr->next = victim->next;
			if (curr->next != nullptr)
			{
				victim->next = nullptr;
				curr->next->prev = curr;
			}
			else tail = curr;
			delete victim;
			--count;
		}
		curr = curr->next;
	}
	return *this;
}

template<typename Type>
inline DoubleLinkedList<Type>& DoubleLinkedList<Type>::removeNextAfter(const Type& E)
{
	if (this->count < 2) return *this;
	Node* curr = head;
	while (curr != nullptr)
	{
		if (curr->value == E && curr->next != nullptr && curr->next->value != E)
		{
			Node* victim = curr->next;
			curr->next = victim->next;
			if (curr->next != nullptr)
			{
				victim->next = nullptr;
				curr->next->prev = curr;
			}
			else tail = curr;
			delete victim;
			--count;
		}
		curr = curr->next;
	}
	return *this;
}
