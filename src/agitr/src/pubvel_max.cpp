#include<ros/ros.h>
#include<geometry_msgs/Twist.h>
#include<stdlib.h>

int main(int argc, char **argv){
    ros::init(argc,argv, "publish_velocity");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);

    srand(time(0));

    const std::string PARAM_NAME = "~max_vel";
    double maxVel;
    bool ok = ros::param::get(PARAM_NAME, maxVel);
    if(!ok){
        ROS_FATAL_STREAM("Could not get param" << PARAM_NAME);
        exit(1);
    }

    ros::Rate rate(2);
    while(ros::ok()){
        geometry_msgs::Twist msg;
        msg.linear.x = maxVel * double(rand())/double(RAND_MAX);
        msg.angular.z = 2 * double(rand())/double(RAND_MAX) - 1;

        pub.publish (msg);

        ROS_INFO_STREAM("Sending velocity command"
        << "linear= " << msg.linear.x
        << "angular= " << msg.angular.z
        );
        rate.sleep();
    }


}