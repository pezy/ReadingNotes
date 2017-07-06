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
- gpu: 在 OpenCV3 中被拆分为多组 cuda* 模块, 
- photo

