# 关联容器 / 无序关联容器

关联容器有 set map multiset multimap，无序关联容器有 unordered_set unordered_map unordered_multiset unordered_multimap。关联容器的内部实现是`红黑树`，无序关联容器的内部实现是`桶`。

关联容器在创建的过程中，就自动排序了。无序关联容器的存储更快，可用于更快的去重。


# 关联容器

## set

集合可用于数据`去重`，求`交集`、`并集`。也可以用于单一数据的排序。

```
// https://zh.cppreference.com/w/cpp/container/set
std::set<int> s;
s.insert(1);
s.insert(1);
s.insert(2);
print_list(s);
    
if (s.find(2) != s.end()) {
    std::cout << "found 2" << std::endl;
}
```

## map

map，是C++的哈希容器（可能这么叫吧），可用于数据`去重`。也可以用来对数据排序。


```
// https://zh.cppreference.com/w/cpp/container/map
std::map<std::string,int> m;
m["a"] = 1;
m["b"] = 2;
m.insert(std::make_pair("c", 3));
print_map(m);
    
if (m.find("c") != m.end()) {
    std::cout << "found c" << std::endl;
}
```

## multiset multimap

multiset 允许多个key相同。用法查看 https://zh.cppreference.com/w/cpp/container/multiset

multimap 允许一个key对应多个value。用法查看 https://zh.cppreference.com/w/cpp/container/multimap

# 无序关联容器

无序关联容器的内部实现是`桶`，元素按照哈希值决定放入哪个桶。因此不能用于排序。

详细见各自文档啦

unordered_set
https://zh.cppreference.com/w/cpp/container/unordered_set

unordered_map
https://zh.cppreference.com/w/cpp/container/unordered_map


# 总结


感觉这些用法也没必要都举例，大同小异，看一遍文档就知道。快速pass吧。

下一步我试试“结合某个问题的解决”来讲解。

