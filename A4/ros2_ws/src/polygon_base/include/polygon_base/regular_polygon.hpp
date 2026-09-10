/*
 * regular_polygon.hpp
 *
 * This file declares the common interface implemented by all polygon plugins
 * used in the Pluginlib example.
 */

#ifndef POLYGON_BASE__REGULAR_POLYGON_HPP_
#define POLYGON_BASE__REGULAR_POLYGON_HPP_


namespace polygon_base
{

// RegularPolygon defines the interface through which polygon plugins are
// initialized and queried for their area.
class RegularPolygon
{
  public:

    // Initializes the polygon using the supplied side length.
    virtual void initialize( double side_length ) = 0;

    // Returns the area of the initialized polygon.
    virtual double area() = 0;

    virtual ~RegularPolygon() {}

  protected:

    RegularPolygon() {}
};

}  // namespace polygon_base


#endif  // POLYGON_BASE__REGULAR_POLYGON_HPP_