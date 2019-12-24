$(function () {
    var $game = $(".game-container");
    var top = 0;
    var speed = 2;
    var domMove, timer, countTime;
    //获取游戏大盒子离上面的距离 下面用来判断有没有元素没被按到
    var totalY = $(".game").offset().top;
    //创建一整个页面 并添加进去
    var createDom = function () {
        var $content = $("<div class=\"game-page\">\n" +
            "            <div class=\"row1\">\n" +
            "                <div class=\"cell1\"></div>\n" +
            "                <div class=\"cell2\"></div>\n" +
            "                <div class=\"cell3\"></div>\n" +
            "                <div class=\"cell4\"></div>\n" +
            "            </div>\n" +
            "            <div class=\"row2\">\n" +
            "                <div class=\"cell1\"></div>\n" +
            "                <div class=\"cell2\"></div>\n" +
            "                <div class=\"cell3\"></div>\n" +
            "                <div class=\"cell4\"></div>\n" +
            "            </div>\n" +
            "            <div class=\"row3\">\n" +
            "                <div class=\"cell1\"></div>\n" +
            "                <div class=\"cell2\"></div>\n" +
            "                <div class=\"cell3\"></div>\n" +
            "                <div class=\"cell4\"></div>\n" +
            "            </div>\n" +
            "            <div class=\"row4\">\n" +
            "                <div class=\"cell1\"></div>\n" +
            "                <div class=\"cell2\"></div>\n" +
            "                <div class=\"cell3\"></div>\n" +
            "                <div class=\"cell4\"></div>\n" +
            "            </div>\n" +
            "        </div>");
        //给每一行随机来一个结点变黑色
        $content.children().each(function () {
            var v = Math.ceil(Math.random()*4);
            $(this).children(".cell"+v).addClass("no-click");
        });
        //注意是添加到前面而不是后面
        $game.prepend($content);
    };
    //页面移动开始 设定一个定时器每20ms移动 平滑效果好一点
    //注意这里如果用animate就不太好随着移动判断有没有超过边缘
    //每什么好的时间监听 除非像listener一样手动设置监听
    var move = function () {
        //下面点开看看
        timer = setInterval(function () {
            //获取当前这个移动的大盒子走了多远了
            top = $game.position().top;
            //如果超过了就别让它超
            if(top + speed >= 0) {
                top = 0;
            } else {
                top += speed;
            }
            //通过每20ms修改top值实现移动
            $game.css("top", top);
            //top>=0实际上是移动到了最下面 也就是要回去了
            //这个时候创建一个结点 就有俩结点了 把盒子撑开了 那回到-460px实际上是回到了
            //新节点那里 从0~460是老的 实现了无缝对接 这里有点需要思考
            //所以这里创建的结点就一定不能脱离文档流 就不能是absolute 因为会不占位置
            if(top >= 0) {
                createDom();
                $game.css("top", "-460px");
                // top = -460;
            }
            //以防加了太多的孩子
            if($game.children().length>=3) {
                $game.children().eq(-1).remove();
            }
        }, 20);
    };
    var gameOver = function($this) {
        // clearInterval(timerAdd);
        clearInterval(domMove);
        clearInterval(timer);
        clearInterval(countTime);
        $this.addClass("error");
        setTimeout(function () {
            alert("游戏结束！\n您的得分是"+$(".score span").text()+"");
            $(".end-page").fadeIn(500);
            $game.html("");
            $(".timing").hide();
        }, 500);

    };
    //初始化绑定事件 就只有开始和重新开始按钮 and cell的点击
    var initEvents = function () {
        $(".start-btn").click(function () {
            //开始页面出去 开始游戏了
            $(".begin-page").fadeOut(500);
            //页面开始移动
            move();
            //安排一个计时器来自己手动监听有没有no-click的黑块没被按到但是到下面的边缘了
            listener();
            //获取时间毫秒
            timing();
        });
        //重新开始按钮和开始按钮功能也差不多
        $(".restart-btn").click(function () {
            $(".end-page").fadeOut(500);
            move();
            //分数清零
            $(".score span").text(0);
            //时间清零
            $(".timing p").text(0);
            listener();
            timing();
        });
        $game.on("click", ".cell1", click);
        $game.on("click", ".cell2", click);
        $game.on("click", ".cell3", click);
        $game.on("click", ".cell4", click);
    };
    //给后面绑定给cell用的 用来判断是按到了黑还是白块
    //加分还是结束游戏
    var click = function () {
        if ($(this).hasClass("no-click")) {
            $(this).removeClass("no-click").addClass("clicked");
            var sc = parseInt($(".score span").text());
            $(".score span").text(sc + 1);
            if(sc>0 && sc%8 == 0) {
                speed += 1;
            }
        } else {
            gameOver($(this));
        }
    };
    //监听有没有黑块没被按到就碰到下边缘了
    var listener = function() {
        domMove = setInterval(function () {
            $(".no-click").each(function () {
                var y = $(this).offset().top-totalY;
                if(y >= 362) {
                    gameOver($(this));
                }
            })
        },100);
    };
    //获取毫秒时间
    var timing = function() {
        $(".timing").show();
        var t1 = new Date().getTime();
        countTime = setInterval(function () {
            var t2 = new Date().getTime();
            var t = t2-t1;
            var mseconds = parseInt(t%1000);
            var seconds = parseInt(t/1000);
            var str = seconds +'.'+ mseconds;
            $(".timing p").text(str);
        },1);

    };

    initEvents();
    //首先就来调用一次这个函数 创建一个游戏页面先
    createDom();

});