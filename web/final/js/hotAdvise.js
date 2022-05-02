'use strict';

const JSONData = {
	name: "热门推荐",
	srcPath: "../images/shopshow/",
	data: [{ href: "#", src: "s1.jpg", price: 56.00 },
	{ href: "#", src: "s2.jpg", price: 97.00 },
	{ href: "#", src: "s3.jpg", price: 89.00 },
	{ href: "#", src: "s4.jpg", price: 69.00 },
	{ href: "#", src: "s5.jpg", price: 35.00 },
	{ href: "#", src: "s6.jpg", price: 18.00 },
	{ href: "#", src: "s7.jpg", price: 76.00 },
	{ href: "#", src: "s8.jpg", price: 82.00 },
	{ href: "#", src: "s9.jpg", price: 60.00 },
	{ href: "#", src: "yifu1.jpg", price: 45.00 },
	{ href: "#", src: "yifu2.jpg", price: 92.00 },
	{ href: "#", src: "yifu3.jpg", price: 16.00 },
	{ href: "#", src: "yifu4.jpg", price: 42.00 },
	{ href: "#", src: "yifu5.jpg", price: 79.00 }]
};

function checkNum(array, num) {
	for (const item of array) {
		if (item == num) return true;
	}
	return false;
}

function getRandomNum(num, minNum, maxNum) {
	const array = [];
	for (let i = 0; i < num; i++) {
		do {
			const randomNum = Math.floor(Math.random() * maxNum + minNum);
			if (!checkNum(array, randomNum)) {
				array.push(randomNum);
				break;
			}
		} while (true);
	}
	return array;
}

function showHotAdvise() {
	let adviseContent = '<h1 class="notice_title">'
		+ JSONData.name + '</h1><ul class="pic_list3">';
	let turnShow = getRandomNum(9, 0, 14);
	for (let i = 0; i < turnShow.length; i++) {
		let index = turnShow[i];
		adviseContent = adviseContent + '<li><a href="' + JSONData.data[index].href
			+ '"><img src="' + JSONData.srcPath + JSONData.data[index].src
			+ '" width="80" height="80"/></a><p class="price2">￥'
			+ JSONData.data[index].price + '元</p></li>';
	}
	adviseContent = adviseContent + '</ul>';
	document.getElementsByClassName("right_nav")[0].innerHTML = adviseContent;
}

window.onload = () => {
	let adviseContent = '<h1 class="notice_title">'
		+ JSONData.name + '</h1><ul class="pic_list3">';
	const turnShow = getRandomNum(9, 0, 14);
	for (let i = 0; i < turnShow.length; i++) {
		const index = turnShow[i];
		adviseContent = adviseContent + '<li><a href="' + JSONData.data[index].href
			+ '"><img src="' + JSONData.srcPath + JSONData.data[index].src
			+ '" width="80" height="80"/></a><p class="price2">￥'
			+ JSONData.data[index].price + '元</p></li>';
	}
	adviseContent = adviseContent + '</ul>';
	document.getElementsByClassName("right_nav")[0].innerHTML = adviseContent;
};

window.setInterval("showHotAdvise()", 2000);