project('remotion_control', 'cpp',
        version : '2.0.0',
        license : 'MIT',
        default_options : ['warning_level=3'])


# ========================
# Library
# ========================

public_include = ['include']
src = [ 
        'src/RemotionContoller.cpp',
        'src/RemotionCamera.cpp',
]

cmake = import('cmake')

libv4l2cpp_proj = cmake.subproject('libv4l2cpp')

opt_var = cmake.subproject_options()
opt_var.add_cmake_defines({'BUILD_TESTS': 'OFF'})
cpp_linux_serial_proj = cmake.subproject('CppLinuxSerial', options: opt_var)
cpp_linux_serial_dep = cpp_linux_serial_proj.dependency('CppLinuxSerial')

v4l2_dep = libv4l2cpp_proj.dependency('libv4l2cpp')
deps = [cpp_linux_serial_dep,
        v4l2_dep]

lib = static_library(meson.project_name(), 
                     src, 
                     dependencies : deps,
                     include_directories : public_include,
                     install : true,
                     install_dir: meson.project_name() + '/lib',
)

install_subdir(public_include, 
               install_dir: meson.project_name())


# ========================
# Dependency
# ========================

dep = declare_dependency(link_with : lib,
                         include_directories : public_include)
                         
# Expose the dependencies to the parent project
meson.override_dependency(meson.project_name(), dep)
meson.override_dependency('libv4l2cpp', v4l2_dep)
meson.override_dependency('CppLinuxSerial', cpp_linux_serial_dep)

