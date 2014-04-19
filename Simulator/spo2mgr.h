#ifndef SPO2MGR_H
#define SPO2MGR_H
#include "basicmgr.h"
class Spo2Mgr : public BasicMgr
{
public:
    Spo2Mgr();
    ~Spo2Mgr();

public:
    void onTimer();
    void sendData(const BYTE* buf,int len);
    void setWindow(void* win){
        assert(win);
        m_Ui = win;
    }
    void display();
    int data_Arrived(int fd);
protected:



private:
    void* m_Ui;//used to display msg on the window

};

#endif // SPO2MGR_H
