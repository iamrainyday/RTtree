// $Id: geo.cc 5444 2012-03-11 11:41:41Z haowu $

/*
 * common.cc
 *
 *  Created on: Jul 1, 2011
 *      Author: Hao Wu
 */

#include "../Geo/geo.h"
//
#include <cmath>
#include <algorithm>


using namespace std;

//
//
//

/*
float Geo::CalcDist(const Point& point1, const Point& point2)
{
  float dx = point2.coord_.x_ - point1.coord_.x_;
  float dy = point2.coord_.y_ - point1.coord_.y_;
  return sqrt(pow(dx, 2) + pow(dy, 2));
}

*/
//
//
//

float Geo::CalcMinDist(const Point& point, const S_Rectangle& rect)
{
  /*
   * This code is partially copied and modified from http://goo.gl/pPrHj
   */
  float x1 = rect.coord1_.x_;
  float y1 = rect.coord1_.y_;
  float x2 = rect.coord2_.x_;
  float y2 = rect.coord2_.y_;
  float x = point.coord_.x_;
  float y = point.coord_.y_;
  //
  float dx1 = x - x1;
  float dx2 = x - x2;
  float dy1 = y - y1;
  float dy2 = y - y2;
  //
  if (dx1 * dx2 < 0) { // x is between x1 and x2
    if (dy1 * dy2 < 0) { // (x,y) is inside the rectangle
      return 0;
    }
    return min(fabs(dy1), fabs(dy2));
  }
  if (dy1 * dy2 < 0) { // y is between y1 and y2
    // we don't have to test for being inside the rectangle, it's already tested.
    return min(fabs(dx1), fabs(dx2));
  }
  float dist_ll = CalcDist(Point(Coordinate(x1, y1)), point);
  float dist_ul = CalcDist(Point(Coordinate(x1, y2)), point);
  float dist_lr = CalcDist(Point(Coordinate(x2, y1)), point);
  float dist_ur = CalcDist(Point(Coordinate(x2, y2)), point);
  return min(min(dist_ll, dist_ul), min(dist_lr, dist_ur));
}

//
//
//
/*
float Geo::CalcSpatialSimilarity(float _euc_dist, float _max_spatial_dist){
	if(_euc_dist>=_max_spatial_dist)
		return 0;
	else return 1-_euc_dist/_max_spatial_dist;
}
*/
float Geo::CalcExpandedRectanglePruningAbility(const S_Rectangle &_br,const S_Rectangle &_rootMBR,float _expandspatialsimilarity,float _glo_maxeucdist,float _glo_maxarea){
	//1. Calulate Euc Dist From spatial similarity
	float t_euc_dist=(1-_expandspatialsimilarity)*_glo_maxeucdist;
	float x_min=max<float>(_br.coord1_.x_-t_euc_dist,_rootMBR.coord1_.x_);
	float y_min=max<float>(_br.coord1_.y_-t_euc_dist,_rootMBR.coord1_.y_);
	float x_max=min<float>(_br.coord2_.x_+t_euc_dist,_rootMBR.coord2_.x_);
	float y_max=min<float>(_br.coord2_.y_+t_euc_dist,_rootMBR.coord2_.y_);
	return (x_max-x_min)*(y_max-y_min)/_glo_maxarea;

}


float Geo::CalcMaxDist(const Point& point, const S_Rectangle& rect)
{
  float x1 = rect.coord1_.x_;
  float y1 = rect.coord1_.y_;
  float x2 = rect.coord2_.x_;
  float y2 = rect.coord2_.y_;
  float x = point.coord_.x_;
  float y = point.coord_.y_;
  float dist_ll = CalcDist(Point(Coordinate(x1, y1)), point);
  float dist_ul = CalcDist(Point(Coordinate(x1, y2)), point);
  float dist_lr = CalcDist(Point(Coordinate(x2, y1)), point);
  float dist_ur = CalcDist(Point(Coordinate(x2, y2)), point);
  return max(max(dist_ll, dist_ul), max(dist_lr, dist_ur));
}

float Geo::CalMinDistInside(const Point &point, const S_Rectangle &rect){
	float l=abs(point.coord_.x_-rect.coord1_.x_);
	float r=abs(point.coord_.x_-rect.coord2_.x_);
	float b=abs(point.coord_.y_-rect.coord1_.y_);
	float u=abs(point.coord_.y_-rect.coord2_.y_);
	return min(min(l,r),min(b,u));
}

//
//
//

bool Geo::Contain(const Point& point, const S_Rectangle& rect)
{
  float x1 = rect.coord1_.x_;
  float y1 = rect.coord1_.y_;
  float x2 = rect.coord2_.x_;
  float y2 = rect.coord2_.y_;
  float x = point.coord_.x_;
  float y = point.coord_.y_;
  return x >= x1 && x < x2 && y >= y1 && y < y2;
}

//
//
//

bool Geo::Contain(const S_Rectangle& rect_small, const S_Rectangle& rect_large)
{
  float x11 = rect_small.coord1_.x_;
  float y11 = rect_small.coord1_.y_;
  float x12 = rect_small.coord2_.x_;
  float y12 = rect_small.coord2_.y_;
  //
  float x21 = rect_large.coord1_.x_;
  float y21 = rect_large.coord1_.y_;
  float x22 = rect_large.coord2_.x_;
  float y22 = rect_large.coord2_.y_;
  //
  bool b1 = x21 <= x11 && x12 <= x22;
  bool b2 = y21 <= y11 && y12 <= y22;
  return b1 && b2;
}

//
//
//

bool Geo::Overlap(const S_Rectangle& rect1, const S_Rectangle& rect2)
{
  float x11 = rect1.coord1_.x_;
  float y11 = rect1.coord1_.y_;
  float x12 = rect1.coord2_.x_;
  float y12 = rect1.coord2_.y_;
  //
  float x21 = rect2.coord1_.x_;
  float y21 = rect2.coord1_.y_;
  float x22 = rect2.coord2_.x_;
  float y22 = rect2.coord2_.y_;
  //
  bool b1 = x21 < x12 && x11 < x22;
  bool b2 = y21 < y12 && y11 < y22;
  return b1 && b2;
}

//
///
////
/////
////
///
//
//
///
////
/////
////
///
//
//
///
////
/////
////
///
//
//
///
////
/////
////
///
//
//
///
////
/////
////
///
//
//
///
////
/////
////
///
//
//
///
////
/////
////
///
//
