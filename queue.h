template<typename T> class queue{
private:
	T *v;
	int top,low;
public:
	void enqueue(T x){
		top++;
		v[top]=x;
		v=(T *)realloc(v,(top+2)*sizeof(T));
	}
	T dequeue(){
		return v[low++];
	}
	T front(){
		return v[top];
	}
	int isEmpty(){
		if(low>top)
			return 1;
		return 0;
	}
	queue(){
		v=(T *)malloc(1*sizeof(T));
		top=-1;
		low=0;
	}
	~queue(){
		free(v);
	}
};
