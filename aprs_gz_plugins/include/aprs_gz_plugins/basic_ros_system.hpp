#ifndef APRS_GZ_PLUGINS__BASIC_ROS_SYSTEM_HPP_
#define APRS_GZ_PLUGINS__BASIC_ROS_SYSTEM_HPP_

#include <thread>

#include <gz/sim/System.hh>

#include <rclcpp/rclcpp.hpp>

#include <example_interfaces/msg/bool.hpp>

namespace aprs_gz_plugins
{
  class BasicRosSystem:
    public gz::sim::System,
    public gz::sim::ISystemConfigure,
    public gz::sim::ISystemUpdate
  {
    public: 
      void Configure(
        const gz::sim::Entity &_entity,
        const std::shared_ptr<const sdf::Element> &_element,
        gz::sim::EntityComponentManager &_ecm,
        gz::sim::EventManager &_eventManager) override;

      void Update(
        const gz::sim::UpdateInfo &_info,
        gz::sim::EntityComponentManager &_ecm) override;

    private:
      rclcpp::Node::SharedPtr ros_node_;
      rclcpp::executors::MultiThreadedExecutor::SharedPtr executor_;
      std::thread thread_executor_spin_;
      rclcpp::Subscription<example_interfaces::msg::Bool>::SharedPtr sub_;

      void OnBoolMsg(const example_interfaces::msg::Bool::SharedPtr msg) const;


  };
}
#endif
