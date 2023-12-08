#include <iostream>

/******************************************************
 *
 * List Abstract Data Type
 *
 *****************************************************/
class List {
public:
    virtual void Append(int val) = 0;

    virtual bool Insert(int pos, int val) = 0;

    virtual bool Remove(int pos) = 0;

    virtual bool Get(int pos, int &val) const = 0;

    virtual int GetSize() const = 0;

    virtual ~List() {}
};

/******************************************************
 *
 * ArrayList
 *
 *****************************************************/
class ArrayList : public List {
    static const int INIT_SIZE = 16;
public:
    ArrayList() : size_(INIT_SIZE), last_idx_(-1) {
        list_ = new int[size_];
    }

    virtual ~ArrayList() { delete[] list_; }

    void Append(int val) override;

    bool Insert(int pos, int val) override;

    bool Remove(int pos) override;

    bool Get(int pos, int &val) const override;

    int GetSize() const override;

private:
    void Resize(int new_size);

    int size_;
    int last_idx_;
    int *list_;
};

void ArrayList::Append(int val) {
    last_idx_++;
    if (last_idx_ > size_ - 1)
        Resize(size_ * 2);
    list_[last_idx_] = val;
}

bool ArrayList::Insert(int pos, int val) {
    if (pos < 0 || pos > last_idx_ + 1)
        return false;
    last_idx_++;
    if (last_idx_ > size_ - 1)
        Resize(size_ * 2);
    for (int i = last_idx_; i > pos; i--) {
        list_[i] = list_[i - 1];
    }
    list_[pos] = val;
    return true;
}

bool ArrayList::Remove(int pos) {
    if (pos < 0 || pos > last_idx_)
        return false;
    last_idx_--;
    if (last_idx_ < size_ / 4)
        Resize(size_ / 2);
    for (int i = pos; i < last_idx_ + 1; i++) {
        list_[i] = list_[i + 1];
    }
    return true;
}

bool ArrayList::Get(int pos, int &val) const {
    if (pos < 0 || pos > last_idx_)
        return false;
    val = list_[pos];
    return true;
}

int ArrayList::GetSize() const {
    return (last_idx_ + 1);
}

void ArrayList::Resize(int new_size) {
    int *new_list = new int[new_size];
    int copy_size = (new_size > size_) ? size_ : new_size;
    for (int i = 0; i < copy_size; i++) {
        new_list[i] = list_[i];
    }
    delete[] list_;
    list_ = new_list;
    size_ = new_size;
}


/******************************************************
 *
 * LinkedList
 *
 *****************************************************/
class Node {
public:
    Node(int val) : val_(val), next_(nullptr) {}

    int GetVal() const { return val_; }

    Node *GetNext() const { return next_; }

    void SetNext(Node *n) { next_ = n; }

private:
    int val_;
    Node *next_;
};

class LinkedList : public List {
public:
    LinkedList() : size_(0), head_(nullptr), tail_(nullptr) {}

    virtual ~LinkedList();

    bool Get(int pos, int &val) const override;

    void Append(int val) override;

    bool Insert(int pos, int val) override;

    bool Remove(int pos) override;

    int GetSize() const override;

private:
    int size_;
    Node *head_, *tail_;
};

LinkedList::~LinkedList() {
    Node *curnode = head_;
    while (curnode) {
        Node *tmpnode = curnode;
        curnode = curnode->GetNext();
        delete tmpnode;
    }
}

void LinkedList::Append(int val) {
    Node *new_node = new Node(val);
    if (!head_) {
        head_ = tail_ = new_node;
    } else {
        tail_->SetNext(new_node);
        tail_ = new_node;
    }
    size_++;
}

bool LinkedList::Insert(int pos, int val) {
    if (pos < 0 || pos > size_)
        return false;
    if (size_ == 0) {
        Append(val);
        return true;
    }
    Node *new_node = new Node(val);
    Node *curnode = head_;
    for (int i = 0; i < pos; i++) {
        curnode = curnode->GetNext();
    }
    new_node->SetNext(curnode->GetNext());
    curnode->SetNext(new_node);
    size_++;
    return true;
}

bool LinkedList::Remove(int pos) {
    if (pos < 0 || pos > size_ - 1)
        return false;
    Node *prevnode = nullptr;
    Node *curnode = head_;
    for (int i = 0; i < pos; i++) {
        prevnode = curnode;
        curnode = curnode->GetNext();
    }
    if (prevnode)
        prevnode->SetNext(curnode->GetNext());
    else
        head_->SetNext(curnode->GetNext());
    delete curnode;
    size_--;
    return true;
}

bool LinkedList::Get(int pos, int &val) const {
    if (pos < 0 || pos > size_ - 1)
        return false;
    Node *curnode = head_;
    for (int i = 0; i < pos; i++) {
        curnode = curnode->GetNext();
    }
    val = curnode->GetVal();
    return true;
}

int LinkedList::GetSize() const {
    return size_;
}


/******************************************************
 *
 * Main Test
 *
 *****************************************************/

void PrintList(const List *list) {
    int val = 0;
    for (int i = 0; i < list->GetSize(); i++) {
        if (list->Get(i, val))
            std::cout << val << " ";
        else
            std::cout << "F ";
    }
    std::cout << std::endl;
}

int main() {
    //List *list = new ArrayList();
    List *list = new LinkedList();
    for (int i = 0; i < 50; i++) {
        list->Append(i);
    }
    PrintList(list);
    for (int i = 0; i < 20; i++) {
        list->Remove(10);
    }
    PrintList(list);
    for (int i = 0; i < 20; i++) {
        list->Insert(10, -1);
    }
    PrintList(list);
}

