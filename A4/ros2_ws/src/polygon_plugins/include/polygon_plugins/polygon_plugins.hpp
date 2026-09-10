/*
 * polygon_plugins.hpp
 *
 * This file declares the concrete polygon plugins used by the ROS 2
 * Pluginlib example, including the House plugin added for A4.
 */

#ifndef POLYGON_PLUGINS__POLYGON_PLUGINS_HPP_
#define POLYGON_PLUGINS__POLYGON_PLUGINS_HPP_

#include <cmath>

#include <polygon_base/regular_polygon.hpp>


namespace polygon_plugins
{

// Square implements the RegularPolygon interface for a square.
class Square : public polygon_base::RegularPolygon
{
  public:

    // Stores the side length used to calculate the square area.
    void initialize( double side_length ) override
    {
      side_length_ = side_length;
    }

    // Returns the area of the initialized square.
    double area() override
    {
      return side_length_ * side_length_;
    }

  private:

    // Length of one side of the square.
    double side_length_{ 0.0 };
};


// Triangle implements the RegularPolygon interface for an equilateral triangle.
class Triangle : public polygon_base::RegularPolygon
{
  public:

    // Stores the side length used to calculate the triangle area.
    void initialize( double side_length ) override
    {
      side_length_ = side_length;
    }

    // Returns the area of the initialized equilateral triangle.
    double area() override
    {
      return 0.5 * side_length_ * height();
    }

  private:

    // Returns the height of the equilateral triangle from its side length.
    double height() const
    {
      const double HalfSide =
        side_length_ / 2.0;

      return std::sqrt(
        ( side_length_ * side_length_ )
        - ( HalfSide * HalfSide ) );
    }

    // Length of one side of the triangle.
    double side_length_{ 0.0 };
};


// House implements the RegularPolygon plugin interface while representing
// its geometry using a composed Square and Triangle.
class House : public polygon_base::RegularPolygon
{
  public:

    // Initializes both component shapes using the same side length.
    void initialize( double side_length ) override
    {
      square_.initialize( side_length );
      triangle_.initialize( side_length );
    }

    // Returns the combined area of the square base and triangular roof.
    double area() override
    {
      return square_.area() + triangle_.area();
    }

  private:

    // Geometric components that make up the house.
    Square square_;
    Triangle triangle_;
};

}  // namespace polygon_plugins


#endif  // POLYGON_PLUGINS__POLYGON_PLUGINS_HPP_