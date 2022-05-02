'use strict';

window.onload = function () {
	initProvince();
	province.onchange = () => {
		console.log('province.onchange');
		provinceChange();
	}
	city.onchange = cityChange;

	var myform = document.forms[0];
	myform.onsubmit = (ev) => {
		ev.preventDefault();
		checkForm();
		console.log(myform);
	}

	var inputs = document.getElementsByTagName("input");
	for (var i = 0; i < inputs.length; i++) {
		var type = inputs[i].type;
		if (type == "text" || type == "password") {
			inputs[i].onfocus = onFoucs;
			inputs[i].onblur = onBlur;
		}
	}
};
