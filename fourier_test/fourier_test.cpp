// fourier_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define PI 3.1415926
#define length 1000

//陷滤波器
void north_filter(int len, int sampleRate, fftw_complex *out, double freq)
{
	int p = (int)(freq*pow(10, 6) / (len*sampleRate));
	cout << "The p is: " << p << endl;
	out[p][0] = 0;
	out[p][1] = 0;
	out[len-p][0] = 0;
	out[len - p][1] = 0;
}

int main()
{
	MatrixXd m(length, 1);
	ofstream sfout, rfout,iout;
	//定义以下三个文件用于数据输出及excel数据的绘图
	sfout.open("sin.txt");				//原始波形数据
	rfout.open("result.txt");			//傅里叶变换之后的数据
	iout.open("inverse_out.txt");		//傅里叶逆变换后的数据

	double sampleRate = 2500.0;			//设定采样频率
	double sampleTime = 1 / sampleRate;	//计算采样时间间隔
	double fre = 50.0;					//设定频率

	//产生正弦信号
	{
		int i = 0; double tmp;
		for (; i < length; i++)
		{
			// Produce a serials of points
			tmp = sin((2 * PI * fre / sampleRate)*((double)i));
			sfout << i << " " << tmp <<endl ;
			m(i, 0) = tmp;
		}
	}

	sfout.close();

	fftw_complex *in;
	fftw_complex *out;
	fftw_plan p;
	//创建傅里叶变换对象
	in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * length);
	out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * length);
	p = fftw_plan_dft_1d(length, in, out, FFTW_BACKWARD, FFTW_MEASURE);
	//对输入进行初始化
	for (int i = 0; i < length; i++)
	{
		in[i][0] = m(i, 0);
		in[i][1] = 0;
	}
	//执行傅里叶变换
	fftw_execute(p);

	north_filter(length, sampleRate, out, 50);
	//将傅里叶变换结果输出
	for (int i = 0; i < length; i++)
	{
		// 输出实际频率及权重的数据，第一列为频率，单位为Hz，第二列为幅值
		rfout << i * length * sampleRate / pow(10, 6) << " " << sqrt(pow(out[i][0], 2) + pow(out[i][1], 2)) * 2 / length << endl;
	}
	rfout.close();
	//销毁傅里叶变换计划
	fftw_destroy_plan(p);
	//创建傅里叶逆变换计划
	fftw_complex *out2;
	out2 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * length);
	p = fftw_plan_dft_1d(length, out, out2, FFTW_BACKWARD, FFTW_MEASURE);
	fftw_execute(p);
	//输出傅里叶逆变换数据
	for (int i = 0; i < length; i++)
	{
		iout << i << " " << -out2[i][0] / length << endl;
	}
	iout.close();
	//清空缓存
	fftw_destroy_plan(p);
	fftw_free(in);
	fftw_free(out);
	fftw_free(out2);
	system("pause");
    return 0;
}

