#include <iostream>
#include "./imgLib/imgTransform.hpp"
int main() {
    sf::Image base;
    base.loadFromFile("../test.png");
    sf::Image res1 = imgTransform::toGrey(base);
    res1 = imgTransform::filtrGaussowski(res1);
    res1 = imgTransform::filtrGaussowski(res1);
    res1 = imgTransform::filtrGaussowski(res1);
    res1 = imgTransform::filtrGaussowski(res1);
    res1 = imgTransform::filtrGaussowski(res1);
    res1 = imgTransform::filtrGaussowski(res1);
    res1.saveToFile("../res.png");
   sf::Image res = imgTransform::transformEdgeFromGreyPrewitts(res1);
    res.saveToFile("../resPrewitts.png");
    res = imgTransform::transformEdgeFromGreySobel(res1);
    res.saveToFile("../resSobel.png");
    res = imgTransform::transformEdgeFromGreyLaplacian(res1);
    res.saveToFile("../resLaplacian.png");
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
