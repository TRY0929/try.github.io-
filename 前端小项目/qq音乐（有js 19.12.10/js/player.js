(function (window) {
    function Player($audio) {
        //这里其实是是new了一个init对象 而init对象的prototype指向的是自己的原型对象
        //而不是Player的原型对象 因此后面要改
        return new Player.prototype.init($audio);
    }
    Player.prototype = {
        constructor: Player,
        musicList: [],
        init: function ($audio) {
            this.$audio = $audio;

            //获得原生dom元素 以后有用
            this.audio = $audio.get(0);
        },
        //记录当前播放的是哪一首
        currentIndex: -1,
        playMusic: function (index, music) {
            //判断点击的和当前播放的是不是同一首
            if(this.currentIndex == index) {
                //是同一首 那就看当前是暂停还是播放
                if(this.audio.paused) {
                    //暂停 那就播放
                    //这里是播放和暂停 是用的原生audio元素的方法 play和pause
                    this.audio.play();
                } else {
                    this.audio.pause();
                }
            } else {
                //不是同一首 直接换音乐的地址 再播放
                this.audio.src = music.link_url;
                this.audio.play();
                this.currentIndex = index;
            }
        },
        //处理前一首歌的索引
        preIndex: function () {
            //啊啊啊啊注意 这里不能将currentIndex直接改变啊啊
            //因为一会点击的时候还要再改变 现在改了一会儿就不会改了啊啊
            if(this.currentIndex < 1) {
                return this.musicList.length-1;
            }
            return this.currentIndex-1;
        },
        //处理后一首歌的索引
        nextIndex: function () {
            if(this.currentIndex >= this.musicList.length-1) {
                return 0;
            }
            return this.currentIndex+1;
        },
        //删除musicList中的音乐信息 并且同时更新currentIndex（不然会有bug
        upDateList: function(index) {
            this.musicList.splice(index, 1);
            //若删除的这首处于当前播放歌曲的前面，则currentIndex要减一
            if(index < this.currentIndex) {
                this.currentIndex--;
            }

        },
        //随着音乐播放更新时间
        musicTimeUpdate: function (callback) {
            // 传递一个回调函数过来，每次调用这个函数就可以了，不用return回去
            var $this = this;
            this.$audio.on("timeupdate", function () {
                // 有个事件名字就是timeupdate，是audio的
                //获得歌曲目前播放时间（原生方法）
                let current = $this.audio.currentTime;
                //获得歌曲总时长（原生方法）
                let duration = $this.audio.duration;
                let timeStr = $this.formatData(current,duration);
                //在这里return无法回到index.js里
                callback(current, duration, timeStr);
            });
        },
        //格式化时间
        formatData: function(time,duration) {
            let endMin = parseInt(duration/60);
            if(endMin < 10) {
                endMin = '0'+endMin;
            }
            let endSec = parseInt(duration%60);
            if(endSec < 10) {
                endSec = '0'+endSec;
            }
            let min = parseInt(time/60);
            if(min < 10) {
                min = '0'+min;
            }
            let sec = parseInt(time%60);
            if(sec < 10) {
                sec = '0'+sec;
            }
            return min + ':'+ sec + " / " + endMin + ':' + endSec;
    },
        //跳转到指定时间
        musicSeekTo: function (value) {
            if(isNaN(value)) return ;
            if(value < 0) value = 0;
            else if(value > 1) value = 1;
            this.audio.currentTime = value*(this.audio.duration);
        },
        voiceSeekTo: function (value) {
            if(isNaN(value)) return ;
            if(value < 0) value = 0;
            else if(value > 1) value = 1;
            this.audio.volume = value;
        }

    };

    //就是这里 要把init的原型指向Player的原型对象 以后就不管是通过init创建的还是直接
    //通过Player创建的对象 原型都指向Player的原型对象  就可以调用其方法
    Player.prototype.init.prototype = Player.prototype;
    window.Player = Player;
})(window)