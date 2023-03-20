# Vue学习笔记

## 1.模板语法

### 1.2 初始化Vue实例：

const vm=vue({

el:'#root' //#绑定的是id （css），.root绑定class

})//{}内的叫配置对象

![image-20230317191834800](C:\Users\86156\AppData\Roaming\Typora\typora-user-images\image-20230317191834800.png)



![image-20230317193117462](C:\Users\86156\AppData\Roaming\Typora\typora-user-images\image-20230317193117462.png)

### 1.3 指令模式

![image-20230317194247403](C:\Users\86156\AppData\Roaming\Typora\typora-user-images\image-20230317194247403.png)

![image-20230317194611640](C:\Users\86156\AppData\Roaming\Typora\typora-user-images\image-20230317194611640.png)

对象{}可以多级嵌套

## 2.数据绑定：

![image-20230317201051885](C:\Users\86156\AppData\Roaming\Typora\typora-user-images\image-20230317201051885.png)

### 2.1 el和data的不同写法

![image-20230317201917011](C:\Users\86156\AppData\Roaming\Typora\typora-user-images\image-20230317201917011.png)

![image-20230317202057273](C:\Users\86156\AppData\Roaming\Typora\typora-user-images\image-20230317202057273.png)

<todo> 查箭头函数和普通函数

对于windows管理的函数需要使用箭头函数，比如定时器等。

对于vue实例管理的函数，使用普通函数

data:function()可以简写成data(){}

![image-20230317202133120](C:\Users\86156\AppData\Roaming\Typora\typora-user-images\image-20230317202133120.png)

这里的this是window

## 3.MVVM模型

![image-20230317203154090](C:\Users\86156\AppData\Roaming\Typora\typora-user-images\image-20230317203154090.png)

## 4.Object.defineProperty

![image-20230317205033132](C:\Users\86156\AppData\Roaming\Typora\typora-user-images\image-20230317205033132.png)

## 5.数据代理

## 6.事件处理

## 7.计算属性

![image-20230320170538053](C:\Users\86156\AppData\Roaming\Typora\typora-user-images\image-20230320170538053.png)

## 8. 监视属性

![image-20230320175722436](C:\Users\86156\AppData\Roaming\Typora\typora-user-images\image-20230320175722436.png)

### 8.1 深度监视

![image-20230320181119139](C:\Users\86156\AppData\Roaming\Typora\typora-user-images\image-20230320181119139.png)

### 8.2 computed和watch对比

![image-20230320190645890](C:\Users\86156\AppData\Roaming\Typora\typora-user-images\image-20230320190645890.png)