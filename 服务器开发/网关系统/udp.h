/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : udp.h
*  Version       : Initial Draft
*  Author        : chandler
*  Created       : 2020/11/23
*  Last Modified :
*  Description   : udp.c header file
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
#ifndef __UDP_H__
#define __UDP_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include "gateway.h"

/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
#define UDP_PORT 8002
#define UDP_SERVER "127.0.0.1"


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern void init_udp(gateway_list_pt ptlist);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __UDP_H__ */
