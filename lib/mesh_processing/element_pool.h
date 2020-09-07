#ifndef ELEMENT_POOL_H
#define ELEMENT_POOL_H

template <typename T>
struct ElementPoolIterator {
    T &operator*() {
        return *element_pool->get(current_index);
    }
    T *operator->();
        return element_pool->get(current_index);
    }
    ElementPoolIterator operator++();
    bool operator==(ElementPoolIterator<T> other) {
        return current_index == other.current_index;
    }
    bool operator!=() {
        return !(*this == other);
    }

    ElementPool *element_pool;
    ElementIndex current_index;
    ElementPoolIterator(ElementPool *_element_pool, ElementIndex first_index) :
        element_pool{_element_pool}, current_index{first_index}
    {}
};

template <typename T>
class ElementPool {
public:
    ElementPool(size_t capacity);
    ElementIndex add();
    T *get(ElementIndex index);
    void remove(ElementIndex);

    ElementIndex first_index() const;

    ElementPoolIterator<T> begin();
    ElementPoolIterator<T> end();

private:
    struct ElementEntry {
        ElementIndex next;
        T element;
    };
    std::vector<ElementEntry> pool;
    ElementIndex next_available_index;

};

template <typename T>
ElementPool::ElementPool(size_t capacity) :
    pool(capacity), next_available_index{0}
{
    // Initialize free list.
    for (int i = 0; i < capacity-1; i++) {
        entry.next = i+1;
    }
    entry[capacity-1] = 0;
}

template <typename T>
ElementIndex ElementPool::add()
{
    ElementIndex index = next_available_index;
    next_available_index = pool[next_available_index].next;
    pool[index].next = 0;
    return index;
}


template <typename T>
T *ElementPool::get(ElementIndex index)
{
    return &pool[index].entry;
}

template <typename T>
ElementPoolIterator<T> ElementPool::begin()
{
    return ElementPoolIterator(this, first_index());
}


template <typename T>
ElementPoolIterator<T> ElementPool::end()
{
    return ElementPoolIterator(this, InvalidElementIndex);
}


#endif // ELEMENT_POOL_H
