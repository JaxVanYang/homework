#include <stdio.h>
#define Time int
#define Max 100

typedef struct process {
  char name[10];   //进程名
  int priority;    //优先数
  Time ReachTime;  //到达时间
  Time NeedTime;   //需要运行时间
  Time UsedTime;   //已用时间
  char state;      //进程状态
} PCB;             //进程控制块

int n;  //标示进程的总数
PCB pcb[Max];
int pTime;  //时间片大小
void AddProcess() {
  char ch;
  do {
    printf("\n请输入进程名");
    scanf("%s", pcb[n].name);
    printf("请输入进程的优先级");
    scanf("%d", &pcb[n].priority);
    printf("请输入进程需要的时间");
    scanf("%d", &pcb[n].NeedTime);
    pcb[n].ReachTime = n;
    pcb[n].UsedTime = 0;
    pcb[n].state = 'W';
    n++;
    printf("还要继续增加进程吗,是(Y),否(N)");
    do {
      ch = getchar();
    } while (ch != 'Y' && ch != 'N' && ch != 'y' && ch != 'n');

  } while (ch == 'Y' || ch == 'y');
}
// 排序函数，将最先运行的进程放在最先即pcb[0]
void sort() {  //用冒泡排序
  int i, j;
  PCB temp;
  //先按到达时间排序
  for (i = 0; i < n - 1; i++) {
    for (j = n - 2; j >= i; j--) {
      if (pcb[j + 1].ReachTime < pcb[j].ReachTime) {
        temp = pcb[j];
        pcb[j] = pcb[j + 1];
        pcb[j + 1] = temp;
      }
    }
  }
  //再按优先级进行排序
  for (i = 0; i < n - 1; i++) {
    for (j = n - 2; j >= i; j--) {
      if (pcb[j + 1].priority > pcb[j].priority) {
        temp = pcb[j];
        pcb[j] = pcb[j + 1];
        pcb[j + 1] = temp;
      }
    }
  }
  if (pcb[0].state != 'F') {
    pcb[0].state = 'R';  //将优先级最高的状态置为运行
  }
}

void print()  //打印
{
  int i;
  sort();
  printf("\n  进程名    优先级   到达时间  需要时间  已用时间  进程状态 \n");
  for (i = 0; i < n; i++) {
    printf("%8s%8d%8d%10d%10d%10c\n", pcb[i].name, pcb[i].priority,
           pcb[i].ReachTime, pcb[i].NeedTime, pcb[i].UsedTime, pcb[i].state);
  }
}
void attemper()  //调度

{
  do {
    if ((pcb[0].NeedTime - pcb[0].UsedTime) > pTime) {
      pcb[0].UsedTime += pTime;  //已用时间加时间片
      pcb[0].priority--;         //优先级减一
      pcb[0].state = 'W';
    } else {
      pcb[0].UsedTime = pcb[0].NeedTime;  //已用时间等于需要时间
      pcb[0].priority = -1000;            //优先级置为零
      pcb[0].state = 'F';                 //完成进程，将状态置为完成
    }
    print();
  } while (pcb[0].state != 'F');
}
char face() {
  char choose;
  printf("\n增加进程并调度进程，请按1");
  printf("\n打印进程，请按2");
  printf("\n任务结束, 请按0");
  printf("\n请选择:");
  do {
    choose = getchar();
  } while (choose != '1' && choose != '2' && choose != '0');
  return choose;
}

void main() {
  char choose;
  n = 0;  //初始化进程数为0
  printf("设置时间片的大小:");
  scanf("%d", &pTime);
  choose = face();
  do {
    if (choose == '1') {
      AddProcess();
      print();
      attemper();
    }
    if (choose == '2') {
      print();
    }
    if (choose == '0') {
      return;
    }
    choose = face();
  } while (1);
}
