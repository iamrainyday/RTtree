objects=main.o RTtree_Index.o algo.o geo.o util.o    
rttree:$(objects)
	g++ -B/usr/lib/x86_64-linux-gnu -O3 $(objects) -o rttree
util.o:Util/util.cc Util/util.h Util/search.h
	g++ -O3 -c Util/util.cc -o util.o
geo.o:Geo/geo.cc Geo/geo.h
	g++ -O3 -c Geo/geo.cc -o geo.o
algo.o:algo.cc algo.h 
	g++ -O3 -c algo.cc -o algo.o
RTtree_Index.o:RTtree_Index.cc RTtree_Index.h RTree.h Global.h
	g++ -O3 -c RTtree_Index.cc -o RTtree_Index.o	
main.o: main.cc  util.o geo.o algo.o RTtree_Index.o
	g++ -O3 -c main.cc  -o main.o
clean:
	rm -rf *.o
