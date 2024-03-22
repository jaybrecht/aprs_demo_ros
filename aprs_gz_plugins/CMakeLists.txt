cmake_minimum_required(VERSION 3.8)
project(aprs_gz_plugins)

set(THIS_PACKAGE_INCLUDE_DEPENDS
  rclcpp
  example_interfaces
)

find_package(ament_cmake REQUIRED)
find_package(gz-cmake3 REQUIRED)
find_package(gz-plugin2 REQUIRED COMPONENTS register)
find_package(gz-sim7 REQUIRED)

foreach(Dependency IN ITEMS ${THIS_PACKAGE_INCLUDE_DEPENDS})
  find_package(${Dependency} REQUIRED)
endforeach()

add_library(BasicRosSystem SHARED src/basic_ros_system.cpp)
target_include_directories(BasicRosSystem PUBLIC include)

target_link_libraries(BasicRosSystem
  gz-sim7::gz-sim7
)

ament_target_dependencies(BasicRosSystem 
  ${THIS_PACKAGE_INCLUDE_DEPENDS})

ament_export_libraries(BasicRosSystem)

install(
  DIRECTORY worlds/
  DESTINATION share/${PROJECT_NAME}/worlds
)

install(
  TARGETS 
  BasicRosSystem
  DESTINATION lib/${PROJECT_NAME}
)


ament_environment_hooks("${CMAKE_CURRENT_SOURCE_DIR}/hooks/${PROJECT_NAME}.dsv.in")
ament_environment_hooks("${CMAKE_CURRENT_SOURCE_DIR}/hooks/${PROJECT_NAME}.sh.in")

ament_package()
