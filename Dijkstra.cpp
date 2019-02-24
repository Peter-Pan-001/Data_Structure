#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
using namespace std;
void gotoxy(int x,int y);   

void gotoxy(int x,int y){  //确定光标位置函数
    COORD c;
    c.X=x-1;
    c.Y=y-1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

struct Edge{          //边节点 
	int Veradj;
	int cost;
	Edge* link;
	Edge(){}
	Edge(int ver,int v){cost=v;Veradj=ver;link=NULL;}
}; 
 
struct Vertex{       //顶点表节点
	int Vername;
	Edge* adjacent;
	Vertex(){}
};

class Graph{                           //有权有向图
	private:
		Vertex* head;                   //顶点表头指针 
		int graphsize;                  //图中点数 
	public:
		Graph(int number=0){          //创建点图
			graphsize=number;
			head=new Vertex[graphsize];
			for(int i=0;i<graphsize;i++){
				head[i].Vername=i;
				head[i].adjacent=NULL;
			}
		}
		~Graph();                       //析构函数 
		void createGraph(int number);                           //创建点图 
		int getWeight(int dot1,int dot2);                       //返回指定边的权值 
		int insertEdge(int dot1,int dot2,int cost1);           //向有向图中插入一条边  
		bool deleteEdge(int dot1,int dot2);                     //删除一条边  
		bool search(int dot);                                   //查看指定点是否在图中
		bool searchEdge(int dot1,int dot2);                     //查看指定边是否在图中
		void Dijkstra(int v);                        //图中指定顶点到其他顶点的最短路径 
		
};


Graph::~Graph(){                      //析构函数
    Edge *p=new Edge();
	Edge *q=new Edge();
	if(graphsize!=0){
    	for(int i=0;i<graphsize;i++){
    	    p=head[i].adjacent;
			while(p!=NULL){
				q=p->link;
				delete p;
				p=q;
			}
		}
    delete[] head;
	}     
}


int Graph::getWeight(int dot1,int dot2){       //返回指定边的权值
    Edge *p=new Edge();
	if(search(dot1) && search(dot2)){
    	for(int i=0;i<graphsize;i++)
    	    if(head[i].Vername==dot1){
    	    	p=head[i].adjacent;
    	    	while(p!=NULL){
    	    		if((p->Veradj)==dot2) return p->cost;
    	    		p=p->link;
				}
			}
	}
	return -1;
}


int Graph::insertEdge(int dot1,int dot2,int cost1){            //向有向图中插入边
	Edge *p=new Edge();
	p->Veradj=dot2;
	p->cost=cost1;
	p->link=NULL;
	if(search(dot1) && search(dot2) && dot1!=dot2){
		Edge *q=head[dot1].adjacent;
		if(q==NULL) head[dot1].adjacent=p;
		else{
			while(q->link!=NULL) q=q->link;
			q->link=p;
		}
		return 1;
	}
	return 0;
}
    	    

bool Graph::deleteEdge(int dot1,int dot2){          //删除边
    Edge *p=new Edge();
	Edge *q=new Edge();
	if(search(dot1) && search(dot2) && dot1!=dot2){
    	for(int i=0;i<graphsize;i++)
			if(head[i].Vername==dot1){        //找到顶点结点     
				p=head[i].adjacent;
				if(p==NULL) return false;
				if(p->Veradj==dot2){
					q=p->link;
					head[i].adjacent=q;
					delete p;
					return true;
				}
				while((p->link)!=NULL){
					q=p->link;
					if((q->Veradj)==dot2){       //q指向要删除的边结点
						if((q->link)!=NULL){     //q不是链表的最后一个结点
							p->link=q->link;
							delete q;
							return true;
						}
						if((q->link)==NULL){     //q是链表的最后一个结点
							p->link=NULL;
							delete q;
							return true;
						}
					}
					p=p->link;
				}
			}
	}
	return false;
}

            	
bool Graph::search(int dot){   
    for(int i=0;i<graphsize;i++)
        if(head[i].Vername==dot) return true;
    return false;
}

bool Graph::searchEdge(int dot1,int dot2){
	Edge *p;
	for(int i=0;i<graphsize;i++){
		if(head[i].Vername==dot1){
			p=head[i].adjacent;
			while(p!=NULL && (p->Veradj)!=dot2) p=p->link;
			if(p==NULL) return false;
			else return true;
		}
	}
	return false;
}


void Graph::Dijkstra(int v){      //正权最短路径算法，v为开始结点
	int u,k,carry_on;int l,m,w;bool e; //l,m作为打印时的中间记录值 
	int max=10000;
	Edge *p=new Edge();
	int n=graphsize;
	int *path=new int[graphsize];
	int *dist=new int[graphsize];
	int *s=new int[graphsize];
	for(int i=0;i<n;++i){
		path[i]=-1;
		dist[i]=max;
		s[i]=0;
	}
	dist[v]=0;
	s[v]=1;
	p=head[v].adjacent;
	u=v;
	system("cls");
	for(int j=0;j<n-1;j++){
		e=true;
		while(p!=NULL){
			k=p->Veradj;
			if(s[k]!=1 && dist[u]+(p->cost)<dist[k]){
				dist[k]=dist[u]+p->cost;
				path[k]=u;
			}
			p=p->link;
		}
		int ldist=max;
		for(int i=0;i<graphsize;i++)
		    if(dist[i]>0 && dist[i]<ldist && s[i]==0){
		    	ldist=dist[i];
		    	u=i;
			}
		s[u]=1;
		p=head[u].adjacent;
		for(i=0;i<31;i++) cout<<endl;   //打印表格
		cout<<"┌────";     
    for(i=1;i<graphsize;i++)
        cout<<"┰───";
        cout<<"┰───┐";
        cout<<endl;
    cout<<"│ "<<"v[i] "<<"  ";
    Sleep(200);
    for(i=0; i<graphsize; i++)
    {
        cout<<"│"<<"  ";
        cout<<i<<"   ";
        Sleep(200);
    }
    cout<<"│";
    cout<<endl;
    cout<<"┠────";
    for(i=1;i<graphsize;i++)
        cout<<"┰───";
        cout<<"┰───┫";
        cout<<endl;
    cout<<"│ "<<"s[i] "<<"  ";
    Sleep(200);
    for(i=0; i<graphsize; i++)
    {
        cout<<"│"<<"  ";
        cout<<s[i]<<"   ";
        Sleep(200);
    }
    cout<<"│";
    cout<<endl;
    cout<<"┠────";
    for(i=1;i<graphsize;i++)
        cout<<"┰───";
        cout<<"┰───┫";
        cout<<endl;
    cout<<"│"<<"dist[i] ";
    Sleep(200);
    for(i=0; i<graphsize; i++)
    {
        cout<<"│"<<"  ";
        if(dist[i]>=0 && dist[i]<10)
        {cout<<dist[i]<<"   ";Sleep(200);}
        if(dist[i]>=10 && dist[i]<100)
        cout<<dist[i]<<"  ";
        if(dist[i]>=100 && dist[i]<1000)
        cout<<dist[i];
        if(dist[i]==max) cout<<"max ";
    }
    cout<<"│";
    cout<<endl;
    cout<<"┠────";
    for(i=1;i<graphsize;i++)
        cout<<"┰───";
        cout<<"┰───┫";
        cout<<endl;
    cout<<"│"<<"path[i] ";
    for(i=0; i<graphsize; i++)
    {
        cout<<"│"<<"  ";
        if(path[i]!=-1)
        cout<<path[i]<<"   ";
        else
            cout<<path[i]<<"  ";
    }
    cout<<"│";
    cout<<endl;
    cout<<"┕━━━━";
    for(i=1;i<graphsize;i++)
        cout<<"┶━━━";
    cout<<"┶━━━┛";
    cout<<endl;
    Sleep(500);      //打印表格
	if(u!=v){        //打印最短路径
		if(path[u]!=-1){
			cout<<"从点"<<v<<"到点"<<u<<"的最短路径为:";
		    cout<<v<<"->";
		    m=v;
		    while(e){
				l=u;
			    while(path[l]!=m) l=path[l];
			    if(l==u){ 
					cout<<l<<endl;
				    e=false;
				}
			    else cout<<l<<"->";
				m=l;
			}
		}
	}   //打印最短路径
	cout<<"从点"<<v<<"到点"<<u<<"的最短路径长度为:"<<dist[u]<<endl;
	cout<<endl;
	if(n==4){       ////本程序只能打印四个顶点的图
		gotoxy(10,10);cout<<"0";Sleep(200);
	    gotoxy(30,10);cout<<"1";Sleep(200);
		gotoxy(10,30);cout<<"2";Sleep(200);
        gotoxy(30,30);cout<<"3";Sleep(200);
		if(searchEdge(0,1) || searchEdge(1,0)){    //判断顶点0,1间是否有边
			if((path[u]==0 && u==1) ||(path[u]==1 && u==0) ){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
				for(i=11;i<30;i++){
						gotoxy(i,10);
						cout<<".";
				        Sleep(50);
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
			}
			else for(i=11;i<30;i++){
						gotoxy(i,10);
						cout<<".";
				        Sleep(50);
				}
			gotoxy(20,9);
			if(searchEdge(0,1)) cout<<getWeight(0,1);
			else cout<<getWeight(1,0);
			Sleep(50);
		}
		if(searchEdge(0,2) || searchEdge(2,0)){    //判断顶点0,2间是否有边
			if((path[u]==0 && u==2) ||(path[u]==2 && u==0) ){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
				for(i=11;i<30;i++){
						gotoxy(10,i);
						cout<<".";
						Sleep(50);
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
			}
			else for(i=11;i<30;i++){
						gotoxy(10,i);
						cout<<".";
						Sleep(50);
				}
			gotoxy(9,20);
			if(searchEdge(0,2)) cout<<getWeight(0,2);
			else cout<<getWeight(2,0);
			Sleep(50);
		}
		if(searchEdge(0,3) || searchEdge(3,0)){    //判断顶点0,3间是否有边
			if((path[u]==0 && u==3) ||(path[u]==3 && u==0) ){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
				i=11;w=11;
				while(i<30 && w<30){
					gotoxy(i,w);
					cout<<".";
					Sleep(50);
					i++;w++;
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
			}
			else{
				i=11;w=11;
				while(i<30 && w<30){
					gotoxy(i,w);
					cout<<".";
					Sleep(50);
					i++;w++;
				}
			}
			gotoxy(19,18);
			if(searchEdge(0,3)) cout<<getWeight(0,3);
			else cout<<getWeight(3,0);
			Sleep(50);
		}
		if(searchEdge(1,2) || searchEdge(2,1)){    //判断顶点1,2间是否有边
			if((path[u]==1 && u==2) ||(path[u]==2 && u==1) ){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
			    i=11;w=29;
				while(i<30 && w>10){
					gotoxy(i,w);
					cout<<".";
					Sleep(50);
					i++;w--;
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
			}
			else{
				i=11;w=29;
				while(i<30 && w>10){
					gotoxy(i,w);
					cout<<".";
					Sleep(50);
					i++;w--;
				}
			}
			gotoxy(19,22);
			if(searchEdge(1,2)) cout<<getWeight(1,2);
			else cout<<getWeight(2,1);
			Sleep(50);
		}
		if(searchEdge(1,3) || searchEdge(3,1)){     //判断顶点1,3间是否有边
			if((path[u]==1 && u==3) ||(path[u]==3 && u==1) ){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
				for(i=11;i<30;i++){
						gotoxy(30,i);
						cout<<".";
						Sleep(50);
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
			}
			else for(i=11;i<30;i++){
						gotoxy(30,i);
						cout<<".";
						Sleep(50);
				}
			gotoxy(31,20);
			if(searchEdge(1,3)) cout<<getWeight(1,3);
			else cout<<getWeight(3,1);
			Sleep(50);
		}
		if(searchEdge(2,3) || searchEdge(3,2)){    //判断顶点2,3间是否有边
			if((path[u]==2 && u==3) ||(path[u]==3 && u==2) ){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
				for(i=11;i<30;i++){
						gotoxy(i,30);
						cout<<".";
						Sleep(50);
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
			}
			else for(i=11;i<30;i++){
						gotoxy(i,30);
						cout<<".";
						Sleep(50);
				}
			gotoxy(20,31);
			if(searchEdge(2,3)) cout<<getWeight(2,3);
			else cout<<getWeight(3,2);
			Sleep(50);
		} 
	}    //打印图
	gotoxy(1,43);
	cout<<"请输入1继续:";
	cin>>carry_on;
	if(carry_on!=1) break;
	system("cls");
	}
	for(int y=0;y<n;y++) if(path[y]==-1 && y!=v) cout<<"没有找到从点"<<v<<"到点"<<y<<"的路径"<<endl;
}

main(){
	bool finish=true,ifdelete1,ifdelete2;//finish是否退出程序
	int ifcontinue=1,choice,i,p,a,b,cost,result1,result2; //i为图中点数，p为选择的操作，a为起点，b为终点，cost为权值
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
	while(finish){
		cout<<"                   ***************************************\n";
        cout<<"．．＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿．╭╮╭╮．＿＿＿＿＿＿＿＿＿＿＿＿．．\n";
        cout<<"．．＿＿＿＿＿＿＿＿＿＿＿＿＿．．． ╭┴┴★╮ ＿＿＿＿＿＿＿＿＿．．．．．\n";
        cout<<"．．＿＿＿＿＿＿＿＿＿＿＿＿＿．．．│◎　　︵│＿＿＿＿＿＿＿＿．．．．．．\n";
        cout<<"．．．＿＿＿＿＿＿＿＿＿＿＿＿※※※╰○－－○╯※※※＿＿＿＿＿＿＿．．．．\n";
        cout<<"．．．＿＿＿＿＿＿＿＿＿＿＿1.创建一个有向带权图.＿＿＿＿＿＿＿．．．．"<<endl;
        cout<<"．．．＿＿＿＿＿＿＿＿＿＿＿2.创建一个无向带权图.＿＿＿＿＿＿＿．．．．"<<endl;
        cout<<"．．．＿＿＿＿＿＿＿＿＿＿＿3.退出系统...........＿＿＿＿＿＿＿．．．．"<<endl;
        cout<<"．．．．．．．．．．．．．．．．．．．．．．．．．．．．．．．．．．．．．．\n";
        cout<<"        ══════════════◆◆◆◆════════════════\n";
		cout<<"请输入您的选择:";
		cin>>choice;
		ifcontinue=1;
		if(choice==3) break;    //退出系统
		while((choice==1 || choice==2) && ifcontinue==1){   
			cout<<"请输入图中的点数:";
			cin>>i;
			Graph g(i);
			if(choice==1){     //有向带权图
				while(ifcontinue==1){
					cout<<"请选择操作:"<<endl;
			        cout<<"1.插入边"<<endl;
			        cout<<"2.删除边"<<endl;
			        cout<<"3.Dijkstra算法"<<endl;
				    cin>>p;
					if(p==1){
						cout<<"请依次输入插入边的起点，终点和权值:";
						cin>>a>>b>>cost;
						result1=g.insertEdge(a,b,cost);
						if(result1==1) cout<<"插入成功!"<<endl;
						if(result1==0) cout<<"插入失败!"<<endl;
					}
					if(p==2){
						cout<<"请依次输入删除边的起点，终点:";
						cin>>a>>b;
						ifdelete1=g.deleteEdge(a,b);
						if(ifdelete1) cout<<"删除成功!"<<endl;
						else cout<<"删除失败!"<<endl;
					}
					if(p==3){
						cout<<"请选择开始结点:";
						cin>>a;
						g.Dijkstra(a);
					}
					cout<<"请选择是否继续:1.继续 2.不继续"<<endl;
					cin>>ifcontinue;
				}
			}
			if(choice==2){         //无向带权图
				while(ifcontinue==1){
					cout<<"请选择操作:"<<endl;
			        cout<<"1.插入边"<<endl;
			        cout<<"2.删除边"<<endl;
			        cout<<"3.Dijkstra算法"<<endl;
				    cin>>p;
					if(p==1){
						cout<<"请依次输入插入边的起点，终点和权值:";
						cin>>a>>b>>cost;
						result1=g.insertEdge(a,b,cost);
						result2=g.insertEdge(b,a,cost);
						if(result1==1 && result2==1) cout<<"插入成功!"<<endl;
						       else cout<<"插入失败!"<<endl;
					}
					if(p==2){
						cout<<"请依次输入删除边的起点，终点:";
						cin>>a>>b;
						ifdelete1=g.deleteEdge(a,b);
						ifdelete2=g.deleteEdge(b,a);
						if(ifdelete1 && ifdelete2) cout<<"删除成功!"<<endl;
						 else cout<<"删除失败!"<<endl;
					}
					if(p==3){
						cout<<"请选择开始结点:";
						cin>>a;
						g.Dijkstra(a);
					}
					cout<<"请选择是否继续:1.继续 2.不继续"<<endl;
					cin>>ifcontinue;
				}
			}
		}
		cout<<"请选择是否继续使用本系统:1.是 2.否"<<endl;
		cin>>p;
		if(p==2) finish=false;
	}
}
