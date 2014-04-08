#ifndef NETWORK_SERVER_H
#define NETWORK_SERVER_H
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <QThread>

class Network_Server : public QThread
{
Q_OBJECT
public:
    explicit Network_Server(QObject *parent = 0);
    ~Network_Server();

    bool init();
    void startServer();
    void stopServer();
    void run();
signals:

public slots:


private:
    int m_serverSockFd;
    unsigned short m_serverPort;
    struct sockaddr_in m_serverAddress;
};

#endif // NETWORK_SERVER_H
