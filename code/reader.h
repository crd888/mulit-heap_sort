#ifndef READER_H
#define READER_H
#include "./config.h"


//读取数据
void read_txt(struct Reader_val *val);
//解析数据
void parse_data(struct Reader_val *val);
//数字解析
float parse_digit(const char* temp);
//out
void output(struct Reader_val *val);

#endif