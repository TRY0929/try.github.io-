$(function () {
    var snakeRun;

    var speed = 200, flag = 0;
    //每个小块的高度
    var minDis = $(".snake").outerHeight();
    //整个游戏模块
    var $game = $(".page");
    var height = $game.height();
    var width = $game.width();
    var type = "ArrowDown";
    var $head, $tail, $food;
    var dic = {"ArrowLeft":"ArrowRight", "ArrowRight":"ArrowLeft", "ArrowUp":"ArrowDown", "ArrowDown":"ArrowUp"};
    var img1 = ['./images/food1.jpg','./images/food2.jpg','./images/food3.jpg','./images/food4.jpg','./images/food5.jpg'];
    var img2 = ['./images/f1.png','./images/f2.png','./images/f3.png','./images/f4.png','./images/f5.png'];

    var init = function () {
        $(".game-box").html("<div class=\"snake snake-tail snake-tail-p\"></div>\n" +
            "            <div class=\"snake\"></div>\n" +
            "            <div class=\"snake snake-head snake-head-p\"></div>");
        type = "ArrowDown";
    };
    var updateTH = function () {
        $head = $(".snake-head");
        $tail = $(".snake-tail");
    };
    var removeElement = function () {
        updateTH();
        var $tmpnode = $("<div class=\"snake\"></div>");
        if(flag === 1) {
            $(".food").remove();
            $tail.removeClass("snake-tail");
            flag = 0;
        } else {
            $tail.remove();
        }
        $tmpnode.removeClass("snake-tail").addClass("snake-head");
        $head.after($tmpnode);
        $head.removeClass("snake-head");
        $(".snake").eq(0).addClass("snake-tail");
        return $tmpnode;
    };
    //判断移动方向和是否撞在墙上的规则
    var moveDirection = function(type) {
        updateTH();
        if(type === "ArrowUp") {
            if($head.position().top-minDis < 0) {
                console.log("上")
                gameOver();
                return false;
            }
            var $tmpnode = removeElement();
            $tmpnode.css({
                top: $head.position().top-minDis,
                left: $head.position().left
            });
        }
        else if(type === "ArrowDown") {
            if($head.position().top+minDis >= height) {
                console.log("下")
                gameOver();
                return false;
            }
            var $tmpnode = removeElement();
            $tmpnode.css({
                top: $head.position().top+minDis,
                left: $head.position().left
            });


        }
        else if(type === "ArrowLeft") {
            if($head.position().left-minDis < 0) {
                console.log("左")
                gameOver();
                return false;
            }
            var $tmpnode = removeElement();
            $tmpnode.css({
                top: $head.position().top,
                left: $head.position().left-minDis
            });
        }
        else if(type === "ArrowRight") {
            if($head.position().left+2*minDis > width) {
                console.log("右")
                gameOver();
                return false;
            }
            var $tmpnode = removeElement();
            $tmpnode.css({
                top: $head.position().top,
                left: $head.position().left+minDis
            });
        }
        updateTH();
        return true;
    };
    var move = function () {
        snakeRun = setInterval(function () {
            if(!moveDirection(type)) return ;
            if($(".food").length === 0) {
                randomFood();
            }
            if(parseInt($food.position().left) === parseInt($(".snake-head").position().left)&&parseInt($food.position().top) === parseInt($(".snake-head").position().top))   {
                flag = 1;
            }
            rule2($head);
        },speed);
    };
    //初始化事件监听
    (function () {
        $(document).keyup(function (event) {
            if(dic[event.key] !== type) {
                type = event.key;
            } else {
                console.log("反了")
            }
        });
        $(".start-btn").click(function () {
            $(".start-page").fadeOut();
            $(".game-box").fadeIn();
            move();
            // init();
        });
        $(".end-btn").click(function () {
            $(".end-page").fadeOut();
            $(".game-box").fadeIn().html("");
            init();
            move();
        });
    })();
    var randomFood = function () {
        var x = Math.floor(Math.random()*40)*minDis;
        var y = Math.floor(Math.random()*25)*minDis;
        var index = Math.floor(Math.random()*5);
        $food = $("<div class=\"food\"></div>");
        $food.css({
            left: x,
            top: y,
            background: "url("+img1[index]+")",
            backgroundSize: "cover"
        });

        $(".game-box").append($food);
    };
    var rule2 = function ($node) {
        $node.siblings(".snake").each(function (index, value) {
            if(parseInt($(value).position().left) === parseInt($node.position().left)
            && parseInt($(value).position().top) === parseInt($node.position().top))
            {
                console.log("自己")
                gameOver();
                return ;
            }
        })
    };
    var gameOver = function () {
        clearInterval(snakeRun);
        $(".end-page").fadeIn();
        $(".score span").text($(".snake").length);
        $head.addClass("error");
    };
});