Component : spring에서 객체 생성 및 관리를 대신 처리하도록 함을 목적으로 사용

반복적인 Bean 등록을 간소화하게 해줌

수동으로 Bean 등록 시, config로 일일이 설정해야 하지만, @Component annotation으로 자동으로 Bean 등록


- Bean 수동 등록

GamingConfiguration class를 context로 가져와, 해당 configuration에 등록된 Bean을 가져와 처리함

```java
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
```

```java
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
```

- Component를 이용한 Bean 자동 등록

context를 자신으로 지정 후, @ComponentScan으로 어떤 컴포넌트를 이용해 Bean으로 사용할 지를 결정

```java
package com.hobin.learn_spring;

import com.hobin.learn_spring.game.GameRunner;
import com.hobin.learn_spring.game.GamingConsole;

import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;

@Configuration
@ComponentScan("com.hobin.learn_spring.game")
public class GamingAppLauncherApplication {

	public static void main(String[] args) {
		try(var context = new AnnotationConfigApplicationContext(GamingAppLauncherApplication.class)) {
			context.getBean(GamingConsole.class).up();

			context.getBean(GameRunner.class).run();
		}
	}

}
```

단, component로 사용할 class에도 @Component annotation을 추가

```java
package com.hobin.learn_spring.game;

import org.springframework.stereotype.Component;

@Component
public class GameRunner {
	
	// private MarioGame game;
	private GamingConsole game;
	
	public GameRunner(GamingConsole game) {
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
```

그리고 아래와 같이 인터페이스로 여러 하위 객체가 있을 시, @Component는 하나만 지정해야 하며, 
그렇지 않은 경우, @Primary 지정 또는 @Qualifier 지정을 해야 함

```java
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
```

```java
package com.hobin.learn_spring.game;

import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Component;

@Component
public class GameRunner {
	
	private GamingConsole game;
	
	public GameRunner(@Qualifier("SuperContraGame") GamingConsole game) {
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
```

```java
package com.hobin.learn_spring;

import com.hobin.learn_spring.game.GameRunner;
import com.hobin.learn_spring.game.GamingConsole;

import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;

@Configuration
@ComponentScan("com.hobin.learn_spring.game")
public class GamingAppLauncherApplication {

	public static void main(String[] args) {
		try(var context = new AnnotationConfigApplicationContext(GamingAppLauncherApplication.class)) {
			context.getBean(GamingConsole.class).up();

			context.getBean(GameRunner.class).run();
		}
	}
}
```
