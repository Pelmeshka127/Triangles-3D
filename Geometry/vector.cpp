#include "vector.hpp"

//-------------------------------------------------------------------------------//

double Vector::X() const
{
    return x_;
}

//-------------------------------------------------------------------------------//

double Vector::Y() const
{
    return y_;
}

//-------------------------------------------------------------------------------//

double Vector::Z() const
{
    return z_;
}

//-------------------------------------------------------------------------------//

bool Vector::IsNullVector(const Vector &v1) const
{
    return (double_numbers::IsEqual(v1.x_, 0) &&
            double_numbers::IsEqual(v1.y_, 0) &&
            double_numbers::IsEqual(v1.z_, 0));
}

//-------------------------------------------------------------------------------//

Point Vector::GetVectorCoordinates(const Vector &v1) const
{
    Point p(v1.x_, v1.y_, v1.z_);

    return p;
}

//-------------------------------------------------------------------------------//

Vector Vector::operator=(const Vector &v)
{
    return Vector(v.x_, v.y_, v.z_);
}

//-------------------------------------------------------------------------------//

Vector& Vector::operator+=(const Vector &v)
{
    x_ += v.x_;
    y_ += v.y_;
    z_ += v.z_;

    return *this;
}

//-------------------------------------------------------------------------------//

Vector Vector::operator+(const Vector &v) const
{
    return Vector(x_ + v.x_, y_ + v.y_, z_ + v.z_);
}

//-------------------------------------------------------------------------------//

Vector& Vector::operator-=(const Vector &v)
{
    x_ -= v.x_;
    y_ -= v.y_;
    z_ -= v.z_;

    return *this;
}

//-------------------------------------------------------------------------------//

Vector Vector::operator-(const Vector &v) const
{
    return Vector(x_ - v.x_, y_ - v.y_, z_ - v.z_);
}

//-------------------------------------------------------------------------------//

Vector& Vector::operator*=(const float &number)
{
    x_ *= number;
    y_ *= number;
    z_ *= number;

    return *this;
}

//-------------------------------------------------------------------------------//

Vector Vector::operator*(const float &number) const
{
    return Vector(x_ * number, y_ * number, z_ * number);
}

//-------------------------------------------------------------------------------//

double Vector::operator*(const Point& point) const
{
    return (x_ * point.X() + y_ * point.Y() + z_ * point.Z());
}

//-------------------------------------------------------------------------------//

bool Vector::operator==(const Vector &v) const
{
    return (double_numbers::IsEqual(x_, v.x_) &&
            double_numbers::IsEqual(y_, v.y_) &&
            double_numbers::IsEqual(z_, v.z_));
}

//-------------------------------------------------------------------------------//

Point Vector::operator+(const Point& p) const
{
    return Point(x_ + p.X(), y_ + p.Y(), z_ + p.Z());
}

//-------------------------------------------------------------------------------//

double Vector::Length() const
{
    return (std::sqrt(x_ * x_ + y_ * y_ + z_ * z_));
}

//-------------------------------------------------------------------------------//

// double Vector::DotProduct(const Vector& v, const Point& p) const
// {
//     return (v.x_ * p.X() + v.y_ * p.Y() + v.z_ * p.Z());
// }

//-------------------------------------------------------------------------------//

double Vector::DotProduct(const Vector &v1, const Vector &v2) const
{
    return (v1.x_ * v2.x_ + v1.y_ * v2.y_ + v1.z_ * v2.z_);
}

//-------------------------------------------------------------------------------//

double Vector::CrossProductValue(const Vector &v1, const Vector &v2) const
{
    double x_new = v1.y_ * v2.z_ - v1.z_ * v2.y_;
    double y_new = v1.z_ * v2.x_ - v1.x_ * v2.z_;
    double z_new = v1.x_ * v2.y_ - v1.y_ * v2.x_;

    double result = x_new + y_new + z_new;

    return result;
}

//-------------------------------------------------------------------------------//

Vector Vector::CrossProductVector(const Vector &v1, const Vector &v2) const
{
    double x_new = v1.y_ * v2.z_ - v1.z_ * v2.y_;
    double y_new = v1.z_ * v2.x_ - v1.x_ * v2.z_;
    double z_new = v1.x_ * v2.y_ - v1.y_ * v2.x_;

    return Vector(x_new, y_new, z_new);
}

//-------------------------------------------------------------------------------//

void Vector::PrintVector() const
{
    std::cout << "Vector has coordinates (" << 
        x_ << ";" << y_ << ";" << z_ << ")" << std::endl; 
}

//-------------------------------------------------------------------------------//