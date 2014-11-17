#include"RTtree_Index.h"

int deb_n_insert;
unordered_map<int,int> glo_hash;
unordered_set<int> glo_answers;
void RTtree_Index::BuildIndex(RTree<int, float, 2, float,IRTREE_NODE_MAX_BRANCH> &_rtree){
	//1. Insert All Locations
   int cur=0;
   double t_start,t_end;
   t_start=(double)clock();
   for(int z=0; z<(int)glo_query_flow.size(); z++){
	    float min[2]={glo_query_flow[z].rect.coord1_.x_,glo_query_flow[z].rect.coord1_.y_};
		float max[2]={glo_query_flow[z].rect.coord2_.x_,glo_query_flow[z].rect.coord2_.y_};
		_rtree.Insert(min,max, z);
		cur++;
	}
   //Line 0;
   deb_n_insert=0;
   //1.1 Assign_Rtree_Node_Parent;
    _rtree.m_root->rect.coord1_.x_=-180;
	_rtree.m_root->rect.coord1_.y_=-90;
	_rtree.m_root->rect.coord2_.x_=180;
	_rtree.m_root->rect.coord2_.y_=90;
	_rtree.m_root->parent=NULL;
   _DFS_AssignNodeParent(_rtree.m_root);
   //2.0 DFS Traverse The Tree
   _DFS_BuildIndex(_rtree.m_root,_rtree.m_root->m_level);
   t_end=(double)clock();
   cout<<"Index Time:"<<(t_end-t_start)*1000/CLOCKS_PER_SEC<<"ms"<<endl;
}
void RTtree_Index::_DFS_AssignNodeParent(RTree<int,float,2,float,IRTREE_NODE_MAX_BRANCH>::Node* _root){
	if(_root->m_level>0){
		for(int z=0;z<_root->m_count;z++){
			RTree<int,float,2,float,IRTREE_NODE_MAX_BRANCH>::Node* t_child=_root->m_branch[z].m_child;
			t_child->parent=_root;
			t_child->rect.coord1_.x_=_root->m_branch[z].m_rect.m_min[0];
			t_child->rect.coord1_.y_=_root->m_branch[z].m_rect.m_min[1];
			t_child->rect.coord2_.x_=_root->m_branch[z].m_rect.m_max[0];
			t_child->rect.coord2_.y_=_root->m_branch[z].m_rect.m_max[1];
			_DFS_AssignNodeParent(t_child);
		}
	}
	else{
		return;
	}

}
void RTtree_Index::_DFS_BuildIndex(RTree<int,float,2,float,IRTREE_NODE_MAX_BRANCH>::Node* _root,int _treelevel){
	if(_root->m_level>0){
		for(int z=0;z<_root->m_count;z++){
			RTree<int,float,2,float,IRTREE_NODE_MAX_BRANCH>::Node* t_child=_root->m_branch[z].m_child;
			_DFS_BuildIndex(t_child,_treelevel);
		}
	}
	else{
		   //2.1 For Every Subscription in Node, Update Index
		   for(int z=0;z<_root->m_count;z++){
		       RTree<int,float,2,float,IRTREE_NODE_MAX_BRANCH>::Node *leafNode=_root;
			   deb_n_insert++;
			   int queryid=(int)_root->m_branch[z].m_data;
			   vector<KeyValuePair<int,float> > t_spatialbound;
			   CalculateSpatialBound(glo_query_flow[queryid],t_spatialbound);
			   int pos=_treelevel-t_spatialbound.size();
			   if(pos<0){
				  for(int z=t_spatialbound.size()-1;z>=t_spatialbound.size()+pos;z--){
					   KeyValuePair<int,float> kp(queryid,0);
					   leafNode->sil_invertedlists.UnorderedAdd(t_spatialbound[z].key,kp);
				  }
				  int t_index=_treelevel-1;
				  while(t_index>=0){
					   KeyValuePair<int,float> kp(queryid,0);
					   leafNode->sil_invertedlists.UnorderedAdd(t_spatialbound[t_index].key,kp);
					   t_index--;
				       leafNode=leafNode->parent;
				  }
			  }
			  else if(pos==0){
				  int t_index=_treelevel-1;
				  while(t_index>=0){
					   KeyValuePair<int,float> kp(queryid,0);
					   leafNode->sil_invertedlists.UnorderedAdd(t_spatialbound[t_index].key,kp);
					   t_index--;
				       leafNode=leafNode->parent;
				  }
			  }
			  else{
				for(int z=0;z<pos;z++){
				    leafNode=leafNode->parent;
				}
				int t_index=t_spatialbound.size()-1;
				while(t_index>=0){
					KeyValuePair<int,float> kp(queryid,0);
					leafNode->sil_invertedlists.UnorderedAdd(t_spatialbound[t_index].key,kp);
					t_index--;
				    leafNode=leafNode->parent;
				}
			  }
		}
		return;
	}
}
void RTtree_Index::CalculateSpatialBound(GeoText_Query &_query, vector<KeyValuePair<int,float> > &_spatialbound){
	vector<KeyValuePair<int,float> > tmp;
	float sum=0;
	for(int z=0;z<_query.tokens.size();z++){
		KeyValuePair<int,float> _pair(_query.tokens[z],0);
		_spatialbound.push_back(_pair);
	}
}

int RTtree_Index::RTtree_Search(MESSAGE &_message, RTree<int,float,2,float,IRTREE_NODE_MAX_BRANCH> &_tree){
	glo_hash.clear();
	glo_answers.clear();
	int _treeheight=_tree.m_root->m_level;
	RTtree_Prune(_tree.m_root,_message,_treeheight);
	return glo_answers.size();
}
int RTtree_Index::RTtree_Prune(RTree<int,float,2,float,IRTREE_NODE_MAX_BRANCH>::Node *_node,MESSAGE &_message,int _treeheight){
	for(int z=0;z<_node->m_count;z++){
	    bool visitFlag=false;
		RTree<int,float,2,float,IRTREE_NODE_MAX_BRANCH>::Node *child=_node->m_branch[z].m_child;
		if(Geo::Overlap(child->rect,_message.rect)){
			 int t_treedepth=_treeheight-child->m_level;
			for(int zz=0;zz<_message.tokens.size();zz++){
				SortedList<int,float> *t_list=child->sil_invertedlists.GetSortedListFromKey(_message.tokens[zz]);	
				if(t_list!=NULL){
					for(int zzz=0;zzz<(int)t_list->list.size();zzz++){
					int _queryid=t_list->list[zzz].key;
			        unordered_map<int,int>::iterator it=glo_hash.find(_queryid);
					if(it==glo_hash.end())
						glo_hash[_queryid]=1;
					else glo_hash[_queryid]=glo_hash[_queryid]+1;
					int t_count=glo_hash[_queryid];
					int t_querysize=glo_query_flow[_queryid].tokens.size();
					if(!visitFlag && t_count==t_treedepth&& t_count<t_querysize&&child->m_level>0){
						visitFlag=true;
					}
					if(t_count==t_querysize&&Geo::Overlap(glo_query_flow[_queryid].rect,_message.rect))
						glo_answers.insert(_queryid);

				    }
			    }

		 }
	  }
	  if(visitFlag)
			RTtree_Prune(child,_message,_treeheight);
   }
}

