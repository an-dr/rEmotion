# API

The library provides a set of functions to control the module. The module is represent with a class Remotion.

- `RemotionError start(std::string port_name, int video_source)`
- `cv::Mat readImage(RemotionError *error_buff=nullptr)`
- `RemotionError setExpression(Expressions exp)`
- `RemotionStatus getStatus()`
