#ifndef DATADEV_H
#define DATADEV_H

//device the data

#include <QThread>
#include "network_server.h"
#include <errno.h>
#include <vector>
#include "datamgr.h"
#include "linkmgr.h"
using namespace std;
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

        int sendData(int fd,const Msg_* msg);


        DataMgr*   m_pDataMgr;
        LinkMgr*   m_pLinkMgr;
    private:
        static DataDev* m_instance;
        Network_Server m_serverNetwork;
        bool m_initServerOk;
        int m_maxClientFd;//client fd max

        vector<int> m_tmpVec;//just a tmp
    };

#endif // DATADEV_H
