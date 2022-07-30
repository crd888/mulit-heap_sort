#include "./writer.h"
#include "./reader.h"


const char *output_txt_name = "./output/result.txt";
FILE *fp = NULL;
extern int error;

int trans(float n)
{
	int temp = (int)n;
	if((n - temp) > 0)
	{
		return -1;
	}
	return temp;
}

//写文件
void writer(float n)
{
		int num = trans(n);
		if(num != -1)
		{
			fprintf(fp, "%d ", num);
		}
		else
		{
			fprintf(fp, "%f ", n);
		}
}

//合并到文件中
void merge(struct Data_val *file)
{
	int n = file->pre_thread_datas;
	int obj = -1;
    int	part[4] = {0};
	float min_val = INT_MAX;
	if(fp == NULL) fp = fopen(output_txt_name, "a");
	if(fp == NULL) 
	{
		perror("fopen error:");
		exit(0);
	}

	while (part[0] < n || part[1] < n || part[2] < n || part[3] < n)
	{
		for(int i = 0; i < CPU_NUMS; ++i)
		{
			if(part[i] < n && file->buf[i][part[i]] < min_val)
			{
				obj = i;
				min_val = file->buf[i][part[i]];
			}
		}
		for(int i = 0; i < CPU_NUMS; ++i)
		{
			if(obj == i)
			{
				++part[obj];
			}
		}
		writer(min_val);
		min_val = INT_MAX;
		obj = -1;
	}
	fclose(fp);
}


//result.txt文件验证
void check_result(int input_nums)
{
	//打开文件
	FILE *fd = fopen(output_txt_name, "r");
	if(fd == NULL)
	{
		printf("文件：%s 打开失败！\n", output_txt_name);
		return;
	}
	//定位到文件末尾，获取文件长度，以决定开辟多大的数组
	fseek(fd, 0, SEEK_END);
	long len = ftell(fd);
	char *ans_buf = (char *)malloc(len);
	if(ans_buf == NULL)
	{
		perror("ans_buf malloc error:");
		return;
	}
	memset(ans_buf, '\0', len);
	fseek(fd, 0, SEEK_SET);

	//读取文件数据到本地缓冲区中
	fread(ans_buf, sizeof(char),  len, fd);
	fclose(fd);

	char temp[32];
	float last = 0;
	//统计有多少个数字
	int nums = 0;
	float ans = 0;
	for(int i = 0, t = 0; i < len; ++i)
	{
		if(ans_buf[i] == ' ') 
		{
			//数字解析
			ans = parse_digit(temp);
			memset(temp, '\0', sizeof(temp));
			if(ans < last) 
			{
				++error;
				myPrint("！！！文件%s中，位于%d处的数字：%f和%f排序错误！！！\n", output_txt_name, nums, last, ans);
			}
			t = 0;
			++nums;
			last = ans;
		}
		else
		{
			temp[t++] = ans_buf[i];
		}
	}
	if(input_nums != nums) 
	{
		printf("！！！输出文件result.txt验证错误，输出文件中共有：%d个数字，应该有：%d个数字！！！\n", nums, input_nums);
	}
	else if(error == 0)
	{
		printf("输出文件result.txt验证正确\n");
	}
	if(ans_buf) {free(ans_buf);ans_buf = NULL;}
}