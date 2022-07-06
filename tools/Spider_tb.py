import requests
from bs4 import BeautifulSoup
import re,json,csv
import threadpool
from urllib import parse

KEYWORD="python"
headers={'user-agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3947.100 Safari/537.36'}
base="https://item.jd.com/"
id_comm_dict=[]

session = requests.session()  #建立会话利用session长链接
session.headers = headers

def get_id(url):
	id=re.compile('\d+')
	res=id.findall(url)
	return res[0]

#一开始的请求页面
def get_index(url):
	session=requests.session()
	session.headers=headers
	html=session.get(url)
	soup=BeautifulSoup(html.text,"lxml")
	items=soup.select('li.gl-item')
	for item in items:
		inner_url=item.select('.gl-i-wrap div.p-img a')[0].get('href')
		new_inner_url=parse.urljoin(base,inner_url)
		#print(inner_url)
		item_id=get_id(new_inner_url)
		#评论数
		comm_num=get_comm_num(new_inner_url)
		#print(comm_num)
		#获取评论内容
		if comm_num>0:
			id_comm_dict[item_id]=get_Comm.delay(new_inner_url,comm_num)
			print(id_comm_dict)
		#店铺内部信息
		shop_info_data=get_shop_info(new_inner_url)
		print(shop_info_data)
		#价格
		
		price=item.select("div.p-price strong i")[0].text
		shop_info_data["price"]=price
		shop_info_data["comm_num"]=comm_num
		shop_info_data["item_id"]=item_id
		#print(shop_info_data)
		write_csv(shop_info_data)

head=['item_id', 'comm_num',"shop_name","shop_evaluation","logistics","sale_server","shop_brand","price",]
def write_csv(row):
	with open("shop.csv","a+",encoding="utf-8") as f:
		csv_writer=csv.DictWriter(f,head)
		csv_writer.writerow(row)

#获取店铺信息			
def get_shop_info(url):
	shop_data={}
	html=requests.get(url,headers=headers)
	soup=BeautifulSoup(html.text,"lxml")
	try:
		shop_name=soup.select("div.mt h3 a")[0].text
	except:
		shop_name="京东"
	shop_score=soup.select(".score-part span.score-detail em")
	try:
		shop_evaluation=shop_score[0].text
		logistics=shop_score[1].text
		sale_server=shop_score[2].text
	except:
		shop_evaluation=None
		logistics=None
		sale_server=None

	shop_info=soup.select("div.p-parameter ul")
	shop_brand=shop_info[0].select("ul li a")[0].text
	try:
		shop_other=shop_info[1].select("li")
		for s in shop_other:
			data=s.text.split(":")
			key=data[0]
			value=data[1]
			shop_data[key]=value
	except:
		pass
	shop_data["shop_name"]=shop_name
	shop_data["shop_evaluation"]=shop_evaluation
	shop_data["logistics"]=logistics
	shop_data["sale_server"]=sale_server
	shop_data["shop_brand"]=shop_brand
	return shop_data

#获取评论数量		
def get_comm_num(url):
	item_id=get_id(url)
	comm_url="https://club.jd.com/comment/productCommentSummaries.action?referenceIds={}&callback=jQuery3108939&_=1583139360714".format(item_id)
	comment=session.get(comm_url,headers=headers).text
	start=comment.find('{"CommentsCount"')
	end=comment.find('"PoorRateStyle":2}]}')+len('"PoorRateStyle":2}]}')
	try:
		content = json.loads(comment[start:end])['CommentsCount']
	except:
		return 0
	comm_num=content[0]["CommentCount"]
	#print(comm_num)
	return int(comm_num)

if __name__ == '__main__':
	urls=[]
	for i in range(1,200,2):
		url="https://search.jd.com/Search?keyword={}&wq={}&page={}".format(KEYWORD,KEYWORD,i)
	urls.append(([url,],None))
	pool=threadpool.ThreadPool(50)
	reque=threadpool.makeRequests(get_index,urls)
	for i in reque:
		pool.putRequest(i)
	pool.wait()