package com.hobin.learn_spring.game;

import org.springframework.stereotype.Component;

@Component
public interface GamingConsole {
	void up();
	void down();
	void left();
	void right();
}
