#include "./reader.h"

extern int error;

//读取数据
void read_txt(struct Reader_val *val)
{
	//属性初始化
	val->digit_nums = 0, val->file_len = 0;
	//打开文件
	FILE *fd = fopen(val->file_name, "r");
	if(fd == NULL)
	{
		printf("文件：%s 打开失败！\n", val->file_name);
		exit(0);
	}
	//定位到文件末尾，获取文件长度，以决定开辟多大的数组
	fseek(fd, 0, SEEK_END);
	val->file_len = ftell(fd);
	memset(val->read_buf, '\0',sizeof(val->read_buf));
	fseek(fd, 0, SEEK_SET);

	//读取文件数据到本地缓冲区中
	fread(val->read_buf, sizeof(char),  sizeof(val->read_buf), fd);
	fclose(fd);
	//统计有多少个数字
	for(int i = 0; i < val->file_len; ++i)
	{
		if(val->read_buf[i] == ' ') ++val->digit_nums;
	}

	//myPrint("文件：%s读取数据为：\n%s\n总共有：%d个数字\n", val->file_name, val->read_buf, val->digit_nums);

	parse_data(val);
}

//解析数据
void parse_data(struct Reader_val *val)
{
	//存放临时数字
	char temp[32];
	//存放总的解析结果
	memset(val->digit_buf, -1, sizeof(val->digit_buf));

	for(int i = 0, d = 0, t = 0; i < val->file_len; ++i)
	{
		if(val->read_buf[i] == ' ')
		{
			//数字解析
			float ans = parse_digit(temp);
			memset(temp, '\0', sizeof(temp));
			val->digit_buf[d++] = ans;
			t = 0;
		}
		else
		{
			temp[t++] = val->read_buf[i];
		}
	}
}

//数字解析
float parse_digit(const char* temp)
{
	float ans = 0;
	int is_integer_part = 1;
	float mul= 10;
	for(int i = 0; temp[i] != '\0' && i < 16; ++i)
	{
		//解析整数部分
		if(is_integer_part == 1)
		{
			if(temp[i] != '.') 
			{
				ans = ans * mul + temp[i] - '0';
			}
			else
			{
				is_integer_part = 0;
				mul = 0.1;
				continue;
			}
		}
		//解析小数部分
		if(is_integer_part == 0)
		{
			ans += mul * (temp[i] - '0');
			mul *= 0.1;
		}
	}
	return ans;
}

//输出
void output(struct Reader_val *val)
{
	myPrint("-----------------------原始数字内容为：------------------------\n");
	for(int i = 0; i < val->digit_nums; ++i)
	{
		myPrint("%f ", val->digit_buf[i]);
	}
	myPrint("     数量：%d\n", val->digit_nums);
}
