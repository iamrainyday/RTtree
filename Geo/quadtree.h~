// $Id: quadtree.h 5444 2012-03-11 11:41:41Z haowu $

#ifndef _ETC_GEO_QUADTREE_H_
#define _ETC_GEO_QUADTREE_H_

#include "../Geo/geo.h"
#include "../Util/base.h"
#include "../Util/util.h"
#include "../Util/invertedlist.h"
#include "../DistanceAwarePrefixInvertedList.h"
//
#include <cassert>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

//
//
//

struct QuadtreeNode
{
  QuadtreeNode()
	  : depth_(0), p_parent_(NULL), pp_child_(NULL)
  {
  }
  //
  int id_;
  //
  int depth_;
  S_Rectangle br_; // bounding rectangle
  //
  QuadtreeNode* p_parent_;
  QuadtreeNode** pp_child_;
  //
  vector<Point*> zp_point_;

  //DistanceAwarePrefixLength
  
  HierarchyDistanceAwarePrefixInvertedLists hdapil;

};

//
//
//

class QuadtreeNeighborIterator
{
public:
  //
  class Checker
  {
  public:
    virtual bool CheckNode(const QuadtreeNode& node) = 0;
    virtual bool CheckPoint(const Point& point) = 0;
  };
  //
  QuadtreeNeighborIterator(const Point& query, const QuadtreeNode& root);
  QuadtreeNeighborIterator(const Point& query, const QuadtreeNode& root,
      const Checker& checker);
  bool HasNext() const;
  void Next(Point** pp_point, float* p_dist);
  //
protected:
  //
  struct QueueEntry
  {
    QueueEntry()
    {
    }
    //
    QueueEntry(int type, void* ptr, float dist)
        : type_(type), ptr_(ptr), dist_(dist)
    {
    }
    //
    int type_; // type_ == 0: node; type_ == 1: point.
    void* ptr_; // ptr_ refers to a node or a point.
    float dist_;
    //
    bool operator > (const QueueEntry& qe) const
    {
      return this->dist_ > qe.dist_;
    }
    //
    bool operator < (const QueueEntry& qe) const
    {
      return this->dist_ < qe.dist_;
    }
  };
  //
  Point query_;
  priority_queue<QueueEntry, vector<QueueEntry>, greater<QueueEntry> > queue_;
  //
  Checker* p_checker_;
};

//
//
//
class Quadtree{

/*******************************
Providing two kind of quadtrees here:
1. Quadtree_xxx: normal quadtree. i.e when a grid receive more than m points, then it will split

2. FixedQuadtree_xxx: quadtree with fixed level d. i.e the query was initilized with d level grids




********************************/
public:
/******Normal Quadtree**/
void Quadtree_Add(const Point& point, int m, int d, QuadtreeNode* p_root);



/****** Fixed Quadtree**/
void FixedQuadtree_Add(const Point& point,const int &d, QuadtreeNode* p_root,QuadtreeNode** _returnLeafNode);


/*********common quadtree function***********/
void Quadtree_AssignIDs(QuadtreeNode* p_root);
void Quadtree_Init(const S_Rectangle& br, QuadtreeNode** pp_root);
void Quadtree_Find(const Point& query, const QuadtreeNode& root,
    QuadtreeNode** pp_leaf_node);
void Quadtree_Destroy(QuadtreeNode* p_root);
void Quadtree_Output(const QuadtreeNode& root, const string& filename);
int Quadtree_GetNumPoints(const QuadtreeNode& root);
int Quadtree_GetNumNodes(const QuadtreeNode& root);
int Quadtree_GetNumLeafNodes(const QuadtreeNode& root);
int Quadtree_GetHeight(const QuadtreeNode& root);
int Quadtree_GetSizeInByte(const QuadtreeNode& root);

//
//
protected:
	//Quadtree
void _Quadtree_Split(int m, int d, QuadtreeNode* p_leaf_node);
void _Quadtree_Add(const Point& point, int m, int d,
    QuadtreeNode* p_non_leaf_node);


//Fixed Quadtree
void _FixedQuadtree_Split(const int &d, QuadtreeNode* p_leaf_node,QuadtreeNode** _returnLeafNode);
void _FixedQuadtree_Add(const Point& point,const int &d,
    QuadtreeNode* p_non_leaf_node,QuadtreeNode** _returnLeafNode);
void _Quadtree_Output(const QuadtreeNode& root, int pos, int* p_id,
    ofstream& ofs);
};

//
//
//

#endif
