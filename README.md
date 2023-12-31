PixivDownloadHelper
===================
# [Release for windows 64-bit / 适用于windows 64位的软件版本](https://github.com/ShimaSh1ma/PixivDownloadHelper/releases/tag/v1.0)
## Introduction / 简介
PixivDownloadHelper / Pixiv下载助手<br/>
&ensp;&ensp; The program is designed for downloading [Pixiv](https://www.pixiv.net/) illusts.
It will automatically read your clipboard, and use regular expression classify url to realize various downloading needs.  <br/>
&ensp;&ensp; You just need to open the program and copy urls you want download, It will start downloading. <br/>
&ensp;&ensp; 此程序功能为下载[Pixiv](https://www.pixiv.net/)网站中的插画作品。
程序自动读取剪贴板内容，并判断url类型，以满足各种下载需求。 <br/>
&ensp;&ensp; 使用时，只需要打开程序，在浏览Pixiv网页时复制你想下载插画的网址即可下载。
## Set your own config before downloading / 下载之前请先设置
1.Check download path. / 检查下载文件保存路径。<br/>
2.Input your Pixiv cookie. / 输入你自己的Pixiv cookie。<br/>
3.确保网络环境可以访问Pixiv，代理请打开Tun模式。（后续可能会支持http代理）<br/><br/>
&ensp;&ensp; _You can click Change Pixiv Cookie widget to fold or unfold it. Click ___"Change"___ button change your pixiv cookie. Click ___"Save"___ save your change._<br/>
&ensp;&ensp; _点击Change Pixiv Cookie窗口可以折叠或者展开cookie信息，点击 ___"Change"___ 按钮可以更改cookie，更改后点击 ___"Save"___ 按钮保存。_<br/><br/>
__How to get cookie / 如何获取cookie__<br/>
[Get pixiv cookie](https://zhuzemin.github.io/pixiv_sort_by_popularity/)<br/>
[获取打开网页的cookie](https://blog.csdn.net/liuyanlin610/article/details/75105105)<br/>
***Folded***<br/>
![image](https://github.com/ShimaSh1ma/PixivDownloadHelper/blob/master/introduction/cookie%20folded.png)<br/>
***Unfolded***<br/>
![image](https://github.com/ShimaSh1ma/PixivDownloadHelper/blob/master/introduction/cookie%20unfolded.jpg)
## Gui / 图形界面
1.Main window / 下载主界面
    ![image](https://github.com/ShimaSh1ma/PixivDownloadHelper/blob/master/introduction/mainWindow.png)
2.setting window / 设置界面
    ![image](https://github.com/ShimaSh1ma/PixivDownloadHelper/blob/master/introduction/settingWindow.jpg)
## Functions / 功能
### __Functions now: / 现有功能：
1.Download by illust url like: __https://www.pixiv.net/artworks/(id)*********__ <br/>
2.Download by user id url like: __https://www.pixiv.net/users/(userId)********/artworks__ <br/>
3.Download by user + tag url like: __https://www.pixiv.net/users/(userId)********/artworks/(Tag)$%^^&*^__ <br/>
<br/>
1、直接通过单个作品链接下载，url格式：__https://www.pixiv.net/artworks/(id)*********__ <br/>
2、通过用户主页url下载，用户主页url格式：__https://www.pixiv.net/users/(userId)********/artworks__ <br/>
3、通过用户主页分类筛选器筛选后的url下载，url格式：__https://www.pixiv.net/users/(userId)********/artworks/(Tag)$%^^&*^__ <br/>
