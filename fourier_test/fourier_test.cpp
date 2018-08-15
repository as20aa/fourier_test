// fourier_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define PI 3.1415926
#define length 1000

int main()
{
	MatrixXd m(length, 1);
	ofstream sfout, rfout;
	sfout.open("sin.txt");
	rfout.open("result.txt");
	double sampleRate = 2500.0;
	double sampleTime = 1 / sampleRate;
	double fre = 50.0;
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

	double *in;
	fftw_complex *out;
	fftw_plan p;

	in = (double*)fftw_malloc(sizeof(double) * length);
	out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * length);
	p = fftw_plan_dft_r2c_1d(length, in, out, FFTW_ESTIMATE);

	for (int i = 0; i < length; i++)
	{
		in[i] = m(i, 0);
	}

	fftw_execute(p);

	for (int i = 0; i < length; i++)
	{
		rfout << i << " " << sqrt(pow(out[i][0], 2) + pow(out[i][1], 2)) << endl;
	}

	rfout.close();
    return 0;
}

