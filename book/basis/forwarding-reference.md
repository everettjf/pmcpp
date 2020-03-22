# Forwarding Reference

还是上篇文章中flutter中的这段代码，这篇文章试图弄明白`Args&&` 和 `std::forward`。

```
template <typename T, typename... Args>
RefPtr<T> MakeRefCounted(Args&&... args) {
  return internal::MakeRefCountedHelper<T>::MakeRefCounted(
      std::forward<Args>(args)...);
}
```

## 引用的种类

要弄清楚`Args&&`，首先要知道C++11引入的一个重要概念就是`右值`。这样C++中的值就有两种：`左值`（lvalue）和`右值`（rvalue）。

> 右值（lvalue）又分为两种`prvalue（pure rvalue）`和`xvalue (expiring value)`。这篇文章就不细说了，个人感觉只是概念而已，不知道也能写代码哈。

`右值`的引用就是`右值引用`，语法层面，右值引用的一个重要特性就是使用`&&`（例如`int &&`或者`const int &&`等），这样C++中就有了两个标记来表示引用：`&`和`&&`。

然而`&&`在某些场景下并不是`右值引用`，而是`forwarding reference`。

关于`&`和`&&`，[C++标准](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4164.pdf)中这样说到：

![](/media/15556665402559.jpg)

- `&` ：lvalue reference（左值引用）
- `&&` ：rvalue reference（右值引用）或者 forwarding reference

C++中目前只有这三种引用类型。

`forwarding reference`的特殊之处是：他既可能是`左值引用`，也可能是`右值引用`，详见下文。

> `forwarding reference` 目前还没有一个合适的中文翻译，或许可以叫`转发引用`（还没人这么叫，这是我直译过来的啊），如果要搜中文资料的话，目前需要搜`万能引用`或`通用引用`，对应英文是`universal reference`。`universal reference`是早期`Scott Meyers`于2012年提出的，但后来C++标准认为这个叫法不太合适，于是2014年最终在上文提到的C++标准中正式修正叫法为`forwarding reference`。

## 如何区分

既然`&&`既可能是右值引用，也可能是forwarding reference。如何区分`rvalue reference` 和 `forwarding reference`呢？

`forwarding reference`仅存在两种场景：

第一种，

```
template <typename T>
void f(T&& param); // 必须严格匹配T&&
```

第二种，

```
auto&& var2 = var1;
```

这两种场景都涉及`类型推导`，也就是类型推导导致了：他既可能是`左值引用`，也可能是`右值引用`。我们要弄明白的`Args&&`，就是第一种场景，只不过同时与`可变参数模板`结合在了一起（`Args&&...`）。

除了这两种情况，其他都是`rvalue reference`了，例如：

```
int && x2 = x1;
Widget && w2 = w1;

template <typename T>
void f(const T&& param); // 存在const
```


## 引用折叠（reference collapsing）

那么我们看第一种场景，

```
template <typename T>
void f(T&& param);
```

在处理`forwarding reference`时，C++引入了一个规则，即`引用折叠`（reference collapsing），规则如下。关于为什么存在`forwarding reference`及`reference collapsing`，StackOverflow有个[不错的回答](https://stackoverflow.com/questions/20364297/why-universal-references-have-the-same-syntax-as-rvalue-references)。

```
& & -> &
& && -> &
&& & -> &
&& && -> &&
```

看如下例子：

```
f(1)
```

1是右值，T推导为`T&&`，f则为 `f(int&& && param)`，根据引种折叠，最终为`f(int&& param)`。param此时是个右值引用，与1是右值匹配。


```
Widget a; // 或 Widget &a = b;
f(a) 
```

a是左值（或注释种的左值引用），T会推断为左值引用（这是个C++的规定），即`T&`，也即`Widget&`，f就是`f(Widget& &&param)`，根据引用折叠的规则`& && -> &`，则f最终为`f(Widget& param)`。param此时是个左值引用，与a是左值匹配。

```
Widget foo(); // function
f(foo());
```

foo()返回一个`xvalue`，也是右值。T推导为`T&&`，也即`Widget&&`，则f是`f(Widget&& && param)`，根据引种折叠，`f(Widget&& param)`。

可见，不管是f传入左值，还是右值，最终推倒后，都是对应匹配的引用。左值对应左值引用，右值对应右值引用。这就是“他既可能是`左值引用`也可能是`右值引用`”的原因。


## std::forward

先看forward的实现：

![](/media/15556907748082.jpg)

其中最关键的代码就最后return那一句：`return static_cast<_Tp&&>(__t)`。两个forward的函数重载是为了接收左值引用参数和右值引用参数。


现在把本文开头那段代码，去掉可变参数模板后，精简如下：

```
void g(int& param) {
    cout<< "g int&"<<endl;
}
void g(int&& param) {
    cout << "g int&&" <<endl;
}
template <typename T>
void f(T&& param){
    g(std::forward<T>(param));
}
int call(){
    return 1;
}
void main(){
    f(1);
    int a = 1;
    f(a);
    f(call());
}
```

输出是：

```
g int&&
g int&
g int&&
```

当`f(1)`时，T推导为`int&&`，f推导为：

```
f(int&& param) {
    g(std::forward<int&&>(param);
}
```

此时调用forward后，

`return static_cast<_Tp&&>(__t)`

会推倒为：

`return static_cast<int&& &&>(__t)`

再次引用折叠

`return static_cast<int&&>(__t)`

也就是把f的参数`完美转发`给了g。因此`std::forward`也称为`完美转发`（perfect forwarding）。



## 总结

回到文章开头的例子， `MakeRefCounted` 的作用就是把参数完美转发给`internal::MakeRefCountedHelper<T>::MakeRefCounted`。

Emmmm...看来下一步需要进一步研究下`internal::MakeRefCountedHelper<T>::MakeRefCounted` 了。


这篇文章超出了我预想的`简洁`，试图更简单的讲明白这个，还真是有点费劲。不得不承认`Forwarding Reference`在我学习C++11时确实是个坎。

未来的几篇文章会简单、轻松很多。



---


欢迎关注订阅号 :)

![](/media/bukuzao.jpg)

