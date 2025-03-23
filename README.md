### ✅ **Comprehensive Plan to Implement a Generic "Filters" Plugin for `ros2_controls`**

This plan provides a step-by-step guide to creating, integrating, and testing a **generic filters plugin** for **`ros2_controls`**. It includes repository structure, build instructions, file modifications, and testing details.

---

## **1. Clone and Prepare Repositories**
Ensure you have all the relevant repositories cloned.

### **Commands:**
```bash
# Navigate to your ROS2 workspace
mkdir -p /workspaces/ros2_ws/src
cd /workspaces/ros2_ws/src

# Clone necessary repositories
git clone https://github.com/ros-controls/ros2_controls.git
git clone https://github.com/ros-controls/ros2_control_demos.git
git clone https://github.com/ros-controls/control_toolbox.git
git clone https://github.com/ros-controls/roscon2024_control_workshop.git

# Source the ROS2 environment
source /opt/ros/humble/setup.bash
```

---

## **2. Understanding the Repositories**
- **`ros2_controls`**: Core ROS2 control framework.
- **`ros2_control_demos`**: Example usage and demonstrations.
- **`control_toolbox`**: Provides utility controllers and filters.
- **`roscon2024_control_workshop`**: Contains the initial filter blueprint.  

### 🔍 **Filter Blueprint:**  
Located in:  
**`roscon2024_control_workshop/workshop_controllers/src/chained_filter_done.cpp`**  
This is the starting point for your plugin.

---

## **3. Create the Generic Filters Plugin in `ros2_controls`**
We need to create a new plugin in **`ros2_controls/ros2_controllers`**.

### **Step-by-Step:**

### ✅ **File Structure:**
```bash
ros2_controls/
├── ros2_controllers/
│   ├── src/
│   │   ├── generic_filters_controller/
│   │   │   ├── include/
│   │   │   │   └── generic_filters_controller/
│   │   │   │       └── generic_filters_controller.hpp
│   │   │   ├── src/
│   │   │   │   └── generic_filters_controller.cpp
│   │   │   ├── CMakeLists.txt
│   │   │   ├── package.xml
│   │   │   ├── plugin_description.xml
```

---

## **4. Implement the Filter Plugin**
### 🔨 **4.1. Create the Header File**
**Location:**  
`include/generic_filters_controller/generic_filters_controller.hpp`

```cpp
#pragma once

#include <controller_interface/controller_interface.hpp>
#include <rclcpp_lifecycle/lifecycle_node.hpp>
#include <control_toolbox/filter_functions.hpp>

namespace generic_filters_controller
{
class GenericFiltersController : public controller_interface::ControllerInterface
{
public:
  GenericFiltersController() = default;

  controller_interface::CallbackReturn on_init() override;
  controller_interface::CallbackReturn on_configure(const rclcpp_lifecycle::State & previous_state) override;
  controller_interface::return_type update(const rclcpp::Time & time, const rclcpp::Duration & period) override;

private:
  double filtered_output_;
};
}  // namespace generic_filters_controller
```

---

### 🔨 **4.2. Create the Source File**
**Location:**  
`src/generic_filters_controller.cpp`

```cpp
#include "generic_filters_controller/generic_filters_controller.hpp"
#include <pluginlib/class_list_macros.hpp>

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

controller_interface::return_type GenericFiltersController::update(const rclcpp::Time &, const rclcpp::Duration & period)
{
  // Example filter: Exponential moving average
  double input = 1.0;  // Replace with real input
  double alpha = 0.5;  // Smoothing factor
  filtered_output_ = alpha * input + (1 - alpha) * filtered_output_;
  
  RCLCPP_INFO(get_node()->get_logger(), "Filtered output: %f", filtered_output_);
  return controller_interface::return_type::OK;
}

}  // namespace generic_filters_controller

// Export the plugin
PLUGINLIB_EXPORT_CLASS(generic_filters_controller::GenericFiltersController, controller_interface::ControllerInterface)
```

---

## **5. Define the Plugin and Build Files**

### 🔨 **5.1. CMakeLists.txt**  
**Location:**  
`~/ros2_ws/src/ros2_controls/ros2_controllers/src/generic_filters_controller/CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 3.5)
project(generic_filters_controller)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(control_toolbox REQUIRED)
find_package(controller_interface REQUIRED)
find_package(pluginlib REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)

add_library(${PROJECT_NAME} SHARED src/generic_filters_controller.cpp)

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
```

---

### 🔨 **5.2. package.xml**  
**Location:**  
`~/ros2_ws/src/ros2_controls/ros2_controllers/src/generic_filters_controller/package.xml`

```xml
<package format="2">
  <name>generic_filters_controller</name>
  <version>0.1.0</version>
  <description>Generic Filters Plugin for ros2_controls</description>
  <maintainer email="your_email@example.com">Your Name</maintainer>
  <license>Apache-2.0</license>

  <buildtool_depend>ament_cmake</buildtool_depend>
  <build_depend>rclcpp</build_depend>
  <build_depend>controller_interface</build_depend>
  <build_depend>pluginlib</build_depend>
  <build_depend>control_toolbox</build_depend>

  <exec_depend>rclcpp</exec_depend>
  <exec_depend>controller_interface</exec_depend>
  <exec_depend>pluginlib</exec_depend>
  <exec_depend>control_toolbox</exec_depend>

  <export>
    <pluginlib plugin="plugin_description.xml"/>
  </export>
</package>
```

---

### 🔨 **5.3. plugin_description.xml**  
**Location:**  
`plugin_description.xml`

```xml
<library path="libgeneric_filters_controller.so">
  <class name="generic_filters_controller/GenericFiltersController"
         type="generic_filters_controller::GenericFiltersController">
    <description>Generic Filters Controller for ros2_controls</description>
  </class>
</library>
```

---

## **6. Modify Top-level CMakeLists.txt**
Add this line in **`ros2_controllers/CMakeLists.txt`**:

```cmake
add_subdirectory(src/generic_filters_controller)
```

---

## **7. Build the Project**
Navigate to your workspace root and build the project.

```bash
cd ~/ros2_ws
colcon build --symlink-install
source install/setup.bash
```

---


## **8. Test the Plugin**
Run a ROS2 launch file or node that uses the plugin.  
```bash
ros2 run generic_filters_controller generic_filters_controller_node
```

---

## **9. Final Steps**
- Create a PR with your changes.
- Follow up with a demo in **`ros2_control_demos`** showcasing how the filter works in a controller chain.

---

✅ **This plan ensures a structured workflow with a clear file structure, build instructions, and testing process for your ROS2 filter plugin.** 🚀
