
单链表 / 双链表

单链表（forward_list ）和 双链表（list）都支持常数时间再任意位置插入和移除，但不支持随机访问（使用0、1、2这种索引访问）。forward_list 的迭代器（iterator）是`单向迭代器`，更节省一点点内存。list 的迭代器是`双向迭代器`，简单说就是iterator支持 `++` 和 `--` 。除了迭代器，使用方法上几乎一样。


# forward_list

详细文档[见这里](https://zh.cppreference.com/w/cpp/container/forward_list)

使用示例：

```
std::forward_list<std::string> words {"one","two","three"};
print_list(words); // one,two,three,
    
auto before_begin = words.before_begin();
words.insert_after(before_begin, "zero");
print_list(words); // zero,one,two,three,
    
std::cout << words.front() << std::endl; // zero
    
words.push_front("-1");
print_list(words); // -1,zero,one,two,three,

words.pop_front();
print_list(words); // zero,one,two,three,
    
words.reverse();
print_list(words); // three,two,one,zero,
    
words.sort();
print_list(words); // one,three,two,zero,
    
words.push_front("one");
print_list(words); // one,one,three,two,zero,

words.unique();
print_list(words); // one,three,two,zero,
    
std::forward_list<int> list1 = { 5,9,0,1,3 };
std::forward_list<int> list2 = { 8,7,2,6,4 };
    
list1.sort();
list2.sort();
std::cout << "list1:  "; print_list(list1); // list1:  0,1,3,5,9,
std::cout << "list2:  "; print_list(list2); // list2:  2,4,6,7,8,
list1.merge(list2);
std::cout << "merged: "; print_list(list1); // merged: 0,1,2,3,4,5,6,7,8,9,

```


# list

[详细文档见这里](https://zh.cppreference.com/w/cpp/container/list)


```
std::list<int> l = { 7, 5, 16, 8 };
l.push_front(25);
print_list(l); // 25,7,5,16,8,

l.push_back(13);
print_list(l); // 25,7,5,16,8,13,

l.pop_front();
print_list(l); // 7,5,16,8,13,

l.pop_back();
print_list(l); // 7,5,16,8,

auto it = std::find(l.begin(), l.end(), 16);
if (it != l.end()) {
    l.insert(it, 42); // 找到16，在前面插入42
}
print_list(l); // 7,5,42,16,8,
```


# 总结


两个list都很简单哈。








