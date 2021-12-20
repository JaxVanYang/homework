package com.example.demo.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.ResponseBody;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map.Entry;
import com.example.demo.entity.Fish;

@Controller
public class FishController {
    
    @GetMapping("/fish")
    @ResponseBody
    public List<Fish> getAllFish() {
        List<Fish> ret = new ArrayList<Fish>();
        Fish fish1 = new Fish();
        fish1.setFishId("1");
        fish1.setFishName("鲫鱼");
        fish1.setFishFamily("鲫鱼科");
        Fish fish2 = new Fish();
        fish2.setFishId("2");
        fish2.setFishName("鲤鱼");
        fish2.setFishFamily("鲤鱼科");

        ret.add(fish1);
        ret.add(fish2);
        return ret;
    }

    @GetMapping("/fish/id/{fishId}")
    @ResponseBody
    public Fish getFishById(
        @PathVariable("fishId") String fishId) {
        Fish fish1 = new Fish();
        fish1.setFishId("1");
        fish1.setFishName("鲫鱼");
        fish1.setFishFamily("鲫鱼科");
        Fish fish2 = new Fish();
        fish2.setFishId("2");
        fish2.setFishName("鲤鱼");
        fish2.setFishFamily("鲤鱼科");

        if (fishId.equals("1")) {
            return fish1;
        } else if (fishId.equals("2")) {
            return fish2;
        }

        return null;
    }

    @PostMapping("/fish")
    @ResponseBody
    public HashMap<String, Object> insertFish(Fish fish) {
        HashMap<String, Object> ret = new HashMap<>();
        System.out.println(fish);
        ret.put("success", true);
        ret.put("msg", "插入" + fish.getFishName() + "成功");
        return ret;
    }

    @PostMapping("/fish/hashpara")
    @ResponseBody
    public HashMap<String, Object> getFishByHashMap(
        @RequestBody HashMap<String, Object> hashMap) {
        HashMap<String, Object> ret = new HashMap<>();
        for (Entry<String, Object> entry : hashMap.entrySet()) {
            System.out.println(entry.getKey() + ":" + entry.getValue());
        }
        ret.put("success", true);
        ret.put("msg", "");
        return ret;
    }

    @DeleteMapping("/fish/id/{fishId}")
    @ResponseBody
    public HashMap<String, Object> deleteFishById(
        @PathVariable("fishId") String fishId) {
        HashMap<String, Object> ret = new HashMap<>();
        if (fishId.equals("1") || fishId.equals("2")) {
            ret.put("success", true);
            ret.put("msg", "删除" + fishId + "成功");
        } else {
            ret.put("success", false);
            ret.put("msg", fishId + "不存在");
        }
        return ret;
    }

    @PutMapping("/fish")
    @ResponseBody
    public HashMap<String, Object> putFish(Fish fish) {
        HashMap<String, Object> ret = new HashMap<>();
        System.out.println("修改学生信息：" + fish);
        ret.put("success", true);
        ret.put("msg", "更新" + fish.getFishName() + "成功");
        return ret;
    }
}
