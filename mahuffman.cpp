#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <string.h>
using namespace std;
struct Node
{
	char ch;
	int freq;
	Node *left, *right;
};
//tao cap phat cho 1 cay moi
Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}
//so sanh de cho vao hang doi.
struct comp
{
	bool operator()(Node* l, Node* r)
	{
		//tan so thap nhat duoc uu tien cao nhat.
		return l->freq > r->freq;
	}
};
void encode(Node* root, string str, unordered_map<char, string> &huffmanCode)
{
	if (root == nullptr)
		return;
	//tim nut la
	if (!root->left && !root->right) 
	{
		huffmanCode[root->ch] = str;
	}
	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}
//giai ma
//xay dung 1 ham de qui trong do lien tiep xay dung 1 cay, trong do di tu nut goc
//roi tu nut goc chuyen den xuong duoi, neu gap 0 thi re trai, gap 1 thi re phai, neu gap nut la thi quay lai nut cha.
int decode(Node* root, int &index, string str)
{
	if (root == nullptr) 
	{
		return 0;
	}
	// tim nut la
	if (!root->left && !root->right)
	{
		cout << root->ch;
		return 0;
	}
	index++;
	if (str[index] =='0')	//khi bang khong thi trai
		decode(root->left, index, str);
	if (str[index]=='1')
		decode(root->right, index, str);	// =1 thi phai
	else
		return 1;
	if ((!root->left or !root->right) == NULL)
		return 1;
}
void buildHuffmanTree(string text)
{
	//dem tan suat xuat hien va luu tru
	unordered_map<char, int> freq;
	for (char ch: text) 
	{
		freq[ch]++;
	}
	//tao hang doi
	priority_queue<Node*, vector<Node*>, comp> pq;
	// to the priority queue.
	for (auto pair: freq) 
	{
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}
	//van lam cho den khi co >1 nut trong hang doi.
	while (pq.size() != 1)
	{
		//xoa hai nut co muc uu tien cao nhat (tan so thap nhat) tu hang doi
		Node *left = pq.top(); pq.pop();
		Node *right = pq.top();	pq.pop();
		//tao mot nut moi = tong hai nut con , sau do them no vao hang doi.
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}
	Node* root = pq.top();
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);
	cout << "Huffman Codes are :\n" << '\n';
	for (auto pair: huffmanCode) 
	{
		cout << pair.first << " " << pair.second << '\n';
	}
	//in ra chuoi da duoc ma hoa
	cout << "\nchuoi da duoc ma hoa: \n" << text << '\n';
	
	
	string str;
	//nhap vao file nhi phan: 
	fstream f;
	f.open("hf2.txt", ios::in);
	getline(f, str);
	f.close();
	cout << "\ninput bit: " << endl;
	cout << str;
	
//	for (char ch: text) 
//	{
//		str += huffmanCode[ch];
//	}
//	cout << "\nEncoded string is :\n" << str << '\n';
	cout << endl;
	int index = -1;
		cout << "\nDecoded string is: \n";
		while (index < (int)str.size() - 2) 	
		{
			decode(root, index, str);
			if(decode(root, index, str)==1)
			{
				cout << "\nSAI: Luu y: Chuoi ma hoa sai hoac chuoi ma hoa khong dung" << endl;
				break;
			}	
		}	
}
int main()
{
	string text;
	fstream f;
	f.open("hf1.txt", ios::in);
	getline(f, text);
	f.close();
	cout << text;
	cout << "\nLength of the quote: " << text.length() << endl;	//do dai chuoi.	
//	cout << "Length of the quote: " << text.size() << endl;	//giong cai tren :D
	buildHuffmanTree(text);
	return 0;
}

