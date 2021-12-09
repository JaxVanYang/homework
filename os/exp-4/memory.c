#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXJOB 5
// const int MAXJOB = 5;  //定义表最大记录数
typedef struct node {
  int front;
  int length;
  char data[20];
} job;  //定义job类型的数据类型

job frees[MAXJOB];  //定义空闲区表
int free_quantity;

job occupys[MAXJOB];  //定义已分配区表
int occupy_quantity;

//初始化并创建空闲分区表函数
int initial() {
  int i;
  frees[0].front = 0;
  frees[0].length = 30;
  occupys[0].front = 0;
  occupys[0].length = 0;
  strcpy(frees[0].data, "free");
  for (i = 1; i < MAXJOB; i++) {
    frees[i].front = frees[i - 1].front + frees[i - 1].length;
    frees[i].length = frees[i - 1].length + 20;
    strcpy(frees[i].data, "free");
    occupys[i].front = 0;
    occupys[i].length = 0;
    strcpy(occupys[i].data, " ");
  }
  free_quantity = MAXJOB;
  occupy_quantity = 0;
  return 1;
}

//显示函数
void show() {
  int i;
  printf("----------------------------------------------------------\n");
  printf("当前空闲分区表如下:\n");
  printf("起始地址     长度      状态\n");
  for (i = 0; i < free_quantity; i++) {
    printf("%5d   %8d       %s\n", frees[i].front, frees[i].length,
           frees[i].data);
  }
  printf("----------------------------------------------------------\n");
  printf("当前已分配表如下:\n");
  printf("起始地址    长度    占用作业名\n");
  for (i = 0; i < occupy_quantity; i++) {
    printf("%5d     %6d       %s\n", occupys[i].front, occupys[i].length,
           occupys[i].data);
  }
  printf("----------------------------------------------------------\n");
}

//首次适应分配算法
void assign() {
  char job_name[20];
  int job_length;
  int i, j, flag, t;
  printf("请输入新申请内存空间的作业名和空间大小:");
  scanf("%s", job_name);
  scanf("%d", &job_length);
  flag = 0;
  for (i = 0; i < free_quantity; i++) {
    if (frees[i].length >= job_length)  //如果空闲空间I的长度>=作业长度
    {
      flag = 1;  //空闲标志位就置1
    }
  }
  if (flag == 0) {
    printf("对不起,当前没有能满足你申请长度的空闲内存,请稍候再试！\n");
  } else {
    t = 0;
    i = 0;
    while (t == 0)  //为空闲区间的时候
    {
      if (frees[i].length >= job_length) {
        t = 1;
      }
      i++;  //如果空闲空间I的长度不大于作业长度，I加1，判断下一个空间
    }
    i--;
    occupys[occupy_quantity].front =
        frees[i].front;  //把未用的空闲空间的首地址付给已用空间的首地址
    strcpy(occupys[occupy_quantity].data, job_name);  //已用空间的内容为作业名
    occupys[occupy_quantity].length = job_length;  //已用空间的长度为作业的长度
    occupy_quantity++;                             //已用空间数量加1
    if (frees[i].length > job_length)  //如果空间的长度大于作业的长度，
    {
      frees[i].front +=
          job_length;  //空闲空间的起始首地址=原空闲区间的起始长度加作业长度
      frees[i].length -=
          job_length;  //空闲区间的长度=原空闲区间的长度-作业的长度
    } else             //如果空间的长度=作业的长度
    {
      for (j = i; j < free_quantity - 1; j++) {
        frees[j] = frees[j + 1];  //空闲区间前移一位
      }
      free_quantity--;  //空闲区间的数量减一
    }
    printf("内存空间分配成功!\n");
  }
}

//撤消作业
void cancel() {
  char job_name[20];
  int i, j, flag, p = 0;
  int start;
  int len;
  printf("请输入要撤消的作业名:");
  scanf("%s", job_name);
  flag = -1;
  for (i = 0; i < occupy_quantity; i++) {
    if (!strcmp(occupys[i].data, job_name))  //当输入作业名匹配时
    {
      flag = i;                  //把i的值赋给flag;
      start = occupys[i].front;  //把已用空间的首地址赋给start
      len = occupys[i].length;   //把已用空间的长度赋给len
    }
  }
  if (flag == -1) {
    printf("没有这个作业名，请重新输入作业名！\n");
  } else {  //加入空闲表
    for (i = 0; i < free_quantity; i++) {
      if ((frees[i].front + frees[i].length) == start)  //上空
      {
        if (((i + 1) < free_quantity) &&
            (frees[i + 1].front == start + len))  //下空
        {
          //第i个空闲区间的长度=第i个空闲区间的长度+第i+1个空闲区间的长度（下空闲区）+length
          frees[i].length = frees[i].length + frees[i + 1].length + len;
          for (j = i + 1; j < free_quantity; j++) {
            frees[j] = frees[j + 1];  //空闲区间前移一位
          }
          free_quantity--;  //空闲区的数量渐少了一个
          p = 1;
        } else {
          frees[i].length +=
              len;  //（上空下不空）第i个空闲区间的长度=第i个空闲区间的长度+length，空闲区个数不变
          p = 1;
        }
      }
      if (frees[i].front == (start + len))  //下空上不空
      {
        frees[i].front = start;  //起始地址等于待回收地址
        frees[i].length +=
            len;  //第i个空闲区间的长度=第i个空闲区间的长度+length
        p = 1;
      }
    }
    if (p ==
        0)  //上下空闲区都不空（直接在空闲区表中找一个空表目，将其内容插入）
    {
      frees[free_quantity].front = start;
      frees[free_quantity].length = len;
      free_quantity++;  //空闲区的数量加1
    }
    //删除分配表中的该作业
    for (i = flag; i < occupy_quantity; i++) {
      occupys[i] = occupys[i + 1];
    }
    occupy_quantity--;  //已用的区的数量
    printf("内存空间回收完毕!\n");
  }
}

//主函数
int main() {
  int flag = 0;
  int t = 1;
  int chioce = 0;
  printf(" |--------------------------------------------------|\n");
  printf(" |     可变分区存储管理模拟系统                     |\n");
  printf(" |--------------------------------------------------|\n");
  printf(" |菜单: (0)退出                                     |\n");
  printf(" |                                                  |\n");
  printf(" |      (1)申请空间     (2)撤消作业                 |\n");
  printf(" |                                                  |\n");
  printf(" |      (3)显示空闲表和分配表                       |\n");
  printf(" |--------------------------------------------------|\n");
  initial();
  flag = initial();
  while (flag == 1) {
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("请选择:");
    scanf("%d", &chioce);
    switch (chioce) {
      case 1:
        assign();
        break;
      case 2:
        cancel();
        break;
      case 3:
        show();
        break;
      case 0:
        flag = 0;
        break;
      default:
        printf("选择错误!");
    }
  }

  return 0;
}
