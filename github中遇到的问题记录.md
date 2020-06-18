## 记录GitHub使用中遇到的问题  
### 首先说一下最常用、最初遇到的命令 <br />
**最开始要说的是，GitHub分为三个部分：工作区，暂存区，远程仓库**  
<br />

![](https://github.com/TRY0929/try.github.io-/blob/master/images/git%E5%88%86%E5%8C%BA.png)

![](https://github.com/TRY0929/try.github.io-/blob/master/images/git%E9%80%9F%E6%9F%A5%E8%A1%A8.jpg)

<br />

*所有带有git前缀的都是git的指令 不带的是系统的指令* 

<br />

#### 帮助指令

+ **git --help** 可得到帮助信息

-----
#### 用户信息

+ **git config --global user.name "xxx"** 设置当前用户名
+ **git config --global user.email "xxx@xxx"** 设置当前邮箱
+ **git config -l/list** 这是查看自己的信息

-----

#### 初始化仓库

+ **git init**

-----
#### 远程仓库

如果是git clone得到的仓库，远程名称默认为origin

+ **git remote add 仓库名 远程地址** 添加远程仓库
+ **git remote (-v)** 查询远程仓库名 -v详细信息
+ **git clone GitHub中仓库旁边的clone那的地址** 复制远程仓库
+ **git push -u 仓库名 仓库地址** 提交到远程仓库（某个操作的最后一步，如add或rm）  
&emsp; 如 git push -u origin master

-----
#### 操作指令

+ **git status** 查看当前状态，如有没有修改，有没有暂存区没push的等等
+ **git add 文件/文件夹名** 将有变化（新的文件）上传到暂存区
+ **git commit -m '描述（显示在GitHub文件后面的描述）'** 确认当前操作
+ **git commit -am “提交描述”** 跳过暂存区直接存到暂存区和仓库
+ **git push** 将上述操作同步到远程仓库中（不仅仅是本地和暂存区中）
+ **git rm -r --cached 文件名** 从本地删除 （需和上两步搭配才能删除远程仓库中的文件）

-----

#### 一些系统的复制指令补充

+ **cd 路径** （CD等盘前要加/）进入某个路径
+ **vi 文件** 创建文件
+ **cd ..** 退回上一级

------

遇到一些奇奇怪怪的问题：

```
编辑器会显示类似下面的文本信息（本例选用 Vim 的屏显方式展示）：

# Please enter the commit message for your changes. Lines starting
# with '#' will be ignored, and an empty message aborts the commit.
# On branch master
# Changes to be committed:
#   (use "git reset HEAD <file>..." to unstage)
#
#       new file:   README
#       modified:   benchmarks.rb 

```
**解决方法**：

1. 按键盘字母 i 进入insert模式

2. 修改最上面那行黄色合并信息,可以不修改

3. 按键盘左上角"Esc"

4. 输入":wq",注意是冒号+wq,按回车键即可

### host文件

在C:\Windows\System32\drivers\etc路径下找到hosts文件，win10一般没有权限，要点击上面的 文件->打开window-powershell->以管理员身份打开，输入notepad hosts即可。