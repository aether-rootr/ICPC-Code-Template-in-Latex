//单调递增栈
void push(int x){
	while(!s.empty()&&s.top()>x) stk.pop();
	s.push(A[i]);
}
//单调递减栈
void push(int x){
	while(!s.empty()&&s.top()<=x) stk.pop();
	s.push(A[i]);
}