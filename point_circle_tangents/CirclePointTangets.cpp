#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <graphics.h>
#include <dos.h>
#include <conio.h>

bool isPointOutOfCircle(double x, double y, double a, double b, double r){
    double leftEquation = pow((x-a), 2) + pow((y-b), 2);
    double rightEquation = pow(r, 2);

    if(leftEquation > rightEquation){
        return true;
    }else{
        return false;
    }
}

double* thalesCircle(double pointX, double pointY, double circleX, double circleY){
    double static thalesArray[3];
    double thalesX = pointX;
    double thalesY = pointY;
    double radius = sqrt((pow((circleX - pointX), 2) + pow((circleY - pointY), 2)));
    thalesArray[0] = thalesX;
    thalesArray[1] = thalesY;
    thalesArray[2] = radius;

    return thalesArray;
}

int circle_circle_intersection(double x0, double y0, double r0,
                               double x1, double y1, double r1,
                               double *xi, double *yi,
                               double *xi_prime, double *yi_prime)
{
  double a, dx, dy, d, h, rx, ry;
  double x2, y2;

  dx = x1 - x0;
  dy = y1 - y0;
  d = hypot(dx,dy);
  if (d > (r0 + r1))
  {
    return 0;
  }
  if (d < fabs(r0 - r1))
  {
    return 0;
  }

  a = ((r0*r0) - (r1*r1) + (d*d)) / (2.0 * d) ;

  x2 = x0 + (dx * a/d);
  y2 = y0 + (dy * a/d);

  h = sqrt((r0*r0) - (a*a));

  rx = -dy * (h/d);
  ry = dx * (h/d);

  *xi = x2 + rx;
  *xi_prime = x2 - rx;
  *yi = y2 + ry;
  *yi_prime = y2 - ry;

  return 1;
}

double* pointIntersections(double x0, double y0, double r0,
              double x1, double y1, double r1)
{
  double static intersectionCoordinates[4];
  double x3, y3, x3_prime, y3_prime;
  circle_circle_intersection(x0, y0, r0, x1, y1, r1,
                             &x3, &y3, &x3_prime, &y3_prime);

  intersectionCoordinates[0] = x3;
  intersectionCoordinates[1] = y3;
  intersectionCoordinates[2] = x3_prime;
  intersectionCoordinates[3] = y3_prime;

  return intersectionCoordinates;
}

int main(){

    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");

    double xCoordinate = 0;
    double yCoordinate = 0;
    double radius = 1;

    double pointX = 0;
    double pointY = 0;

    double* thalesCircleParameters;
    double* result;

    printf("Standard equation of a circle: (x-a)^2 + (y-b)^2 = r^2 \n");
    printf("Please give me the circle center coordinates (a,b)\n");
    printf("x coordinate: ");
    scanf("%lf", &xCoordinate);
    printf("y coordinate: ");
    scanf("%lf", &yCoordinate);
    printf("Please give me the circle radius: ");
    scanf("%lf", &radius);

    printf("Give me the outer point\n");
    printf("x coordinate: ");
    scanf("%lf", &pointX);
    printf("y coordinate: ");
    scanf("%lf",  &pointY);

    if(!isPointOutOfCircle(pointX, pointY, xCoordinate,yCoordinate, radius)){
        printf("Point is not out of the circle!");
        return 0;
    }

    thalesCircleParameters = thalesCircle(pointX, pointY, xCoordinate, yCoordinate);
    printf("\n %lf, %lf, %lf", thalesCircleParameters[0], thalesCircleParameters[1], thalesCircleParameters[2]);
    result = pointIntersections(xCoordinate, yCoordinate, radius, thalesCircleParameters[0], thalesCircleParameters[1], thalesCircleParameters[2]);

    circle(xCoordinate, yCoordinate, radius);
    circle(pointX, pointY, 1);
    line(pointX, pointY, result[0], result[1]);
    line(pointX, pointY, result[2], result[3]);

    getch();
    closegraph();

    return 0;
}
