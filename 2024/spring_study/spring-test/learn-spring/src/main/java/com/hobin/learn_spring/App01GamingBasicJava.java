package com.hobin.learn_spring;

import com.hobin.learn_spring.game.MarioGame;
import com.hobin.learn_spring.game.SuperContraGame; 
import com.hobin.learn_spring.game.PacmanGame;
import com.hobin.learn_spring.game.GameRunner; 

public class App01GamingBasicJava {

	public static void main(String[] args) {

		var game1 = new MarioGame();
		var gameRunner1 = new GameRunner(game1);
		gameRunner1.run();
		
		var game2 = new SuperContraGame();
		var gameRunner2 = new GameRunner(game2);
		gameRunner2.run();
		
		var game3 = new PacmanGame();
		var gameRunner3 = new GameRunner(game3);
		gameRunner3.run();
	}

}
