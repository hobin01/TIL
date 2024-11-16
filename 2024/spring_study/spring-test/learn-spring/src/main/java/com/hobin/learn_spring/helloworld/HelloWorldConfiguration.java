package com.hobin.learn_spring.helloworld;

import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Primary;


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
	@Primary
	public Address address() {
		return new Address("line!!!", "city!!!", "country!!!");
	}
	
	@Bean(name="addr2")
	@Qualifier("addr3qualifier")
	public Address address2() {
		return new Address("line2!!!", "city2!!!", "country2!!!");
	}
	
	@Bean
	@Primary
	public Person person2MethodCall() {
		return new Person(name(), age(), address());
	}
	
	@Bean
	public Person person3Parameters(String name, int age, Address addr) {
		return new Person(name + "123", age, addr);
	}
	
	@Bean
	public Person person4Qualifier(String name, int age, @Qualifier("addr3qualifier") Address addr) {
		return new Person(name, age, addr);
	}
}
