#pragma once

#include <stdexcept>
#include "account.h"

template <class T>
class Element
{
public:
	Element(T& data, Element* next, Element* last)
	{
		this->data = data;
		this->next = next;
		this->last = last;
	};

	Element<T>* getNext() const
	{
		return next;
	};

	Element<T>* getPrevious() const
	{
		return last;
	};

	T& getData()
	{
		return data;
	};

	void setNext(Element<T>* pElement)
	{
		next = pElement;
	};

	void setPrevious(Element<T>* pElement)
	{
		last = pElement;
	};

private:
	T data;
	Element* next;
	Element* last;
};

template <class T>
class ReVector
{
public:
	ReVector()
	{
		this->first = nullptr;
		this->last = nullptr;
	};

	void pop_front()
	{
		if (first)
		{
			Element<T>* pElement = first;
			pElement = pElement->getNext();
			delete first;
			first = pElement;
		}
	};

	void pop_back()
	{
		if (last)
		{
			Element<T>* cur = last;
			cur = cur->getPrevious();
			delete cur->getNext();
		}
	};
	;

	void pop(int index) const
	{
		size_t i = 0;

		Element<T>* el = first;

		while (el != nullptr && i != index)
		{
			i++;
			el = el->getNext();
		}

		if (i != index)
			return;

		Element<T>* previous = el->getPrevious(), * next = el->getNext();

		if (next == nullptr)
			next->setPrevious(previous);

		previous->setNext(next);

		delete el;
	};

	void push_front(T data)
	{
		Element<T>* pEl = new Element<T>(data);
		last = pEl;

		if (first)
		{
			Element<T>* tmp = first;
			first = pEl;
			pEl->setNext(tmp);
		}
		else
		{
			first = pEl;
			pEl->setNext(nullptr);
		}
	};

	void push_back(T data)
	{
		auto* pElement = new Element<T>(data, nullptr, last);
		last = pElement;

		if (first)
		{
			Element<T>* current = first;
			while (current->getNext())
				current = current->getNext();

			current->setNext(pElement);
		}
		else
			first = pElement;
	};

	size_t size() const
	{
		size_t counter = 0;

		Element<T>* el = this->first;

		while (el != nullptr)
		{
			counter++;
			el = el->getNext();
		}

		return counter;
	};

	T& operator[](int index) const
	{
		size_t i = 0;

		Element<T>* el = first;

		while (el != nullptr && i != index)
		{
			i++;
			el = el->getNext();
		}

		if (i != index)
			throw std::out_of_range("out of range");

		return el->getData();
	};

private:
	Element<T>* first;

	Element<T>* last;
};