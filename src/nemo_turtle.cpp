#include <chrono>
#include <functional>
#include <memory>


#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;

class NemoTurtle : public rclcpp::Node
{
  public:
    NemoTurtle()
    : Node("nemo_turtle"), count_(0)
    {
      publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);
      timer_ = this->create_wall_timer(
      1000ms, std::bind(&NemoTurtle::timer_callback, this));
    }

  private:
    int A = 0;
    
    void timer_callback()
    {
      auto message = geometry_msgs::msg::Twist();
      
      if ((A%2) == 0)
      {message.linear.x = 2.0; }  
      else 
      {message.angular.z = 1.5707963268; }

      publisher_->publish(message);
      A = A + 1;
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    int count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<NemoTurtle>());
  rclcpp::shutdown();
  return 0;
}


