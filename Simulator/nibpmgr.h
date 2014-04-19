#ifndef NIBPMGR_H
#define NIBPMGR_H
#include "basicmgr.h"
class NibpMgr : public BasicMgr
{
public:
    NibpMgr();
    ~NibpMgr();

public:
    void onTimer();
    void sendData(const BYTE* msg,int len);

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

#endif // NIBPMGR_H
