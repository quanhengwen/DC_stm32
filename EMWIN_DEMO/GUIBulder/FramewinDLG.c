/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.30                          *
*        Compiled Jul  1 2015, 10:50:32                              *
*        (c) 2015 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"
#include "led.h"
#include "GUI.h"
#include "Timer.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0   (GUI_ID_USER + 0x00)
#define ID_HEADER_0   (GUI_ID_USER + 0x01)
#define ID_TEXT_0   (GUI_ID_USER + 0x02)
#define ID_BUTTON_0   (GUI_ID_USER + 0x03)
#define ID_BUTTON_1   (GUI_ID_USER + 0x04)
#define ID_BUTTON_2   (GUI_ID_USER + 0x05)
#define ID_TEXT_1   (GUI_ID_USER + 0x06)
#define ID_TEXT_2   (GUI_ID_USER + 0x07)
#define ID_SPINBOX_0   (GUI_ID_USER + 0x08)
#define ID_CHECKBOX_0   (GUI_ID_USER + 0x09)
#define ID_CHECKBOX_1   (GUI_ID_USER + 0x0A)
#define ID_BUTTON_3   (GUI_ID_USER + 0x0B)
#define ID_BUTTON_4   (GUI_ID_USER + 0x0C)
#define ID_TEXT_3   (GUI_ID_USER + 0x0D)
#define ID_LISTVIEW_0   (GUI_ID_USER + 0x0E)


// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
static u8 ConfirmFlag; //����Confirmbox��ȫ�ֱ���
static u8 drill_depth; //������
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 480, 800, 0, 0x64, 0 },
  { HEADER_CreateIndirect, "Header", ID_HEADER_0, 0, 0, 480, 50, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text1", ID_TEXT_0, 0, 0, 469, 50, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, "Button1", ID_BUTTON_0, 40, 150, 100, 50, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button2", ID_BUTTON_1, 185, 150, 100, 50, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button3", ID_BUTTON_2, 330, 150, 100, 50, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text2", ID_TEXT_1, 40, 100, 240, 40, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text3", ID_TEXT_2, 40, 250, 200, 56, 0, 0x64, 0 },
  { SPINBOX_CreateIndirect, "Spinbox", ID_SPINBOX_0, 160, 255, 123, 46, 0, 0x0, 0 },
  { CHECKBOX_CreateIndirect, "Checkbox1", ID_CHECKBOX_0, 44, 350, 149, 20, 0, 0x0, 0 },
  { CHECKBOX_CreateIndirect, "Checkbox2", ID_CHECKBOX_1, 250, 350, 173, 20, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button4", ID_BUTTON_3, 40, 410, 150, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button5", ID_BUTTON_4, 250, 410, 150, 60, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text4", ID_TEXT_3, 288, 263, 93, 30, 0, 0x64, 0 },
  { LISTVIEW_CreateIndirect, "Listview", ID_LISTVIEW_0, 40, 520, 200, 180, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code

*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
//����������ת��Ϊ�Ƕ�
double count_to_angle(u16 count)
{
	double angle = 0.0;
//	if(count > 65535/2)count -= 65535;
	if(count > 65535/2)count = 65535 - count;
	angle = (double)count / 10000 * 360;
	return angle;
}


// USER END


/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
	u16 count1 = 0;
	u16 count2 = 0;
	u16 count3 = 0;
	u16 count4 = 0;
	u16 count5 = 0;	
	double angle1 = 123.12312;
	double angle2 = -0.444;
	double angle3 = 123.4111;
	double angle4 = 1.323;
	double angle5 = 13.0121;
	char joint_angle1[6]; 
	char joint_angle2[6]; 
	char joint_angle3[6];
	char joint_angle4[6]; 
	char joint_angle5[6];
  // USER START (Optionally insert additional variables)
  // USER END
  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Framewin'
    //
    hItem = pMsg->hWin;
		
    FRAMEWIN_SetText(hItem, "Framewin");
    FRAMEWIN_SetTitleVis(hItem, 0);
    FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    FRAMEWIN_SetTextColor(hItem, GUI_MAKE_COLOR(0x00FFFF00));
    //
    // Initialization of 'Text1'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetFont(hItem, GUI_FONT_32_ASCII);
    TEXT_SetTextColor(hItem, GUI_MAKE_COLOR(0x000000FF));
    TEXT_SetText(hItem, "Auxiliary Drilling Device");
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    //
    // Initialization of 'Button1'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetFont(hItem, GUI_FONT_20_ASCII);
    BUTTON_SetText(hItem, "Drag");
    //
    // Initialization of 'Button2'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetFont(hItem, GUI_FONT_20_ASCII);
    BUTTON_SetText(hItem, "Inch");
    //
    // Initialization of 'Button3'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
    BUTTON_SetFont(hItem, GUI_FONT_20_ASCII);
    BUTTON_SetText(hItem, "Lock");
    //
    // Initialization of 'Text2'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
    TEXT_SetText(hItem, "Position and Orientation");
    TEXT_SetTextColor(hItem, GUI_MAKE_COLOR(0x00FF0000));
    //
    // Initialization of 'Text3'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "Drilling Depth:");
    TEXT_SetFont(hItem, GUI_FONT_20_ASCII);
    TEXT_SetTextColor(hItem, GUI_MAKE_COLOR(0x00FF0000));
    //
    // Initialization of 'Spinbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_0);
    SPINBOX_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'Checkbox1'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_0);
    CHECKBOX_SetText(hItem, "Depth Confirm");
    CHECKBOX_SetFont(hItem, GUI_FONT_20_ASCII);
		ConfirmFlag = 0; //Ĭ��Confrim û��ѡ��
    //
    // Initialization of 'Checkbox2'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_1);
    CHECKBOX_SetText(hItem, "Reverse Direction");
    CHECKBOX_SetFont(hItem, GUI_FONT_20_ASCII);
    //
    // Initialization of 'Button4'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
    BUTTON_SetText(hItem, "Start");
    BUTTON_SetFont(hItem, GUI_FONT_32_ASCII);
    //
    // Initialization of 'Button5'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_4);
    BUTTON_SetText(hItem, "Stop");
    BUTTON_SetFont(hItem, GUI_FONT_32_ASCII);
    //
    // Initialization of 'Text4'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_20_ASCII);
    TEXT_SetText(hItem, "(mm)");
    TEXT_SetTextColor(hItem, GUI_MAKE_COLOR(0x00000000));
    //
    // Initialization of 'Listview'
    //
//		count1=__HAL_TIM_GET_COUNTER(&TIM1_Handler);
//		count2=__HAL_TIM_GET_COUNTER(&TIM2_Handler);
//		count3=__HAL_TIM_GET_COUNTER(&TIM3_Handler);
//		count4=__HAL_TIM_GET_COUNTER(&TIM4_Handler);
//		count5=__HAL_TIM_GET_COUNTER(&TIM5_Handler);
//		angle1 = count_to_angle(count1);
//		angle2 = count_to_angle(count2);
//		angle3 = count_to_angle(count3);
//		angle4 = count_to_angle(count4);
//		angle5 = count_to_angle(count5);
		//С��ת�ַ���
		sprintf(&joint_angle1[0], "%6.2f", angle1);
		sprintf(&joint_angle2[0], "%6.2f", angle2);
		sprintf(&joint_angle3[0], "%6.2f", angle3);
		sprintf(&joint_angle4[0], "%6.2f", angle4);
		sprintf(&joint_angle5[0], "%6.2f", angle5);
		
    hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
    LISTVIEW_AddColumn(hItem, 100, "number of joints", GUI_TA_HCENTER | GUI_TA_VCENTER);
    LISTVIEW_SetGridVis(hItem, 1);
    LISTVIEW_AddRow(hItem, NULL);
		LISTVIEW_AddRow(hItem, NULL);
		LISTVIEW_AddRow(hItem, NULL);
    LISTVIEW_AddRow(hItem, NULL);
    LISTVIEW_AddRow(hItem, NULL);
    LISTVIEW_AddColumn(hItem, 100, "relative angles", GUI_TA_HCENTER | GUI_TA_VCENTER);
    LISTVIEW_SetRowHeight(hItem, 30);
    LISTVIEW_SetHeaderHeight(hItem, 30);
    LISTVIEW_SetItemText(hItem, 0, 0, "joint1");
    LISTVIEW_SetItemText(hItem, 0, 1, "joint2");
    LISTVIEW_SetItemText(hItem, 0, 2, "joint3");
    LISTVIEW_SetItemText(hItem, 0, 3, "joint4");
    LISTVIEW_SetItemText(hItem, 0, 4, "joint5");
		LISTVIEW_SetItemText(hItem, 1, 0, &joint_angle1[0]);
    LISTVIEW_SetItemText(hItem, 1, 1, &joint_angle2[0]);
    LISTVIEW_SetItemText(hItem, 1, 2, &joint_angle3[0]);
    LISTVIEW_SetItemText(hItem, 1, 3, &joint_angle4[0]);
    LISTVIEW_SetItemText(hItem, 1, 4, &joint_angle5[0]);
    LISTVIEW_SetFont(hItem, GUI_FONT_20_ASCII);
    LISTVIEW_SetItemBkColor(hItem, 0, 0, LISTVIEW_CI_UNSEL, GUI_MAKE_COLOR(0x00FFFFFF));
		
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
		case WM_PAINT:
		count1=__HAL_TIM_GET_COUNTER(&TIM1_Handler);
		count2=__HAL_TIM_GET_COUNTER(&TIM2_Handler);
		count3=__HAL_TIM_GET_COUNTER(&TIM3_Handler);
		count4=__HAL_TIM_GET_COUNTER(&TIM4_Handler);
		count5=__HAL_TIM_GET_COUNTER(&TIM5_Handler);
		angle1 = count_to_angle(count1);
		angle2 = count_to_angle(count2);
		angle3 = count_to_angle(count3);
		angle4 = count_to_angle(count4);
		angle5 = count_to_angle(count5);
		//С��ת�ַ���
		sprintf(&joint_angle1[0], "%6.2f", angle1);
		sprintf(&joint_angle2[0], "%6.2f", angle2);
		sprintf(&joint_angle3[0], "%6.2f", angle3);
		sprintf(&joint_angle4[0], "%6.2f", angle4);
		sprintf(&joint_angle5[0], "%6.2f", angle5);
//		
    hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
//    LISTVIEW_AddColumn(hItem, 100, "number of joints", GUI_TA_HCENTER | GUI_TA_VCENTER);
//    LISTVIEW_SetGridVis(hItem, 1);
//    LISTVIEW_AddRow(hItem, NULL);
//		LISTVIEW_AddRow(hItem, NULL);
//		LISTVIEW_AddRow(hItem, NULL);
//    LISTVIEW_AddRow(hItem, NULL);
//    LISTVIEW_AddRow(hItem, NULL);
//    LISTVIEW_AddColumn(hItem, 100, "relative angles", GUI_TA_HCENTER | GUI_TA_VCENTER);
//    LISTVIEW_SetRowHeight(hItem, 30);
//    LISTVIEW_SetHeaderHeight(hItem, 30);
    LISTVIEW_SetItemText(hItem, 0, 0, "joint1");
    LISTVIEW_SetItemText(hItem, 0, 1, "joint2");
    LISTVIEW_SetItemText(hItem, 0, 2, "joint3");
    LISTVIEW_SetItemText(hItem, 0, 3, "joint4");
    LISTVIEW_SetItemText(hItem, 0, 4, "joint5");
		LISTVIEW_SetItemText(hItem, 1, 0, &joint_angle1[0]);
    LISTVIEW_SetItemText(hItem, 1, 1, &joint_angle2[0]);
    LISTVIEW_SetItemText(hItem, 1, 2, &joint_angle3[0]);
    LISTVIEW_SetItemText(hItem, 1, 3, &joint_angle4[0]);
    LISTVIEW_SetItemText(hItem, 1, 4, &joint_angle5[0]);
//    LISTVIEW_SetFont(hItem, GUI_FONT_20_ASCII);
//    LISTVIEW_SetItemBkColor(hItem, 0, 0, LISTVIEW_CI_UNSEL, GUI_MAKE_COLOR(0x00FFFFFF));
		break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
		
    switch(Id) {
    case ID_HEADER_0: // Notifications sent by 'Header'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_MOVED_OUT:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_0: // Notifications sent by 'Button1'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				TIM_SetTIM8Compare1(10);
				TIM_SetTIM8Compare2(10);
				TIM_SetTIM8Compare3(10);
				TIM_SetTIM8Compare4(10);
				TIM_SetTIM9Compare1(0);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'Button2'
			
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				TIM_SetTIM8Compare1(50);
				TIM_SetTIM8Compare2(50);
				TIM_SetTIM8Compare3(50);
				TIM_SetTIM8Compare4(50);
				TIM_SetTIM9Compare1(30);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_2: // Notifications sent by 'Button3'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				TIM_SetTIM8Compare1(100);
				TIM_SetTIM8Compare2(100);
				TIM_SetTIM8Compare3(100);
				TIM_SetTIM8Compare4(100);
				TIM_SetTIM9Compare1(100);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_SPINBOX_0: // Notifications sent by 'Spinbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_MOVED_OUT:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
				drill_depth = SPINBOX_GetValue(pMsg->hWinSrc);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_CHECKBOX_0: // Notifications sent by 'Checkbox1'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
				if (ConfirmFlag)ConfirmFlag = 0;
			  else ConfirmFlag = 1; 
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_CHECKBOX_1: // Notifications sent by 'Checkbox2'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
				LED1_Toggle;   //�����ѡ��2��ѡ�У�LED1��ת,�ı䷽��
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_3: // Notifications sent by 'Button4'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				if(ConfirmFlag)SendPulse(drill_depth);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_4: // Notifications sent by 'Button5'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				HAL_TIM_PWM_Stop_IT(&TIM10_Handler,TIM_CHANNEL_1);//�ر�TIM10ͨ��1�ж�ģʽ
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_LISTVIEW_0: // Notifications sent by 'Listview'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateFramewin
*/
WM_HWIN CreateFramewin(void);
WM_HWIN CreateFramewin(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	while(1)
	{
		WM_Invalidate(hWin);
		GUI_Delay(100);
	}
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/