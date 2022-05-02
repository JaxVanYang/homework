'use strict';
const prefix = "../images/index/pic";

let sign = 2;
function showPic(index) {
    const focusImg = document.getElementById("focusImg");
    const imgSrc = prefix + index + ".jpg";
    focusImg.src = imgSrc;
    let lis = document.getElementsByClassName("focusBox")[0].getElementsByTagName("li");
    for (const li of lis) {
        li.className = "";
    }
    lis[index - 1].className = "cur";
}

function setCurrentPic() {
    showPic(sign);
    sign = 1 + sign % 3;
}

window.onload = () => {
    showPic(1);
}
window.setInterval("setCurrentPic()", 5000);