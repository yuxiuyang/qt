#ifndef DATADEV_H
#define DATADEV_H

//device the data

#include <QThread>
#include <errno.h>
#include <vector>
 #include <QMutex>
#include "l_jn.h"
#include <algorithm>//使用泛型算法必须包含头文件algorithm
#include "datamgr.h"
#include "recvobject.h"
using namespace std;
class DataDev;
struct INFO_DATA{
    int fd;
    BYTE* buf;
    int len;
    DataDev* pThis;
};
enum THREAD_STATE{
    THREAD_RUNNING,
    THREAD_STOP,
    THREAD_SUSPEND,
};
struct RECVOBJECT_FD{
    RecvObject* object;
    int         fd;
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

        friend class RecvObject;
        static DataDev* getInstance();

        void sendData(int fd,const BYTE* buf,int len);
        void sendData(int socketFd,MsgType_ msgType,ClientType_ clientType,DataSource_ dataSource,const BYTE* buf,const int len);
        bool checkData(const BYTE* buf,const int len,const BYTE value);
//        void setCallback(void(*callback)(int)){
//            CallBack_ = callback;
//        }
        bool removeFd(int fd);
        RecvObject* findFd(int fd);
protected:
        static void sendData_(void* pv);
        void recvData();
        virtual void run();


        bool addFd(RecvObject* object,int fd);
        bool removeAll(RecvObject* object=NULL);

private:
        static DataDev* m_instance;

        vector<RECVOBJECT_FD*> m_objectFdVec;//just

        QMutex m_sendMutex;//
        QMutex m_socketFdMutex;
        CJobNest *m_pDataJob;//send data task thread.

        THREAD_STATE m_pthreadState;
        //void (*CallBack_)(int);

};

#endif // DATADEV_H
