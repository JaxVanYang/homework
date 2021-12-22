package com.example.exam.controller;


import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.core.conditions.update.LambdaUpdateWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.example.exam.Pages;
import com.example.exam.entity.Person;
import com.example.exam.mapper.PersonMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import java.util.HashMap;
import java.util.List;

@Controller
@RequestMapping("/person")
public class PersonController {
    @Autowired
    PersonMapper personMapper;

    @ResponseBody
    @GetMapping("/all")
    public List<Person> getAll() {
        return personMapper.selectList(null);
    }

    @ResponseBody
    @GetMapping("/id/{id}")
    public Person getPersonById(@PathVariable("id") String id) {
        QueryWrapper<Person> querycond = new QueryWrapper<Person>();
        querycond = querycond.eq("pid", id);
        List<Person> pList = personMapper.selectList(querycond);
        if (pList != null) {
            return pList.get(0);
        } else {
            System.out.println("error");
            return null;
        }
    }

    @SuppressWarnings({"rawtypes", "unchecked"})
    @ResponseBody
    @PostMapping("/")
    public HashMap insertPeron(@RequestBody Person person) {
        HashMap result = new HashMap();
        result.put("success", false);
        int i = personMapper.insert(person);
        if (i == 1) {
            result.put("success", true);
        }
        return result;
    }

    @SuppressWarnings({"rawtypes", "unchecked"})
    @ResponseBody
    @PutMapping("/")
    public HashMap updatePeron(@RequestBody Person person) {
        HashMap<String, Boolean> result = new HashMap();
        result.put("success", false);
        LambdaUpdateWrapper<Person> uu = new LambdaUpdateWrapper<Person>();
        uu = uu.set(Person::getPjob, person.getPjob());
        uu = uu.eq(Person::getPid, person.getPid());
        int i = personMapper.update(null, uu);
        if (i == 1) {
            result.put("success", true);
        }
        return result;
    }

    @SuppressWarnings({"rawtypes", "unchecked"})
    @ResponseBody
    @GetMapping("/")
    public HashMap hello() {
        HashMap hash = new HashMap();
        hash.put("hello", true);
        return hash;
    }

    @SuppressWarnings({"rawtypes", "unchecked"})
    @ResponseBody
    @GetMapping("/pages")
    public HashMap getPages(@RequestBody Pages pages) {
        HashMap result = new HashMap();
        System.out.println(pages);
        if (null == pages) {
            pages = new Pages();
            pages.setCurrentpage(1);
            pages.setPagesize(10);
        } else {
            if (null == pages.getCurrentpage()) {
                pages.setCurrentpage(Integer.valueOf(0));
            }
            if (null == pages.getPagesize()) {
                pages.setPagesize(Integer.valueOf(10));
            }
        }
        Page<Person> page;
        page = new Page<Person>(pages.getCurrentpage(), pages.getPagesize());
        Page<Person> userIPage = personMapper.selectPage(page, null);
        List<Person> records = userIPage.getRecords();
        int count = personMapper.selectCount(null);
        if (null != records) {
            pages.setCounts(count);
            pages.setPagesize(records.size());
            pages.computePageByCountandPagesize();
        } else {
            pages.setCounts(0);
            pages.setCurrentpage(0);
            pages.setPages(0);
        }
        result.put("success", true);
        result.put("pages", pages);
        result.put("person", records);
        return result;
    }
}


