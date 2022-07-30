# mulit-heap_sort
多线程堆排序

方案设计书

一、任务要求
将resource文件夹下面的1.txt，2.txt，3.txt三个文件里面的数据合并后按升序排列，并将排序结果存储在output/result.txt文件中，result.txt存储格式与原txt文件相同（数字之间用空格分隔）。
要求：用你能想到的最快的方式升序排列，写出思路和相应的C语言实现代码。

二、解决方案
针对传统的排序方法在数据量较大时出现计算过慢等情况，本方案设计了一种基于多线程加速的排序方法，首先利用多线程同时读取3个文档中的数据，并存入本地定义的结构体缓冲区中，同时对输入数据进行统计；依据CPU核心数与待排序数字的数量，通过主线程将数据分割，本方案设计4核cpu，因为由统计得出总共有160000个数据排序，所以每个线程分得40000个数据进行排序，各个线程的排序使用堆排序方法；当4个线程都排完序以后，各自进行数据量与是否有序进行验证；最后主线程将其合并到输出文件result.txt中，并且对输出文件进行验证分析，即验证是否全部按照升序排序。

三、说明
在读文件数据的时候，读入的整数部分与原文件一致，但小数部分在小数点后面第4位左右会与源文件有差异，但经过观察，不影响最后的排序结果。

四、运行
在Makefile文件所在的目录运行make命令即可，会自动编译并输出排序结果到文件中。

五、方案排序结果
实验平台：基于x86的Ubuntu 18.04，CMake 3.22.0，GCC 7.3.0，CPU主频最高1.7GHZ（最高2.4GHZ）。输出文件保存在/output/result.txt中，平均排序时间：90ms左右，实验阶段进行多次排序计时，结果如下所示：

<img width="444" alt="image" src="https://user-images.githubusercontent.com/81498573/181882906-cf0007e1-5e2d-4660-b113-b035e7f339dc.png">
<img width="415" alt="image" src="https://user-images.githubusercontent.com/81498573/181883013-ac730756-f8cd-4892-be99-4feb2c565ea5.png">
<img width="415" alt="image" src="https://user-images.githubusercontent.com/81498573/181883055-2407eb7a-7fa9-457c-973e-d27df996b9d3.png">
<img width="415" alt="image" src="https://user-images.githubusercontent.com/81498573/181883096-308546fc-4f54-4ae6-b19b-5765eda7312e.png">

