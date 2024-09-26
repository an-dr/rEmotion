project('rEmotion_control-example', 'cpp',
        version : '2.0.0',
        license : 'MIT',
        default_options : ['warning_level=3'])


# ========================
# Library
# ========================

public_include = [ ]
src = [ 'src/app.cpp',
        ]

cmake = import('cmake')
opt_var = cmake.subproject_options()
opt_var.add_cmake_defines({'BUILD_TESTS': 'OFF'})

ocv_dep = dependency('opencv', required: false)
if not ocv_dep.found()
  ocv_dep = dependency('opencv4')
endif

remotion_control_dep = dependency('remotion_control')


deps = [remotion_control_dep,
        ocv_dep,
        dependency('CppLinuxSerial'),
        dependency('libv4l2cpp')
        ]

executable = executable(meson.project_name(), 
                     src, 
                     dependencies : deps,
                     include_directories : public_include,
                     install : true,
                     install_dir: '../install',
)


