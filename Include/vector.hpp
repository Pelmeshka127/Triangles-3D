#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <iostream>
#include <cmath>

#include "point.hpp"

class Vector
{
    private:
        double x_;
        double y_;
        double z_;

    public:
        Vector(const double x = 0, const double y = 0, const double z = 0) : 
            x_{x}, y_{y}, z_{z} {}

        Vector(const Point &p) :
            x_{p.GetX()}, y_{p.GetY()}, z_{p.GetZ()} {}

        Vector(const Point &p1, const Point &p2) : 
            x_{p2.GetX() - p1.GetX()}, y_{p2.GetY() - p1.GetY()}, z_{p2.GetZ() - p1.GetZ()} {}

        ~Vector() {}

        bool IsNullVector(const Vector &v1) const
        {
            return (double_numbers::IsEqual(v1.x_, 0) &&
                    double_numbers::IsEqual(v1.y_, 0) &&
                    double_numbers::IsEqual(v1.z_, 0));
        }

        Vector operator=(const Vector &v)
        {
            return Vector(v.x_, v.y_, v.z_);
        }

        Vector &operator+=(const Vector &v)
        {
            x_ += v.x_;
            y_ += v.y_;
            z_ += v.z_;

            return *this;
        }

        Vector operator+(const Vector &v) const
        {
            return Vector(x_ + v.x_, y_ + v.y_, z_ + v.z_);
        }

        Vector &operator-=(const Vector &v)
        {
            x_ -= v.x_;
            y_ -= v.y_;
            z_ -= v.z_;

            return *this;
        }

        Vector operator-(const Vector &v) const
        {
            return Vector(x_ - v.x_, y_ - v.y_, z_ - v.z_);
        }

        Vector &operator*=(const int &number)
        {
            x_ *= number;
            y_ *= number;
            z_ *= number;

            return *this;
        }

        Vector operator*(const int &number) const
        {
            return Vector(x_ * number, y_ * number, z_ * number);
        }

        bool operator==(const Vector &v) const
        {
            return (double_numbers::IsEqual(x_, v.x_) &&
                    double_numbers::IsEqual(y_, v.y_) &&
                    double_numbers::IsEqual(z_, v.z_));
        }

        double Length() const
        {
            return (std::sqrt(x_ * x_ + y_ * y_ + z_ * z_));
        }

        double ScalarProduct(const Vector &v1, const Vector &v2) const
        {
            return (v1.x_ * v2.x_ + v1.y_ * v2.y_ + v1.z_ * v2.z_);
        }

        bool IsOrthogonal(const Vector &v1, const Vector &v2) const
        {
            return (double_numbers::IsEqual(ScalarProduct(v1, v2), 0));
        }

        Vector VectorProduct(const Vector &v1, const Vector &v2) const
        {
            double x_new = v1.y_ * v2.z_ - v1.z_ * v2.y_;
            double y_new = v1.z_ * v2.x_ - v1.x_ * v2.z_;
            double z_new = v1.x_ * v2.y_ - v1.y_ * v2.x_;

            return Vector(x_new, y_new, z_new);
        }

        bool IsCollinear(const Vector &v1, const Vector &v2) const
        {
            return double_numbers::IsEqual( v1.y_ * v2.z_ - v1.z_ * v2.y_ +
                                            v1.z_ * v2.x_ - v1.x_ * v2.z_ +
                                            v1.x_ * v2.y_ - v1.y_ * v2.x_, 0);
        }

        double MixedProduct(const Vector &v1, const Vector &v2, const Vector &v3) const
        {
            return (ScalarProduct(v1, VectorProduct(v2, v3)));
        }

        bool AreCoplanar(const Vector &v1, const Vector &v2, const Vector &v3) const
        {
            return double_numbers::IsEqual(MixedProduct(v1, v2, v3), 0);
        }

        void PrintVector() const
        {
            std::cout << "Vector has coordinates (" << 
                x_ << ";" << y_ << ";" << z_ << ")" << std::endl; 
        }
};

#endif