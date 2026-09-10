#ifndef POLYGON_PLUGINS__POLYGON_PLUGINS_HPP_
#define POLYGON_PLUGINS__POLYGON_PLUGINS_HPP_

#include <polygon_base/regular_polygon.hpp>
#include <cmath>

namespace polygon_plugins
{
  class Square : public polygon_base::RegularPolygon
  {
    public:
      void initialize(double side_length) override
      {
        side_length_ = side_length;
      }

      double area() override
      {
        return side_length_ * side_length_;
      }

    private:
      double side_length_;
  };

  class Triangle : public polygon_base::RegularPolygon
  {
    public:
      void initialize(double side_length) override
      {
        side_length_ = side_length;
      }

      double area() override
      {
        return 0.5 * side_length_ * height();
      }

      double height()
      {
        return sqrt((side_length_ * side_length_) - ((side_length_ / 2) * (side_length_ / 2)));
      }

    private:
      double side_length_;
  };

  class House : public polygon_base::RegularPolygon
  {
    public:
      void initialize(double side_length) override
      {
        square_.initialize(side_length);
        triangle_.initialize(side_length);
      }
  
      double area() override
      {
        return square_.area() + triangle_.area();
      }
            
    private:
      Square square_;
      Triangle triangle_;
  };
}  // namespace polygon_plugins

#endif  // POLYGON_PLUGINS__POLYGON_PLUGINS_HPP_
