cmake_minimum_required(VERSION 3.8)
project(polygon_plugins)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(pluginlib REQUIRED)
find_package(polygon_base REQUIRED)

add_library(polygon_plugins SHARED src/polygon_plugins.cpp)
target_include_directories(polygon_plugins PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
ament_target_dependencies(polygon_plugins polygon_base pluginlib)


pluginlib_export_plugin_description_file(polygon_base polygon_plugins.xml)

install(TARGETS polygon_plugins
  DESTINATION lib
)
install(FILES polygon_plugins.xml
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
