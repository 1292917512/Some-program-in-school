/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : tcp.c
*  Version       : Initial Draft
*  Author        : chandler
*  Created       : 2020/11/23
*  Last Modified :
*  Description   : gateway tcp send 
*  Function List :
*
*       1.                init_tcp
*       2.                init_tcp_node
*       3.                register_tcp_method
*       4.                tcp_send
*
*  History:
* 
*       1.  Date         : 2020/11/23
*           Author       : chandler
*           Modification : Created file
*
******************************************************************************/

/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include "tcp.h"

/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

static u32 init_tcp_node(gateway_opr_pt pdata)
{
    pdata->sockfd= socket(AF_INET,SOCK_STREAM,0);
    if(pdata->sockfd < 0){
        perror("socket error");
        exit(0);
    }
    struct sockaddr_in remote;
    bzero(&remote,sizeof(remote));
    remote.sin_family = AF_INET;
    remote.sin_port = htons(TCP_PORT);
    if(inet_pton(AF_INET,TCP_SERVER,&remote.sin_addr)<=0)
    {
        perror("net_pton error!\n");
        exit(1);
    }
    int ret = connect(pdata->sockfd,(struct sockaddr*)&remote,sizeof(remote));
    if(ret < 0){
        perror("connect failed\n");
        exit(1);
    }
    printf("connect success!\n");
}

static int tcp_send(gateway_opr_pt pdata)
{
    int ret= write(pdata->sockfd,pdata->send_buffer,strlen(pdata->send_buffer));
    if(ret<0)
    {
        perror("write\n");
        exit(1);
    }
    else
    {   
        printf("send sucess,send length:%d\n",ret);
    }
    return ret;
}

static gateway_opr_t tcp_node={
    .id =TCP,
    .flag =INUSE,
    .init =init_tcp_node  ,
    .sendfunction= tcp_send,
};

static void register_tcp_method(gateway_list_pt ptlist,void *pdata)
{
    if(ptlist==NULL || pdata==NULL)
    {
        perror("malloc error\n");
        exit(1);
    }
    gateway_insert_before(&ptlist,0, pdata);
}

void init_tcp(gateway_list_pt ptlist)
{
    register_tcp_method(ptlist,(void *)&tcp_node);
}
