#pragma once
#include <iostream>
#include <iomanip>

template<typename T>
class single_list
{
private:
	struct NodeList {
		T value;
		NodeList* next;

		NodeList(T _value) : value(_value), next(nullptr) {};
	};

	NodeList* first;
	NodeList* last;

public:
	single_list() : first(nullptr), last(nullptr) {};

	bool is_empty() {
		return first == nullptr;
	}

	void push_back(T _value) {
		NodeList* temp = new NodeList(_value);

		if (is_empty()) {
			first = temp;
			last = temp;
		}
		else {
			last->next = temp;
			last = temp;
		}

		return;
	}

	NodeList* get_node(int _index) {
		if (_index < 0 || is_empty() || _index > get_count_elem()) return nullptr;

		NodeList* temp = first;
		int count = 0;

		for (; temp != nullptr && count < _index;
			temp = temp->next)
		{
			count++;
		}

		return temp;
	}

	T get_value(int _index) {
		NodeList* temp = get_node(_index);
		return temp ? temp->value : nullptr;
	}

	NodeList* get_last() {
		if (is_empty()) return nullptr;
		return last;
	}

	T get_last_val() {
		return last->value;
	}

	void set_value(int _index, T _value) {
		if (_index < 0 || is_empty()) return;

		NodeList* temp = get_node(_index);

		if (temp) temp->value = _value;

		return;
	}

	T operator[](int _index) {
		NodeList* temp = get_node(_index);
		return temp ? temp->value : nullptr;
	}

	int get_count_elem()
	{
		if (is_empty()) return 0;

		NodeList* temp = first;
		int result = 0;

		while (temp) {
			result++;
			temp = temp->next;
		}

		return result;
	}

	void remove_node(int _index) {
		if (_index < 0 || is_empty()) return;

		NodeList* temp_rm = get_node(_index);
		NodeList* temp_prev = get_node(_index - 1);
		NodeList* temp_next = get_node(_index + 1);

		if (temp_next) temp_prev->next = temp_next;
		else temp_prev->next = nullptr;
		delete temp_rm;

		return;
	}

	void remove_last_node() {
		if (is_empty() || first == last) return;

		NodeList* temp = first;
		while (temp->next != last) {
			temp = temp->next;
		}

		delete last;
		last = temp;
		last->next = nullptr;
		return;
	}

	~single_list() {
		if (is_empty()) return;

		NodeList* temp_now = first;
		NodeList* temp_next = first->next;

		while (temp_now != nullptr) {
			delete temp_now;
			temp_now = nullptr;
			temp_now = temp_next;
			if (temp_next && temp_next->next) temp_next = temp_next->next;
			else temp_next = nullptr;
		}

		return;
	}
};

