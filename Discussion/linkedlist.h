#include <cassert>
#include <stdexcept>

template <typename T>
class ListDoublyLinked
{
private:
    struct Node
    {
        T item;
        Node *next;
        Node *prev;
    };
    Node *head = nullptr;
    Node *tail = nullptr;
    unsigned int cur_size = 0;
    public:
    Node *GetNode(unsigned int pos)
    {
        assert(pos < cur_size);
        if (pos == cur_size - 1)
            return tail;
        Node *n = head;
        while (pos--)
            n = n->next;
        return n;
    }

    ListDoublyLinked() = default;
    ~ListDoublyLinked()
    {
        Node *n = head;
        while (n)
        {
            Node *d = n;
            n = n->next;
            delete d;
        }
    }
    unsigned int Size()
    {
        return cur_size;
    }
    const T &Get(const unsigned int pos)
    {
        if (pos >= cur_size)
            throw std::out_of_range("Position out of range!");
        Node *n = GetNode(pos);
        return n->item;
    }
    int Find(const T &item)
    {
        int i = 0;
        for (Node *n = head; n; n = n->next, i++)
            if (n->item == item)
                return i;
        return -1;
    }
    void Remove(const unsigned int pos)
    {
        if (pos >= cur_size)
            throw std::out_of_range("Position out of range!");
        Node *n = GetNode(pos);
        if (n->next)
            n->next->prev = n->prev;
        else
            tail = n->prev;
        if (n->prev)
            n->prev->next = n->next;
        else
            head = n->next;
        cur_size--;
    }
    void Insert(const T &item, const unsigned int pos)
    {
        if (pos > cur_size)
            throw std::out_of_range("Position out of range!");
        Node *n = new Node;
        n->item = item;
        if (pos == 0)
        {
            n->next = head;
            n->prev = nullptr;
            if (n->next)
                n->next->prev = n;
            else
                tail = n;
            head = n;
        }
        else
        {
            Node *prev = GetNode(pos - 1);
            n->next = prev->next;
            n->prev = prev;
            if (n->next)
                n->next->prev = n;
            else
                tail = n;
            prev->next = n;
        }
        cur_size++;
    }
};
