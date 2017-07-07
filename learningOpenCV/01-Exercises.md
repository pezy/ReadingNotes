# Exercises

## Download and install the latest release of OpenCV. Compile it in debug and release mode

Download from <https://github.com/opencv/opencv/releases>, then same as using Git.

## Download and build the latest trunk version of OpenCV using Git

In Windows:

```sh
cd c:
mkdir opencv && cd opencv
git clone git@github.com:opencv/opencv.git source
```

1. open CMake(cmake-gui).
1. drag the CMakeLists.txt(in source) to it.
1. set build path, `C:/opencv/build` for me.
1. check Advanced, then Configure.
1. choose `Visual Studio 14 2015 Win64` for me.
1. chonfigure again, and check the configuration.
1. generate.
1. open `C:\opencv\build\OpenCV.sln`.
1. build.
1. set `Install` as active project, then build.
1. the `C:\opencv\build\install` directory would be generated.
1. set System Enviroments: `OPENCV_DIR`:  `C:\opencv\build\install`

Note:

1. In CMake configure, you can check `BUILD_opencv_world`, then you will get only one lib and dll.
1. You can check `BUILD_EXAMPLES`, that will let you more easy to start.

When you new a project with OpenCV:

1. `Properties` -> `C/C++` -> `Additional Include Directories` -> `$(OPENCV_DIR)\include`
1. `Properties` -> `Linker` -> `Additional Library Directories` -> `$(OPENCV_DIR)\x64\vc14\lib`
1. `Properties` -> `Linker` -> `Input` -> `Additional Dependencies` -> `opencv_world330d.lib` or `opencv_world330.lib`(debug or release mode)
1. `Properties` -> `Debugging` -> `Enviroment` -> `PATH=$(OPENCV_DIR)\x64\vc14\bin%3b$(PATH)`

## Describe at least three ambiguous aspects of converting 3D inputs into a 2D representation. How would you overcome these ambiguities

1. variations in the world (weather, lighting, reflections, movements)
1. imperfections in the lens and mechanical setup
1. finite integration time on the sensor (motion blur)
1. electrical noise in the sensor or other electronics
1. compression artifacts after image capture
