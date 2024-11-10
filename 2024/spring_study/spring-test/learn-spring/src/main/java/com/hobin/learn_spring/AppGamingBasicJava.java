package com.hobin.learn_spring;

import com.hobin.learn_spring.game.MarioGame;
import com.hobin.learn_spring.game.GameRunner; 

public class AppGamingBasicJava {

	public static void main(String[] args) {

		var marioGame = new MarioGame();
		var gameRunner = new GameRunner(marioGame);
		gameRunner.run();
	}

}
