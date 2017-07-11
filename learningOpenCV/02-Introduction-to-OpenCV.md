# 介绍 OpenCV

## Include 文件

通常需要引用的头文件一般是: `../include/opencv2/opencv.hpp`, 它又会调用以下头文件:

```cpp
#include "opencv2/core/core_c.h" // 传统 C 接口，以及通用计算方法
#include "opencv2/core/core.hpp" // C++ 数据结构，以及通用计算方法
#include "opencv2/flann/miniflann.hpp" // 近似最近邻匹配方法
#include "opencv2/imgproc/imgproc_c.h" // 传统 C 图像处理方法
#include "opencv2/imgproc/imgproc.hpp" // C++ 图像处理方法
#include "opencv2/video/photo.hpp" // 针对照片处理与恢复的算法
#include "opencv2/video/video.hpp" // 影像追踪与通用背景分割方法
#include "opencv2/features2d/features2d.hpp" // 二维特征追踪
#include "opencv2/objdetect/objdetect.hpp" // 人脸识别, 最新支持向量机, 方向梯度直方图, 平面贴片检测
#include "opencv2/calib3d/calib3d.hpp" // 校准与立体
#include "opencv2/ml/ml.hpp" // 机器学习: 集群与模式识别
#include "opencv2/highgui/highgui_c.h" // 传统 C 图像展示, 滑块, 鼠标交互, I/O
#include "opencv2/highgui/highgui.hpp" // C++ 图像展示, 滑块, 按钮, 鼠标, I/O
#include "opencv2/contrib/contrib.hpp" // 用户贡献代码, 前沿检测, 模糊平移追踪, 图像旋转, 自相似特征
```

你完全可以包含一个 "opencv.hpp" 来调用绝大部分 OpenCV 的函数, 但这样会降低编译速度. 如果你只用到图像处理功能, 那么你只引入 "opencv2/imgproc/imgproc.hpp" 会快很多. 类似的, 函数的实现会在它们各自的 `src` 目录下. 例如, `imgproc` 模块的 `cv::Canny()` 实现位于 `../modules/improc/src/canny.cpp`.

## 习题要求编译文档与示例代码

在 CMake 里勾选 `BUILD_DOCS`, 并指定 DOXYGEN 相关路径. 这就要求你安装以下两个工具:

1. [doxygen](http://www.stack.nl/~dimitri/doxygen/index.html)
1. [graphviz](http://www.graphviz.org/)

然后分别指定 doxygen.exe 的位置与 dot.exe 的位置即可.

在 build/doc 下会产生一个 `opencv_docs.sln`, 双击进入, 然后 build `ALL_BUILD` 和 `install_docs` 即可, 最后可以在 doc/doxygen/html/index.html 进入文档.

----

关于示例代码, 在 CMake 里勾选 `BUILD_EXAMPLES` 即可.
