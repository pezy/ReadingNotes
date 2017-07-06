# 概览

## 关于 OpenCV

如果在 Intel 架构下需要进一步自动优化, 可以购买 Intel's Integrated Performance Primitives (IPP). 在 OpenCV 3.0 以后, Intel 授权给 OpenCV 团队与社区一份免费的 IPP 子集 (IPPICV), 已默认内置于 OpenCV, 为 OpenCV 提速。

## 使用 OpenCV

OpenCV 的开源协议, 允许你在商业产品中使用, 并无需开源该产品或是公开实现. 当然, 如果你能那样做更好.

## 什么是计算机视觉

计算机视觉是一种数据转换, 它根据静态图片或视频, 来做出结论, 或采用一种更新的方式呈现. 所有这些转换, 都是为了某种特定的目的. 输入数据可能包含一些上下文信息, 诸如"车里安装了相机"或"激光测距仪表明一米远处有一个物体". 做出的结论可能是"场景里有一个人"或是"载玻片上有14个肿瘤细胞". 一种更新的呈现方式, 可以是将有颜色的图片, 转为灰度图, 也可以是从图像序列中移除相机运动.

## OpenCV 的一些资料

- [Reference](http://docs.opencv.org/master/)
- [Tutorials](http://docs.opencv.org/master/d9/df8/tutorial_root.html)
- [Wiki](https://github.com/opencv/opencv/wiki)
- [Q&A](http://answers.opencv.org/questions/)

## OpenCV 的主要模块

- core: 基本对象类型与操作
- imgproc: 基本的图像转换, 包括滤波器与近似卷积运算.
- highgui: 轻量级 GUI 工具, 在 OpenCV3 中细分为 imgcodec, vidioio 和 highgui.
- video: 读写视频流
- calib3d: 单个相机与立体或相机组的校准算法实现
- features2d: 特征点的检测, 描述与匹配算法
- objdetect: 特定对象的检测, 如人脸与行人. 也可以训练探测器用来检测其他物体.
- ml: 机器学习库本身就是一个独立的库, 包含一个广泛的机器学习算法, 以及兼容 OpenCV 的数据结构.
- flann: 即“快速最邻近搜索库”.
- gpu: 在 OpenCV3 中被拆分为多组 cuda* 模块, 包含针对 CUDA GPU 操作的优化. 有时需要提供更优秀的结果, 需要足够高的计算资源. 但在非 GPU 硬件上实用性将大大减弱.
- photo: 这是一个比较新的模块, 用于可计算的摄影控制.
- stitching: 该模块实现了一个复杂的图像拼接管道. 和 photo 模块一样, 这也是一个较新的模块, 有待增长.
- nonfree: 在 OpenCV3 中移至 opencv_contrib/xfeatures2d 中. 包含了一些特殊的算法实现, 要么受制于专利, 要么有使用限制(如 SIFT 算法). 这些算法被隔离在各自模块中, 如果要在商业产品中使用它们, 你或许得做一些额外的工作.
- contrib: 在 OpenCV3 中, 部分已融入 opencv_contrib 模块中.
- legacy: 在 OpenCV3 中废弃.
- ocl: 在 OpenCV3 中废弃, 用 T-API 技术替代. 这也是与 GPU 模块类似的技术, 但它实现了用于开放并行编程的 OpenCL 标准. 虽然此刻其特性不如 GPU 模块, 但其目标在于可以在任何 GPU 或 Khronos 兼容的并行设备上运行. (而 GPU 模块明确运用了 Nvidia 的 CUDA 工具包, 专注于 Nvidia 设备)

## OpenCV Contribution Repository

从 OpenCV3.0 开始, 以前的单库分为了两个部分:

1. 成熟的 OpenCV
1. 当前状态下拥有更多功能的 opencv_contrib

前者由 OpenCV 核心团队维护, 涵盖大多数稳定代码. 后者不太成熟, 由社区开发力量来维护, 且部分不受 OpenCV license 的管控, 可能涵盖一些专利算法.

以下是其主要模块:

- Dnn: 深度神经网络
- face: 人脸识别
- text: 文本检测与识别, 可能选择性的使用开源 OCR Tesseract 为后端.
- rgbd: 处理 RGB+ 深度图, 配合 Kinect 和 其他深度传感器(或简单与立体图像对应算法配合计算)
- bioinspired: 仿生视觉
- ximgproc, xphoto: 先进的图像处理和计算摄影学算法
- tracking: 现代的物体追踪算法