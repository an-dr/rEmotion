# rEmotion control library

The library provides an API to control the rEmotion module. Check the example  [example/src/app.cpp](example/src/app.cpp).

The library provides two classes:

- `remotion::RemotionCamera` - the class to read camera data.
- `remotion::RemotionController` - the main class to control the rEmotion module - setting emotions and moving.

To read the supported formats of your webcam use the following command:

```bash
v4l2-ctl --list-formats-ext
```

Based on the format you might need different conversions in order to display the image correctly.

## Requirements

All library dependencies are already included in the repository. You can check them in the meson file. The only package that we need is `meson` to build the library. And for building just run the script.

```bash
bash library/scripts/build_library.sh
```

But you want to build the example you'll need at least OpenCV, so the dependencies will be:

- libopencv-dev
- meson
