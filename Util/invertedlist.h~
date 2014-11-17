
#ifndef _ETC_INVERTEDLIST_H_
#define _ETC_INVERTEDLIST_H_


#include"../Util/base.h"
#include"../Util/search.h"
#include"../Util/keyvaluepair.h"



template<class KeyValuePair_Key, class KeyValuePair_Value, class Comp=less<KeyValuePair_Key> >
struct SortedList{
    
    
    struct Comp_key{
        public:
        Comp _comp;
        bool operator () (const  KeyValuePair<KeyValuePair_Key,KeyValuePair_Value> &m1,const  KeyValuePair<KeyValuePair_Key,KeyValuePair_Value> &m2) {
                return  _comp(m1.key,m2.key);
        }
	};

	

	vector<KeyValuePair<KeyValuePair_Key,KeyValuePair_Value> > list;
	
	SortedList(){
	}
	void Insert(const KeyValuePair<KeyValuePair_Key,KeyValuePair_Value>& _apair){
		if(list.empty()){
			list.push_back(_apair);
		}
		else{

			//Do binary Search
			typename vector<KeyValuePair<KeyValuePair_Key,KeyValuePair_Value> >::iterator it;
			Flag result=BinarySearch(_apair,list.begin(),list.end(),&it);
			list.insert(it,_apair);
		}
	}
	
	void UnorderedInsert(const KeyValuePair<KeyValuePair_Key,KeyValuePair_Value>& _apair){
			list.push_back(_apair);
	}
    
   // return the KeyValuePair which first greater than _apair
   void  SL_BinarySearch_Value(KeyValuePair<KeyValuePair_Key,KeyValuePair_Value> &_apair){
			typename vector<KeyValuePair<KeyValuePair_Key,KeyValuePair_Value> >::iterator it;
			Flag result=BinarySearch(_apair,list.begin(),list.end(),&it);
            if(it==list.end())
                   return;
			_apair.key=it->key;
           
	}

bool SL_BinarySearch_KEY(const KeyValuePair_Key &_key,int *pos){
      
		KeyValuePair<KeyValuePair_Key,KeyValuePair_Value> _apair;
        _apair.key=_key;		
        Comp_key comp_key;
		typename vector<KeyValuePair<KeyValuePair_Key,KeyValuePair_Value> >::iterator _it;
		if(SUCCESS==BinarySearch(_apair,list.begin(),list.end(), comp_key,&_it)){
		    *pos=_it-list.begin();
			return true;
        }
		else{
           *pos=_it-list.begin();
           return false;
		}
	}
	
	void Delete(){
	}
 
};
template<class Key, class KeyValuePair_Key, class KeyValuePair_Value, class CompKey=less<Key> >
class SortedInvertedList{
	 
	public:
	  map<Key,SortedList<KeyValuePair_Key,KeyValuePair_Value>,CompKey> lists;
	  void Clear();
      void Add(const Key& _key, const KeyValuePair<KeyValuePair_Key,KeyValuePair_Value>& _item);
	  void UnorderedAdd(const Key &_key, const KeyValuePair<KeyValuePair_Key,KeyValuePair_Value> &_item);
	  void Delete(const Key &_key, const KeyValuePair_Key &_item);
	SortedList<KeyValuePair_Key,KeyValuePair_Value>* GetSortedListFromKey( const Key& _key );
	  int GetSortedListSizeFromKey(const Key& _key);
	  
};


template<class Key, class KeyValuePair_Key, class KeyValuePair_Value, class CompKey>
void SortedInvertedList<Key,KeyValuePair_Key,KeyValuePair_Value,CompKey>::Add(const Key& _key, const KeyValuePair<KeyValuePair_Key,KeyValuePair_Value>& _item){
	typename map<Key,SortedList<KeyValuePair_Key,KeyValuePair_Value>,CompKey>::iterator t_list=lists.find(_key);
	if(lists.end()==t_list){
		//Insert a new sortedList
		SortedList<KeyValuePair_Key,KeyValuePair_Value> t_new;
		t_new.Insert(_item);
		lists.insert(make_pair(_key,t_new));
	    
	}
	else{
		SortedList<KeyValuePair_Key,KeyValuePair_Value>& t=t_list->second;
		t.Insert(_item);
	}
}
template<class Key, class KeyValuePair_Key, class KeyValuePair_Value, class CompKey>
void SortedInvertedList<Key,KeyValuePair_Key,KeyValuePair_Value,CompKey>::UnorderedAdd(const Key& _key, const KeyValuePair<KeyValuePair_Key,KeyValuePair_Value>& _item){
	
	typename map<Key,SortedList<KeyValuePair_Key,KeyValuePair_Value>,CompKey>::iterator t_list=lists.find(_key);
	if(lists.end()==t_list){
		//Insert a new sortedList
		SortedList<KeyValuePair_Key,KeyValuePair_Value> t_new;
		t_new.UnorderedInsert(_item);
		lists.insert(make_pair(_key,t_new));
	    
	}
	else{
		SortedList<KeyValuePair_Key,KeyValuePair_Value>& t=t_list->second;
		t.UnorderedInsert(_item);
	}
	
}

template<class Key, class KeyValuePair_Key, class KeyValuePair_Value, class CompKey>
void SortedInvertedList<Key,KeyValuePair_Key,KeyValuePair_Value,CompKey>::Delete(const Key& _key,const KeyValuePair_Key& _item_key){


}

template<class Key, class KeyValuePair_Key, class KeyValuePair_Value, class CompKey>
 SortedList<KeyValuePair_Key,KeyValuePair_Value>* SortedInvertedList<Key,KeyValuePair_Key,KeyValuePair_Value,CompKey>::GetSortedListFromKey( const Key& _key ){
   typename	map<Key,SortedList<KeyValuePair_Key,KeyValuePair_Value>,CompKey>::iterator t_list=lists.find(_key);
	if(lists.end()==t_list){
	   return NULL;
	}
	else{
         return &t_list->second;
	}
}
 template<class Key, class KeyValuePair_Key, class KeyValuePair_Value, class CompKey>
 void SortedInvertedList<Key,KeyValuePair_Key,KeyValuePair_Value,CompKey>::Clear(){
     lists.clear();
}
template<class Key, class KeyValuePair_Key, class KeyValuePair_Value, class CompKey>
int SortedInvertedList<Key,KeyValuePair_Key,KeyValuePair_Value,CompKey>::GetSortedListSizeFromKey(const Key& _key){
	SortedList<KeyValuePair_Key,KeyValuePair_Value>* temp=GetSortedListFromKey(_key);
	if(temp==NULL)
		return 0;
	else{
		return temp->list.size();
	}
}

#endif
