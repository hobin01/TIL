package com.hobin.learn_spring.game;

public class GameRunner {
	
	MarioGame game;
	
	public GameRunner(MarioGame game) {
		this.game = game;
	}
	
	public void run() {
		System.out.println("Running game : " + game);
		
		game.up();
		game.down();
		game.left();
		game.right();
	}
}
