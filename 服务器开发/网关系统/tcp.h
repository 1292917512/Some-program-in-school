/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : tcp.h
*  Version       : Initial Draft
*  Author        : chandler
*  Created       : 2020/11/23
*  Last Modified :
*  Description   : tcp.c header file
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2020/11/23
*           Author       : chandler
*           Modification : Created file
*
******************************************************************************/
#ifndef __TCP_H__
#define __TCP_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include "gateway.h"

/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/    
#define TCP_PORT 8000
#define TCP_SERVER "127.0.0.1"

/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern void init_tcp(gateway_list_pt ptlist);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __TCP_H__ */
