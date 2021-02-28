#ifndef CUSTOM_LIST_H
#define CUSTOM_LIST_H

#include "custom_node.h"

/*!
 * @brief custom_list object, linked list implementation that contains
 *        list nodes, pointing to others and containing values
 */
template <typename T>
class custom_list
{
    private:
        custom_node<T> dummy; // dummy node, stores nothing, points to start
        int n; // number of filled nodes in the list
    
    public:
        /*!
         * @brief default constructor, dummy points to itself, empty list
         * @pre none
         * @post create empty custom_list, with n=0 and dummy pointing to self
         */
        custom_list();

        /*!
         * @brief destructor, destroys all nodes in list
         * @pre none
         * @post deletes custom_list object, deleting all nodes inside
         */
        ~custom_list();

        /*!
         * @brief clear function, removes all nodes, sets n to 0
         * @pre none
         * @post removes all nodes in calling object, sets n to 0
         */
        void clear();

        /*!
         * @brief get_node function, returns pointer to node at ith index
         * @pre i must be a nonnegative number (0 or higher)
         * @param[in] i index to search for in linked list
         * @throw std::out_of_range if i < 0
         * @post gets the node at the ith index in the linked list
         * @returns a reference to the node at the ith index
         */
        custom_node<T>* get_node(const int i);

        /*!
         * @brief at function, returns the x value of ith node
         * @pre i must be a nonnegative number
         * @param[in] i index to search for in linked list
         * @throw std::out_of_range if i < 0
         * @post gets the x value at the ith node in linked list
         * @returns the x value from the ith node in list
         */
        T at(const int i) const;

        /*!
         * @brief set_node function, sets x value of ith node
         * @pre i must be a nonnegative number
         * @param[in] i index to search for in linked list
         * @param[in] x value to replace with at ith node
         * @throw std::out_of_range if i < 0
         * @post sets the x value of ith node in linked list
         */
        void set_node(const int i, const T x);

        /*!
         * @brief add_before function, adds node to list with x before w
         * @pre none
         * @param[in,out] w node to insert before, in list object
         * @param[in] x value to store in new node
         * @post adds a node with x before the node w
         * @returns newly created node with value x after creation
         */
        custom_node<T>* add_before(custom_node<T> *w, const T x);

        /*!
         * @brief add_node function, adds node at index i with value x
         * @pre i must be within the scope of the list
         * @param[in] i index to insert new node at
         * @param[in] x value to insert in new node
         * @throw std::out_of_range if i not in range of list
         * @post creates a new node at index i, containing value x
         */
        void add_node(const int i, const T x);

        /*!
         * @brief remove function, removes node w from list
         * @pre none
         * @param[in] w node to remove from list
         * @post removes the node w from the linked list
         */
        void remove(custom_node<T> *w);

        /*!
         * @brief remove function, removes node at index i
         * @pre i must be in range of linked list
         * @param[in] i index to remove node at
         * @throw std::out_of_range if i not in range of linked list
         * @post removes the node at the ith index in the linked list
         */
        void remove(const int i);
};

#include "custom_list.hpp"

#endif