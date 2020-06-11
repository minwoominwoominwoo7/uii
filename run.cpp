#include <ros/ros.h>
#include <std_msgs/UInt16.h>
#include <sensor_msgs/Range.h>

double range;
enum State 
{
    IDLE, 
    HEART_OK, 
    HEART_FIRST_STOP, 
    HEART_COMPLETE_STOP
};
State cur_state = IDLE ;
ros::Time heart_first_stop_time ;

void ecg_callback(const sensor_msgs::Range range_msg) {
    ROS_INFO("Hello ROS %f", range_msg.range);
    range = range_msg.range;

    if ( range > 0 ){
        cur_state = HEART_OK;
    }else if ( range == 0 ){
        if (cur_state == HEART_COMPLETE_STOP){
            cur_state = HEART_COMPLETE_STOP;
        }else if ( cur_state == HEART_OK || cur_state == IDLE  ){
            cur_state = HEART_FIRST_STOP;
            heart_first_stop_time = ros::Time::now();
        }else if ( cur_state == HEART_FIRST_STOP ){
            if ( 5 < ( ros::Time::now().toSec() - heart_first_stop_time.toSec()) ){
                // 심박이 0이고 5초이상 지속=심정지로 판단
                cur_state = HEART_COMPLETE_STOP;
            }
        }
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "dyros_publisher_node");
    ros::NodeHandle nh;
    ros::Subscriber helloros_sub = nh.subscribe("/ecg", 1, &ecg_callback);
    ros::Publisher helloros_pub = nh.advertise<std_msgs::UInt16>("/heartrate", 1000);
    heart_first_stop_time = ros::Time::now();

    ros::Rate rate(10);     
    std_msgs::UInt16 msg;

    while(ros::ok()) {
        ros::spinOnce();
        if ( cur_state == HEART_OK ){
            msg.data = 1;
            ROS_INFO("send heart ok data to arduino");            
        }else if ( cur_state == HEART_COMPLETE_STOP ){
            msg.data = 0;
            ROS_INFO("send heart stop data to arduino");       
        }
        helloros_pub.publish(msg); 
        rate.sleep();
    }

    return 0;
}