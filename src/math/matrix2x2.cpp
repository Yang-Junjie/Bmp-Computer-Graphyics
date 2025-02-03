#include "matrix2x2.hpp"

Matrix2x2::Matrix2x2(const Matrix2x2 &mat)
{
    this->column1 = mat.column1;
    this->column2 = mat.column2;
}

Matrix2x2::Matrix2x2(const oeVec2 &col1, const oeVec2 &col2) : column1(col1), column2(col2)
{
}

Matrix2x2::Matrix2x2(const real &row1_x, const real &row1_y,
                     const real &row2_x, const real &row2_y)
{
    column1 = {row1_x, row2_x};
    column2 = {row1_y, row2_y};
}

Matrix2x2 &Matrix2x2::operator=(const Matrix2x2 &rhs)
{
    if (this == &rhs)
        return *this;
    column1 = rhs.column1;
    column2 = rhs.column2;
    return *this;
}

Matrix2x2 &Matrix2x2::operator+=(const Matrix2x2 &rhs)
{
    column1 += rhs.column1;
    column2 += rhs.column2;
    return *this;
}

Matrix2x2 &Matrix2x2::operator-=(const Matrix2x2 &rhs)
{
    column1 -= rhs.column1;
    column2 -= rhs.column2;
    return *this;
}

Matrix2x2 &Matrix2x2::operator*=(const real &factor)
{
    column1 *= factor;
    column2 *= factor;
    return *this;
}

Matrix2x2 &Matrix2x2::operator/=(const real &factor)
{
    column1 /= factor;
    column2 /= factor;
    return *this;
}

Matrix2x2 Matrix2x2::operator+(const Matrix2x2 &rhs) const
{
    return Matrix2x2(column1 + rhs.column1, column2 + rhs.column2);
}

Matrix2x2 Matrix2x2::operator-(const Matrix2x2 &rhs) const
{
    return Matrix2x2(column1 - rhs.column1, column2 - rhs.column2);
}

oeVec2 Matrix2x2::row1() const
{
    return oeVec2(column1.x, column2.x);
}

oeVec2 Matrix2x2::row2() const
{
    return oeVec2(column1.y, column2.y);
}

real &Matrix2x2::e11()
{
    return column1.x;
}

real &Matrix2x2::e21()
{
    return column1.y;
}
real &Matrix2x2::e12()
{
    return column2.x;
}

real &Matrix2x2::e22()
{
    return column2.y;
}

real Matrix2x2::determinant() const
{
    return determinant(*this);
}

Matrix2x2 &Matrix2x2::transpose()
{
    std::swap(column1.y, column2.x);
    return *this;
}

Matrix2x2 &Matrix2x2::invert()
{
    invert(*this);
    return *this;
}

Matrix2x2 &Matrix2x2::multiply(const Matrix2x2 &rhs)
{
    *this = multiply(*this, rhs);
    return *this;
}

oeVec2 Matrix2x2::multiply(const oeVec2 &rhs) const
{
    return multiply(*this, rhs);
}

Matrix2x2 &Matrix2x2::clear()
{
    column1.clear();
    column2.clear();
    return *this;
}

Matrix2x2 &Matrix2x2::set(const real &col1_x, const real &col1_y, const real &col2_x, const real &col2_y)
{
    column1.set(col1_x, col1_y);
    column2.set(col2_x, col2_y);
    return *this;
}

Matrix2x2 &Matrix2x2::set(const oeVec2 &col1, const oeVec2 &col2)
{
    column1 = col1;
    column2 = col2;
    return *this;
}

Matrix2x2 &Matrix2x2::set(const Matrix2x2 &other)
{
    column1 = other.column1;
    column2 = other.column2;
    return *this;
}
Matrix2x2 Matrix2x2::skewSymmetricMatrix(const oeVec2 &r)
{
    return Matrix2x2(0, -r.y, r.x, 0);
}

Matrix2x2 Matrix2x2::identityMatrix()
{
    return Matrix2x2(1, 0, 0, 1);
}

oeVec2 Matrix2x2::multiply(const Matrix2x2 &lhs, const oeVec2 &rhs)
{
    return oeVec2(lhs.column1.x * rhs.x + lhs.column2.x * rhs.y, lhs.column1.y * rhs.x + lhs.column2.y * rhs.y);
}

Matrix2x2 Matrix2x2::multiply(const Matrix2x2 &lhs, const Matrix2x2 &rhs)
{
    return Matrix2x2(lhs.column1.x * rhs.column1.x + lhs.column2.x * rhs.column1.y,
                     lhs.column1.y * rhs.column1.x + lhs.column2.y * rhs.column1.y,
                     lhs.column1.x * rhs.column2.x + lhs.column2.x * rhs.column2.y,
                     lhs.column1.y * rhs.column2.x + lhs.column2.y * rhs.column2.y);
}

real Matrix2x2::determinant(const Matrix2x2 &mat)
{
    return mat.column1.x * mat.column2.y - mat.column2.x * mat.column1.y;
}

bool Matrix2x2::invert(Matrix2x2 &mat)
{
    const real det = mat.determinant();

    if (det < 0.00000001)
        return false;

    std::swap(mat.column1.x, mat.column2.y);
    mat.column1.y *= -1;
    mat.column2.x *= -1;
    mat /= det;
    return true;
}