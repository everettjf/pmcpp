# deque - double ended queue

deque，双端队列，是C++中一个古老的容器类。他能提供O(1)的随机访问（使用索引访问），以及O(1)的两端（开头和结尾）的插入和删除。

## 原理

相比vector，deque内部的元素存储不是顺序的。通常情况下，deque内部使用多个固定大小的数组来实现。也正是由于这个实现原理，当添加的数据大于deque当前的空间大小时，deque可以继续加入更多的数组，而不需要复制所有数据到新的空间。

如下图：

![](/media/15577970735170.jpg)

当我们使用索引来访问时，deque内部会计算定位到对应哪个数组的内容。

详细可参考[这里](https://stackoverflow.com/questions/6292332/what-really-is-a-deque-in-stl)

## 使用

`push_front`在队列前加入数据，`push_back`在队列后加入数据。

使用索引访问数据 `d[0]`，也可以使用索引修改数据`d[0] = 100;`

当数据不使用时，`d.clear();`，注意，此时deque内部的空间仍然没有释放，如果要释放需要再次调用`d.shrink_to_fit();`


参考代码：


```
#include <deque>
#include <iostream>

template <typename T>
void print_deque(T&& t) {
    for(auto &n : t){
        std::cout << n<< ",";
    }
    std::cout << std::endl;
}

void deque_test(){
    std::deque<int> d = {1,20,3,40,5,60};
    print_deque(d); // 1,20,3,40,5,60,
    
    std::cout << d[0] << "," << d[1] << std::endl; // 1,20
    
    d.push_front(0);
    d.push_back(7);
    
    std::cout << d[0] << "," << d[1] << std::endl; // 0,1
    
    print_deque(d); // 0,1,20,3,40,5,60,7,
    
    d[0] = 100;
    
    print_deque(d); // 100,1,20,3,40,5,60,7,
    
    d.clear();
    d.shrink_to_fit();
}

```

所有方法见[这里](https://en.cppreference.com/w/cpp/container/deque)


## 总结

deque适合添加“前后”都可能加入数据，同时还希望”使用索引访问“的情况。

---

有趣，欢迎关注。

![](/media/bukuzao.jpg)

