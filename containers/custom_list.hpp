template <typename T>
custom_list<T>::custom_list()
{
    dummy.next = &dummy;
    dummy.prev = &dummy;
    n = 0;
}

template <typename T>
custom_list<T>::~custom_list()
{
    clear();
}

template <typename T>
void custom_list<T>::clear()
{
    custom_node<T> *u = dummy.next;
    while(u != &dummy)
    {
        custom_node<T> *w = u->next;
        delete u;
        u = w;
    }
    n = 0;
}

template <typename T>
custom_node<T>* custom_list<T>::get_node(const int i)
{
    if(i < 0 || i >= n)
        throw std::out_of_range("i out of range in get_node() call");

    custom_node<T> *p;
    if(i < n / 2) // if i is closer to the front
    {
        p = dummy.next;
        for(int j = 0; j < i; j++)
            p = p->next;
    }
    else // if i is closer to the end
    {
        p = &dummy;
        for(int j = n; j > i; j--)
            p = p->prev;
    }
    return p;
}
template <typename T>
T custom_list<T>::at(const int i) const
{
    if(i < 0 || i >= n)
        throw std::out_of_range("i out of range in at() call");
    return get_node(i)->x;
}

template <typename T>
void custom_list<T>::set_node(const int i, const T x)
{
    custom_node<T> *u = get_node(i);
    u->x = x;
}

template <typename T>
custom_node<T>* custom_list<T>::add_before(custom_node<T> *w, const T x)
{
    custom_node<T> *u(x);
    u->prev = w->prev;
    u->next = w;
    u->next->prev = u;
    u->prev->next = u;
    n++;
    return u;
}

template <typename T>
void custom_list<T>::add_node(const int i, const T x)
{
    add_before(get_node(i), x);
}

template <typename T>
void custom_list<T>::remove(custom_node<T> *w)
{
    w->prev->next = w->next;
    w->next->prev = w->prev;
    delete w;
    n--;
}

template <typename T>
void custom_list<T>::remove(const int i)
{
    custom_node<T> *w = get_node(i);
    remove(w);
}