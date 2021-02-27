#ifndef CUSTOM_MATRIX_H
#define CUSTOM_MATRIX_H

#include "custom_vector.h"
using std::initializer_list;

/*! matrix class, matrix created via implementation of nested vector
 * @brief custom_matrix class, matrix via nested custom_vectors, supports arithmetic
 */
template <typename T>
class custom_matrix;

/*! extraction operator, outputs contents of src to console
 * @brief extraction operator, outputs contents of src to console
 * @pre none
 * @param[in,out] out ostream object to output with
 * @param[in] src matrix object to be outputted to console
 * @post outputs the contents of src to the console
 * @returns the modified ostream object
 */
template <typename T>
ostream& operator<<(ostream &out, const custom_matrix<T> &src);

/*! insertion operator, reads in contents to create custom_matrix with
 * @brief insertion op, reads contents in to create custom_matrix object
 * @pre none
 * @param[in,out] in istream object to input with
 * @param[in] src matrix object to be filled with inputted data
 * @post fills src with information inputted to console via stdin
 * @returns the modified istream object
 */
template <typename T>
istream& operator>>(istream &in, custom_matrix<T> &src);

/*! swap function, swaps contents of a and b
 * @brief swap function, swaps contents of a and b
 * @pre a and b must be matrices of same size
 * @param[in,out] a matrix object, lhs of the swap function
 * @param[in,out] b matrix object, rhs of the swap function
 * @throw std::invalid_argument if a and b are not the same size
 * @post swaps the matrix contents of a and b
 */
template <typename T>
void swap(custom_matrix<T> &a, custom_matrix<T> &b);

/*! matrix addition, adds matrices a and b and returns new matrix
 * @brief matrix addition, adds matrices a and b and returns new matrix
 * @pre type T must be capable of addition, a and b are same size
 * @param[in] a matrix object, lhs of addition operator
 * @param[in] b matrix object, rhs of addition operator
 * @post add the contents of a and b to a new matrix
 * @returns the new matrix after all addition completed
 */
template <typename T>
custom_matrix<T> operator+(const custom_matrix<T> &a, const custom_matrix<T> &b);

/*! matrix subtraction, minus matrices a and b and returns new matrix
 * @brief matrix subtraction, minus matrices a and b and returns new matrix
 * @pre type T must be capable of subtraction, a and b are same size
 * @param[in] a matrix object, lhs of subtraction operator
 * @param[in] b matrix object, rhs of subtraction operator
 * @post subtract the contents of a and b to a new matrix
 * @returns the new matrix after all subtraction completed
 */
template <typename T>
custom_matrix<T> operator-(const custom_matrix<T> &a, const custom_matrix<T> &b);

/*! matrix multiplication, multiples matrices a and b, returns result
 * @brief matrix multiplying, multiples matrices a and b, return result
 * @pre type T must be capable of addition and multiplication, the cols of
 *      the matrix 'a' must be equal to the rows of the matrix 'b'
 * @param[in] a matrix object, lhs of multiplication operator
 * @param[in] b matrix object, rhs of multiplication operator
 * @throw std::invalid_argument if a.cols() != b.rows()
 * @post multiplies matrices a and b
 * @returns the new matrix containing result of multiplying a and b
 */
template <typename T>
custom_matrix<T> operator*(const custom_matrix<T> &a, const custom_matrix<T> &b);

/*! scalar multiplication, multiplies matrix b by scalar a
 * @brief scalar multiplication, multiplies matrix b by scalar a
 * @pre type T must be capable of multiplication
 * @param[in] a scalar value of type T to be multiplied by elements of b
 * @param[in] b matrix, each value is multiplied by scalar a
 * @post multiples each value of matrix b by scalar a
 * @returns new matrix object after all multiplication is completed
 */
template <typename T>
custom_matrix<T> operator*(const T a, const custom_matrix<T> &b);

/*! scalar multiplication, multiplies matrix a by scalar b
 * @brief scalar multiplication, multiplies matrix a by scalar b
 * @pre type T must be capable of multiplication
 * @param[in] b scalar value of type T to be multiplied by elements of a
 * @param[in] a matrix, each value is multiplied by scalar b
 * @post multiples each value of matrix a by scalar b
 * @returns new matrix object after all multiplication is completed
 */
template <typename T>
custom_matrix<T> operator*(const custom_matrix<T> &a, const T b);

/*! vector * matrix multiplication, multiplies vector a by matrix b
 * @brief vector*matrix multiplication, multiplies vector a by matrix b
 * @pre type T must be capable of multiplication, the rows of matrix b must
 *      be equal to the elements in vector a
 * @param[in] a vector to be multiplied by matrix b
 * @param[in] b matrix to be multiplied by vector a
 * @throw std::invalid_argument if b.rows() != a.size()
 * @post multiplies the vector a by the matrix b
 * @returns a new matrix containing result of multiplication
 */
template <typename T>
custom_matrix<T> operator*(const custom_vector<T> &a, const custom_matrix<T> &b);

/*! matrix*vector multiplication, multiplies vector b by matrix a
 * @brief matrix*vector multiplication, multiplies vector b by matrix a
 * @pre type T must be capable of multiplication, the rows of matrix a must
 *      be equal to the elements in vector b
 * @param[in] b vector to be multiplied by matrix a
 * @param[in] a matrix to be multiplied by vector b
 * @throw std::invalid_argument if a.rows() != b.size()
 * @post multiplies the vector b by the matrix a
 * @returns a new vector containing result of multiplication
 */
template <typename T>
custom_vector<T> operator*(const custom_matrix<T> &a, const custom_vector<T> &b);

/*! matrix class, matrix created via implementation of nested vector
 * @brief custom_matrix class, matrix via nested custom_vectors, supports arithmetic
 */
template <typename T>
class custom_matrix
{
    private:
        custom_vector<T> *m_data; //! vector of vectors = matrix rep.
        size_t r; //! the number of rows in the matrix
        size_t c; //! the number of columns in the matrix

    public:
        /*!
         * @brief default constructor, create empty matrix of size 0x0
         * @pre none
         * @post creates empty matrix object of size 0 x 0
         */
        custom_matrix(): m_data(nullptr), r(0), c(0) {}

        /*! Parameterized constructor, given a 2D initializer list
         * @brief param. constructor, create matrix given 2d initializer list
         * @pre all inner initializer_lists must be same size
         * @param[in] l 2d initializer list containing elements of type T
         * @throw std::invalid_argument if inner init_lists are diff. sizes
         * @post creates an custom_matrix with all elements in l
         */
        custom_matrix(const initializer_list<initializer_list<T>> &l);

        /*! Destructor, deallocates all memory allocated to matrix
         * @brief Destructor, deallocates memory alloc. to matrix obj
         * @pre none
         * @post deallocates all memory allocated to calling object
         */
        ~custom_matrix();

        /*! Parameterized constructor, given an amount of rows and columns
         * @brief param. constructor, create matrix given size as params
         * @pre rows and cols must be a positive number
         * @param[in] rows the amount of rows in the matrix
         * @param[in] cols the amount of columns in the matrix
         * @throw std::invalid_argument if rows or cols is not positive
         * @post creates custom_matrix of size (rows x cols)
         */
        custom_matrix(const size_t r, const size_t c);

        /*! copy constructor, given an existing matrix 'a'
         * @brief copy constructor, given existing matrix 'a'
         * @pre none
         * @param[in] a matrix object to be copied to calling object
         * @post creates an custom_matrix object copied from 'a'
         */
        custom_matrix(const custom_matrix<T> &a);

        /*! assignment operator, returns calling object after copied from 'a'
         * @brief assignment operator, copies 'a' object and returns new obj
         * @pre none
         * @param[in] a matrix object to be copied to calling object
         * @post creates a new custom_matrix object copied from 'a'
         * @returns the new equivalent custom_matrix object
         */
        custom_matrix<T>& operator=(custom_matrix<T> a);

        /*! resize function, resizes matrix to be new_r x new_c,
         * @brief resize function to size (new_r x new_c)
         * @pre new_r and new_c must be positive
         * @param[in] new_r amount of rows for new matrix
         * @param[in] new_c amount of cols for new matrix
         * @throw std::out_of_range if new_r, new_c negative
         * @post resize the matrix, getting rid of previous elements
         */
        void resize(const size_t new_r, const size_t new_c);

        /*! subscript operator, returns vector in matrix at index i by copy
         * @brief subscript operator, returns vector in matrix at index i
         * @pre i must be a positive number (>0)
         * @param[in] i a positive size_t to access custom_matrix from
         * @throw std::invalid_argument if i is not positive
         * @post accesses the vector at index i
         * @returns copy of the accessed vector at index i
         */
        custom_vector<T> operator[](const size_t i) const;

        /*! subscript operator, returns reference to vector at index i
         * @brief subscript operator, return ref. to vector at index i
         * @pre i must be a positive number (>0)
         * @param[in] i a positive size_t to access custom_matrix from
         * @throw std::invalid_argument if i is not positive
         * @post accesses the vector at index i
         * @returns reference to vector at index i
         */
        custom_vector<T>& operator[](const size_t i);

        /*! evaluation operator, returns copy of element at matrix[i][j]
         * @brief eval. operator, returns copy of element at matrix[i][j]
         * @pre i and j must be positive numbers (>0)
         * @param[in] i the index of the row to access in matrix
         * @param[in] j the index of the col to access in matrix
         * @throw std::invalid_argument if i or j is not positive
         * @post access the T value at index matrix[i][j]
         * @returns a copy of the accessed T value at matrix[i][j]
         */
        T operator()(const size_t i, const size_t j) const;

        /*! evaluation operator, returns ref. of element at matrix[i][j]
         * @brief eval. operator, returns ref. of element at matrix[i][j]
         * @pre i and j must be positive numbers (>0)
         * @param[in] i the index of the row to access in matrix
         * @param[in] j the index of the col to access in matrix
         * @throw std::invalid_argument if i or j is not positive
         * @post access the T value at index matrix[i][j]
         * @returns a reference to the accessed T value at matrix[i][j]
         */
        T& operator()(const size_t i, const size_t j);

        /*! row function, returns the amount of rows in the matrix
         * @brief row function, returns the amount of rows in the matrix
         * @pre none
         * @post returns the amount of the rows in the matrix
         * @returns the amount of rows in the matrix
         */
        size_t rows() const { return r; }

        /*! col function, returns the amount of columns in the matrix
         * @brief col function, returns the amount of columns in the matrix
         * @pre none
         * @post returns the amount of the columns in the matrix
         * @returns the amount of columns in the matrix
         */
        size_t cols() const { return c; }

        /*! unary minus, returns new matrix, all the elements are negative
         * @brief unary minus, returns new matrix with elements inverted
         * @pre type T must be capable of being made negative
         * @post returns a new matrix, where all elements are negative
         * @returns the new matrix, with same elements as call obj., inverted
         */
        custom_matrix<T>& operator-();

        /*! identity helper function, create identity matrix same size as call
         * @brief identity function, creates identity matrix same size as call
         * @pre none
         * @post creates identity matrix with same size as calling object
         * @returns identity matrix with same size as calling object with ints
         */
        custom_matrix<int> identity();

        /*! transpose helper function, transposes the calling matrix
         * @brief transpose helper function, transposes the calling matrix
         * @pre none
         * @post transposes the calling matrix
         * @returns a copy of this matrix transposed
         */
        custom_matrix<T> transpose();

        /*! invert function, performs matrix inversion based on newton-schulz
         * @brief invert function, inverts matrix based on newton-schulz method
         * @pre none
         * @post inverts the calling object using the newton-schulz method
         * @returns a new matrix equal to inverse of calling object
         */
        custom_matrix<T> invert() const;

        /*! swap function, swaps contents of a and b
         * @brief swap function, swaps contents of a and b
         * @pre a and b must be matrices of same size
         * @param[in,out] a matrix object, lhs of the swap function
         * @param[in,out] b matrix object, rhs of the swap function
         * @throw std::invalid_argument if a and b are not the same size
         * @post swaps the matrix contents of a and b
         */
        friend void swap<T>(custom_matrix<T> &a, custom_matrix<T> &b);

        /*! extraction operator, outputs contents of src to console
         * @brief extraction operator, outputs contents of src to console
         * @pre none
         * @param[in,out] out ostream object to output with
         * @param[in] src matrix object to be outputted to console
         * @post outputs the contents of src to the console
         * @returns the modified ostream object
         */
        friend ostream& operator<<<T>(ostream &out, const custom_matrix<T> &src);

        /*! insertion operator, reads in contents to create custom_matrix with
         * @brief insertion op, reads contents in to create custom_matrix object
         * @pre none
         * @param[in,out] in istream object to input with
         * @param[in] src matrix object to be filled with inputted data
         * @post fills src with information inputted to console via stdin
         * @returns the modified istream object
         */
        friend istream& operator>><T>(istream &in, custom_matrix<T> &src);
};

#include "custom_matrix.hpp"

#endif