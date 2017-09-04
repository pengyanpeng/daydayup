/*************************************************************************
	> File Name: shmdata.h
	> Author: 
	> Mail: 
	> Created Time: 2017年09月04日 星期一 23时52分54秒
 ************************************************************************/

#ifndef _SHMDATA_H
#define _SHMDATA_H

#define TEXT_SZ 2048  
  
struct shared_use_shm  
{  
    int written;//作为一个标志，非0：表示可读，0表示可写  
    char text[TEXT_SZ];//记录写入和读取的文本  
};

#endif
