/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : http.h
*  Version       : Initial Draft
*  Author        : chandler
*  Created       : 2020/11/23
*  Last Modified :
*  Description   : http.c header file
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
#ifndef __HTTP_H__
#define __HTTP_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "gateway.h"


/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
#define HTTP_PORT 8001
#define HTTP_SERVER "127.0.0.1"


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern void init_http(gateway_list_pt ptlist);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __HTTP_H__ */
