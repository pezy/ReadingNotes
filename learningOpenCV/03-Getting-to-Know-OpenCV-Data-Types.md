# 开始了解 OpenCV 的数据类型

## 基本类型

最直接的基本数据类型是模板类 `cv::Vec<>`, 一个原始类型的容器类, 我们称之为**定长向量类**. 为什么不直接用 STL 的类呢? 最关键的不同在于: 定长向量类, 注意力放在那些在编译期就知道维度的小 vectors 上.
这就使得处理一些小型公共操作, 会很高效. "小"的意思在于, 如果你用的元素个数比较多了, 那么这个类可能就不适合你.(事实上, 在 2.2 版, 超过 9 就完蛋了) 在下一章, 我们将关注 `cv::Mat` 类, 那才是对任意维度的大数组的正确处理方式. 现在, 我们仅考虑定长向量类对于小数据集合的方便与高效.

类似的, 还有 `cv::Matx<>`. 用作矩阵运算. `cv::Point<>` 作为坐标.

`cv::Scalar` 本质上是一个四维的 Point. 但与 Point 不同的是, 它只支持下标访问, 就像 `cv::Vec<>` 一样, 更准确的说, 是 `cv::Vec<double, 4>` 的实例化.

`cv::Size` 和 `cv::Rect` 就更好理解了, 前者有两个成员: width, height; 后者有四个, 除了长宽, 还有起始点的 x, y.

`cv::RotatedRect` 与 `cv::Rect` 的最大区别是: 前者以中心点为第一参数, 而后者以左上角为第一参数.

定长矩阵类的效率很高, 因为在编译期就确定了尺寸. 因此其数据所有内存都分配在栈上, 可以被快速的分配与清理. 定长矩阵类其实是一个模板, 但单个矩阵通常会用别名, 别名的形式如下: `cv::Matx{1,2,...}{1,2,...}`, 其中的数字范围是 1~6. 如果你要表示的范围非常大, 这个必然不合适. 可以考虑后续介绍的 `cv::Mat`.

定长 `vector` 派生自定长矩阵类. `cv::Vec<>` is a `cv::Matx<>`, 但维度为 1. 用的时候也会借助别名, 和固定矩阵类的形式类似.

OpenCV 中的复数类与 STL 中的兼容, 最显著的一点区别在于, STL 中读取实部与虚部, 需要借助 `real()` 和 `imag()` 接口.

## 辅助对象

`cv::TermCriteria` 是一个终止条件变量. 关键参数: `type`, `maxCount`, `epsilon`.

`cv::Range` 类用来指定一段 int 型的连续区间. 关键参数: `start`, `end`. 与 STL 的习惯一样, end 是一个标志位, 不在范围区间中. 如 `rng(0,4)` 包含的值是 0, 1, 2, 3. 关键方法: `size`, `empty`, `all`.

`cv::Ptr` 模板与垃圾回收 101 : 与 C++11 之后的 `std::shared_ptr` 机制类似. 同样借助引用计数来回收. 并且专门提示, 说是线程安全的.

`cv::Exception` 派生自 `std::exception`. 其成员有 `code`, `err`, `func`, `file` 和 `line`, 代表着错误代码, 错误描述信息, 错误发生所在函数名, 错误发生所在文件名及在文件中的行数.

几个比较有用的宏:

```cpp
CV_Error( errorcode, description ); // 生成并抛出异常, 并给出相应描述
CV_Error_( errorcode, printf_fmt_str, [printf-args] ); // 这个就是允许描述信息按照 printf-like 的形式组织
CV_Assert( condition ); // 相当于 assert();
CV_DbgAssert( condition ); // 这个与上面的作用类似, 但仅在 debug 条件下工作.
```

`cv::DataType<>` 模板, OpenCV 中具体数据类型, 多自此特例化而来. 这有点类似 C++ 的特征萃取技术(types traits). 针对基本类型(float), 复杂类型(Rect)分别举例说明.

`cv::InputArray` 和 `cv::OutputArray` 统一了输入输出接口. It is const.

这一大截东西略感无聊, 感觉介绍的干巴巴的.
