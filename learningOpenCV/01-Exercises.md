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
1. build `ALL_BUILD`.
1. set `Install` as active project, then build.
1. the `C:\opencv\build\install` directory would be generated.
1. set System Enviroments: `OPENCV_DIR`:  `C:\opencv\build\install`

Note:

1. In CMake configure, you can check `BUILD_opencv_world`, then you will get only one lib and dll.
1. You can check `BUILD_EXAMPLES`, that will let you more easy to start.
1. If you want to add more GUI feature, and the Qt is already installed, then you can check `WITH_QT`.

When you check `WITH_QT`, the compiler may complain an error: `window_QT.obj : error LNK2001`, `31 linkage errors while building OpenCV_world dll`

I find the solution in <http://answers.opencv.org/question/99223/31-linkage-errors-while-building-opencv_world-dll-on-vs2013-with-qt/>

But we don't want to always `moc` the header in every compilation. You can do that to avoid:

1. find `Microsoft.Cpp.x64.user` in Property Manager>, then double-click it.
1. `User Macros` -> `Add Macro` -> Name: `QTDIR`, Value: `{your Qt path}`, such as `C:\Qt\Qt5.7.0\5.7\msvc2015_64`.
1. find the `window_QT.h` in Solution Explorer.(in the `modules` -> `opencv_world` -> `Src`)
1. right-click `window_QT.h` -> `properties` -> `General` -> change the `Item Type` to `Custom Build Tool`, then click the `Apply`.
1. the `Custom Build Tool` would show after apply:
    1. Command Line: `"$(QTDIR)\bin\moc.exe"  "%(FullPath)" -o ".\GeneratedFiles\$(ConfigurationName)\moc_%(Filename).cpp"  -DUNICODE -DWIN32 -DQT_DLL -DQT_CORE_LIB -DQT_GUI_LIB -DQT_WIDGETS_LIB "-I.\GeneratedFiles" "-I." "-I$(QTDIR)\include" "-I.\GeneratedFiles\$(ConfigurationName)\." "-I$(QTDIR)\include\QtCore" "-I$(QTDIR)\include\QtGui" "-I$(QTDIR)\include\QtWidgets"`
    1. Description: `Moc%27ing window_QT.h...`
    1. Outputs: `.\GeneratedFiles\$(ConfigurationName)\moc_%(Filename).cpp`
    1. Additional Dependencies: `$(QTDIR)\bin\moc.exe;%(FullPath)`
1. find the `Include` in Solution Explorer.(in the `modules` -> `opencv_world`)
1. right-click `Include`, and `Add` -> `New Filter`, change name to `GeneratedFiles`. then added `Debug` and `Release` filter in the `GenerateFiles`.
1. added the generated files `moc_window_QT.cpp` in `C:\opencv\build\modules\world\GeneratedFiles` to respective filter(Debug or Release).

then, build again, it would be passed.

When you new a project with OpenCV:

1. `Properties` -> `C/C++` -> `Additional Include Directories` -> `$(OPENCV_DIR)\include`
1. `Properties` -> `Linker` -> `Additional Library Directories` -> `$(OPENCV_DIR)\x64\vc14\lib`
1. `Properties` -> `Linker` -> `Input` -> `Additional Dependencies` -> `opencv_world330d.lib` or `opencv_world330.lib`(debug or release mode)
1. `Properties` -> `Debugging` -> `Enviroment` -> `PATH=$(OPENCV_DIR)\x64\vc14\bin%3b$(PATH)` (or `PATH=$(OPENCV_DIR)\x64\vc14\bin%3b$(QTDIR)\bin%3b$(PATH)` if with QT)

## Describe at least three ambiguous aspects of converting 3D inputs into a 2D representation. How would you overcome these ambiguities

1. variations in the world (weather, lighting, reflections, movements)
1. imperfections in the lens and mechanical setup
1. finite integration time on the sensor (motion blur)
1. electrical noise in the sensor or other electronics
1. compression artifacts after image capture
