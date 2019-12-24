$(function () {
    //滚动条插件
    $(".music-info").mCustomScrollbar();
    var $audio = $("audio");
    var player = new Player($audio);
    var $musicList = $(".music-info ul");
    var $musicPlay = $(".playing");
    //用来保存上一次的音量值
    var nowVolume = 1;
    var lyric;

    var progress,voiceProgress;
    initProgress();
    function initProgress() {
        var $progressBar = $(".progress-bar");
        var $progressLine = $(".progress-line");
        var $progressDot = $(".progress-dot");
        progress = Progress($progressBar,$progressLine, $progressDot);
        progress.progressClick(function (value) {
            player.musicSeekTo(value);
        });
        progress.progressMove(function (value) {
            player.musicSeekTo(value);
        });
        player.musicTimeUpdate(function (current, duration, timeStr) {
            //如果正在拖拽 那暂时不要随着歌曲播放变化进度条
            if(progress.isMove) {
                return ;
            }
            //同步时间
            $(".now-time").text(timeStr);
            //同步进度条
            progress.setPosition(current/duration*100);

            //同步歌词
            var index = lyric.currrentIndex(current);

            $(".lyric ul li").eq(index).addClass("lyric-cur").siblings().removeClass("lyric-cur");

            //歌词滚动
            if(index <= 1) return ;
            var height =$(".lyric ul li").height();
            $(".lyric ul").stop().animate({
                "margin-top": -(index-1)*height
            });
        });

        var $vprogressBar = $(".v-progress-bar");
        var $vprogressLine = $(".v-progress-line");
        var $vprogressDot = $(".v-progress-dot");
        voiceProgress = Progress($vprogressBar,$vprogressLine, $vprogressDot);
        voiceProgress.progressClick(function (value) {
            player.voiceSeekTo(value);
        });
        voiceProgress.progressMove(function (value) {
            player.voiceSeekTo(value);
        });
    }

    //加载歌曲列表
    getPlayerList();
    function getPlayerList() {
        $.ajax({
            url: "./source/musiclist.json",
            dataType: "json",
            success: function (data) {

                //直接把歌曲给创建的对象 以后可以通过对象直接查询到信息
                player.musicList = data;
                $.each(data, function (index,value) {
                    var $item = createMusicItem(index,value);
                    $musicList.append($item);
                });
                //初始化歌曲信息 默认是第0首
                updateMusicInfo(data[0]);
                updateLyric(data[0]);
            },
            error: function (reason) {
                console.log(reason);
            }
        })
    }
    function createMusicItem(index,value) {
        var $item = $("<li>\n" +
            "                        <div class=\"li-in\">\n" +
            "                            <div class=\"checkbox\">\n" +
            "                                <input type=\"checkbox\">\n" +
            "                            </div>\n" +
            "                            <div class=\"music-name\">\n" +
            "                                <span>"+(index+1)+"</span>"+value.name+"</div>\n" +
            "                            <div class=\"time\">"+value.time+"</div>\n" +
            "                            <div class=\"singer\">"+value.singer+"</div>\n" +
            "                        </div>\n" +
            "                        <div class=\"li-selection\">\n" +
            "                            <a href=\"javascript:;\" title=\"播放\" class=\"play\">\n" +
            "                                \n" +
            "                            </a>\n" +
            "                            <a href=\"javascript:;\" title=\"添加到歌单\" class=\"add\"></a>\n" +
            "                            <a href=\"javascript:;\" title=\"下载\" class=\"down\">\n" +
            "                            <a href=\"javascript:;\" title=\"分享\" class=\"share\"></a>\n" +
            "                            <a href=\"javascript:;\" title=\"删除\" class=\"del\"></a>\n" +
            "                        </div>\n" +
            "                    </li>")

        //直接把当前这首的索引号和对应的音乐信息作为一个属性
        //绑定到了原生js上 不能用setArrtibute不知道为啥
        $item.get(0).index = index;
        $item.get(0).music = value;
        return $item;
    }

    function updateLyric(music) {
        lyric = new Lyric(music.link_lrc);
        $(".lyric ul").html("");
        lyric.loadLyric(function () {
            $.each(lyric.lyrs, function (index, elem) {
                var $lyc = $("<li>"+elem+"</li>");
                $(".lyric ul").append($lyc);
            })
        });
        
    }
    //初始化歌曲信息
    function updateMusicInfo(music) {
        var $albumImg = $(".album-cover img");
        var $songName = $(".song-name a");
        var $singerName = $(".singer-name a");
        var $albumName = $(".album-name a");
        var $songNameDwon = $(".play-t a").eq(0);
        var $singerNameDwon = $(".play-t a").eq(1);
        var $songTime = $(".now-time");
        var $bgImg = $(".mask-bg");
        $albumImg.attr("src", music.cover);
        $songName.text(music.name);
        $singerName.text(music.singer);
        $albumName.text(music.album);
        $songNameDwon.text(music.name);
        $singerNameDwon.text(music.singer);
        $songTime.text("00:00 / "+music.time);
        $bgImg.css("background-image","url(\""+music.cover+"\")");
    }

    //初始化事件监听
    initEvents();
    function initEvents() {
        $(".user").hover(function () {
            $(".log-out").css("visibility", "visible");
        }, function () {
            $(".log-out").css("visibility", "hidden");
        })
        //由于歌曲是后面读到文件内容后动态创建的列表，因此不能直接用之前的绑定事件方式
        //要用事件委托 找到动态状态前就已经存在的元素ul

        //鼠标移入某首歌 显示菜单栏
        $(".music-info ul").on("mouseenter", "li", function () {
            if($(this).index()!=0) {
                $(this).children(".li-selection").show();
                $(this).find(".time").css("visibility","hidden");
            }
        });
        //鼠标离开
        $(".music-info ul").on("mouseleave", "li", function () {
            if($(this).index()!=0) {
                $(this).children(".li-selection").hide();
                $(this).find(".time").css("visibility","visible");
            }
        });
        //点击前面的多选框 多选框高亮
        $(".music-info ul").on("click", ".checkbox", function () {
            $(this).toggleClass("check-now");
        });
        //点击某首具体的歌 播放
        $(".music-info ul").on("click", ".play", function () {
            var $item = $(this).parents("li");
            $(this).toggleClass("play2");
            $item.find(".music-name span").toggleClass("index-play");
            $item.siblings().css("color","rgba(225,225,225,.8)").find(".play").removeClass("play2");
            $item.siblings().find(".music-name span").removeClass("index-play");
            if($(this).hasClass("play2")) {
                $musicPlay.addClass("playing-now");
                $item.css("color","#fff");
            } else {
                $musicPlay.removeClass("playing-now");
                $item.css("color","rgba(225,225,225,.8)");
            }
            //播放音乐
            player.playMusic($item.get(0).index,$item.get(0).music);
            //更新音乐信息
            updateMusicInfo($item.get(0).music);
            updateLyric($item.get(0).music);
        });
        //下面总播放键的点击
        $(".playing").click(function () {
            $(this).toggleClass("playing-now");
            if(player.currentIndex == -1) {
                $musicList.find(".play").eq(0).click();
            } else {
                $musicList.find(".play").eq(player.currentIndex).trigger("click");
            }
        });
        //切到上一首歌
        $(".last").click(function () {
            $musicList.find(".play").eq(player.preIndex()).click();
        });
        //下
        $(".next").click(function () {
            $musicList.find(".play").eq(player.nextIndex()).trigger("click");
        });
        //点击删除某首歌
        $(".music-info ul").on("click", ".del", function () {
            let $item = $(this).parents("li");
            let index = $item.get(0).index;
            //若**删除的歌曲刚好是在播放的这一首**，则删除当前这首后自动播放下一首歌曲，注意这一步操作要在remove当前li操作的前面！不然会移到下一首的下一首；
            if(index == player.currentIndex) {
                $(".next").trigger("click");
            }
            //在页面中移除元素
            $item.remove();
            //在musicList里删除该首歌的信息
            player.upDateList(index);
            //以下遍历是更新两个number的值
            $(".li-selection").each(function (index, value) {
                //原生dom里存放的index属性的值要更新
                $(value).parent("li").get(0).index = index;
                //页面中歌曲序号也要更新
                $(value).parent("li").find(".music-name span").text(index+1);
            })
        });

        $(".v-img a").click(function () {
            $(this).toggleClass("no-play");
            if($(this).hasClass("no-play")) {
                nowVolume = player.audio.volume;
                player.voiceSeekTo(0);
            } else {
                player.voiceSeekTo(nowVolume);
            }
        })
    }
    player.voiceSeekTo(0.2);
});