#include <gz/common/Console.hh>

#include <gz/plugin/Register.hh>

#include <aprs_gz_plugins/basic_ros_system.hpp>

GZ_ADD_PLUGIN(
  aprs_gz_plugins::BasicRosSystem,
  gz::sim::System,
  aprs_gz_plugins::BasicRosSystem::ISystemConfigure
  // aprs_gz_plugins::BasicRosSystem::ISystemUpdate
)

namespace aprs_gz_plugins 
{

void BasicRosSystem::Configure(
  const gz::sim::Entity &_entity,
  const std::shared_ptr<const sdf::Element> &_sdf,
  gz::sim::EntityComponentManager &_ecm,
  gz::sim::EventManager &)
{
  if (!rclcpp::ok()) {
    rclcpp::init(0, nullptr);
  }

  ros_node_ = rclcpp::Node::make_shared("basic_ros_system");

  executor_ = std::make_shared<rclcpp::executors::MultiThreadedExecutor>();
  executor_->add_node(ros_node_);
  
  auto spin = [this]()
    {
      while (rclcpp::ok()) {
        executor_->spin_once();
      }
    };

  thread_executor_spin_ = std::thread(spin);

  sub_ = ros_node_->create_subscription<example_interfaces::msg::Bool>(
    "/test", 1, std::bind(&BasicRosSystem::OnBoolMsg, this, std::placeholders::_1) 
  );

  std::cout << "Plugin loaded" << std::endl;
}

// void BasicRosSystem::Update(
//   const gz::sim::UpdateInfo &_info,
//   gz::sim::EntityComponentManager &_ecm)
// {
//   //
// }

void BasicRosSystem::OnBoolMsg(const example_interfaces::msg::Bool::SharedPtr msg) const 
{
  std::cout << "callback received" << std::endl;
}

}  // namespace aprs_gz_plugins
