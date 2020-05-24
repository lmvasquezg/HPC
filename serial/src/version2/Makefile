CXXFLAGS = -qopenmp
CXX = icpc

bin/app: bin/main.o 
	mkdir -p bin/
	$(CXX) -o $@ $^ $(CXXFLAGS)

bin/main.o: main.cpp
	mkdir -p bin/
	$(CXX) -c $^ -o $@ $(CXXFLAGS) 

clean:
	rm -rf bin/ *.o *.gch transcoder