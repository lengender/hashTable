#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include<vector>
#include<list>
#include<iostream>
#include<algorithm>
#include"hashFunc.h"
using namespace std;


//哈希节点,包括键值和指针
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
	//哈希表节点键值类型
	typedef pair<Key, Value> T;

	//表节点
	typedef hashtable_node<T> node;
public:
	//构造函数
	hashtable();
	hashtable(hashtable<Key, Value> &ht)
		: buckets(ht.buckets), num_elements(ht.num_elements)
	{}

	//插入一个关键字
	void insert(T kv);   

	//根据键值删除关键字 
	void erase(Key key);

	//判断关键字是否在哈希表中
	bool find(Key key);  

	//返回哈希表中关键字个数
	int size(){
		return num_elements;
	}

	void printHashTable();
private:
	//根据传入大小判断是否需要重新分配哈希表
	void resize(int num_elements);

	//根据键值返回桶的编号
	int buckets_index(Key key, int size){
		return hash(key) % size;
	}

	//根据节点返回键值
	Key get_key(T  node){
		return node.first;
	}
private:
	//使用STL list<T>作桶
	vector<node*> buckets;    

	//哈希表中元素个数
	size_t num_elements;

	//哈希函数
	hashFunc<Key> hash;
};

//构造函数，初始化哈希表
template<class Key, class Value>
hashtable<Key, Value>::hashtable(){
	const int n_buckets = next_prime(1);
	buckets.reserve(n_buckets);
	buckets.insert(buckets.end(), n_buckets, (node*)0);
	num_elements = 0;
}

//插入一个关键字
template<class Key, class Value>
void hashtable<Key, Value>::insert(T kv){
	//在插入之前，调用resize函数，判断是否需要重建哈希表
	resize(num_elements + 1);
	//计算出插入位置
	int pos = buckets_index(kv.first, buckets.size());
	node *head = buckets[pos];	

	//判断键值是否已经存在，若存在，则直接返回，不插入
	for (node *cur = head; cur; cur = cur->next){
		if (cur->val.first == kv.first)
			return;
	}

	//分配节点，插入
	node *tmp = new node(kv);
	tmp->next = head;
	buckets[pos] = tmp;
	num_elements++; //记录个数
}

//根据键值删除关键字 
template < class Key, class Value> 
void hashtable<Key, Value>::erase(Key key){
	//找出桶的位置
	int pos = buckets_index(key, buckets.size());
	node *head = buckets[pos];
	node *pre = NULL; 
	while (head){
		//查找到对应键，并删除
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

//根据键值，判断是否在哈希表中
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
	//当元素个数大于桶的个数时，重新分配哈希表
	const int size = buckets.size();
	if (num_elements <= size) return;

	//找出下一个质数
	const int next_size = next_prime(num_elements);

	//初始化新的哈希表
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

	//交换新旧哈希表
	buckets.swap(tmp);
}

template<class Key, class Value>
void hashtable<Key, Value>::printHashTable(){
	cout << "哈希表内容如下 :" << endl;
	for (int i = 0; i < buckets.size(); ++i){
		node *head = buckets[i];
		while (head){
			cout << head->val.first << "  " << head->val.second << endl;
			head = head->next;
		}
	}
}
#endif