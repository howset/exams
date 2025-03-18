#ifndef TSP_H
#define TSP_H

#define MAX_CITIES 11

typedef struct {
    float x;
    float y;
} City;

float distance(float x1, float y1, float x2, float y2);

#endif