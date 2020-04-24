#include "heartbeat.h"


EventGroupHandle_t HbEventGroup;
volatile TickType_t lastRevOrSend;

/* 
������⹦��ģ���ʼ��
*/
int HbInit(void)
{
#ifdef HEARTBEAT_ENABLE
    HbEventGroup = NULL;
	
	/* ���������¼��� */
	HbEventGroup = xEventGroupCreate();
	if(NULL == HbEventGroup)
	{
		dbg_printf(DEBUG_ERR, "Heartbeat Event Group Create fail...");
		return -1;
    }
    lastRevOrSend = xTaskGetTickCount();
#endif
	return 0;
}

/* TCP ���������¼� */
void tcpSendEvent(void)
{
#ifdef HEARTBEAT_ENABLE
	xEventGroupSetBits(HbEventGroup,TCPSEND_EVENT);
#endif
}

/* TCP ���������¼� */
void tcpRevEvent(void)
{
#ifdef HEARTBEAT_ENABLE
	xEventGroupSetBits(HbEventGroup,TCPREV_EVENT);
#endif
}

/* ������������ */
void HbMainTask(void)
{
    
#ifdef HEARTBEAT_ENABLE	

    EventBits_t HbBits;
    static int trytimes = 0;
    int op_res;


    /* �ж��Ƿ���TCP���ջ����¼� */
    HbBits = xEventGroupWaitBits(HbEventGroup, TCPSEND_EVENT | TCPREV_EVENT, pdTRUE, pdFALSE, 1);

    if(0 < (HbBits & (TCPSEND_EVENT | TCPREV_EVENT)))
    {
        /*����TCP���ݽ����¼�*/
        lastRevOrSend = xTaskGetTickCount();
        trytimes = 0;
        dbg_printf(DEBUG_DEBUG,"Socket send or receive event.");
    }

    /* �ж��Ƿ���Ҫ�������� */
    if(xTaskGetTickCount() - lastRevOrSend > HEARTBEAT_TIMEOUT)
    {

        lastRevOrSend = xTaskGetTickCount();
        trytimes++;

        /* �жϳ��Դ����Ƿ��� */
        if(trytimes > HEARTBEAT_TRYTIMES)
        {
            /* TCP��������������DTU���� */
            dbg_printf(DEBUG_WARNING,"TCP����ʧЧ...");
            trytimes = 0;
            op_res = setServerIP(SysPara.IP1,SysPara.IP2,SysPara.IP3,SysPara.IP4,SysPara.PortNum);
            if(0 != op_res)
            {
                dbg_printf(DEBUG_WARNING,"DTU����ʧ��...");
            }
            else
            {
                dbg_printf(DEBUG_INFO,"DTU�����ɹ�...");
            }
        }
        else
        {
            /* �������� */
            UART_TO_FY1000_QueueSend_Stru SendBuffer;
            FY_1000Send_Code_QInput(&SendBuffer,0X11);
        }
    }

#endif	

}



