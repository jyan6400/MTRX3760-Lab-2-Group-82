#include <polygon_plugins/polygon_plugins.hpp>
#include <pluginlib/class_list_macros.hpp>

PLUGINLIB_EXPORT_CLASS(polygon_plugins::Square, polygon_base::RegularPolygon)
PLUGINLIB_EXPORT_CLASS(polygon_plugins::Triangle, polygon_base::RegularPolygon)

// New class
PLUGINLIB_EXPORT_CLASS(polygon_plugins::House, polygon_base::RegularPolygon)
