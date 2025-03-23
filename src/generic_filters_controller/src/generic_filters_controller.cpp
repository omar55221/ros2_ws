#include "generic_filters_controller/generic_filters_controller.hpp"
#include <pluginlib/class_list_macros.hpp>
#include <control_toolbox/filter_functions.hpp>  // Add this line

namespace generic_filters_controller
{

controller_interface::CallbackReturn GenericFiltersController::on_init()
{
  RCLCPP_INFO(get_node()->get_logger(), "Initializing Generic Filters Controller");
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn GenericFiltersController::on_configure(const rclcpp_lifecycle::State &)
{
  RCLCPP_INFO(get_node()->get_logger(), "Configuring Generic Filters Controller");
  filtered_output_ = 0.0;  // Initialize output
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn GenericFiltersController::on_activate(const rclcpp_lifecycle::State &)
{
  RCLCPP_INFO(get_node()->get_logger(), "Activating Generic Filters Controller");
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn GenericFiltersController::on_deactivate(const rclcpp_lifecycle::State &)
{
  RCLCPP_INFO(get_node()->get_logger(), "Deactivating Generic Filters Controller");
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::return_type GenericFiltersController::update(const rclcpp::Time &, const rclcpp::Duration & period)
{
  // Exponential Moving Average Filter
  double input = 1.0;  // Replace with actual sensor data input
  double alpha = 0.5;  // Smoothing factor
  filtered_output_ = control_toolbox::exponentialSmoothing(input, filtered_output_, alpha);
  
  RCLCPP_INFO(get_node()->get_logger(), "Filtered output: %f", filtered_output_);
  return controller_interface::return_type::OK;
}

// Interface Configuration
controller_interface::InterfaceConfiguration GenericFiltersController::command_interface_configuration() const
{
  return controller_interface::InterfaceConfiguration{
    controller_interface::interface_configuration_type::NONE};
}

controller_interface::InterfaceConfiguration GenericFiltersController::state_interface_configuration() const
{
  return controller_interface::InterfaceConfiguration{
    controller_interface::interface_configuration_type::NONE};
}

}  // namespace generic_filters_controller

// Export the plugin
PLUGINLIB_EXPORT_CLASS(generic_filters_controller::GenericFiltersController, controller_interface::ControllerInterface)
