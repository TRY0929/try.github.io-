(function (window) {
    function Progress($progressBar,$progressLine,$progressDot) {
        //这里其实是是new了一个init对象 而init对象的prototype指向的是自己的原型对象
        //而不是Player的原型对象 因此后面要改
        return new Progress.prototype.init($progressBar,$progressLine,$progressDot);
    }
    Progress.prototype = {
        constructor: Progress,
        //定义一个数据元素判断当前是否在拖拽进度条 如果在拖拽则暂时不让音乐进度变化
        //（否则会拖拽的时候断断续续很难听）
        isMove: false,
        init: function ($progressBar,$progressLine,$progressDot) {
            this.$progressBar = $progressBar;
            this.$progressLine = $progressLine;
            this.$progressDot = $progressDot;
        },
        progressClick: function (callback) {
            var $this = this;
            var left = this.$progressBar.offset().left;
            var w;
            this.$progressBar.click(function (event) {
                w = event.pageX - left;
                $this.$progressLine.width(w);
                $this.$progressDot.css("left", w);
                callback(w/$this.$progressBar.width());
            });
            this.$progressLine.click(function (event) {
                w = event.pageX - left;
                $this.$progressLine.width(w);
                $this.$progressDot.css("left", w);
                callback(w/$this.$progressBar.width());
            });
        },
        progressMove: function (callback) {
            //歌曲正在拖拽
            let $this = this;
            let Left = $this.$progressBar.offset().left;
            let width = $this.$progressBar.width();
            this.$progressDot.mousedown(function (event) {
                $this.isMove = true;
                var w = event.pageX - Left;
                $this.$progressLine.width(w);
                $this.$progressDot.css("left", w);
                $(document).mousemove(function (event) {
                    var w = event.pageX - Left;
                    if(w < 0) {
                        w = 0;
                    } else if(w > width) {
                        w = width;
                    }
                    $this.$progressLine.width(w);
                    $this.$progressDot.css("left", w);
                });
            });
            $(document).mouseup(function (event) {
                $(document).off("mousemove");
                //拖拽完了 开始继续修改
                if($this.isMove) {
                    //注意 由于这里是给文档添加的mouseup，但是要仅在拖拽的时候起效，所以要
                    //添加判断条件
                    $this.isMove = false;
                    callback((event.pageX - Left)/$this.$progressBar.width());
                }
            })

        },
        setPosition: function (value) {
            this.$progressLine.width(value+'%');
            this.$progressDot.css("left", value+'%');
        }
    };

    //就是这里 要把init的原型指向Player的原型对象 以后就不管是通过init创建的还是直接
    //通过Player创建的对象 原型都指向Player的原型对象  就可以调用其方法
    Progress.prototype.init.prototype = Progress.prototype;
    window.Progress = Progress;
})(window)