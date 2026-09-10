/*
 * polygon_plugins.cpp
 *
 * This file registers the concrete polygon classes with Pluginlib so they can
 * be created dynamically through the RegularPolygon interface.
 */

#include <polygon_plugins/polygon_plugins.hpp>

#include <pluginlib/class_list_macros.hpp>


// Register the concrete polygon implementations with the common plugin
// interface used by the class loader.
PLUGINLIB_EXPORT_CLASS(
  polygon_plugins::Square,
  polygon_base::RegularPolygon )

PLUGINLIB_EXPORT_CLASS(
  polygon_plugins::Triangle,
  polygon_base::RegularPolygon )

PLUGINLIB_EXPORT_CLASS(
  polygon_plugins::House,
  polygon_base::RegularPolygon )