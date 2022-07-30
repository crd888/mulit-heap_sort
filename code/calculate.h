#ifndef CALCULATE_H_
#define CALCULATE_H_
#include "./config.h"

//文件1.txt处理函数
void *sort_txt1(void *val1);
//文件2.txt处理函数
void *sort_txt2(void *val2);
//文件3.txt处理函数
void *sort_txt3(void *val3);

//part1排序函数
void *sort1(void *val1);
//part2排序函数
void *sort2(void *val1);
//part3排序函数
void *sort3(void *val1);
//part4排序函数
void *sort4(void *val1);

//构造大根堆
void max_heap(struct Data_val *file, int start, int end, int index);
//每个文件最小堆排序
void min_heap_sort(struct Data_val *file, int index);
//swap
void swap(float *f1, float *f2);
//数据分配
int alloc_data(struct Reader_val *file1, struct Reader_val *file2, struct Reader_val *file3, struct Data_val *data);
//调试输出
void output1(struct Data_val *data);
//调试输出
void sorted_check(struct Data_val *data, int index);

#endif