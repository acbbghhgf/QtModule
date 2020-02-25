#include <QtCore/QCoreApplication>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int read(void){
    static int num = 0;
    printf("请输入一个数字：");
    num = 15;
//    scanf("%d", &num);
    return num;
}

int main(){
    int num;
    printf("hello world\n");
    num = read();
    printf("%d\n", num);
    return 0;
}
