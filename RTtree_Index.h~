#ifndef _H_RTTREEINDEX_
#define _H_RTTREEINDEX_
#include"RTree.h"
#include"Global.h"
class RTtree_Index{
public:
	void BuildIndex(RTree<int, float, 2, float,IRTREE_NODE_MAX_BRANCH> &tree);
int RTtree_Search(MESSAGE &_message, RTree<int,float,2,float,IRTREE_NODE_MAX_BRANCH> &_tree);
protected:
	void _DFS_AssignNodeParent(RTree<int,float,2,float,IRTREE_NODE_MAX_BRANCH>::Node* _root);
	void _DFS_BuildIndex(RTree<int,float,2,float,IRTREE_NODE_MAX_BRANCH>::Node* _root,int _n_treelevel);
	void CalculateSpatialBound(GeoText_Query &_query, vector<KeyValuePair<int,float> > &_spatialbound);
int RTtree_Prune(RTree<int,float,2,float,IRTREE_NODE_MAX_BRANCH>::Node *_node,MESSAGE &_message,int _treeheight);
};


#endif
