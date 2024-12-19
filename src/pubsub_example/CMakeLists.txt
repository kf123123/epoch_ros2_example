cmake_minimum_required(VERSION 3.8)
project(pubsub_example)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rclcpp_components REQUIRED) #组件

#add_executable(publisher src/publisher_node.cpp)

## --------------------------------------------------------------
## |                       publisher                            |
## --------------------------------------------------------------


#/ 创建共享库/#
add_library(publisher SHARED
  src/publisher_.cpp
)
#/ 添加依赖/#
ament_target_dependencies(publisher
  rclcpp
  rclcpp_components
  std_msgs
)
target_compile_definitions(publisher
  PRIVATE "pubsub_example_BUILDING_DLL")

#/组件注册/#
rclcpp_components_register_nodes(publisher PLUGIN "pubsub_example::PublisherExample" EXECUTABLE publisher)


## --------------------------------------------------------------
## |                       subscriber                            |
## --------------------------------------------------------------


#/ 创建共享库/#
add_library(subscriber SHARED
  src/subscriber_.cpp
)
#/ 添加依赖/#
ament_target_dependencies(subscriber
  rclcpp
  rclcpp_components
  std_msgs
)
target_compile_definitions(subscriber
  PRIVATE "pubsub_example_BUILDING_DLL")

#/组件注册/#
rclcpp_components_register_nodes(subscriber PLUGIN "pubsub_example::SubscriberExample" EXECUTABLE subscriber)




## --------------------------------------------------------------
## |                           install                          |
## --------------------------------------------------------------
install(TARGETS

  publisher
  subscriber
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

install(DIRECTORY config
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
