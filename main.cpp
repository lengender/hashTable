#include"hashtable.h"

int main()
{
	//(int, string) �������£�
	hashtable<int, string> ht;
	
	ht.insert(pair<int, string>(12, "this"));
	ht.insert(pair<int, string>(3, "is"));
	ht.insert(pair<int, string>(58, "a"));
	ht.insert(pair<int, string>(10, "test"));
	ht.insert(pair<int, string>(23, "hashtable"));

	ht.printHashTable();
	cout << "ɾ��(3, a)��";
	ht.erase(3);
	ht.printHashTable();

	cout << "����(3, hahaha)��";
	ht.insert(pair<int, string>(3, "hahaha"));
	ht.printHashTable();

	cout << "===================================" << endl;
	
	//(string, string) ��������
	hashtable<string, string> strHt;
	strHt.insert(pair<string, string>("hello", "world"));
	strHt.insert(pair<string, string>("other", "hash"));
	strHt.insert(pair<string, string>("test", "china"));
	strHt.insert(pair<string, string>("stl", "nimeiya"));

	strHt.printHashTable();

	cout << "�ж� test �Ƿ��ڹ�ϣ���У�" << strHt.find("test") << endl;
	cout << "���ش�ʱ��ϣ���е�Ԫ�ظ�����" << strHt.size() << endl;
	cout << "ɾ��test��" << endl;
	strHt.erase("test");
	strHt.printHashTable();
	cout << "�ж� test �Ƿ��ڹ�ϣ���У�" << strHt.find("test") << endl;
	cout << "���ش�ʱ��ϣ���е�Ԫ�ظ�����" << strHt.size() << endl;
}