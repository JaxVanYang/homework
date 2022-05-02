'use strict';

function onFoucs() {
	this.select();
	this.style.backgroundColor = "#FFEC8B";
	this.style.color = "#000000";
}

function onBlur() {
	this.style.backgroundColor = "#FFFFFF";
	this.style.color = "#000000";
}

function checkUserName() {
	var userName = document.getElementById("userName");
	if (userName.value == "" || userName.value == "请输入用户名") {
		alert("用户名不能为空");
		userName.focus();
		return false;
	}
	return true;
}

function checkPassword() {
	var userPwd = document.getElementById("userPwd").value;
	var userRePwd = document.getElementById("userRePwd").value;
	if (userPwd === "") {
		alert("密码不能为空！");
		return false;
	} else if (userPwd.length < 6 || userPwd.length > 20) {
		alert("密码长度为6~20位，请进行确认！");
		return false;
	} else if (userPwd != userRePwd) {
		alert("新密码和确认密码不一致！");
		return false;
	}
	var componentCnt = 0;
	for (const regex of [/\d/, /[a-z]/i, /[\@\#\$\%\&\*]/]) {
		if (regex.test(userPwd)) {
			++componentCnt;
		}
	}
	if (componentCnt < 2) {
		alert("密码必须是由字母、数字和符号的两种以上组合!");
		return false;
	}
	return true;
}

function checkForm() {
	return checkUserName() && checkPassword();
}