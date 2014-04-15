#ifndef DATADEV_H
#define DATADEV_H

//device the data

#include <QThread>
#include "network_server.h"
#include <errno.h>
#include <vector>
#include "datamgr.h"
#include "linkmgr.h"
 #include <QMutex>
#include "l_jn.h"
using namespace std;
class DataDev;
struct INFO_MSG{
    int fd;
    Msg_* msg;
    DataDev* pThis;
};
struct INFO_DATA{
    int fd;
    char* buf;
    int len;
    DataDev* pThis;
};
class DataDev : public QThread
{
    Q_OBJECT
    private:
        explicit DataDev(QObject *parent = 0);
    public:
        virtual ~DataDev();
    signals:

    public slots:


    public:
        virtual void run();

        static DataDev* getInstance();

        void sendData(int fd,const Msg_* msg);
        void sendData(int fd,const char* buf,int len);
        void sendStateMsg(int fd,const Msg_* msg);

        DataMgr*   m_pDataMgr;
        LinkMgr*   m_pLinkMgr;


protected:
        static void sendMsgData_(void* pv);
        static void sendData_(void* pv);
        static void sendStateMsg_(void* pv);

        void recvData();

private:
        static DataDev* m_instance;
        Network_Server m_serverNetwork;
        bool m_initServerOk;
        int m_maxClientFd;//client fd max

        vector<int> m_tmpVec;//just a tmp

        QMutex m_sendMutex;//
        CJobNest *m_pSendDataJob;//send data task thread.
        CJobNest *p_pSendStateMsgJob;//send state msg thread
    };

#endif // DATADEV_H
