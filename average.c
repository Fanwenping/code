/*
@ 规避边界溢出的求均值算法
@（1）算法
	设x为已有数据的平均数，n为已有数据的个数，新的数据为y，那么
	(x * n + y)/(n+1) =( x  (n+1)  - x + y )/(n+1) = x + (y-x)/(n+1);
@（2）实现
*/
/* calculate average will not overflow */
float average(float *data, unsigned int len)
{
    int i;
    float tmp_aver = 0.0;

    for (i = 1; i <= len; i++)
        tmp_aver += (*(data + i - 1) - tmp_aver) / i;

    return tmp_aver;
}