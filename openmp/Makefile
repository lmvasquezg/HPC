CXXFLAGS = -qopenmp
CXX = icpc

bin/app: main.cpp 
	mkdir -p bin/
	$(CXX) -c ${CXXFLAGS} -o "$@" "$^"  

clean:
	rm -rf bin/ *.o *.gch 
