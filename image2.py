import matplotlib.pyplot as plt
import numpy as np
from numpy import *

points1 = [[10, 90], [20, 80],[30,40],[50,90],[80,30]]
points2 = [[50, 70], [20, 50],[40,10],[70,20],[30,90]]
points3 = [[60,40], [10,40],[30,60],[50,30],[20,0]]


rows = 100
clos = 100
num = zeros((rows,clos),dtype=int)  #先创建一个 3x3的全零方阵A，并且数据的类型设置为float浮点型

plt.xticks(np.arange(0,rows,1))			
plt.yticks(np.arange(0,clos,1))

#readin
f = open('finalPoints.txt')        #打开数据文件文件
lines = f.readlines()      #把全部数据文件读到一个列表lines中
A_row = 0            #表示矩阵的行，从0行开始
for line in lines:       #把lines中的数据逐行读取出来
	list = line.strip('\n').split(' ')   #处理逐行数据：strip表示把头尾的'\n'去掉，split表示以空格来分割行数据，然后把处理后的行数据返回到list列表中
	num[A_row:] = list[0:clos]          #把处理后的数据放到方阵A中。list[0:3]表示列表的0,1,2列数据放到矩阵A中的A_row行
	A_row+=1                #然后方阵A的下一行接着读
	#print(line)
 
# print(num)  #打印 方阵A里的数据
[rows,clos] = num.shape
# print(rows,clos)



#绘制连线
start = 1
block = 9
node = 3

#[rows1,clos1] = points1.shape
rows1 = len(points1)
for i in range(rows1):
	num[points1[i][0],points1[i][1]] = 4

for i in range(rows):
	for j in range(clos):
		#障碍
		if num[i,j] == 9:
			if i+1 < clos and num[i+1,j] == 9:
				plt.plot([i,j],[i+1,j],color='r')
			if j+1 < rows and num[i,j+1] == 9:
				plt.plot([i,j],[i,j+1],color = 'r')
		#连接点，其中4代表起始点
		elif num[i,j] == 1 or num[i,j] == 4:
			if i+1 < clos and (num[i+1,j] == 1 or num[i+1,j] == 4):
				plt.plot([i,i+1],[j,j],color='b')
			if j+1 < rows and (num[i,j+1] == 1 or num[i,j+1] == 4):
				plt.plot([i,i],[j,j+1],color = 'b')

#[rows2,clos2] = points2.shape
rows2 = len(points2)
for i in range(rows2):
	num[points2[i][0],points2[i][1]] = 5

for i in range(rows):
	for j in range(clos):
		#障碍
		if num[i,j] == 9:
			if i+1 < clos and num[i+1,j] == 9:
				plt.plot([i,j],[i+1,j],color='r')
			if j+1 < rows and num[i,j+1] == 9:
				plt.plot([i,j],[i,j+1],color = 'r')
		#连接点，其中4代表起始点
		elif num[i,j] == 2 or num[i,j] == 5:
			if i+1 < clos and (num[i+1,j] == 2 or num[i+1,j] == 5):
				plt.plot([i,i+1],[j,j],color='r')
			if j+1 < rows and (num[i,j+1] == 2 or num[i,j+1] == 5):
				plt.plot([i,i],[j,j+1],color = 'r')

#[rows3,clos3] = points3.shape
rows3 = len(points3)
for i in range(rows3):
	num[points3[i][0],points3[i][1]] = 6

for i in range(rows):
	for j in range(clos):
		#障碍
		if num[i,j] == 9:
			if i+1 < clos and num[i+1,j] == 9:
				plt.plot([i,j],[i+1,j],color='r')
			if j+1 < rows and num[i,j+1] == 9:
				plt.plot([i,j],[i,j+1],color = 'r')
		#连接点，其中4代表起始点
		elif num[i,j] == 3 or num[i,j] == 6:
			if i+1 < clos and (num[i+1,j] == 3 or num[i+1,j] == 6):
				plt.plot([i,i+1],[j,j],color='g')
			if j+1 < rows and (num[i,j+1] == 3 or num[i,j+1] == 6):
				plt.plot([i,i],[j,j+1],color = 'g')

#绘制起始点
for i in range(rows):
	for j in range(clos):
		if num[i,j] == 4 or num[i,j] == 5 or num[i,j] == 6:
			plt.scatter(i,j,color = 'black')
plt.show()