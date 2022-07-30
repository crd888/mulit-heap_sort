#include <pthread.h>
#include <sys/time.h>
#include "./reader.h"
#include "./writer.h"
#include "./config.h"
#include "./calculate.h"

int error = 0;//排序错误个数

int main()
{
	//开始计时
	struct timeval start1, start2, end2, end1;
	gettimeofday(&start1, NULL);
	struct Reader_val *file1 = (struct Reader_val*)malloc(sizeof(struct Reader_val));
	struct Reader_val *file2 = (struct Reader_val*)malloc(sizeof(struct Reader_val));
	struct Reader_val *file3 = (struct Reader_val*)malloc(sizeof(struct Reader_val));
	if(file1 == NULL || file2 == NULL || file3 == NULL)
	{
		perror("file malloc error:");
		return 0;
	}

//--------------------------------多线程读文件-----------------------------------
	pthread_t pid1, pid2, pid3, pid4;
	if(pthread_create(&pid1, NULL, &sort_txt1, (void*)file1) != 0)
	{
		perror("pthread_create1:");
		return 0;
	}
	if(pthread_create(&pid2, NULL, &sort_txt2, (void*)file2) != 0)
	{
		perror("pthread_create2:");
		return 0;
	}
	if(pthread_create(&pid3, NULL, &sort_txt3, (void*)file3) != 0)
	{
		perror("pthread_create3:");
		return 0;
	}
	pthread_join(pid1, NULL);
	pthread_join(pid2, NULL);
	pthread_join(pid3, NULL);
	myPrint("多线程读文档完毕\n");

//--------------------------------主线程数据分配------------------------------------
	gettimeofday(&start2, NULL);
	struct Data_val *data = (struct Data_val *)malloc(sizeof(struct Data_val));
	if(data == NULL)
	{
		perror("data malloc error:");
		return 0;
	}
	//数据分配
	int total_digits = alloc_data(file1, file2, file3, data);
	if(total_digits == 0)
	{
		printf("！！！数据分配错误，已退出！！！\n");
		return 0;
	}
	//output1(data);
	myPrint("分配数据完毕\n");

//-----------------------------------多线程排序-------------------------------------
	if(pthread_create(&pid1, NULL, &sort1, (void*)data) != 0)
	{
		perror("pthread_create1:");
		return 0;
	}
	if(pthread_create(&pid2, NULL, &sort2, (void*)data) != 0)
	{
		perror("pthread_create2:");
		return 0;
	}
	if(pthread_create(&pid3, NULL, &sort3, (void*)data) != 0)
	{
		perror("pthread_create3:");
		return 0;
	}
	if(pthread_create(&pid4, NULL, &sort4, (void*)data) != 0)
	{
		perror("pthread_create4:");
		return 0;
	}
	pthread_join(pid1, NULL);
	pthread_join(pid2, NULL);
	pthread_join(pid3, NULL);
	pthread_join(pid4, NULL);
	myPrint("多线程排序完毕\n");

	if(error > 0) 
	{
		printf("！！！分组排序失败，共有%d个错误！！！\n", error);
		return 0;
	}
	else
	{
		printf("分组排序成功\n");
	}
	merge(data);

	gettimeofday(&end2, NULL);
	myPrint("单独排序花费时间：%dms\n", (int)(end2.tv_usec - start2.tv_usec) / 1000);
	gettimeofday(&end1, NULL);
	myPrint("加上输入输出文件排序花费时间：%dms\n", (int)(end1.tv_usec - start1.tv_usec) / 1000);

	//check result.txt
	check_result(total_digits);
	
	if(file1) {free(file1);file1 = NULL;}
	if(file2) {free(file2);file2 = NULL;}
	if(file3) {free(file3);file3 = NULL;}
	if(data) {free(data);data = NULL;}

	return 0;
}

