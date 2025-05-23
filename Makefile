build:
	g++ -std=c++11 -o project2.out src/main.cpp src/Image.cpp src/HelperMethods.cpp

tasks:
	./project2.out output/part11.tga input/circles.tga multiply input/layer1.tga
	./project2.out output/part12.tga input/layer1.tga flip
	./project2.out output/part13.tga input/layer1.tga subtract input/layer2.tga

clean:
	rm -f project2.out
	rm -rf output/*