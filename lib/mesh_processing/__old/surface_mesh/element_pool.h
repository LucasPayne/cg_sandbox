#ifndef ELEMENT_POOL_H
#define ELEMENT_POOL_H

/*--------------------------------------------------------------------------------
    typedefs
--------------------------------------------------------------------------------*/
typedef uint32_t ElementIndex;
constexpr ElementIndex InvalidElementIndex = std::numeric_limits<ElementIndex>::max();



template <typename T>
struct ElementPoolIterator; // forward-declare iterator.

/*--------------------------------------------------------------------------------
    ElementPool
--------------------------------------------------------------------------------*/

template <typename T>
class ElementPool {
public:
    ElementPool(size_t capacity = 1);
    ElementIndex add();
    T *get(ElementIndex index);
    void remove(ElementIndex);

    size_t capacity() const { return pool.size(); }

    ElementPoolIterator<T> begin();
    ElementPoolIterator<T> end();

    void attach(ElementAttachment *attachment);
    void detach(ElementAttachment *attachment);

private:
    ElementIndex first_index() const { return m_first_index; }

    std::list<ElementAttachmentBase *> attachments;

    struct ElementEntry {
        ElementIndex next;
        T element;
    };
    std::vector<ElementEntry> pool;
    ElementIndex next_available_index;
    ElementIndex m_first_index;

    template <typename T2>
    friend class ElementAttachment<T2>;
};


/*--------------------------------------------------------------------------------
    ElementPoolIterator
--------------------------------------------------------------------------------*/
template <typename T>
struct ElementPoolIterator {
    T &operator*() {
        return *element_pool->get(current_index);
    }
    T *operator->() {
        return element_pool->get(current_index);
    }
    ElementPoolIterator operator++();
    bool operator==(ElementPoolIterator<T> other) {
        return current_index == other.current_index;
    }
    bool operator!=(ElementPoolIterator<T> other) {
        return !(*this == other);
    }

    ElementPool<T> *element_pool;
    ElementIndex current_index;
    ElementPoolIterator(ElementPool<T> *_element_pool, ElementIndex first_index) :
        element_pool{_element_pool}, current_index{first_index}
    {}
};

/*--------------------------------------------------------------------------------
    Template method implementations
--------------------------------------------------------------------------------*/
template <typename T>
ElementPool<T>::ElementPool(size_t capacity) :
    pool(capacity), next_available_index{0}
{
    assert(capacity > 0);

    // Initialize free list.
    for (unsigned int i = 0; i < capacity-1; i++) {
        pool[i].next = i+1;
    }
    pool[capacity-1].next = 0;

    // The pool is empty, so there is no first active element.
    m_first_index = InvalidElementIndex;
}

template <typename T>
ElementIndex ElementPool<T>::add()
{
    // Use the next available index to insert a new element.
    ElementIndex index = next_available_index;
    next_available_index = pool[next_available_index].next;
    pool[index].next = 0;

    if (next_available_index == 0) {
        // Grow the pool if needed.
        size_t prev_capacity = pool.size();
        size_t new_capacity = prev_capacity * 2;
        pool.resize(new_capacity, 0);
        for (auto attachment : attachments) {
            attachment.
        }

        next_available_index = prev_capacity;
        // Fix up the free list.
        for (int i = prev_capacity; i < new_capacity-1; i++) {
            pool[i].next = i+1;
        }
        pool[new_capacity-1] = 0;
    }
    return index;
}


template <typename T>
T *ElementPool<T>::get(ElementIndex index)
{
    return &pool[index].element;
}

template <typename T>
ElementPoolIterator<T> ElementPool<T>::begin()
{
    return ElementPoolIterator<T>(this, first_index());
}

template <typename T>
ElementPoolIterator<T> ElementPool<T>::end()
{
    return ElementPoolIterator<T>(this, InvalidElementIndex);
}

template <typename T>
void ElementPool<T>::attach(ElementAttachment *attachment)
{
    attachments.push_front(attachment);
}
template <typename T>
void ElementPool<T>::detach(ElementAttachment *attachment)
{
    attachments.remove(attachment);
}

#endif // ELEMENT_POOL_H
