#ifndef CUSTOM_ITERATOR_H
#define CUSTOM_ITERATOR_H

/*! custom_iterator class
 * @brief My Iterator class, custom iterator
 *        to allow for range based for loop usage
 */
template <typename T>
class custom_iterator
{
    public:
        /*! Paramterized constructor, give the pointer to type T
         * @brief parameterized constructor, given the pointer to type T
         * @pre none
         * @param[in] ptr pointer to object of type T to be used for iterator
         * @post creates a custom_iterator object with this.ptr pointing to ptr
         */
        explicit custom_iterator(T *ptr): ptr(ptr) {}

        /*! Increment operator, increments the pointer member variable
         * @brief Increment operator, increments the ptr member variable
         * @pre none
         * @post increments the ptr member variable and returns new calling obj
         * @returns modified calling obj. after ptr is incremented
         */
        custom_iterator<T> operator++() {++ptr; return *this;}

        /*! Not comparison operator, returns true if pointers are not equal
         * @brief Not comp. operator, returns true if pointers are not equal
         * @pre none
         * @param[in] r second custom_iterator object to compare to calling obj
         * @post compares this.ptr to r.ptr and returns result
         * @returns true if ptr != r.ptr, false otherwise
         */
        bool operator!=(const custom_iterator<T>&r) const {return ptr != r.ptr;}

        /*! Dereference operator, returns the dereferenced pointer
         * @brief Deference operator, returns the dereferenced ptr member var.
         * @pre none
         * @post returns the deferenced ptr member var.
         * @returns the deferenced ptr member variable
         */
        const T& operator*() const {return *ptr;}
    
    private:
        T *ptr; //! pointer object to do iteration with
};

#endif