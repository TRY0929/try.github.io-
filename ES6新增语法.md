## ES6新增语法

### 一、let变量

#### 1）使用let关键字声明的变量具有块级作用域

+ 块级作用域，即一个大括号内的区域(如if for)；
+ 在大括号中，使用let关键字声明的变量才具有块级作用域。

#### 2）使用let关键字声明的变量没有变量提升

+ 变量提升，即语言支持 先使用变量再声明。

#### 3）使用let声明的变量 暂时性死区

+ 即使在作用域之外用var定义了同名变量，若在作用域内也定义了同名变量，则声明之前还是无法使用外部的那个变量，会报错，如下：

```javascript
var num = 20;
if (true) {
	console.log(num)
	let num = 10;
}
```

#### 4）var与let使用比较(面试题)

```javascript
var arr = [];
for(var i = 0; i<2;i++) {
	arr[i] = function() {
		console.log(i)
	}
}
arr[0]();
arr[1]();
```

+ 上面这段代码的输出结果都是2；
+ 这时由于 **函数是在执行的时候才去在作用域中寻找i的值**，i为全局变量，执行时i的值以及为2，所以输出都是2。

```javascript
var arr = [];
for(let i = 0; i<2;i++) {
	arr[i] = function() {
		console.log(i)
	}
}
arr[0]();
arr[1]();
```

+ 这段代码就是输出 0 1；
+ 这时由于**每次循环都会产生一个块级作用域**，每个块级作用域中的变量都是不同的，函数执行时输出的是自己上一级(循环产生的块级作用域)作用域下的i值。

### 二、const关键字

作用：声明常量，常量就是值(内存地址)不能变化的量。

#### 1）具有块级作用域

#### 2）声明变量时必须赋初值

#### 3）常量赋值后，值不能修改

+ 若是常量，则的确不能修改，必须数字；
+ 但是若是数组、对象这种保存的是地址的值，可以修改该地址内保存的值，但不能修改地址(即将其他数组赋给该常量)

| var        | let            | const          |
| ---------- | -------------- | -------------- |
| 函数作用域 | 块级作用域     | 块级作用域     |
| 变量提升   | 不存在变量提升 | 不存在变量提升 |
| 值可更改   | 值可更改       | 值不可更改     |

### 三、解构

+ 数组解构允许按照一一对应的关系从数组中提取值，然后赋值给变量；

```javascript
let ary = [1, 2, 3];
let [a, b, c] = ary; //左边[]代表是数组解构
```

+ 对象解构允许使用变量的名字匹配对象的属性，匹配成功将对象的值赋值给变量；

```javascript
let person = {name: 'try', age: '20'};
let {name: myName, age: myAge} = person; //左边{}代表是对象解构
```

### 四、箭头函数

#### 1）若函数体内只有一句代码，且代码的执行结构就是返回值，则可以省略大括号；

```javascript
function sum(num1, num2) {
	return num1+num2;
}
const fn = (num1, num2) => num1+num2;
```

#### 2）若形参只有一个，则装形参的小括号可以省略；

```javascript
function(v) {
	return v;
}
const fn = v => v;
```

#### 3）箭头函数不绑定this关键字，箭头函数中的this指向**函数定义位置**的上下文this；

+ 明明retFn是在全局环境下调用，为什么还是会输出obj？这时由于，上面retFn在得到的时候就是fn在obj环境下调用的，也就是定义的环境是obj，即使运行环境是全局，但还是输出定义时的对象。

```javascript
const obj = {name: 'try'};
function fn() {
	console.log(this);
	return () => {
		console.log(this);
	}
}
const retFn = fn.call(obj); //输出obj——不是箭头函数
retFn(); //输出obj——是箭头函数
```

#### 4）面试题(this指向的问题)

+ 箭头函数没有自己的this，就会去它定义的那一层去找，但是**对象是不能产生作用域的**，所以定义的时候作用域实际上是全局，因此输出的为全局的type。

```javascript
var type = '全局';
var obj = {
	type: 'obj',
	sayType: () => {
		console.log(this.type);
	}
}
obj.sayType(); //输出 全局
```

### 五、剩余参数

+ 当函数的参数个数不固定时，要一次性拿到所有的参数，之前是用过this.arguments来获得参数列表，但**箭头函数不能使用this**，所以这里采用：

```javascript
const sum = (...args) => {
	let totle = 0;
	args.forEach(item => totle += item);
	return totle;
}
console.log(sum(10, 20, 30));
```

+ 剩余参数与数组解构结合使用：

```javascript
var array = [1, 2, 3, 4, 5];
let [arr1, ...arr2] = array;
console.log(arr1, arr2);
```

### 六、扩展运算符

#### 1）扩展运算符可以将数组或对象转为用逗号分隔的参数序列

+ 下面用console.log打印没有逗号的原因是，逗号在这里被console.log当作了参数分隔符：

```javascript
var arr = [1, 2, 3, 4, 5];
...arr // 1, 2, 3, 4, 5
console.log(...arr) //1 2 3 4 5
console.log(1, 2, 3, 4, 5) //1 2 3 4 5
```

#### 2）扩展运算符应用于数组合并

```javascript
let arr1 = [1, 2, 3];
let arr2 = [4, 5, 6];
//法一：
let arr = [...arr1, ...arr2];
console.log(arr); //[1 2 3 4 5 6]
//法二：
arr1.push(...arr2);
console.log(arr1); //[1 2 3 4 5 6]
```

#### 3）利用扩展运算符将伪数组转变为真正的数组

```javascript
let divs = document.getElementById('div'); //伪数组
divs = [...divs]; //真正的数组
```

### 七、ES6的内置对象扩展

#### 1）Array的扩展方法

+ 构造函数方法：**Array.from()**，将伪数组转变为真正的数组：

```javascript
let arrl = {
	'0': '1',
	'1': '2',
	'2': '3',
	'length': 3
}; //伪数组
let arr = Array.from(arrl, item => item*2); //真正的数组 第二个参数为一个函数，对每个元素进行处理
console.log(arr);
```

+ 实例方法：**find()**，找出第一个符合条件的数组成员，若未找到则返回undefined，参数为一个函数：

```javascript
let arr = [{
	name: 'try',
	id: '1'
	}, {
	name: 'shun',
	id: '2'
}]
let tar = arr.find((item, index) => item.id === '2');
console.log(tar);
```

+ 实例方法：**findIndex()**，找出第一个符合条件的数组成员的索引，若未找到则返回-1，使用方法和上面一样。

+ 实例方法：**includes()**，表示某个数组是否包含特定的值，返回布尔值。

#### 2）String的扩展方法

+ **模板字符串**，使用反引号定义；
  + 模板字符串中可以解析变量：

```javascript
let name = 'try';
let sayName = `My name is ${name}`;
console.log(sayName); //My name is try
```

+ 模板字符串可以换行；

+ 模板字符串中可以调用函数：

```javascript
const fn = () => {return 'try';}
let sayName = `My name is ${fn()}`;
console.log(sayName); //My name is try
```

+ 实例方法：**startsWith() endsWith()**，判断参数字符串是否在原字符串的头(尾)部，返回布尔值。

+ 实例方法**repeat()**，表示将原字符串重复n次，返回一个新字符串：

```javascript
let str = 'x'.repeat(2); //'xxx'
```

