build:
	g++ -std=c++11 -o project2.out src/main.cpp src/Image.cpp src/HelperMethods.cpp

clean:
	rm -f project2.out
	rm -rf src/output/*