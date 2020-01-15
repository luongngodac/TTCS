#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
using namespace std;
// khai bao cau truc
struct node{
    int Data;
    struct node *pLeft;
    struct node *pRight;
};
typedef struct node NODE;
typedef NODE *Tree;

// khoi tao cay
void Init(Tree &t){
    t=NULL;
}

// Tao Node tren cay
NODE *makeNode(int x){
    NODE *p = new NODE;
    if(p==NULL) return NULL;
    else{
        p->Data = x;
        p->pLeft = p->pRight = NULL;
    }
    return p;
}

// Insert Node vao cay
void insertNode(Tree &t, int x){

    if(t==NULL){ // cay rong => x la Node goc
        NODE *p = new NODE;
        p=makeNode(x);
        t=p;
    }
    else {
        if(t->Data > x){
            insertNode(t->pLeft,x);
        }
        else if(t->Data < x){
         insertNode(t->pRight,x);
        }
    }
}

// Nhap du lieu cho cay
void inputTree(Tree &t){
    Init(t);// phai khoi tao cay truoc thi moi co the nhap du lieu cho cay
    cout<<"Nhap du lieu cho cay tu file np1\n";
	
	int a[11];
    ifstream f ("np1.txt");
    if(! f.is_open())
    {
        cout<<"Khong the mo file.\n";
    }
    else {
        for(int i = 0; i <10; i++)	// chay chi den 10 boi vi khi khao bao 11 thi phai tru di 1 bien trong sau cung
        {
            f>>a[i];
            insertNode(t,a[i]);
        }
    }
    for(int i =0; i <10; i++)
    {
        cout << a[i] <<" ";
    }
    cout << endl;
    f.close();	 
}

// Xuat du lieu
void output(Tree &t){
    if(t!=NULL){
        cout<<t->Data<<" ";
        output(t->pLeft);
        output(t->pRight);
    }
}

// tim phan tu trong cay
//NODE *searchTree(Tree &t, int x){
//    if(t==NULL) return NULL;
//    else if(t->Data<x) searchTree(t->pRight,x);
//    else if(t->Data>x) searchTree(t->pLeft,x);
//    else return t;
//}

// Tim phan tu q bi xoa, cho phan tu p len thay the
void thaythe(Tree &q, Tree &p){
    // tim phan tu trai nhat cua cay ben phai
    //if(t==NULL) return;
    if(p->pLeft!=NULL){
        thaythe(q,p->pLeft);
    }
    else {
        q->Data = p->Data;
        q=p;
        p=p->pRight;
    }
}

// xoa phan tu
void delTree(Tree &t, int x){
    if(t==NULL) return;
    if(t->Data > x) delTree(t->pLeft,x);
    if(t->Data < x) delTree(t->pRight,x);
    if(t->Data == x) { // khi tim ra phan tu do roi
        // xoa Node la hoac Node co 1 phan tu
        NODE *q = t;// xoa phan tu bang con tro
        if(t->pLeft==NULL) { // neu ma ben traiphan tu do bang NULL
            t=t->pRight; // cho t tro toi t->pRight
        }
        else if(t->pRight==NULL){
            t=t->pLeft;
        }
        // xoa Node co 2 phan tu Trai va Phai
       else thaythe(q,t->pRight);
        delete q;
    }
}
int main()
{
    Tree t;
    int k,x;
    inputTree(t);
    cout << "duyet cay nhi phan:" <<endl;
    output(t);

//    cout<<endl<<"Nhap so ban muon tim:";
//    cin>>x;
//    NODE *p = searchTree(t,x);
//    if(p==NULL) cout<<"Khong tim thay";
//    else cout<<"Co tim thay";

    cout<<endl<<"Nhap phan tu can xoa:";
    cin>>k;
    delTree(t,k);
    output(t);
    return 0;
}
