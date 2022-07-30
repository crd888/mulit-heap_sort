#ifndef CONFIG_H_
#define CONFIG_H_
#include <stdio.h>
#include "stdlib.h"
#include <unistd.h>
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "string.h"
#include "limits.h"
#include "stdbool.h"

#define CPU_NUMS 4 //4核处理器为例
//#define DEBUG

//用于调试输出
#ifdef DEBUG
	#define myPrint(...) printf(__VA_ARGS__)
#else
	#define myPrint(...)
#endif

//属性文件封装
struct Reader_val
{
	char file_name[36];
	long file_len;//文件原始长度
	int digit_nums;//文件中的数字个数
	char read_buf[600000];
	float digit_buf[600000];//建议值：100000
};

//统计数据属性
struct Data_val
{
	long total;//总数据量
	int pre_thread_datas;//每个线程处理的数据量
	float buf[CPU_NUMS][400000];//建议值：40000
};

//排序结果
struct Resault_val
{
	int all_digit_nums;//总的数字个数
	float res_buf[160000];
};

#endif