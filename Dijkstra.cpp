#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
using namespace std;
void gotoxy(int x,int y);   

void gotoxy(int x,int y){  //ȷ�����λ�ú���
    COORD c;
    c.X=x-1;
    c.Y=y-1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

struct Edge{          //�߽ڵ� 
	int Veradj;
	int cost;
	Edge* link;
	Edge(){}
	Edge(int ver,int v){cost=v;Veradj=ver;link=NULL;}
}; 
 
struct Vertex{       //�����ڵ�
	int Vername;
	Edge* adjacent;
	Vertex(){}
};

class Graph{                           //��Ȩ����ͼ
	private:
		Vertex* head;                   //�����ͷָ�� 
		int graphsize;                  //ͼ�е��� 
	public:
		Graph(int number=0){          //������ͼ
			graphsize=number;
			head=new Vertex[graphsize];
			for(int i=0;i<graphsize;i++){
				head[i].Vername=i;
				head[i].adjacent=NULL;
			}
		}
		~Graph();                       //�������� 
		void createGraph(int number);                           //������ͼ 
		int getWeight(int dot1,int dot2);                       //����ָ���ߵ�Ȩֵ 
		int insertEdge(int dot1,int dot2,int cost1);           //������ͼ�в���һ����  
		bool deleteEdge(int dot1,int dot2);                     //ɾ��һ����  
		bool search(int dot);                                   //�鿴ָ�����Ƿ���ͼ��
		bool searchEdge(int dot1,int dot2);                     //�鿴ָ�����Ƿ���ͼ��
		void Dijkstra(int v);                        //ͼ��ָ�����㵽������������·�� 
		
};


Graph::~Graph(){                      //��������
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


int Graph::getWeight(int dot1,int dot2){       //����ָ���ߵ�Ȩֵ
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


int Graph::insertEdge(int dot1,int dot2,int cost1){            //������ͼ�в����
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
    	    

bool Graph::deleteEdge(int dot1,int dot2){          //ɾ����
    Edge *p=new Edge();
	Edge *q=new Edge();
	if(search(dot1) && search(dot2) && dot1!=dot2){
    	for(int i=0;i<graphsize;i++)
			if(head[i].Vername==dot1){        //�ҵ�������     
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
					if((q->Veradj)==dot2){       //qָ��Ҫɾ���ı߽��
						if((q->link)!=NULL){     //q������������һ�����
							p->link=q->link;
							delete q;
							return true;
						}
						if((q->link)==NULL){     //q����������һ�����
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


void Graph::Dijkstra(int v){      //��Ȩ���·���㷨��vΪ��ʼ���
	int u,k,carry_on;int l,m,w;bool e; //l,m��Ϊ��ӡʱ���м��¼ֵ 
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
		for(i=0;i<31;i++) cout<<endl;   //��ӡ���
		cout<<"����������";     
    for(i=1;i<graphsize;i++)
        cout<<"�ԩ�����";
        cout<<"�ԩ�������";
        cout<<endl;
    cout<<"�� "<<"v[i] "<<"  ";
    Sleep(200);
    for(i=0; i<graphsize; i++)
    {
        cout<<"��"<<"  ";
        cout<<i<<"   ";
        Sleep(200);
    }
    cout<<"��";
    cout<<endl;
    cout<<"�ĩ�������";
    for(i=1;i<graphsize;i++)
        cout<<"�ԩ�����";
        cout<<"�ԩ�������";
        cout<<endl;
    cout<<"�� "<<"s[i] "<<"  ";
    Sleep(200);
    for(i=0; i<graphsize; i++)
    {
        cout<<"��"<<"  ";
        cout<<s[i]<<"   ";
        Sleep(200);
    }
    cout<<"��";
    cout<<endl;
    cout<<"�ĩ�������";
    for(i=1;i<graphsize;i++)
        cout<<"�ԩ�����";
        cout<<"�ԩ�������";
        cout<<endl;
    cout<<"��"<<"dist[i] ";
    Sleep(200);
    for(i=0; i<graphsize; i++)
    {
        cout<<"��"<<"  ";
        if(dist[i]>=0 && dist[i]<10)
        {cout<<dist[i]<<"   ";Sleep(200);}
        if(dist[i]>=10 && dist[i]<100)
        cout<<dist[i]<<"  ";
        if(dist[i]>=100 && dist[i]<1000)
        cout<<dist[i];
        if(dist[i]==max) cout<<"max ";
    }
    cout<<"��";
    cout<<endl;
    cout<<"�ĩ�������";
    for(i=1;i<graphsize;i++)
        cout<<"�ԩ�����";
        cout<<"�ԩ�������";
        cout<<endl;
    cout<<"��"<<"path[i] ";
    for(i=0; i<graphsize; i++)
    {
        cout<<"��"<<"  ";
        if(path[i]!=-1)
        cout<<path[i]<<"   ";
        else
            cout<<path[i]<<"  ";
    }
    cout<<"��";
    cout<<endl;
    cout<<"����������";
    for(i=1;i<graphsize;i++)
        cout<<"�ک�����";
    cout<<"�ک�������";
    cout<<endl;
    Sleep(500);      //��ӡ���
	if(u!=v){        //��ӡ���·��
		if(path[u]!=-1){
			cout<<"�ӵ�"<<v<<"����"<<u<<"�����·��Ϊ:";
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
	}   //��ӡ���·��
	cout<<"�ӵ�"<<v<<"����"<<u<<"�����·������Ϊ:"<<dist[u]<<endl;
	cout<<endl;
	if(n==4){       ////������ֻ�ܴ�ӡ�ĸ������ͼ
		gotoxy(10,10);cout<<"0";Sleep(200);
	    gotoxy(30,10);cout<<"1";Sleep(200);
		gotoxy(10,30);cout<<"2";Sleep(200);
        gotoxy(30,30);cout<<"3";Sleep(200);
		if(searchEdge(0,1) || searchEdge(1,0)){    //�ж϶���0,1���Ƿ��б�
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
		if(searchEdge(0,2) || searchEdge(2,0)){    //�ж϶���0,2���Ƿ��б�
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
		if(searchEdge(0,3) || searchEdge(3,0)){    //�ж϶���0,3���Ƿ��б�
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
		if(searchEdge(1,2) || searchEdge(2,1)){    //�ж϶���1,2���Ƿ��б�
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
		if(searchEdge(1,3) || searchEdge(3,1)){     //�ж϶���1,3���Ƿ��б�
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
		if(searchEdge(2,3) || searchEdge(3,2)){    //�ж϶���2,3���Ƿ��б�
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
	}    //��ӡͼ
	gotoxy(1,43);
	cout<<"������1����:";
	cin>>carry_on;
	if(carry_on!=1) break;
	system("cls");
	}
	for(int y=0;y<n;y++) if(path[y]==-1 && y!=v) cout<<"û���ҵ��ӵ�"<<v<<"����"<<y<<"��·��"<<endl;
}

main(){
	bool finish=true,ifdelete1,ifdelete2;//finish�Ƿ��˳�����
	int ifcontinue=1,choice,i,p,a,b,cost,result1,result2; //iΪͼ�е�����pΪѡ��Ĳ�����aΪ��㣬bΪ�յ㣬costΪȨֵ
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
	while(finish){
		cout<<"                   ***************************************\n";
        cout<<"�����ߣߣߣߣߣߣߣߣߣߣߣߣߣߣߣߣ��q�r�q�r���ߣߣߣߣߣߣߣߣߣߣߣߣ���\n";
        cout<<"�����ߣߣߣߣߣߣߣߣߣߣߣߣߣ����� �q�ةء�r �ߣߣߣߣߣߣߣߣߣ���������\n";
        cout<<"�����ߣߣߣߣߣߣߣߣߣߣߣߣߣ��������򡡡��੦�ߣߣߣߣߣߣߣߣ�����������\n";
        cout<<"�������ߣߣߣߣߣߣߣߣߣߣߣߡ������t�𣭣���s�������ߣߣߣߣߣߣߣ�������\n";
        cout<<"�������ߣߣߣߣߣߣߣߣߣߣ�1.����һ�������Ȩͼ.�ߣߣߣߣߣߣߣ�������"<<endl;
        cout<<"�������ߣߣߣߣߣߣߣߣߣߣ�2.����һ�������Ȩͼ.�ߣߣߣߣߣߣߣ�������"<<endl;
        cout<<"�������ߣߣߣߣߣߣߣߣߣߣ�3.�˳�ϵͳ...........�ߣߣߣߣߣߣߣ�������"<<endl;
        cout<<"����������������������������������������������������������������������������\n";
        cout<<"        �T�T�T�T�T�T�T�T�T�T�T�T�T�T���������T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n";
		cout<<"����������ѡ��:";
		cin>>choice;
		ifcontinue=1;
		if(choice==3) break;    //�˳�ϵͳ
		while((choice==1 || choice==2) && ifcontinue==1){   
			cout<<"������ͼ�еĵ���:";
			cin>>i;
			Graph g(i);
			if(choice==1){     //�����Ȩͼ
				while(ifcontinue==1){
					cout<<"��ѡ�����:"<<endl;
			        cout<<"1.�����"<<endl;
			        cout<<"2.ɾ����"<<endl;
			        cout<<"3.Dijkstra�㷨"<<endl;
				    cin>>p;
					if(p==1){
						cout<<"�������������ߵ���㣬�յ��Ȩֵ:";
						cin>>a>>b>>cost;
						result1=g.insertEdge(a,b,cost);
						if(result1==1) cout<<"����ɹ�!"<<endl;
						if(result1==0) cout<<"����ʧ��!"<<endl;
					}
					if(p==2){
						cout<<"����������ɾ���ߵ���㣬�յ�:";
						cin>>a>>b;
						ifdelete1=g.deleteEdge(a,b);
						if(ifdelete1) cout<<"ɾ���ɹ�!"<<endl;
						else cout<<"ɾ��ʧ��!"<<endl;
					}
					if(p==3){
						cout<<"��ѡ��ʼ���:";
						cin>>a;
						g.Dijkstra(a);
					}
					cout<<"��ѡ���Ƿ����:1.���� 2.������"<<endl;
					cin>>ifcontinue;
				}
			}
			if(choice==2){         //�����Ȩͼ
				while(ifcontinue==1){
					cout<<"��ѡ�����:"<<endl;
			        cout<<"1.�����"<<endl;
			        cout<<"2.ɾ����"<<endl;
			        cout<<"3.Dijkstra�㷨"<<endl;
				    cin>>p;
					if(p==1){
						cout<<"�������������ߵ���㣬�յ��Ȩֵ:";
						cin>>a>>b>>cost;
						result1=g.insertEdge(a,b,cost);
						result2=g.insertEdge(b,a,cost);
						if(result1==1 && result2==1) cout<<"����ɹ�!"<<endl;
						       else cout<<"����ʧ��!"<<endl;
					}
					if(p==2){
						cout<<"����������ɾ���ߵ���㣬�յ�:";
						cin>>a>>b;
						ifdelete1=g.deleteEdge(a,b);
						ifdelete2=g.deleteEdge(b,a);
						if(ifdelete1 && ifdelete2) cout<<"ɾ���ɹ�!"<<endl;
						 else cout<<"ɾ��ʧ��!"<<endl;
					}
					if(p==3){
						cout<<"��ѡ��ʼ���:";
						cin>>a;
						g.Dijkstra(a);
					}
					cout<<"��ѡ���Ƿ����:1.���� 2.������"<<endl;
					cin>>ifcontinue;
				}
			}
		}
		cout<<"��ѡ���Ƿ����ʹ�ñ�ϵͳ:1.�� 2.��"<<endl;
		cin>>p;
		if(p==2) finish=false;
	}
}
