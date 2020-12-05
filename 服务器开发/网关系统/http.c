/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : http.c
*  Version       : Initial Draft
*  Author        : chandler
*  Created       : 2020/11/23
*  Last Modified :
*  Description   : gateway http send
*  Function List :
*
*       1.                http_send
*       2.                init_http
*       3.                init_http_node
*       4.                register_http_method
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

#include "http.h"



/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

static u32 init_http_node(gateway_opr_pt pdata)
{
    pdata->sockfd= socket(AF_INET,SOCK_STREAM,0);
    if(pdata->sockfd < 0){
        perror("socket error");
        exit(0);
    }
    struct sockaddr_in remote;
    bzero(&remote,sizeof(remote));
    remote.sin_family = AF_INET;
    remote.sin_port = htons(HTTP_PORT);
    if(inet_pton(AF_INET,HTTP_SERVER,&remote.sin_addr)<=0)
    {
        perror("net_pton error!\n");
        exit(1);
    }
    int ret = connect(pdata->sockfd,(struct sockaddr*)&remote,sizeof(remote));
    if(ret < 0){
        printf("connect failed:%s\n",strerror(errno));
        exit(1);
    }
    printf("connect success!\n");
}

static int http_send(gateway_opr_pt pdata)
{
    u8* length=(u8 *)malloc(128);
    int len =strlen(pdata->send_buffer);
    sprintf(length,"%d",len);
    u8 *http_data=(u8 *)malloc(len+1024);
    memset(http_data, 0, len+1024);
    strcat(http_data, "POST /webservices/qqOnlineWebService.asmx/qqCheckOnline HTTP/1.1\r\n");
    strcat(http_data, "Host: www.webxml.com.cn\r\n");
    strcat(http_data, "Content-Type: application/x-www-form-urlencoded\r\n");
    strcat(http_data, "Content-Length: ");
    strcat(http_data, length);
    strcat(http_data, "\r\n");
    strcat(http_data, pdata->send_buffer);
    strcat(http_data, "\r\n\r\n");
    printf("%s\n",http_data);
    int ret= write(pdata->sockfd,pdata->send_buffer,strlen(pdata->send_buffer));
    if(ret<0)
    {
        printf("write:%s\n",strerror(errno));
        exit(1);
    }
    else
    {   
        printf("send sucess,send length:%d\n",ret);
    }
    free(length);
    free(http_data);
    length=NULL;
    http_data=NULL;
    return ret;
}

static gateway_opr_t http_node={
    .id =HTTP,
    .flag =INUSE,
    .init =init_http_node  ,
    .sendfunction= http_send,
};

static void register_http_method(gateway_list_pt ptlist,void *pdata)
{
     if(ptlist==NULL || pdata==NULL)
    {
        perror("malloc error\n");
        exit(1);
    }
    gateway_insert_after(&ptlist,1, pdata);
}

void init_http(gateway_list_pt ptlist)
{
    register_http_method(ptlist,(void *)&http_node);
}

