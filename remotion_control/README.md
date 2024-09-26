# rEmotion control library

[![abcmake](https://img.shields.io/badge/uses-abcmake-blue)](https://github.com/an-dr/abcmake)

The library provides an API to control the rEmotion module. Check the example  [example/src/app.cpp](example/src/app.cpp).

To read the supported formats of your webcam use the following command:

```bash
v4l2-ctl --list-formats-ext
```

Based on the format you might need different conversions in order to display the image correctly.

## Requirements

For tests:

- libgtest-dev
