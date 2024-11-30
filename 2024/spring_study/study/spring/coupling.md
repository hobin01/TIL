OOP에서 중요한 내용 중 하나

강한 결합 : 아래와 같이 특정 class를 반드시 사용하여야 동작되는 결합 구조 

```java
package com.hobin.learn_spring.game;

public class MarioGame {
	public void up() {
		System.out.println("Jump!");
	}
	public void down() {
		System.out.println("Go into a hole!");
	}
	public void left() {
		System.out.println("Go back!");
	}
	public void right() {
		System.out.println("Accelerate!");
	}
}
```

```java
package com.hobin.learn_spring.game;

public class SuperContraGame {
	public void up() {
		System.out.println("Jump!");
	}
	public void down() {
		System.out.println("Sit down!");
	}
	public void left() {
		System.out.println("Go back!");
	}
	public void right() {
		System.out.println("Shoot a bullet!");
	}
}
```

```java
package com.hobin.learn_spring.game;

public class GameRunner {
	// private MarioGame game;
	private SuperContraGame game;
	
	public GameRunner(SuperContraGame game) {
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

MarioGame, SuperContraGame 모두 up, down, left, right을 동일한 기능으로 가지고 있지만

GameRunner에서 사용하려면 매번 타입 변경을 해야 함 

이렇게 특정 class와 결합되어 있는 것이 강한 결합 상태

----

약한 결합 : interface를 이용해서 공통 지점을 만드는 것 

interface 정의 : interface 키워드 이용해서 정의

```java
package com.hobin.learn_spring.game;

public interface GamingConsole {
	void up();
	void down();
	void left();
	void right();
}
```

interface 적용 : implements 키워드로 적용

```java
package com.hobin.learn_spring.game;

public class MarioGame implements GamingConsole {
	
	public void up() {
		System.out.println("Jump!");
	}
	
	public void down() {
		System.out.println("Go into a hole!");
	}
	
	public void left() {
		System.out.println("Go back!");
	}
	
	public void right() {
		System.out.println("Accelerate!");
	}
	
}
```

```java
package com.hobin.learn_spring.game;

public class SuperContraGame implements GamingConsole {
	public void up() {
		System.out.println("Jump!");
	}
	
	public void down() {
		System.out.println("Sit down!");
	}
	
	public void left() {
		System.out.println("Go back!");
	}
	
	public void right() {
		System.out.println("Shoot a bullet!");
	}
}
```

이제 interface로 묶였으므로, GameRunner class에서도 해당 interface를 인수로 갖는 등 적용해주면 됨

```java
package com.hobin.learn_spring.game;

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

아래와 같이 main 동작하게 됨

```java
package com.hobin.learn_spring;

import com.hobin.learn_spring.game.MarioGame;
import com.hobin.learn_spring.game.SuperContraGame; 
import com.hobin.learn_spring.game.GameRunner; 

public class AppGamingBasicJava {

	public static void main(String[] args) {

		var game1 = new MarioGame();
		var gameRunner1 = new GameRunner(game1);
		gameRunner1.run();
		
		var game2 = new SuperContraGame();
		var gameRunner2 = new GameRunner(game2);
		gameRunner2.run();
	}

}
```

