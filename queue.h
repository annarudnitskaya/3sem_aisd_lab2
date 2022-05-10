#pragma once
#include <exception>
using namespace std;

using namespace std;

struct empty_queue : public exception {
	const char* what() const throw () {
		return "Couldn't complete option. Queue is empty.";
	}
};


class queue_el {
private:
	queue_el* next;

	bool data;

public:
	queue_el() {
		next = nullptr;
	}
	explicit queue_el(const bool value) {
		next = nullptr;
		data = value;
	}
	~queue_el() {
		next = nullptr;
	}

	void set_next(queue_el* const next_el) {
		next = next_el;
	};
	void set_data(bool new_data) {
		data = new_data;
	};


	queue_el* get_next() {
		return next;
	};
	bool get_data() {
		return data;
	};

	void clr_next() {
		delete this;
		next = nullptr;
	};
};


class queue {
private:
	queue_el* front;
	queue_el* back;
	queue_el* temp;

	size_t queue_size;

public:
	queue() {
		front = nullptr;
		back = nullptr;
		temp = nullptr;
		queue_size = 0;
	}

	~queue() {
		while (queue_size != 0) {
			this->dequeue();
		}
		front = nullptr;
		back = nullptr;
		temp = nullptr;
		queue_size = 0;
	}

	queue_el* get_front() {
		return front;
	}

	queue_el* get_back() {
		return back;
	}

	void enqueue(bool data) {
		temp = new queue_el(data);
		if (queue_size == 0) {
			front = temp;
			back = temp;
			temp = nullptr;
			queue_size++;
			return;
		}
		back->set_next(temp);
		back = back->get_next();

		temp = nullptr;
		queue_size++;
	}

	bool dequeue() {
		if (queue_size == 0) {
			throw empty_queue();
		}
		bool front_data;
		front_data = front->get_data();
		if (queue_size == 1) {
			front = nullptr;
			back = nullptr;
			temp = nullptr;
			queue_size = 0;
			return front_data;
		}
		temp = front;
		front = front->get_next();
		temp->clr_next();

		temp = nullptr;
		queue_size--;
		return front_data;
	};

	bool isEmpty() {
		if (queue_size == 0)
			return true;
		else
			return false;
	}

	bool peek() {
		if (queue_size == 0) {
			throw empty_queue();
		}
		return front->get_data();
	}

	size_t get_size() {
		return queue_size;
	}

	void show_queue()
	{
		queue_el* temp = front;
		for (int i = 0; i < queue_size; i++)
		{
			if (temp->get_data() == false)
				cout << "0";
			else
				cout << "1";
			temp = temp->get_next();
		}


	}

	bool compare(string line, bool found) {
		if (line.length() == queue_size && found == false) {
			queue_el* temp = front;
			int i;
			for (i = 0; i < queue_size; i++)
			{
				if ((temp->get_data() == false && line[i] != '0') || (temp->get_data() == true && line[i] != '1'))
					break;
				temp = temp->get_next();

			}
			if (i == queue_size)
				return true;
			else
				return false;

		}

	}
}; 
