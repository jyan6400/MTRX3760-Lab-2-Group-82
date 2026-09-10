#include <pluginlib/class_loader.hpp>
#include <polygon_base/regular_polygon.hpp>
#include <iostream>

int main(int argc, char** argv)
{
  (void) argc;
  (void) argv;

  pluginlib::ClassLoader<polygon_base::RegularPolygon> poly_loader("polygon_base", "polygon_base::RegularPolygon");

  try
  {
    std::shared_ptr<polygon_base::RegularPolygon> triangle = poly_loader.createSharedInstance("polygon_plugins::Triangle");
    triangle->initialize(10.0);

    std::shared_ptr<polygon_base::RegularPolygon> square = poly_loader.createSharedInstance("polygon_plugins::Square");
    square->initialize(10.0);

    std::shared_ptr<polygon_base::RegularPolygon> house = poly_loader.createSharedInstance("polygon_plugins::House");
    house->initialize(10.0);

    std::cout << "Triangle area: " << triangle->area() << std::endl;
    std::cout << "Square area: " << square->area() << std::endl;
    std::cout << "House area: " << house->area() << std::endl;
  }
  catch(pluginlib::PluginlibException& ex)
  {
    std::cout << "The plugin failed to load for some reason. Error: " << ex.what() << std::endl;
  }

  return 0;
}
