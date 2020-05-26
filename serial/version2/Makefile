CXX = icpc

bin/app: bin/main.o 
	mkdir -p bin/
	$(CXX) -o $@ $^ 

bin/main.o: main.cpp
	mkdir -p bin/
	$(CXX) -c $^ -o $@ 

clean:
	rm -rf bin/ *.o *.gch 