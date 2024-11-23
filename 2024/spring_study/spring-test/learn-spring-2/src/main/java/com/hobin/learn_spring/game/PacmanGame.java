package com.hobin.learn_spring.game;

import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.context.annotation.Primary;
import org.springframework.stereotype.Component;

@Component
@Primary
@Qualifier("PacmanGame")
public class PacmanGame implements GamingConsole {
	
	public void up() {
		System.out.println("Pacman : Up!");
	}
	
	public void down() {
		System.out.println("Pacman : Down!");
	}
	
	public void left() {
		System.out.println("Pacman : Left!");
	}
	
	public void right() {
		System.out.println("Pacman : Right!");
	}
	
}
