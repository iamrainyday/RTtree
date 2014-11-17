// $Id: quadtree.cc 5498 2012-03-16 14:13:31Z haowu $


#include "quadtree.h"
//


//


//
//
//

int assignId=0;
QuadtreeNeighborIterator::QuadtreeNeighborIterator(const Point& query,
    const QuadtreeNode& root)
    : query_(query), p_checker_(NULL)
{
  float dist = Geo::CalcMinDist(query_, root.br_);
  QueueEntry qe(0, (void*)&root, dist);
  queue_.push(qe);
}

//
//
//

QuadtreeNeighborIterator::QuadtreeNeighborIterator(const Point& query,
    const QuadtreeNode& root, const Checker& checker)
    : query_(query), p_checker_((Checker*)(&checker))
{
  float dist = Geo::CalcMinDist(query_, root.br_);
  QueueEntry qe(0, (void*)&root, dist);
  queue_.push(qe);
}

//
//
//

void QuadtreeNeighborIterator::Next(Point** pp_point, float* p_dist)
{
  while (true) {
    if (queue_.size() == 0) {
      *pp_point = NULL;
      break;
    }
    QueueEntry qe_top = queue_.top();
    queue_.pop();
    if (qe_top.type_ == 0) { // this is a quadtree node
      QuadtreeNode& node = *((QuadtreeNode*)qe_top.ptr_);
      if (node.pp_child_ != NULL) { // this is a non-leaf node
        for (int i = 0; i < 4; i++) {
          QuadtreeNode& child = *(node.pp_child_[i]);
          if (p_checker_ == NULL || p_checker_->CheckNode(child)) {
            float dist = Geo::CalcMinDist(query_, child.br_);
            QueueEntry qe(0, (void*)&child, dist);
            queue_.push(qe);
          }
        }
      } else { // this is a leaf node

//        if (qe_top.dist_ == 0) {
//          cout << "hahaha!!!!!!! " << node.id_ << endl;
//        }

        for (int i = 0; i < (int)node.zp_point_.size(); i++) {
          const Point& point = *(node.zp_point_[i]);
          if (p_checker_ == NULL || p_checker_->CheckPoint(point)) {
            QueueEntry qe(1, (void*)&point, Geo::CalcDist(query_, point));
            queue_.push(qe);
          }
        }
      }
    } else { // this is a point
      Point& point = *((Point*)qe_top.ptr_);
      if (p_checker_ == NULL || p_checker_->CheckPoint(point)) {
        if (pp_point != NULL) {
          *pp_point = (Point*)qe_top.ptr_;
        }
        if (p_dist != NULL) {
          *p_dist = qe_top.dist_;
        }
        break;
      }
    }
  }
}

//
//
//

void  Quadtree::Quadtree_Init(const S_Rectangle& br, QuadtreeNode** pp_root)
{
  *pp_root = new QuadtreeNode();
  QuadtreeNode& root = **pp_root;
  root.br_ = br;
}

//
//
//

void  Quadtree::Quadtree_Add(const Point& point, int m, int d, QuadtreeNode* p_root)
{
  QuadtreeNode& root = *p_root;
  if (root.pp_child_ != NULL) { // the root is a non-leaf node
    _Quadtree_Add(point, m, d, p_root);
  } 
  else { // the root is a leaf node
    root.zp_point_.push_back((Point*)&point);
    if ((int)root.zp_point_.size() > m && root.depth_ < d) {
      _Quadtree_Split(m, d, p_root);
    }
  }
}


void Quadtree::FixedQuadtree_Add(const Point& point,const int &d, QuadtreeNode* p_root,QuadtreeNode** _returnLeafNode){
	QuadtreeNode& root = *p_root;
  if (root.pp_child_ != NULL) { // the root is a non-leaf node
     _FixedQuadtree_Add(point,  d, p_root,_returnLeafNode);
  } 
  else { // the root is a leaf node
	root.zp_point_.push_back((Point*)&point);
    if (root.depth_ < d) {
      _FixedQuadtree_Split(d, p_root,_returnLeafNode);
	
    }
	else{
		*_returnLeafNode=p_root;
	}
	root.zp_point_.clear();
	
  }
}


void   Quadtree::_Quadtree_Split(int m, int d, QuadtreeNode* p_leaf_node)
{
  QuadtreeNode& root = *p_leaf_node;
  float rcx = (root.br_.coord1_.x_ + root.br_.coord2_.x_) / 2;
  float rcy = (root.br_.coord1_.y_ + root.br_.coord2_.y_) / 2;
  Coordinate c0(rcx, rcy);
  Coordinate c1 = Coordinate(root.br_.coord1_.x_, rcy);
  Coordinate c2 = Coordinate(rcx, root.br_.coord2_.y_);
  Coordinate c3 = Coordinate(root.br_.coord2_.x_, rcy);
  Coordinate c4 = Coordinate(rcx, root.br_.coord1_.y_);
  root.pp_child_ = new QuadtreeNode*[4];
  S_Rectangle z_br[4];
  z_br[0] = S_Rectangle(root.br_.coord1_, c0);
  z_br[1] = S_Rectangle(c1, c2);
  z_br[2] = S_Rectangle(c0, root.br_.coord2_);
  z_br[3] = S_Rectangle(c4, c3);
  for (int i = 0; i < 4; i++) {
    QuadtreeNode*& p_child = root.pp_child_[i];
    Quadtree_Init(z_br[i], &p_child);
    p_child->depth_ = root.depth_ + 1;
    p_child->p_parent_ = &root;
  }
  for (int i = 0; i < (int)root.zp_point_.size(); i++) {
    Point& point = *((Point*)root.zp_point_[i]);
    Quadtree_Add(point, m, d, &root);
  }
  root.zp_point_.clear();
}

void   Quadtree::_FixedQuadtree_Split( const int &d, QuadtreeNode* p_leaf_node,QuadtreeNode** _returnLeafNode)
{
  QuadtreeNode& root = *p_leaf_node;
  float rcx = (root.br_.coord1_.x_ + root.br_.coord2_.x_) / 2;
  float rcy = (root.br_.coord1_.y_ + root.br_.coord2_.y_) / 2;
  Coordinate c0(rcx, rcy);
  Coordinate c1 = Coordinate(root.br_.coord1_.x_, rcy);
  Coordinate c2 = Coordinate(rcx, root.br_.coord2_.y_);
  Coordinate c3 = Coordinate(root.br_.coord2_.x_, rcy);
  Coordinate c4 = Coordinate(rcx, root.br_.coord1_.y_);
  root.pp_child_ = new QuadtreeNode*[4];
  S_Rectangle z_br[4];
  z_br[0] = S_Rectangle(root.br_.coord1_, c0);
  z_br[1] = S_Rectangle(c1, c2);
  z_br[2] = S_Rectangle(c0, root.br_.coord2_);
  z_br[3] = S_Rectangle(c4, c3);
  for (int i = 0; i < 4; i++) {
    QuadtreeNode*& p_child = root.pp_child_[i];
    Quadtree_Init(z_br[i], &p_child);
    p_child->depth_ = root.depth_ + 1;
    p_child->p_parent_ = &root;
  }
  for (int i = 0; i < (int)root.zp_point_.size(); i++) {
    Point& point = *((Point*)root.zp_point_[i]);
    FixedQuadtree_Add(point,d, &root, _returnLeafNode);
  }
  root.zp_point_.clear();
}

//
void   Quadtree::_Quadtree_Add(const Point& point, int m, int d,
    QuadtreeNode* p_non_leaf_node)
{
  QuadtreeNode& root = *p_non_leaf_node;
  float rcx = (root.br_.coord1_.x_ + root.br_.coord2_.x_) / 2;
  float rcy = (root.br_.coord1_.y_ + root.br_.coord2_.y_) / 2;
  float x = point.coord_.x_;
  float y = point.coord_.y_;
  int j = 0;
  if (x < rcx && y <= rcy) j = 0;
  else if (x < rcx && y > rcy) j = 1;
  else if (x >= rcx && y > rcy) j = 2;
  else if (x >= rcx && y <= rcy) j = 3;
  Quadtree_Add(point, m, d, root.pp_child_[j]);
}

void   Quadtree::_FixedQuadtree_Add(const Point& point,const int &d,
    QuadtreeNode* p_non_leaf_node,QuadtreeNode** _returnLeafNode)
{
  QuadtreeNode& root = *p_non_leaf_node;
  float rcx = (root.br_.coord1_.x_ + root.br_.coord2_.x_) / 2;
  float rcy = (root.br_.coord1_.y_ + root.br_.coord2_.y_) / 2;
  float x = point.coord_.x_;
  float y = point.coord_.y_;
  int j = 0;
  if (x < rcx && y <= rcy) j = 0;
  else if (x < rcx && y > rcy) j = 1;
  else if (x >= rcx && y > rcy) j = 2;
  else if (x >= rcx && y <= rcy) j = 3;
  FixedQuadtree_Add(point, d, root.pp_child_[j],_returnLeafNode);
}

//

void  Quadtree::Quadtree_AssignIDs(QuadtreeNode* p_root)
{
 QuadtreeNode& root = *p_root;
  root.id_ =assignId;
  assignId++;
  if (root.pp_child_ != NULL) {
    for (int i = 0; i < 4; i++) {
      QuadtreeNode*& p_child = root.pp_child_[i];
      Quadtree_AssignIDs(p_child);
    }
  }
}

//
//
//

void  Quadtree::Quadtree_Find(const Point& query, const QuadtreeNode& root,
    QuadtreeNode** pp_leaf_node)
{
  QuadtreeNode* p_node = (QuadtreeNode*)&root;
  while (true) {
    if (p_node->pp_child_ != NULL) { // this is a non-leaf node
      float min_min_dist = 0;
      int i_min_min_dist = -1;
      for (int i = 0; i < 4; i++) {
        QuadtreeNode& child = *(p_node->pp_child_[i]);
        float min_dist = Geo::CalcMinDist(query, child.br_);
        if (i_min_min_dist == -1 || min_min_dist > min_dist) {
          i_min_min_dist = i;
          min_min_dist = min_dist;
        }
      }
      if (min_min_dist > 0) {
        pp_leaf_node = NULL;
        break;
      }
      p_node = p_node->pp_child_[i_min_min_dist];
    } else { // this is a leaf node
      *pp_leaf_node = p_node;
      break;
    }
  }
}

//
//
//

void  Quadtree::Quadtree_Destroy(QuadtreeNode* p_root)
{
  QuadtreeNode& root = *p_root;
  if (root.pp_child_ == NULL) { // the root is a leaf node
    root.zp_point_.clear();
  } else { // the root is a non-leaf node
    for (int i = 0; i < 4; i++) {
      QuadtreeNode*& p_child = root.pp_child_[i];
      Quadtree_Destroy(p_child);
    }
    delete[] root.pp_child_;
  }
  delete p_root;
}

//
//
//

void  Quadtree::Quadtree_Output(const QuadtreeNode& root, const string& filename)
{
  ofstream ofs(filename.c_str());
  ofs << "digraph G {" << endl;
  ofs << "  size    = \"30,30\"" << endl;
  ofs << "  rankdir = \"UD\";" << endl;
  int counter = 0;
  _Quadtree_Output(root, -1, &counter, ofs);
  ofs << "}" << endl;
  ofs.close();
}

//
//
//

int  Quadtree::Quadtree_GetNumPoints(const QuadtreeNode& root)
{
  int total = 0;
  if (root.pp_child_ != NULL) { // this is a non-leaf node
    for (int i = 0; i < 4; i++) {
      QuadtreeNode& child = *(root.pp_child_[i]);
      total += Quadtree_GetNumPoints(child);
    }
  } else { // this is a leaf node
    total += (int)root.zp_point_.size();
  }
  return total;
}

//
//
//

int  Quadtree::Quadtree_GetNumNodes(const QuadtreeNode& root)
{
  int total = 0;
  if (root.pp_child_ != NULL) { // this is a non-leaf node
    for (int i = 0; i < 4; i++) {
      QuadtreeNode& child = *(root.pp_child_[i]);
      total += Quadtree_GetNumNodes(child);
    }
  }
  return total + 1;
}

//
//
//

int  Quadtree::Quadtree_GetNumLeafNodes(const QuadtreeNode& root)
{
  int total = 0;
  if (root.pp_child_ != NULL) { // this is a non-leaf node
    for (int i = 0; i < 4; i++) {
      QuadtreeNode& child = *(root.pp_child_[i]);
      total += Quadtree_GetNumLeafNodes(child);
    }
  } else {
    return 1;
  }
  return total;
}

//
//
//

int   Quadtree::Quadtree_GetHeight(const QuadtreeNode& root)
{
  int sub_tree_height = 0;
  if (root.pp_child_ != NULL) { // this is a non-leaf node
    for (int i = 0; i < 4; i++) {
      QuadtreeNode& child = *(root.pp_child_[i]);
      int height = Quadtree_GetHeight(child);
      if (sub_tree_height < height) {
        sub_tree_height = height;
      }
    }
  }
  return sub_tree_height + 1;
}

//
//
//

int   Quadtree::Quadtree_GetSizeInByte(const QuadtreeNode& root)
{
  int sz = 0;
  sz += sizeof(int); // id_
  sz += sizeof(int); // depth_
  sz += sizeof(Coordinate); // coord_
  sz += sizeof(Dimension); // dim_
  sz += sizeof(QuadtreeNode*); // p_parent_
  sz += sizeof(QuadtreeNode**); // pp_child_
  if (root.pp_child_ != NULL) { // this is a non-leaf node
    for (int i = 0; i < 4; i++) {
      QuadtreeNode& child = *(root.pp_child_[i]);
      sz += Quadtree_GetSizeInByte(child);
    }
  }
  sz += root.zp_point_.size() * sizeof(Point*); // zp_point_
  return sz;
}


//
//
//



//
//
//


//
//
//

void  Quadtree::_Quadtree_Output(const QuadtreeNode& root, int pos, int* p_id,
    ofstream& ofs)
{
  int root_id = *p_id;
  //
  float rcx = (root.br_.coord1_.x_ + root.br_.coord2_.x_) / 2;
  float rcy = (root.br_.coord1_.y_ + root.br_.coord2_.y_) / 2;
  float w = root.br_.coord2_.x_ - root.br_.coord1_.x_;
  float h = root.br_.coord2_.y_ - root.br_.coord1_.y_;
  //
  string color_str = "#888888";
  if (pos == 0) {
    color_str = "#ff000088";
  } else if (pos == 1) {
    color_str = "#00ff0088";
  } else if (pos == 2) {
    color_str = "#0000ff88";
  } else if (pos == 3) {
    color_str = "#88008888";
  }
  if (root.pp_child_ == NULL) {
    ofs << "  node [shape=box];" << endl;
  } else {
    ofs << "  node [shape=ellipse];" << endl;
  }
  ofs << "  " << root_id << " [style=filled, fillcolor=\"" << color_str
      << "\", label=<";
  ofs << "<font color='gray'>";
  ofs << "n" << root_id << ":";
  ofs << "(" << Util::floatToString(rcx, 3) << ","
      << Util::floatToString(rcy, 3) << ")";
  ofs << "<br/>";
  ofs << Util::floatToString(w, 3) << "*" << Util::floatToString(h, 3);
  ofs << "</font>";
  if (root.pp_child_ == NULL) {
    for (int i = 0; i < (int)root.zp_point_.size(); i++) {
      const Point& point = *(root.zp_point_[i]);
      ofs << "<br/>";
      ofs << "(" << Util::floatToString(point.coord_.x_, 3) << ","
          << Util::floatToString(point.coord_.y_, 3) << ")";
    }
    ofs << ">];" << endl;
  } else {
    ofs << ">];" << endl;
    for (int i = 0; i < 4; i++) {
      QuadtreeNode*& p_child = root.pp_child_[i];
      (*p_id)++;
      int child_id = *p_id;
      _Quadtree_Output(*p_child, i, p_id, ofs);
      ofs << "  " << root_id << " -> " << child_id
          << " [style=\"setlinewidth(4)\"];" << endl;
    }
  }
}


