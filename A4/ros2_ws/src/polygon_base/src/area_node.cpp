/*
 * area_node.cpp
 *
 * This file loads the polygon plugins, initializes each one using the required
 * test side length, and prints their calculated areas.
 */

#include <iostream>
#include <memory>

#include <pluginlib/class_loader.hpp>
#include <polygon_base/regular_polygon.hpp>


int main( int argc, char** argv )
{
  (void) argc;
  (void) argv;

  // Required A4 test side length for all polygon plugins.
  const double TestSideLength{ 10.0 };

  pluginlib::ClassLoader<polygon_base::RegularPolygon> PolyLoader(
    "polygon_base",
    "polygon_base::RegularPolygon" );

  try
  {
    // Load each concrete implementation through the common plugin interface.
    std::shared_ptr<polygon_base::RegularPolygon> Triangle =
      PolyLoader.createSharedInstance( "polygon_plugins::Triangle" );

    std::shared_ptr<polygon_base::RegularPolygon> Square =
      PolyLoader.createSharedInstance( "polygon_plugins::Square" );

    std::shared_ptr<polygon_base::RegularPolygon> House =
      PolyLoader.createSharedInstance( "polygon_plugins::House" );

    // The same test side length is used for all three shapes.
    Triangle->initialize( TestSideLength );
    Square->initialize( TestSideLength );
    House->initialize( TestSideLength );

    std::cout
      << "Triangle area: "
      << Triangle->area()
      << std::endl;

    std::cout
      << "Square area: "
      << Square->area()
      << std::endl;

    std::cout
      << "House area: "
      << House->area()
      << std::endl;
  }
  catch( pluginlib::PluginlibException& ex )
  {
    std::cout
      << "The plugin failed to load. Error: "
      << ex.what()
      << std::endl;
  }

  return 0;
}