#ifndef DATADEV_H
#define DATADEV_H

//device the data

#include <QThread>
#include <errno.h>
#include <vector>
 #include <QMutex>
#include "l_jn.h"
#include "../include/define.h"
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


protected:
        static void sendMsgData_(void* pv);
        static void sendData_(void* pv);
        static void sendStateMsg_(void* pv);

private:
        static DataDev* m_instance;
        bool m_initServerOk;
        int m_maxClientFd;//client fd max

        vector<int> m_tmpVec;//just a tmp

        QMutex m_sendMutex;//
        CJobNest *m_pDataJob;//send data task thread.
    };

#endif // DATADEV_H
