#pragma once

#include <controller_interface/controller_interface.hpp>
#include <rclcpp_lifecycle/lifecycle_node.hpp>
#include <control_toolbox/filters.hpp>

namespace generic_filters_controller
{
class GenericFiltersController : public controller_interface::ControllerInterface
{
public:
  GenericFiltersController() = default;

  controller_interface::CallbackReturn on_init() override;
  controller_interface::CallbackReturn on_configure(const rclcpp_lifecycle::State & previous_state) override;
  controller_interface::return_type update(const rclcpp::Time & time, const rclcpp::Duration & period) override;
  controller_interface::CallbackReturn on_activate(const rclcpp_lifecycle::State & previous_state) override;
  controller_interface::CallbackReturn on_deactivate(const rclcpp_lifecycle::State & previous_state) override;
  controller_interface::InterfaceConfiguration command_interface_configuration() const override;
  controller_interface::InterfaceConfiguration state_interface_configuration() const override;

private:
  double filtered_output_;
};
}  // namespace generic_filters_controller
