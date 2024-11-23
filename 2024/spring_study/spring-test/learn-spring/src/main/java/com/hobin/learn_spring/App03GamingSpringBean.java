package com.hobin.learn_spring;

import com.hobin.learn_spring.game.GameRunner;
import com.hobin.learn_spring.game.GamingConsole;

import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class App03GamingSpringBean {

	public static void main(String[] args) {
		try(var context = new AnnotationConfigApplicationContext(GamingConfiguration.class)) {
			context.getBean(GamingConsole.class).up();
			
			context.getBean(GameRunner.class).run();
		}
	}

}
