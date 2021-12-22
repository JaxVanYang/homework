package com.example.exam.service.impl;

import com.example.exam.entity.Person;
import com.example.exam.mapper.PersonMapper;
import com.example.exam.service.IPersonService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import org.springframework.stereotype.Service;

/**
 * <p>
 *  服务实现类
 * </p>
 *
 * @author wonker47
 * @since 2021-12-22
 */
@Service
public class PersonServiceImpl extends ServiceImpl<PersonMapper, Person> implements IPersonService {

}
