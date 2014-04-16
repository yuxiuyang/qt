#ifndef DATADEV_H
#define DATADEV_H

//device the data

#include <QThread>
#include <errno.h>
#include <vector>
 #include <QMutex>
#include "l_jn.h"
#include "../include/define.h"
#include <algorithm>//使用泛型算法必须包含头文件algorithm
#include "datamgr.h"

using namespace std;
class DataDev;
struct INFO_DATA{
    int fd;
    char* buf;
    int len;
    DataDev* pThis;
};
enum THREAD_STATE{
    THREAD_RUNNING,
    THREAD_STOP,
    THREAD_SUSPEND,
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

        void sendData(int fd,const BYTE* buf,int len);

        void setCallback(void(*callback)(int)){
            CallBack_ = callback;
        }

        bool addFd(int fd);
        bool removeFd(int fd);
        bool findFd(int fd);

protected:
        static void sendData_(void* pv);


        void recvData();

private:
        static DataDev* m_instance;

        vector<int> m_fdVec;//just

        QMutex m_sendMutex;//
        QMutex m_socketFdMutex;
        CJobNest *m_pDataJob;//send data task thread.

        THREAD_STATE m_pthreadState;
        void (*CallBack_)(int);

};

#endif // DATADEV_H
