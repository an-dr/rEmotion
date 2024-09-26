# rEmotion control library

The library provides an API to control the rEmotion module.

The library provides two classes:

- `remotion::RemotionCamera` - the class to read camera data.
- `remotion::RemotionController` - the main class to control the rEmotion module - setting emotions and moving.

 Check the example  [example/src/app.cpp](example/src/app.cpp). To read the supported formats of your webcam use the following command:

```bash
v4l2-ctl --list-formats-ext
```

Based on the format you might need different conversions in order to display the image correctly.

## Requirements and Building

All library dependencies are already included in the repository. You can check them in the meson file. The only package that we need is `meson` to build the library. And for building just run the script.

```bash
bash library/scripts/build_library.sh
```

But you want to build the example you'll need at least OpenCV, so the dependencies will be:

- libopencv-dev
- meson

To integrate the library into your meson project:

1. Clone the repository in some place in your project, e.g. `MyProject/submodules/rEmotion`.
2. Create a `subproject` directory in your project near the `meson.build` file, e.g. `MyProject/src/subprojects`.
3. Go to your subproject folder and create a relative symlink e.g.:

    ```bash
    cd MyProject/src/subprojects
    ln -s ../../submodules/rEmotion/library remotion_control
    ```

As a result you'll have something like this:

```plaintext
MyProject
│
├── submodules
│   └── rEmotion
│       ├── ...
│       └── library
├── src
│   ├── include
│   ├── src
│   ├── subprojects
│   │   └── remotion_control -> ../../submodules/rEmotion/library
│   ├── ...
│   └── meson.build
├── ...
└── README
```

In the meson file of your project you can add the following lines:

```meson
remotion_control_dep = subproject('remotion_control')

...

exe = executable('my_app',
  ...
  dependencies: [remotion_control_dep],
  ...
)
```
