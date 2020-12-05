/******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : gateway.h
*  Version       : Initial Draft
*  Author        : chandler
*  Created       : 2020/11/23
*  Last Modified :
*  Description   : gateway.c header file
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
#ifndef __GATEWAY_H__
#define __GATEWAY_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
    
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

    
#define TCP 1
#define UDP 2
#define HTTP 3
    
#define INUSE 1
#define NOUSE 0
    
    
typedef struct gateway_opr
{
    u8 id;
    u8 flag;
    int sockfd ;
    u8 * send_buffer;
    u32 (* init)(struct gateway_opr * pdata );
    int (* sendfunction)(struct gateway_opr * pdata);
}gateway_opr_t;
typedef gateway_opr_t* gateway_opr_pt;

typedef struct gateway_node{
    void * data;
    struct gateway_node * prev;
    struct gateway_node * next;
}gateway_node_t;
typedef gateway_node_t* gateway_node_pt;

typedef struct gateway_list
{
    u32 size;
    gateway_node_pt head;
    gateway_node_pt tail;
}gateway_list_t;
typedef  gateway_list_t * gateway_list_pt;


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern int gateway_delete_node(gateway_list_pt * list, int num);
extern int gateway_insert_after(gateway_list_pt *list,int num,void *new_node_data);
extern int gateway_insert_before(gateway_list_pt *list,int num,void *new_node_data);
extern int gateway_manage_create(gateway_list_pt *list);
extern int gateway_modify(gateway_list_pt * list, int num, void * new_node_data);
extern int gateway_search(gateway_list_t * list,void *find_data,int(*compare)(void*,void*));
extern void gateway_travel(gateway_list_t * list,void(*do_function)(void *));

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __GATEWAY_H__ */
