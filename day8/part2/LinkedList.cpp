#include <string>
#include <iostream>
#include <set>

template <class T>
struct LinkedListNode
{
    T data;
    LinkedListNode<T> *next;
    LinkedListNode<T> *previous;
};

template <class T>
class LinkedList
{
public:
    LinkedListNode<T> *head = NULL;
    LinkedListNode<T> *tail = NULL;
    class Iterator;
    void remove_at(int position)
    {
        LinkedListNode<T> *previous_node = head->previous;
        LinkedListNode<T> *current_node = head;

        for (size_t i = 0; i < position; i++)
        {
            previous_node = current_node;
            current_node = current_node->next;
            if (current_node == nullptr)
                return;
        }

        previous_node->next = current_node->next;

        if (current_node->next == nullptr)
            current_node->next->previous = previous_node;
        else
            this->tail = current_node;
        --_size;
    }

    void remove(T argv)
    {
        LinkedListNode<T> *previous_node = head->previous;
        LinkedListNode<T> *current_node = head;
        while (current_node != nullptr)
        {
            if (current_node->data == argv)
            {
                previous_node->next = current_node->next;

                if (current_node->next == nullptr)
                    current_node->next->previous = previous_node;
                else
                    this->tail = current_node;

                --_size;
            }
            current_node = current_node->next;
            previous_node = current_node;
        }
    }

    void insert(T argv)
    {
        LinkedListNode<T> *new_node = new LinkedListNode<T>;
        new_node->data = argv;
        new_node->next = NULL;

        if (this->head == nullptr)
        {
            this->head = new_node;
            this->tail = new_node;
            return;
        }

        else
        {
            LinkedListNode<T> *current_node = this->head;
            while (current_node->next != nullptr)
                current_node = current_node->next;

            current_node->next = new_node;
            new_node->previous = current_node;
            this->tail = new_node;
        }
        ++_size;
    }

    bool has(T argv)
    {
        return this->get_index(argv) != -1;
    }

    int get_index(T argv)
    {
        LinkedListNode<T> *current_node = this->head;
        int i = 0;
        int NOT_FOUND = -1;

        if (current_node == nullptr)
            return NOT_FOUND;

        while (current_node != nullptr && current_node->data != argv)
        {
            if (current_node->next == nullptr)
                return NOT_FOUND;
            current_node = current_node->next;
            ++i;
        }

        return i;
    }

    void for_each(bool (*iteratee)(LinkedListNode<T> *argv))
    {
        LinkedListNode<T> *current_node = head;

        while (current_node != nullptr)
        {
            if (iteratee(current_node) == true)
                break;
            current_node = current_node->next;
        }
    }

    void for_each(void (*iteratee)(LinkedListNode<T> *argv))
    {
        LinkedListNode<T> *current_node = head;

        while (current_node != nullptr)
        {
            iteratee(current_node);
            current_node = current_node->next;
        }
    }

    void print()
    {
        this->for_each(LinkedList::log_str);
    }

    int get_size()
    {
        return this->_size;
    }

    LinkedList<T>::Iterator begin()
    {
        return Iterator(head);
    }

    LinkedList<T>::Iterator end()
    {
        return Iterator(tail);
    }

    int size()
    {
        return _size;
    }

    LinkedListNode<T> *find(bool (*predicate)(LinkedListNode<T> *argv))
    {
        LinkedListNode<T> *current_node = this->head;
        while (current_node != nullptr)
        {
            if (predicate(current_node))
                return current_node;
            current_node = current_node->next;
        }
        return nullptr;
    }

    void remove_while(bool (*predicate)(LinkedListNode<T> *argv))
    {
        LinkedListNode<T> *current_node = this->head;

        while (current_node != nullptr)
        {
            if (predicate(current_node))
                this->remove(current_node->data);
            current_node = current_node->next;
        }
    }
    class Iterator
    {
    private:
        LinkedListNode<T> *_node;

    public:
        Iterator(LinkedListNode<T> *node)
        {
            _node = node;
        }

        Iterator &operator=(LinkedListNode<T> *node)
        {
            this->_node = node;
            return *this;
        }

        Iterator &operator++()
        {
            if (_node)
            {
                _node = _node->next;
            }
            return *this;
        }

        bool operator!=(const Iterator &iterator)
        {
            return !!_node && _node != iterator._node;
        }

        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }

        T get_data()
        {   
            return this->_node->data;
        }
    };

private:
    int _size = 0;
    static void log_str(LinkedListNode<T> *argv)
    {
        std::cout << argv->data << std::endl;
    }
};