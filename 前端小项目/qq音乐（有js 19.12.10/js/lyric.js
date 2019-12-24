(function (window) {
    function Lyric(path) {
        //拿到歌词的路径
        return new Lyric.prototype.init(path);
    }
    Lyric.prototype = {
        constructor: Lyric,
        init: function (path) {
            this.path = path;
        },
        times: [],
        lyrs: [],
        loadLyric: function (callback) {
            var $this = this;
            this.times = [];
            this.lyrs = [];
            //这里要保存一下this 不然Ajax函数内拿不到
            $.ajax({
                url: this.path,
                dataType: "text",
                success: function (data) {
                    $this.parseLyric(data);
                    callback();
                },
                error: function (reason) {
                    console.log(reason);
                }
            })

        },
        parseLyric: function (data) {
            var $this = this;
            var array = data.split('\n');
            var timeReg = /\[(\d*:\d*\.\d*)\]/;
            $.each(array, function (index, elem) {
                var lyr = elem.split(']')[1];
                if(lyr.length <= 1) return true;
                $this.lyrs.push(lyr);

                var res = timeReg.exec(elem);
                var min = parseFloat(res[1].split(':')[0]);
                var sec = parseFloat(res[1].split(':')[1]);
                var time = Number(parseFloat(min*60+sec).toFixed(2));
                $this.times.push(time);

            })
        },
        currrentIndex: function (currentTime) {
            var index = 0;
            while(currentTime > this.times[index]) {
                index++;
            }
            return index-1;
        }
    };

    //就是这里 要把init的原型指向Player的原型对象 以后就不管是通过init创建的还是直接
    //通过Player创建的对象 原型都指向Player的原型对象  就可以调用其方法
    Lyric.prototype.init.prototype = Lyric.prototype;
    window.Lyric = Lyric;
})(window);