#ifndef DATAMGR_H
#define DATAMGR_H
#include "../include/define.h"
#include "linkmgr.h"
#include "../common/recvobject.h"
class DataMgr
{
public:
    DataMgr();
    ~DataMgr();

public:
    int open_block();
    bool anal_pag(const BYTE* buf,const int len);
    void setWindow(void*);
    void handle(const BYTE* buf,int len);
protected:

    void addBuf(const BYTE* buf,int len);

private:
    BYTE m_dataBuf[MAX_DATA_BUF];
    int m_curPos;

    void* m_pWindow;
};

#endif // DATAMGR_H
