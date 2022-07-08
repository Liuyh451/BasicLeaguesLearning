#将txt合并成一列
import os
SaveList = []  # 存档列表
# 读取文本内容到列表
with open("1.txt", "r", encoding='utf-8') as file:
    for line in file:
        line = line.strip('\n')  # 删除换行符
        SaveList.append(line)
        #这个savelist是把每行作为一个list元素
        #原始数据集是第一行很大一堆，没有换行，所以list[0]比较大
    file.close()
print(SaveList)
with open("data8.txt","w",encoding='utf-8') as file:
    for i in SaveList[0].split():
        file.write(i+'\n')
    #由于这个下面的list都是一行一个不用分割，直接写入即可
    for i in SaveList[1:]:
        file.write(i+'\n')
    file.close()          

