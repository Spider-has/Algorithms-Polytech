#include <iostream>
#include <limits>

struct Matrix
{
private:
  size_t n_, m_;
  int **data;

public:
  Matrix(const int *d, size_t n, size_t m);

  Matrix(const Matrix &c);
  Matrix(Matrix &&c);

  ~Matrix();

  Matrix &operator=(const Matrix &r);
  Matrix &operator=(Matrix &&c);
  Matrix &operator+=(const Matrix &r);
  Matrix &operator-=(const Matrix &r);
  Matrix &operator*=(const Matrix &r);
  Matrix &operator*=(int k);
  size_t rows() const;
  size_t cols() const;
  int get(size_t row, size_t col) const;
  void set(size_t row, size_t col, int val);
};

void rm(int **mtx, size_t n)
{
  if (mtx)
  {
    for (size_t i = 0; i < n; i++)
    {
      delete[] mtx[i];
    }
    delete[] mtx;
  }
}

void copyRow(const int *from, int *to, size_t m)
{
  for (size_t j = 0; j < m; j++)
  {
    to[j] = from[j];
  }
}

void copyMtx(int *const *from, int **to, size_t n, size_t m)
{
  for (size_t i = 0; i < n; i++)
  {
    copyRow(from[i], to[i], m);
  }
}

void copyMtx(const int *from, int **to, size_t n, size_t m)
{
  for (size_t i = 0; i < n; i++)
  {
    copyRow(&from[i * m], to[i], m);
  }
}

void makeMtxRows(int **mtx, size_t n, size_t m)
{
  size_t i = 0;
  try
  {
    for (; i < n; i++)
    {
      mtx[i] = new int[m];
    }
  }
  catch (...)
  {
    rm(mtx, i);
    throw;
  }
}

int safe_sum(int a, int b)
{
  using lim_int = std::numeric_limits<int>;
  const int max_int = lim_int::max();
  const int min_int = lim_int::min();
  if (a > 0 && b > 0 && a > max_int - b)
  {
    throw std::overflow_error("sum up");
  }
  if (a < 0 && b < 0 && (b == min_int || a < min_int - b))
  {
    throw std::overflow_error("sum down");
  }
  return a + b;
}

int safe_subtract(int a, int b)
{
  using lim_int = std::numeric_limits<int>;
  const int max_int = lim_int::max();
  const int min_int = lim_int::min();
  if (b < 0 && a > max_int + b)
  {
    throw std::overflow_error("subtract up");
  }
  if (b > 0 && a < min_int + b)
  {
    throw std::overflow_error("subtract down");
  }
  return a - b;
}

int safe_multiple(int a, int b)
{
  using lim_int = std::numeric_limits<int>;
  const int max_int = lim_int::max();
  const int min_int = lim_int::min();
  if ((a > 0 && b > 0 && a > max_int / b) || (a < 0 && b < 0 && (a == min_int || b == min_int || a < max_int / b)))
  {
    throw std::overflow_error("multiple up");
  }
  if ((a > 0 && b < -1 && a > min_int / b) || (a < -1 && b > 0 && b > min_int / a))
  {
    throw std::overflow_error("multiple down");
  }
  return a * b;
}

Matrix::Matrix(const int *d, size_t n, size_t m):
    n_(n),
    m_(m),
    data(n > 0 && m > 0 && d ? new int *[n] : nullptr)
{
  if (d)
  {
    makeMtxRows(data, n, m);
    copyMtx(d, data, n, m);
  }
  else if (d == nullptr && (n > 0 || m > 0))
  {
    throw std::runtime_error("Error matrix inisialize");
  }
}

Matrix::Matrix(const Matrix &c):
    n_(c.n_),
    m_(c.m_),
    data(c.n_ > 0 && c.m_ > 0 ? new int *[c.n_] : nullptr)
{
  size_t i = 0;
  makeMtxRows(data, n_, m_);
  copyMtx(c.data, data, n_, m_);
}

Matrix::Matrix(Matrix &&c):
    n_(c.n_),
    m_(c.m_),
    data(c.data)
{
  c.data = nullptr;
  c.n_ = 0;
  c.m_ = 0;
}

Matrix::~Matrix()
{
  rm(data, n_);
}

Matrix &Matrix::operator=(const Matrix &r)
{
  if (this == &r)
  {
    return *this;
  }
  size_t i = 0;
  int **newData = new int *[r.n_];
  makeMtxRows(newData, r.n_, r.m_);
  copyMtx(r.data, newData, r.n_, r.m_);
  rm(data, n_);
  data = newData;
  n_ = r.n_;
  m_ = r.m_;
  return *this;
}

Matrix &Matrix::operator=(Matrix &&c)
{
  if (this != &c)
  {
    rm(data, n_);
    data = c.data;
    n_ = c.n_;
    m_ = c.m_;
    c.data = nullptr;
    c.n_ = 0;
    c.m_ = 0;
  }
  return *this;
}

Matrix &Matrix::operator+=(const Matrix &r)
{
  if (r.n_ != n_ || m_ != r.m_)
  {
    throw std::runtime_error("incorrect matrix sizes to sum");
  }
  for (size_t i = 0; i < r.n_; i++)
  {
    for (size_t j = 0; j < r.m_; j++)
    {
      data[i][j] = safe_sum(data[i][j], r.data[i][j]);
    }
  }
  return *this;
}

Matrix &Matrix::operator-=(const Matrix &r)
{
  if (r.n_ != n_ || m_ != r.m_)
  {
    throw std::runtime_error("incorrect matrix sizes to subtract");
  }
  for (size_t i = 0; i < r.n_; i++)
  {
    for (size_t j = 0; j < r.m_; j++)
    {
      data[i][j] = safe_subtract(data[i][j], r.data[i][j]);
    }
  }
  return *this;
}

Matrix &Matrix::operator*=(int k)
{
  for (size_t i = 0; i < n_; i++)
  {
    for (size_t j = 0; j < m_; j++)
    {
      data[i][j] = safe_multiple(data[i][j], k);
    }
  }
  return *this;
}

Matrix &Matrix::operator*=(const Matrix &r)
{
  if (m_ != r.n_)
  {
    throw std::runtime_error("incorrect matrix sizes to muptily");
  }
  int **newMtx = new int *[n_];
  size_t i = 0;
  try
  {
    for (; i < n_; i++)
    {
      newMtx[i] = new int[r.m_];
      for (size_t j = 0; j < r.m_; j++)
      {
        int result = 0;
        for (size_t k = 0; k < r.n_; k++)
        {
          result = safe_sum(result, safe_multiple(data[i][k], r.data[k][j]));
        }
        newMtx[i][j] = result;
      }
    }
    rm(data, n_);
    m_ = r.m_;
    data = newMtx;
    return *this;
  }
  catch (...)
  {
    rm(newMtx, i);
    throw;
  }
}

size_t Matrix::rows() const
{
  return n_;
}

size_t Matrix::cols() const
{
  return m_;
}

int Matrix::get(size_t row, size_t col) const
{
  return data[row][col];
}

void Matrix::set(size_t row, size_t col, int val)
{
  data[row][col] = val;
}

void printMtx(const Matrix &mtx)
{
  for (size_t i = 0; i < mtx.rows(); i++)
  {
    for (size_t j = 0; j < mtx.cols(); j++)
    {
      std::cout << mtx.get(i, j) << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

int main()
{
  try
  {
    int a[] = {1, 2, 3, 4};
    int b[] = {0, 1, 1, 0};
    Matrix m1(a, 2, 2);
    Matrix m2(b, 2, 2);

    Matrix sum = m1;
    sum += m2;
    printMtx(sum);

    Matrix diff = m1;
    diff -= m2;
    printMtx(diff);

    Matrix scaled = m1;
    scaled *= 10;
    printMtx(scaled);

    Matrix prod = m1;
    prod *= m2;
    printMtx(prod);

    int c[] = {1, 2};
    Matrix m3(c, 1, 2);
    printMtx(m3);

    int big[] = {std::numeric_limits<int>::max()};
    Matrix overflow(big, 1, 1);
    printMtx(overflow);
    // overflow *= 2;
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}