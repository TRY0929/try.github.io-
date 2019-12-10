## qq音乐网页版仿写 一些步骤与注意事项
> 一开始肯定就是**html+css**布局和页面了，这段特别耗时间，耐心写完就好了

-----

首先要说一下大致流程：

1. 一定要先布局html！，所以一定要先分析页面布局情况，用不同的颜色把区位定好。html的大致框架出来才能办事，搭配比较简单的css，如宽度高度定位什么的；
2. css在html布好大致的局基础上开始细化细节（你最终会发现，好像你的大部分时间都送给了css）；
3. js一直是最后，如图标点击有变化什么的（这部分代码是真不多...写起来也是真爽，不过一定要考虑到各种情况和bug，调bug比较难，比第二步更有技术含量）。



### 0、css出现的一些问题

#### 1）进度条

其实进度条可以分成三个部分

底部，盖住的条条，以及小圆点

![image-20191205234221320](C:\Users\ARASHI\AppData\Roaming\Typora\typora-user-images\image-20191205234221320.png)

```javascript
<div class="play-b">
    <div class="progress-bar"></div>
    <div class="progress-line"></div>
    <div class="progress-dot"></div>
</div>
```

#### 2） 背景模糊效果

在原版qq音乐中，背景图片会随着歌曲变化发生改变，但可以看到其十分的模糊且保证能使人看清字，所以采用**两层底部背景**的方式；

+ 整个body的背景色处于半透明状态，这样就能看到后面的效果；

+ 当前歌曲的图片作为背景图片，且cover在整个页面中，用`filter: blur(100px);`来出现模糊效果，blur里的参数越大越模糊，且该层应置为底下，即`z-index=-2`；

+ 歌曲图片上面一层需要拿一个灰色的盒子来遮着，这样能保证人能看清字，如何保证灰色盒子在背景之上？`z-index=-1;background-color: rgba(0,0,0,0.35);`

  



>  接下来主要讲js的部分 页面布局多练则熟

### 1、基础的事件监听

+ 需要对一些基础的点击事件，如 点击切换模式，点击播放与暂停图标变化（主要就是图标变化 用精灵图的话就是把background-position改一下）；

+ 需要注意的点就是，在对事件进行监听的时候，动态创建的元素不能使用原来的方式绑定事件，要用**事件委托，找到动态状态前就已经存在的元素ul**。

&emsp; 这里可以用on函数`on(events,[selector],[data],fn)` 。

+ 注意点击的时候的**排他思想**，比如点击播放这首歌曲，那么其他歌曲的播放图标必须全部变为暂停模式，一般用`parents("selector").siblings().xxx`就改掉其他的了。  

  &emsp; 这里要注意的就是**children("selector")**只能找到亲孩子，而用的多的一般都是**find("selector")**，这个可以在所有后代元素中找到符号条件的，并且**siblings()**也是亲兄弟，表兄不能直接找到，只能通过parents再siblings找到，（找叔叔伯伯再找他们的孩子）。  

+ 还有一点小点就是，`visibili:hidden(visible);` `display:none(block);`的区别：
  + 前者不会影响界面布局，不会使页面重构，也就是说使用这个的元素在文档中依然占有位置；
  + 而后者是直接让整个元素在页面中飞起来，也就是不占有位置了，会使页面重构；

### 2、加载歌曲列表

> 这里虽然还没学Ajax，但是初步使用了一下jQuery里的Ajax函数，仅用来获取本地资源。

#### 1）很简单的使用了ajax函数

<img src="C:\Users\ARASHI\AppData\Roaming\Typora\typora-user-images\image-20191205203634675.png" alt="image-20191205203634675" style="zoom:80%;" />

其中，url是获取资源的位置(这里就是本地的资源)，dataType是获取资源的类型，success是获取成功之后要干什么，error显而易见；

#### 2）利用json文件里的信息初始化音乐列表

+ 用jQuery的静态函数each来遍历json中的每个对象，提取信息并且安排好排版之后 变成jQuery对象放到音乐列表里；

  ```javascript
  $.each(data, function (index,value) {
  	var $item = createMusicItem(index,value);
  	$musicList.append($item);
  })
  ```

  

+ 其中在这要做一步为后面做铺垫：每创建一个元素对它的原生dom对象添加两个属性，index和music信息，便于后面访问。

  ```javascript
  //直接把当前这首的索引号和对应的音乐信息作为一个属性
  //绑定到了原生js上 不能用setArrtibute不知道为啥
  $item.get(0).index = index;
  $item.get(0).music = value;
  ```

  

### 3、创建一个类，专门来播放音乐

#### js面向对象的知识来复习下

+ 面向对象编程在创建方法时，最好保证方法的单一性，一个方法只做一件事情，代码更容易维护

+ 用另一个单独的文件来存放Player类，其中用函数闭包的方法来写；

+ 框架如下，该解释的地方都在代码注释里了，主要就是面向对象原型的知识：

  ```javascript
  (function (window) {
      function Player($audio) {
          //这里其实是是new了一个init对象 而init对象的prototype指向的是自己的原型对象
          //而不是Player的原型对象 因此后面要改
          return new Player.prototype.init($audio);
      }
      Player.prototype = {
          constructor: Player,
          //用字面量重写原型会导致constructor不再指向自己本身，所以这里用一个属性指回来
          init: function ($audio) {},
          playMusic: function (index, music) {}
      }
  
      //就是这里 要把init的原型指向Player的原型对象 以后就不管是通过init创建的还是直接通过Player创建的对象 原型都指向Player的原型对象  就可以调用其方法
      Player.prototype.init.prototype = Player.prototype;
      window.Player = Player;
  })(window)
  ```

  

### 4、播放音乐

#### 1）来写Player里的playMusic方法

> 要做几项准备工作  

1. 类进行实例化(创建对象)的时候，应要传进来关于当前这首音乐的**索引号以及信息**，这就可以回到刚刚那里说的做铺垫，`每创建一个元素对它的原生dom对象添加两个属性，index和music信息，便于后面访问`；
2. 在html文档里添加audio标签来播放音乐；
3. 类中还要添加几个属性：放所有歌曲信息的musicList[]，放jQuery对象的$audio，放原生dom对象的audio；
4. 为什么专门要拿到audio原生对象？不仅仅是由于在它上可以直接设置新的属性且访问方便，还是因为 audio上的原生方法pause()、play() 可以直接控制音乐的暂停与播放；

准备工作做完了，接下来写方法。

+ 设置一个全局变量currentIndex来记录当前播放的是第几首音乐，这是由于，如果连续点击两次同一首音乐，那么分别是播放和暂停，效果不一样；
+ **进行判断**：若当前播放的索引号和是与currentIndex相同的，就继续判断，当前是暂停还是播放；若不相同，就将当前对象的audio标签的src属性设置为当前点击的这首音乐的地址，且currentIndex更新；
+ 这里不用进行排他，因为audio标签就一个...

#### 2）下方工具栏的总播放

+ 这里有个注意事项，若点击工具栏的总播放键时还从未播放过歌曲，那么就默认从第一首开始播放，否则就播放currentIndex这一首；

+ **核心思想**：其实点击下面的播放键，**就是模拟点击了某首歌里的播放键**，那么就直接利用trigger触发(或者直接click也一样)，通过currentIndex来找到要播放的歌曲，直接模拟点击即可；

  

#### 3）上一首下一首切歌

+ 若当前为第一首(或从未播放过)，点击上一首后播放最后一首；

+ 若为最后一首，点击下一首后播放第一首；

+ 在Player类里封装两个函数 `preIndex`和`nextIndex`，之后直接调用即可；

  > 这里写的时候我写出了一个极其低级的bug...注意在`preIndex`和`nextIndex`两个函数里，不能直接改变currentIndex的值....因为之后点击还要再改变，现在改变了后面就不会变了，导致页面看起来会随着点击切歌，但点击按钮指回重复暂停播放同一首歌......（难过 调了好久



#### 4）删除音乐

> 删除的时候极易出现以下几个bug 不仔细想根本想不到

+ 删除音乐首先是在视觉上删除，也就是**在页面上删除这首歌整个元素**；
+ 再接着是要**删除musicList里的这首歌的元素**，这里利用**当时保存在原生dom结点中的index属性**来删除，不然仅在页面上删除，实际上列表里任然存在这首歌，只是视觉上看不见了；
+ 删除之后还要善后，要将**两个number也更新**，一个是页面上的歌曲序号，另一个是保存在原生dom结点中的index属性的值；
+ 在原版网站里，若**删除的歌曲刚好是在播放的这一首**，则删除当前这首后自动播放下一首歌曲，注意这一步操作要在remove当前li操作的前面！不然会移到下一首的下一首；
+ 最后一个小bug，若**删除的歌处于当前播放这一首之前**，这指向现在播放这一首的"指针"currentIndex的值也要更新，也就是减一；

#### 5）更新音乐信息

&emsp; 这里其实没什么好注意的，就是直接先拿到所有与当前播放音乐相关的信息，再进行修改就可以了。

&emsp; 可以定义一个函数，参数就是当前歌曲的所有信息（这个作为一个属性保存到原生dom的music属性里了，比较容易拿到），然后逐个修改就可以了。

#### 6）点击、拖拽音乐播放进度条

> 注意这里另外写了一个新类来专门控制进度条有关事件，便于维护，格式与player(播放器)差不多

+ 类里面的初始化需要的数据就是进度条有关的三样东西，progressBar、progressLine、progressDot
+ 分别定义点击和拖拽的方法

##### 点击事件（Bar和Line都要设置）

+ 获取点击的位置离**屏幕**左端距离 `event.pageX`
+ 获取progressBar这个盒子离屏幕左端距离 `$this.$progressBar.offset().left`
+ 上面两值相减后分别赋给 小圆点的left值以及progressLine的宽度

##### 拖拽事件

拖拽事件可分为三个部分

1. 鼠标按下
2. 鼠标移动
3. 鼠标松开

+ 按下的话肯定是按下小圆点，所以对progressDot添加点击事件(click)（这是新创建的元素，注意用事件委托）
+ **在按下事件里，添加鼠标移动事件，并且是对整个document添加移动事件**，这样可以提高用户体验(mousemove)，同样算上面说的两个距离之差，注意这个差的范围，必须在0~$this.$progressBar.width()之间，超过就不能再多(少)了
+ 松开，同样是对文档，就直接清除dodument的mousemove事件即可(off("mousemove"))

#### 7）随着音乐播放更新时间与进度条

&emsp; 这里用到了原生dom的方法，**audio.duration**——获取歌曲总时长，**audio.currentTime**——获取歌曲当前播放的时长

##### 更新时间

&emsp; 获取之后就 对事件进行格式化 xx:xx / xx:xx 这种（可以新定义一个方法来实现），再替换原来盒子里的值即可，这个方法最好也封装在player里

+ 在player里添加一个新方法musicTimeUpdate，**参数为一个回调函数callback**，将函数中产生的数据结构通过在函数里调用回调函数，传参，从而传到外面，**这种方法十分重要 掌握**
+ 对$audio进行事件监听，**timeupdate**事件，歌曲播放就会触发，暂停则不触发
+ **在事件绑定中每次调用回调函数**从而修改页面中的时间，不在这调用的话就需要返回到index.js中，不方便

##### 更新进度条

&emsp; 元素的left与width都可以设置为百分比，那就直接断出currentTime与duration的百分比就可以了

+ 这里可以在进度条类中新设一个方法(setPosition)，用于更新进度条有关数据的元素位置

#### 8）音乐播放与进度条改变同步

&emsp; 修改音乐播放进度的方式是修改刚刚获得的audio.currentTime（有不小的兼容性和七七八八的问题，如Google里就有点小错误）

##### 点击修改

+ 修改一下刚刚的进度条点击函数，添加一个callback回调函数作为参数，将里面产生的数据结果作为callback的参数传到外部使用（每次调用callback）
+ 由于要修改播放器的数据，所以在player里再新设一个方法(musicSeekTo(value))专门用来修改当前的播放时长，value是百分比
+ 修改的时候，先要判断传进去的value值是否符合要求：不是NAN，0<=value<=1

##### 拖拽修改

总体和刚刚的点击修改差不多，也是添加一个回调函数，但要注意以下几点

+ 由于拖拽进度条和歌曲播放音乐都会修改进度条，同时修改会出现神奇的现象，因此在process里设置一个数据变量专门用来判断当前是否正在拖拽进度条，在拖拽的时候音乐播放不会修改进度条
+ 拖拽的途中歌曲还是按照原来的节奏正常播放，**修改歌曲播放位置是在鼠标松开的时候**，不然拖拽的时候歌曲进度会很奇怪
+ 只要按下的时候是在小圆点处，鼠标可以在页面里拖拽，所以和上面一样 给小圆点绑定mousedown事件，给document绑定mousemove和mouseup事件，**mouseup事件不在mousedown事件里面**
+ 由于修改歌曲播放位置(确定拖拽最终会造成什么影响)是在松开鼠标(mouseup)事件中，所以在**mouseup事件里造成影响的语句前要判断是否当前是在拖拽结束时引起的mouseup**，如果整个页面的mouseup时都造成影响，就会出现错误（找了好久的bug

#### 9）音量控制进度条

&emsp; 同样是进度条，所以可以**直接用刚刚创建的progress类**，这就是将所有方法封装起来的好处，以后只要有进度条的地方都可以使用这个类，而不用重写代码。仅需要在**player**中添加方法（progress类不用动）

+ `voiceSeekTo(value)` 把value这个值赋给当前音量以修改音量，修改音量就用原生dom的方法，audio.volume=value，注意：这里的volume在0~1间
+ 定义的修改方法仍然要现判断value是否符合条件

#### 10）歌词信息

&emsp; 便于维护与封装，新设置一个类Lyric专门用于控制歌词信息，初始化数据元素path是歌词的路径

+ 歌词信息和歌曲一样都需要从本地文件中读取，因此也要用到ajax方法来获取
+ 定义两个方法，loadLyric和parseLyric，分别用于加载歌词以及将歌词分开固定格式，上面loadLyric中ajax成功(success)后调用parseLyric方法
+ 利用对字符串的分割（用换行符分割每行歌词）以及正则表达式（识别时间），将时间以及对应的歌词分别保存到Lyric的两个数据元素times和lyrs内，注意时间都换成秒，这样便于后面匹配
+ 注意将空字符串或无意义行去掉，就在每次遍历开始的时候识别一下当前行的歌词是否有效，无效则`return true;`——相当于C++的continue
+ 最后在获取好times时间和lyrics每句歌词后，将所有歌词变成li添加到页面中显示歌词的ul处，这个作为一个回调函数在执行完success后的parseLyric后执行callback()

```javascript
$.each(lyric.lyrs, function (index, elem) {
        var $lyc = $("<li>"+elem+"</li>");
        $(".lyric ul").append($lyc);
})
```

+ 最后给页面中显示歌词的ul设置一个固定高度，且`overflow:hidden;`即可

#### 11）歌词同步

&emsp; 歌词同步的基本原理就是，逐个将10）中提取出来的times时间数组与currentTime比较，找到**第一个比currentTime大的时间**，返回其对应的索引，再高亮和跳转到相应位置即可

+ 获取歌曲当前播放的进度，也就是currentTime，之前在同步歌曲进度条的时候就利用回调函数得到了这个值，可以直接在player的musicTimeUpdate方法的回调函数（参数为current, duration, timeStr）里面直接写歌词的同步
+ 获取到currentTime了，在lyric类里新设一个方法currrentIndex来获取当前播放时间对应到歌词数组里是第几句的索引，再给当前句添加相应的高亮类即可
+ 歌词要随着播放而移动，注意这里的移动依然是装着歌词的ul来移动，通过修改margin-top的值来实现移动，可以使用动画（注意移动的距离是负值）