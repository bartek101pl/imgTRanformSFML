//
// Created by Bartosz Śnieg on 25.12.2021.
//

#ifndef IMGTRANFORMSFML_IMGTRANSFORM_HPP
#define IMGTRANFORMSFML_IMGTRANSFORM_HPP
#include <SFML/Graphics/Image.hpp>

class imgTransform {
public:
    static sf::Image toGrey(sf::Image &src);
    static sf::Image transformEdgeFromGreySobel(sf::Image &src);
    static sf::Image transformEdgeFromGreyPrewitts(sf::Image &src);
    static sf::Image transformEdgeFromGreyLaplacian(sf::Image &src);
private:
    static sf::Color colorToGrey(sf::Color src);
    static sf::Color getGreyColor(int x);
    static int  colorToInt(sf::Color src);
    static int multiplayArray(int mask[3][3],int img[3][3]);
    static sf::Image transformEdge(int filtrx[3][3], int filtry[3][3], sf::Image &src);
};


#endif //IMGTRANFORMSFML_IMGTRANSFORM_HPP
