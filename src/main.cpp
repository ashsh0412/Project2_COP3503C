#include "Image.h"
#include "HelperMethods.h"
#include <iostream>
#include <filesystem>

int main() {

	// Task 1
	Image layer1("src/input/layer1.tga");
	Image pattern1("src/input/pattern1.tga");
	Image task1 = multiply(layer1, pattern1);
	task1.write("src/output/part1.tga");

	// Task 2
	Image layer2("src/input/layer2.tga");
	Image car("src/input/car.tga");
	Image task2 = subtract(car, layer2);
	task2.write("src/output/part2.tga");

	// Task 3
	Image pattern2("src/input/pattern2.tga");
	Image text("src/input/text.tga");
	Image temp3 = multiply(layer1, pattern2);
	Image task3 = screen(text, temp3);
	task3.write("src/output/part3.tga");

	// Task 4
	Image circles("src/input/circles.tga");
	Image temp4 = multiply(layer2, circles);
	Image task4 = subtract(temp4, pattern2);
	task4.write("src/output/part4.tga");

	// Task 5
	Image task5 = overlay(layer1, pattern1);
	task5.write("src/output/part5.tga");

	// Task 6
	Image task6 = addChannel(car, 200, 'g');
	task6.write("src/output/part6.tga");

	// Task 7
	Image task7 = scaleChannel(car, 4.0f, 'r');
	task7 = scaleChannel(task7, 0.0f, 'b');
	task7.write("src/output/part7.tga");

	// Task 8
	onlyChannel(car, 'r').write("src/output/part8_r.tga");
	onlyChannel(car, 'g').write("src/output/part8_g.tga");
	onlyChannel(car, 'b').write("src/output/part8_b.tga");

	// Task 9
	Image red("src/input/layer_red.tga");
	Image green("src/input/layer_green.tga");
	Image blue("src/input/layer_blue.tga");
	combineChannels(red, green, blue).write("src/output/part9.tga");

	// Task 10
	Image text2("src/input/text2.tga");
	flip180(text2).write("src/output/part10.tga");

	return 0;
}