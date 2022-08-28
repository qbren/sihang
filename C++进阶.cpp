#include <iostream>
using namespace std;

class Person {
public:                                             //可读可写
     void setNum(int num){
         m_Num=num;
     }
int getNum(){
     return m_Num;
}

private:
    int m_Num;
};


int main(){
    int num=0;
    Person s;
   cin >> num;s.setNum(num);
     int a;
    if (num<=10)
   {for (a=1;a<=s.getNum();a++)
    cout<<"Hello,RoboMaster!"<<endl;}
    if(num>10) 
    cout<<"error"<<endl;
    getchar();
    return 0;
}
