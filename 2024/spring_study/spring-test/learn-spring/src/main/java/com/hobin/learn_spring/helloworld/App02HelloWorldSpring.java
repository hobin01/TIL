package com.hobin.learn_spring.helloworld;

import java.util.Arrays;

import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class App02HelloWorldSpring {

	public static void main(String[] args) {
		// 1. launch a spring context
		var context = 
				new AnnotationConfigApplicationContext(HelloWorldConfiguration.class);
		
		// 2. configure the things that we want Spring to manage
		// HelloWorldConfiguration - @Configuration
		// name - @Bean
		
		// 3. retrieving Beans managed by Spring
		System.out.println(context.getBean("name"));
		
		System.out.println(context.getBean("age"));
		
		System.out.println(context.getBean("person"));

		System.out.println(context.getBean("address"));
		
		System.out.println(context.getBean("person2MethodCall"));
		
		System.out.println(context.getBean("person3Parameters"));
		
		System.out.println(context.getBean("person4Qualifier"));

		
		System.out.println("==========");
		
		// bean definition
		Arrays.stream(context.getBeanDefinitionNames()).forEach(System.out::println);
	}

}
