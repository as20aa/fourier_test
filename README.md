# fourier_test
# 功能说明
使用fftw和eigen进行傅里叶正、逆变换，并将变换结果数据导出，使用excel直观现实
# 使用说明
使用visual studio 2017打开项目文件，点击运行。程序运行结束之后使用excel打开data_view.xlsx文件，点击数据->全部刷新
即可查看傅里正负变换的结果
# 文件说明
```bash
sin.txt			# 产生的正弦信号数据文件
result.txt		# 傅里叶正变换得到的数据文件
inverse_out.txt # 傅里叶逆变换得到的数据文件
data_view.xlsx  # 结合上述三个文件绘制波形图