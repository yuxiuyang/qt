#ifndef RECVOBJECT_H
#define RECVOBJECT_H

class RecvObject
{
public:
    RecvObject();
    virtual ~RecvObject();

    virtual int recvData(int fd)=0;

    bool addFd(int fd);
    bool removeFd(int fd);
    RecvObject* findFd(int fd);
};

#endif // RECVOBJECT_H
