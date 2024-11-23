package com.hobin.learn_spring.game;

import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Component;

@Component
@Qualifier("SuperContraGame")
public class SuperContraGame implements GamingConsole {
	public void up() {
		System.out.println("SuperContra : Jump!");
	}
	
	public void down() {
		System.out.println("SuperContra : Sit down!");
	}
	
	public void left() {
		System.out.println("SuperContra : Go back!");
	}
	
	public void right() {
		System.out.println("SuperContra : Shoot a bullet!");
	}
}
