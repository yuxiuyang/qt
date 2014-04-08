#ifndef DATAMGR_H
#define DATAMGR_H

#include <QThread>
#include "l_jn.h"
#include "../include/define.h"
class DataMgr : public QThread
{
Q_OBJECT
public:
    explicit DataMgr(QObject *parent = 0);
    ~DataMgr();
signals:

public slots:


public:
    void sentData(const Msg_* msg);
    void run();

protected:
    static void sendState(void* pv);
    void recvData();


private:
    CJobNest *m_pSendJob;//send data task thread.
};

#endif // DATAMGR_H
