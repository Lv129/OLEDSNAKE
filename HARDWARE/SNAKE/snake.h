#ifndef _SNAKE_H_
#define _SNAKE_H_
#include "sys.h"
#include "stdbool.h"

#define UP 2
#define DOWN 8
#define LEFT 4
#define RIGHT 6

extern u8 length;
extern u8 direction;//�ߵķ���
extern u8 command_dir;//ָ�ӷ���
void GUI_Refresh(void);//����ˢ��
void GUI(void);//�����ʼ��
void Map(void);//��ʼ����ͼ�߽�
void Point(u8 x,u8 y,u8 t);
void Paint_Body(u8 x,u8 y ,u8 t);//��������
void Move(void);//�ƶ�
void Snake_Init(void);//�߼�ʳ���ʼ��
void New_Head(u8 t);  //��ͷ��
void Command(void );//���Ʒ���
void GameOver(void);//��Ϸ����
void Food(void);//����ʳ��
void Eat_Food(u8 t);//��ʳ��
void Show(void);//��ʾ


#endif  


