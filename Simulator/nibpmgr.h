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

    void setWindow(void* win){
        assert(win);
        m_Ui = win;
    }
    void display();

    void sendData(BYTE* msg,int len);
protected:



private:
    void* m_Ui;//used to display msg on the window
};

#endif // NIBPMGR_H
