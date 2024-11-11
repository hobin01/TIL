package com.hobin.learn_spring;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;


record Person(String name, int age) {};
record Address(String line, String city, String country) {};

@Configuration
public class HelloWorldConfiguration {
	
	@Bean
	public String name() {
		return "Name!!!";
	}
	
	@Bean
	public int age() {
		return 1;
	}
	
	@Bean
	public Person person() {
		var person = new Person("person!!!", 123);
		return person;
	}
	
	@Bean
	public Address address() {
		return new Address("line!!!", "city!!!", "country!!!");
	}
}
