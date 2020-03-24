# 使用C++模板生成wasm3函数签名

前不久学习了解了下WebAssembly，推荐一个系列文章，看完即可达到入门级别。

https://developer.mozilla.org/en-US/docs/WebAssembly/Concepts

![](/media/15850625038567.jpg)


然而App开发者看这个有啥用呢，当然是想着能不能让WebAssembly运行到App里。

答案当然是“能”。

在经过各种搜索Github之后，找到了一款WebAssembly解释器。注意，这里是解释器。Github大量的WebAssembly Virtual Machine或多或少带有一些JIT的意思，只有这个是纯正的解释器。

这个解释器就是：wasm3
https://github.com/wasm3/wasm3

![](/media/15850628112952.jpg)


看到上图中闪亮亮的「Android，iOS」了吗？当时找到这个repo时，他就在那里发光～哈 :)

好了……背景就是这样。这篇文章不讲wasm3的使用，有需要的童鞋去看repo里的sample，有点跑题但也不算跑题吧。


## 看到了什么

wasm3中有个函数 m3_LinkRawFunction，可以让宿主环境为WebAssembly脚本提供功能，反过来说，WebAssembly中可以调用宿主的函数。如下图，其中第四个参数是个函数签名。

![](/media/15850630601952.jpg)

而当我看wasm3的c++例子时，发现c++代码中并没有像上图这样手动填写函数签名（姑且就叫做wasm3的函数签名吧）。

![](/media/15850633762679.jpg)

代码见
https://github.com/wasm3/wasm3/blob/master/platforms/cpp/main.cpp

也就是说`mod.link`函数自动把`sum`和`ext_memcpy`的函数签名计算出来了。一直感觉自己c++还算入门的我，顿时有了兴趣。


## 怎么实现的

同样有兴趣的话，可以直接去看代码
https://github.com/wasm3/wasm3/blob/master/platforms/cpp/wasm3_cpp/include/wasm3_cpp.h

也可以看下我抽出来的一个简单例子。

首先定义一些WebAssembly的类型

```
typedef double          f64;
typedef float           f32;
typedef uint64_t        u64;
typedef int64_t         i64;
typedef uint32_t        u32;
typedef int32_t         i32;
typedef uint16_t        u16;
typedef int16_t         i16;
typedef uint8_t         u8;
typedef int8_t          i8;
```

然后定义一个基类。这算是一个`非类型的模板参数` (`non-type template parameters`)，这个模板类用于编译时生成包含value是某个值的类。

```
template<char c>
struct m3_sig {
    static const char value = c;
};
```

然后定义一些具体类型 m3_type_to_sig，默认 m3_type_to_sig 是没有实现的。也就是说除了`模板特化`(`Template Specialization`)的类型之外，不接受其他类型。下面的代码建立了编译时的`类型`（i32、i64、f32这些类型）与`字符`（i、I、f这些字符）的关联。

```
template<typename T> struct m3_type_to_sig;
template<> struct m3_type_to_sig<i32> : m3_sig<'i'> {};
template<> struct m3_type_to_sig<i64> : m3_sig<'I'> {};
template<> struct m3_type_to_sig<f32> : m3_sig<'f'> {};
template<> struct m3_type_to_sig<f64> : m3_sig<'F'> {};
template<> struct m3_type_to_sig<void> : m3_sig<'v'> {};
template<> struct m3_type_to_sig<void *> : m3_sig<'*'> {};
template<> struct m3_type_to_sig<const void *> : m3_sig<'*'> {};
```

然后GetTypeEncoding模板函数，可以把多个模板类型转化成函数签名。

```
template <typename Ret, typename ... Args>
string GetTypeEncoding() {
    char arr[] = {
        m3_type_to_sig<Ret>::value,
        '(',
        m3_type_to_sig<Args>::value...,
        ')',
        0
    };
    return string(arr);
}
```

这里用到了`变参模板`，可参考过去一篇的文章
https://mp.weixin.qq.com/s/iiLXYGrT3TaCe8esSM1gtw

这个函数的使用方法如下：

```
cout << GetTypeEncoding<i32,i32,i32>() << endl;
cout << GetTypeEncoding<i32,f32,f32>() << endl;
```

输出

```
i(ii)
i(ff)
```

最后需要把c函数的参数传递到GetTypeEncoding的模板参数中

```
template <auto value>
class FunctionWrapper;

template<typename Ret, typename ... Args, Ret (*Fn)(Args...)>
class FunctionWrapper<Fn> {
public:
    static string GetFunctionSignature() {
        return GetTypeEncoding<Ret, Args...>();
    }
};
```

通过上图这个方式即可把函数的参数类型逐个传入GetTypeEncoding的模板参数中。

首先定义的`template <auto value> class FunctionWrapper;` 是为了避免传入了`非类型`的模板参数。


使用方法：

```
i32 foo1(i32 a, i32 b) {
    return 0;
}
i64 foo2(i64 a, i64 b) {
    return 0;
}
int main(int argc, const char * argv[]) {
    cout << FunctionWrapper<foo1>::GetFunctionSignature() << endl;
    cout << FunctionWrapper<foo2>::GetFunctionSignature() << endl;
    return 0;
}
```

输出

```
i(ii)
I(II)
```

源码见：

https://github.com/everettjf/pmcpp/blob/master/code/signature/cpp-signature/main.cpp

补充：
需要使用C++17标准编译。C++17的原因是 `template <auto value>`，当然也可以改为C++11的语法，就交给大家了～

## 总结

C++很有趣呀 :)


---


广告时间到。

一个人探索这些偏底层的技术细节，独乐乐不如众乐乐，大家一起探索一起交流。创建了一个群，群内已经有300多位盆友，氛围还真不错。已经不能扫码加了，如需加入，加我微信 everettjf，备注：加群。

抖音团队招iOS开发，初级、中级、高级开发都有需要，欢迎随时联系我（ 微信：everettjf ），`北京、深圳`可以直接来我的部门，`上海`可以推荐到同事部门。工作内容就是`抖音iOS App的业务、性能、稳定性等方方面面`的开发。`入职后的方向看你的兴趣`。

如果不好意思联系我，可以直接扫描下面的二维码选择职位投递。

![](/media/15850648781755.jpg)






