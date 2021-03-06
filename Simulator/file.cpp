#include "file.h"
#include <sys/stat.h>
#include <assert.h>
#include <stdarg.h>
#include <iostream>
using namespace std;

File::File()
{
    memset(m_strFileName,0,sizeof(m_strFileName));
    memset(m_strBuf,0,sizeof(m_strBuf));

    m_readCurPos = 0;
    m_fileSize = 0;
    m_isRepeatReadFile = false;
    m_pFile = NULL;
}

File::~File()
{
}

bool File::open(const char* type){
    m_fileSize = getFileSize();
    cout<<"m_fileSize="<<m_fileSize<<endl;
    m_pFile = fopen(m_strFileName, type);
    if(!m_pFile){
        cout<<"open file="<<m_strFileName<<"failure"<<endl;
        return false;
    }
    return true;
}
bool File::close(){
    if(m_pFile)
        assert(fclose(m_pFile)==0);
    m_pFile = NULL;
    m_readCurPos=0;
    return true;
}

int File::write(const char* msg,...){//external interface
    if(!m_pFile){
        cout<<"please open file first"<<endl;
        return 0;
    }
    va_list ap;
    va_start(ap, msg);
    memset(m_strBuf,0,sizeof(m_strBuf));
    int len = vsnprintf(m_strBuf,BUF_LEN,msg,ap);//其返回值是 拷贝字串的字节数
    if(len<0)
    {
         cout<<"can't format msg to bufTmp"<<endl;
         va_end(ap);
         return 0;
    }
    va_end(ap);
    
    len = fwrite(m_strBuf, 1,strlen(m_strBuf), m_pFile);
    //cout<<"len="<<len<<"  m_strBuf="<<m_strBuf<<"  m_strFileName="<<m_strFileName<<endl;
    return len;//return active size of writing to file.
}
void File::setFileName(const char* name){
    assert(strncpy(m_strFileName,name,(size_t)(sizeof(m_strFileName))));
}
void File::clear(){//clear all data in the file
    FILE* file = fopen(m_strFileName, "w");
    if(file){
        fclose(file);
    }
}
int File::read(char *buffer,int size){
    /*
        SEEK_SET： 文件开头
        SEEK_CUR： 当前位置
        SEEK_END： 文件结尾
    */
    if(!m_pFile){
        cout<<"read  please open file first"<<endl;
        return 0;
    }

    if(m_readCurPos<=m_fileSize){
        assert(!fseek(m_pFile,m_readCurPos,SEEK_SET));//move cur point
    }else{
        m_readCurPos=0;
    }

    size_t numread=0;

    numread=fread(buffer,1,size,m_pFile);

    m_readCurPos += numread;

    if(m_readCurPos>=m_fileSize){
        if(m_isRepeatReadFile){
           m_readCurPos = 0;//repeat to read file
           cout<<"repeat read file"<<endl;
        }else{
           cout<<"had arrived the file end"<<endl;
        }
    }
    return numread;
}
int File::flush(){//the cache is written to file
    int rel = fflush(m_pFile);
    if(rel==0){//success
        m_fileSize = getFileSize();
    }
    return rel;
}
long File::getFileSize(){
    FILE* file = fopen(m_strFileName, "r");
    long length=0;
    if(file){
        long curpos = ftell(file);//獲取文件指針的位置
        fseek(file, 0L, SEEK_END);//文件指針在文件的末尾
        length = ftell(file);//獲取文件指針的位置，
        fseek(file, curpos, SEEK_SET);//將文件指針放回文件頭處

        fclose(file);
    }else{
        cout<<"getfilesize failure"<<endl;
    }
    cout<<"getfilesize="<<length<<endl;

    return length;
}

/*
 返回值列表：
 -1 文件结束；
 0 读取一行成功；
 1 首字符等于ellipsis值。
 *
 */
int File::readLine(char *strPtr, int strlen, char ellipsis) {
        /*   文件指针，存储读取数据的字符串数组，字符串数组长度，当一行数据以ellipsis值开头时废弃该行，注：ellipsis值为“.”时，直接输出所有行   */
        int ch;
        char *tmpPtr;

        memset(strPtr, 0x0, strlen);
        ch = 0x0;
        tmpPtr = strPtr;

        if (feof(m_pFile))/*如果文件结束，返回错误代码   -1   */
                return -1;

        while (!feof(m_pFile) && ch != 0xa) { /*   读入一行数据   */
                ch = fgetc(m_pFile);
                if (ch != EOF && ch != '\n ') {
                        *strPtr = ch;
                        strPtr++;
                }
        }
        if (*tmpPtr == ellipsis || *tmpPtr == '\0 ' || *tmpPtr == '\n ')/*   如果行首字符等于ellipsis，返回错误代码   1   */
                return 1;
        else
                return 0;

}
