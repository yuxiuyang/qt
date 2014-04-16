#ifndef DATAMGR_H
#define DATAMGR_H
#include "../include/define.h"
#include "linkmgr.h"

class DataMgr
{
public:
    DataMgr();
    ~DataMgr();

public:
    static void recvData(int fd);
    void setWindow(void*);
protected:

    void setBuf(const BYTE* buf,int len);
    void handle();

private:
    LinkMgr* m_pLinkMgr;
    static DataMgr* pThis;

    BYTE m_dataBuf[MAX_DATA_BUF];
    int m_pWirte;
    int m_pRead;

    void* m_pWindow;
};

#endif // DATAMGR_H
