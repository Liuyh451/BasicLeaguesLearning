import pygame
import sys
pygame.init()
speed=[1,1]
BLACK=[0,0,0]
vInfo=pygame.display.Info()
size=width,height=600,400
screen=pygame.display.set_mode(size,pygame.RESIZABLE)
pygame.display.set_caption('LYH-game')
ball=pygame.image.load('xiangjiaojun.jpg')
ballrect=ball.get_rect()
fps=300
fclock=pygame.time.Clock()
while True:
    for event in pygame.event.get():
        if event.type==pygame.QUIT:
            pygame.quit
            sys.exit()
        elif event.type==pygame.KEYDOWN:  #检测键盘输入
            if event.key==pygame.K_LEFT:
                if speed[0]==0:
                    speed[0]=speed[0]
                else:
                    speed[0]=(abs(speed[0])-1)*int(abs(speed[0])/speed[0])
            elif event.key==pygame.K_RIGHT:
                if speed[0]>0:
                    speed[0]+=1
                else:
                    speed[0]-=1
            elif event.key==pygame.K_UP:
                if speed[1]>0:
                    speed[1]+=1
                else:
                    speed[1]-=1
            elif event.key==pygame.K_DOWN:
                if speed[1]==0:
                    speed[1]=speed[1]
                else:
                    speed[1]=(abs(speed[1])-1)*int(abs(speed[1])/speed[1])#减速，带正负号
            elif event.key==pygame.K_ESCAPE:  #使用esc退出
                sys.exit()
        elif event.type==pygame.VIDEORESIZE:   #检测到屏幕尺寸发生变化时，重新设置size
            size=width,height=event.size[0],event.size[1]
            screen=pygame.display.set_mode(size,pygame.RESIZABLE)
            print(size)
    if pygame.display.get_active():#获取窗口的状态，最小化时返回false
        ballrect=ballrect.move(speed[0],speed[1])
    if ballrect.left<0 or ballrect.right>width:
        speed[0]=-speed[0]
    if ballrect.top<0 or ballrect.bottom>height:
        speed[1]=-speed[1]
    screen.fill(BLACK)
    screen.blit(ball,ballrect)
    pygame.display.update()
    fclock.tick(fps)
