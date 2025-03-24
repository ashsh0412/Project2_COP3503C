#include "Image.h"
#include "Filters.h"

int main() {
    Image layer1, layer2, pattern1, pattern2, text, car, circles;
    layer1.load("input/layer1.tga");
    layer2.load("input/layer2.tga");
    pattern1.load("input/pattern1.tga");
    pattern2.load("input/pattern2.tga");
    text.load("input/text.tga");
    car.load("input/car.tga");
    circles.load("input/circles.tga");

    // Task 1
    Multiply(layer1, pattern1).save("output/part1.tga");

    // Task 2
    Subtract(car, layer2).save("output/part2.tga");

    // Task 3
    Image tmp = Multiply(layer1, pattern2);
    Screen(text, tmp).save("output/part3.tga");

    // Task 4
    Image tmp4 = Multiply(layer2, circles);
    Subtract(tmp4, pattern2).save("output/part4.tga");

    // Task 5
    Overlay(layer1, pattern1).save("output/part5.tga");

    // Task 6
    AddChannel(car, 200, 'g').save("output/part6.tga");

    // Task 7
    Image carScaled = car;
    carScaled = ScaleChannel(carScaled, 4, 'r');
    carScaled = ScaleChannel(carScaled, 0, 'b');
    carScaled.save("output/part7.tga");

    // Task 8
    OnlyChannel(car, 'r').save("output/part8_r.tga");
    OnlyChannel(car, 'g').save("output/part8_g.tga");
    OnlyChannel(car, 'b').save("output/part8_b.tga");

    // Task 9
    Image red, green, blue;
    red.load("input/layer_red.tga");
    green.load("input/layer_green.tga");
    blue.load("input/layer_blue.tga");
    CombineChannels(red, green, blue).save("output/part9.tga");

    // Task 10
    Image text2;
    text2.load("input/text2.tga");
    Flip180(text2).save("output/part10.tga");

    return 0;
}