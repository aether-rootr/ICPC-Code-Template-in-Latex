deque<int> a; // 定义一个int类型的双端队列a
deque<int> a(10); // 定义一个int类型的双端队列a，并设置初始大小为10
deque<int> a(10, 1); // 定义一个int类型的双端队列a，并设置初始大小为10且初始值都为1
deque<int> b(a); // 定义并用双端队列a初始化双端队列b
deque<int> b(a.begin(), a.begin()+3); // 将双端队列a中从第0个到第2个(共3个)作为双端队列b的初始值

int n[] = { 1, 2, 3, 4, 5 };
// 将数组n的前5个元素作为双端队列a的初值
// 说明：当然不包括arr[4]元素，末尾指针都是指结束元素的下一个元素，
// 这个主要是为了和deque.end()指针统一。
deque<int> a(n, n + 5); 
deque<int> a(&n[1], &n[4]); // 将n[1]、n[2]、n[3]作为双端队列a的初值

deq.size();//容器大小
deq.max_size();//容器最大容量
deq.resize(x);//更改容器大小为x
deq.empty();//容器判空
deq.shrink_to_fit();//减少容器大小到满足元素所占存储空间的大小

// 遍历显示
for (it = deq.begin(); it != deq.end(); it++)
	cout << *it << " ";
cout << endl;

// 头部增加元素
deq.push_front(4);
// 末尾添加元素
deq.push_back(5);
// 任意位置插入一个元素
deque<int>::iterator it = deq.begin();
deq.insert(it, 2);
// 任意位置插入n个相同元素
it = deq.begin(); // 必须要有这句
deq.insert(it, 3, 9);
// 插入另一个向量的[forst,last]间的数据
deque<int> deq2(5,8);
it = deq.begin(); // 必须要有这句
deq.insert(it, deq2.end() - 1, deq2.end());

// 头部删除元素
deq.pop_front();
// 末尾删除元素
deq.pop_back();
// 任意位置删除一个元素
deque<int>::iterator it = deq.begin();
deq.erase(it);
// 删除[first,last]之间的元素
deq.erase(deq.begin(), deq.begin()+1);
// 清空所有元素
deq.clear();

// 下标访问
cout << deq[0] << endl;
// at方法访问
cout << deq.at(0) << endl;
// 访问第一个元素
cout << deq.front() << endl;
// 访问最后一个元素
cout << deq.back() << endl;

// 多个元素赋值
deque<int> deq;
deq.assign(3, 1);
deque<int> deq2;
deq2.assign(3, 2);

// 交换两个容器的元素
deq.swap(deq2);

deq.begin();//开始迭代器指针
deq.end(); //末尾迭代器指针,指向最后一个元素的下一个位置
deq.cbegin();//指向常量的开始迭代器指针,意思就是不能通过这个指针来修改所指的内容，但还是可以通过其他方式修改的，而且指针也是可以移动的。
deq.cend();//指向常量的末尾迭代器指针
deq.rbegin();//反向迭代器指针，指向最后一个元素
deq.rend();//反向迭代器指针，指向第一个元素的前一个元素