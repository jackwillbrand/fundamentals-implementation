#ifndef CUSTOM_NODE_H
#define CUSTOM_NODE_H

/*!
 * @brief custom doubly-linked list node
 */
template <typename T>
class custom_node
{
    public:
        T x; //! value that the custom_node contains
        custom_node<T> *prev; //! pointer to previous node in sequence
        custom_node<T> *next; //! pointer to next node in sequence

        custom_node() { next = nullptr; prev = nullptr; }

        /*! Paramterized constructor, store x0 in new node
         * @brief parameterized constructor, given the value x0
         * @pre none
         * @param[in] x0 value to input into the new node
         * @post creates a custom_node object with x0, pointing to nullptr
         */
        custom_node(const T x0) { x = x0; next = nullptr; prev = nullptr; }
};

#endif