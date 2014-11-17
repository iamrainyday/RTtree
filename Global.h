#ifndef _GLO_GLOBAL_H_
#define _GLO_GLOBAL_H_




//DEBUG INFORMATIOn


#include"Util/base.h"
#include"Util/keyvaluepair.h"
#include"Geo/geo.h"
//#include"Geo/quadtree.h"
#include <assert.h>


//#define _DEBUG
/***Global Structure Are Defined Here*/

#define GLO_ASSERT assert
#define MIN_FLOAT_VALUE 0.000001
#define INF 9999999999

//Global Parmeters

#define IRTREE_NODE_MAX_BRANCH 100
#define GLO_N_UNIONPREFIX_UNITS 10
#define GLO_TOKENORDER "e_des"  //e_des or e_as
#define GLO_PREFIXSCHEMA "e_fix"
#define GLO_INSERT_K_ 10
#define GLO_MAX_EUC_DIST 100



//algo.c
extern S_Rectangle rootMBR;
//extern float GLO_MAX_EUC_DIST;
extern vector<GeoText_Query> glo_query_flow;
extern vector<MESSAGE> glo_message_flow;






/*** global functions***********/
extern void Glo_LoadSubscriptionFlow(string _filepath,int _topK);
extern void Glo_LoadMessageFlow(string _filepath,int _topK);

#endif
