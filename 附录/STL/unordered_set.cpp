unordered_set<string> c//初始化容器
unordered_set<string> c//{ "aaa", "bbb", "ccc" }：初始化容器，并将"aaa", "bbb", "ccc"加入到容器中
unordered_set<string> c//{ 16 }：初始化容器，并设置16个桶

c.insert("dddd")//向容器添加元素”dddd"
a.insert({ "aaa","bbbb","cccc" })//向容器添加元素"aaa","bbbb","cccc"
a.insert(b.begin(), b.end())//b是一个存储着和a相同类型元素的向量，可将b中所有元素添加到a中

a.find("eeee")//查找元素"eeee"，返回结果为a.end()则表明没有找到，否则返回所对应元素
a.count("eeee")//查找元素"eeee"在a中有几个（由于unordered_set中没有相同的元素，所以结果通常为0或1）

a.bucket_count()//返回数据结构中桶的数量
a.bucket_size(i)//返回桶i中的大小
a.bucket("eeee")//返回元素"eeee"在哪个桶里

a.hash_function()("aaa")//返回"aaa"所对应的hash值
a.key_eq()("aaa","aaaa")//当元素相同时返回true，否则返回false

a.clear()//清除a中所有元素
a.erase("aaa")//清除元素"aaa"

a.size()//返回a中总的元素个数
a.max_size()//返回a中最大容纳元素
a.empty()//判断a中是否为空