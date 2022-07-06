# -*- coding:utf-8 -*-
from PIL import Image
import os
import sys
 
 
def get_urllist():
    base = r'D:\图片\\'#这个是要清理的文件夹
    list = os.listdir(base)
    urllist = []
    for i in list:
        url = base + i
        urllist.append(url)
    return urllist
 
def get_imgSize(filename):
    img = Image.open(filename)
    imgSize = img.size
    #print(imgSize)
 
    return imgSize
 
if __name__ == '__main__':
    file_list = get_urllist()
    print("test1")
    for a in file_list:
        try:
            imgSize = get_imgSize(a)
            maxSize = max(imgSize)
            minSize = min(imgSize)
            print(maxSize, minSize)
            if (maxSize<20 or minSize<20 ):
                os.remove(a)
                print("已移除小于360x360分辨率的图片：%s" % a)
            else:
                pass
        except:
            os.remove(a)