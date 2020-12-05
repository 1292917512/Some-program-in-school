/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : udp.c
*  Version       : Initial Draft
*  Author        : chandler
*  Created       : 2020/11/23
*  Last Modified :
*  Description   : gateway udp send
*  Function List :
*
*       1.                init_udp
*       2.                init_udp_node
*       3.                register_udp_method
*       4.                udp_send
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
#include "udp.h"


/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/


static u32 init_udp_node(gateway_opr_pt pdata)
{
    pdata->sockfd= socket(AF_INET,SOCK_DGRAM,0);
    if(pdata->sockfd < 0){
        perror("socket error");
        exit(0);
    }
}

static int udp_send(gateway_opr_pt pdata)
{
    struct sockaddr_in remote;
    bzero(&remote,sizeof(remote));
    remote.sin_family = AF_INET;
    remote.sin_port = htons(UDP_PORT);
    if(inet_pton(AF_INET,UDP_SERVER,&remote.sin_addr)<=0)
    {
        printf("net_pton error!\n");
        exit(1);
    }
    int ret=sendto(pdata->sockfd,pdata->send_buffer,strlen(pdata->send_buffer),0,(struct sockaddr*)&remote,sizeof(remote));
    if(ret<0)
    {
        printf("write:%s\n",strerror(errno));
        exit(1);
    }
    else
    {   
        printf("send sucess,send length:%d\n",ret);
    }
    return ret;
}

static gateway_opr_t udp_node={
    .id =UDP,
    .flag =INUSE,
    .init =init_udp_node  ,
    .sendfunction= udp_send,
};

static void register_udp_method(gateway_list_pt ptlist,void *pdata)
{
     if(ptlist==NULL || pdata==NULL)
    {
        perror("malloc error\n");
        exit(1);
    }
    gateway_insert_before(&ptlist,2, pdata);
}

void init_udp(gateway_list_pt ptlist)
{
    register_udp_method(ptlist,(void *)&udp_node);
}
