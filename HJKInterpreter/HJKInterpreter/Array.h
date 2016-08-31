//Array.h
#ifndef _ARRAY_H
#define _ARRAY_H
typedef signed long int Long;//정수 자료형 설계
template <typename T>

class Array{
public:
	Array(Long capacity = 0);//디폴트 생성자
	Array(const Array& source);//복사생성자
	~Array();

	Long Store(Long index, T object);
	Long Insert(Long index, T object);
	Long AppendFromFront(T object);
	Long AppendFromRear(T object);
	Long Delete(Long index);
	Long DeleteFromFront();
	Long DeleteFromRear();
	Long Modify(Long index, T object);
	void Clear();
	Long LinearSearchUnique(void *key, int(*compare)(void*, void*));
	void LinearSearchDuplicate(void *key,Long *(*indexes),Long *count, int(*compare)(void*, void*));
	Long BinarySearchUnique(void *key, int(*compare)(void*, void*));
	void BinarySearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void*, void*));
	void SelectionSort(int(*compare)(void*, void*));
	void BubbleSort(int(*compare)(void*, void*));
	void InsertionSort(int(*compare)(void*, void*));
	void MergeSort(const Array &one, const Array &other, int(*compare)(void*, void*));
	
	Array& operator = (const Array& source);
	T& GetAt(Long index);
	T& operator[](Long index);
	T& operator+(Long index);
	Long GetCapacity()const;
	Long GetLength()const;

private:
	T(*front);
	Long capacity;
	Long length;
};

template <typename T>
Array<T>& Array<T>::operator=(const Array& source){
	Long i = 0;
	if (this->front != 0){
		delete[] this->front;
	}
	this->front = new T[source.capacity];
	while (i < source.length){
		this->front[i] = source.front[i];
		i++;
	}
	this->length = source.length;
	this->capacity = source.capacity;

	return *this;
}
template <typename T>
T& Array<T>::GetAt(Long index){
	return this->front[index];
}
template <typename T>
T& Array<T>::operator[](Long index){
	return this->front[index];
}
template <typename T>
T& Array<T>::operator+(Long index){
	return this->front + index;
}
template <typename T>
inline Long Array<T>::GetCapacity()const{
	return this->capacity;
}
template <typename T>
inline Long Array<T>::GetLength()const{
	return this->length;
}
template <typename T>
Array<T>::Array(const Array& source){//복사생성자
	Long i = 0;
	this->front = new T[source.capacity];
 	while (i < source.length){
		this->front[i] = source.front[i];
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
}

template <typename T>
  Array<T>::Array(Long capacity){
	this->front = new T[capacity];//할당량만큼 공간을 만든다
	this->capacity = capacity;//할당량을 입력받은 할당량으로 정한다
	this->length = 0;// 사용량을 0으로 초기화한다
}

template <typename T>
Long Array<T>::Store(Long index, T object){
	this->front[index] = object;//배열의 위치에 객체를 입력한다
	(this->length)++;//사용량을 늘린다
	return index;//위치를 출력한다
}

template <typename T>
Long Array<T>::Insert(Long index, T object){
	T(*temp);
	Long i = 0;

	temp = new T[this->capacity + 1];//할당량보다 큰 배열을 만든다
	while (i < index){//i가 위치보다 작을동안 반복한다
		temp[i] = this->front[i];//front의i번째 객체를 temp의i번째로 복사한다
		i++;//i를 센다
	}
	i = index;//i를 index로 정한다
	while (i < this->length){//i가 사용량보다 작을동안 반복한다
		temp[i + 1] = this->front[i];////front의i번째 객체를 temp i+1번째로 복사한다
		i++;//i를 센다
	}

	if (this->front != 0){//front를 지운다
		delete[] this->front;

	}

	this->front = temp;//front의 위치를 temp로 정한다
	(this->capacity)++;//할당량을 늘린다
	this->front[index] = object;//객체를 front의 i번째에 입력한다
	(this->length)++;//사용량을 늘린다

	return index;//위치를 반환한다
}

template <typename T>
Long Array<T>::AppendFromFront(T object){
	T(*temp);
	Long i = 0, j = 1;
	Long index = 0;
	temp = new T[this->capacity + 1];//temp를 할당량보다 1크게 생성한다
	while (i < this->length){//i가 사용량보다 작을동안 반복한다
		temp[j] = this->front[i];//temp j번째에 front i번째 객체를 복사한다
		j++;//i를 센다
		i ++ ;//j를 센다
	}
	if (this->front != 0){//front를 지운다
		delete[] this->front;
	}

	this->front = temp;//front를 temp로 한다
	(this->capacity)++;//할당량을 늘린다
	this->front[index] = object;//index번째에 객체를 입력한다
	(this->length)++;//사용량을 늘린다

	return index;//위치를 반환한다
}

template <typename T>
Long Array<T>::AppendFromRear(T object){
	T(*temp);
	Long i = 0;
	temp = new T[this->capacity + 1];//temp를 할당량보다 1 크게 생성한다
	while (i < this->length){//i가 사용량보다 작을동안 반복한다
		temp[i] = this->front[i];//front i의 객체를 temp i에 옮긴다
		i++;//i를 센다
	}
	if (this->front != 0){//front를 지운다
		delete[] this->front;
	}
	this->front = temp;//front를 temp로한다
	(this->capacity)++;//할당을 늘린다
	Long index = this->capacity - 1;
	this->front[index] = object;//객체를 front의 마지막에 입력한다
	(this->length)++;//사용량을 늘린다
	return index;//위치를 반환한다
}

template <typename T>
Long Array<T>::Delete(Long index){
	T(*temp)=0;
	Long i = 0, j = 0;
	if (this->capacity > 1){//할당량이 1보다 크다면
		temp = new T[this->capacity - 1];//temp를 할당량보다 작게 만든다
	}
	while (j < index){//j가 위치보다 작을동안 반복한다
		temp[i] = this->front[j];//front j번째의 값을 temp i번째의 값으로 복사한다
		i++;//i를 센다
		j++;//j를 센다
	}
	j++;//j를 센다
	while (j < this->length){//j가 사용량보다 작을동안 반복한다
		temp[i] = this->front[j];//front j번째의 값을 temp i번째의 값으로 복사한다
		i++;//i를 센다
		j++;//j를 센다
	}
	if (this->front != 0){//front를 지운다
		delete[] this->front;
		this->front = 0;
	}
	if (this->capacity > 1){//사용량이 1보다 크다면
		this->front = temp;//front의 위치를 temp로 정한다
	}
	(this->length)--;//사용량을 줄인다
	(this->capacity)--;//할당량을 줄인다

	index = -1;

	return index;//-1을 반환한다
}

template <typename T>
Long Array<T>::DeleteFromFront(){
	T(*temp)=0;
	Long index = -1;
	Long i = 0, j = 1;
	if (this->capacity > 1){//할당량이 1보다 크다면
		temp = new T[this->capacity - 1];//할당량보다 1 작게 temp를 만든다
	}
	while (j < this->length){//j가 사용량보다 작을동안 반복한다
		temp[i] = this->front[j];//front j번째값을 temp i번째에 복사한다
		i++;//i를 센다
		j++;//j를 센다
	}
	if (this->front != 0){//front를 지운다
		delete[] this->front;
		this->front = 0;
	}

	if (this->capacity > 1){//할당량이 1보다 크다면 front를 temp의 위치로 정한다
		this->front = temp;
	}
	(this->length)--;//사용량을 줄인다
	(this->capacity)--;//할당량을 줄인다

	return index;//빈 위치를 출력한다(-1)
}

template <typename T>
Long Array<T>::DeleteFromRear(){
	T(*temp)=0;
	Long index = -1;
	Long i = 0;
	if (this->capacity > 1){//할당량이 1보다 크다면
		temp = new T[this->capacity - 1];//temp를 할당량보다 1 작게 생성한다
	}
	while (i < this->capacity - 1){//i가 할당량-1보다 작을동안 반복한다
		temp[i] = this->front[i];//front i번째의 객체를 temp i번째로 복사한다
		i++;//i를 센다
	}
	if (this->front != 0){//front를 지운다
		delete[] this->front;
		this->front = 0;
	}
	if (this->capacity > 1){//할당량이 1보다 크다면
		this->front = temp;//front를 temp의 위치로 정한다
	}
	(this->length)--;//사용량을 줄인다
	(this->capacity)--;//할당량을 줄인다

	return index;//빈 위치(-1)를 반환한다
}

template <typename T>
Long Array<T>::Modify(Long index, T object){
	this->front[index] = object;//front index번째의 객체를 object로 바꾼다
	return index;//index를 출력한다
}

template <typename T>
void Array<T>::Clear(){
	if (this->front != 0){//front를 지운다
		delete[] this->front;
		this->front = 0;
	}

	this->length = 0;//사용량을 지운다
	this->capacity = 0;//할당량을 지운다
}

template <typename T>
Long Array<T>::LinearSearchUnique(void *key, int(*compare)(void*, void*)){
	Long index = -1;
	Long i = 0;
	while (i < this->length&&compare(this->front+i, key) != 0){//사용량보다 작을동안, 찾을값이 같지 않을동안 반복한다
		i++;//i를 센다
	}
	if (i < this->length){//사용량보다 작다면
		index = i;//위치를 i로 정한다
	}

	return index;//위치를 출력한다
}

template <typename T>
void Array<T>::LinearSearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void*, void*)){
	Long i = 0, j = 0;
	*count = 0;//개수를 지운다
	*indexes = new Long[this->length];//위치들을 사용량만큼 만든다
	while (i < this->length){//i가 사용량보다 작을동안 반복한다
		if (compare(this->front + i, key) == 0){//키와 front i번째 값이 같다면
			(*indexes)[j] = i;//위치들 j번째에 i를 복사한다
			(*count)++;//개수를 센다
			j++;//j를 센다
		}
		i++;//i를 센다
	}
}

template <typename T>
Long Array<T>::BinarySearchUnique(void *key, int(*compare)(void*, void*)){
	Long front = 0;//시작 위치를 구한다
	Long mid;
	Long rear;
	Long index = -1;
	rear = this->length - 1;//끝위치를 구한다
	mid = (front + rear) / 2;//중간위치를 구한다
	while (front <= rear&&compare(this->front + mid, key) != 0){//시작위치가 끝위치보다 작거나 같을동안, 중간위치가 찾는값과 다를동안 반복한다
		if (compare(this->front + mid, key) > 0){//front의 중간위치값이 찾는값보다 크다면
			rear = mid - 1;//끝위치를 중간위치-1로 정한다
		}
		else{//크다면
			front = mid + 1;//시작위치를 중간위치+1로 정한다
		}
		mid = (front + rear) / 2;//중간위치를 다시 구한다
	}
	if (front <= rear){//시작위치가 끝위치보다 작거나 같다면
		index = mid;//찾은 위치를 중간위치로 정한다
	}

	return index;//찾은 위치를 출력한다
}

template <typename T>
void Array<T>::BinarySearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void*, void*)){
	Long front = 0;
	Long mid;
	Long rear;
	Long i;
	Long j = 0;
	*count = 0;
	*indexes = new Long[this->length];//사용량만큼 위치들을 만든다
	rear = this->length - 1;//끝 위치를 구한다
	mid = (front + rear) / 2;//중간 위치를 구한다
	while (front <= rear&&compare(this->front + mid, key) != 0){//처음위치가 끝위치보다 작거나 같을동안, front mid의 값이 찾는값과 다른동안 반복한다
		if (compare(this->front + mid, key) > 0){//front mid의 값이 찾는값보다 크다면
			rear = mid - 1;//끝위치를 중간위치-1로 정한다
		}
		else{//작다면
			front = mid + 1;//시작위치를 중간위치 +1로 정한다
		}
		mid = (front + rear) / 2;//중간위치를 구한다
	}
	if (front <= rear){//처음위치가 끝위치보다 작거나 같을동안 반복한다
		i = mid - 1;//i를 중간위치-1로 정한다
		while (i >= 0 && compare(this->front + i, key) == 0){//i가 0보다 크거나 같을동안, front의 i의 값이 찾는값과 같을동안 반복한다
			(*indexes)[j] = i;//위치들에 i를 입력한다
			(*count++);//개수를 센다
			j++;//j를 센다
			i++;//i를 센다
		}
	}
}

template <typename T>
void Array<T>::SelectionSort(int(*compare)(void*, void*)){
	T temp;
	Long i = 0, j;

	while (i < this->length - 1){//i가 사용량-1보다 작을동안 반복한다
		j = i + 1;//j를 i+1로 정한다
		while (j < this->length){//j가 사용량보다 작을동안 반복한다
			if (compare(this->front + i, this->front+j) > 0){//front i번째의 값이 front j번째의 값보다 크다면
				temp = this->front[i];//값을 바꾼다
				this->front[i] = this->front[j];
				this->front[j] = temp;
			}
			j++;//j를 센다
		}
		i++;//i를 센다
	}
}

template <typename T>
void Array<T>::BubbleSort(int(*compare)(void*, void*)){
	T temp;
	Long count = 1;
	Long i = 0, j;
	
	while (i < this->length - 1 && count>0){//i가 사용량-1보다 작을동안, 카운트가 0보다 클동안 반복한다
		count = 0;//카운트를 0으로 정한다
		j = 0;//j를 0으로 정한다
		while (j < this->length - i - 1){//j가 사용량-i-1보다 작을동안 반복한다
			if (compare(this->front + j, this->front + (j + 1))>0){//front j번째가 front j+1번째보다 크다면
				temp = this->front[j];//j와 j+1번째 객체를 바꾼다
				this->front[j] = this->front[j + 1];
				this->front[j + 1] = temp;
				count++;//카운트를 센다
			}
			j++;//j를 센다
		}
		i++;//i를 센다
	}
}

template <typename T>
void Array<T>::InsertionSort(int(*compare)(void*, void*)){
	T temp;
	Long i = 1, j;

	while (i < this->length){//i가 사용량보다 작을동안 반복한다
		temp = this->front[i];//front i번째를 temp로 복사한다
		j = i - 1;//j는 i-1로 정한다
		while (j >= 0 && compare(this->front + j, &temp) > 0){//j가 0보다 크거나같고, front j번째가 temp보다 클동안 반복한다
			this->front[j + 1] = this->front[j];//front j를 front j+1번쨰로 복사한다
			j--;//j를 뺀다
		}
		this->front[j + 1] = temp;//temp를 front j+1번째로 복사한다
		i++;//i를 센다
	}
}

template <typename T>
void Array<T>::MergeSort(const Array &one, const Array &other, int(*compare)(void*, void*)){
	T(*temp);
	Long i = 0, j = 0, k = 0;
	temp = new T[one.length + other . length];//temp를 one와 other의 사용량을 더한 값으로 할당한다
	while (i < one.length && j < other.length){//i가 one의 사용량보다 작거나 other이 j의 사용량보다 작을동안 반복한다
		if (compare(one.front + i, other.front + j)<0){//one i번째가 other j번째보다 작을경우
			temp[k] = one.front[i];//temp에 one을 복사한다
			i++;//i를센다
		}
		else{//크거나 같을경우
			temp[k] = other.front[j];//temp에 other를 복사한다
			j++;//j를 센다
		}
		k++;//k를 센다
	}

	while (i < one.length){//i가 one의 사용량보다 작을동안 반복한다
		temp[k] = one.front[i];//temp에 one을 복사한다
		k++;//k를 센다
		i++;//i를 센다
	}
	while (j < other.length){//j가 other의 사용량보다 작을동안 반복한다
		temp[k] = other.front[j];//temp에 other를 복사한다
		k++;//k를 센다
		j++;//j를 센다
	}

	if (this->front != 0){//front를 지운다
		delete[] this->front;
	}

	this->front = temp;//front를 temp로 정한다
	this->capacity = one.length + other.length;//할당량을 one과 other의 사용량을 더한값으로 정한다
	this->length = one.length + other.length;//사용량을 one과 other의 사용량을 더한값으로 정한다
}
template <typename T>
Array<T>::~Array(){
	if (this->front != 0){
		delete[] this->front;
	}
}

#endif //_ARRAY_H