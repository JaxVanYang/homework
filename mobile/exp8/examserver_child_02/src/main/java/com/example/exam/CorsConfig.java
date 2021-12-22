package com.example.exam;

import org.springframework.context.annotation.Configuration;
import org.springframework.http.HttpHeaders;
import org.springframework.web.servlet.config.annotation.CorsRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

@Configuration
public class CorsConfig implements WebMvcConfigurer{	
	
	public WebMvcConfigurer coresConfigurer() {
		return new WebMvcConfigurer() {
			@Override
			public void addCorsMappings(CorsRegistry registry) {
				registry.addMapping("/**").
				allowedOrigins("http://localhost:8081")
				.allowedMethods("*")
				.allowedHeaders("*").allowCredentials(true)
				.exposedHeaders(HttpHeaders.SET_COOKIE).maxAge(3600L);
			}
		};
	}
}
