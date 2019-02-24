#include<iostream>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
using namespace std;
bool Isincreasing(int *A,int n1);
void Binarysearch(int *A,int n1,int k1);
int Fbnqsearch(int *A,int m1,int k1,int *fib);
void Createfbnq(int n,int *f);
static int count1,count2;


void Createfbnq(int n,int *f){
	f[0]=1;f[1]=1;
	for(int i=2;i<n+3;i++)f[i]=f[i-1]+f[i-2];
}


bool Isincreasing(int *A,int n1){
	for(int u=0;u<n1-1;u++){
		if(A[u]>A[u+1]){
			cout<<"并不是递增序列^_^没办法用本程序排序哦亲"<<endl;return false;
		}
	}
	return true;
}

void Binarysearch(int *A,int n1,int k1){
	int i,s=1,e=n1;count1=0;
	while(s<=e){
		i=(s+e)/2;
		for(int j=0;j<n1;j++){
			if(A[j]==A[i-1]){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
				cout<<A[j]<<" ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
			}
			else cout<<A[j]<<" ";
		}
		count1++;
		cout<<endl;
		if(k1<A[i-1])e=i-1;
		if(k1>A[i-1])s=i+1;
		if(k1==A[i-1]){
			cout<<"您所查找的数为输入数列的第"<<i<<"个数"<<endl;
			cout<<"查找次数为"<<count1<<"次"<<endl;
			return;
		}
		Sleep(500);
	}
	cout<<"Sorry. Not found."<<endl;
	cout<<"查找次数为"<<count1<<"次"<<endl;
	return;
}

int Fbnqsearch(int *A,int m1,int k1,int *fib){
	int i1=fib[m1],p1=fib[m1-1],q1=fib[m1-2];
	int t1;count2=0;
	int n1=fib[m1+1]-1;
	while(k1!=A[i1]){
		for(int j=0;j<n1;j++){
			if(A[j]==A[i1-1]){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
				cout<<A[j]<<" ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
			}
			else cout<<A[j]<<" ";
		}
		count2++;
	    cout<<endl;
		if(k1<A[i1]){
			if(q1==0)return 1;
			else{i1-=q1;t1=p1;p1=q1;q1=t1-q1;}
		}
		if(k1>A[i1]){
			if(p1==1)return i1;
			else{i1+=q1;p1-=q1;q1-=p1;}
		}
		Sleep(500);
	}
	return i1+1;
}



main(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
	clock_t t1,t2;
	bool Isexit=false;
	int n,k,i;
	int *a;
	int m=0;//n=fib[m+1]-1
	int *fib;
	while(!Isexit){
	cout<<"                ***************************************\n";
    cout<<"．．＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿．╭╮╭╮．＿＿＿＿＿＿＿＿＿＿＿＿．．\n";
    cout<<"．．＿＿＿＿＿＿＿＿＿＿＿＿＿．．． ╭┴┴★╮ ＿＿＿＿＿＿＿＿＿．．．．．\n";
    cout<<"．．＿＿＿＿＿＿＿＿＿＿＿＿＿．．．│◎　　︵│＿＿＿＿＿＿＿＿．．．．．．\n";
    cout<<"．．．＿＿＿＿＿＿＿＿＿＿＿＿※※※╰○－－○╯※※※＿＿＿＿＿＿＿．．．．\n";
	cout<<"请输入查找总数字的个数:"<<endl;
	cin>>n;
	a=new int[n];
	fib=new int[n+3];
	Createfbnq(n,fib);
	cout<<"请按递增次序依次输入数列:"<<endl;
	for(i=0;i<n;i++){cin>>a[i];}
	bool Isincrease=Isincreasing(a,n);
	while(!Isincrease){
		cout<<"请按递增次序依次输入数列:"<<endl;
		for(i=0;i<n;i++){cin>>a[i];}
		Isincrease=Isincreasing(a,n);
	}
	cout<<"请输入要查找的数:"<<endl;
	cin>>k;
	bool Iscontinue=true;
	bool Canfbnq=false;
	while(Iscontinue){
        cout<<"请选择1.对半查找2.斐波那契查找"<<endl;
	    int p;cin>>p;
	    while(p!=1 && p!=2){
		    cout<<"Error"<<endl;
		    cout<<"请选择1.对半查找2.斐波那契查找"<<endl;
		    cin>>p;
		}
		if(p==1){
			t1=clock();
			Binarysearch(a,n,k);
			t2=clock();
			cout<<"运行时间为"<<double(t2-t1)*1000/CLOCKS_PER_SEC<<"ms"<<endl;
		}
		if(p==2){
			for(i=0;i<n+3;i++){
				if(n==fib[i+1]-1){
					m=i;
					Canfbnq=true;
					break;
				}
			}
			if(!Canfbnq)cout<<"不能进行斐波那契排列哦亲"<<endl;
			if(Canfbnq){
				t1=clock();
				int result=Fbnqsearch(a,m,k,fib);
				t2=clock();
				if(result==0){cout<<"Sorry. Not found."<<endl;cout<<"查找次数为"<<count2<<"次"<<endl;}
				if(result==n){
					if(a[n]!=k){cout<<"Sorry. Not found."<<endl;cout<<"查找次数为"<<count2<<"次"<<endl;}
					else{cout<<"您所查找的数为输入数列的第"<<result<<"个数"<<endl;cout<<"查找次数为"<<count2<<"次"<<endl;}
				}
				else{cout<<"您所查找的数为输入数列的第"<<result<<"个数"<<endl;cout<<"查找次数为"<<count2<<"次"<<endl;}
				cout<<"运行时间为"<<double(t2-t1)*1000/CLOCKS_PER_SEC<<"ms"<<endl;
			}
		}
		cout<<"请选择是否继续:1.Yes 2.No"<<endl;
		cin>>p;
		if(p==2) Iscontinue=false;
	}
	cout<<"请选择是否退出本程序:1.Yes 2.No"<<endl;
	int l;
	cin>>l;
	if(l==1)Isexit=true;
	system("Cls");
	}
}



