template<typename T> class stack{
private:
	T *v;
	int nr;
public:
	void push(T x){
		nr++;
		v[nr]=x;
		v=(T *)realloc(v,(nr+2)*sizeof(T));
	}
	T pop(){
		return v[nr--];
	}
	T peek(){
		return v[nr];
	}
	int isEmpty(){
		if(nr==-1)
			return 1;
		return 0;
	}
	stack(){
		v=(T *)malloc(1*sizeof(T));
		nr=-1;
	}
	~stack(){
		free(v);
	}
};
