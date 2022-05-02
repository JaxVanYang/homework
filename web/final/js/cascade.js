'use strict';

const provinces = ["山东省", "河北省"];
const cities = [["济南市", "青岛市"], ["石家庄市", "廊坊市"]];
const areas = [
    [
        ["市中区", "历下区", "天桥区", "槐荫区", "历城区", "长清区"],
        ["市南区", "市北区", "四方区", "李沧区", "城阳区", "崂山区"]
    ], [
        ["桥西区", "新华区", "长安区", "裕华区", "井陉区", "藁城区", "鹿泉区", "栾城区"],
        ["安次区", "广阳区", "三河市", "霸州市", "香河县", "永清县", "固安县", "文安县"]
    ]
];


let province, city, area;


function initProvince() {
    province = document.getElementById("province");
    city = document.getElementById("city");
    area = document.getElementById("area");
    province.options.length = 1;
    for (let i = 0; i < provinces.length; i++) {
        const option = new Option(provinces[i], provinces[i]);
        province.options.add(option);
    }
}
function provinceChange() {
    cityChange();
    city.options.length = 1;
    if (province.selectedIndex == 0) {
        return;
    }
    const pIndex = province.selectedIndex;
    for (let i = 0; i < cities[pIndex - 1].length; i++) {
        const optionValue = cities[pIndex - 1][i];
        const option = new Option(optionValue, optionValue);
        city.options.add(option);
    }
}
function cityChange() {
    area.options.length = 1;
    if (city.selectedIndex == 0) {
        return;
    }
    const pIndex = province.selectedIndex;
    const cIndex = city.selectedIndex;
    for (let i = 0; i < areas[pIndex - 1][cIndex - 1].length; i++) {
        let optionValue = areas[pIndex - 1][cIndex - 1][i];
        let option = new Option(optionValue, optionValue);
        area.options.add(option);
    }
}