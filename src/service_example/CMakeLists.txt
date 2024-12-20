cmake_minimum_required(VERSION 3.8)
project(service_example)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_srvs REQUIRED)
find_package(rclcpp_components REQUIRED) #组件


## --------------------------------------------------------------
## |                       service_client                         |
## --------------------------------------------------------------


#/ 创建共享库/#
add_library(service_client  SHARED
  src/service_client_example.cpp
)
#/ 添加依赖/#
ament_target_dependencies(service_client 
  rclcpp
  rclcpp_components
  std_srvs
)
target_compile_definitions(service_client 
  PRIVATE "service_example_BUILDING_DLL")

#/组件注册/#
rclcpp_components_register_nodes(service_client  PLUGIN "service_example::ServiceClientExample" EXECUTABLE service_client )

## --------------------------------------------------------------
## |                       service_server                            |
## --------------------------------------------------------------


#/ 创建共享库/#
add_library(service_server SHARED
  src/service_server_example.cpp
)
#/ 添加依赖/#
ament_target_dependencies(service_server
  rclcpp
  rclcpp_components
  std_srvs
)
target_compile_definitions(service_server
  PRIVATE "service_example_BUILDING_DLL")

#/组件注册/#
rclcpp_components_register_nodes(service_server PLUGIN "service_example::ServiceServerExample" EXECUTABLE service_server)


## --------------------------------------------------------------
## |                           install                          |
## --------------------------------------------------------------
install(TARGETS

  service_server
  service_client
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
