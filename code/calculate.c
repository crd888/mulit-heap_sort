#include "./calculate.h"
#include "./reader.h"


const char* txt1 = "./resource/1.txt";
const char* txt2 = "./resource/2.txt";
const char* txt3 = "./resource/3.txt";

extern int error;

//文件1.txt处理函数
void *sort_txt1(void *val1)
{
	struct Reader_val *file1 = (struct Reader_val *)val1;
	strcpy(file1->file_name, txt1);
	read_txt(file1);
	//output(file1);//调试
	return NULL;
} 

//文件2.txt处理函数
void *sort_txt2(void *val2)
{
	struct Reader_val *file2 = (struct Reader_val *)val2;
	strcpy(file2->file_name, txt2);
	read_txt(file2);
	//output(file2);
	return NULL;
} 

//文件3.txt处理函数
void *sort_txt3(void *val3)
{
	struct Reader_val *file3 = (struct Reader_val *)val3;
	strcpy(file3->file_name, txt3);
	read_txt(file3);
	//output(file3);
	return NULL;
} 


//part1排序函数
void *sort1(void *val1)
{
	struct Data_val *file1 = (struct Data_val *)val1;
	min_heap_sort(file1, 0);
	sorted_check(file1, 0);//校验
	return NULL;
}

//part2排序函数
void *sort2(void *val2)
{
	struct Data_val *file2 = (struct Data_val *)val2;
	min_heap_sort(file2, 1);
	sorted_check(file2, 1);
	return NULL;
}

//part3排序函数
void *sort3(void *val3)
{
	struct Data_val *file3 = (struct Data_val *)val3;
	min_heap_sort(file3, 2);
	sorted_check(file3, 2);
	return NULL;
}

//part4排序函数
void *sort4(void *val4)
{
	struct Data_val *file4 = (struct Data_val *)val4;
	min_heap_sort(file4, 3);
	sorted_check(file4, 3);
	return NULL;
}


//构造大根堆
void max_heap(struct Data_val *file, int start, int end, int index)
{
	//定位父子节点
	int father = start;
	int son = 2 * father + 1;
	while(son < end)//向下搜索
	{
		if(son + 1 < end && file->buf[index][son] < file->buf[index][son + 1])
		{
			son++;
		}
		if(file->buf[index][father] > file->buf[index][son])
		{
			return;
		}
		else
		{
			swap(&file->buf[index][father], &file->buf[index][son]);
			father = son;
			son = 2 * father + 1;
		}
	}
}

//每个文件最小堆排序
void min_heap_sort(struct Data_val *file, int index)
{
	int n = file->pre_thread_datas;
	//从最后一个父节点开始搜索更新
	for (int i = (n - 1) / 2; i >= 0; --i)
	{
		max_heap(file, i, n, index);
	}
	//堆顶元素与最后一个元素交换
	for(int i = n - 1; i >= 0; --i)
	{
		swap(&file->buf[index][0], &file->buf[index][i]);
		max_heap(file, 0, i, index);
	}
}

void swap(float *f1, float *f2)
{
	float t = *f1;
	*f1 = *f2;
	*f2 = t;
}


//数据分配
int alloc_data(struct Reader_val *file1, struct Reader_val *file2, struct Reader_val *file3, struct Data_val *data)
{
	for(int i = 0; i < CPU_NUMS; ++i)
	{
		memset(data->buf[i], 0, sizeof(data->buf[i]));
	}
	int total =  file1->digit_nums + file2->digit_nums + file3->digit_nums;
	data->pre_thread_datas = total / CPU_NUMS;
	myPrint("总共有：%d个排序数字，%d线程CPU中，每个线程处理%d个数据\n",total, CPU_NUMS, data->pre_thread_datas);

	int p = 0, file_flag = 1, f = 0;
	while (1)
	{
		if(file_flag == 1)//拷贝第一个文件
		{
			if(f < file1->digit_nums)
			{
				int i = p / data->pre_thread_datas;
				int j = p++ % data->pre_thread_datas;
				data->buf[i][j] = file1->digit_buf[f++];
			}
			else
			{
				file_flag = 2;
				f = 0;
			}
		}
		if(file_flag == 2)
		{
			if(f < file2->digit_nums)
			{
				int i = p / data->pre_thread_datas;
				int j = p++ % data->pre_thread_datas;
				data->buf[i][j] = file2->digit_buf[f++];
			}
			else
			{
				file_flag = 3;
				f = 0;
			}
		}
		if(file_flag == 3)
		{
			if(f < file3->digit_nums)
			{
				int i = p / data->pre_thread_datas;
				int j = p++ % data->pre_thread_datas;
				data->buf[i][j] = file3->digit_buf[f++];
			}
			else
			{
				break;
			}
		}
	}
	if(p != total) 
	{
		printf("！！！数据分组错误，原来有：%d个数字，实际拷贝了：%d个数字\n", total, p);
		exit(0);
	}
	return total;
}

//调试输出
void output1(struct Data_val *data)
{
	for(int i = 0; i < CPU_NUMS; ++i)
	{
		for(int j = 0; j < data->pre_thread_datas; ++j)
		{
			myPrint("%f,", data->buf[i][j]);
		}
		myPrint("\n");
	}
}

//调试输出
void sorted_check(struct Data_val *data, int index)
{
	for(int j = 0; j < data->pre_thread_datas; ++j)
	{
		//myPrint("%f,", data->buf[index][j]);
		if(j > 0 && data->buf[index][j - 1] > data->buf[index][j]) 
		{
			printf("！！！缓存区%d排序错误，%f和%f错误！\n", index, data->buf[index][j - 1] , data->buf[index][j]);
			error ++;
		}
	}
}

