
#ifndef _ETC_KEYVALUEPAIR_H_
#define _ETC_KEYVALUEPAIR_H_

#include "../Util/base.h"

template<class KEY, class T, class Comp=std::less<T> >
struct KeyValuePair{
	KEY key;
	T value;
	Comp _comp;
	KeyValuePair(){
		
	}
	KeyValuePair(KEY _key, T _value):key(_key),value(_value){
		
	}
	bool operator <(const KeyValuePair &other) const {
		return _comp(value,other.value);
	}
	bool operator >(const KeyValuePair &other) const {
		if(_comp(other.value,value))
			return true;
		else false;
	}
	bool operator ==(const KeyValuePair &other) const{
		if(!_comp(other.value,value)&&!_comp(value,other.value))
			return true;
		else return false;
	}
};

#endif
