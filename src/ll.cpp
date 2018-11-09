#include "ll.h"
#include <utility>

namespace snakelinkedlist {

	// Default constructor
	LinkedList::LinkedList() {
		head_ = nullptr;
	};

	// Initilize from vector
	LinkedList::LinkedList(const std::vector<SnakeBodySegment>& values) {
		if (values.size() == 0) {
			LinkedList();
		}
		head_ = new ListNode(values[0]);
		ListNode *temp = head_;
		for (size_t i = 1; i < values.size(); i++) {
			ListNode *temp_next = new ListNode(values[i]);
			temp->next_ = temp_next;
			temp = temp->next_;
		}
		temp = nullptr;
	};

	// Big 5

	// Copy constructor
	snakelinkedlist::LinkedList::LinkedList(const snakelinkedlist::LinkedList& source) {
		if (source.head_) {
			head_ = source.head_;
		} else {
			head_ = nullptr;
		}
	};

	// Move constructor
	snakelinkedlist::LinkedList::LinkedList(LinkedList&& source) noexcept {
		head_ = source.head_;
		source.head_ = nullptr;
	}
	
	// Destructor
	snakelinkedlist::LinkedList::~LinkedList() {
		this->clear();
		delete head_;
	}

	// Copy assignment operator
	snakelinkedlist::LinkedList & snakelinkedlist::LinkedList::operator=(const LinkedList& source) {
		if (this == &source) {
			return *this;
		}
		delete head_;
		head_ = nullptr;
		if (source.head_) {
			head_ = new ListNode(*source.head_);
		}
		return *this;
	};

	// Move assignment operator
	snakelinkedlist::LinkedList & snakelinkedlist::LinkedList::operator=(LinkedList&& source) noexcept {
		if (this == &source) {
			return *this;
		}
		delete head_;
		head_ = source.head_;
		source.head_ = nullptr;
		return *this;
	}

	// Modifiers

	// Push value on front
	void snakelinkedlist::LinkedList::push_front(SnakeBodySegment data) {
		ListNode *new_node = new ListNode(data);
		new_node->next_ = head_;
		head_ = new_node;
	};

	// Push value on back
	void snakelinkedlist::LinkedList::push_back(SnakeBodySegment value) {
		if (!head_) {
			return;
		}
		ListNode *temp = head_;
		while (temp->next_ != nullptr) {
			temp = temp->next_;
		}
		ListNode *last_node = new ListNode(value);
		temp->next_ = last_node;
	};

	// remove front element
	void snakelinkedlist::LinkedList::pop_front() {
		if (!head_) {
			return;
		}
		ListNode *temp = head_;
		head_ = head_->next_;
		delete temp;
	};

	// remove back element
	void snakelinkedlist::LinkedList::pop_back() {
		if (!head_) {
			return;
		}
		ListNode *to_remove = head_;
		while (to_remove->next_->next_ != nullptr) {
			to_remove = to_remove->next_;
		}
		delete to_remove->next_;
		to_remove->next_ = nullptr;
	};
	
	// remove the Nth emement from the front
	void snakelinkedlist::LinkedList::RemoveNth(int n) {
		if (!head_) {
			return;
		}
		ListNode *to_remove = head_;
		if (n == 0) {
			pop_front();
		}
		else {
			for (int i = 0; i < n - 1; i++) {
				to_remove = to_remove->next_;
			}
			ListNode *temp = to_remove->next_;
			to_remove->next_ = to_remove->next_->next_;
			delete temp;
		}
	};

	// clear the contents
	void snakelinkedlist::LinkedList::clear() {
		if (!head_) {
			return;
		}
		while (head_->next_ != nullptr) {
			pop_back();
		}
		head_ = nullptr;
	};
											 
	// Accessors
	
	// Access the front value
	snakelinkedlist::SnakeBodySegment snakelinkedlist::LinkedList::front() const {
		if (head_) {
			return head_->data_;
		}
		return SnakeBodySegment();
	};

	// Access the back valueW
	snakelinkedlist::SnakeBodySegment snakelinkedlist::LinkedList::back() const {
		if (!head_) {
			return SnakeBodySegment();
		}
		ListNode *temp = head_;
		while (temp->next_ != nullptr) {
			temp = temp->next_;
		}
		return temp->data_;
	};

	// return number of elements
	int snakelinkedlist::LinkedList::size() const {
		if (!head_) {
			return 0;
		}
		int count = 1;
		ListNode *temp = head_;
		while (temp->next_ != nullptr) {
			count++;
			temp = temp->next_;
		}
		return count;
	};

	// return a vector of the values
	std::vector<snakelinkedlist::SnakeBodySegment> snakelinkedlist::LinkedList::GetVector() const {
		std::vector<SnakeBodySegment> *values = new std::vector<SnakeBodySegment>();
		ListNode *temp = head_;
		while (temp != nullptr) {
			values->push_back(temp->data_);
			temp = temp->next_;
		}
		return *values;
	};

	// check if empty
	bool LinkedList::empty() const {
		return !head_;
	};

	std::ostream& operator<<(std::ostream& os, const snakelinkedlist::LinkedList& list) {
		LinkedList::ListNode *temp = list.head_;
		while (temp->next_ != nullptr) {
			os << temp->data_ << ", ";
			temp = temp->next_;
		}
		os << temp->data_ << std::endl;
		return os;
	};

	bool snakelinkedlist::LinkedList::operator==(const LinkedList& rhs) const {
		if (size() != rhs.size()) {
			return false;
		}
		ListNode *temp_one = this->head_;
		ListNode *temp_two = rhs.head_;
		while (temp_one != nullptr && temp_two != nullptr) {
			if (temp_one->data_ != temp_two->data_) {
				return false;
			}
			temp_one = temp_one->next_;
			temp_two = temp_two->next_;
		}
		return true;
	};

	// This can effiently be implemented outside the class
	bool operator!=(const snakelinkedlist::LinkedList& lhs, const snakelinkedlist::LinkedList& rhs) {
		return !lhs.operator==(rhs);
	};


}; // namespace snakelinkedlist
