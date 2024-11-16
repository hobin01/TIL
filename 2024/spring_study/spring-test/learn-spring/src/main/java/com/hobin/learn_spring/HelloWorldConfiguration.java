package com.hobin.learn_spring;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;


record Person(String name, int age, Address addr) {};
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
		var person = new Person("person!!!", 123, address());
		return person;
	}
	
	@Bean
	public Address address() {
		return new Address("line!!!", "city!!!", "country!!!");
	}
	
	@Bean(name="addr2")
	public Address address2() {
		return new Address("line2!!!", "city2!!!", "country2!!!");
	}
	
	@Bean
	public Person person2MethodCall() {
		return new Person(name(), age(), address());
	}
	
	@Bean
	public Person person3Parameters(String name, int age, Address addr2) {
		return new Person(name, age, addr2);
	}
}
