## 📦 **Generic Filters Controller for ros2_controls**  

### 🔍 **Overview**  
The **Generic Filters Controller** is a plugin for the **ros2_controls** framework, designed to apply customizable filtering to state or command interfaces in a robot control system. It is based on the initial implementation from the **ROSCon 2024 Control Workshop**, where a basic chained filter example was showcased.  

This project moves the filter to the **ros2_controls** repository, enhances it with parameterization, and adds comprehensive testing. The controller leverages ROS2's **control_toolbox** package to support multiple filter types, including:  

- 🏞️ **Low-Pass Filter** — Smooths data by reducing high-frequency noise.  
- 🎚️ **High-Pass Filter** — Captures rapid changes by filtering out low-frequency components.  
- 🏗️ **Median Filter** — Useful for eliminating outliers and spikes in data.

---

## 📂 **Project Structure**  
```plaintext
ros2_controls/
├── ros2_controllers/
│   ├── src/
│   │   └── generic_filters_controller/
│   │       ├── generic_filters_controller.cpp
│   │       └── generic_filters_controller.hpp
│   ├── include/
│   │   └── generic_filters_controller/
│   │       └── generic_filters_controller.hpp
│   ├── plugin/
│   │   └── generic_filters_controller.xml
│   ├── test/
│       └── test_generic_filters_controller.cpp
```

---

## 🚀 **Installation Instructions**  
1. **Create a Workspace:**  
```bash
mkdir -p ~/ros2_ws/src && cd ~/ros2_ws/src
```

2. **Clone Required Repositories:**  
```bash
git clone https://github.com/ros-controls/ros2_controls.git
git clone https://github.com/ros-controls/ros2_control_demos.git
git clone https://github.com/ros-controls/control_toolbox.git
git clone https://github.com/ros-controls/roscon2024_control_workshop.git
```

3. **Source ROS2 Environment:**  
```bash
source /opt/ros/humble/setup.bash
```

4. **Build the Workspace:**  
```bash
cd ~/ros2_ws
colcon build --symlink-install
source install/setup.bash
```

## 🏗️ **How It Works**  
- **Input Interfaces:** Reads data from state interfaces.  
- **Filter Application:** Applies the selected filter type.  
- **Output Interfaces:** Writes filtered values to a new interface.  

This structure allows chaining multiple controllers or processing state data before use.

---

## 🧪 **Testing**  
Comprehensive unit and integration tests are provided to ensure the controller works as expected.  

### **Run Tests:**  
```bash
colcon test --packages-select ros2_controllers
colcon test-result --verbose
```

✅ **Tests cover:**  
- **Correct filter application** for each filter type.  
- **Edge cases** such as empty inputs and extreme values.  
- **Chaining multiple controllers** for advanced processing.  

---


🚀 **Enjoy clean, smooth control data with the Generic Filters Controller!**
# ✅ **Step 1: Setup Repositories & Environment**

⏱️ **Time Estimate:** 1-2 hours  

### **Objective:**  
Prepare the development environment by setting up the workspace and cloning all necessary repositories. Ensure ROS2 (Humble/Rolling) is properly sourced.

---

### 🔍 **Why This Matters:**  
Having an organized workspace ensures efficient compilation and debugging of **ros2_controls** packages.

---

### 📂 **Workspace File Structure (After This Step):**  
```plaintext
~/ros2_ws/src/
├── roscon2024_control_workshop/               # Contains original filter example
├── ros2_controls/                             # Main repo for ros2 controllers
├── ros2_control_demos/                        # For demos and examples
├── control_toolbox/                           # Provides ready-made filters
```

---

### 💻 **Commands to Run:**  
```bash
# 1. Create a workspace
mkdir -p ~/ros2_ws/src && cd ~/ros2_ws/src

# 2. Clone required repositories
git clone https://github.com/ros-controls/roscon2024_control_workshop.git
git clone https://github.com/ros-controls/ros2_controls.git
git clone https://github.com/ros-controls/ros2_control_demos.git
git clone https://github.com/ros-controls/control_toolbox.git

# 3. Source ROS2
source /opt/ros/humble/setup.bash

# 4. Build the workspace
cd ~/ros2_ws
colcon build --symlink-install
```

✅ **Verify Installation:**  
```bash
source install/setup.bash
ros2 pkg list | grep ros2_controls
```

---

---

# ✅ **Step 2: Migrate the Filter from Workshop to ros2_controls**

⏱️ **Time Estimate:** 2-3 hours  

### **Objective:**  
Move the **filter controller** from the **ROSCon 2024 workshop** repository to the **ros2_controls** package.

---

### 🔍 **Why This Matters:**  
The existing filter is a proof of concept. Migrating it to **ros2_controls** enables **reusability**, **maintainability**, and **extensibility**.

---

### 📂 **File Structure (After This Step):**  
```plaintext
ros2_controls/
├── ros2_controllers/
│   ├── src/
│       └── generic_filters_controller/
│           ├── generic_filters_controller.cpp
│           └── generic_filters_controller.hpp
│   ├── plugin/
│       └── generic_filters_controller.xml
```

---

### 💻 **Commands to Run:**  
```bash
# 1. Create the necessary directories
cd ~/ros2_ws/src/ros2_controls/ros2_controllers
mkdir -p src/generic_filters_controller
mkdir -p include/generic_filters_controller
mkdir -p plugin

# 2. Copy the existing filter from the workshop
cp ~/ros2_ws/src/roscon2024_control_workshop/workshop_controllers/src/chained_filter_done.cpp \
   src/generic_filters_controller/generic_filters_controller.cpp

# 3. Rename headers and update include paths
mv src/generic_filters_controller/chained_filter_done.cpp \
   src/generic_filters_controller/generic_filters_controller.cpp
```

---

### ✏️ **Edit the Plugin File (generic_filters_controller.xml):**  
```xml
<library path="libgeneric_filters_controller.so">
  <class name="GenericFiltersController"
         type="generic_filters_controller::GenericFiltersController"
         base_class_type="controller_interface::ControllerInterface">
    <description>Generic filters controller for chaining state interfaces.</description>
  </class>
</library>
```

---

### ✏️ **Modify CMakeLists.txt:**  
```cmake
add_library(generic_filters_controller SHARED
  src/generic_filters_controller/generic_filters_controller.cpp
)

target_include_directories(generic_filters_controller PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

pluginlib_export_plugin_description_file(controller_interface plugin/generic_filters_controller.xml)

ament_export_dependencies(controller_interface)
```

---

✅ **Verify the Build:**  
```bash
cd ~/ros2_ws
colcon build --packages-select ros2_controllers
```

---

---

# ✅ **Step 3: Generalize the Filter Plugin**

⏱️ **Time Estimate:** 4-5 hours  

### **Objective:**  
Transform the filter controller to support **multiple filter types** with dynamic parameters from **control_toolbox**.

---

### 🔍 **Why This Matters:**  
This allows developers to easily switch between **low-pass**, **high-pass**, and **median** filters using ROS2 parameters.

---

### 📂 **File Structure (After This Step):**  
```plaintext
ros2_controls/
├── ros2_controllers/
│   ├── include/generic_filters_controller/generic_filters_controller.hpp
│   ├── src/generic_filters_controller/generic_filters_controller.cpp
```

---

### 💻 **Commands to Run:**  
```bash
# Edit the C++ file
nano src/generic_filters_controller/generic_filters_controller.cpp
```

---

### ✏️ **Edit `generic_filters_controller.cpp` to Support Multiple Filters:**  
```cpp
#include <control_toolbox/filter_base.hpp>
#include <control_toolbox/low_pass_filter.hpp>
#include <control_toolbox/high_pass_filter.hpp>
#include <control_toolbox/median_filter.hpp>

std::shared_ptr<control_toolbox::FilterBase> filter_;

// Load Parameters
auto param_listener = std::make_shared<ParamListener>(get_node());
auto params = param_listener->get_params();

if (params.filter_type == "low_pass") {
    filter_ = std::make_shared<control_toolbox::LowPassFilter>();
    filter_->configure(params.cutoff_frequency, get_node());
} else if (params.filter_type == "high_pass") {
    filter_ = std::make_shared<control_toolbox::HighPassFilter>();
} else {
    filter_ = std::make_shared<control_toolbox::MedianFilter>();
}
```

---

✅ **Build and Test:**  
```bash
cd ~/ros2_ws
colcon build --packages-select ros2_controllers
colcon test --packages-select ros2_controllers
```

---

---

# ✅ **Step 4: Create Unit & Integration Tests**

⏱️ **Time Estimate:** 4-6 hours  

### **Objective:**  
Ensure the controller functions as expected by writing **unit tests** and **integration tests**.

---

### 🔍 **Why This Matters:**  
Automated testing ensures the controller handles edge cases and works with multiple filter types.

---

### 📂 **File Structure (After This Step):**  
```plaintext
ros2_controls/
├── ros2_controllers/
│   ├── test/
│       └── test_generic_filters_controller.cpp
```

---

### 💻 **Commands to Run:**  
```bash
mkdir -p ~/ros2_ws/src/ros2_controls/ros2_controllers/test
cd ~/ros2_ws/src/ros2_controls/ros2_controllers/test
nano test_generic_filters_controller.cpp
```

---

### ✏️ **Write a Basic Unit Test:**  
```cpp
#include <gtest/gtest.h>
#include <generic_filters_controller/generic_filters_controller.hpp>

class GenericFiltersControllerTest : public ::testing::Test {
protected:
    void SetUp() override {
        controller_ = std::make_shared<generic_filters_controller::GenericFiltersController>();
    }
    std::shared_ptr<generic_filters_controller::GenericFiltersController> controller_;
};

TEST_F(GenericFiltersControllerTest, AppliesLowPassFilter) {
    double input = 10.0;
    double expected_output = 5.0;  // Hypothetical
    ASSERT_NEAR(controller_->filter(input), expected_output, 0.1);
}
```

---

✅ **Run Tests:**  
```bash
colcon build --packages-select ros2_controllers
colcon test --packages-select ros2_controllers
colcon test-result --verbose
```

---

✅ **Summary of Steps 1-4:**  
| **Step** | **Task** | **Time Estimate** |
|----------|---------|------------------|
| **1** | Setup workspace and repositories | 2h |
| **2** | Migrate existing filter to ros2_controls | 3h |
| **3** | Generalize the filter with parameters | 5h |
| **4** | Write unit and integration tests | 6h |  

Would you like me to help with specific test cases or build issues? 🚀
