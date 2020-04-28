/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HEARTBEAT_H
#define __HEARTBEAT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "debug.h"
#include "app_ui.h"

#define HEARTBEAT_ENABLE                                    //�Ƿ�������������
#define TCPSEND_EVENT           0x01                        //TCP���ݷ����¼�
#define TCPREV_EVENT            0x02                        //TCP���ݽ����¼�
#define HEARTBEAT_TIMEOUT       (pdMS_TO_TICKS(60000))      //������ʱʱ��
#define HEARTBEAT_TRYTIMES		30	                        //������ʱ�����Դ���

	 
int HbInit(void);
void HbMainTask(void);
void tcpSendEvent(void);
void tcpRevEvent(void);


#ifdef __cplusplus
}
#endif
#endif /*__heartbeat_H */




