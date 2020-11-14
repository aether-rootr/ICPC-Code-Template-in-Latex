string s;  //生成一个空字符串s
string s(str) //拷贝构造函数 生成str的复制品
string s(str,stridx) //将字符串str内“始于位置stridx”的部分当作字符串的初值
string s(str,stridx,strlen) //将字符串str内“始于stridx且长度顶多strlen”的部分作为字符串的初值
string s(cstr) //将C字符串作为s的初值
string s(chars,chars_len) //将C字符串前chars_len个字符作为字符串s的初值。
string s(num,c) //生成一个字符串，包含num个c字符
string s(beg,end) //以区间beg;end(不包含end)内的字符作为字符串s的初值
s.~string() //销毁所有字符，释放内存

=,assign()   //赋以新值
swap()  //交换两个字符串的内容
+=,append(),push_back() //在尾部添加字符
insert() //插入字符
erase() //删除字符
clear() //删除全部字符 
replace() //替换字符
+ //串联字符串
==,!=,<,<=,>,>=,compare()  //比较字符串
size(),length()  //返回字符数量
max_size() //返回字符的可能最大个数
empty()  //判断字符串是否为空
capacity() //返回重新分配之前的字符容量
reserve() //保留一定量内存以容纳一定数量的字符
[ ], at() //存取单一字符
>>,getline() //从stream读取某值
<<  //将谋值写入stream
copy() //将某值赋值为一个C_string
c_str() //将内容以C_string返回
substr() //返回某个子字符串
begin() end() //提供类似STL的迭代器支持
rbegin() rend() //逆向迭代器
get_allocator() //返回配置器

