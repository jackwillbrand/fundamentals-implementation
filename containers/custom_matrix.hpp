template <typename T>
custom_matrix<T>::custom_matrix(const initializer_list<initializer_list<T>> &l)
{
    size_t init_list_size = l.begin()->size();
    for(auto &inner_list : l)
    {
        if(inner_list.size() != init_list_size)
            throw std::invalid_argument("init_list diff. sizes in matrix con");
    }

    m_data = new custom_vector<T>[l.size()];
    for(size_t i = 0; i < l.size(); i++)
        m_data[i] = custom_vector<T>(l.begin()->size());

    size_t curr_vect = 0;
    for(auto i = l.begin(); i != l.end(); i++)
    {
        size_t curr_i = 0;
        for(auto x = i->begin(); x != i->end(); x++)
        {
            m_data[curr_vect][curr_i] = *x;
            curr_i++;
        }
        curr_vect++;
    }
    r = l.size();
    c = l.begin()->size();
}

template <typename T>
custom_matrix<T>::~custom_matrix()
{
    delete[] m_data;
    m_data = nullptr;
}

template <typename T>
custom_matrix<T>::custom_matrix(const size_t rows, const size_t cols)
{
    if(rows <= 0 || cols <= 0)
        throw std::invalid_argument("matrix constr. given neg. size");

    m_data = new custom_vector<T>[rows];
    for(size_t i = 0; i < rows; i++)
        m_data[i] = custom_vector<T>(cols);
    r = rows;
    c = cols;

    for(size_t i = 0; i < rows; i++)
    {
        for(size_t j = 0; j < cols; j++)
            operator[](i).operator[](j) = 0;
    }
}

template <typename T>
custom_matrix<T>::custom_matrix(const custom_matrix<T> &a)
{
    m_data = new custom_vector<T>[a.rows()];
    for(size_t i = 0; i < a.rows(); i++)
        m_data[i] = custom_vector<T>(a.cols());

    r = a.rows();
    c = a.cols();

    for(size_t i = 0; i < r; i++)
    {
        for(size_t j = 0; j < c; j++)
            m_data[i][j] = a[i][j];
    }
}

template <typename T>
void swap(custom_matrix<T> &a, custom_matrix<T> &b)
{
    if(a.rows() != b.rows() || a.cols() != b.cols())
        throw std::invalid_argument("swap function a size DNE b size");
    for(size_t i = 0; i < a.rows(); i++)
    {
        for(size_t j = 0; j < a.cols(); j++)
            std::swap(a.m_data[i][j], b.m_data[i][j]);
    }
}

template <typename T>
custom_matrix<T>& custom_matrix<T>::operator=(custom_matrix<T> a)
{
    swap(*this, a);
    return *this;
}

template <typename T>
void custom_matrix<T>::resize(const size_t new_r, const size_t new_c)
{
    if(new_r < 0 || new_c < 0)
        throw std::invalid_argument("matrix resize given neg. size");

    delete[] m_data;

    m_data = new custom_vector<T>[new_r];
    for(size_t i = 0; i < new_r; i++)
        m_data[i] = custom_vector<T>(new_c);
    r = new_r;
    c = new_c;

    for(size_t i = 0; i < new_r; i++)
    {
        for(size_t j = 0; j < new_c; j++)
            operator[](i).operator[](j) = 0;
    }
}

template <typename T>
custom_vector<T> custom_matrix<T>::operator[](const size_t i) const
{
    if(i < 0)
        throw std::invalid_argument("[i] for matrix is negative");
    return m_data[i];
}

template <typename T>
custom_vector<T>& custom_matrix<T>::operator[](const size_t i)
{
    if(i < 0)
        throw std::invalid_argument("[i] for matrix is negative");
    return *&m_data[i];
}

template <typename T>
T custom_matrix<T>::operator()(const size_t i, const size_t j) const
{
    if(i < 0 || j < 0)
        throw std::invalid_argument("negative index for matrix(i, j) call");
    return m_data[i][j];
}

template <typename T>
T& custom_matrix<T>::operator()(const size_t i, const size_t j)
{
    if(i < 0 || j < 0)
        throw std::invalid_argument("negative index for matrix(i, j) call");
    return *&m_data[i][j];
}

template <typename T>
custom_matrix<T>& custom_matrix<T>::operator-()
{
    for(size_t i = 0; i < rows(); i++)
    {
        for(size_t j = 0; j < cols(); j++)
            operator[](i).operator[](j) *= -1;
    }
    return *this;
}

template <typename T>
ostream& operator<<(ostream &out, const custom_matrix<T> &src)
{
    for(size_t i = 0; i < src.rows(); i++)
    {
        for(size_t j = 0; j < src.cols(); j++)
        {
            if(j != src.cols() - 1)
                out << src[i][j] << " ";
            else
                out << src[i][j];
        }
        if(i != src.rows() - 1)
            out << std::endl;
    }
    return out;
}

template <typename T>
istream& operator>>(istream &in, custom_matrix<T> &src)
{
    for(size_t i = 0; i < src.rows(); i++)
    {
        for(size_t j = 0; j < src.cols(); j++)
            in >> src[i][j];
    }
    return in;
}

template <typename T>
custom_matrix<T> operator+(const custom_matrix<T> &a, const custom_matrix<T> &b)
{
    if(a.rows() != b.rows() || a.cols() != b.cols())
        throw std::invalid_argument("cant add matrices, different sizes");

    custom_matrix<T> added_matrix(a.rows(), a.cols());
    for(size_t i = 0; i < a.rows(); i++)
    {
        for(size_t j = 0; j < a.cols(); j++)
            added_matrix[i][j] = a[i][j] + b[i][j];
    }
    return added_matrix;
}

custom_matrix<float> operator+(const custom_matrix<int> &a, const custom_matrix<float> &b)
{
    if(a.rows() != b.rows() || a.cols() != b.cols())
        throw std::invalid_argument("cant add matrices, different sizes");

    custom_matrix<float> added_matrix(a.rows(), a.cols());
    for(size_t i = 0; i < a.rows(); i++)
    {
        for(size_t j = 0; j < a.cols(); j++)
            added_matrix[i][j] = a[i][j] + b[i][j];
    }
    return added_matrix;
}

template <typename T>
custom_matrix<T> operator-(const custom_matrix<T> &a, const custom_matrix<T> &b)
{
    if(a.rows() != b.rows() || a.cols() != b.cols())
        throw std::invalid_argument("cant minus matrices, different sizes");

    custom_matrix<T> added_matrix(a.rows(), a.cols());
    for(size_t i = 0; i < a.rows(); i++)
    {
        for(size_t j = 0; j < a.cols(); j++)
            added_matrix[i][j] = a[i][j] - b[i][j];
    }
    return added_matrix;
}

custom_matrix<float> operator-(const custom_matrix<int> &a, const custom_matrix<float> &b)
{
    if(a.rows() != b.rows() || a.cols() != b.cols())
        throw std::invalid_argument("cant minus matrices, different sizes");

    custom_matrix<float> added_matrix(a.rows(), a.cols());
    for(size_t i = 0; i < a.rows(); i++)
    {
        for(size_t j = 0; j < a.cols(); j++)
            added_matrix[i][j] = a[i][j] - b[i][j];
    }
    return added_matrix;
}

template <typename T>
custom_matrix<T> operator*(const custom_matrix<T> &a, const custom_matrix<T> &b)
{
    if(a.cols() != b.rows())
        throw std::invalid_argument("cant mult. matrices, incompat. sizes");
    
    custom_matrix<T> product(a.rows(), b.cols());
    for(size_t i = 0; i < product.rows(); i++)
    {
        for(size_t j = 0; j < product.cols(); j++)
        {
            T curr_sum = 0;
            for(size_t curr_i = 0; curr_i < a.cols(); curr_i++)
                curr_sum += (a[i][curr_i] * b[curr_i][j]);
            product[i][j] = curr_sum;
        }
    }
    return product;
}

template <typename T>
custom_matrix<T> operator*(const T a, const custom_matrix<T> &b)
{
    return (b * a);
}

template <typename T>
custom_matrix<T> operator*(const custom_matrix<T> &a, const T b)
{
    custom_matrix<T> scaled_matrix(a);
    for(size_t i = 0; i < a.rows(); i++)
    {
        for(size_t j = 0; j < a.cols(); j++)
            scaled_matrix[i][j] *= b;
    }
    return scaled_matrix;
}

template <typename T>
custom_matrix<T> operator*(const custom_vector<T> &a, const custom_matrix<T> &b)
{
    if(a.size() != b.rows())
        throw std::invalid_argument("cant mult. matrix/vect, incompat. sizes");
    
    custom_matrix<T> product(1, b.cols());
    for(size_t i = 0; i < product.cols(); i++)
    {
        T curr_sum = 0;
        for(size_t curr_r = 0; curr_r < a.size(); curr_r++)
            curr_sum += (a[curr_r] * b[curr_r][i]);
        product[0][i] = curr_sum;
    }
    return product;
}

template <typename T>
custom_vector<T> operator*(const custom_matrix<T> &a, const custom_vector<T> &b)
{
    if(a.cols() != b.size())
        throw std::invalid_argument("cant mult. vect/matrix, incompat. sizes");
    
    custom_vector<T> product(b.size());
    for(size_t i = 0; i < product.size(); i++)
    {
        T curr_sum = 0;
        for(size_t curr_r = 0; curr_r < a.cols(); curr_r++)
            curr_sum += (a[i][curr_r] * b[curr_r]);
        product[i] = curr_sum;
    }
    return product;
}

template <typename T>
custom_matrix<int> custom_matrix<T>::identity()
{
    custom_matrix<int> iden(rows(), cols());
    for(size_t i = 0; i < rows(); i++)
    {
        for(size_t j = 0; j < cols(); j++)
        {
            if(i == j)
                iden[i][j] = 1;
            else
                iden[i][j] = 0;
        }
    }
    return iden;
}

template <typename T>
custom_matrix<T> custom_matrix<T>::transpose()
{
    custom_matrix<T> this_copy(*this);
    for(size_t i = 0; i < rows(); i++)
    {
        for(size_t j = 0; j < rows(); j++)
            this_copy[j][i] = operator[](i).operator[](j);
    }
    return this_copy;
}

template <typename T>
custom_matrix<T> custom_matrix<T>::invert() const
{
    T row_sum, col_sum;

    T sum = 0;
    for(size_t i = 0; i < rows(); i++)
    {
        for(size_t j = 0; j < cols(); j++)
            sum += m_data[i][j];
        if(i == 0 || sum > row_sum)
            row_sum = sum;
    }
    sum = 0;
    for(size_t j = 0; j < cols(); j++)
    {
        for(size_t i = 0; i < rows(); i++)
            sum += m_data[i][j];
        if(j == 0 || sum > col_sum)
            col_sum = sum;
    }

    T t = 1 / (row_sum * col_sum);
    custom_matrix<T> this_transpose(*this);
    this_transpose.transpose();

    custom_matrix<T> b = t * this_transpose;
    bool is_accurate = false;
    while(!is_accurate)
    {
        custom_matrix<T> e = this_transpose.identity() - (b * *this);
        b = (this_transpose.identity() + e) * b;

        is_accurate = true;
        for(size_t i = 0; i < b.rows(); i++)
        {
            for(size_t j = 0; j < b.cols(); j++)
            {
                if(b[i][j] > 0.001)
                    is_accurate = false;
            }
        }
    }
    return b;
}

template <>
custom_matrix<float> custom_matrix<float>::invert() const
{
    float row_sum, col_sum;

    float sum = 0;
    for(size_t i = 0; i < rows(); i++)
    {
        for(size_t j = 0; j < cols(); j++)
            sum += m_data[i][j];
        if(i == 0 || sum > row_sum)
            row_sum = sum;
    }
    sum = 0;
    for(size_t j = 0; j < cols(); j++)
    {
        for(size_t i = 0; i < rows(); i++)
            sum += m_data[i][j];
        if(j == 0 || sum > col_sum)
            col_sum = sum;
    }

    float t = 1.0 / (row_sum * col_sum);
    custom_matrix<float> this_transpose(*this);
    this_transpose.transpose();

    custom_matrix<float> b = t * this_transpose;
    bool is_accurate = false;
    while(!is_accurate)
    {
        custom_matrix<float> e = (this_transpose.identity() - (b * *this));
        b = (this_transpose.identity() + e) * b;

        is_accurate = true;
        for(size_t i = 0; i < b.rows(); i++)
        {
            for(size_t j = 0; j < b.cols(); j++)
            {
                if(b[i][j] > 0.001)
                    is_accurate = false;
            }
        }
    }
    return b;
}