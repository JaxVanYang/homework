package com.example.exam;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
@MapperScan("com.example.exam.mapper")
public class ExamserverChild02Application {

	public static void main(String[] args) {
		SpringApplication.run(ExamserverChild02Application.class, args);
	}

}
