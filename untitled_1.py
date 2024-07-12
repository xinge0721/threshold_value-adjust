# Untitled - By: j - Sat Jul 6 2024


import sensor, image,time,pyb
from pyb import UART,LED,Pin,Timer
import json
import ustruct
import utime
import display

import sensor, image, time
uart = UART(3,115200)
uart.init(115200, bits=8, parity=None, stop=1)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
sensor.skip_frames(time = 2000)
clock = time.clock()


#调阈值使能标志：
thr_enable = 0
start = 1
#黑白色块初始阈值：
white = [58, 88, 6, -17, -3, -16]
black = [15, 23, -7, 10, 1, -16]

#黑白色块特征：
area_max = 135         #色块面积上限（用于色块面积筛选）
area_min = 40          #色块面积下限（用于色块面积筛选）
x_diff = 35            #某个色块的x坐标与x坐标均值之差的允许最大值（用于x坐标连续性筛选 该参数越小，对误识别的筛选范围越大，但识别率和稳定性越低）

#识别范围：
Range = (0,16,160,120) #放弃顶部图像

THRESHOLD = [0, 100, -128, 127, -128, 127]

#接受串口
def data_get():
    getrx = uart.readchar()
    return getrx

#发送串口
def sending_data_cycle(a):
    global uart
    data = bytearray(a)
    uart.write(data)

#寻找最大色块
def find_max(blobs):
    max_size=0
    for blob in blobs:
        if blob[4] > max_size:
            max_blob=blob
            max_size = blob[4]
    return max_blob
add = 0

def threshold_value(command):
    if   command == 97:
        if THRESHOLD[0] < 100:THRESHOLD[0] = THRESHOLD[0] + 1  #调节L的最小值
        else:THRESHOLD[0] = 100
    elif command == 98:
        if THRESHOLD[0] > 0:   THRESHOLD[0] = THRESHOLD[0] - 1
        else:THRESHOLD[0] = 0
    elif command == 99:
        if THRESHOLD[1] < 127: THRESHOLD[1] = THRESHOLD[1] + 1 #调节L的最大值
        else:THRESHOLD[1] = 127
    elif command == 100:
        if THRESHOLD[1] > -128: THRESHOLD[1] = THRESHOLD[1] - 1
        else:THRESHOLD[1] = -128
    elif command == 101:
        if THRESHOLD[2] < 127: THRESHOLD[2] = THRESHOLD[2] + 1 #调节A的最小值
        else:THRESHOLD[2] = 127
    elif command == 102:
        if THRESHOLD[2] > -128: THRESHOLD[2] = THRESHOLD[2] - 1
        else:THRESHOLD[2] = -128
    elif command == 103:
        if THRESHOLD[3] < 127: THRESHOLD[3] = THRESHOLD[3] + 1  #调节A的最大值
        else:THRESHOLD[3] = 127
    elif command == 104:
        if THRESHOLD[3] > -128: THRESHOLD[3] = THRESHOLD[3] - 1
        else:THRESHOLD[3] = -128
    elif command == 105:
        if THRESHOLD[4] < 127: THRESHOLD[4] = THRESHOLD[4] + 1  #调节B的最小值
        else:THRESHOLD[4] = 127
    elif command == 106:
        if THRESHOLD[4] > -128: THRESHOLD[4] = THRESHOLD[4] - 1
        else:THRESHOLD[4] = -128
    elif command == 107:
        if THRESHOLD[5] < 127: THRESHOLD[5] = THRESHOLD[5] + 1  #调节B的最大值
        else:THRESHOLD[5] = 127
    elif command == 108:
        if THRESHOLD[5] > -128: THRESHOLD[5] = THRESHOLD[5] - 1
        else:THRESHOLD[5] = -128
    return 0
nums = 1
while (start):
    print(THRESHOLD,thr_enable,nums)   #当开启调阈值模式时，若单片机不传来结束标志位，则卡死在这
    if uart.any():               #看是否有传过来的数据，有就接收，没有就不管
        thr_enable = data_get()  #接受串口,然后把传过来的数据传给thr_enable（调阈值使能标志）
        if thr_enable >= 97 and thr_enable <= 108:
            nums = nums + 1
            threshold_value(thr_enable)
        if thr_enable == 123 :
            start = 0
            break
    img = sensor.snapshot()
    img.binary([THRESHOLD])

while(True):
    clock.tick()
    img = sensor.snapshot()
    print(THRESHOLD,0)
    if uart.any():#看是否有传过来的数据，有就接收，没有就不管
        thr_enable = data_get()  #接受串口,然后把传过来的数据传给thr_enable（调阈值使能标志）
        if thr_enable == 89:   #只有传过来的数值为0x89时启动调阈值模式
            start = 1            #调阈值的标志位


    img.binary([THRESHOLD])
