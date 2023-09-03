#ifndef _model_H_
#define _model_H_

class Model_a{
public:
     Model_a();
     void setmodel(float x,float v,float x0,float v0,float accelerate,float time);
     void update(float);
     float getx();
     float getv();
     float getx0();
     float getv0();
     float geta();
     float gett();
private:
    float x;
    float v;
    float x0;//初始位置
    float v0;//初始速度
    float accelerate;//固定的加速度
    float time;     //采样时间
};

float getnoise(float);

#endif
