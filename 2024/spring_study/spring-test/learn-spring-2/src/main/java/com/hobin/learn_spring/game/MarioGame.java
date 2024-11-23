package com.hobin.learn_spring.game;

import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Component;

@Component
@Qualifier("MarioGame")
public class MarioGame implements GamingConsole {
	
	public void up() {
		System.out.println("Mario : Jump!");
	}
	
	public void down() {
		System.out.println("Mario : Go into a hole!");
	}
	
	public void left() {
		System.out.println("Mario : Go back!");
	}
	
	public void right() {
		System.out.println("Mario : Accelerate!");
	}
	
}
