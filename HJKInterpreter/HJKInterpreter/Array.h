//Array.h
#ifndef _ARRAY_H
#define _ARRAY_H
typedef signed long int Long;//���� �ڷ��� ����
template <typename T>

class Array{
public:
	Array(Long capacity = 0);//����Ʈ ������
	Array(const Array& source);//���������
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
Array<T>::Array(const Array& source){//���������
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
	this->front = new T[capacity];//�Ҵ緮��ŭ ������ �����
	this->capacity = capacity;//�Ҵ緮�� �Է¹��� �Ҵ緮���� ���Ѵ�
	this->length = 0;// ��뷮�� 0���� �ʱ�ȭ�Ѵ�
}

template <typename T>
Long Array<T>::Store(Long index, T object){
	this->front[index] = object;//�迭�� ��ġ�� ��ü�� �Է��Ѵ�
	(this->length)++;//��뷮�� �ø���
	return index;//��ġ�� ����Ѵ�
}

template <typename T>
Long Array<T>::Insert(Long index, T object){
	T(*temp);
	Long i = 0;

	temp = new T[this->capacity + 1];//�Ҵ緮���� ū �迭�� �����
	while (i < index){//i�� ��ġ���� �������� �ݺ��Ѵ�
		temp[i] = this->front[i];//front��i��° ��ü�� temp��i��°�� �����Ѵ�
		i++;//i�� ����
	}
	i = index;//i�� index�� ���Ѵ�
	while (i < this->length){//i�� ��뷮���� �������� �ݺ��Ѵ�
		temp[i + 1] = this->front[i];////front��i��° ��ü�� temp i+1��°�� �����Ѵ�
		i++;//i�� ����
	}

	if (this->front != 0){//front�� �����
		delete[] this->front;

	}

	this->front = temp;//front�� ��ġ�� temp�� ���Ѵ�
	(this->capacity)++;//�Ҵ緮�� �ø���
	this->front[index] = object;//��ü�� front�� i��°�� �Է��Ѵ�
	(this->length)++;//��뷮�� �ø���

	return index;//��ġ�� ��ȯ�Ѵ�
}

template <typename T>
Long Array<T>::AppendFromFront(T object){
	T(*temp);
	Long i = 0, j = 1;
	Long index = 0;
	temp = new T[this->capacity + 1];//temp�� �Ҵ緮���� 1ũ�� �����Ѵ�
	while (i < this->length){//i�� ��뷮���� �������� �ݺ��Ѵ�
		temp[j] = this->front[i];//temp j��°�� front i��° ��ü�� �����Ѵ�
		j++;//i�� ����
		i ++ ;//j�� ����
	}
	if (this->front != 0){//front�� �����
		delete[] this->front;
	}

	this->front = temp;//front�� temp�� �Ѵ�
	(this->capacity)++;//�Ҵ緮�� �ø���
	this->front[index] = object;//index��°�� ��ü�� �Է��Ѵ�
	(this->length)++;//��뷮�� �ø���

	return index;//��ġ�� ��ȯ�Ѵ�
}

template <typename T>
Long Array<T>::AppendFromRear(T object){
	T(*temp);
	Long i = 0;
	temp = new T[this->capacity + 1];//temp�� �Ҵ緮���� 1 ũ�� �����Ѵ�
	while (i < this->length){//i�� ��뷮���� �������� �ݺ��Ѵ�
		temp[i] = this->front[i];//front i�� ��ü�� temp i�� �ű��
		i++;//i�� ����
	}
	if (this->front != 0){//front�� �����
		delete[] this->front;
	}
	this->front = temp;//front�� temp���Ѵ�
	(this->capacity)++;//�Ҵ��� �ø���
	Long index = this->capacity - 1;
	this->front[index] = object;//��ü�� front�� �������� �Է��Ѵ�
	(this->length)++;//��뷮�� �ø���
	return index;//��ġ�� ��ȯ�Ѵ�
}

template <typename T>
Long Array<T>::Delete(Long index){
	T(*temp)=0;
	Long i = 0, j = 0;
	if (this->capacity > 1){//�Ҵ緮�� 1���� ũ�ٸ�
		temp = new T[this->capacity - 1];//temp�� �Ҵ緮���� �۰� �����
	}
	while (j < index){//j�� ��ġ���� �������� �ݺ��Ѵ�
		temp[i] = this->front[j];//front j��°�� ���� temp i��°�� ������ �����Ѵ�
		i++;//i�� ����
		j++;//j�� ����
	}
	j++;//j�� ����
	while (j < this->length){//j�� ��뷮���� �������� �ݺ��Ѵ�
		temp[i] = this->front[j];//front j��°�� ���� temp i��°�� ������ �����Ѵ�
		i++;//i�� ����
		j++;//j�� ����
	}
	if (this->front != 0){//front�� �����
		delete[] this->front;
		this->front = 0;
	}
	if (this->capacity > 1){//��뷮�� 1���� ũ�ٸ�
		this->front = temp;//front�� ��ġ�� temp�� ���Ѵ�
	}
	(this->length)--;//��뷮�� ���δ�
	(this->capacity)--;//�Ҵ緮�� ���δ�

	index = -1;

	return index;//-1�� ��ȯ�Ѵ�
}

template <typename T>
Long Array<T>::DeleteFromFront(){
	T(*temp)=0;
	Long index = -1;
	Long i = 0, j = 1;
	if (this->capacity > 1){//�Ҵ緮�� 1���� ũ�ٸ�
		temp = new T[this->capacity - 1];//�Ҵ緮���� 1 �۰� temp�� �����
	}
	while (j < this->length){//j�� ��뷮���� �������� �ݺ��Ѵ�
		temp[i] = this->front[j];//front j��°���� temp i��°�� �����Ѵ�
		i++;//i�� ����
		j++;//j�� ����
	}
	if (this->front != 0){//front�� �����
		delete[] this->front;
		this->front = 0;
	}

	if (this->capacity > 1){//�Ҵ緮�� 1���� ũ�ٸ� front�� temp�� ��ġ�� ���Ѵ�
		this->front = temp;
	}
	(this->length)--;//��뷮�� ���δ�
	(this->capacity)--;//�Ҵ緮�� ���δ�

	return index;//�� ��ġ�� ����Ѵ�(-1)
}

template <typename T>
Long Array<T>::DeleteFromRear(){
	T(*temp)=0;
	Long index = -1;
	Long i = 0;
	if (this->capacity > 1){//�Ҵ緮�� 1���� ũ�ٸ�
		temp = new T[this->capacity - 1];//temp�� �Ҵ緮���� 1 �۰� �����Ѵ�
	}
	while (i < this->capacity - 1){//i�� �Ҵ緮-1���� �������� �ݺ��Ѵ�
		temp[i] = this->front[i];//front i��°�� ��ü�� temp i��°�� �����Ѵ�
		i++;//i�� ����
	}
	if (this->front != 0){//front�� �����
		delete[] this->front;
		this->front = 0;
	}
	if (this->capacity > 1){//�Ҵ緮�� 1���� ũ�ٸ�
		this->front = temp;//front�� temp�� ��ġ�� ���Ѵ�
	}
	(this->length)--;//��뷮�� ���δ�
	(this->capacity)--;//�Ҵ緮�� ���δ�

	return index;//�� ��ġ(-1)�� ��ȯ�Ѵ�
}

template <typename T>
Long Array<T>::Modify(Long index, T object){
	this->front[index] = object;//front index��°�� ��ü�� object�� �ٲ۴�
	return index;//index�� ����Ѵ�
}

template <typename T>
void Array<T>::Clear(){
	if (this->front != 0){//front�� �����
		delete[] this->front;
		this->front = 0;
	}

	this->length = 0;//��뷮�� �����
	this->capacity = 0;//�Ҵ緮�� �����
}

template <typename T>
Long Array<T>::LinearSearchUnique(void *key, int(*compare)(void*, void*)){
	Long index = -1;
	Long i = 0;
	while (i < this->length&&compare(this->front+i, key) != 0){//��뷮���� ��������, ã������ ���� �������� �ݺ��Ѵ�
		i++;//i�� ����
	}
	if (i < this->length){//��뷮���� �۴ٸ�
		index = i;//��ġ�� i�� ���Ѵ�
	}

	return index;//��ġ�� ����Ѵ�
}

template <typename T>
void Array<T>::LinearSearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void*, void*)){
	Long i = 0, j = 0;
	*count = 0;//������ �����
	*indexes = new Long[this->length];//��ġ���� ��뷮��ŭ �����
	while (i < this->length){//i�� ��뷮���� �������� �ݺ��Ѵ�
		if (compare(this->front + i, key) == 0){//Ű�� front i��° ���� ���ٸ�
			(*indexes)[j] = i;//��ġ�� j��°�� i�� �����Ѵ�
			(*count)++;//������ ����
			j++;//j�� ����
		}
		i++;//i�� ����
	}
}

template <typename T>
Long Array<T>::BinarySearchUnique(void *key, int(*compare)(void*, void*)){
	Long front = 0;//���� ��ġ�� ���Ѵ�
	Long mid;
	Long rear;
	Long index = -1;
	rear = this->length - 1;//����ġ�� ���Ѵ�
	mid = (front + rear) / 2;//�߰���ġ�� ���Ѵ�
	while (front <= rear&&compare(this->front + mid, key) != 0){//������ġ�� ����ġ���� �۰ų� ��������, �߰���ġ�� ã�°��� �ٸ����� �ݺ��Ѵ�
		if (compare(this->front + mid, key) > 0){//front�� �߰���ġ���� ã�°����� ũ�ٸ�
			rear = mid - 1;//����ġ�� �߰���ġ-1�� ���Ѵ�
		}
		else{//ũ�ٸ�
			front = mid + 1;//������ġ�� �߰���ġ+1�� ���Ѵ�
		}
		mid = (front + rear) / 2;//�߰���ġ�� �ٽ� ���Ѵ�
	}
	if (front <= rear){//������ġ�� ����ġ���� �۰ų� ���ٸ�
		index = mid;//ã�� ��ġ�� �߰���ġ�� ���Ѵ�
	}

	return index;//ã�� ��ġ�� ����Ѵ�
}

template <typename T>
void Array<T>::BinarySearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void*, void*)){
	Long front = 0;
	Long mid;
	Long rear;
	Long i;
	Long j = 0;
	*count = 0;
	*indexes = new Long[this->length];//��뷮��ŭ ��ġ���� �����
	rear = this->length - 1;//�� ��ġ�� ���Ѵ�
	mid = (front + rear) / 2;//�߰� ��ġ�� ���Ѵ�
	while (front <= rear&&compare(this->front + mid, key) != 0){//ó����ġ�� ����ġ���� �۰ų� ��������, front mid�� ���� ã�°��� �ٸ����� �ݺ��Ѵ�
		if (compare(this->front + mid, key) > 0){//front mid�� ���� ã�°����� ũ�ٸ�
			rear = mid - 1;//����ġ�� �߰���ġ-1�� ���Ѵ�
		}
		else{//�۴ٸ�
			front = mid + 1;//������ġ�� �߰���ġ +1�� ���Ѵ�
		}
		mid = (front + rear) / 2;//�߰���ġ�� ���Ѵ�
	}
	if (front <= rear){//ó����ġ�� ����ġ���� �۰ų� �������� �ݺ��Ѵ�
		i = mid - 1;//i�� �߰���ġ-1�� ���Ѵ�
		while (i >= 0 && compare(this->front + i, key) == 0){//i�� 0���� ũ�ų� ��������, front�� i�� ���� ã�°��� �������� �ݺ��Ѵ�
			(*indexes)[j] = i;//��ġ�鿡 i�� �Է��Ѵ�
			(*count++);//������ ����
			j++;//j�� ����
			i++;//i�� ����
		}
	}
}

template <typename T>
void Array<T>::SelectionSort(int(*compare)(void*, void*)){
	T temp;
	Long i = 0, j;

	while (i < this->length - 1){//i�� ��뷮-1���� �������� �ݺ��Ѵ�
		j = i + 1;//j�� i+1�� ���Ѵ�
		while (j < this->length){//j�� ��뷮���� �������� �ݺ��Ѵ�
			if (compare(this->front + i, this->front+j) > 0){//front i��°�� ���� front j��°�� ������ ũ�ٸ�
				temp = this->front[i];//���� �ٲ۴�
				this->front[i] = this->front[j];
				this->front[j] = temp;
			}
			j++;//j�� ����
		}
		i++;//i�� ����
	}
}

template <typename T>
void Array<T>::BubbleSort(int(*compare)(void*, void*)){
	T temp;
	Long count = 1;
	Long i = 0, j;
	
	while (i < this->length - 1 && count>0){//i�� ��뷮-1���� ��������, ī��Ʈ�� 0���� Ŭ���� �ݺ��Ѵ�
		count = 0;//ī��Ʈ�� 0���� ���Ѵ�
		j = 0;//j�� 0���� ���Ѵ�
		while (j < this->length - i - 1){//j�� ��뷮-i-1���� �������� �ݺ��Ѵ�
			if (compare(this->front + j, this->front + (j + 1))>0){//front j��°�� front j+1��°���� ũ�ٸ�
				temp = this->front[j];//j�� j+1��° ��ü�� �ٲ۴�
				this->front[j] = this->front[j + 1];
				this->front[j + 1] = temp;
				count++;//ī��Ʈ�� ����
			}
			j++;//j�� ����
		}
		i++;//i�� ����
	}
}

template <typename T>
void Array<T>::InsertionSort(int(*compare)(void*, void*)){
	T temp;
	Long i = 1, j;

	while (i < this->length){//i�� ��뷮���� �������� �ݺ��Ѵ�
		temp = this->front[i];//front i��°�� temp�� �����Ѵ�
		j = i - 1;//j�� i-1�� ���Ѵ�
		while (j >= 0 && compare(this->front + j, &temp) > 0){//j�� 0���� ũ�ų�����, front j��°�� temp���� Ŭ���� �ݺ��Ѵ�
			this->front[j + 1] = this->front[j];//front j�� front j+1������ �����Ѵ�
			j--;//j�� ����
		}
		this->front[j + 1] = temp;//temp�� front j+1��°�� �����Ѵ�
		i++;//i�� ����
	}
}

template <typename T>
void Array<T>::MergeSort(const Array &one, const Array &other, int(*compare)(void*, void*)){
	T(*temp);
	Long i = 0, j = 0, k = 0;
	temp = new T[one.length + other . length];//temp�� one�� other�� ��뷮�� ���� ������ �Ҵ��Ѵ�
	while (i < one.length && j < other.length){//i�� one�� ��뷮���� �۰ų� other�� j�� ��뷮���� �������� �ݺ��Ѵ�
		if (compare(one.front + i, other.front + j)<0){//one i��°�� other j��°���� �������
			temp[k] = one.front[i];//temp�� one�� �����Ѵ�
			i++;//i������
		}
		else{//ũ�ų� �������
			temp[k] = other.front[j];//temp�� other�� �����Ѵ�
			j++;//j�� ����
		}
		k++;//k�� ����
	}

	while (i < one.length){//i�� one�� ��뷮���� �������� �ݺ��Ѵ�
		temp[k] = one.front[i];//temp�� one�� �����Ѵ�
		k++;//k�� ����
		i++;//i�� ����
	}
	while (j < other.length){//j�� other�� ��뷮���� �������� �ݺ��Ѵ�
		temp[k] = other.front[j];//temp�� other�� �����Ѵ�
		k++;//k�� ����
		j++;//j�� ����
	}

	if (this->front != 0){//front�� �����
		delete[] this->front;
	}

	this->front = temp;//front�� temp�� ���Ѵ�
	this->capacity = one.length + other.length;//�Ҵ緮�� one�� other�� ��뷮�� ���Ѱ����� ���Ѵ�
	this->length = one.length + other.length;//��뷮�� one�� other�� ��뷮�� ���Ѱ����� ���Ѵ�
}
template <typename T>
Array<T>::~Array(){
	if (this->front != 0){
		delete[] this->front;
	}
}

#endif //_ARRAY_H