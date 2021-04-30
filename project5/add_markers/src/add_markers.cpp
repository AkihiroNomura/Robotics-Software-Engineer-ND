#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h> 
#include <nav_msgs/Odometry.h>
#include <math.h>

bool at_pickup_zone = false;
bool at_drop_off_zone = false;
double threshold = 0.2;

double pickup_zone_x = 0.3;
double pickup_zone_y = 3.0;
double drop_off_zone_x = -2.0;
double drop_off_zone_y = -0.3;

double distance(double x1, double x2, double y1, double y2)
{
  return sqrt(pow((x1 - x2), 2.0) + pow((y1 - y2), 2.0));
}

void odomCallback(const nav_msgs::Odometry &odom_msg)
{
  // ROS_INFO("odom : x %lf  : y %lf\n", odom_msg.pose.pose.position.x, odom_msg.pose.pose.position.y); 
  double current_position_x = odom_msg.pose.pose.position.y;
  double current_position_y = (-1) * odom_msg.pose.pose.position.x;
  
  // ROS_INFO("current position : x %lf  : y %lf\n", current_position_x, current_position_y); 
  // ROS_INFO("pickup distance: %lf \n", distance(current_position_x, pickup_zone_x, current_position_y, pickup_zone_y));
  // ROS_INFO("drop off distance: %lf \n", distance(current_position_x, drop_off_zone_x, current_position_y, drop_off_zone_y));
  
  if (distance(current_position_x, pickup_zone_x, current_position_y, pickup_zone_y) <= threshold)
  {
    at_pickup_zone = true;
  }
  else
  {
    at_pickup_zone = false;
  }
  
  if (distance(current_position_x, drop_off_zone_x, current_position_y, drop_off_zone_y) <= threshold)
  {
    at_drop_off_zone = true;
  }
  else
  {
    at_drop_off_zone = false;
  }
  
  return;
}
  
int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  
  ros::Subscriber odom_sub = n.subscribe("odom", 1, odomCallback);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  while (ros::ok())
  {
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    // For pickup zone
    marker.pose.position.x = pickup_zone_x;
    marker.pose.position.y = pickup_zone_y;
    marker.pose.position.z = 1.0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.5;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Publish the marker for pickup zone
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    // ROS_INFO("Sending marker at pickup zone");
    marker_pub.publish(marker);
    
    while (!at_pickup_zone)
    {
      ros::spinOnce();
    }
    ROS_INFO("Arrived at pickup zone");
    
    // Wait 5 seconds
    ros::Duration(5).sleep();
    
    // Delete (hide) the marker
    ROS_INFO("Pickup the marker");
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);
    
    // Set the marker action to ADD
    marker.action = visualization_msgs::Marker::ADD;
    
    // Set the pose of the marker for drop off zone
    marker.pose.position.x = drop_off_zone_x;
    marker.pose.position.y = drop_off_zone_y;
    // marker.pose.position.z = -1.0;
    
    ROS_INFO("Go to drop off zone");
    while (!at_drop_off_zone)
    {
      ros::spinOnce();
    }
    ROS_INFO("Arrived at drop off zone");

    // Publish the marker for drop off zone
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    ROS_INFO("Drop off the marker!");
    marker_pub.publish(marker);
    
    return 0;
  }
}