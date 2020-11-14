若有unordered_map <int, int> mp;查找x是否在map中
方法1:  若存在  mp.find(x)!=mp.end()
方法2:  若存在  mp.count(x)!=0

mp.insert(Map::value_type(1,"Raoul"));

unordered_map<key,T>::iterator it;
(*it).first;   //the key value
(*it).second   //the mapped value
for(unordered_map<key,T>::iterator iter=mp.begin();iter!=mp.end();iter++)
      cout<<"key value is"<<iter->first<<" the mapped value is "<< iter->second;


//也可以这样
for(auto& v : mp)
    print v.first and v.second

//其它操作同map