# 可变参数模板函数


flutter engine 的代码中存在下面这个模版函数，初次看这个定义，很容易被吓到。这篇文章就先讲下其中一部分。

```
// Creates an intrusively reference counted |T|, producing a |RefPtr<T>| (and
// performing the required adoption). Use like:
//
//   auto my_foo = MakeRefCounted<Foo>(ctor_arg1, ctor_arg2);
//
// (|my_foo| will be of type |RefPtr<Foo>|.)
template <typename T, typename... Args>
RefPtr<T> MakeRefCounted(Args&&... args) {
  return internal::MakeRefCountedHelper<T>::MakeRefCounted(
      std::forward<Args>(args)...);
}
```

## 使用方式

使用方式很简单，如注释所示：

```
auto my_foo = MakeRefCounted<Foo>(ctor_arg1, ctor_arg2);
```

`Foo` 是个类名，`ctor_arg1, ctor_arg2`是构造函数的两个参数，返回的`my_foo` 是 `RefPtr<T>`类型，本例中就是 `RefPtr<Foo>` 类型。

从`typename... Args`可知，这是个`可变参数模板`，应用到`MakeRefCounted` 函数上，就是`可变参数模板函数`，因此`MakeRefCounted` 的参数是可动态变化的，用来适应各种类的各种构造函数。


## 可变参数模板函数

可变参数模板是`C++11`引入的，`函数`和`类`都可以`可变参数`。上面的例子只涉及`函数`。那我们就单独看可变参数模板函数，最简单的可变参数模板函数如下：

```
// print parameter count
template <typename ... T>
void print_param_count(T... args) {
    cout << sizeof...(args) << endl;
}
```

`sizeof...(args)`可直接输出可变参数的个数。使用方法如下：

```
print_param_count();
print_param_count(1);
print_param_count(1,2);
print_param_count(1,2,3);
```

则输出：

```
0
1
2
3
```


## 展开方式一

单纯打印参数个数肯定是不够的，我们需要对每一个参数都能操作，就需要可变参数的展开。一种展开方式是：递归。


```
// expand parameters : method 1
void print_params_one() {
    cout << "last" << endl;
}
template <typename T, typename ... Q>
void print_params_one(T first, Q ... others) {
    cout << first << endl;
    print_params_one(others...);
}
```

没有参数的 `print_params_one()` 是用来终止递归的，`print_params_one(T first, Q ... others)` 则把参数分解成两部分，`第一个参数`和`剩余参数`，然后对第一个参数`first`进行操作（本例中就是通过cout打印），并继续分解剩余的参数。


## 展开方式二

这个方式利用了`逗号表达式`和`初始化列表`。

```
// expand parameters : method 2
template <typename T>
void print_arg(T t) {
    cout << t << endl;
}
template <typename ... T>
void print_params_two(T ... args) {
    int arr[] = {(print_arg(args),0)...};
    // or
    //initializer_list<int>{(print_arg(args),0)...};
}
```

`(print_arg(args),0)`是一个逗号表达式，逗号表达式会先逐个执行逗号分隔开的每一个表达式，然后返回最后一个逗号之后的表达式的值。这里就是会执行`print_arg(args)`，然后返回 0 。

`初始化列表` 是指用可用大括号的语法来初始化`数组`、`STL容器`等，例如：

```
int arr[] = {1,2,3,4};
vector<int> array{1,2,3,4};
```

`(args)...`则是可变参数模板的语法，用来展开args。展开后如下：

```
    int arr[] = {(print_arg(args1),0),(print_arg(args2),0),(print_arg(args3),0),(print_arg(args4),0)};

```



## 总结

这篇文章就先这些，下一篇我们看看 `Args&&` 和 `std::forward`。

参考书籍：

- 深入应用C++11
- Effective Modern C++



毕业后我做了5年Windows平台的C++开发，但工作中几乎没有用到C++11。2014年我曾经在一个项目中愉快的、自作主张的使用了C++11的各种语法，但最后客户有大量的Windows XP SP2 及以下版本的系统，只能加班把代码改回C++03支持的语法。（当时使用 Visual Studio 2013 如果要用C++11，最低支持到 Windows XP SP3。）

但现在已经9102年了，C++14已经作为Xcode创建新工程时的默认选项，C++17也已经被Xcode和Visual Studio几乎完美支持，愉快的使用现代C++已经不再是问题。（Emmmm...除非客户还要支持Windows XP SP2……）

还有，Practical Modern C++ 以后就简称 PMCPP啦。

---

有趣，欢迎关注。

![](/media/bukuzao.jpg)



