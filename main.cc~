#include"algo.h"
#include<sys/time.h>
#include"Geo/geo.h"
#include"Global.h"
#include"RTtree_Index.h"


//timer //每1s 发送1000个query, 每100-110秒测100个message

int timer;
int n_message_index;
double glo_inserttime;
int glo_init_memory_size;

RTree<int, float, 2, float,IRTREE_NODE_MAX_BRANCH> *tree;


int main(int argc ,char *argv[])
{
 
	string suf_sub(argv[1]);
	int scalnum_sub=atoi(argv[2]);
	string suf_message(argv[3]);
	int scalnum_message=atoi(argv[4]);

	
	string subpath="../Data/"+suf_sub;
	string messagepath="../Data/"+suf_message;
	Glo_LoadSubscriptionFlow(subpath,scalnum_sub);
	Glo_LoadMessageFlow(messagepath,scalnum_message);
	tree=new RTree<int, float, 2, float,IRTREE_NODE_MAX_BRANCH>;
	RTtree_Index rttree;
    rttree.BuildIndex(*tree);
	int glo_result=0;
	cout<<"Data Set:"<<subpath<<" Scal:"<<scalnum_sub<<endl;
	double start,end;
	start=(double)clock();
	for(int z=0;z<100;z++){
		 glo_result+=rttree.RTtree_Search(glo_message_flow[z],*tree);
	}
	end=(double)clock();
  cout<<"Result:"<<glo_result<<endl;
   cout<<"Search:"<<(end-start)*1000/CLOCKS_PER_SEC<<"ms"<<endl;
 cout<<endl;
  return 0;
}
