package com.hobin.learn_spring;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import com.hobin.learn_spring.game.GameRunner;
import com.hobin.learn_spring.game.GamingConsole;
import com.hobin.learn_spring.game.PacmanGame;

@Configuration
public class GamingConfiguration {

	@Bean
	public GamingConsole game() {
		var game = new PacmanGame();
		return game;
	}
	
	@Bean
	public GameRunner gameRunner(GamingConsole game) {
		var gameRunner = new GameRunner(game);
		return gameRunner;
	}
}
