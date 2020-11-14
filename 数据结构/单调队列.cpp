deque<int> q;

void push(int x){
	if(q.empty()) q.push_back(x);
	else if(q.back()>x){
  		while((!q.empty())&&q.back()>x) q.pop_back();
  		q.push_back(x);
	}else q.push_back(x);
}