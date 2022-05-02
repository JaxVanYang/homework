var sign = 2;

function showPic(index) {
    var focusImg = document.getElementById("focusImg");
    var imgSrc = "images/index/pic";
    imgSrc = imgSrc + index + ".jpg";
    focusImg.src = imgSrc;
    var lis = document.getElementsByClassName("focusBox")[0].getElementsByTagName("li");
    for (var i = 0; i < lis.length; i++) {
        lis[i].className = "";
    }
    lis[index - 1].className = "cur";
}

function setCurrentPic() {
    showPic(sign);
    sign++;
    if (sign == 4) {
        sign = 1;
    }
}

window.onload = function () {
    showPic(1);
}

window.setInterval("setCurrentPic()", 1000);
