#ifndef CUSTOM_VECTOR_H
#define CUSTOM_VECTOR_H

#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <cmath>
#include "custom_iterator.h"

using std::ostream;
using std::istream;

template <typename T>
class custom_vector;

/*! Overloaded output, output contents of custom_vector
 * @brief output operator to output contents of custom_vector to console
 * @pre type T must be capable of outputting to console
 * @param[in,out] out ostream object to perform outputting with
 * @param[in] src custom_vector to be outputted to the console
 * @post outputs the contents of src to the console
 * @returns the modified ostream object
 */
template <typename T>
ostream& operator<<(ostream &out, const custom_vector<T> &src);

/*! Overloaded insertion, fill contents of custom_vector with input
 * @brief insertion operator to fill contents of custom_vector with input
 * @pre cin must be called 'm_size' times to fill each vector element
 * @param[in,out] in istream object to perform inputting with
 * @param[in] src custom_vector to be inputted with data
 * @post inputs the contents of the console to src
 * @returns the modified istream object
 */
template <typename T>
istream& operator>>(istream &in, custom_vector<T> &src);

/*! swap function, swaps contents of a and b vector with each other
 * @brief swap function, swaps contents of a and b with each other
 * @pre a and b must be vectors of the same size
 * @param[in,out] a vector object to be switched with 'b'
 * @param[in,out] b vector object to be switched with 'a'
 * @throw std::invalid_argument if a.m_size != b.m_size
 * @post swaps the contents of custom_vector 'a' and 'b'
 */
template <typename T>
void swap(custom_vector<T> &a, custom_vector<T> &b);

/*! addition operator, for all element add by a's corresponding element
 * @brief addition, for all elements add by a's corresponding element
 * @pre a must be of same size as b, T must support addition
 * @param[in] a vector of same size as b to add with
 * @param[in] b vector of same size as a to add with
 * @throw std::invalid_argument if a is not same size as b
 * @post for each element in both vectors, a.m_data[i] + b.m_data[i]
 * @returns the new custom_vector after all addition is completed
 */
template <typename T>
custom_vector<T> operator+(const custom_vector<T> &a, const custom_vector<T> &b);

/*! subtract operator, for all element minus by a's corresponding element
 * @brief subtraction, for all elements minus by a's corresponding element
 * @pre a must be of same size as b, T must support subtraction
 * @param[in] a vector of same size as b to subtract with
 * @param[in] b vector of same size as a to subtract with
 * @throw std::invalid_argument if a is not same size as b
 * @post for each element in both vectors, a.m_data[i] - b.m_data[i]
 * @returns the new custom_vector after all subtraction is completed
 */
template <typename T>
custom_vector<T> operator-(const custom_vector<T> &a, const custom_vector<T> &b);

/*! multiplication operator, multiply all elements of lhs by rhs
 * @brief scalar mult., multiply all elements of lhs by rhs
 * @pre T must be of type that supports multiplication
 * @param[in] lhs a custom_vector object w/ elements to be multiplied
 * @param[in] rhs a scalar value of type T to multiply with
 * @post multiplies all elements of lhs by a scalar rhs
 * @returns new custom_vector after multiplication performed
 */
template <typename T>
custom_vector<T> operator*(const custom_vector<T> &lhs, const T &rhs);

/*! multiplication operator, multiply all elements of lhs by rhs
 * @brief scalar mult., multiply all elements of lhs by rhs
 * @pre T must be of type that supports multiplication
 * @param[in] lhs a custom_vector object w/ elements to be multiplied
 * @param[in] rhs a scalar value of type T to multiply with
 * @post multiplies all elements of lhs by a scalar rhs
 * @returns new custom_vector after multiplication performed
 */
template <typename T>
custom_vector<T> operator*(const T lhs, const custom_vector<T> &rhs);

/*! dot product operator, compute dot product of lhs and rhs
 * @brief dot product, computes dot product of lhs and rhs
 * @pre lhs must be of same size as rhs, T must support multiplication
 * @param[in] lhs a custom_vector to compute dot product with
 * @param[in] rhs a custom_vector to compute dot product with
 * @post adds product of all corresponding elements and returns num
 * @returns the dot product of lhs and rhs
 */
template <typename T>
T operator*(const custom_vector<T> &lhs, const custom_vector<T> &rhs);

/*! Numerical exponentiation, compute x^n via squaring method
 * @brief computes x^n via squaring numerical exponentiation method
 * @param[in] x the base of the exponential to evaluate
 * @param[in] n the exponent of the exponential to evaluate (integer)
 * @post computes x^n via squaring method of numerical methods
 * @returns the computed x^n value
 */
template <typename T>
T exp_by_squaring(const T x, const int n);

/*! Newton's method for nth root, calculates x^(1/n)
 * @brief uses newton's method to compute and return x^(1/n)
 * @pre n must not equal 0
 * @param[in] x the base of the nth root to evaluate
 * @param[in] n the denominator of the exponent (1/n) to raise x to
 * @throw std::invalid_argument if n == 0
 * @post computes the nth root of x to precision to 8 decimal places
 * @returns the computed nth root of x w/ precision to 8 decimal places
 */ 
template <typename T>
T sqrt_newton(const T x, const int n);

/*! custom_vector class
 * @brief custom vector implementation
 */
template <typename T>
class custom_vector
{

    private:
        T *m_data; //! dynamic array of size 'm_size' holding vector contents
        size_t m_size; //! size_t variable representing size of m_data

    public:
        /*! Default constructor, defaults to 0 vector with m_size 0
         * @brief Default constructor making zero vector with size of 0
         * @pre none
         * @post creates vector object with size 0
         */
        custom_vector(): m_data(nullptr), m_size(0) {}

        /*! Parameterized constructor, given initializer_list 'l'
         * @brief Parameterized constructor given initializer_list 'l'
         * @pre none
         * @param[in] l initializer list of T elements to copy to vector
         * @post creates a custom_vector obj with dynamic array of 'l' elements
         */
        custom_vector(const std::initializer_list<T> &l);

        /*! Parameterized constructor, given size of custom_vector 'space'
         * @brief Parameterized constructor, given size of vector 'space'
         * @pre space must be positive
         * @param[in] space size_t representing size of custom_vector storage
         * @throw std::invalid_argument if space < 0
         * @post creates a custom_vector object with storage size 'space'
         */
        explicit custom_vector(const size_t space);

        /*! Parameterized constructor, given arr of values of size n
         * @brief Parameterized constructor, given arr of values of size n
         * @pre none
         * @param[in] arr array of values to copy to custom_vector
         * @param[in] n value to initialize as size of custom_vector
         * @post creates a custom_vector object with values of arr and equal size
         */
        custom_vector(const T *arr, const size_t n);

        /*! Destructor, clears memory allocated to internal array
         * @brief Destructor, clears memory allocated to internal array
         * @pre none
         * @post clears and deletes pointer to internal dynamic array
         */
        ~custom_vector();

        /*! Copy constructor
         * @brief Copy constructor, creates identical custom_vector object to src
         * @pre template type T must support assignment
         * @param[in] src the object to be copied to calling object
         * @post creates custom_vector with copy of src's m_data and m_size values
         */
        custom_vector(const custom_vector<T> &src);

        /*! Assignment operator, returns custom_vector equal to given src
         * @brief Assignment operator, returns custom_vector object equal to src
         * @pre template type T must support assignment
         * @param[in] src copy of src vector to swap contents with to new obj
         * @post swaps contents of calling object and src
         * @returns the modified calling object, contains contents of src
         */
        custom_vector<T>& operator=(custom_vector<T> src);

        /*! Resize function, changes custom_vector size to new_size
         * @brief Resize function, changes custom_vector size to new_size
         * @pre new_size must be positive
         * @param[in] new_size size_t representing new dyn. array size
         * @throw std::invalid_argument if size_t < 0
         * @post modifies custom_vector so dyn. array is resized and m_size set
         */
        void resize(const size_t new_size);

        /*! Size function, returns the size of the custom_vector storage
         * @brief Size function, returns size of custom_vector storage
         * @pre none
         * @post returns the size of custom_vector
         * @returns the size of custom_vector
         */
        size_t size() const;

        /*! Subscript operator, returns val of m_data at index i
         * @brief Subscript operator, returns val of m_data at index i
         * @pre i must be in range 0 <= i < m_size
         * @param[in] i size_t representing index to pull from m_data
         * @throw std::out_of_range if i < 0 or i >= m_size
         * @post returns the value of m_data[i]
         * @returns the value of m_data[i]
         */
        T operator[](const size_t i) const;

        /*! Subscript operator, returns ref. to val of m_data at index i
         * @brief Subscript operator, returns ref. to val of m_data at index i
         * @pre i must be in range 0 <= i < m_size
         * @param[in] i size_t representing index to pull from m_data
         * @throw std::out_of_range if i < 0 or i >= m_size
         * @post returns a reference to value of m_data[i]
         * @returns the reference to value of m_data[i]
         */
        T& operator[](const size_t i);

        /*! apply function, returns new vector with func applied to all elements
         * @brief apply function, returns new vector with func on each element
         * @pre function must be of form func(T) with return type T
         * @param[in] func function of form func(T) with return type T
         * @post applies func() to all elements in m_data, return modified obj
         * @returns the modified vector with func() applied to all elements
         */
        custom_vector<T>& apply(T(*func)(T));

        /*! unary minus operator, makes all elements in custom_vector negative
         * @brief unary minus, for all elements in vector, change to inverse
         * @pre none
         * @post for each element in vector, change each to inverse
         * @returns a modified vector with each element inverted
         */
        custom_vector<T>& operator-();

        /*! P-norm evaluator, calculates the p-norm of vector
         * @brief calculates and returns p-norm of lhs of ^ operator
         * @pre exponentiation (squaring) must be supported for template type T
         * @param[in] p integer value to calculate norm with
         * @post calculates the p-norm of calling custom_vector
         * @returns the calculated p-norm value (of type T)
         */
        T operator^(const int p) const;

        /*! begin() function, returns iter at beginning of m_data
         * @brief begin() function, returns iter at beginning of m_data
         * @pre none
         * @post returns an iterator to beginning of m_data
         * @returns an iterator to beginning of m_data
         */
        custom_iterator<T> begin() const { return custom_iterator<T>(m_data); }
        
        /*! end() function, returns iter at end of m_data
         * @brief end() function, returns iter at end of m_data
         * @pre none
         * @post returns an iterator to end of m_data
         * @returns an iterator to end of m_data
         */
        custom_iterator<T> end() const 
            { return custom_iterator<T>(m_data + unsigned(m_size)); }

        /*! Overloaded insertion, fill contents of custom_vector with input
         * @brief insertion operator to fill contents of custom_vector with input
         * @pre cin must be called 'm_size' times to fill each vector element
         * @param[in,out] out ostream object to perform outputting with
         * @param[in] src custom_vector to be outputted to the console
         * @post outputs the contents of src to the console
         * @returns the modified ostream object
         */
         friend istream& operator>><T>(istream &in, custom_vector<T> &src);

        /*! swap function, swaps contents of a and b vector with each other
         * @brief swap function, swaps contents of a and b with each other
         * @pre a and b must be vectors of the same size
         * @param[in,out] a vector object to be switched with 'b'
         * @param[in,out] b vector object to be switched with 'a'
         * @throw std::invalid_argument if a.m_size != b.m_size
         * @post swaps the contents of custom_vector 'a' and 'b'
         */
        friend void swap<T>(custom_vector<T> &a, custom_vector<T> &b);
};

#include "custom_vector.hpp"

#endif