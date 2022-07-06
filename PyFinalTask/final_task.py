# code: UTF-8
import jieba
import wordcloud
import requests
import bs4
import re
from bs4 import BeautifulSoup
import time
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import string

lists=[]
ulist=[]
uulist=[]
f=0

def geturl(url,headers):
    try:
        r=requests.get(url,headers=headers)
        r.encoding=r.apparent_encoding
        r.raise_for_status()
        return r.text

    except:
        return 'error'


if __name__ == '__main__':
    time_begin=time.time()
    headers={'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.88 Safari/537.36'}#更换用户名
    depth=10
    for i in range(depth):
        x=25*i
        url="https://movie.douban.com/top250"+'?start={}&filter='.format(x)#实现翻页
        htext=geturl(url,headers)
        soup=BeautifulSoup(htext,'html.parser')
        for tr in soup.find('ol').children:
            soup=BeautifulSoup(htext, 'html.parser')
            tp=soup.find('ol', class_='grid_view')
            tds=tp.find_all('li')
        for td in tds:
            filmnum=f+1     #电影排名
            f+=1
            filmname=td.find('span', class_='title').text   #电影名称
            filmfen=td.find('span', class_='rating_num').text    #电影评分
            filmp=td.find('p').text   #将p标签中的信息分开，以及去掉<br>
            filmp1=filmp.split('\n')[1]
            filmp2=filmp.split('\n')[2]
            filmyear=re.findall(r'\d{4}', filmp2)[0]     #上映年份
            filmarea = filmp2.split('\xa0/\xa0')[-2]    #制片国家
            filmtype = filmp2.split('\xa0/\xa0')[-1].strip()   #电影类型
            lists.append([filmnum,filmname,filmfen,filmyear,filmarea,filmtype])
            print("\r当前进度: {:.2f}%".format(f*100/250),end="")   #显示进度
    #保存为列表
    for i in range(250):
        ilist=lists[i]
        a='{}/{}/{}/{}/{}/{}'.format(ilist[0],ilist[1],ilist[2],ilist[3],ilist[4],ilist[5])
        b='{}'.format(ilist[5])
        ulist.append(a)
        uulist.append(b)
    #写入文件
    fname='movie top250'
    f=open(fname,'w+')
    for i in ulist:
        f.write(i)
        f.write('\n')
    f.seek(0)
    f.close()
    #单独生成filmtype类型的副本，供生成词云
    fname='movie top250_type'
    f=open(fname,'w+')
    for i in uulist:
        f.write(i)
    f.seek(0)
    f.close()
    #运行时间
    time_end=time.time()
    time = time_end - time_begin
    t=float(time)
    print()
    print('豆瓣top250爬取成功共用时: {:.2f}s'.format(t))


def getHTMLText(url):
    try:
        r = requests.get(url, timeout=60)
        r.raise_for_status()
        r.encoding = r.apparent_encoding
        return r.text
    except:
        return "timeout"

def fillList(ulist, html):   #爬取票房top100电影类型
    soup = BeautifulSoup(html, "html.parser")
    trs=soup.find_all('tr')
    ulist=[]   #存储电影类型
    for i in trs:
        a=i.find('td',class_='type')
        if a!=None:
           ulist+=a.text.split("/")
    fname = 'box office top 100 type.txt'   #票房top100电影类型写入文档
    f = open(fname, 'w+')
    f.writelines(ulist)
    f.seek(0)
    f.close()

list = []
url = 'http://www.piaofang.biz/'
html = getHTMLText(url)

if html=="timeout":  #超时报错
    print(html)
else:
    fillList(list, html)
    print("box office top100 爬取成功")
    # 生成票房top100电影类型词云
    f = open("box office top 100 type.txt", "r")
    t = f.read()
    f.close()
    ls = jieba.lcut(t)
    txt = " ".join(ls)
    w = wordcloud.WordCloud( \
        width=1000, height=700, \
        background_color="white",
        font_path="msyh.ttc"
    )      #设置词云属性
    w.generate(txt)
    w.to_file("box office top 100 type.png")
    # 生成豆瓣评分top250的电影类型词云
    f = open("movie top250_type", "r")
    t = f.read()
    f.close()
    ls = jieba.lcut(t)
    txt = " ".join(ls)
    w = wordcloud.WordCloud( \
        width=1000, height=700, \
        background_color="white",
        font_path="msyh.ttc"
    )     #设置词云属性
    w.generate(txt)
    w.to_file("movie top250_type.png")

a = np.loadtxt('movie top250', dtype=np.str, delimiter='/')   # 读取数据
matplotlib.rcParams['font.family']='Microsoft YaHei'          # 设置字体
# part 1 评分条形图
name1 = []   # 名称列表
pop1 = []    # 评分列表
max1 = 20    # 最大值
now1 = 100
for i in range(100):
    for j in range(250):
        if eval(a[j, 2]) * 10 == now1:
            name1.append(a[j, 1])
            pop1.append(now1 / 10)
    if len(name1) >= max1:
        break
    now1 -= 1
name1 = name1[::-1]  # 翻转处理
pop1 = pop1[::-1]
plt.figure(figsize=(6, 10))                # 设置画布大小
plt.barh(name1, pop1, facecolor='tan')     # 绘图
for i in range(len(name1)):                # 标数据
    plt.text(pop1[i] - 0.5, i, pop1[i])
plt.title('豆瓣排名Top{}'.format(max1))    # 标题
plt.tight_layout()                         # 导出
plt.savefig('save 1.png',dpi = 600)
# part 2 年份折线图
plt.figure(figsize=(6, 6))                 # 设置画布大小
yearlist = ['1994年以前', '1995-2000', '2001-2005', '2006-2010', '2011-2015', '2016年以后']
yearnum = [0,0,0,0,0,0]
for i in range(250):
    year = eval(a[i, 3])
    if year <= 1994:
        yearnum[0] += 1
    elif year <= 2000:
        yearnum[1] += 1
    elif year <= 2005:
        yearnum[2] += 1
    elif year <= 2010:
        yearnum[3] += 1
    elif year <= 2015:
        yearnum[4] += 1
    else:
        yearnum[5] += 1
for i in range(len(yearlist)):
    plt.text(yearlist[i],yearnum[i],yearnum[i],ha='center',fontsize=11)
plt.plot(yearlist,yearnum)
plt.title('年份走势')
plt.tight_layout()
plt.savefig('save 2.png',dpi = 600)
# part 3 生成国家 饼图
countrys = []                           # 统计国家
for i in range(250):
    countrys.extend(a[i, 4].split())    # 分隔多个国家
sum1 = len(countrys)                    # 统计
countryd = {}
for i in countrys:
    if i in countryd:
        countryd[i] += 1
    else:
        countryd[i] = 1
countryd = sorted(countryd.items(),key=lambda x:x[1],reverse = True)  # 排序
max2 = 6              # 最大值
countrylist = []
countrysum = []
for i in range(max2):
    countrylist.append(countryd[i][0])
    countrysum.append(countryd[i][1])
    sum1 -= countryd[i][1]
countrylist.append('其他国家')
countrysum.append(sum1)
plt.pie(countrysum,labels=countrylist,autopct='%1.1f%%')
plt.title('各国比例')
plt.savefig('save 3.png',dpi = 600)
print("图表生成完成")