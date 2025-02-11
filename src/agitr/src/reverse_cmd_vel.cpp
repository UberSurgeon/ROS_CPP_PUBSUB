#include<ros/ros.h>
#include <geometry_msgs/Twist.h>

ros::Publisher *pubPtr;

void cb(const geometry_msgs::Twist &msgin){
    geometry_msgs::Twist msgOut;
    msgOut.linear.x = -msgin.linear.x;
    msgOut.angular.z = -msgin.angular.z;
    pubPtr->publish(msgOut); 

}


int main(int argc, char **argv){
    ros::init(argc, argv, "reverse_velocity");
    ros::NodeHandle nh;
    pubPtr = new ros::Publisher(nh.advertise<geometry_msgs::Twist>(
        "turtle1/cmd_vel_reversed", 1000
    ));
    ros::Subscriber sub = nh.subscribe("turtle1/cmd_vel", 1000, &cb);
    ros::spin();
    delete pubPtr;
}