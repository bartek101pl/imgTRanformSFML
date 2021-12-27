//
// Created by Bartosz Śnieg on 25.12.2021.
//

#include "imgTransform.hpp"
#include "math.h"
sf::Image imgTransform::toGrey(sf::Image &src) {
    sf::Image res;
    res.create(src.getSize().x,src.getSize().y,sf::Color::Black);
    for (int i = 0; i < src.getSize().y; ++i) {
        for (int j = 0; j < src.getSize().x; ++j) {
            res.setPixel(j,i,imgTransform::colorToGrey(src.getPixel(j,i)));
        }
    }

    return  res;
}

sf::Color imgTransform::colorToGrey(sf::Color src) {
    int a =imgTransform::colorToInt(src);
    return sf::Color(a,a,a);
}




sf::Color imgTransform::getGreyColor(int x) {
    return sf::Color(x,x,x);
}

int imgTransform::colorToInt(sf::Color src) {
    return (src.r/3)+(src.b/3)+(src.g/3);
}

int imgTransform::multiplayArray(int (*mask)[3], int (*img)[3]) {
    int a = 0;
    for(int i = 0;i<3;i++)
    {
        for (int j = 0; j < 3; ++j) {
            a+=mask[i][j]*img[i][j];
        }
    }
    return a;
}

sf::Image imgTransform::transformEdge(int (*filtrx)[3], int (*filtry)[3], sf::Image &src) {
    sf::Image res;
    res.create(src.getSize().x,src.getSize().y,sf::Color::Black);

    for (int i = 1; i < src.getSize().x-1; ++i) {
        for (int j = 1; j < src.getSize().y-1; ++j) {
            int matriX[3][3] ={{imgTransform::colorToInt(src.getPixel(i-1,j-1)),imgTransform::colorToInt(src.getPixel(i-1,j)),imgTransform::colorToInt(src.getPixel(i-1,j+1))},
                               {imgTransform::colorToInt(src.getPixel(i,j-1)),imgTransform::colorToInt(src.getPixel(i,j)),imgTransform::colorToInt(src.getPixel(i,j+1))},
                               {imgTransform::colorToInt(src.getPixel(i+1,j-1)),imgTransform::colorToInt(src.getPixel(i+1,j)),imgTransform::colorToInt(src.getPixel(i+1,j+1))}};

            int withX = imgTransform::multiplayArray(filtrx,matriX);
            int withY = imgTransform::multiplayArray(filtry,matriX);
            int r = sqrt(pow(withX,2)+ pow(withY,2))-10;
            r = (r<0)?0:r;
            res.setPixel(i,j,imgTransform::getGreyColor(r));

        }
    }
    return res;
}
sf::Image imgTransform::transformEdgeFromGreySobel(sf::Image &src) {
    int filtrx[3][3] = {{1,0,-1},{2,0,-2},{1,0,-1}};
    int filtry[3][3] = {{1,2,1},{0,0,0},-1,-2,-1};


    return imgTransform::transformEdge(filtrx,filtry,src);
}

sf::Image imgTransform::transformEdgeFromGreyPrewitts(sf::Image &src) {
    int filtrx[3][3] = {{1,0,-1},{1,0,-1},{1,0,-1}};
    int filtry[3][3] = {{1,1,1},{0,0,0},-1,-1,-1};


    return imgTransform::transformEdge(filtrx,filtry,src);
}

sf::Image imgTransform::transformEdgeFromGreyLaplacian(sf::Image &src) {
    int filtrx[3][3] = {{0,-1,0},{-1,4,-1},{0,-1,0}};
    int filtry[3][3] = {{-1,-1,-1},{-1,0,-1},-1,-1,-1};


    return imgTransform::transformEdge(filtrx,filtry,src);
}

sf::Image imgTransform::filtrGaussowski(sf::Image &src) {
    int filter[5][5] = {{1,4,7,4,1},{4,16,26,16,4},{7,26,41,26,7},{4,16,26,16,4},{1,4,7,4,1}};

    sf::Image res = src;
//    res.create(src.getSize().x-2,src.getSize().y-2,sf::Color::Black);

    for (int i = 2; i < src.getSize().x-2; ++i) {
        for (int j = 2; j < src.getSize().y-2; ++j) {
            int matriX[5][5] ={{imgTransform::colorToInt(src.getPixel(i-2,j-2)),imgTransform::colorToInt(src.getPixel(i-2,j-1)),imgTransform::colorToInt(src.getPixel(i-2,j)),imgTransform::colorToInt(src.getPixel(i-2,j+1)),imgTransform::colorToInt(src.getPixel(i-2,j+2))},
                               {imgTransform::colorToInt(src.getPixel(i-1,j-2)),imgTransform::colorToInt(src.getPixel(i-1,j-1)),imgTransform::colorToInt(src.getPixel(i-1,j)),imgTransform::colorToInt(src.getPixel(i-1,j+1)),imgTransform::colorToInt(src.getPixel(i-1,j+2))},
                               {imgTransform::colorToInt(src.getPixel(i,j-2)),imgTransform::colorToInt(src.getPixel(i,j-1)),imgTransform::colorToInt(src.getPixel(i,j)),imgTransform::colorToInt(src.getPixel(i,j+1)),imgTransform::colorToInt(src.getPixel(i,j+2))},
                               {imgTransform::colorToInt(src.getPixel(i+1,j-2)),imgTransform::colorToInt(src.getPixel(i+1,j-1)),imgTransform::colorToInt(src.getPixel(i+1,j)),imgTransform::colorToInt(src.getPixel(i+1,j+1)),imgTransform::colorToInt(src.getPixel(i+1,j+2))},
                               {imgTransform::colorToInt(src.getPixel(i+2,j-2)),imgTransform::colorToInt(src.getPixel(i+2,j-1)),imgTransform::colorToInt(src.getPixel(i+2,j)),imgTransform::colorToInt(src.getPixel(i+2,j+1)),imgTransform::colorToInt(src.getPixel(i+2,j+2))}
                               };


            int r = imgTransform::multiplayArray(filter,matriX);
            r= abs(r)/273;
            res.setPixel(i,j,imgTransform::getGreyColor(r));

        }
    }
    return res;
}

int imgTransform::multiplayArray(int (*mask)[5], int (*img)[5]) {
    int a = 0;
    for(int i = 0;i<5;i++)
    {
        for (int j = 0; j < 5; ++j) {
            a+=mask[i][j]*img[i][j];
        }
    }
    return a;
}

