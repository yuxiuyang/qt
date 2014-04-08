#ifndef MGRDEV_H
#define MGRDEV_H

#include <QThread>
#include <QTimer>
#include <vector>
using namespace std;
#define BASIC_TIMER_TIME 2// mms

struct TimerTask{
    bool bLimit;
    int iCount;
    void* pObject;
};

class MgrDev : public QThread
{
Q_OBJECT
private:
    explicit MgrDev(QObject *parent = 0);
public:
    ~MgrDev();
    void run();
    static MgrDev* getInstance();
    static MgrDev* m_instance;

    bool registerObject(void* object);//
    bool unregisterObject(void* object);
protected:
    void stopTimer();
    bool findObject(void* object);
signals:

public slots:
    void _onWriteTimeout();
private:
   QTimer *m_timer;//timer in the another thread not in main thread
   vector<void*> m_vecObject;


};

#endif // MGRDEV_H
