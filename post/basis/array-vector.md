# 数组

C++ 中有三种数组：`C风格的数组`、`std::array`、`std::vector`。

## C风格的数组

当然这个风格不够*现代*，且不够*安全*，仅示例如下：

```
int carr[10]; // 内容随机
print_array(carr);
    
int carr1[10] = {1}; // 第一个元素为1，其余0
print_array(carr1);

int carr2[10] = {1,2}; // 第一个元素为1，第二个2，其余0
print_array(carr2);
```

可能的输出如下：

```
-272632512 32766 0 1 1 14 0 0 0 0 
1 0 0 0 0 0 0 0 0 0 
1 2 0 0 0 0 0 0 0 0 
```


## std::array

`std::array`是C++11引入的一个模板类，封装了C风格的数组，因此是`固定大小的数组容器`。所谓固定大小，是指`编译时就确定了大小`。通常情况下是占用`栈（stack）`上的空间，且性能更好（相比std::vector）。

需要头文件：

```
#include <array>
```

`std::array<int,10> stdarr;` 表示`int`类型的`大小为10`的数组。

示例如下：

```
std::array<int,10> stdarr; // 内容随机
print_array(stdarr);

std::array<int,10> stdarr1 = {1}; // 第一个元素为1，其余0
print_array(stdarr1);
    
std::array<int,10> stdarr2 = {1,2}; // 第一个元素为1，第二个2，其余0
print_array(stdarr2);
```

`std::array`相比C风格数组的另一个优势是：可以使用STL的各种算法函数。

例如[这里](https://en.cppreference.com/w/cpp/container/array)的示例：

```
std::array<int, 3> stdarr3 = {1, 2, 3};
std::sort(stdarr3.begin(), stdarr3.end());
print_array(stdarr3,3);
```

`std::array`有如下方法，[更多方法见这里](https://en.cppreference.com/w/cpp/container/array) ：

![](/media/15562029049754.jpg)



## std::vector

`std::vector`是一个老牌的C++模板类，提供了`动态大小的数组`。std::vector的数据是存储在`堆（heap）`上的，因此性能上不如`std::array`（堆的访问速度小于栈的访问速度）。

首先包含头文件：

```
#include <vector>
```

示例如下：

```
// Create a vector containing integers
std::vector<int> v = {7, 5, 16, 8};
    
// Add two more integers to vector
v.push_back(25);
v.push_back(13);
print_array(v,v.size());
```

更多方法见[这里](https://en.cppreference.com/w/cpp/container/vector)：

![](/media/15562034434705.jpg)


由于std::vector是动态大小的数组，那必然存在已有空间不够的情况，那空间大小是如何再次分配的呢？
通过跟进push_back的代码，可看到如下：

![](/media/15562037092219.jpg)

可知当最终空间不足时，会不断的把`容量*2`。`容量`是`capacity`，而不是`size`。`size`是已经占用数据的大小，`capacity`是vector为了实现动态数组，提前申请出的空间。因此vector当发生容量乘以2时，会带来数据的复制。从老的地址空间复制数据到扩大后的地址空间。这也是可能带来性能问题的地方。因此有时可以提前一次申请足够的空间，例如：`std::vector<int> v(100)`。



## print_array

上文代码中的辅助方法：

```
template <typename ARR>
void print_array(ARR arr){
    for(int i=0;i<10;i++)
        printf("%d ",arr[i]);
    printf("\n");
}

template <typename ARR>
void print_array(ARR arr,int size){
    for(int i=0;i<size;i++)
        printf("%d ",arr[i]);
    printf("\n");
}
```



## 代码

[Code](https://github.com/everettjf/pmcpp/blob/master/pmcpp-code/pmcpp-code/basis/array_vector.cpp)


## 参考

- [std::vector versus std::array in C++](https://stackoverflow.com/questions/4424579/stdvector-versus-stdarray-in-c)


---

欢迎关注订阅号 :)

![](/media/bukuzao.jpg)

