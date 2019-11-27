//要注意等全部页面加载完毕才可以开始执行
window.addEventListener("load", function(){
	var focus = document.querySelector(".focus");
	var circle = document.querySelector(".circle");
	var sliderL = document.querySelector(".slider-l");
	var sliderR = document.querySelector(".slider-r");
	var cirul = circle.querySelector("ul");
	var focul = focus.querySelector("ul");
	var num=0, cur=0;
	//获得总共有的焦点图个数
	var len = focul.children.length;
	var imgWidth = focul.children[0].offsetWidth;

	for(let i=0;i<len;++i) {
		var li = document.createElement("li");
		//给每个小圆点建立一个新的属性 index 便于后面焦点图的位置变化
		li.setAttribute("index",i);

		//动态生成小圆点并加进去
		cirul.appendChild(li); 
		li.addEventListener("click", function(event){
			var index = this.getAttribute("index");
			num = index;
			cur = index;
			for(let j=0;j<len;++j) {
				cirul.children[j].style.backgroundColor = "#999";
			}
			this.style.backgroundColor = "rgba(0,0,0,0)";
			//注意这里是负的 为什么？因为是距左边的距离改成这么多
			animate(focul, -imgWidth*index);
		})
	}
	//初始第一个小圆点被选中 播放第一张图片
	cirul.children[0].style.backgroundColor = "rgba(0,0,0,0)";
	//在最后增加一个新图片 用于缓冲 若到这个图片了 就迅速跳回(人类无法感知的快速)第一张图片
	focul.appendChild(focul.children[0].cloneNode(true));
	sliderR.addEventListener("click", function(event) {
		//若到了最后一张图(实际上是到达了虚拟的第一张图)
		if(num == len) {
			num = 0;
			//迅速跳回第一张
			focul.style.left = '0px';
		}
		++num;
		++cur;
		if(cur == len) {cur = 0;}
		animate(focul, -num*imgWidth);
		for(let j=0;j<len;++j) { //排他思想
			cirul.children[j].style.backgroundColor = "#999";
		}
		cirul.children[cur].style.backgroundColor = "rgba(0,0,0,0)";
	})
	sliderL.addEventListener("click", function(event) {
		if(num == 0) {
			num = len;
			focul.style.left = -len*imgWidth+'px';
		}
		--num;
		if(cur == 0) {
			cur = len;
		}
		--cur;
		animate(focul, -num*imgWidth);
		for(let j=0;j<len;++j) {
			cirul.children[j].style.backgroundColor = "#999";
		}
		cirul.children[cur].style.backgroundColor = "rgba(0,0,0,0)";
	})
	//设置定时器 每三秒自动换图片
	var timer = setInterval(function() {
		sliderR.click();
	}, 3000);

	//离开则把定时加上
	focus.addEventListener("mouseleave", function(event){
		timer = setInterval(function() {
			sliderR.click();
		}, 3000);
	})

	//若鼠标在焦点大图上则取消定时
	focus.addEventListener("mouseover", function(event){
		clearInterval(timer);
		timer = null;
	})
})