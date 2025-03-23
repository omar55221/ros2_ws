cmake_minimum_required(VERSION 3.5)
project(generic_filters_controller)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(control_toolbox REQUIRED)
find_package(controller_interface REQUIRED)
find_package(pluginlib REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)

add_library(${PROJECT_NAME} SHARED
  src/generic_filters_controller.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

ament_target_dependencies(${PROJECT_NAME}
  rclcpp
  control_toolbox
  controller_interface
  pluginlib
  rclcpp_lifecycle
)

pluginlib_export_plugin_description_file(controller_interface plugin_description.xml)

install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION lib
)

ament_package()
