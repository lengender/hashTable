#include"hashtable.h"

int main()
{
	//(int, string) 测试如下：
	hashtable<int, string> ht;
	
	ht.insert(pair<int, string>(12, "this"));
	ht.insert(pair<int, string>(3, "is"));
	ht.insert(pair<int, string>(58, "a"));
	ht.insert(pair<int, string>(10, "test"));
	ht.insert(pair<int, string>(23, "hashtable"));

	ht.printHashTable();
	cout << "删除(3, a)后，";
	ht.erase(3);
	ht.printHashTable();

	cout << "插入(3, hahaha)后，";
	ht.insert(pair<int, string>(3, "hahaha"));
	ht.printHashTable();

	cout << "===================================" << endl;
	
	//(string, string) 测试如下
	hashtable<string, string> strHt;
	strHt.insert(pair<string, string>("hello", "world"));
	strHt.insert(pair<string, string>("other", "hash"));
	strHt.insert(pair<string, string>("test", "china"));
	strHt.insert(pair<string, string>("stl", "nimeiya"));

	strHt.printHashTable();

	cout << "判断 test 是否在哈希表中：" << strHt.find("test") << endl;
	cout << "返回此时哈希表中的元素个数：" << strHt.size() << endl;
	cout << "删除test后" << endl;
	strHt.erase("test");
	strHt.printHashTable();
	cout << "判断 test 是否在哈希表中：" << strHt.find("test") << endl;
	cout << "返回此时哈希表中的元素个数：" << strHt.size() << endl;
}