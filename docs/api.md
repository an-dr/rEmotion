# API

The library provides a set of functions to control the module. The module is represent with a class Remotion.

- `RemotionError start(std::string device, int width, int height, int format, int fps)` 
    - start the module with the given parameters. The function returns an error code.
- `void stop()` 
    - stop the module.
- `RemotionError readVideoFrame(char *out_buffer, size_t out_buffer_size)` 
    - read a video frame from the module. The function returns an error code.
- `int getVideoCaptureBufferSize()` 
    - get the size of the video capture buffer.
- `RemotionError setExpression(RemotionExpression exp)` 
    - set the expression. The function returns an error code.
- `RemotionStatus getStatus()` 
    - get the status of the module.
