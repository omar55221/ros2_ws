#include <rclcpp/rclcpp.hpp>
#include "generic_filters_controller/generic_filters_controller.hpp"

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<rclcpp::Node>("generic_filters_controller_node");
  auto controller = std::make_shared<generic_filters_controller::GenericFiltersController>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
