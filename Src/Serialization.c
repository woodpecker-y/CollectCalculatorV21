#include "serialization.h"


extern char SD_Path[4];					// SD���߼��豸·��
volatile uint32_t SD_Live = 0;
extern HAL_SD_CardInfoTypeDef SDCardInfo;

/* �ڲ��������� */


/* �����豸�������ɲ�ͬ���ļ��� */
RTC_EXT RealClock_Str RTC_Time;//ʵʱʱ��
void CreateFileName(char *buf, SysDEV_Type type)
{
    /* �����ļ��� */
    uint32_t tick = HAL_GetTick();
    char typeName[8];
    switch(type)
    {
        case Meter_B:
        sprintf(typeName,"MB");
        break;
        case Meter_U:
        sprintf(typeName,"MU");
        break;
        case Valve_U:
        sprintf(typeName,"VU");
        break;
        case Valve_UH:
        sprintf(typeName,"VUH");
        break;
#ifdef Meter_H_ENABLE
        case Meter_H:
        sprintf(typeName,"MH");

        break;
#endif
        default:
        break;
    }

    sprintf(buf,"%04d%02d%02d%02d%02d%02d-%s-%d.csv",RTC_Time.Year,RTC_Time.Month,RTC_Time.Day,RTC_Time.Hour,RTC_Time.Minute,RTC_Time.Second,typeName,tick);
    dbg_printf(DEBUG_INFO,"Create CSV fileName:%s",buf);
}


/* ��ȡSDCard��Ϣ�������ж�SD���Ƿ���� */
static int checkCard(void)
{
    HAL_StatusTypeDef res;
    res = SD_GetCardInfo(&SDCardInfo);
    if(HAL_OK == res)
    {
        LEDSD_ON;
        dbg_printf(DEBUG_INFO,"Get SDCard Info Success...");
        dbg_printf(DEBUG_INFO,"CardType:     %d",SDCardInfo.CardType);
        dbg_printf(DEBUG_INFO,"CardVersion:  %d",SDCardInfo.CardVersion);
        dbg_printf(DEBUG_INFO,"Class:        %d",SDCardInfo.Class);
        dbg_printf(DEBUG_INFO,"RelCardAdd:   %d",SDCardInfo.RelCardAdd);
        dbg_printf(DEBUG_INFO,"BlockNbr:     %d",SDCardInfo.BlockNbr);
        dbg_printf(DEBUG_INFO,"BlockSize:    %d",SDCardInfo.BlockSize);
        dbg_printf(DEBUG_INFO,"LogBlockNbr:  %d",SDCardInfo.LogBlockNbr);
        dbg_printf(DEBUG_INFO,"LogBlockSize: %d",SDCardInfo.LogBlockSize);
        return 0;
    }
    else
    {
        LEDSD_OFF;
        dbg_printf(DEBUG_WARNING,"Get SDCard Info Fail...");
        return -1;
    }
}

/* �����ļ�ϵͳ */
static FRESULT MountFS(void)
{
    static FATFS fs;							// FatFs�ļ�ϵͳ����
    FRESULT f_res;						//�ļ�������� 

    f_res = f_mount(&fs,(TCHAR const*)SD_Path,1);		//��SD�������ļ�ϵͳ���ļ�ϵͳ����ʱ���SD����ʼ��
    
    if(f_res == FR_NO_FILESYSTEM)					//���û���ļ�ϵͳ�͸�ʽ�����������ļ�ϵͳ
    {
        dbg_printf(DEBUG_WARNING,"��SD����û���ļ�ϵͳ���������и�ʽ��...");
        f_res = f_mkfs((TCHAR const*)SD_Path,0,0);			//��ʽ�� 			
      
        if(f_res == FR_OK)
        {
            dbg_printf(DEBUG_INFO,"SD���ѳɹ���ʽ���ļ�ϵͳ...");
            f_res = f_mount(NULL,(TCHAR const*)SD_Path,1);			// ��ʽ������ȡ������SD��
            f_res = f_mount(&fs,(TCHAR const*)SD_Path,1);			// ���¹���SD��
            return f_res;
        }
        else
        {
            dbg_printf(DEBUG_ERR,"��ʽ��ʧ��...");
            return f_res;
        }
    }
    else if(f_res != FR_OK)
    {
        dbg_printf(DEBUG_WARNING,"SD�������ļ�ϵͳʧ�ܡ�(%d)...",f_res);
        return f_res;
    }
    else
    {
        dbg_printf(DEBUG_INFO,"�ļ�ϵͳ���سɹ��������ʹ��...");
        return f_res;
    }
}

/* ϵͳ�ϵ��ʼ��SD�� */
static int InitSDCard(void)
{
    /* ���SD���Ƿ���� */
    int op_res;
    FRESULT mount_res;
    int try = FS_TRY_TIMES;

    while(try--)
    {
        op_res = checkCard();
        if(0 == op_res)
        {
            break;
        }
    }

    if(try <= 0)
    {
        return -1;//��ȡSD��ʧ��
    }

    /* ��⵽SD���������ļ�ϵͳ */
    try = FS_TRY_TIMES;
    while(try--)
    {
        mount_res = MountFS();
        if(FR_OK == mount_res)
        {
            break;
        }
    }
    
    if(try <= 0)
    {
        return -1;//�����ļ�ϵͳʧ��
    }

    return 0;
}

/* ж��SD�� */
static int DisSDCard(void)
{
    /* ж���ļ�ϵͳ */
    FRESULT res;
    res = f_mount(NULL,(TCHAR const*)SD_Path,1);// ����ʹ�ã�ȡ������
    if(FR_OK != res)
    {
        dbg_printf(DEBUG_WARNING,"Unmount FATFS fail...");
        return -1;
    }
    return 0;
}

/* �����豸���ͱ���ʵʱ���� */
const char *MeterB_Title = "�豸ID,��ˮ�¶�,��ˮ�¶�,˲ʱ���������٣�,��λ,˲ʱ���������ʣ�,��λ,�ۼ�����,��λ,�ۼ�����,��λ,�ۼ�����,��λ,���ڱ��,�����ڷ�̯����,����ʱ��,�ȱ����״̬1,�ȱ����״̬2\n";
const char *MeterU_Title = "�豸ID,��ˮ�¶�,��ˮ�¶�,˲ʱ���������٣�,��λ,˲ʱ���������ʣ�,��λ,�ۼ�����,��λ,�ۼ�����,��λ,�ۼ�����,��λ,����ʱ��,�ȱ����״̬1,�ȱ����״̬2\n";
const char *ValveU_Title = "�豸ID,ϵͳ�趨�¶�ǿ�Ʊ�־,�趨�¶�,ϵͳ�����¶�ǿ�Ʊ�־,�����趨�¶�,��������,ǿ�ƿ��Ʊ�־,��ǰ�¶�,ƽ���¶�,��ˮ�¶�,��ˮ�¶�,����λ��,���ڿ���ʱ��,���ڿ�������,��̯����,���״̬,����״̬\n";
const char *ValveUH_Title = "�豸ID,��������,ǿ�ƿ��Ʊ�־,����λ��,���ڿ���ʱ��,���ڿ�������,��̯����,����״̬\n";
const char *MeterH_Title = "�豸ID,��ˮ�¶�,��ˮ�¶�,˲ʱ���������٣�,��λ,˲ʱ���������ʣ�,��λ,�ۼ�����,��λ,�ۼ�����,��λ,�ۼ�����,��λ,���ڱ��,�����ڷ�̯����,����ʱ��,�ȱ����״̬1,�ȱ����״̬2\n";
DEVPARA_EXT SysDevData_Stru SysDevData[MAXDevice_Num];
DEVPARA_EXT SysDeviceList_Stru SysDeviceList;
#define WRITEBUFSIZE 2048
int SaveDeviceInfo(SysDEV_Type type)
{
    int sd_res;
    FRESULT f_res;
    FIL file;
    uint32_t writed;
    uint32_t key;
    char *writeBuf = NULL;

    /* ����д�뻺���� */
    writeBuf = pvPortMalloc(WRITEBUFSIZE);
    if(NULL == writeBuf)
    {
        dbg_printf(DEBUG_ERR,"�ڴ治�㣬SD�����ݱ���ʧ��");
        return -1;
    }
    memset(writeBuf,0x00,WRITEBUFSIZE);
    
    /*�����ļ�*/
    CreateFileName(writeBuf,type);//�����ļ���
    /* ���SD�� */
    sd_res = InitSDCard();
    if(0 != sd_res)
    {
        dbg_printf(DEBUG_WARNING,"SD������...");
        vPortFree(writeBuf);
        return -1;
    }
    /* �����ļ� */
    f_res = f_open(&file, writeBuf, FA_CREATE_ALWAYS | FA_WRITE );
    if(FR_OK != f_res)
    {
        vPortFree(writeBuf);
        return f_res;
    }

    /* �����ļ��ɹ�����ʼд������ */
    /*д�����*/
    switch(type)
    {
        case Meter_B:
        f_res = f_write(&file, MeterB_Title, strlen(MeterB_Title), &writed);
        break;
        case Meter_U:
        f_res = f_write(&file, MeterU_Title, strlen(MeterU_Title), &writed);
        break;
        case Valve_U:
        f_res = f_write(&file, ValveU_Title, strlen(ValveU_Title), &writed);
        break;
        case Valve_UH:
        f_res = f_write(&file, ValveUH_Title, strlen(ValveUH_Title), &writed);
        break;
#ifdef Meter_H_ENABLE
        case Meter_H:
        f_res = f_write(&file, MeterH_Title, strlen(MeterH_Title), &writed);
        break;
#endif
        default:
        break;
    }

    /* ѭ�������豸�б����浽Excel */
    for(int i=0;i<MAXDevice_Num;i++)
    {
        /* �����豸IDΪ����豸������Ҫ���� */
        if(0 == SysDeviceList.Device[i].ID)
        {
            continue;
        }

        /* ��ѡ���豸�����л� */
        if(type != SysDeviceList.Device[i].Type)
        {
            continue;
        }

        /* �豸ID��Ϊ��������ƥ��Ľ������л� */
        memset(writeBuf,0x00,WRITEBUFSIZE);
        key = BcdToHex4(&SysDeviceList.Device[i].ID);
        switch(type)
        {
            case Meter_B:
            sprintf(writeBuf,"%u,%u,%u,%lu,%u,%lu,%u,%lu,%u,%lu,%u,%lu,%u,%lu,%lu,%lu,%u,%u\n",key,SysDevData[i].Device1.Input_Temp,SysDevData[i].Device1.Output_Temp,\
            SysDevData[i].Device1.Instant_Current,SysDevData[i].Device1.Instant_Current_Unit,SysDevData[i].Device1.Instant_Energy,\
            SysDevData[i].Device1.Instant_Energy_Unit,SysDevData[i].Device1.Total_Current,SysDevData[i].Device1.Total_Current_Unit,\
            SysDevData[i].Device1.Total_Code,SysDevData[i].Device1.Total_Code_Unit,SysDevData[i].Device1.Total_Energy,SysDevData[i].Device1.Total_Energy_Unit,\
            SysDevData[i].Device1.CycBot_Energy,SysDevData[i].Device1.Apportion_Energy,SysDevData[i].Device1.Work_Time,
            SysDevData[i].Device1.STATE1,SysDevData[i].Device1.STATE2);
            f_res = f_write(&file, writeBuf, strlen(writeBuf), &writed);
            break;
            case Meter_U:
            sprintf(writeBuf,"%u,%u,%u,%lu,%u,%lu,%u,%lu,%u,%lu,%u,%lu,%u,%lu,%u,%u\n",key,SysDevData[i].Device2.Input_Temp,SysDevData[i].Device2.Output_Temp,\
            SysDevData[i].Device2.Instant_Current,SysDevData[i].Device2.Instant_Current_Unit,SysDevData[i].Device2.Instant_Energy,\
            SysDevData[i].Device2.Instant_Energy_Unit,SysDevData[i].Device2.Total_Current,SysDevData[i].Device2.Total_Current_Unit,\
            SysDevData[i].Device2.Total_Code,SysDevData[i].Device2.Total_Code_Unit,SysDevData[i].Device2.Total_Energy,SysDevData[i].Device2.Total_Energy_Unit,\
            SysDevData[i].Device2.Work_Time,SysDevData[i].Device2.STATE1,SysDevData[i].Device2.STATE2);
            f_res = f_write(&file, writeBuf, strlen(writeBuf), &writed);
            break;
            case Valve_U:
            sprintf(writeBuf,"%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%lu,%u,%lu,%u,%u,\n",key,SysDevData[i].Device3.Set_TCtrlFg,SysDevData[i].Device3.Set_Temp,\
            SysDevData[i].Device3.LimtTE_Flag,SysDevData[i].Device3.LimtTE_Value,SysDevData[i].Device3.ControlType,SysDevData[i].Device3.ForceCtrlFlg,
            SysDevData[i].Device3.Cur_Temp,SysDevData[i].Device3.Ave_Temp,SysDevData[i].Device3.Input_Temp,SysDevData[i].Device3.Output_Temp,\
            SysDevData[i].Device3.ValvePosition,SysDevData[i].Device3.Cycle_OpTim,SysDevData[i].Device3.Cycle_OpRat,SysDevData[i].Device3.Apportion_Energy,
            SysDevData[i].Device3.Face_State,SysDevData[i].Device3.Valve_State);
            f_res = f_write(&file, writeBuf, strlen(writeBuf), &writed);
            break;
            case Valve_UH:
            sprintf(writeBuf,"%u,%u,%u,%u,%lu,%u,%lu,%u\n",key,SysDevData[i].Device4.ControlType,SysDevData[i].Device4.ForceCtrlFlg,SysDevData[i].Device4.ValvePosition,\
            SysDevData[i].Device4.Cycle_OpTim,SysDevData[i].Device4.Cycle_OpRat,SysDevData[i].Device4.Apportion_Energy,SysDevData[i].Device4.Valve_State);
            f_res = f_write(&file, writeBuf, strlen(writeBuf), &writed);
            break;
#ifdef Meter_H_ENABLE
            case Meter_H:
            sprintf(writeBuf,"%u,%u,%u,%lu,%u,%lu,%u,%lu,%u,%lu,%u,%lu,%u,%lu,%lu,%lu,%u,%u\n",key,SysDevData[i].Device5.Input_Temp,SysDevData[i].Device5.Output_Temp,\
            SysDevData[i].Device5.Instant_Current,SysDevData[i].Device5.Instant_Current_Unit,SysDevData[i].Device5.Instant_Energy,\
            SysDevData[i].Device5.Instant_Energy_Unit,SysDevData[i].Device5.Total_Current,SysDevData[i].Device5.Total_Current_Unit,SysDevData[i].Device5.Total_Code,\
            SysDevData[i].Device5.Total_Code_Unit,SysDevData[i].Device5.Total_Energy,SysDevData[i].Device5.Total_Energy_Unit,\
            SysDevData[i].Device5.CycBot_Energy,SysDevData[i].Device5.Apportion_Energy,SysDevData[i].Device5.Work_Time,SysDevData[i].Device5.STATE1,SysDevData[i].Device5.STATE2);
            f_res = f_write(&file, writeBuf, strlen(writeBuf), &writed);
            break;
#endif
            default:
            break;
        }
        if(FR_OK != f_res)
        {
            dbg_printf(DEBUG_WARNING,"SD���ļ�д��ʧ��");
            break;
        }
    }
    /* д����ɣ��ر��ļ������ؽ�� */
    f_close(&file);

    /* ��־�ļ�д����ɣ��ͷ��ڴ沢ж���ļ�ϵͳ */
    sd_res = DisSDCard();
    vPortFree(writeBuf);
    return sd_res;
}

/* ������־ */
int SaveLog(void)
{
    int res;

    SDIO_Cfg();//SDIO���ܶ˿ڳ�ʼ��

    res = SaveDeviceInfo(Meter_B);
    if(0 != res)
    {
        dbg_printf(DEBUG_WARNING,"Save device:%d data fail...",Meter_B);
        return -1;
    }
    else
    {
        dbg_printf(DEBUG_NOTICE,"Save device:%d data success...",Meter_B);
    }

    res = SaveDeviceInfo(Meter_U);
    if(0 != res)
    {
        dbg_printf(DEBUG_WARNING,"Save device:%d data fail...",Meter_U);
        return -1;
    }
    else
    {
        dbg_printf(DEBUG_NOTICE,"Save device:%d data success...",Meter_U);
    }
    res = SaveDeviceInfo(Valve_U);
    if(0 != res)
    {
        dbg_printf(DEBUG_WARNING,"Save device:%d data fail...",Valve_U);
        return -1;
    }
    else
    {
        dbg_printf(DEBUG_NOTICE,"Save device:%d data success...",Valve_U);
    }
    res = SaveDeviceInfo(Valve_UH);
    if(0 != res)
    {
        dbg_printf(DEBUG_WARNING,"Save device:%d data fail...",Valve_UH);
        return -1;
    }
    else
    {
        dbg_printf(DEBUG_NOTICE,"Save device:%d data success...",Valve_UH);
    }
#ifdef Meter_H_ENABLE
    res = SaveDeviceInfo(Meter_H);
    if(0 != res)
    {
        dbg_printf(DEBUG_WARNING,"Save device:%d data fail...",Meter_H);
        return -1;
    }
    else
    {
        dbg_printf(DEBUG_NOTICE,"Save device:%d data success...",Meter_H);
    }
#endif
    return res;
}


