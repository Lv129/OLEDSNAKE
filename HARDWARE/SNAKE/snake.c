#include "snake.h"
#include "oled.h"
#include "key.h"
#include "stdio.h"
#include "delay.h"
#include "adc.h"

int Snake[27][15]={0};//�����ƶ��ĵ�ͼ
u8 length;    //�ߵĳ���
u8 direction;//�ߵķ���
u8 command_dir;//���Ʒ���
u8 Snake_Head_X;
u8 Snake_Head_Y;
u8 Snake_Tail_X;
u8 Snake_Tail_Y;

void GUI()//�����ʼ��
{
	Command();    //����
	Move();	      //�˶�
	GUI_Refresh();//����ˢ��
	Show();       //��ʾ����
	OLED_Refresh_Gram();	
}
void Show()//��ʾ
{
	OLED_ShowNum(116,0,length,2,12);//��ʾ����

}

//==================================================================
//������: Point
//����:   Lv����
//����:   2020/08/23
//����:   
//�������:
//����ֵ: 
//�޸ļ�¼:
//==================================================================

void GUI_Refresh()//����ˢ��
{
	int i,j;
	for(i=0;i<27;i++)
	for(j=0;j<15;j++)
	Paint_Body(i,j,Snake[i][j]);//����
	Point(Snake_Head_X,Snake_Head_Y,1);//����ͷ���ʵ��
	
}

void Command(void )//���Ʒ���
{
	u16 shangxia,zuoyou;
	  zuoyou=Get_Adc_Average(ADC_Channel_2,10);//��ȡҡ�����ҷ���ĵ�λ����ѹ��ģ��ֵ
		shangxia=Get_Adc_Average(ADC_Channel_1,10);//��ȡҡ�����·���ĵ�λ����ѹ��ģ��ֵ
	//����ģ�������жϷ���
	if(shangxia>3500)
		command_dir=DOWN;
	if(shangxia<1500)
		command_dir=UP;
	if(zuoyou>3500)
		command_dir=LEFT;
	if(zuoyou<1500)
		command_dir=RIGHT;

}

//==================================================================
//������: Snake_Init
//����:   Lv����
//����:   2020/08/23
//����:   ��ʼ���ߵ�λ���Լ�����
//�������:
//����ֵ: 
//�޸ļ�¼:
//==================================================================
void Snake_Init()//�߼�ʳ���ʼ��
{  int i,j;
	for(i=0;i<27;i++)
	for(j=0;j<15;j++)
	Snake[i][j]=0;
  length=3;
	direction=RIGHT;//���� 2468
	command_dir=RIGHT;
  Snake[7][7]=1;
	Snake[6][7]=2;
	Snake[5][7]=3;
	Snake_Head_X=7;
	Snake_Head_Y=7;
	Snake_Tail_X=5;
	Snake_Tail_X=7;
}

//==================================================================
//������: Map
//����:   Lv����
//����:   2020/08/23
//����:   ��泤���ε�ͼ�߽�
//�������:
//����ֵ: 
//�޸ļ�¼:
//==================================================================
void Map()//��ʼ����ͼ�߽�
{
		OLED_DrawLine(0,0,110,0);
		OLED_DrawLine(0,1,111,1);
		OLED_DrawLine(0,62,110,62);
		OLED_DrawLine(0,63,111,63);
	
		OLED_DrawLine(0,0,0,64);
		OLED_DrawLine(1,0,1,64);
		OLED_DrawLine(110,0,110,64);
		OLED_DrawLine(111,0,111,64);
}

//==================================================================
//������: Point
//����:   Lv����
//����:   2020/08/23
//����:   ���4*4��ʵ�ķ���
//�������:����:x(0~26)  ����:y(0~14) ģʽ:t 1��� 0����
//����ֵ: 
//�޸ļ�¼:
//==================================================================
void Point(u8 x,u8 y,u8 t)
{
	int i,j;
	if (t==0)
		t=0;
	else
		t=1;
	for(i=4*x+2;i<4*x+6;i++)    
	  for(j=4*y+2;j<4*y+6;j++)
		    OLED_DrawPoint(i,j,t); 
	
} 

//==================================================================
//������: Paint_Body
//����:   Lv����
//����:   2020/08/23
//����:   ����ߵ����岿�� �ڿյ�4*4���� 
//�������:����:x(0~26)  ����:y(0~14) ģʽ:t 1��� 0����
//����ֵ: 
//�޸ļ�¼:
//==================================================================
void Paint_Body(u8 x,u8 y,u8 t)
{
	Point(x,y,t);  //����4*4ʵ�ķ���
	OLED_DrawPoint(4*x+3,4*y+3,0); //�ڿ�4*4����
	OLED_DrawPoint(4*x+4,4*y+4,0); 
	OLED_DrawPoint(4*x+3,4*y+4,0); 
	OLED_DrawPoint(4*x+4,4*y+3,0); 
}
//==================================================================
//������: Food
//����:   Lv����
//����:   2020/08/23 
//����:   �ڿհ�(0)������ʳ(-1)
//�������:
//����ֵ: 
//�޸ļ�¼:
//==================================================================
void Food( )//����ʳ��
	{
		u8 x,y;
		do{
		x=rand()%27;   //��0-26���������
    y=rand()%15;   //��0-14���������
			}
		while(Snake[x][y]!=0);//ֱ��������괦Ԫ��Ϊ�հ�0 ��������������
	 Snake[x][y]=-1;//������Ҫ�������Ԫ�ظ�ֵʳ��-1
	}

//==================================================================
//������: New_Head
//����:   Lv����
//����:   2020/08/23
//����:   �����뷽����������ͷ
//�������:���� UP DOWN LEFT RIGHT
//����ֵ: 
//�޸ļ�¼:
//==================================================================
void New_Head(u8 t)
{
		switch(t)
		{
			case UP:
				if(Snake_Head_Y-1<0)//�ж��Ƿ�Խ�����ϱ߽磬����������±߽�������ͷ
				{
					Snake[Snake_Head_X][14]=1;
					Snake_Head_Y=14;
				}
				else
				Snake[Snake_Head_X][--Snake_Head_Y]=1;//�������һ�������Ԫ�ظ�ֵ1����ͷ��
				break;
				//���²ο�UP
			case DOWN:
				if(Snake_Head_Y+1>14)
				{
					Snake[Snake_Head_X][0]=1;
					Snake_Head_Y=0;
				}
				else
				Snake[Snake_Head_X][++Snake_Head_Y]=1;		
				break;
				
				case LEFT:
					if(Snake_Head_X-1<0)
				{
					Snake[26][Snake_Head_Y]=1;
					Snake_Head_X=26;
				}
				Snake[--Snake_Head_X][Snake_Head_Y]=1;		;
				break;
				
			case RIGHT:
			if(Snake_Head_X+1>26)
				{
					Snake[0][Snake_Head_Y]=1;
					Snake_Head_X=0;
				}
				else
				Snake[++Snake_Head_X][Snake_Head_Y]=1;		;
				break;
				
				default:
				break;
		}
			
}

//==================================================================
//������: Eat_Food
//����:   Lv����
//����:   2020/08/23 
//����:   ����Ե�ʳ�������� �ƶ�+ʳ���������
//�������:���� UP DOWN LEFT RIGHT
//����ֵ: 
//�޸ļ�¼:
//==================================================================

void Eat_Food(u8 t)
{
	switch(t)
	{
		case UP:
				New_Head(UP);//������ͷ
				Snake[Snake_Tail_X][Snake_Tail_Y]=length+1;		//����β��ֵ����+1��֮ǰȥ������β
				Food();	//�������ʳ��
				break;
			
		case DOWN:
				New_Head(DOWN);
				Snake[Snake_Tail_X][Snake_Tail_Y]=length+1;
				Food();
				break;
		
		case LEFT:
				New_Head(LEFT);
				Snake[Snake_Tail_X][Snake_Tail_Y]=length+1;
				Food();
				break;
		
				case RIGHT:	
				New_Head(RIGHT);
				Snake[Snake_Tail_X][Snake_Tail_Y]=length+1;
				Food();
				break;
				
				default:
				break;
	}
}

//==================================================================
//������: Game_Over
//����:   Lv����
//����:   2020/08/23 
//����:   ��Ϸ��������ʾGAMEOVER
//�������:
//����ֵ: 
//�޸ļ�¼:
//==================================================================

void Game_Over()
{
			OLED_ShowString(24,25,"GAME OVER",16);	
		  delay_ms(1000);
			Snake_Init();
	    Map();//��ʼ����ͼ�߽�
	    Food();
			OLED_Refresh_Gram();	
}

//==================================================================
//������: Move
//����:   Lv����
//����:   2020/08/23  
//����:   �ߵ��ƶ�
//�������:
//����ֵ: 
//�޸ļ�¼:
//==================================================================
void Move()
{
	int i,j;
	for(i=0;i<27;i++)
	for(j=0;j<15;j++)
	{
		if(Snake[i][j]>=length)//�����β����
		{
			length=Snake[i][j];
			Snake_Tail_X=i;
			Snake_Tail_Y=j;
		}
		if(Snake[i][j]==1)//�����ͷ����
		{
			Snake_Head_X=i;
			Snake_Head_Y=j;
		}
		if(Snake[i][j]>0)
			Snake[i][j]+=1;//��ά����SNAKE����Ԫ�أ�����0��+1
	}
	Snake[Snake_Tail_X][Snake_Tail_Y]=0;//��ȥ��β

	
		 switch(command_dir)//�Կ��Ʒ������ѡ����
    { 
			case UP:
			if(Snake[Snake_Head_X][Snake_Head_Y-1]>3)  				//ҧ������
	     Game_Over();																			//��Ϸ����
			else	if(Snake[Snake_Head_X][Snake_Head_Y-1]==-1)	//�Ե�ʳ��
				Eat_Food(command_dir);
			else if(direction==DOWN)                          //�˶��������£����ǿ��Ʒ������ϣ�Υ��
				New_Head(DOWN);                                 //����ԭ���ķ����ƶ�
			else{                                             //�����Υ�����տ��Ʒ����ƶ����˶�������Ϊ���Ʒ���
				New_Head(UP);
				direction=UP;}
        break;
			
			case DOWN:
				if(Snake[Snake_Head_X][Snake_Head_Y+1]>3)
					Game_Over();
			else if(Snake[Snake_Head_X][Snake_Head_Y+1]==-1)
					Eat_Food(command_dir);
			else if(direction==UP)
					New_Head(UP);
			else {
				New_Head(DOWN);
				direction=DOWN;}
        break;
				
			case LEFT:
			if(Snake[Snake_Head_X-1][Snake_Head_Y]>3)
				Game_Over();
			else if(Snake[Snake_Head_X-1][Snake_Head_Y]==-1)
				Eat_Food(command_dir);	
			else if(direction==RIGHT)
				New_Head(RIGHT);	
				else {			
					New_Head(LEFT);
					direction=LEFT;}	
        break;
				
			case RIGHT:
			if(Snake[Snake_Head_X+1][Snake_Head_Y]>3)
				Game_Over();
			else	if(Snake[Snake_Head_X+1][Snake_Head_Y]==-1)
				Eat_Food(command_dir);
			else if(direction==LEFT)
				New_Head(LEFT);
				else {
				New_Head(RIGHT);
				direction=RIGHT;	}
				break;
				
			default:
				break;	
		}	
}



