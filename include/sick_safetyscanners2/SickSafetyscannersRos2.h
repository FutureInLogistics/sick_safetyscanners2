#include <sick_safetyscanners_base/SickSafetyscanners.h>
#include <sick_safetyscanners_base/Types.h>
#include <sick_safetyscanners_base/datastructure/Data.h>

#include <sick_safetyscanners2_interfaces/msg/extended_laser_scan.hpp>
#include <sick_safetyscanners2_interfaces/msg/output_paths_msg.hpp>
#include <sick_safetyscanners2_interfaces/srv/field_data.hpp>

#include <sick_safetyscanners2/utils/Conversions.h>
#include <sick_safetyscanners2/utils/MessageCreator.h>

#include <sensor_msgs/msg/laser_scan.hpp>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

namespace sick {

class SickSafetyscannersRos2 : public rclcpp::Node
{
public:
  SickSafetyscannersRos2();

private:
  void receiveUDPPaket(const sick::datastructure::Data& data);

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::Publisher<sensor_msgs::msg::LaserScan>::SharedPtr m_laser_scan_publisher;
  rclcpp::Publisher<sick_safetyscanners2_interfaces::msg::ExtendedLaserScan>::SharedPtr
    m_extended_laser_scan_publisher;
  rclcpp::Publisher<sick_safetyscanners2_interfaces::msg::OutputPathsMsg>::SharedPtr
    m_output_paths_publisher;
  rclcpp::Service<sick_safetyscanners2_interfaces::srv::FieldData>::SharedPtr m_field_data_service;

  std::unique_ptr<sick::AsyncSickSafetyScanner> m_device;
  sick::datastructure::CommSettings m_communications_settings;

  std::unique_ptr<sick::MessageCreator> m_msg_creator;

  boost::asio::ip::address_v4 m_sensor_ip;
  std::string m_frame_id;
  double m_time_offset;
  double m_range_min;
  double m_range_max;
  double m_frequency_tolerance      = 0.1;
  double m_expected_frequency       = 20.0;
  double m_timestamp_min_acceptable = -1.0;
  double m_timestamp_max_acceptable = 1.0;
  double m_min_intensities          = 0.0; /*!< min intensities for laser points */

  bool m_use_sick_angles;
  float m_angle_offset;
  bool m_use_pers_conf;

  // diagnostics?


  // dynamic reconfigure?

  void initialize_parameters();
  void load_parameters();


  // bool getFieldData();
  bool getFieldData(
    const std::shared_ptr<sick_safetyscanners2_interfaces::srv::FieldData::Request> request,
    std::shared_ptr<sick_safetyscanners2_interfaces::srv::FieldData::Response> response);
  void readTypeCodeSettings();
  void readPersistentConfig();

  // void getMedianReflectors(const sick::datastructure::Data);
};
} // namespace sick
