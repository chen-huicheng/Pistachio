# 像素填充图

## 思路：遍历原图像素，选取适合图片取代

### 大致分为三步
> * 1，将已有图片转化为特定大小的图片
> * 2，提取图片色彩
> * 3，生成像素填充图
 
### 参数说明：
> + --path:图片集路径  [**必选**]
> + --resize:将图片集resize后的大小，默认100*100像素
> + --img：待填充的图像 [**必选**]
> + --size：填充的图片的大小，默认100*100像素

* 结果展示
<div align=center><img src="https://img-blog.csdnimg.cn/20190717095540564.jpg" width="500"/> </div>
<div align=center><img src="output.png" width="500"/> </div>
<div align=center><img src="https://img-blog.csdnimg.cn/20190717102229545.png" width="500"/> </div>
