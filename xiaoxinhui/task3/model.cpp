#include<iostream>
#include<opencv2/opencv.hpp>
#include<cmath>
#include<stdlib.h>
#include<ctime>
#include"model.h"

void Model_a::setmodel(float x1,float v1,float x01,float v01,float accelerate1,float time1)
{
  x=x1;
  v=v1;
  v0=v01;
  x0=x01;
  accelerate=accelerate1;
  time=time1;
}

Model_a::Model_a()
{
  x=0;
  v=0;
  x0=0;
  v0=0;
  accelerate=0;
  time=0;
}

float getnoise(float sigam)
{
srand(time(0));
float x1=rand()%101/100.0;
float x2=rand()%101/100.0;
float y=sqrt(-2*log(x1))*cos(2*3.1415*x2);
y=y*sigam;
return y;
}

void Model_a::update(float sigam)
{
  x=x+v0+accelerate*time+0.5*accelerate+getnoise(sigam);
  v=v+accelerate*1+0.1*getnoise(sigam);
  time=time+1;
}

float Model_a::getx()
{
  return x;
}

float Model_a::getv()
{
  return v;
}

float Model_a::getx0()
{
  return x0;
}

float Model_a::getv0()
{
  return v0;
}

float Model_a::geta()
{
  return accelerate;
}

float Model_a::gett()
{
  return time;
}