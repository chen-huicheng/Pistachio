# -*- coding: utf-8 -*-
"""
Created on Sat Jan 30 17:53:23 2021

@author: Icheng
"""
import os
from PIL import Image
import cv2
import argparse




# ascii_char = list("@WMQN&%ORH#$AUXSVLmaegot<>ri;:^~-,.'`        ")
ascii_char = list("@WMQN&%ORH#$AUXSVLmaegot<+>ri;:_^~-,.'`                       ")
# ascii_char = list(r"$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,\"^`'. ")

# 将256灰度映射到字符上
def get_char(r,g,b,alpha = 256):
    if alpha == 0:
        return ' '
    length = len(ascii_char)
    gray = int(r + g + b)

    unit = (256.0*3 + 1)/length
    return ascii_char[int(gray/unit)]

if __name__ == '__main__':
    #命令行输入参数处理
    parser = argparse.ArgumentParser()
    parser.add_argument('--path', type=str, default="", help="img dir")     #输入文件
    parser.add_argument('--output', type=str, default='output.txt', help="output path")   #输出文件
    parser.add_argument('--width', type = int, default = 210) #输出字符画宽
    parser.add_argument('--height', type = int, default = 90) #输出字符画高

    #获取参数
    args = parser.parse_args()

    path = args.path
    WIDTH = args.width
    HEIGHT = args.height
    OUTPUT = args.output
    if(path==""):
        print("please using --path imgpath")
        assert(0)
    imgs = os.listdir(path)
    for img in imgs:
        if not (img.endswith(".jpg") or img.endswith(".png")):
            continue
        IMG = os.path.join(path,img)
        im = Image.open(IMG)
        im = im.resize((WIDTH,HEIGHT), Image.NEAREST)
        txt = ""
    
        for i in range(HEIGHT):
            for j in range(WIDTH):
                txt += get_char(*im.getpixel((j,i)))
            txt += "\n"
        txt+="\n"
        # print(txt)
    
        #字符画输出到文件
        with open(OUTPUT,'a') as f:
            f.write(txt)