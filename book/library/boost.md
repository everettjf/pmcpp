# Boost C++ Libraries在iOS/Android上的基础使用

## Boost库是什么

Boost provides free peer-reviewed portable C++ source libraries. 这是官方网站的第一句话。`免费、同行评审、可移植、开源`四个关键词。

Wikipedia如下介绍：

Boost是一组C++语言的库，它提供了很多任务和数据结构上的支持，如线性代数，伪随机数生成，多线程，图像处理，正则表达式和单元测试等。它包含超过80个独立的库。

大多数Boost库都是使用Boost协议授权的，目的是允许Boost与免费和特有的软件一起使用。 Boost的许多创始人都在C++标准委员会中，而且已经有好几个Boost库最终成为了C++标准库。

原文如下：

> Boost is a set of libraries for the C++ programming language that provide support for tasks and structures such as linear algebra, pseudorandom number generation, multithreading, image processing, regular expressions, and unit testing. It contains over eighty individual libraries.

> Most of the Boost libraries are licensed under the Boost Software License, designed to allow Boost to be used with both free and proprietary software projects. Many of Boost's founders are on the C++ standards committee, and several Boost libraries have been accepted for incorporation into both the C++ Technical Report 1 and the C++11 standard.

官方网站是：https://www.boost.org/ 印象中这个UI风格至少6年没变了。

![](/media/15603512589772.jpg)



## Boost库有什么

目前最新版本是1.70.0

![](/media/15603514703685.jpg)

Boost包含的库的完整列表可见 https://www.boost.org/doc/libs/1_70_0/

下面的截图`只是一小部分`

![](/media/15603516040216.jpg)





## 下载

点击[官网](https://www.boost.org/) Current Release 中的`Download`。

![](/media/15603517695530.jpg)

然后下载`boost_1_70_0.7z` （或者 boost_1_70_0.zip 等）。


## Header-Only 方式使用

Boost方便的地方在于：大部分的库是Header-Only的。也就是不需要编译，只包含头文件就能使用。

那么首先我们先解压下载的文件，例如：解压后放到HOME目录下的 `~/local/src/boost_1_70_0`。

```
/Users/YourUserName/local/src/boost_1_70_0
```

![](/media/15603523019544.jpg)

由于只需要包含头文件，那我们在配置工程时只需要配置`include path`即可。


### iOS 使用

只需要配置`Header Search Paths`为`$HOME/local/src/boost_1_70_0`，如下图：

![](/media/15603541858597.jpg)


那么为了在iOS工程中使用C++，可以把`AppDelegate.m` 改名为`AppDelegate.mm` (Objective C++)，然后感受下boost提供的format功能。

头文件

```
#include <boost/format.hpp>
```

使用boost format：

```
auto str = boost::format("writing %1%,  x=%2% : %3%-th try") % "toto" % 40.23 % 50;
NSLog(@"%s",str.str().c_str());
```

![](/media/15603548676181.jpg)

参考代码：

https://github.com/everettjf/pmcpp/tree/master/boost



### Android 使用


使用 Android Studio 创建一个 `Native C++` 工程。

![](/media/15603550683562.jpg)


修改 `CMakeList.txt`文件，加入 `include_directories($ENV{HOME}/local/src/boost_1_70_0)`， 如下图：

![](/media/15603552090481.jpg)

然后同样的使用方式，

![](/media/15603553316526.jpg)

参考代码：https://github.com/everettjf/pmcpp/tree/master/boost

## 编译使用


Boost的大部分库都是Header-Only的，少部分库是需要编译的，如下：

![](/media/15603554860802.jpg)


还有一些库介于两者之间，一部分功能Header-Only即可，另一部分功能需要编译。如下：

![](/media/15603555384787.jpg)

那么如何编译呢？

macOS和Windows平台编译比较简单，按照官方提供的工具一步一步操作即可。详细可见：

- [Linux / macOS Getting Started](https://www.boost.org/doc/libs/1_70_0/more/getting_started/unix-variants.html)
- [Windows Getting Started](https://www.boost.org/doc/libs/1_70_0/more/getting_started/windows.html)

iOS和Android的编译就不是那么方便了，具体怎么操作网上有很多人总结了一些脚本，由于我自己最近也没用（也不打算用编译版本），我就不再总结了哈，详细参考这两个链接或者自行搜索。

- https://minidump.info/blog/2017/05/build-boost-for-4-platforms/
- https://www.jianshu.com/p/64a873ec30aa




## 总结

Boost C++ Libraries 十分庞大，可以在[了解有什么](https://www.boost.org/doc/libs/1_70_0/)后根据需要选用。未来我会选取几个常用的功能，让我们一起踏入这个宝库。另外，在开发`Messier`（可在订阅号或博客了解什么是Messier）的过程中用了不少好玩实用的boost header-only的库的功能，未来慢慢分享。

虽然9102年了，但C++仍然是很多上层技术的基石，在可预见的未来仍然没有替代品（个人观点哦），欢迎加入微信群交流哈。点击订阅号菜单`C++`加群。

---

有趣，欢迎关注。

![](/media/bukuzao.jpg)




