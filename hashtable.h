#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include<vector>
#include<list>
#include<iostream>
#include<algorithm>
#include"hashFunc.h"
using namespace std;


//��ϣ�ڵ�,������ֵ��ָ��
template<class T>
struct hashtable_node{
	hashtable_node *next;
	T val;
	hashtable_node(T val)
		: val(val), next(NULL)
	{}
};

template<class Key, class Value>
class hashtable{
public:
	//��ϣ��ڵ��ֵ����
	typedef pair<Key, Value> T;

	//��ڵ�
	typedef hashtable_node<T> node;
public:
	//���캯��
	hashtable();
	hashtable(hashtable<Key, Value> &ht)
		: buckets(ht.buckets), num_elements(ht.num_elements)
	{}

	//����һ���ؼ���
	void insert(T kv);   

	//���ݼ�ֵɾ���ؼ��� 
	void erase(Key key);

	//�жϹؼ����Ƿ��ڹ�ϣ����
	bool find(Key key);  

	//���ع�ϣ���йؼ��ָ���
	int size(){
		return num_elements;
	}

	void printHashTable();
private:
	//���ݴ����С�ж��Ƿ���Ҫ���·����ϣ��
	void resize(int num_elements);

	//���ݼ�ֵ����Ͱ�ı��
	int buckets_index(Key key, int size){
		return hash(key) % size;
	}

	//���ݽڵ㷵�ؼ�ֵ
	Key get_key(T  node){
		return node.first;
	}
private:
	//ʹ��STL list<T>��Ͱ
	vector<node*> buckets;    

	//��ϣ����Ԫ�ظ���
	size_t num_elements;

	//��ϣ����
	hashFunc<Key> hash;
};

//���캯������ʼ����ϣ��
template<class Key, class Value>
hashtable<Key, Value>::hashtable(){
	const int n_buckets = next_prime(1);
	buckets.reserve(n_buckets);
	buckets.insert(buckets.end(), n_buckets, (node*)0);
	num_elements = 0;
}

//����һ���ؼ���
template<class Key, class Value>
void hashtable<Key, Value>::insert(T kv){
	//�ڲ���֮ǰ������resize�������ж��Ƿ���Ҫ�ؽ���ϣ��
	resize(num_elements + 1);
	//���������λ��
	int pos = buckets_index(kv.first, buckets.size());
	node *head = buckets[pos];	

	//�жϼ�ֵ�Ƿ��Ѿ����ڣ������ڣ���ֱ�ӷ��أ�������
	for (node *cur = head; cur; cur = cur->next){
		if (cur->val.first == kv.first)
			return;
	}

	//����ڵ㣬����
	node *tmp = new node(kv);
	tmp->next = head;
	buckets[pos] = tmp;
	num_elements++; //��¼����
}

//���ݼ�ֵɾ���ؼ��� 
template < class Key, class Value> 
void hashtable<Key, Value>::erase(Key key){
	//�ҳ�Ͱ��λ��
	int pos = buckets_index(key, buckets.size());
	node *head = buckets[pos];
	node *pre = NULL; 
	while (head){
		//���ҵ���Ӧ������ɾ��
		if (head->val.first == key){
			if (pre == NULL){
				buckets[pos] = head->next;
				delete head;
				num_elements--;
				return;
			}
			else{
				pre->next = head->next;
				delete head;
				num_elements--;
				return;
			}
		}

		pre = head;
		head = head->next;
	}
}

//���ݼ�ֵ���ж��Ƿ��ڹ�ϣ����
template<class Key, class Value>
bool hashtable<Key, Value>::find(Key key){
	int pos = buckets_index(key, buckets.size());
	node *head = buckets[pos];

	while (head){
		if (head->val.first == key)
			return true;
		head = head->next;
	}
	return false;
}


template<class Key, class Value>
void hashtable<Key, Value>::resize(int num_elements){
	//��Ԫ�ظ�������Ͱ�ĸ���ʱ�����·����ϣ��
	const int size = buckets.size();
	if (num_elements <= size) return;

	//�ҳ���һ������
	const int next_size = next_prime(num_elements);

	//��ʼ���µĹ�ϣ��
	vector<node*> tmp(next_size, (node*)0);

	for (int i = 0; i < size; ++i){
		node *head = buckets[i];
		while (head){
			int new_pos = buckets_index(head->val.first, next_size);
			buckets[i] = head->next;
			head->next = tmp[new_pos];
			tmp[new_pos] = head;
			head = buckets[i];
		}
	}

	//�����¾ɹ�ϣ��
	buckets.swap(tmp);
}

template<class Key, class Value>
void hashtable<Key, Value>::printHashTable(){
	cout << "��ϣ���������� :" << endl;
	for (int i = 0; i < buckets.size(); ++i){
		node *head = buckets[i];
		while (head){
			cout << head->val.first << "  " << head->val.second << endl;
			head = head->next;
		}
	}
}
#endif