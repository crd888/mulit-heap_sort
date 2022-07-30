#ifndef WRITER_H_
#define WRITER_H_
#include "./config.h"

//打开输出文件
void open_output_txt();
//写文件
void writer(float n);
//合并所有的排序
void merge(struct Data_val *file);
int trans(float n);
//验证写文件是否正确
void check_result(int input_nums);

#endif