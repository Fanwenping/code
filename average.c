/*
@ ��ܱ߽���������ֵ�㷨
@��1���㷨
	��xΪ�������ݵ�ƽ������nΪ�������ݵĸ������µ�����Ϊy����ô
	(x * n + y)/(n+1) =( x  (n+1)  - x + y )/(n+1) = x + (y-x)/(n+1);
@��2��ʵ��
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