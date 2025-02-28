// #include "vicon_receiver/publisher.hpp"

// Publisher::Publisher(std::string topic_name, rclcpp::Node* node)
// {
//     position_publisher_ = node->create_publisher<vicon_receiver::msg::Position>(topic_name, 10);
//     is_ready = true;
//     std::cout << "Publisher is ready for topic: " << topic_name << std::endl;
// }

// void Publisher::publish(PositionStruct p)
// {
//     auto msg = std::make_shared<vicon_receiver::msg::Position>();
//     msg->x_trans = p.translation[0];
//     msg->y_trans = p.translation[1];
//     msg->z_trans = p.translation[2];
//     msg->x_rot = p.rotation[0];
//     msg->y_rot = p.rotation[1];
//     msg->z_rot = p.rotation[2];
//     msg->w = p.rotation[3];
//     msg->subject_name = p.subject_name;
//     msg->segment_name = p.segment_name;
//     msg->frame_number = p.frame_number;
//     msg->translation_type = p.translation_type;
//     std::cout << "Published message: x_trans=" << msg->x_trans << ", y_trans=" << msg->y_trans << ", z_trans=" << msg->z_trans << std::endl;
//     position_publisher_->publish(*msg); // PROBLEM SEEMS TO BE HERE
//     // std::cout << "position_publisher has published" << std::endl; WORKS
// }

#include "vicon_receiver/publisher.hpp"
#include "rclcpp/rclcpp.hpp"

Publisher::Publisher(std::string topic_name, rclcpp::Node* node)
{
    // Create publisher
    position_publisher_ = node->create_publisher<vicon_receiver::msg::Position>(topic_name, 10);

    // Create subscriber
    position_subscriber_ = node->create_subscription<vicon_receiver::msg::Position>(
        topic_name,
        10,
        std::bind(&Publisher::callback, this, std::placeholders::_1));

    is_ready = true;
    std::cout << "Publisher is ready for topic: " << topic_name << std::endl;
}

void Publisher::publish(PositionStruct p)
{
    auto msg = std::make_shared<vicon_receiver::msg::Position>();
    msg->x_trans = p.translation[0];
    msg->y_trans = p.translation[1];
    msg->z_trans = p.translation[2];
    msg->x_rot = p.rotation[0];
    msg->y_rot = p.rotation[1];
    msg->z_rot = p.rotation[2];
    msg->w = p.rotation[3];
    msg->subject_name = p.subject_name;
    msg->segment_name = p.segment_name;
    msg->frame_number = p.frame_number;
    msg->translation_type = p.translation_type;
    std::cout << "Published message: x_trans=" << msg->x_trans << ", y_trans=" << msg->y_trans << ", z_trans=" << msg->z_trans << std::endl;
    position_publisher_->publish(*msg); 
}

void Publisher::callback(const vicon_receiver::msg::Position::SharedPtr msg) 
{
    // RCLCPP_INFO(this->get_logger(), "I heard something");
    // Process received message here
    std::cout << "Received message: x_trans=" << msg->x_trans << ", y_trans=" << msg->y_trans << ", z_trans=" << msg->z_trans << std::endl;
}
// rclcpp::Subscription<vicon_receiver::msg::Position>::SharedPtr position_subscriber_;
