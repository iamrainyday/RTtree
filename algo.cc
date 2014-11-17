#include"algo.h"


S_Rectangle rootMBR(-180,-90,180,90);
vector<GeoText_Query> glo_query_flow;
vector<MESSAGE> glo_message_flow;



void Glo_LoadSubscriptionFlow(string _filepath,int _topK){
	cout<<_filepath<<endl;
	ifstream _fqueryflow(_filepath.c_str());
	string line="";
	if(_topK==-1)
		_topK=2147483640;
	int count=1;
	while(!_fqueryflow.eof()){
		getline(_fqueryflow,line);
		line=Util:: Trim(line);
		vector<string> tks;
		Util::Split(line," ",&tks);
		if((int)tks.size()<5)
			continue;
		int id=atoi(tks[0].c_str());
		float _x1=(float)atof(tks[1].c_str());
		float _y1=(float)atof(tks[2].c_str());
		float _x2=(float)atof(tks[3].c_str());
		float _y2=(float)atof(tks[4].c_str());
		vector<int> _tokenset;
	    for(int z=5;z<(int)tks.size();z++){
				int token=atoi(tks[z].c_str());
				_tokenset.push_back(token);
		}
		GeoText_Query gt(id,_tokenset,_x1,_y1,_x2,_y2);
		glo_query_flow.push_back(gt);
		count++;
		if(count>_topK)
			break;
		
	}
	_fqueryflow.close();
}
void Glo_LoadMessageFlow(string _filepath,int _topK){
	ifstream _fmessageflow(_filepath.c_str());
	string line="";
	int count=1;
	if(_topK==-1)
		_topK=2147483640;
	while(!_fmessageflow.eof()){
		getline(_fmessageflow,line);
		line=Util:: Trim(line);
		vector<string> tks;
		Util::Split(line," ",&tks);
		if((int)tks.size()<5)
			continue;
		int id=atoi(tks[0].c_str());
		float _x1=(float)atof(tks[1].c_str());
		float _y1=(float)atof(tks[2].c_str());
		float _x2=(float)atof(tks[1].c_str());
		float _y2=(float)atof(tks[2].c_str());
		vector<int> _tokenset;
		_tokenset.push_back(-1);
		for(int z=5;z<(int)tks.size();z++){
			int token=atoi(tks[z].c_str());
			_tokenset.push_back(token);
		}
		 MESSAGE t_message(id,_tokenset,_x1,_y1,_x2,_y2);
		 glo_message_flow.push_back(t_message);
         count++;
		if(count>_topK)
			break;
	}
	_fmessageflow.close();
}
