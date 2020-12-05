        /******************************************************************************
*
*  Copyright (C), 2001-2005, Huawei Tech. Co., Ltd.
*
*******************************************************************************
*  File Name     : gateway.c
*  Version       : Initial Draft
*  Author        : chandler
*  Created       : 2020/11/23
*  Last Modified :
*  Description   : gateway management core level
*  Function List :
*
*       1.                gateway_delete_node
*       2.                gateway_insert_after
*       3.                gateway_insert_before
*       4.                gateway_manage_create
*       5.                gateway_modify
*       6.                gateway_node_visit
*       7.                gateway_search
*       8.                gateway_travel
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
#include "gateway.h"
/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/

/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

/*****************************************************************************
*   Prototype    : gateway_manage_create
*   Description  : gateway manage core level list create functon
*   Input        : gateway_list_pt *list  
*   Output       : None
*   Return Value : int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/11/12
*           Author       : chandler
*           Modification : Created function
*
*****************************************************************************/
int gateway_manage_create(gateway_list_pt *_list)
{
    gateway_list_pt list = *_list;
    list=(gateway_list_pt)malloc(sizeof(gateway_list_t));
    if(list==NULL)
    {
        perror("malloc error\n");
        return -1;
    }
    list->size=0;
    list->head=(gateway_node_pt)malloc(sizeof(gateway_node_t));
    if( list->head==NULL)
    {
        perror("malloc error\n");
        return -1;
    }    
    list->head->next=list->head->prev=NULL;
    list->head->data=NULL;
    list->tail=list->head;
    return 0;
}

/*****************************************************************************
*   Prototype    : gateway_insert_before
*   Description  : insert node before 
*   Input        : gateway_list_pt *list  
*                  int num                
*                  void *new_node_data    
*   Output       : None
*   Return Value : int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/11/16
*           Author       : chandler
*           Modification : Created function
*
*****************************************************************************/
int gateway_insert_before(gateway_list_pt *_list,int num,void *new_node_data)
{
    u32 counter=1;
    gateway_list_pt list=*_list;
    gateway_node_pt  current=NULL;
    gateway_node_pt  new_node=NULL; 

    if(list==NULL||_list==NULL)
    {
        perror("Invaile argrument!\n");
        return (-1);
    }
    if(list->size!=0)
    {
        new_node=(gateway_node_pt)malloc(sizeof(gateway_node_t));
        if(new_node==NULL)
       {
            perror("malloc error\n");
            return -1;
       }
        new_node->data=new_node_data;
        new_node->prev=new_node->next=NULL; 
        if(num >0 &&num <=list->size)
        {
            current=list->head;
            while(counter<num)
            {
                counter++;
                current=current->next;
            }
            if(counter==1)
            {
                list->head->prev=new_node;
                new_node->next=list->head;
                list->head=new_node;
                list->size++;
            }
            
            current->prev->next=new_node;
            new_node->prev=current->prev;
            current->prev=new_node;
            new_node->next=current;
            list->size++;
            return 0;
        }
        else
        {
            free(new_node);
            new_node=NULL;
            return -1;
        }
        
    }
    else
    {
        if(num!=0)
        {
            perror("Invaile argrument!\n") ;
            return -1;
        }
        list->head->data=new_node_data;
        list->size++;
        return 0;
    }
    
}



/*****************************************************************************
*   Prototype    : gateway_insert_after
*   Description  : insert node after
*   Input        : gateway_list_pt *list  
*                  int num                
*                  void *new_node_data    
*   Output       : None
*   Return Value : int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/11/16
*           Author       : chandler
*           Modification : Created function
*
*****************************************************************************/
int gateway_insert_after(gateway_list_pt *_list,int num,void *new_node_data)
{
    u32 counter=1;
    gateway_node_pt  current=NULL;
    gateway_node_pt  new_node=NULL; 
    gateway_list_pt list = *_list;

    if(list==NULL||_list==NULL)
    {
        perror("Invaile argrument!\n");
        return -1;
    }
    if((list)->size!=0)
    {
        new_node=(gateway_node_pt)malloc(sizeof(gateway_node_t));
        if(new_node==NULL)
       {
            perror("malloc error\n");
            return -1;
       }
        new_node->data=new_node_data;
        new_node->prev=new_node->next=NULL; 
        if(num >0 &&num <=(list)->size)
        {
            current=list->head;
            while(counter<num)
            {
                counter++;
                current=current->next;
            }
            if(current->next==NULL)
            {
                list->tail=new_node;
                current->next=new_node;
                new_node->prev=current;
                list->size++;
                return 0;
            }
            new_node->prev=current;
            new_node->next=current->next;
            current->next->prev = new_node ;
            current->next=new_node;
            list->size++;
            return 0;
        }
        else
        {
            free(new_node);
            new_node=NULL;
            return -1;
        }
        
    }
    else
    {
        if(num!=0)
        {
            perror("Invaile argrument!\n") ;
            return -1;
        }
        list->head->data=new_node_data;
        list->size++;
        return 0;
    }
    
}

/*****************************************************************************
*   Prototype    : gateway_delete_node
*   Description  : delete node
*   Input        : gateway_list_pt * list  
*                  int num                 
*   Output       : None
*   Return Value : int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/11/23
*           Author       : chandler
*           Modification : Created function
*
*****************************************************************************/
int gateway_delete_node(gateway_list_pt * _list, int num)
{
    u32 counter=1;
    gateway_node_pt  current=NULL;
    gateway_opr_pt temp;
    gateway_node_pt tmp;
    gateway_list_pt list = *_list;
    if(list==NULL||_list==NULL||(num > list->size))
    {
        perror("Invaile argrument!\n");
        return -1;
    }
    current=list->head; 
    while(counter<num)
    {
        counter++;
        current=current->next;
    }
    if (list->size==1)
    {
        temp=list->head->data;
        list->head->data=NULL;
        free(temp);
        temp=NULL;
        list->size--;
        return 0;
    }
    if(list->size==counter)
    {
        tmp=list->tail;
        list->tail = list->tail->prev;
        free(tmp);
        tmp=NULL;
        list->tail->next=NULL;
        list->size--;
        return 0;
    }
    tmp=current;
    current->next->prev=current->prev;
    current->prev->next=current->next;
    free(tmp);
    tmp=NULL;
    list->size--;
    return 0;
}

/*****************************************************************************
*   Prototype    : gateway_modify
*   Description  : modify node data
*   Input        : gateway_list_pt * list  
*                  int num                 
*                  void * new_node_data    
*   Output       : None
*   Return Value : int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/11/17
*           Author       : chandler
*           Modification : Created function
*
*****************************************************************************/
int gateway_modify(gateway_list_pt *_list, int num, void * new_node_data)
{
    int counter =0;
    gateway_node_pt current=NULL;
    gateway_list_pt list=*_list;
    if(list==NULL || _list==NULL ||num<0 || num >list->size)
    {
        perror("Invaile argrument!\n");
        return -1;
    }
    current=list->head;
    while(counter!=num-1)
    {
        current=current->next;
        counter++;
    }
    current->data=new_node_data;
}

/*****************************************************************************
*   Prototype    : gateway_node_visit
*   Description  : visit node data
*   Input        : gateway_list_pt * list  
*                  u32 num                 
*   Output       : None
*   Return Value : static inline void *
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/11/17
*           Author       : chandler
*           Modification : Created function
*
*****************************************************************************/
static inline void * gateway_node_visit(gateway_list_pt * list,u32 num)
{
    int counter;
    gateway_node_pt current=NULL;
    if((*list)==NULL || list==NULL ||num<0 || num >(*list)->size)
    {
        perror("Invaile argrument!\n");
        return NULL;
    }
    for ( counter=0 ; counter<num;counter++ )
    {
        current=current->next;
    }
    return (void *)current->data;
}


/*****************************************************************************
*   Prototype    : gateway_travel
*   Description  : travel list for function
*   Input        : gateway_list_t * list       
*                  void(*do_function)(void *)  
*   Output       : None
*   Return Value : void
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/11/17
*           Author       : chandler
*           Modification : Created function
*
*****************************************************************************/
void gateway_travel(gateway_list_t * list,void(*do_function)(void *))
{
    u32 i=0;
    if(list->size<0||list==NULL)
    {
        perror("Invaile argrument!\n");
        return ;
    }
    for(i=0;i<list->size;i++)
        (*do_function)(gateway_node_visit(&list,i));
}

/*****************************************************************************
*   Prototype    : gateway_search
*   Description  : compare node in gateway list
*   Input        : gateway_list_t * list  
*                  void *find_data        
*                  int(*compare)(void*    
*                  void*)                 
*   Output       : None
*   Return Value : int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/11/17
*           Author       : chandler
*           Modification : Created function
*
*****************************************************************************/
int gateway_search(gateway_list_t * list,void *find_data,int(*compare)(void*,void*))
{
    int counter=1;
    gateway_node_pt current=NULL;
    if(list==NULL)
    {
        perror("Invaile argrument!\n");
        return -1;
    }
    current=list->head;
    while(compare(current->data,find_data)!=0 && current->next!=NULL)
    {
        current=current->next;
        counter++;
    }
    if(current->next==NULL && compare(current->data,find_data)==0)
        return 0;
    return counter;
}
