#include "gateway.h"
#include "tcp.h"
#include "udp.h"
#include "http.h"


int gateway_inues_send(gateway_opr_pt pdata);


/*****************************************************************************
*   Prototype    : main
*   Description  : main
*   Input        : int argc       
*                  char * argv[]  
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
int main(int argc,char * argv[])
{
    gateway_list_pt p_manage;
    gateway_manage_create(&p_manage);
    init_tcp(p_manage);
    init_http(p_manage);
    init_udp(p_manage);
    gateway_travel(p_manage,gateway_inues_send);
    gateway_delete_node(&p_manage,1);
    gateway_delete_node(&p_manage,1);
    gateway_delete_node(&p_manage,1);
}


/*****************************************************************************
*   Prototype    : gateway_inues_send
*   Description  : gateway inuse send
*   Input        : gateway_opr_pt pdata  
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
int gateway_inues_send(gateway_opr_pt pdata)
{
    int ret=0;
    if(pdata->flag==INUSE)
    {
      pdata->init(pdata);
      pdata->send_buffer = (char *)malloc(2048);
      memset(pdata->send_buffer,0,2048);
      strcpy(pdata->send_buffer,"hello tanzhou\n");
      ret = pdata->sendfunction(pdata);
      if(ret<0)
      {
          printf("Inuse type: %d send fail\n",pdata->id);
          free(pdata->send_buffer);
          pdata->send_buffer=NULL;
          return -1;
      }
      printf("Inuse type: %d send success\n",pdata->id);
      free(pdata->send_buffer);
      pdata->send_buffer=NULL;
      return ret;
    }
}
